#pragma once

#include"../BaseScene/BaseScene.h"

class Pipe;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;

	void Init()  override;


	Pipe* m_pPipe = nullptr;        
};
