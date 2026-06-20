#include "TitleScene.h"
#include "../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Back/Back.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/BeltConveyor/BeltConveyor.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	//カメラ用
	static Math::Vector3 CameraPos = { 0,3.7 ,-6.75 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(CameraPos);

	m_camera->SetCameraMatrix(transMat);

}

void TitleScene::Init()
{
	KdAudioManager::Instance().StopAllSound();

	m_camera = std::make_shared<KdCamera>();

	//地面
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	ground->Init();
	m_objList.push_back(ground);

	//背景
	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	back->Init();
	m_objList.push_back(back);

}
