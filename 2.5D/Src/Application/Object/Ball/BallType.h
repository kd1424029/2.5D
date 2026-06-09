#pragma once

enum BallKind //プレイヤーにボールタイプを渡す用
{
	Kind_BasketBall,
	Kind_VolleyBall,
	Kind_SoccerBall,
};

class BallType
{

protected:

	BallKind ballKind; //各BallBaseの子クラスで初期化

};