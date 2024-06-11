
#include <HellfireControl/Asset/Font.hpp>

Font::~Font() {
	m_texSDF.release();
}
