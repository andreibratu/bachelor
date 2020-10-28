from repository.ppm_repository import PPMRepository
from service.decoder import DecoderService
from service.encoder import EncoderService
from service.io import IOService

filenames = [r"C:\Users\bratu\Desktop\bachelor\sem5\avdp\lab1\input_p3.ppm"]
repository = PPMRepository()
io = IOService(repository, filenames)
io.read_images()
encoder = EncoderService(repository)
decoder = DecoderService(repository)
encoder.convert_rgb_yuv()
encoder.subsample()
encoder.quantisize()
decoder.dequantisize()
decoder.upsample()
decoder.reconstruct_yuvs()
decoder.yuvs_to_rgbs()
io.write_results_to_ppm()
