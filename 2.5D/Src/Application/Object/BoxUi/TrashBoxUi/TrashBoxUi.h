#pragma once

#include "../BoxUiBase.h"

class TrashBoxUi : public BoxUiBase
{
public:

	TrashBoxUi() {}
	~TrashBoxUi() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;


private:


};