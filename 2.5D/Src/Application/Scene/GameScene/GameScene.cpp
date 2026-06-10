#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Back/Back.h"
#include "../../Object/BeltConveyor/BeltConveyor.h"
#include "../../Object/Ball/BallGenerate.h" 
#include "../../Object/Ground/Ground.h"

void GameScene::Event()
{
	//現在のオブジェクト数をデバッグ
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", (int)m_objList.size());

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//カメラ用
	Math::Vector3 comPos = { 0,5,-7 };//{-6, 6, -1};//{ 0, 10 , 0 };

	//Math::Matrix rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(comPos);

	m_camera->SetCameraMatrix(transMat);
	

	GenerateTimer--;
	if (GenerateTimer <= 0)
	{
		//BallGenerateがランダムに種類を決めて生成する
		m_objList.push_back(m_ballGenerator.Generate());

		//タイマーをリセット（次の生成までのフレーム数）
		GenerateTimer = 120; //5秒間隔
	}

}

void GameScene::Init()
{
	GenerateTimer = 120;


	m_camera = std::make_unique<KdCamera>();

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

	//プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	player->Init();
	m_objList.push_back(player);

	m_ballGenerator.SetTarget(player.get());

	//ベルトコンベア
	std::shared_ptr<BeltConveyor> beltConveyor;
	beltConveyor = std::make_shared<BeltConveyor>();
	beltConveyor->Init();
	m_objList.push_back(beltConveyor);

}
