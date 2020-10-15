from typing import List, Tuple

from domain.types import YUVImage, Convolution


class Sample:

    def __init__(self, image: YUVImage, channel: int, up_left_h: int, up_left_w: int,
                 down_right_h: int, down_right_w: int, subsample: Convolution,
                 upsample: Convolution):
        self.channel = {0: 'y', 1: 'u', 2: 'v'}[channel]
        self.subsample = subsample
        self.upsample = upsample

        self.up_left_h = up_left_h
        self.up_left_w = up_left_w
        self.down_right_h = down_right_h
        self.down_right_w = down_right_w

        h_size = down_right_h - up_left_h + 1
        w_size = down_right_w - up_left_w + 1
        self.values = [[0 for _ in range(w_size)] for _ in range(h_size)]

        sample_i = 0
        for i in range(up_left_h, down_right_h):
            sample_j = 0
            for j in range(up_left_w, down_right_w):
                self.values[sample_i][sample_j] = image[i][j][channel]
                sample_j += 1
            sample_i += 1

    def __str__(self):
        print(self.values)

    __rep__ = __str__

    def apply_subsample(self):
        self.values = self.subsample(self.values)

    def get_upsample(self):
        return self.upsample(self.values)


# One list for each channel
SampledYUV = Tuple[List[Sample], List[Sample], List[Sample]]