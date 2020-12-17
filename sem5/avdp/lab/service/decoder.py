import json
import math
import pickle
from concurrent.futures.thread import ThreadPoolExecutor
from typing import Tuple, List

from domain.sample import Sample, SampledYUV
from domain.types import Matrix, YUVImage, RGBImage
from helper.math import component_wise_multiplication, inverse_dct
from helper.quants import Q
from helper.walk import reverse_zig_zag_walk

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


def decode_entropy(quant_channels) -> Tuple[List[Sample], List[Sample], List[Sample]]:
    with open("precompute_bit.json") as fp:
        _, bit_to_int = json.load(fp)
    with open("output", 'rb') as fp:
        output = pickle.load(fp)
    samples = []
    sample = []
    first_byte = True
    while len(output) != 0:
        if first_byte:
            first_byte = False
            byts = output[:8]
            output = output[8:]
            how_many = int(byts, base=2)
            if how_many == 0:
                # DC coefficient is somehow 0, append and whatever
                sample.append(0)
                continue
            # Else we are going to read DC coefficient
            byts = output[:how_many]
            assert (len(byts) == how_many)
            old_len = len(output)
            output = output[how_many:]
            assert len(output) == old_len - how_many
            value = int(bit_to_int[byts])
            sample.append(value)
        else:
            byts = output[:8]
            output = output[8:]
            how_many = int(byts, base=2)
            print('HOW_MANY', how_many)
            byts = output[:8]
            output = output[8:]
            next_how_many = int(byts, base=2)
            # Check if next byte is also 0 - if yes, we finished a sample
            if how_many == 0 and next_how_many == 0:
                # Sample is finished
                while len(sample) != 64:
                    sample.append(0)
                first_byte = True
                samples.append(reverse_zig_zag_walk(sample))
                sample = []
                continue
            else:
                # Not finished, append zeros before AC coefficient
                for _ in range(how_many):
                    sample.append(0)
                # Now append the AC coefficient
                byts = output[:next_how_many]
                output = output[next_how_many:]
                sample.append(int(bit_to_int[byts]))

    assert(len(samples) % 3 == 0)
    size_ch = len(samples) // 3
    y_samples = samples[:size_ch]
    samples = samples[size_ch:]
    u_samples = samples[:size_ch]
    samples = samples[size_ch:]
    v_samples = samples[:]

    assert len(y_samples) == len(quant_channels[0])
    for y_s_r, y_s in zip(y_samples, quant_channels[0]):
        assert len(y_s_r) == 8
        assert len(y_s_r[0]) == 8
        for i in range(8):
            for j in range(8):
                assert y_s.values[i][j] == y_s_r[i][j]
        y_s.values = y_s_r

    assert len(u_samples) == len(quant_channels[1])
    for u_s_r, u_s in zip(u_samples, quant_channels[1]):
        u_s.values = u_s_r

    assert len(v_samples) == len(quant_channels[2])
    for v_s_r, v_s in zip(v_samples, quant_channels[2]):
        v_s.values = v_s_r

    return quant_channels
