#include "TitleScene.h"
#include "../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Ball/BallGenerate.h" 
#include "../../Object/Ball/BallBase.h" 
#include "../../Object/Back/Back.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/BeltConveyor/BeltConveyor.h"
#include "../../Object/TitleName/TitleName.h"
#include "../../Object/TitleUi/TitleUi.h"
#include "../../Object/Shelf/Shelf.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	//GenerateTimer--;

	//if (GenerateTimer < 0)
	//{
	//	//BallGenerateがランダムに種類を決めて生成する
	//	std::shared_ptr<BallBase> newBall = m_BallGenerate->Generate();

	//	if (newBall != nullptr)
	//	{
	//		m_objList.push_back(newBall);

	//		GenerateTimer = NormalInterval;
	//	}
	//}

	//カメラ用
	static Math::Vector3 CameraPos = { 0,3.7 ,-6.75 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(CameraPos);

	m_camera->SetCameraMatrix(transMat);
}

void TitleScene::Init()
{
	GenerateTimer = NormalInterval;

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

	//m_BallGenerate = std::make_shared<BallGenerate>();

	//m_BallGenerate->SetRemainingTime(0);

	//ベルトコンベア
	std::shared_ptr<BeltConveyor> beltconveyor;
	beltconveyor = std::make_shared<BeltConveyor>();
	beltconveyor->Init();
	m_objList.push_back(beltconveyor);

	//棚
	std::shared_ptr<Shelf> shelf;

	//右側に7個
	for (int i = 0; i < 7; i++)
	{
		shelf = std::make_shared<Shelf>();
		shelf->Init();
		shelf->SetPos(Math::Vector3(15, 1.5, i * 3.5 + 10));
		m_objList.push_back(shelf);
	}

	//左側に7個
	for (int i = 0; i < 7; i++)
	{
		shelf = std::make_shared<Shelf>();
		shelf->Init();
		shelf->SetPos(Math::Vector3(-15, 1.5, i * 3.5 + 10));
		m_objList.push_back(shelf);
	}

	KdAudioManager::Instance().Play("Asset/Sounds/Bgm/TitleBgm.WAV", true);

	//タイトル名
	std::shared_ptr<TitleName> titlename;
	titlename = std::make_shared<TitleName>();
	titlename->Init();
	m_objList.push_back(titlename);

	//タイトルUi
	std::shared_ptr<TitleUi> titleui;
	titleui = std::make_shared<TitleUi>();
	titleui->Init();
	m_objList.push_back(titleui);

}
