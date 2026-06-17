#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Back/Back.h"
#include "../../Object/BeltConveyor/BeltConveyor.h"
#include "../../Object/Ball/BallGenerate.h" 
#include "../../Object/Ball/BallBase.h" 
#include "../../Object/Ground/Ground.h"
#include "../../Object/BoxUi/NormalBoxUi/NormalBoxUi.h"
#include "../../Object/BoxUi/TrashBoxUi/TrashBoxUi.h"
#include "../../Object/KeyUi/XUi/XUi.h"
#include "../../Object/KeyUi/ZUi/ZUi.h"
#include "../../Object/Line/Line.h"
#include "../../Object/Timer/Timer.h"
#include "../../Object/Score/Score.h"
#include "../../Object/NewProducts/NewProductsGenerate.h"

GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene() {}

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
	Math::Vector3 comPos = { 0,4.5,-6.5 };//{-6, 6, -1};//{ 0, 10 , 0 };

	//Math::Matrix rotation = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));

	Math::Matrix transMat = Math::Matrix::CreateTranslation(comPos);

	m_camera->SetCameraMatrix(transMat);

	//一定間隔でボールを1つ生成してゲーム世界へ追加する
	//種類・出現位置の決定はBallGenerateに任せている
	GenerateTimer--;

	if (GenerateTimer < 0)
	{
		if (m_pTimer)
		{
			m_BallGenerator->SetRemainingTime(static_cast<int>(m_pTimer->GetRemainingTime()));
		}

		//BallGenerateがランダムに種類を決めて生成する
		//フィーバー中に決められた個数を出し切った場合はnullptrが返るので、その場合はリストに追加しない
		std::shared_ptr<BallBase> newBall = m_BallGenerator->Generate();

		if (newBall != nullptr)
		{
			m_objList.push_back(newBall);
		}

		//タイマーをリセット（次の生成までのフレーム数）
		if (m_pPlayer && m_pPlayer->GetFeverFlg())
		{
			GenerateTimer = FeverInterval;
		}
		else
		{
			GenerateTimer = NormalInterval;
		}
	}

	//NewProductsGenerateが種類を決めて生成をする
	//ウェーブが変わった瞬間にだけラベルを1つ生成する
	if (m_BallGenerator->IsWaveChanged())
	{
		std::shared_ptr<NewProductsBase> newProduct = m_NewProductsGenerate->Generate();

		if (newProduct)
		{
			m_objList.push_back(newProduct);
		}
	}

}

void GameScene::Init()
{
	GenerateTimer = NormalInterval;

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

	//プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	player->Init();

	m_pPlayer = player.get();

	m_objList.push_back(player);

	//ボール工場にプレイヤーを登録する
	//当たり判定の通知先として生成された各ボールへ渡される
	m_BallGenerator = std::make_unique<BallGenerate>(); // ここで生成
	m_BallGenerator->SetTarget(player.get());
	player->SetBallGenerate(m_BallGenerator.get());

	//ベルトコンベア
	std::shared_ptr<BeltConveyor> beltConveyor;
	beltConveyor = std::make_shared<BeltConveyor>();
	beltConveyor->Init();
	m_objList.push_back(beltConveyor);

	//ノーマルボックスUI
	std::shared_ptr<NormalBoxUi> normalboxui;
	normalboxui = std::make_shared<NormalBoxUi>();
	normalboxui->Init();
	normalboxui->SetCamera(m_camera);
	m_objList.push_back(normalboxui);

	//ゴミ箱UI
	std::shared_ptr<TrashBoxUi> trashboxui;
	trashboxui = std::make_shared<TrashBoxUi>();
	trashboxui->Init();
	trashboxui->SetCamera(m_camera);
	m_objList.push_back(trashboxui);

	//XキーUI
	std::shared_ptr<XUi> xui;
	xui = std::make_shared<XUi>();
	xui->Init();
	xui->SetCamera(m_camera);
	m_objList.push_back(xui);

	//ZキーUI
	std::shared_ptr<ZUi> zui;
	zui = std::make_shared<ZUi>();
	zui->Init();
	zui->SetCamera(m_camera);
	m_objList.push_back(zui);

	//ライン
	std::shared_ptr<Line> line;
	line = std::make_shared<Line>();
	line->Init();
	line->SetCamera(m_camera);
	line->SetPlayer(player.get());
	m_objList.push_back(line);

	//タイマー
	std::shared_ptr<Timer> timer;
	timer = std::make_shared<Timer>();
	timer->Init();
	timer->SetCamera(m_camera);
	m_pTimer = timer.get();

	m_objList.push_back(timer);

	//スコア
	std::shared_ptr<Score> score;
	score = std::make_shared<Score>();
	score->Init();
	score->SetCamera(m_camera);
	score->SetPlayer(player.get());
	m_objList.push_back(score);

	//商品ラベル
	m_NewProductsGenerate = std::make_unique<NewProductsGenerate>(); //ここで生成
	m_NewProductsGenerate->SetTarget(m_BallGenerator.get());

}
