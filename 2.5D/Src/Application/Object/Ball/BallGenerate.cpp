#include "BallGenerate.h"

#include "BasketBall/BasketBall.h"

#include "Volleyball/Volleyball.h"


std::shared_ptr<BallBase> BallGenerate::Generate()
{
	std::shared_ptr<BallBase> ball;

	//ボールの種類数
	const int ballTypeCount = BallCount; //BasketBall=0　VolleyBall=1


	int ballType;

	//前回と同じにならないように選び直す
	static int lastBallType = None;

	do
	{
		ballType = rand() % ballTypeCount;
	}
	while (ballType == lastBallType);

	lastBallType = ballType;

	switch (ballType)
	{
	case 0:

		ball = std::make_shared<BasketBall>();

		break;

	case 1:

		ball = std::make_shared<VolleyBall>();

		break;
	}


	ball->Init();


	//出現位置を決める（完全に交互）
	static int lastPosType = -1; //前回の位置を記憶（0:左, 1:右）

	int currentPosType;

	if (lastPosType == -1)
	{
		//初回だけはランダムで 0(左) か 1(右) を決める
		currentPosType = rand() % 2;
	}
	else
	{
		//2回目以降は必ず反転（0なら1、1なら0）
		currentPosType = (lastPosType == 0) ? 1 : 0;
	}

	lastPosType = currentPosType; // 今回の位置を記憶


	//初期位置を上書きして確定させる
	//BallBase.h で定義されている座標をここで直接指定します
	if (currentPosType == 0)
	{
		ball->SetPos(FirstLeftPos); // 左側の座標
	}
	else
	{
		ball->SetPos(FirstRightPos);  // 右側の座標
	}

	return ball;
}
