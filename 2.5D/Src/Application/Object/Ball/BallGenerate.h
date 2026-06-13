#pragma once
#include "BallBase.h"
#include <vector>
#include <random>

class Player;

class BallGenerate
{
public:

	BallGenerate();
	~BallGenerate() {}

	//ランダムなボールを1つ生成して返す
	std::shared_ptr<BallBase> Generate();

	void SetTarget(Player* player) { m_TargetPlayer = player; }

	void ResetGoldFlg() { GoldFlg = false; }

	void SetMoveSpeed(float move) { MoveSpeed = move; }

	void SetRotationSpeed(float rotationspeed) { RotationSpeed = rotationspeed; }

private:

	std::shared_ptr<KdModelData> m_BasketBallModel;

	std::shared_ptr<KdModelData> m_VolleyBallModel;
	
	std::shared_ptr<KdModelData> m_SoccerBallModel;

	std::shared_ptr<KdModelData> m_DirtySoccerBallModel;

	std::shared_ptr<KdModelData> m_GoldBallModel;

	Player* m_TargetPlayer = nullptr;

	// デッキをシャッフルして先頭から配り直す
	void ShuffleDeck();

	const int BallCount = 4;

	bool GoldFlg = false; 

	const int Left = 1;
	const int Right = 0;
	const int None = -1;

	const Math::Vector3 FirstLeftPos = { -6, 3.23f, -2 };
	const Math::Vector3 FirstRightPos = { 6, 3.23f, -2 };

	// --- シャッフルデッキ用 ---
	std::mt19937            m_Rng;       //乱数エンジン
	std::vector<int>        m_Deck;      //今のデッキ（BallTypeのint値が入る）
	int                     DeckIndex; //次に配るインデックス

	//出現位置用
	int m_lastPosType; //前回の位置 (0:左 / 1:右 / -1:未設定)

	//BallSpeed用
	float MoveSpeed = 0.04f;
	float RotationSpeed = 3.0f;
};
