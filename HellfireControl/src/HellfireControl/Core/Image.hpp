#pragma once

#include <HellfireControl/Core/Common.hpp>

#include <HellfireControl/Core/File.hpp>

class File;

template<typename ChannelType, uint8_t ChannelCount, HC_SFINAE_REQUIRE_NUMERIC(ChannelType)>
class Image {
private:
	struct Pixel {
		ChannelType m_arrChannelValues[ChannelCount] = {};
	};

	uint32_t m_u32Width;
	uint32_t m_u32Height;
	uint32_t m_u32PixelCount;
	std::unique_ptr<Pixel[]> m_pPixels;

public:
	Image(uint32_t _u32Width, uint32_t _u32Height) :
		m_u32Width(_u32Width),
		m_u32Height(_u32Height),
		m_u32PixelCount(_u32Width * _u32Height),
		m_pPixels(std::make_unique<Pixel[]>(m_u32PixelCount)) {}

	Image(Image&& _other) noexcept :
		m_u32Width(_other.m_u32Width),
		m_u32Height(_other.m_u32Height),
		m_u32PixelCount(_other.m_u32PixelCount),
		m_pPixels(std::move(_other.m_pPixels)) {}

	void PlotPixel(int _iX, int _iY, Pixel _pPixel) {
		int iNdx = _iY * (m_u32Width) + _iX;

		if (iNdx > m_u32PixelCount - 1 || iNdx < 0) return;

		m_pPixels[iNdx] = _pPixel;
	}

	void ReflectHorizontal() {
		throw std::runtime_error("ERROR: Function not implemented!");
	}

	void ReflectVertical() {
		throw std::runtime_error("ERROR: Function not implemented!");
	}

	[[nodiscard]] HC_INLINE uint32_t GetWidth() const { return m_u32Width; }

	[[nodiscard]] HC_INLINE uint32_t GetHeight() const { return m_u32Height; }

	[[nodiscard]] HC_INLINE uint8_t GetChannels() const { return ChannelCount; }

	[[nodiscard]] HC_INLINE const std::unique_ptr<Pixel[]>& GetPixelData() const { return m_pPixels; }
};

//TODO: Add more specializations here!
typedef Image<uint8_t, 1> ImageR8;
typedef Image<uint8_t, 2> ImageRG8;
typedef Image<uint8_t, 3> ImageRGB8;
typedef Image<uint8_t, 4> ImageRGBA8;