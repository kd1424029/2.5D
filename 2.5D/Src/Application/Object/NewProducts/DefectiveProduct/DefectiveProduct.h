#pragma once

#include "../NewProductsBase.h"

class DefectiveProduct : public NewProductsBase
{
public:

	DefectiveProduct() {}
	~DefectiveProduct() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};