#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Back/Back.h"
#include "../../Object/BeltConveyor/BeltConveyor.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//カメラ用
	Math::Vector3 comPos = { 0,5,-7 };//{ 0, 10 , -5 };

	//Math::Matrix rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));

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

	//ベルトコンベア

	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<BeltConveyor> beltConveyor;
		beltConveyor = std::make_shared<BeltConveyor>(i);
		m_objList.push_back(beltConveyor);
	}
}
