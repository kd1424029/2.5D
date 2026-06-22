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
#include "../../Object/Transparent/Transparent.h"
#include "../../Object/FeverFrame/FeverFrame.h"
#include "../../Object/CountDownUi/CountDownUi.h"
#include "../../Object/Shelf/Shelf.h"

GameScene::GameScene()
{
	Init();
}

GameScene::~GameScene() {}

void GameScene::Event()
{
	//タイマーが0になったらゲームを停止しリザルトシーンへ遷移する
	if (m_pTimer && m_pTimer->GetTimeUp())
	{
		if (m_pPlayer)
		{
			m_pPlayer->SetGameStopped(true);

			//現在のスコアをSceneManagerへ保存し、ResultSceneで表示できるようにする
			SceneManager::Instance().SetFinalScore(m_pPlayer->GetScore());
		}

		if (m_pTimer->IsReadyToChangeScene())  //音が鳴り終わってから遷移
		{
			if (m_pPlayer)
			{
				SceneManager::Instance().SetFinalScore(m_pPlayer->GetScore());
			}

			if (m_pScore)
			{
				SceneManager::Instance().SetIsNewRecord(m_pScore->IsNewRecord());
			}

			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		}

		return;
	}

	if (m_State == GameState::CountDown)
	{
		if (m_pCountDown && m_pCountDown->IsFinished())
		{
			m_State = GameState::Playing;

			if (m_pTimer)
			{
				m_pTimer->SetPaused(false);   //カウントダウン終了でタイマー再開
			}
		}
	}

	//現在のオブジェクト数をデバッグ
	//KdDebugGUI::Instance().ClearLog();
	//KdDebugGUI::Instance().AddLog("%d", (int)m_objList.size());

	if (GetAsyncKeyState('T') & 0x8000)
	{
		if (m_pPlayer)
		{
			SceneManager::Instance().SetFinalScore(m_pPlayer->GetScore());
		}

		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Result
		);
	}

	//カメラ用
	static Math::Vector3 CameraPos = { 0,3.7 ,-6.75 }; //{ 0,10 , 0 };//{ 0,3.7 ,-6.75 }; // {15,1,5};

	Math::Matrix transMat = Math::Matrix::CreateTranslation(CameraPos);

	//Math::Matrix rotaionMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));

	m_camera->SetCameraMatrix(transMat);

	//一定間隔でボールを1つ生成してオブジェクトリストへ追加する
	//種類 出現位置の決定はBallGenerateに任せている
	GenerateTimer--;

	if (GenerateTimer < 0)
	{
		if (m_pTimer)
		{
			m_BallGenerator->SetRemainingTime(static_cast<int>(m_pTimer->GetRemainingTime()));
		}

		//BallGenerateがランダムに種類を決めて生成する
		//フィーバー中に決められた個数を出し切った場合はnullptrが返るのでその場合はリストに追加しない
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
	//ウェーブが変わった瞬間にだけラベル要求を1つ積む
	if (m_BallGenerator->IsWaveChanged())
	{
		m_NewProductsGenerate->Generate();
	}

	//フィーバーが終了した時、保留していた新商品ラベルがあれば要求を積む
	m_NewProductsGenerate->CheckPendingGenerate();

	if (m_BallGenerator->IsGoldFlgChanged())
	{
		m_NewProductsGenerate->FeverGenerate();
	}

	//積まれた要求を間隔を空けて1個ずつ取り出して実際に生成する
	std::shared_ptr<NewProductsBase> newProduct = m_NewProductsGenerate->Update();

	if (newProduct)
	{
		m_objList.push_back(newProduct);
	}

}

void GameScene::Init()
{
	KdAudioManager::Instance().StopAllSound();

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
	m_BallGenerator = std::make_unique<BallGenerate>();
	m_BallGenerator->SetTarget(player.get());
	player->SetBallGenerate(m_BallGenerator.get());

	//棚
	std::shared_ptr<Shelf> shelf;

	//右側に7個
	for (int i = 0; i < 7; i++)
	{
		shelf = std::make_shared<Shelf>();
		shelf->Init();
		shelf->SetPos(Math::Vector3(15, 1.5, i * 3.5 + 10));
		shelf->SetTarget(player.get());
		m_objList.push_back(shelf);
	}

	KdAudioManager::Instance().Play("Asset/Sounds/Bgm/GameBgm.WAV", true);

	//左側に7個
	for (int i = 0; i < 7; i++)
	{
		shelf = std::make_shared<Shelf>();
		shelf->Init();
		shelf->SetPos(Math::Vector3(-15, 1.5, i * 3.5 + 10));
		shelf->SetTarget(player.get());
		m_objList.push_back(shelf);
	}

	//ベルトコンベア
	std::shared_ptr<BeltConveyor> beltConveyor;
	beltConveyor = std::make_shared<BeltConveyor>();
	beltConveyor->Init();
	beltConveyor->SetTarget(player.get());
	m_objList.push_back(beltConveyor);

	//透過画像
	std::shared_ptr<Transparent> transparent;
	transparent = std::make_shared<Transparent>();
	transparent->Init();
	m_objList.push_back(transparent);

	//ノーマルボックスUI
	std::shared_ptr<NormalBoxUi> normalboxui;
	normalboxui = std::make_shared<NormalBoxUi>();
	normalboxui->Init();
	m_objList.push_back(normalboxui);

	//ゴミ箱UI
	std::shared_ptr<TrashBoxUi> trashboxui;
	trashboxui = std::make_shared<TrashBoxUi>();
	trashboxui->Init();
	m_objList.push_back(trashboxui);

	//XキーUI
	std::shared_ptr<XUi> xui;
	xui = std::make_shared<XUi>();
	xui->Init();
	m_objList.push_back(xui);

	//ZキーUI
	std::shared_ptr<ZUi> zui;
	zui = std::make_shared<ZUi>();
	zui->Init();
	m_objList.push_back(zui);

	//ライン
	std::shared_ptr<Line> line;
	line = std::make_shared<Line>();
	line->Init();
	line->SetPlayer(player.get());
	m_objList.push_back(line);

	//タイマー
	std::shared_ptr<Timer> timer;
	timer = std::make_shared<Timer>();
	timer->Init();
	m_pTimer = timer.get();

	m_objList.push_back(timer);

	//スコア
	std::shared_ptr<Score> score;
	score = std::make_shared<Score>();
	score->Init();
	score->SetPlayer(player.get());
	score->SetTimer(timer.get());
	m_pScore = score.get();
	m_objList.push_back(score);

	//フィーバータイム演出用フレーム（画面の縁を光らせるUI）
	std::shared_ptr<FeverFrame> feverFrame;
	feverFrame = std::make_shared<FeverFrame>();
	feverFrame->Init();
	feverFrame->SetPlayer(player.get());
	m_objList.push_back(feverFrame);

	//商品ラベル
	m_NewProductsGenerate = std::make_unique<NewProductsGenerate>(); //ここで生成
	m_NewProductsGenerate->SetTarget(m_BallGenerator.get());
	m_NewProductsGenerate->SetPlayer(player.get());

	//カウントダウンUI（3,2,1,START）
	std::shared_ptr<CountDownUi> countDown;
	countDown = std::make_shared<CountDownUi>();
	countDown->Init();
	m_pCountDown = countDown.get();
	m_objList.push_back(countDown);

	m_State = GameState::CountDown;

	if (m_pTimer)
	{
		m_pTimer->SetPaused(true);   //カウントダウン中はタイマーを止める
	}
}
