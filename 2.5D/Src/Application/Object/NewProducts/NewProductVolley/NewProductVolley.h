#pragma once

#include "../NewProductsBase.h"

class NewProductVolley : public NewProductsBase
{
public:

	NewProductVolley() {}
	~NewProductVolley() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};