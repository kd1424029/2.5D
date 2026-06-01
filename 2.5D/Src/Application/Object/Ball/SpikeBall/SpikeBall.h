#pragma once

#include "../BallBase.h"

class SpikeBall : public BallBase
{
public:

	SpikeBall() {}
	~SpikeBall() override {}

	void Update() override;

private:

	void ChildClassInit() override;

	bool ColorGetFlg = false; //色取得済みフラグ

};