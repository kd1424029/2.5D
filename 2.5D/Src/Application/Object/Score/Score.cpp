#include "Score.h"

#include "../Player/Player.h"

void Score::Init()
{
	m_Score = std::make_shared<KdTexture>();
	m_Score->Load("Asset/Textures/Score/Score.png");

	m_ScoreUi = std::make_shared<KdTexture>();
	m_ScoreUi->Load("Asset/Textures/Score/ScoreUi.png");

	
}

void Score::Update()
{

	m_score = m_pPlayer->GetScore();

	if (m_score > MaxScore)
	{
		m_score = MaxScore;
	}
	else if (m_score < 0)
	{
		m_score = 0;
	}


	//配列に各桁の数値を格納
	unsigned long tmp = m_score;

	for (int i = maxDigits - 1; i >= 0; --i)
	{
		//下位の桁から抽出し配列に格納
		m_digits[i] = tmp % 10;//余りを求める演算子 %
		tmp /= 10;
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

	//KdShaderManager::Instance().m_spriteShader.DrawTex(m_ScoreUi, ScoreUiPosX, ScoreUiPosY, ScoreUiWidth, ScoreUiHeight);

}
