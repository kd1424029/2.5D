#include "BallGenerate.h"

#include "BasketBall/BasketBall.h"
#include "Volleyball/Volleyball.h"
#include "SoccerBall/SoccerBall.h"
#include "GoldBall/GoldBall.h"
#include "DirtySoccerBall/DirtySoccerBall.h"

#include "../Player/Player.h"

BallGenerate::BallGenerate(): m_Rng(std::random_device{}()), DeckIndex(0), m_lastPosType(-1)
{
	ShuffleDeck();

	ShuffleLaneDeck();

	m_BasketBallModel = std::make_shared<KdModelData>();
	m_BasketBallModel->Load("Asset/Models/Ball/BasketBall/BasketBall.gltf");

	m_VolleyBallModel = std::make_shared<KdModelData>();
	m_VolleyBallModel->Load("Asset/Models/Ball/VolleyBall/VolleyBall.gltf");

	m_SoccerBallModel = std::make_shared<KdModelData>();
	m_SoccerBallModel->Load("Asset/Models/Ball/SoccerBall/SoccerBall.gltf");

	m_DirtySoccerBallModel = std::make_shared<KdModelData>();
	m_DirtySoccerBallModel->Load("Asset/Models/Ball/DirtySoccerBall/DirtySoccerBall.gltf");

	m_GoldBallModel = std::make_shared<KdModelData>();
	m_GoldBallModel->Load("Asset/Models/Ball/GoldBall/GoldBall.gltf");
}

void BallGenerate::ShuffleDeck()
{
	m_Deck.clear();

	//残り時間に応じてデッキに含めるボール種類を決定
	//数字は BallType:  0=SoccerBall 1=DirtySoccerBall 2=BasketBall 3=VolleyBall
	int WaveLevel;
	if (RemainingTime >= WaveTime1) 
	{
		WaveLevel = 1;
	}
	else if (RemainingTime >= WaveTime2)
	{
		WaveLevel = 2;
	}
	else if (RemainingTime >= WaveTime3)
	{
		WaveLevel = 3;
	}
	else 
	{
		WaveLevel = 4;
	}

	for (int i = 0; i < WaveLevel; ++i)
	{
		m_Deck.push_back(i); //0番から waveLevel-1番まで追加
	}

	std::shuffle(m_Deck.begin(), m_Deck.end(), m_Rng);
	DeckIndex = 0;
}

void BallGenerate::ShuffleLaneDeck()
{
	m_LaneDeck.clear();
	for (int i = 0; i < MaxLane; ++i) //レーンは5本（0〜4）
	{
		m_LaneDeck.push_back(i);
	}
	std::shuffle(m_LaneDeck.begin(), m_LaneDeck.end(), m_Rng);
	m_LaneDeckIndex = 0;
}

std::shared_ptr<BallBase> BallGenerate::Generate()
{
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("GoldFlg: %d", GoldFlg);

	std::shared_ptr<BallBase> ball = nullptr;

	if (m_TargetPlayer->GetGoldCnt() < MaxGoldCnt)
	{
		GoldFlg = false;
	}

	// 先にレーン用デッキから配置するレーン番号を引いておく（金・通常共通で使うため）
	if (m_LaneDeckIndex >= static_cast<int>(m_LaneDeck.size()))
	{
		ShuffleLaneDeck();
	}

	int AssignedLane = m_LaneDeck[m_LaneDeckIndex++];


	// ========================================================
	// 1. ボールのインスタンス生成と 出現位置(座標) の決定
	// ========================================================
	if (m_TargetPlayer->GetGoldCnt() >= MaxGoldCnt && GoldFlg == false)
	{
		// ------------------------------------------
		// 【金のボールが生成されるときの処理】
		// ------------------------------------------
		ball = std::make_shared<GoldBall>();
		ball->Init();
		ball->SetModel(m_GoldBallModel);

		// 金のボール専用の出現位置（右側固定）を設定
		ball->SetPos(FirstRightPos);

		ball->SetMoveSpeed(MoveSpeed);
		ball->SetRotationSpeed(RotationSpeed);

		GoldFlg = true;
	}
	else
	{
		//===========================================
		//通常ボールが生成されるときの処理
		//===========================================
		
		// ウェーブレベルを計算(ShuffleDeckと同じロジック)
		int CurrentWave;

		if (RemainingTime >= WaveTime1) 
		{
			CurrentWave = 1;
		}
		else if (RemainingTime >= WaveTime2)
		{
			CurrentWave = 2;
		}
		else if (RemainingTime >= WaveTime3)
		{
			CurrentWave = 3;
		}
		else 
		{
			CurrentWave = 4;
		}

		//ウェーブが変わった or デッキ切れ → 再シャッフル
		if (CurrentWave != LastWaveLevel || DeckIndex >= static_cast<int>(m_Deck.size()))
		{
			LastWaveLevel = CurrentWave;

			ShuffleDeck();
		}

		int BallType;

		if (m_TargetPlayer->GetFeverFlg())
		{
			BallType = FeverBallType;    //フィーバー中は固定
		}
		else
		{
			BallType = m_Deck[DeckIndex++]; //通常はデッキから
		}

		switch (BallType)
		{
		case 0:

			ball = std::make_shared<SoccerBall>();
			ball->Init();
			ball->SetModel(m_SoccerBallModel);

			break;
		case 1:

			ball = std::make_shared<DirtySoccerBall>();
			ball->Init();
			ball->SetModel(m_DirtySoccerBallModel);

			break;
		case 2:

			ball = std::make_shared<BasketBall>();
			ball->Init();
			ball->SetModel(m_BasketBallModel);

			break;
		case 3:

			ball = std::make_shared<VolleyBall>();
			ball->Init();
			ball->SetModel(m_VolleyBallModel);

			break;
		}

		ball->SetMoveSpeed(MoveSpeed);
		ball->SetRotationSpeed(RotationSpeed);

		//通常ボールの時だけ左右交互に出現させる
		if (m_lastPosType == -1)
		{
			std::uniform_int_distribution<int> dist(0, 1);
			m_lastPosType = dist(m_Rng);
		}
		else
		{
			m_lastPosType = 1 - m_lastPosType;
		}

		if (m_lastPosType == 0)
		{
			ball->SetPos(FirstLeftPos);
		}
		else
		{
			ball->SetPos(FirstRightPos);
		}
	}

	//========================================================
	//最後に共通のデータ（レーン番号、ターゲット）をセットする
	//========================================================
	ball->SetSecondPosition(AssignedLane); //金・通常どちらにも綺麗に分配される
	ball->SetTarget(m_TargetPlayer);

	return ball;
}