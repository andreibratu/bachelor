import time

from service.decoder import upsample, reconstruct_yuv, yuv_to_rgb, dequantisize
from service.encoder import rgb_image_to_yuv_image, subsample_yuv, quantisize
from service.io import read_rgb_image, write_rgb_image

if __name__ == '__main__':
    start_time = time.time()
    image = read_rgb_image(r"input_p3.ppm")
    yuv = rgb_image_to_yuv_image(image)
    sampled_channels = subsample_yuv(yuv)
    quant_channels = quantisize(sampled_channels)
    sampled_channels = dequantisize(quant_channels)
    upsampled_channels = upsample(sampled_channels)
    yuv = reconstruct_yuv(upsampled_channels)
    rgb = yuv_to_rgb(yuv)
    write_rgb_image(rgb)
    print("--- %s seconds ---" % (time.time() - start_time))
