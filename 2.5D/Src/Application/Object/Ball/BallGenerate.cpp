#include "BallGenerate.h"

#include "BasketBall/BasketBall.h"
// 追加するボールはここに include する
// #include "Football/Football.h"
// #include "Volleyball/Volleyball.h"


std::shared_ptr<BallBase> BallGenerate::Generate()
{
	std::shared_ptr<BallBase> ball;

	const int Adjustment = 1;

	//rand() で十分だが速度差が無視できるくらい小さいのでコストゼロで質を上げられるならそうしておく判断

	//高性能な乱数生成器メルセンヌ・ツイスタでランダムなBallTypeを選ぶ
	static std::mt19937 RandomNumberGenerator{ std::random_device{}() };

	//ballTypeの種類数に合わせて上限を変える
	const int ballTypeCount = static_cast<int>(BallType::None) + Adjustment; //+1することで（ボールの種類が全部で何個あるか(3個)）を動的に計算

	std::uniform_int_distribution<int> Distribution(0, ballTypeCount - Adjustment);//0(最小値)から 種類数 - 1(最大値) までの整数を等確率で(一様整数分布)発生させるための設定

	//前回生成したボールを記憶する静的変数
	static BallType lastBallType = BallType::None;

	BallType ballType;

	do 
	{
		ballType = static_cast<BallType>(Distribution(RandomNumberGenerator));
	}
	while (ballType == lastBallType); //前回と同じなら選び直す

	lastBallType = ballType; //今回の種類を記憶

	switch (ballType)
	{
	case BallType::BasketBall:

		ball = std::make_shared<BasketBall>();
		
		break;

		// 他のボールを追加するときはここに case を足す
		// case BallType::Football:
		//     ball = std::make_shared<Football>();
		//     break;
		// case BallType::Volleyball:
		//     ball = std::make_shared<Volleyball>();
		//     break;

	default:

		//フォールバック：種類が未実装でも BasketBallを返す
		ball = std::make_shared<BasketBall>();
		
		break;
	}

	ball->Init();
	return ball;
}
