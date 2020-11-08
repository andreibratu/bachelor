class Repository:

    def __init__(self):
        self.rgbs, self.yuvs, self.samples = [], [], []
        self.upsamples, self.ups_yuvs, self.ups_rgbs = [], [], []
        self.bytes = []