#pragma once

#include "../KeyUiBase.h"

class XUi : public KeyUiBase
{
public:

	XUi() {}
	~XUi() {}

	void Init() override;

	void DrawSprite() override;

private:


	const float PosX = 150;
	const float PosY = -290;
};