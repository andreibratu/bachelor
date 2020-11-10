import os
from concurrent.futures.thread import ThreadPoolExecutor
from typing import List

from domain.types import RGBImage
from repository.repository import Repository


class IOService:

    def __init__(self, repo: Repository, filenames: List[str]):
        self.repository = repo
        self.input_filenames = filenames

    def read_images(self):
        with ThreadPoolExecutor(max_workers=4) as executor:
            futures = [executor.submit(IOService._read_file, fn) for idx, fn in enumerate(self.input_filenames)]
        self.repository.rgbs = [future.result() for future in futures]

    def write_results_to_ppm(self):
        with ThreadPoolExecutor(max_workers=4) as executor:
            for idx, rgb in enumerate(self.repository.ups_rgbs):
                IOService.write_rgb_image(idx, rgb)
                # executor.submit(IOService._write_file, idx, rgb)

    @staticmethod
    def _read_file(filename):
        # Read PPM3 file

        with open(filename, 'r') as f:
            # Skip descriptive lines
            next(f)
            next(f)

            width, height = [int(v) for v in f.readline().split()]
            image = [[None for _ in range(width)] for _ in range(height)]
            # Skip max value of pixels - assumed 255
            next(f)
            for i in range(height):
                for j in range(width):
                    r, g, b = [int(v) for v in [f.readline(), f.readline(), f.readline()]]
                    image[i][j] = (r, g, b)

        return image

    @staticmethod
    def write_rgb_image(idx: int, rgb: RGBImage):
        h, w = len(rgb), len(rgb[0])
        with open(f"ups_rgb_{idx}.ppm", "w+") as f:
            f.write("P3\n")
            f.write("# WRITTEN BY MY DUMBASS VIDEO DECODER\n")
            f.write(f"{w} {h}\n")
            f.write(f"{255}\n")
            for i in range(h):
                for j in range(w):
                    f.write(f"{rgb[i][j][0]}\n")
                    f.write(f"{rgb[i][j][1]}\n")
                    f.write(f"{rgb[i][j][2]}\n")