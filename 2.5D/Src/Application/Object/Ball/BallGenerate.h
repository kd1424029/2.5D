#pragma once
#include "BallBase.h"

class BallGenerate
{
public:

	BallGenerate() {};
	~BallGenerate() {}

	// ランダムなボールを1つ生成して返す
	std::shared_ptr<BallBase> Generate();


private:

	const int BallCount = 2;


	const Math::Vector3 FirstLeftPos = { -6,3.7,0 };//最初の左側の位置

	const Math::Vector3 FirstRightPos = { 6,3.7,0 }; //最初の右側の位置
};