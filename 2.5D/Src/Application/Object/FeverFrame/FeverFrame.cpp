#include "FeverFrame.h"

#include "../Player/Player.h"

void FeverFrame::Init()
{
	Time = 0.0f;
}

void FeverFrame::Update()
{
	//フィーバー中だけ時間を進める
	if (m_pPlayer != nullptr && m_pPlayer->GetFeverFlg())
	{
		Time += FrameTime; //固定60FPS換算で経過時間を加算

		Alpha = 1.0f;

		UpdateShake();
	}
	else
	{
		Alpha -= AlphaSpeed;

		//完全に消えたら時間とシェイクをリセット
		if (Alpha < 0.0f)
		{
			Alpha = 0.0f;
			Time = 0.0f;
			ShakeOffsetX = 0.0f;
			ShakeFrameCounter = 0;
		}
	}
}

void FeverFrame::UpdateShake()
{
	//数フレームごとにだけ新しい乱数へ切り替える
	ShakeFrameCounter--;

	if (ShakeFrameCounter <= 0)
	{
		std::uniform_real_distribution<float> dist(-ShakeAmplitude, ShakeAmplitude);
		ShakeOffsetX = dist(m_ShakeRng);

		ShakeFrameCounter = ShakeUpdateInterval;
	}
}

void FeverFrame::DrawSprite()
{
	//フィーバー中でなければ何も描画しない
	if (m_pPlayer == nullptr || m_pPlayer->GetFeverFlg() == false || Alpha <= 0.0f)
	{
		return;
	}

	Math::Color frameColor = CalcFrameColor();

	const int HalfW = ScreenWidth / 2;
	const int HalfH = ScreenHeight / 2;

	const int ShakeX = static_cast<int>(ShakeOffsetX); //枠全体を左右に揺らすオフセット

	//上辺
	KdShaderManager::Instance().m_spriteShader.DrawBox(ShakeX, HalfH - FrameThickness, HalfW, FrameThickness,&frameColor, true);

	//下辺
	KdShaderManager::Instance().m_spriteShader.DrawBox(ShakeX, -HalfH + FrameThickness,HalfW, FrameThickness,&frameColor, true);

	//左辺
	KdShaderManager::Instance().m_spriteShader.DrawBox(-HalfW + FrameThickness + ShakeX, 0,FrameThickness, HalfH,&frameColor, true);

	//右辺
	KdShaderManager::Instance().m_spriteShader.DrawBox(HalfW - FrameThickness + ShakeX, 0,FrameThickness, HalfH,&frameColor, true);
}

Math::Color FeverFrame::CalcFrameColor() const
{
	//色相を時間で回転させる
	float hue = fmodf(Time / HueCycleSeconds, 1.0f);

	//明るさをsin波で脈動させる
	float pulse = PulseBase + PulseAmplitude * sinf(Time * PulseSpeed * DirectX::XM_2PI);

	//0.0〜1.0の範囲にクランプ
	if (pulse < 0.0f) pulse = 0.0f;
	if (pulse > 1.0f) pulse = 1.0f;

	return HsvToColor(hue, FrameSaturation, pulse , Alpha);
}

Math::Color FeverFrame::HsvToColor(float hue, float saturation, float value,float alpha)
{
	//HSV→RGB変換（hueは0.0〜1.0、saturation/valueは0.0〜1.0）
	float h = hue * 6.0f;
	int   i = static_cast<int>(floorf(h));
	float f = h - i;

	float p = value * (1.0f - saturation);
	float q = value * (1.0f - saturation * f);
	float t = value * (1.0f - saturation * (1.0f - f));

	float r, g, b;

	switch (i % 6)
	{
	case 0: r = value; g = t;     b = p;     break;
	case 1: r = q;     g = value; b = p;     break;
	case 2: r = p;     g = value; b = t;     break;
	case 3: r = p;     g = q;     b = value; break;
	case 4: r = t;     g = p;     b = value; break;
	default: r = value; g = p;   b = q;     break;
	}

	return Math::Color(r, g, b, alpha);
}
