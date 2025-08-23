
#include <HellfireControl/Asset/Font.hpp>

Font::~Font() {
	//TODO: Bitmap textures must be removed from VRAM
}

void Font::Initialize() {
	//TODO: Bitmap textures must be submitted to the GPU and the character map must be prepped for rendering.
}

std::shared_ptr<Asset> FontParser::Parse(File& _fAssetFile) const {


	return std::shared_ptr<Asset>();
}