from concurrent.futures import ThreadPoolExecutor, as_completed
from typing import List

from domain.sample import Sample, SampledYUV
from domain.types import RGBImage, YUVImage, Convolution, Matrix
from helper.walk import zig_zag_walk
from repository.repository import Repository
from helper.convolutions import identity, average_2d, up_sample
from helper.math import forward_dct, component_wise_division
from helper.quants import Q
from service.io import IOService


class EncoderService:

    def __init__(self, repo: Repository):
        self.repository = repo

    def convert_rgb_yuv(self):
        self.repository.yuvs = list(
            map(self._rgb_image_to_yuv_image, self.repository.rgbs))

    def subsample(self):
        self.repository.samples = list(
            map(EncoderService._subsample_yuv, self.repository.yuvs))

    def quantisize(self):
        # 8x8 blocks are required for DCT - upsample Cb and Cr channels
        with ThreadPoolExecutor(max_workers=8) as executor:
            for sampled_yuv in self.repository.samples:
                for channel in range(1, 3):
                    for sample in sampled_yuv[channel]:
                        sample.values = sample.get_upsample()
                        # Sample is now in 8x8 format, no need to upsample again in decoder
                        sample.upsample = identity
                for channel in sampled_yuv:
                    for sample in channel:
                        executor.submit(
                            EncoderService._quant_sample_subtask, sample)

    def encode(self):
        with ThreadPoolExecutor(max_workers=8) as executor:
            for idx, sampled_yuv in enumerate(self.repository.samples):
                encoded_bytes = bytes(0)
                for y_sample, u_sample, v_sample in sampled_yuv:
                    EncoderService._encode_sample_subtask(
                        encoded_bytes, y_sample)
                    EncoderService._encode_sample_subtask(
                        encoded_bytes, u_sample)
                    EncoderService._encode_sample_subtask(
                        encoded_bytes, v_sample)
                assert len(encoded_bytes) != 0
                self.repository.bytes.append(encoded_bytes)

    @staticmethod
    def _get_amplitude_size(amplitude: int) -> int:
        """Get number of bits necessary to represent amplitude."""
        assert isinstance(amplitude, int)
        pw = 1
        while True:
            if amplitude <= (2 ** pw) - 1:
                break
            pw += 1
        return pw

    @staticmethod
    def _encode_sample_subtask(encoded_bytes: str, sample: Matrix):
        walk = zig_zag_walk(sample)
        sample_entropy_encoding = []
        sample_entropy_encoding.extend([
            EncoderService._get_amplitude_size(walk[0]),
            walk[0]
        ])
        count_zeros = 0
        for value in walk:
            if value == 0:
                count_zeros += 1
                continue
            else:
                sample_entropy_encoding.extend([
                    count_zeros,
                    EncoderService._get_amplitude_size(value),
                    value
                ])
                count_zeros = 0
        sample_entropy_encoding = [x.to_bytes(
            2, byteorder='big') for x in sample_entropy_encoding]
        sample_entropy_encoding.extend([0, 0])
        encoded_bytes += ''.join(sample_entropy_encoding)

    @staticmethod
    def _quant_sample_subtask(sample: Sample):
        """Quantizize sample in-place."""
        quant_values = forward_dct(sample.values)
        quant_values = component_wise_division(quant_values, Q)
        sample.values = quant_values

    # noinspection DuplicatedCode
    @staticmethod
    def _rgb_image_to_yuv_image(rgb: RGBImage) -> YUVImage:
        h, w = len(rgb), len(rgb[0])
        h_step, w_step = h // 8, w // 8
        yuv = [[(0, 0, 0) for _ in range(w)] for _ in range(h)]

        with ThreadPoolExecutor(max_workers=8) as executor:
            for top_left_h in range(0, h, h_step):
                for top_left_w in range(0, w, w_step):
                    bot_right_h = min(top_left_h + h_step - 1, h - 1)
                    bot_right_w = min(top_left_w + w_step - 1, w - 1)
                    executor.submit(
                        EncoderService._rgb_to_yuv_conv_subtask, rgb, yuv,
                        top_left_h, top_left_w, bot_right_h, bot_right_w
                    )
        return yuv

    @staticmethod
    def _rgb_to_yuv_conv_subtask(rgb: RGBImage, yuv: YUVImage, top_left_h: int,
                                 top_left_w: int, bottom_right_h: int, bottom_right_w: int):
        """Convert coordinates defined subregion of RGB image to YUV in parallel."""
        for i in range(top_left_h, bottom_right_h + 1):
            for j in range(top_left_w, bottom_right_w + 1):
                r, g, b = rgb[i][j]
                yuv[i][j] = (
                    0.299 * r + 0.587 * g + 0.114 * b,
                    -0.147 * r - 0.289 * g + 0.436 * b,
                    0.615 * r - 0.515 * g - 0.100 * b
                )

    @staticmethod
    def _subsample_yuv(image: YUVImage) -> SampledYUV:
        EncoderService._add_padding(image, 8)
        futures, result = [], []
        def avg_conv(img): return average_2d(img, 2)
        def up_conv(img): return up_sample(img, 2)
        with ThreadPoolExecutor(max_workers=3) as executor:
            # Extract Y channel
            futures.append(executor.submit(
                EncoderService._extract_channel, image, 0, 8, identity, identity
            ))
            # Extract U channel
            futures.append(executor.submit(
                EncoderService._extract_channel, image, 1, 8, avg_conv, up_conv
            ))
            # Extract V channel
            futures.append(executor.submit(
                EncoderService._extract_channel, image, 2, 8, avg_conv, up_conv
            ))
            for future in as_completed(futures):
                result.append(future.result())
        # Executor seems not to guarantee order of the futures; that or I messed up somewhere above
        # Anyways, big sort incoming
        result.sort(key=lambda ch: {'y': 0, 'u': 1, 'v': 2}[ch[0].channel])
        assert result[0][0].channel == 'y' and result[1][0].channel == 'u' and result[2][0].channel == 'v'
        return tuple(result)

    @staticmethod
    def _add_padding(image: YUVImage, dim: int):
        # Add black pixels as padding in-place
        black_yuv = (0, 0, 0)
        while len(image) % dim != 0:
            image.append([black_yuv for _ in range(len(image[0]))])
        for row in image:
            while len(row) % dim != 0:
                row.append(black_yuv)

    @staticmethod
    def _extract_channel(image: YUVImage, channel: int, dim: int,
                         subsample: Convolution, upsample: Convolution) -> List[Sample]:
        h, w = len(image), len(image[0])
        samples = []
        for up_left_h in range(0, h, dim):
            for up_left_w in range(0, w, dim):
                # Avoid going out of bounds
                down_right_h = up_left_h + dim - 1
                down_right_w = up_left_w + dim - 1
                sample = Sample(
                    image, channel, up_left_h,
                    up_left_w, down_right_h, down_right_w,
                    subsample, upsample
                )
                sample.apply_subsample()
                samples.append(sample)
        return samples
