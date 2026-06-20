#pragma once

#include"../BaseScene/BaseScene.h"

class BallGenerate;

class TitleScene : public BaseScene
{
public :

	TitleScene()  { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init()  override;

	std::shared_ptr<BallGenerate> m_BallGenerate;

	int GenerateTimer;

	const int NormalInterval = 120;

};
