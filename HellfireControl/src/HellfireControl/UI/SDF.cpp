
#include <HellfireControl/UI/SDF.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <External/stb/stb_image.h>

void SignedDistanceField::Run() {
    int h, w, comp;
    void* img = stbi_load("test.png", &h, &w, &comp, 4);
    stbi_image_free(img);
    std::cout << h << " " << w << " " << comp;
};