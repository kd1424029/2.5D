#include "BallGenerate.h"

#include "BasketBall/BasketBall.h"
#include "Volleyball/Volleyball.h"
#include "SoccerBall/SoccerBall.h"
#include "DirtySoccerBall/DirtySoccerBall.h"

BallGenerate::BallGenerate(): m_Rng(std::random_device{}()), DeckIndex(0), m_lastPosType(-1)
{
	ShuffleDeck();

	m_BasketBallModel = std::make_shared<KdModelData>();
	m_BasketBallModel->Load("Asset/Models/Ball/BasketBall/BasketBall.gltf");

	m_VolleyBallModel = std::make_shared<KdModelData>();
	m_VolleyBallModel->Load("Asset/Models/Ball/VolleyBall/VolleyBall.gltf");

	m_SoccerBallModel = std::make_shared<KdModelData>();
	m_SoccerBallModel->Load("Asset/Models/Ball/SoccerBall/SoccerBall.gltf");

	m_DirtySoccerBallModel = std::make_shared<KdModelData>();
	m_DirtySoccerBallModel->Load("Asset/Models/Ball/DirtySoccerBall/DirtySoccerBall.gltf");
}

void BallGenerate::ShuffleDeck()
{
	//種類を1枚ずつ詰める（枚数を増やせば偏りを調整できる）
	m_Deck.clear();
	for (int i = 0; i < BallCount; ++i)
	{
		m_Deck.push_back(i); // 0:BasketBall  1:VolleyBall  2:SoccerBall
	}

	std::shuffle(m_Deck.begin(), m_Deck.end(), m_Rng);
	DeckIndex = 0;
}

std::shared_ptr<BallBase> BallGenerate::Generate()
{
	// デッキを使い切ったら再シャッフル
	if (DeckIndex >= static_cast<int>(m_Deck.size()))
	{
		ShuffleDeck();
	}

	int ballType = m_Deck[DeckIndex++];

	// ボール生成
	std::shared_ptr<BallBase> ball;

	switch (ballType)
	{
	case 0:

		ball = std::make_shared<BasketBall>();

		ball->Init();

		ball->SetModel(m_BasketBallModel);

		break;
	case 1:

		ball = std::make_shared<VolleyBall>();

		ball->Init();

		ball->SetModel(m_VolleyBallModel);

		break;
	case 2:

		ball = std::make_shared<SoccerBall>();

		ball->Init();

		ball->SetModel(m_SoccerBallModel);
		
		break;
	case 3:

		ball = std::make_shared<DirtySoccerBall>();

		ball->Init();

		ball->SetModel(m_DirtySoccerBallModel);

		break;
	}

	//出現位置（交互）
	if (m_lastPosType == -1)
	{
		// uniform_int_distribution を使う（% は偏りが出ることがある）
		std::uniform_int_distribution<int> dist(0, 1);
		m_lastPosType = dist(m_Rng);
	}
	else
	{
		//確実に反転
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

	ball->SetTarget(m_TargetPlayer); 

	return ball;
}