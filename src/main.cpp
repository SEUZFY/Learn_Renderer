#include <cmath>
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color) {
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    int y_increment = y1 > y0 ? 1 : -1;

    if (steep) {
        for (int x = x0; x <= x1; ++x) {
            image.set(y, x, TGAColor(255, 1));
            error2 += derror2;
            if (error2 > dx) {
                y += y_increment;
                error2 -= dx * 2;
            }
        }
    }
    else {
        for (int x = x0; x <= x1; ++x) {
            image.set(x, y, TGAColor(255, 1));
            error2 += derror2;
            if (error2 > dx) {
                y += y_increment;
                error2 -= dx * 2;
            }
        }
    }
}

int main(int argc, char** argv) {
    std::cout << "this is: " << argv[0] << '\n';

    TGAImage image(100, 100, TGAImage::RGB);
    for (int i = 0; i < 1000000; i++) {
        line(13, 20, 80, 40, image, white);
        line(20, 13, 40, 80, image, red);
        line(80, 40, 13, 20, image, red);
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

    const std::string& datapath = DATA_PATH;
    const std::string filename = "/output.tga";
    const std::string& file = datapath + filename;
    const char* file_c_str = file.c_str();

    image.write_tga_file(file_c_str);
    return 0;
}