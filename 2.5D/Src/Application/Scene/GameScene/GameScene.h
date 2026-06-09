#pragma once

#include"../BaseScene/BaseScene.h"

#include "../../Object/Ball/BallGenerate.h"

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

	
private:

	void Event() override;

	void Init()  override;

	BallGenerate m_ballGenerator;

	int GenerateTimer;
};
