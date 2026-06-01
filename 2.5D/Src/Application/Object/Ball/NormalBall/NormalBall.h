#pragma once

#include "../BallBase.h"

class NormalBall : public BallBase
{
public:

	NormalBall() {}
	~NormalBall() override {}

	void Update() override;

	//void SetPipe(Pipe* pipe) { m_Pipe = pipe; }

private:

	void ChildClassInit() override;

	bool ColorGetFlg = false; //色取得済みフラグ

};