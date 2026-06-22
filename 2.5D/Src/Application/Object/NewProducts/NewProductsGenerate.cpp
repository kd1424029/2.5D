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
	m_NewFeverBall->Load("Asset/Textures/NewProducts/BonusBallUi.png");
}

void NewProductsGenerate::Generate()
{
	if (m_Player && m_Player->GetFeverFlg() == true)
	{
		//フィーバー中は出さずに、終了後に出すために保留する
		m_PendingWaveLevel = m_BallGenerate->GetWaveLevel();
		m_IsPending = true;
		return;
	}

	ProductRequest req;
	req.type = ProductRequestType::Wave;
	req.waveLevel = m_BallGenerate->GetWaveLevel();
	m_RequestQueue.push(req);
}

void NewProductsGenerate::CheckPendingGenerate()
{
	bool isFever = (m_Player && m_Player->GetFeverFlg());

	//フィーバーが true → false になった瞬間に、保留していたラベルの要求を積む
	if (m_PrevFeverFlg == true && isFever == false && m_IsPending == true)
	{
		ProductRequest req;
		req.type = ProductRequestType::Wave;
		req.waveLevel = m_PendingWaveLevel;
		m_RequestQueue.push(req);

		m_IsPending = false;
	}

	m_PrevFeverFlg = isFever;
}

void NewProductsGenerate::FeverGenerate()
{
	if (m_BallGenerate->GetGoldFlg() == true)
	{
		ProductRequest req;
		req.type = ProductRequestType::Fever;
		m_RequestQueue.push(req);
	}
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::Update()
{
	//間隔タイマーが残っている間は何も生成しない
	if (m_IntervalTimer > 0)
	{
		m_IntervalTimer--;
		return nullptr;
	}

	if (m_RequestQueue.empty())
	{
		return nullptr;
	}

	//キューの先頭を1個だけ取り出して生成する
	ProductRequest req = m_RequestQueue.front();
	m_RequestQueue.pop();

	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	if (req.type == ProductRequestType::Wave)
	{
		newProduct = CreateProductByWaveLevel(req.waveLevel);
	}
	else if (req.type == ProductRequestType::Fever)
	{
		newProduct = std::make_shared<NewFeverBall>();
		newProduct->Init();
		newProduct->SetModel(m_NewFeverBall);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}

	//実際に何か生成できた時だけ次の間隔を空ける
	if (newProduct)
	{
		m_IntervalTimer = kDisplayInterval;
	}

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