import math
from concurrent.futures.thread import ThreadPoolExecutor
from typing import Tuple, List

from domain.sample import Sample, SampledYUV
from domain.types import Matrix, YUVImage, RGBImage
from helper.math import component_wise_multiplication, inverse_dct
from helper.quants import Q


Upsample = Tuple[Matrix, int, int, int, int]


def upsample(samples: SampledYUV):
    def _get_upsample_info(sample: Sample) -> Upsample:
        """Get a sample's upsampled values and its coordinates in the original YUV image."""
        return (
            sample.get_upsample(),
            sample.up_left_h, sample.up_left_w,
            sample.down_right_h, sample.down_right_w
        )

    return tuple([
        list(map(_get_upsample_info, samples[0])),
        list(map(_get_upsample_info, samples[1])),
        list(map(_get_upsample_info, samples[2]))
    ])


def reconstruct_yuv(up_channels) -> YUVImage:
    def _find_image_coords(channel: List[Upsample]) -> Tuple[int, int, int, int]:
        """Leverage EncoderService._extract_channel processing order to find the original size of the image.
        The samples were extracted in a left to right, up-bottom manner. Thus the minimum coordinates
        will be found in the first sample while maximum coordinates will be found in the last sample.
        :param channel: Image channel processed by _get_upsample_info
        :return: Coordinates of the upper left and bottom right corners of the original YUV image.
        """
        first_sample, last_sample = channel[0], channel[-1]
        return first_sample[1], first_sample[2], last_sample[3], last_sample[4]

    y, u, v = up_channels
    # min_h, max_h are obviously equal to zero but whatever
    min_h, min_w, max_h, max_w = _find_image_coords(y)
    assert min_w == min_h == 0
    yuv = [[(0, 0, 0) for _ in range(min_w, max_w + 1)]
           for _ in range(min_h, max_h + 1)]
    with ThreadPoolExecutor(max_workers=4) as executor:
        for idx in range(len(y)):
            executor.submit(
                _reconstruct_yuv_subregion,
                yuv, y[idx], u[idx], v[idx]
            )
    return yuv


def yuv_to_rgb(yuv: YUVImage) -> RGBImage:
    h, w = len(yuv), len(yuv[0])
    h_step, w_step = h // 8, w // 8
    rgb = [[(0, 0, 0) for _ in range(w)] for _ in range(h)]

    with ThreadPoolExecutor(max_workers=8) as executor:
        for top_left_h in range(0, h, h_step):
            for top_left_w in range(0, w, w_step):
                bot_right_h = top_left_h + h_step - 1
                bot_right_w = top_left_w + w_step - 1
                executor.submit(
                    _yuv_to_rgb_conv_subtask, yuv, rgb,
                    top_left_h, top_left_w, bot_right_h, bot_right_w
                )
    return rgb


def _reconstruct_yuv_subregion(yuv: YUVImage, y_sample: Upsample, u_sample: Upsample, v_sample: Upsample):
    i, j = 0, 0  # Used  to iterate through the upsampled values
    up_left_h, up_left_w, down_right_h, down_right_w = y_sample[1:]
    # For loops for iterating through original image indices
    for ii in range(up_left_h, down_right_h + 1):
        j = 0
        for jj in range(up_left_w, down_right_w + 1):
            yuv[ii][jj] = y_sample[0][i][j], u_sample[0][i][j], v_sample[0][i][j]
            j += 1
        i += 1


def _yuv_to_rgb_conv_subtask(yuv: YUVImage, rgb: RGBImage, top_left_h: int,
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


def dequantisize(quant_channels):
    for channel in quant_channels:
        for sample in channel:
            dequant_values = component_wise_multiplication(sample.values, Q)
            dequant_values = inverse_dct(dequant_values)
            sample.values = dequant_values
    return quant_channels


# class DecoderService:
#
#
#     def decode(self):
#         for encoded_img in self.repository.bytes:
#             y_samples, u_samples, v_samples = [], [], []
#             bytes_iter = iter(encoded_img)
#             flag = 0
#             try:
#                 while True:
#                     values = DecoderService._decode_sample(bytes_iter)
#
#             except StopIteration:
#                 # Iterator was exhausted, as did my patience
#                 pass
#
#     @staticmethod
#     def _decode_sample(bytes_iter: iter) -> Matrix:
#         decoded_walk = []
#         # Read first number
#         first_size = DecoderService._read_integer(bytes_iter, 1)
#         decoded_walk.append(DecoderService._read_integer(bytes, first_size))
#         while True:
#             # Read until two zero bytes are reached
#             count_zero = DecoderService._read_integer(bytes_iter, 1)
#             size = DecoderService._read_integer(bytes_iter, 1)
#             if count_zero == 0 and size == 0:
#                 break
#             decoded_walk.extend([0 for _ in range(count_zero)])
#             decoded_walk.append(DecoderService._read_integer(bytes_iter, size))
#         # Encoding will not include ending zeros, add them if needed
#         decoded_walk.extend([0 for _ in range(64 - len(decoded_walk))])
#         assert len(decoded_walk) == 64
#
#     @staticmethod
#     def _read_integer(bytes_iter: iter, int_size: int) -> int:
#         """Read int_size bytes from iterator and """
#         int_bytes = bytes(0)
#         for _ in range(int_size):
#             int_bytes += next(bytes_iter)
#         return int.from_bytes(int_bytes, "big", signed=True)

