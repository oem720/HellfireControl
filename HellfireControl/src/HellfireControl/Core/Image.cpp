
#include <HellfireControl/Core/Image.hpp>

#include <HellfireControl/Core/File.hpp>

void Image::PlotPixel(int _iX, int _iY, PixelRGB _pColor) {	
	int iNdx = _iY * m_u32Width + _iX;

	if (iNdx > m_u32PixelCount - 1 || iNdx < 0) return;

	m_pPixels[iNdx] = _pColor;
}

void Image::ReflectHorizontal() {
	//TODO: Implement
	throw std::logic_error("NOT IMPLEMENTED!");
}

void Image::ReflectVertical() {
	//TODO: Implement
	throw std::logic_error("NOT IMPLEMENTED!");
}