#include "ResultScene.h"
#include "../SceneManager.h"

void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}
}

void ResultScene::Init()
{
}
