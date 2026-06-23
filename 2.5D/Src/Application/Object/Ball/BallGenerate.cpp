#include "BallGenerate.h"

#include "BasketBall/BasketBall.h"
#include "Volleyball/Volleyball.h"
#include "SoccerBall/SoccerBall.h"
#include "GoldBall/GoldBall.h"
#include "DirtySoccerBall/DirtySoccerBall.h"

#include "../Player/Player.h"

BallGenerate::BallGenerate() : m_Rng(std::random_device{}()), DeckIndex(0), m_lastPosType(-1)
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
	//数字は BallType:  1=SoccerBall 2=DirtySoccerBall 3=BasketBall 4=VolleyBall
	WaveLevel = CalcCurrentWave();

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
	if (m_TargetPlayer->GetFeverFlg() && FeverRemainingSpawnCount <= 0)
	{
		return nullptr;
	}

	std::shared_ptr<BallBase> ball = nullptr;
	bool isFeverSpawn = false;

	if (m_TargetPlayer->GetGoldCnt() < MaxGoldCnt)
	{
		GoldFlg = false;
	}

	// ★ここに移動：金/通常どちらが生成されるかに関わらず、毎回ウェーブを判定・更新する
	int CurrentWave = CalcCurrentWave();
	if (CurrentWave != LastWaveLevel || DeckIndex >= static_cast<int>(m_Deck.size()))
	{
		LastWaveLevel = CurrentWave;
		ShuffleDeck(); // この中でWaveLevelも更新される
	}

	if (m_LaneDeckIndex >= static_cast<int>(m_LaneDeck.size()))
	{
		ShuffleLaneDeck();
	}

	int AssignedLane = m_LaneDeck[m_LaneDeckIndex++];

	if (m_TargetPlayer->GetGoldCnt() >= MaxGoldCnt && GoldFlg == false)
	{
		// 金のボール生成（ここはCalcCurrentWave/ShuffleDeck呼び出し不要、上で済んでいる）
		ball = std::make_shared<GoldBall>();
		ball->Init();
		ball->SetModel(m_GoldBallModel);
		ball->SetPos(FirstRightPos);
		ball->SetMoveSpeed(MoveSpeed);
		ball->SetRotationSpeed(RotationSpeed);

		GoldFlg = true;
	}
	else
	{
		// 通常ボール：もう一度CalcCurrentWaveやShuffleDeckの判定をする必要はない
		int BallType;
		isFeverSpawn = (m_TargetPlayer->GetFeverFlg() && FeverRemainingSpawnCount > 0);

		if (isFeverSpawn)
		{
			BallType = FeverBallType;
			FeverRemainingSpawnCount--;
		}
		else
		{
			BallType = m_Deck[DeckIndex++];
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

		if (m_lastPosType == -1)
		{
			std::uniform_int_distribution<int> dist(0, 1);
			m_lastPosType = dist(m_Rng);
		}
		else
		{
			m_lastPosType = 1 - m_lastPosType;
		}

		ball->SetPos(m_lastPosType == 0 ? FirstLeftPos : FirstRightPos);
	}

	ball->SetSecondPosition(AssignedLane);
	ball->SetTarget(m_TargetPlayer);
	ball->SetIsFeverBall(isFeverSpawn);

	return ball;
}