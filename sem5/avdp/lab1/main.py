from repository.ppm_repository import PPMRepository
from service.encoder import EncoderService

filenames = [r"C:\Users\bratu\Desktop\bachelor\sem5\avdp\lab1\input_p3.ppm"]
repository = PPMRepository(filenames)
encoder = EncoderService(repository)
encoder.convert_rgb_yuv()
encoder.subsample()
