#include "DefectiveProduct.h"

void DefectiveProduct::Init()
{
	NewProductsBase::Init();

	BallLabel = Label::Label_DefectiveProduct;
}

void DefectiveProduct::Update()
{
	NewProductsBase::Update();
}

void DefectiveProduct::PostUpdate()
{
	NewProductsBase::PostUpdate();
}

void DefectiveProduct::DrawLit()
{
	NewProductsBase::DrawLit();
}
