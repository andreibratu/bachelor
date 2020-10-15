from concurrent.futures.thread import ThreadPoolExecutor
from typing import Tuple, List

from domain.sample import Sample
from domain.types import Matrix, YUVImage, RGBImage
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

    def write_rgbs_to_ppm(self):
        for idx, rgb in enumerate(self.repository.ups_rgbs):
            h, w = len(rgb), len(rgb[0])
            with open(f"ups_rgb_{idx}", "w+") as f:
                f.write("P3\n")
                f.write("# WRITTEN BY MY DUMBASS VIDEO DECODER")
                f.write(f"{h} {w}\n")
                for i in range(h):
                    for j in range(w):
                        rgb_line = "\n".join(v for v in rgb[i][j]) + "\n"
                        f.write(rgb_line)

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
    def _reconstruct_yuv_sector(yuv: YUVImage, y_sample: Upsample, u_sample: Upsample, v_sample: Upsample):
        assert (y_sample[1:] == u_sample[1:] == v_sample[1:], "Coordinates not aligned!")
        i, j = 0, 0  # Used  to iterate through the upsampled values
        up_left_h, up_left_w, down_right_h, down_right_w = y_sample[1:]
        # For loops for iterating through original image indices
        for ii in range(up_left_h, down_right_h):
            for jj in range(up_left_w, down_right_w):
                yuv[ii][jj] = y_sample[0][i][j], u_sample[0][i][j], v_sample[0][i][j]
                j += 1
            i += 1

    @staticmethod
    def _reconstruct_yuv(yuv_channels: Tuple[List[Upsample], List[Upsample], List[Upsample]]) -> YUVImage:
        y, u, v = yuv_channels
        min_h, min_w, max_h, max_w = DecoderService._find_image_coords(y)
        yuv = [[(0, 0, 0) for _ in range(min_w, max_w)] for _ in range(min_h, max_h)]
        assert(len(y) == len(u) == len(v), "Channels contain different amount samples!")
        with ThreadPoolExecutor(max_workers=8) as executor:
            for y_sample, u_sample, v_sample in zip(y, u, v):
                executor.submit(DecoderService._reconstruct_yuv_sector, yuv, y_sample, u_sample, v_sample)
        return yuv

    @staticmethod
    def _divide_conquer_rgb_conv_task(yuv: YUVImage, rgb: RGBImage, top_left_h: int,
                                      top_left_w: int, bottom_right_h: int, bottom_right_w: int):
        for i in range(top_left_h, bottom_right_h + 1):
            for j in range(top_left_w, bottom_right_w + 1):
                y, u, v = yuv[i][j]
                rgb[i][j] = (
                    int(y + 1.402 * (v - 128)),
                    int(y - 0.344136 * (u - 128) - 0.714136 * (v - 128)),
                    int(y + 1.772 * (u - 128))
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
                        DecoderService._divide_conquer_rgb_conv_task, yuv, rgb,
                        top_left_h, top_left_w, bot_right_h, bot_right_w
                    )
        return rgb
