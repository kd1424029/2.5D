#pragma once

#include "../NewProductsBase.h"

class NewFeverBall : public NewProductsBase
{
public:

	NewFeverBall() {}
	~NewFeverBall() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};