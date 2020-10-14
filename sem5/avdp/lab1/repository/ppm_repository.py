from concurrent.futures import ThreadPoolExecutor, as_completed


class PPMRepository:

    @staticmethod
    def read_file(filename):
        # Read PPM3 file

        with open(filename, 'r') as f:
            # Skip descriptive lines
            next(f)
            next(f)

            height, width = [int(v) for v in f.readline().split()]
            image = [[None for _ in range(width)] for _ in range(height)]
            for i in range(height):
                for j in range(width):
                    r, g, b = [int(v) for v in [f.readline(), f.readline(), f.readline()]]
                    image[i][j] = (r, g, b)

        return image

    def __init__(self, filenames):
        self.rgbs = []
        self.yuvs = []
        self.samples = []
        with ThreadPoolExecutor(max_workers=5) as executor:
            futures = [executor.submit(PPMRepository.read_file, fn) for idx, fn in enumerate(filenames)]
            self.rgbs = [future.result() for future in futures]