#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <HellfireControl/UI/SDF.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <External/stb/stb_image.h>
#include <External/stb/stb_image_write.h>

void SignedDistanceField::Run() {
    int h, w, comp;
    unsigned char *img = stbi_load("test.png", &h, &w, &comp, 4);
    unsigned char* data = (unsigned char*)malloc(h * w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            // Get the index of the current pixel.
            int index = (y * w + x) * comp;

            // Read the red, green, and blue channel values.
            unsigned char alpha = img[index + 3];
            if (alpha != 0) {
                data[y * w + x] = 255;
            }
            else {
                data[y * w + x] = 0;
            }

            // Do something with the color values...
        }
    }
    stbi_write_bmp("bitmap.bmp", h, w, 1, data);
    free(data);
    stbi_image_free(img);
    std::cout << h << " " << w << " " << comp;
};

void SignedDistanceField::Bit() {
    // Create a bitmap image with 100x100 pixels and 3 channels (RGB).
    unsigned char* data = (unsigned char*)malloc(100 * 100 * 3);

    // Set the pixel values.
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            data[i * 100 * 3 + j * 3 + 0] = 255; // Red

        }
    }

    // Write the bitmap to a file.
    stbi_write_bmp("bitmap.bmp", 100, 100, 3, data);

    // Free the memory.
    free(data);
}