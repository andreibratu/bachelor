from domain.types import RGBImage


def read_rgb_image(filename):
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


def write_rgb_image(rgb: RGBImage):
    h, w = len(rgb), len(rgb[0])
    with open(f"result.ppm", "w+") as f:
        f.write("P3\n")
        f.write("# WRITTEN BY VIDEO DECODER\n")
        f.write(f"{w} {h}\n")
        f.write(f"{255}\n")
        for i in range(h):
            for j in range(w):
                f.write(f"{rgb[i][j][0]}\n")
                f.write(f"{rgb[i][j][1]}\n")
                f.write(f"{rgb[i][j][2]}\n")
