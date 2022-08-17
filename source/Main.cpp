
#include <iostream>
#include "HCMath/HCVector.h"

int main() {
	std::cout << "Hello World!" << std::endl;

	Vec3 vec(4, 3, 2);
	Vec3 vec2(1.32f, 12.1f, 1.12f);

	vec = vec * vec2;

	std::cin.get();
}