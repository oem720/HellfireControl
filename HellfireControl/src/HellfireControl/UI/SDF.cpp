
#include <HellfireControl/UI/SDF.hpp>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <fstream>
#include <External/stb/stb_image.h>
#include <External/stb/stb_image_write.h>

void SignedDistanceField::Run() {
    int h, w, comp;
    void* img = stbi_load("test.png", &h, &w, &comp, 4);
    stbi_image_free(img);
    std::cout << h << " " << w << " " << comp;
};

void SignedDistanceField::Bit() {
    // Create a bitmap image with 100x100 pixels and 3 channels (RGB).
    unsigned char* data = (unsigned char*)malloc(100 * 100);

    // Set the pixel values.
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            data[i * 100 + j + 0] = 255; // Red
        }
    }

    // Write the bitmap to a file.
    stbi_write_bmp("bitmap.bmp", 100, 100, 1, data);

    // Free the memory.
    free(data);
}