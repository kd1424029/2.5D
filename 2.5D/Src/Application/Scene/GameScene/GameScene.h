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

	//ボールの種類・出現位置をランダムに決めて生成する工場
	//ゲームオブジェクトではないのでm_objListには入らない
	BallGenerate m_ballGenerator;

	Player* m_pPlayer = nullptr;

	int GenerateTimer;
};
