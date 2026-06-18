#pragma once

#include "../KeyUiBase.h"

class ZUi : public KeyUiBase
{
public:

	ZUi() {}
	~ZUi() {}

	void Init() override;

	void DrawSprite() override;

private:


	const float PosX = -150;
	const float PosY = -290;
};