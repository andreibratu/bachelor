from concurrent.futures import ThreadPoolExecutor, as_completed

from domain.sample import Sample, SampledChannel, SampledYUV
from domain.types import RGBPixel, YUVPixel, RGBImage, YUVImage, Convolution
from repository.ppm_repository import PPMRepository
from service.convolutions import identity, average_2d, up_sample


class EncoderService:

    def __init__(self, repo: PPMRepository):
        self.repository = repo

    def convert_rgb_yuv(self):
        self.repository.yuvs = list(map(self._rgb_image_to_yuv_image, self.repository.rgbs))

    def subsample(self):
        self.repository.samples = list(map(EncoderService._subsample_yuv, self.repository.yuvs))

    @staticmethod
    def _rgb_image_to_yuv_image(rgb: RGBImage) -> YUVImage:
        h, w = len(rgb), len(rgb[0])
        h_step, w_step = h // 8, w // 8
        yuv = [[(0, 0, 0) for _ in range(w)] for _ in range(h)]

        with ThreadPoolExecutor(max_workers=5) as executor:
            for top_left_h in range(0, h, h_step):
                for top_left_w in range(0, w, w_step):
                    bot_right_h = min(top_left_h + h_step - 1, h - 1)
                    bot_right_w = min(top_left_w + w_step - 1, w - 1)
                    executor.submit(
                        EncoderService._divide_conquer_yuv_conv_task, rgb, yuv,
                        top_left_h, top_left_w, bot_right_h, bot_right_w
                    )
        return yuv

    @staticmethod
    def _divide_conquer_yuv_conv_task(rgb: RGBImage, yuv: YUVImage, top_left_h: int,
                                      top_left_w: int, bottom_right_h: int, bottom_right_w: int):
        for i in range(top_left_h, bottom_right_h + 1):
            for j in range(top_left_w, bottom_right_w + 1):
                yuv[i][j] = rgb[i][j]

    @staticmethod
    def _rgb_pixel_to_yuv_pixel(pixel: RGBPixel) -> YUVPixel:
        r, g, b = pixel
        return (
            0.299 * r + 0.587 * g + 0.114 * b,
            128 - 0.1687 * r - 0.3312 * g + 0.5 * b,
            128 + 0.5 * r - 0.4186 * g - 0.0813 * b
        )

    @staticmethod
    def _subsample_yuv(image: YUVImage) -> SampledYUV:
        EncoderService._add_padding(image, 8)
        futures, result = [], []
        avg_conv = lambda img: average_2d(img, 2)
        up_conv = lambda img: up_sample(img, 2)
        with ThreadPoolExecutor(max_workers=3) as executor:
            futures.append(executor.submit(
                EncoderService._extract_channel, image, 0, 8, identity, identity
            ))
            futures.append(executor.submit(
                EncoderService._extract_channel, image, 1, 8, avg_conv, up_conv
            ))
            futures.append(executor.submit(
                EncoderService._extract_channel, image, 2, 8, avg_conv, up_conv
            ))
            for future in as_completed(futures):
                result.append(future.result())
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
                         subsample: Convolution, upsample: Convolution) -> SampledChannel:
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
                sample.apply_subsampling()
                samples.append(sample)
        return samples