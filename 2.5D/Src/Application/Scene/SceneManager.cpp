#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"
#include "ResultScene/ResultScene.h"

void SceneManager::PreUpdate()
{
	// シーン切替
	UpdateFade();

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();

	//暗転画像を最前面に重ねて描画
	if (m_fadeAlpha > 0.0f)
	{
		Math::Color fadeColor = Math::Color(0, 0, 0, m_fadeAlpha);

		//画面全体を覆う黒いボックス（中心0,0、半幅・半高さで画面いっぱいに広げる）
		KdShaderManager::Instance().m_spriteShader.DrawBox(0, 0,ScreenWidth / 2, ScreenHeight / 2,&fadeColor,true);
	}
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

void SceneManager::UpdateFade()
{
	switch (m_fadeState)
	{
	case FadeState::None:

		//次のシーンが指定されたらフェードアウトを開始する
		if (m_currentSceneType != m_nextSceneType)
		{
			m_fadeState = FadeState::FadeOut;
			m_fadeAlpha = 0.0f;
		}

		break;

	case FadeState::FadeOut:

		m_fadeAlpha += FadeSpeed;

		if (m_fadeAlpha >= 1.0f)
		{
			m_fadeAlpha = 1.0f;

			//画面が真っ暗になったタイミングで実際にシーンを切り替える
			ChangeScene(m_nextSceneType);

			m_fadeState = FadeState::FadeIn;
		}

		break;

	case FadeState::FadeIn:

		m_fadeAlpha -= FadeSpeed;

		if (m_fadeAlpha <= 0.0f)
		{
			m_fadeAlpha = 0.0f;
			m_fadeState = FadeState::None;
		}

		break;
	}
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	case SceneType::Result:
		m_currentScene = std::make_shared<ResultScene>();
		break;
	}

	// 現在のシーン情報を更新
	m_currentSceneType = _sceneType;
}
