#pragma once

#include "../BoxUiBase.h"

class VolleyBallUi : public BoxUiBase
{
public:

	VolleyBallUi() {}
	~VolleyBallUi() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;


private:


};