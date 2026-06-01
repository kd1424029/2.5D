#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/Player/Player.h"
#include "../../Object/Pipe/Pipe.h"
#include "../../Object/Ball/NormalBall/NormalBall.h"
#include "../../Object/Ball/SpikeBall/SpikeBall.h"
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

	//ノーマルボール用
	if (m_pPipe && m_pPipe->GetReachBottom())
	{
		m_pPipe->SetReachBottom(); 
		
		auto normalBall = std::make_shared<NormalBall>();
		normalBall->SetPipe(m_pPipe);
		normalBall->Init();
		m_objList.push_back(normalBall);
	}

	//針ボール用
	else if (m_pPipe && m_pPipe->GetSpikeReachBottom())
	{
		m_pPipe->SetSpikeReachBottom();

		auto spikeBall = std::make_shared<SpikeBall>();
		spikeBall->SetPipe(m_pPipe);
		spikeBall->Init();
		m_objList.push_back(spikeBall);
	}
}

void GameScene::Init()
{

	m_camera = std::make_unique<KdCamera>();

	//パイプ
	std::shared_ptr<Pipe> pipe;
	pipe = std::make_shared<Pipe>();
	m_pPipe = pipe.get();
	m_objList.push_back(pipe);

	//背景
	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	m_objList.push_back(back);

	//プレイヤー
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);

}
