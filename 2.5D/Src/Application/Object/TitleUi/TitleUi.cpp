#include "TitleUi.h"

#include "../../Scene/SceneManager.h"

#include "../../Object/Score/Score.h"

void TitleUi::Init()
{
	m_StartUi = std::make_shared<KdTexture>();
	m_StartUi->Load("Asset/Textures/TitleUi/Start.png");

	m_BestScoreUi = std::make_shared<KdTexture>();
	m_BestScoreUi->Load("Asset/Textures/TitleUi/BestScore.png");

	m_Pick = std::make_shared<KdTexture>();
	m_Pick->Load("Asset/Textures/TitleUi/Pick.png");

	StartAlpha = MaxAlpha;

	BestScoreAlpha = MaxAlpha;

	StartAlphaFlg = true;

	BestScoreAlphaFlg = true;

	PickY = StartPosY;

	KeyFlg = false;

	KeySpaceFlg = false;

	NowPick = 0; //0 はじめる　1 最高スコア

	//最高スコア表示用
	m_pBestScoreDisplay = std::make_shared<Score>();
	m_pBestScoreDisplay->Init();
	m_pBestScoreDisplay->SetGoalPosY(0);     //画面中央あたりに表示
	m_pBestScoreDisplay->SetScorePosX(-150);
	m_pBestScoreDisplay->SetScorePosY(0);

	ShowBestScore = false;
}

void TitleUi::Update()
{
	if (!ShowBestScore)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (!KeyFlg)
			{
				KdAudioManager::Instance().Play("Asset/Sounds/Se/CursorMove.WAV", false);
				KeyFlg = true;
				PickY = StartPosY;
				NowPick = 0;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (!KeyFlg)
			{
				KdAudioManager::Instance().Play("Asset/Sounds/Se/CursorMove.WAV", false);
				KeyFlg = true;
				PickY = BestScorePosY;
				NowPick = 1;
			}
		}
		else
		{
			KeyFlg = false;
		}
	}

	if (NowPick == 0)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!KeySpaceFlg)
			{
				KdAudioManager::Instance().Play("Asset/Sounds/Se/Click.WAV", false);
				SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
				KeySpaceFlg = true;
			}
		}
		else
		{
			KeySpaceFlg = false;
		}

		BestScoreAlpha = MaxAlpha;

		if (StartAlphaFlg == true)
		{
			StartAlpha -= AlphaSpeed;
			if (StartAlpha < BottomAlpha)
			{
				StartAlphaFlg = false;
			}
		}
		else
		{
			StartAlpha += AlphaSpeed;
			if (StartAlpha > MaxAlpha)
			{
				StartAlpha = MaxAlpha;
				StartAlphaFlg = true;
			}
		}
	}
	else if (NowPick == 1)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!KeySpaceFlg)
			{
				//最高スコア表示の暗転をトグル（表示中なら閉じる、非表示なら開く）
				ShowBestScore = !ShowBestScore;

				if (ShowBestScore && m_pBestScoreDisplay)
				{
					KdAudioManager::Instance().Play("Asset/Sounds/Se/Click.WAV", false);

					//表示を開く瞬間に最新のハイスコアを読み込んでセットする
					m_pBestScoreDisplay->SetFixedScore(m_pBestScoreDisplay->LoadHighScore());
				}

				KeySpaceFlg = true;
			}
		}
		else
		{
			KeySpaceFlg = false;
		}

		StartAlpha = MaxAlpha;

		if (BestScoreAlphaFlg == true)
		{
			BestScoreAlpha -= AlphaSpeed;
			if (BestScoreAlpha < BottomAlpha)
			{
				BestScoreAlphaFlg = false;
			}
		}
		else
		{
			BestScoreAlpha += AlphaSpeed;
			if (BestScoreAlpha > MaxAlpha)
			{
				BestScoreAlpha = MaxAlpha;
				BestScoreAlphaFlg = true;
			}
		}
	}

	//暗転中は最高スコア表示オブジェクトも更新する（スライドイン演出のため）
	if (ShowBestScore && m_pBestScoreDisplay)
	{
		m_pBestScoreDisplay->Update();

		BestScoreAlpha = MaxAlpha;
	}
}

void TitleUi::DrawSprite()
{
	Math::Color startcolor = { 1,1,1,StartAlpha };

	Math::Color bestscorecolor = { 1,1,1,BestScoreAlpha };

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_StartUi, PosX, StartPosY, nullptr,&startcolor);

 	KdShaderManager::Instance().m_spriteShader.DrawTex(m_BestScoreUi, BestScorePosX, BestScorePosY, nullptr, &bestscorecolor);

 	KdShaderManager::Instance().m_spriteShader.DrawTex(m_Pick, PickX, PickY);

	if (ShowBestScore)
	{
		Math::Color darkColor = Math::Color(0, 0, 0, DarkAlpha);

		KdShaderManager::Instance().m_spriteShader.DrawBox(0, 0, ScreenWidth / 2, ScreenHeight / 2, &darkColor, true);

		if (m_pBestScoreDisplay)
		{
			m_pBestScoreDisplay->DrawSprite();
		}
	}
}
