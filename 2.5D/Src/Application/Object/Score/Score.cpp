#include "Score.h"

#include "../Player/Player.h"

void Score::Init()
{
	m_Score = std::make_shared<KdTexture>();
	m_Score->Load("Asset/Textures/Score/Score.png");

	
}

void Score::Update()
{

	m_score = m_pPlayer->GetScore();

	if (m_score > 99999)
	{
		m_score = 99999;
	}
	if (m_score < 0)
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
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

	if (_spCamera)
	{
		Math::Vector3 _3DPos = GetPos();
		_3DPos.x -= 1.5;
		_3DPos.y += 8;

		//2D座標(3D座標->2D座標への変換作業)
		Math::Vector3 _2dPos = Math::Vector3::Zero;
		_spCamera->ConvertWorldToScreenDetail(_3DPos, _2dPos);

		//スコア表示
		for (int i = 0; i < maxDigits; ++i)
		{
			Math::Rectangle rc = { 64 * m_digits[i],0,64,64 };

			//表示(サイズ10倍)                                          X座標                Y         幅  高さ 矩形データ       
			KdShaderManager::Instance().m_spriteShader.DrawTex(m_Score, _2dPos.x + (i * 64), _2dPos.y, 64, 100, &rc);

		}
	}
}
