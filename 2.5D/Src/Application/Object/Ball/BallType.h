#pragma once

enum BallKind //プレイヤーにボールタイプを渡す用
{
	Kind_BasketBall,
	Kind_VolleyBall,
	Kind_SoccerBall,
	Kind_DirtySoccerBall,
	Kind_GoldBall,
};

class BallType
{

protected:

	BallKind ballKind; //各BallBaseの子クラスで初期化

};