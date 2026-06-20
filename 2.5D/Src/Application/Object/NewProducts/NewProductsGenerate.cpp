#include "NewProductsGenerate.h"

#include "DefectiveProduct/DefectiveProduct.h"
#include "NewProductBasket/NewProductBasket.h"
#include "NewProductVolley/NewProductVolley.h"
#include "NewFeverBall/NewFeverBall.h"

#include "../Player/Player.h"

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
	if (m_Player && m_Player->GetFeverFlg() == true)
	{
		//フィーバー中は出さずに、終了後に出すために保留する
		m_PendingWaveLevel = m_BallGenerate->GetWaveLevel();
		m_IsPending = true;

		return nullptr;
	}

	return CreateProductByWaveLevel(m_BallGenerate->GetWaveLevel());
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::CheckPendingGenerate()
{
	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	bool isFever = (m_Player && m_Player->GetFeverFlg());

	//フィーバーが true → false になった瞬間に、保留していたラベルを生成する
	if (m_PrevFeverFlg == true && isFever == false && m_IsPending == true)
	{
		newProduct = CreateProductByWaveLevel(m_PendingWaveLevel);
		m_IsPending = false;
	}

	m_PrevFeverFlg = isFever;

	return newProduct;
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::CreateProductByWaveLevel(int waveLevel)
{
	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	if (waveLevel == 2)
	{
		newProduct = std::make_shared<DefectiveProduct>();
		newProduct->Init();
		newProduct->SetModel(m_DefectiveProduct);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}
	else if (waveLevel == 3)
	{
		newProduct = std::make_shared<NewProductBasket>();
		newProduct->Init();
		newProduct->SetModel(m_NewProductBasketBall);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}
	else if (waveLevel == 4)
	{
		newProduct = std::make_shared<NewProductVolley>();
		newProduct->Init();
		newProduct->SetModel(m_NewProductVolleyBall);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
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

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}

	return newProduct;
}