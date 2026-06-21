#include "Timer.h"

void Timer::Init()
{
	m_Timer = std::make_shared<KdTexture>();
	m_Timer->Load("Asset/Textures/Timer/Time.png");

	m_RestUi = std::make_shared<KdTexture>();
	m_RestUi->Load("Asset/Textures/Timer/TimeUi.png");

	RemainTime = 120.0f;   //2分00秒

	TimeUpFlg = false;

	TimerPosY = MaxPosY;
}

void Timer::Update()
{
	TimerPosY -= MoveSpeed;

	if (TimerPosY < GoalPosY)
	{
		TimerPosY = GoalPosY;
	}

	if (TimeUpFlg) return;
	
	if (PausedFlg == false)
	{
		RemainTime -= DeltaTime;  //毎フレーム 1/60秒 減算
	}

	if (RemainTime < 0.0f)
	{
		RemainTime = 0.0f;

		TimeUpFlg = true;
	}

	//分・秒に分解してDigitsに格納
	const int Total = TimeUpFlg ? 0 : std::min(static_cast<int>(RemainTime) + RoundUp, MaxTime);

	Digits[0] = Total  / SecondsPerMinute;                 //分
	Digits[1] = ColonIndex;								   //コロン(画像の11番目 = index10)
	Digits[2] = (Total % SecondsPerMinute) / DecimalBase;  //秒の十の位
	Digits[3] = (Total % SecondsPerMinute) % DecimalBase;  //秒の一の位


}

void Timer::DrawSprite()
{
	//(分)(：)(秒の十の位)(秒の一の位)の順に描画
	for (int i = 0; i < MaxDigits; ++i)
	{
		Math::Rectangle Rect = { CharSize * Digits[i], 0, CharSize, CharRectHeight };

		KdShaderManager::Instance().m_spriteShader.DrawTex(m_Timer, TimerPosX + (i * CharSpacing), TimerPosY, CharSize, CharHeight, &Rect);
	}
}