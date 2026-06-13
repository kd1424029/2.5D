#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Back/Back.h"
#include "../../Object/BeltConveyor/BeltConveyor.h"
#include "../../Object/Ball/BallGenerate.h" 
#include "../../Object/Ball/BallBase.h" 
#include "../../Object/Ground/Ground.h"
#include "../../Object/BoxUi/BasketBallUi/BasketBallUi.h"
#include "../../Object/BoxUi/VolleyBallUi/VolleyBallUi.h"
#include "../../Object/BoxUi/SoccerBallUi/SoccerBallUi.h"
#include "../../Object/BoxUi/TrashBoxUi/TrashBoxUi.h"

void GameScene::Event()
{
	//現在のオブジェクト数をデバッグ
	//KdDebugGUI::Instance().ClearLog();
	//KdDebugGUI::Instance().AddLog("%d", (int)m_objList.size());

	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//カメラ用
	Math::Vector3 comPos = { 0,5,-7.2 };//{-6, 6, -1};//{ 0, 10 , 0 };

	//Math::Matrix rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(comPos);

	m_camera->SetCameraMatrix(transMat);
	
	//一定間隔でボールを1つ生成してゲーム世界へ追加する
	//種類・出現位置の決定はBallGenerateに任せている
	GenerateTimer--;
	if (GenerateTimer <= 0)
	{
		//BallGenerateがランダムに種類を決めて生成する
		m_objList.push_back(m_ballGenerator.Generate());

		//タイマーをリセット（次の生成までのフレーム数）
		GenerateTimer = 120; //2秒間隔
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

	//ボール工場にプレイヤーを登録する
	//当たり判定の通知先として生成された各ボールへ渡される
	m_ballGenerator.SetTarget(player.get());

	player->SetBallGenerate(&m_ballGenerator);

	//ベルトコンベア
	std::shared_ptr<BeltConveyor> beltConveyor;
	beltConveyor = std::make_shared<BeltConveyor>();
	beltConveyor->Init();
	m_objList.push_back(beltConveyor);

	//バスケットボールUI
	std::shared_ptr<BasketBallUi> basketballui;
	basketballui = std::make_shared<BasketBallUi>();
	basketballui->Init();
	m_objList.push_back(basketballui);

	//バレーボールUI
	std::shared_ptr<VolleyBallUi> volleyballui;
	volleyballui = std::make_shared<VolleyBallUi>();
	volleyballui->Init();
	m_objList.push_back(volleyballui);

	//サッカーボールUI
	std::shared_ptr<SoccerBallUi> soccerballui;
	soccerballui = std::make_shared<SoccerBallUi>();
	soccerballui->Init();
	m_objList.push_back(soccerballui);

	//ゴミ箱UI
	std::shared_ptr<TrashBoxUi> trashboxui;
	trashboxui = std::make_shared<TrashBoxUi>();
	trashboxui->Init();
	m_objList.push_back(trashboxui);

}
