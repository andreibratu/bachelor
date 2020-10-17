import math
from concurrent.futures.thread import ThreadPoolExecutor
from typing import Tuple, List

from domain.sample import Sample
from domain.types import Matrix, YUVImage, RGBImage
from helper.math import component_wise_multiplication, inverse_dct
from helper.quants import Q
from repository.ppm_repository import PPMRepository

Upsample = Tuple[Matrix, int, int, int, int]


class DecoderService:

    def __init__(self, repo: PPMRepository):
        self.repository = repo

    def upsample(self):
        for sampled_yuv_chns in self.repository.samples:
             self.repository.upsamples.append(
                (
                     list(map(DecoderService._get_upsample_info, sampled_yuv_chns[0])),
                    list(map(DecoderService._get_upsample_info, sampled_yuv_chns[1])),
                    list(map(DecoderService._get_upsample_info, sampled_yuv_chns[2]))
                )
            )

    def reconstruct_yuvs(self):
        self.repository.ups_yuvs = list(map(DecoderService._reconstruct_yuv, self.repository.upsamples))

    def yuvs_to_rgbs(self):
        self.repository.ups_rgbs = list(map(DecoderService._yuv_to_rgb, self.repository.ups_yuvs))

    def dequantizize(self):
        for quant_yuv in self.repository.samples:
            for channel in quant_yuv:
                for sample in channel:
                    dequant_values = component_wise_multiplication(sample.values, Q)
                    dequant_values = inverse_dct(dequant_values)
                    sample.values = dequant_values

    @staticmethod
    def _get_upsample_info(sample: Sample) -> Upsample:
        """Get a sample's upsampled values and its coordinates in the original YUV image."""
        return (
            sample.get_upsample(),
            sample.up_left_h, sample.up_left_w,
            sample.down_right_h, sample.down_right_w
        )

    @staticmethod
    def _find_image_coords(channel: List[Upsample]) -> Tuple[int, int, int, int]:
        """Leverage EncoderService._extract_channel processing order to find the original size of the image.
        The samples were extracted in a left to right, up-bottom manner. Thus the minimum coordinates
        will be found in the first sample while maximum coordinates will be found in the last sample.
        :param channel: Image channel processed by _get_upsample_info
        :return: Coordinates of the upper left and bottom right corners of the original YUV image.
        """
        first_sample, last_sample = channel[0], channel[-1]
        return first_sample[1], first_sample[2], last_sample[3], last_sample[4]

    @staticmethod
    def _reconstruct_yuv_subregion(yuv: YUVImage, y_sample: Upsample, u_sample: Upsample, v_sample: Upsample):
        i, j = 0, 0  # Used  to iterate through the upsampled values
        up_left_h, up_left_w, down_right_h, down_right_w = y_sample[1:]
        # For loops for iterating through original image indices
        for ii in range(up_left_h, down_right_h+1):
            j = 0
            for jj in range(up_left_w, down_right_w+1):
                yuv[ii][jj] = y_sample[0][i][j], u_sample[0][i][j], v_sample[0][i][j]
                j += 1
            i += 1

    @staticmethod
    def _reconstruct_yuv(yuv_channels: Tuple[List[Upsample], List[Upsample], List[Upsample]]) -> YUVImage:
        y, u, v = yuv_channels
        # min_h, max_h are obviously equal to zero but whatever
        min_h, min_w, max_h, max_w = DecoderService._find_image_coords(y)
        yuv = [[(0, 0, 0) for _ in range(min_w, max_w+1)] for _ in range(min_h, max_h+1)]
        with ThreadPoolExecutor(max_workers=8) as executor:
            for y_sample, u_sample, v_sample in zip(y, u, v):
                executor.submit(
                    DecoderService._reconstruct_yuv_subregion,
                    yuv, y_sample, u_sample, v_sample
                )
        return yuv

    @staticmethod
    def yuv_to_rgb_conv_subtask(yuv: YUVImage, rgb: RGBImage, top_left_h: int,
                                top_left_w: int, bottom_right_h: int, bottom_right_w: int):
        """Convert coordinates defined subregion of YUV image to RGB in parallel."""
        for i in range(top_left_h, bottom_right_h + 1):
            for j in range(top_left_w, bottom_right_w + 1):
                y, u, v = yuv[i][j]

                def _round_to_rgb_interval(x: float) -> int:
                    if x < 0:
                        return 0
                    if x > 255:
                        return 255
                    return math.floor(x)

                rgb[i][j] = (
                    _round_to_rgb_interval(y + 1.140 * v),
                    _round_to_rgb_interval(y - 0.395 * u - 0.581 * v),
                    _round_to_rgb_interval(y + 2.032 * u)
                )

    # noinspection DuplicatedCode
    @staticmethod
    def _yuv_to_rgb(yuv: YUVImage) -> RGBImage:
        h, w = len(yuv), len(yuv[0])
        h_step, w_step = h // 8, w // 8
        rgb = [[(0, 0, 0) for _ in range(w)] for _ in range(h)]

        with ThreadPoolExecutor(max_workers=8) as executor:
            for top_left_h in range(0, h, h_step):
                for top_left_w in range(0, w, w_step):
                    bot_right_h = min(top_left_h + h_step - 1, h - 1)
                    bot_right_w = min(top_left_w + w_step - 1, w - 1)
                    executor.submit(
                        DecoderService.yuv_to_rgb_conv_subtask, yuv, rgb,
                        top_left_h, top_left_w, bot_right_h, bot_right_w
                    )
        return rgb
