#include "Score.h"

#include "../Player/Player.h"
#include "../Timer/Timer.h"

#include <fstream>

void Score::Init()
{
	m_Score = std::make_shared<KdTexture>();
	m_Score->Load("Asset/Textures/Score/Score.png");

	m_ScoreUi = std::make_shared<KdTexture>();
	m_ScoreUi->Load("Asset/Textures/Score/ScoreUi.png");

	ScorePosY = MaxPosY;

	HasSavedHighScore = false;

	GoalPosY = 280;

	Width = 70;

	Height = 111;

	ScorePosX = -170;
}

void Score::Update()
{

	ScorePosY -= MoveSpeed;

	if (ScorePosY < GoalPosY)
	{
		ScorePosY = GoalPosY;
	}

	//Playerが存在する場合（プレイ中）はPlayerから現在のスコアを取得する
	//Playerが存在しない場合（ResultSceneなど）はSetFixedScore()で設定済みの値をそのまま使う
	if (m_pPlayer != nullptr)
	{
		m_score = m_pPlayer->GetScore();

		if (m_score > MaxScore)
		{
			m_score = MaxScore;
		}
	}


	//配列に各桁の数値を格納
	unsigned long tmp = m_score;

	for (int i = maxDigits - 1; i >= 0; --i)
	{
		//下位の桁から抽出し配列に格納
		m_digits[i] = tmp % 10;//余りを求める演算子 %
		tmp /= 10;
	}

	//タイマーが0になった瞬間に1回だけハイスコア判定 保存
	if (m_pTimer != nullptr && m_pTimer->GetTimeUp() && !HasSavedHighScore)
	{
		SaveHighScore();

		HasSavedHighScore = true;
	}
}

unsigned long Score::LoadHighScore() const
{
	unsigned long highScore = 0;

	std::ifstream ifs(HighScoreFilePath);

	if (ifs)
	{
		ifs >> highScore;
	}

	//ファイルが不正に書き換えられている場合などに備えて上限を適用する
	if (highScore > MaxScore)
	{
		highScore = static_cast<unsigned long>(MaxScore);
	}

	return highScore;
}

void Score::SaveHighScore()
{
	//SetFixedScore()経由などでクランプされていない値が来る場合があるため、保存前に上限を適用する
	unsigned long scoreToSave = m_score;

	if (scoreToSave > MaxScore)
	{
		scoreToSave = static_cast<unsigned long>(MaxScore);
	}

	unsigned long highScore = LoadHighScore();

	if (scoreToSave <= highScore)
	{
		IsNewRecordFlg = false;
		return; //今回のスコアがハイスコア以下なら何もしない
	}

	IsNewRecordFlg = true;

	std::ofstream ofs(HighScoreFilePath);

	if (ofs)
	{
		ofs << scoreToSave;
	}
}

void Score::DrawSprite()
{
	//スコア表示
	for (int i = 0; i < maxDigits; ++i)
	{
		Math::Rectangle Rect = { CuttingInterval * m_digits[i],0,CuttingWidth,CuttingHeight };

		//表示														 X座標                         Y        幅    高さ    矩形データ       
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_Score, ScorePosX + (i * Interval), ScorePosY, Width, Height, &Rect);

	}
}
