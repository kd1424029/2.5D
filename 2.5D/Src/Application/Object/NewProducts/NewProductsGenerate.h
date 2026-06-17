#pragma once

#include "NewProductsBase.h"

class BallGenerate;

class NewProductsGenerate
{
public:

	NewProductsGenerate();
	~NewProductsGenerate() {}

	std::shared_ptr<NewProductsBase> Generate();

	void SetTarget(BallGenerate* ballgenerate) { m_BallGenerate = ballgenerate; }

private:

	std::shared_ptr<KdTexture> m_DefectiveProduct;

	std::shared_ptr<KdTexture> m_NewProductBasketBall;
	
	std::shared_ptr<KdTexture> m_NewProductVolleyBall;

	BallGenerate* m_BallGenerate = nullptr;

};