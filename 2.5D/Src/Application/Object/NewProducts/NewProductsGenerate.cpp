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
	if (!m_BallGenerate) return;

	//現在のウェーブレベル（＝要素数）を取得
	int currentWave = m_BallGenerate->GetWaveLevel();
	//新しく追加されたボールの種類(waveLevelが3なら、新要素はインデックス2のバスケ)
	int newBallType = currentWave - 1;

	if (m_Player && m_Player->GetFeverFlg() == true)
	{
		//フィーバー中は出さずに、終了後に出すために保留する
		//複数回ウェーブが変わっても上書きせず全部キューに積んでおく
		m_PendingBallTypes.push(newBallType);
		return;
	}

	ProductRequest req;
	req.type = ProductRequestType::Wave;
	req.ballType = newBallType; // ボールタイプを直接記録
	m_RequestQueue.push(req);
}

void NewProductsGenerate::CheckPendingGenerate()
{
	//フィーバーが終わっていたら、保留していた分を全てキューに積む
	if (m_Player && m_Player->GetFeverFlg() == false)
	{
		while (!m_PendingBallTypes.empty())
		{
			ProductRequest req;
			req.type = ProductRequestType::Wave;
			req.ballType = m_PendingBallTypes.front(); //保留していたボールタイプを積む
			m_RequestQueue.push(req);

			m_PendingBallTypes.pop();
		}
	}
}

void NewProductsGenerate::FeverGenerate()
{
	ProductRequest req;
	req.type = ProductRequestType::Fever;
	m_RequestQueue.push(req);
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::Update()
{
	if (m_IntervalTimer > 0)
	{
		m_IntervalTimer--;
		return nullptr;
	}

	if (m_RequestQueue.empty())
	{
		return nullptr;
	}

	// キューから要求を1個取り出して生成する
	ProductRequest req = m_RequestQueue.front();
	m_RequestQueue.pop();

	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	if (req.type == ProductRequestType::Wave)
	{
		//ボールタイプに基づいた生成関数を呼ぶ
		newProduct = CreateProductByBallType(req.ballType);
	}
	else if (req.type == ProductRequestType::Fever)
	{
		newProduct = std::make_shared<NewFeverBall>();
		newProduct->Init();
		newProduct->SetModel(m_NewFeverBall);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}

	// 実際に何か生成できた時だけ次の間隔を空ける
	if (newProduct)
	{
		if (req.type == ProductRequestType::Fever)
		{
			m_IntervalTimer = 120; //ボーナスが通り過ぎるまで長めにあける
		}
		else
		{
			m_IntervalTimer = kDisplayInterval; //通常間隔(150)
		}
	}

	return newProduct;
}

std::shared_ptr<NewProductsBase> NewProductsGenerate::CreateProductByBallType(int ballType)
{
	std::shared_ptr<NewProductsBase> newProduct = nullptr;

	//BallGenerate.cpp の switch(BallType) と完全に数値を一致させる
	if (ballType == 1) //1 DirtySoccerBall (泥サッカー = 不良品)
	{
		newProduct = std::make_shared<DefectiveProduct>();
		newProduct->Init();
		newProduct->SetModel(m_DefectiveProduct);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}
	else if (ballType == 2) // 2: BasketBall (バスケットボール)
	{
		newProduct = std::make_shared<NewProductBasket>();
		newProduct->Init();
		newProduct->SetModel(m_NewProductBasketBall);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}
	else if (ballType == 3) // 3: VolleyBall (バレーボール)
	{
		newProduct = std::make_shared<NewProductVolley>();
		newProduct->Init();
		newProduct->SetModel(m_NewProductVolleyBall);

		KdAudioManager::Instance().Play("Asset/Sounds/Se/Inform.WAV", false);
	}

	return newProduct;
}