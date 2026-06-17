#pragma once

#include "../NewProductsBase.h"

class NewProductBasket : public NewProductsBase
{
public:

	NewProductBasket() {}
	~NewProductBasket() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};