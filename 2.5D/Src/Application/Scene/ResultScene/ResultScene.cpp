#include "ResultScene.h"
#include "../SceneManager.h"

#include "../../Object/Back/Back.h"
#include "../../Object/Score/Score.h"
#include "../../Object/NewRecord/NewRecord.h"
#include "../../Object/ResultUi/ResultUi.h"

void ResultScene::Event()
{
}

void ResultScene::Init()
{
	KdAudioManager::Instance().StopAllSound();

	KdAudioManager::Instance().Play("Asset/Sounds/Bgm/Result.WAV", false);

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
	score->SetWidth(90);
	score->SetHeight(171);
	score->SetInterval(104);
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

	//タイトルへ
	std::shared_ptr<ResultUi> resultui;
	resultui = std::make_shared<ResultUi>();
	resultui->Init();
	m_objList.push_back(resultui);
}
