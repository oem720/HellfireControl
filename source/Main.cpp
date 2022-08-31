
#include <iostream>
#include "HCMath/HCMatrix.h"

int __cdecl main() {
	std::cout << "Hellfire Control Engine\n----------------------------------------------" << std::endl;

	MatrixF mat;

	mat[0] = Vec4F(5.0f, 6.0f, 6.0f, 8.0f);
	mat[1] = Vec4F(2.0f, 2.0f, 2.0f, 8.0f);
	mat[2] = Vec4F(6.0f, 6.0f, 3.0f, 8.0f);
	mat[3] = Vec4F(2.0f, 3.0f, 6.0f, 7.0f);

	mat = Inverse(mat);

	return 0;
}