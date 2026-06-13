#pragma once

#include "../BoxUiBase.h"

class BasketBallUi : public BoxUiBase
{
public:

	BasketBallUi() {}
	~BasketBallUi() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;

private:


};