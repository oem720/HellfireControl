
#include <Torchlight/Util/FontTypes.hpp>

void TTFBitmap::PlotPixel(int _iX, int _iY, uint32_t _u32Color) {
	int iNdx = _iY * m_u32Width + _iX;

	if (iNdx > m_u32ArraySize - 1 || iNdx < 0) return;

	m_pPixels[iNdx] = _u32Color;
}

void TTFBitmap::FlipImageVertically() {
	std::vector<std::vector<uint32_t>> vRows;
	for (int iRow = 0; iRow < m_u32Height; ++iRow) {
		int iRowStart = iRow * m_u32Width;
		int iRowEnd = iRowStart + m_u32Width;

		std::vector<uint32_t> vRow;
		vRow.insert(vRow.begin(), m_pPixels + iRowStart, m_pPixels + iRowEnd);

		vRows.push_back(vRow);
	}

	std::reverse(vRows.begin(), vRows.end());

	int iStride = 0;
	for (auto& aRow : vRows) {
		std::copy(aRow.begin(), aRow.end(), m_pPixels + iStride);
		iStride += aRow.size();
	}
}