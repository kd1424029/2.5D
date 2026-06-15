#pragma once

#include"../BaseScene/BaseScene.h"

class BallGenerate; 

class Timer;

class Player;

class GameScene : public BaseScene
{
public :

	GameScene();
	~GameScene();
	
private:

	void Event() override;

	void Init()  override;

	//ボールの種類・出現位置をランダムに決めて生成する工場
	//ゲームオブジェクトではないのでm_objListには入らない
	std::unique_ptr<BallGenerate> m_BallGenerator;

	Player* m_pPlayer = nullptr;

	Timer* m_pTimer = nullptr;

	int GenerateTimer;

	const int NormalInterval = 120;

	const int FeverInterval = 10;
};
