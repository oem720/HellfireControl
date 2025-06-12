#pragma once

#include <HellfireControl/Core/Common.hpp>

class File;

class Image {
private:
	std::unique_ptr<uint32_t[]> m_pPixels;
	uint32_t m_u32PixelCount;
	uint32_t m_u32Width;
	uint32_t m_u32Height;

public:
	Image(uint32_t _u32Width, uint32_t _u32Height) :
		m_pPixels(std::make_unique<uint32_t[]>(_u32Width * _u32Height)),
		m_u32PixelCount(_u32Width * _u32Height),
		m_u32Width(_u32Width),
		m_u32Height(_u32Height) {}

	Image(Image&& _other) noexcept :
		m_pPixels(std::move(_other.m_pPixels)),
		m_u32PixelCount(_other.m_u32PixelCount),
		m_u32Width(_other.m_u32Width),
		m_u32Height(_other.m_u32Height) {}

	void PlotPixel(int _iX, int _iY, uint32_t _u32Color, bool _bFlipY = true);

	void ReflectHorizontal();

	void ReflectVertical();

	[[nodiscard]] HC_INLINE uint32_t GetWidth() const { return m_u32Width; }

	[[nodiscard]] HC_INLINE uint32_t GetHeight() const { return m_u32Height; }

	[[nodiscard]] HC_INLINE const std::unique_ptr<uint32_t[]>& GetPixelData() { return m_pPixels; }
};