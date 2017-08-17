#ifndef _FONTTYPE_H
#define _FONTTYPE_H

#include "MeshList.h"

/*
Credit : Ow Hong Yu
*/

class FontType
{
public:
	FontType() {
		textWidth = nullptr;
	}
	virtual ~FontType() {
		if (textWidth != nullptr)
			delete textWidth;
		textWidth = nullptr;
	}
	float* textWidth;
	Mesh* textFont;
};

#endif
