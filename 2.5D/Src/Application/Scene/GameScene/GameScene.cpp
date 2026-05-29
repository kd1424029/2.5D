#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Pipe/Pipe.h"
#include "../../Object/Back/Back.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	Math::Vector3 comPos = { 0,5,-7 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(comPos);

	m_camera->SetCameraMatrix(transMat);
}

void GameScene::Init()
{

	m_camera = std::make_unique<KdCamera>();

	//背景
	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	m_objList.push_back(back);

	//プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);


	//パイプ
	std::shared_ptr<Pipe> pipe;
	pipe = std::make_shared<Pipe>();
	m_objList.push_back(pipe);

}
