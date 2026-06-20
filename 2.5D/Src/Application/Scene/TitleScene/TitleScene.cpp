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

void TitleScene::Event()
{
	//if (GetAsyncKeyState('G') & 0x8000)
	//{
	//	SceneManager::Instance().SetNextScene
	//	(
	//		SceneManager::SceneType::Game
	//	);
	//}
}

void TitleScene::Init()
{
	GenerateTimer = NormalInterval;

	KdAudioManager::Instance().StopAllSound();

	KdAudioManager::Instance().Play("Asset/Sounds/Bgm/TitleBgm.WAV", true);

	m_camera = std::make_shared<KdCamera>();

	//背景
	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	back->Init();
	back->SetPosY(-70);
	back->SetScale(208);
	m_objList.push_back(back);

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
