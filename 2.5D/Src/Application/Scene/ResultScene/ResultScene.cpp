#include "ResultScene.h"
#include "../SceneManager.h"

#include "../../Object/Back/Back.h"
#include "../../Object/Score/Score.h"
#include "../../Object/NewRecord/NewRecord.h"

void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void ResultScene::Init()
{
	KdAudioManager::Instance().StopAllSound();

	//背景
	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	back->Init();
	back->SetPosY(-100);
	m_objList.push_back(back);

	//スコア（GameScene終了時にSceneManagerへ保存しておいた最終スコアを表示する）
	std::shared_ptr<Score> score;
	score = std::make_shared<Score>();
	score->Init();
	score->SetFixedScore(SceneManager::Instance().GetFinalScore());
	score->SetGoalPosY(100);
	score->SetWidth(150);
	score->SetHeight(150);
	score->SetInterval(100);
	score->SetScorePosX(-205);
	m_objList.push_back(score);

	//新記録
	if (SceneManager::Instance().GetIsNewRecord())
	{
		std::shared_ptr<NewRecord> newrecord;
		newrecord = std::make_shared<NewRecord>();
		newrecord->Init();
		m_objList.push_back(newrecord);
	}
}
