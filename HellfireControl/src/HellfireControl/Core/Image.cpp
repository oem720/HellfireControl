
#include <HellfireControl/Core/Image.hpp>

#include <HellfireControl/Core/File.hpp>

void Image::PlotPixel(int _iX, int _iY, uint32_t _u32Color, bool _bFlipY) {	
	int iY = _bFlipY ? m_u32Height - _iY : _iY;

	int iNdx = iY * m_u32Width + _iX;

	if (iNdx > m_u32PixelCount - 1 || iNdx < 0) return;

	m_pPixels[iNdx] = _u32Color;
}

void Image::ReflectHorizontal() {
	//TODO: Implement
	throw std::logic_error("NOT IMPLEMENTED!");
}

void Image::ReflectVertical() {
	//TODO: Implement
	throw std::logic_error("NOT IMPLEMENTED!");
}