#pragma once
#include "BallBase.h"

enum class BallType
{
	BasketBall,    //バスケットボール   (0番目)
	SoccerBall,    //サッカーボール		(1番目)
	VolleyBall,    //バレーボール		(2番目)
	None,          //ボールの種類が未定義
};

class BallGenerate
{
public:

	BallGenerate() {};
	~BallGenerate() {}

	// ランダムなボールを1つ生成して返す
	std::shared_ptr<BallBase> Generate();

};