#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 800;
const int height = 800;

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

    const std::string& datapath = DATA_PATH;

    const std::string inputname = "/obj/head.obj";
    const std::string& inputfile = datapath + inputname;
    const char* inputfile_c_str = inputfile.c_str();
    Model* model = new Model(inputfile_c_str);
    assert(model);

    /*TGAImage image(100, 100, TGAImage::RGB);
    for (int i = 0; i < 1000000; i++) {
        line(13, 20, 80, 40, image, white);
        line(20, 13, 40, 80, image, red);
        line(80, 40, 13, 20, image, red);
    }*/

    TGAImage image(width, height, TGAImage::RGB);
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.) * width / 2.;
            int y0 = (v0.y + 1.) * height / 2.;
            int x1 = (v1.x + 1.) * width / 2.;
            int y1 = (v1.y + 1.) * height / 2.;
            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image

    const std::string outputname = "/output.tga";
    const std::string& outputfile = datapath + outputname;
    const char* outfile_c_str = outputfile.c_str();

    image.write_tga_file(outfile_c_str);

    delete model;
    return 0;
}