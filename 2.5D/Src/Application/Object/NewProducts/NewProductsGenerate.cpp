#include "NewProductsGenerate.h"

#include "DefectiveProduct/DefectiveProduct.h"
#include "NewProductBasket/NewProductBasket.h"
#include "NewProductVolley/NewProductVolley.h"
#include "NewFeverBall/NewFeverBall.h"

#include "../Ball/BallGenerate.h"

NewProductsGenerate::NewProductsGenerate()
{
	m_DefectiveProduct = std::make_shared<KdTexture>();

	m_DefectiveProduct->Load("Asset/Textures/NewProducts/DefectiveProduct.png");

	m_NewProductBasketBall = std::make_shared<KdTexture>();

	m_NewProductBasketBall->Load("Asset/Textures/NewProducts/NewProductBasket.png");

	m_NewProductVolleyBall = std::make_shared<KdTexture>();

	m_NewProductVolleyBall->Load("Asset/Textures/NewProducts/NewProductVolley.png");

	m_NewFeverBall = std::make_shared<KdTexture>();

	m_NewFeverBall->Load("Asset/Textures/NewProducts/FeverBallUi.png");
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::Generate()
{
	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	if (m_BallGenerate->GetWaveLevel() == 2)
	{
		newProduct = std::make_shared<DefectiveProduct>();
		newProduct->Init();
		newProduct->SetModel(m_DefectiveProduct);
	}
	else if (m_BallGenerate->GetWaveLevel() == 3)
	{
		newProduct = std::make_shared<NewProductBasket>();
		newProduct->Init();
		newProduct->SetModel(m_NewProductBasketBall);
	}
	else if (m_BallGenerate->GetWaveLevel() == 4)
	{
		newProduct = std::make_shared<NewProductVolley>();
		newProduct->Init();
		newProduct->SetModel(m_NewProductVolleyBall);
	}

	return newProduct;
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::FeverGenerate()
{
	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	if (m_BallGenerate->GetGoldFlg() == true)
	{
		newProduct = std::make_shared<NewFeverBall>();
		newProduct->Init();
		newProduct->SetModel(m_NewFeverBall);
	}

	return newProduct;
}
