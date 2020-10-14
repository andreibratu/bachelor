from typing import List, Tuple, Callable

Pixel = Tuple[float, float, float]
RGBPixel = Pixel
YUVPixel = Pixel

Matrix = List[List[float]]
YUVImage = List[List[YUVPixel]]
RGBImage = List[List[RGBPixel]]

Convolution = Callable[[Matrix], Matrix]