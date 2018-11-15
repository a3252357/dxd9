#pragma once
#include <spine/spine.h>
#include "TextureManager.h"

class MyTextureLoader : public spine::TextureLoader
{
	virtual void load(spine::AtlasPage& page, const spine::String& path) {
		void* texture = (void *)TextureManager::getTexture(StringUtil::ConvertstringToLPCWSTR(path.buffer()), 0, 0, BOX_WIDTH, BOX_WIDTH)->ptexture9;
		page.setRendererObject(texture); // use the texture later in your rendering code
	}

	virtual void unload(void* texture) { // TODO 

	};
}