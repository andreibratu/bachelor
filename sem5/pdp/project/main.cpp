#include "canny.h"
#include "hough.h"
#include "iostream"

int main() {
    Mat img = imread("/Users/andreibratu/bachelor/sem5/pdp/project/city.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }
    startWindowThread();
    filter gaussian_filter = create_gaussian_filter(3, 3, 1);
    img = apply_gaussian_filter(img, gaussian_filter);
    auto pair = apply_sobel(img);
    img = apply_non_max_suppresion(pair.first, pair.second);
    img = get_binary_canny_image(img, 10, 40);
    img = hough_transform(img, 10, 10);
    namedWindow("Grayscale", WINDOW_AUTOSIZE);
    resizeWindow("Grayscale", 500, 500);
    imshow("Grayscale", img);
    waitKey(0);
    destroyAllWindows();
    return 0;
}
