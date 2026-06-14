#include "Timer.h"

void Timer::Init()
{
	m_Timer = std::make_shared<KdTexture>();
	m_Timer->Load("Asset/Textures/Timer/Timer.png");

	m_RestUi = std::make_shared<KdTexture>();
	m_RestUi->Load("Asset/Textures/Timer/RestUi.png");

	RemainTime = 180.0f;   //3分00秒

	TimeUpFlg = false;
}

void Timer::Update()
{
	if (TimeUpFlg) return;

	RemainTime -= DeltaTime;  //毎フレーム 1/60秒 減算

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
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();
	if (!_spCamera) return;

	//3D→2D座標変換
	Math::Vector3 _3DPos = GetPos();

	_3DPos.x = PosX;

	_3DPos.y += PosY;

	Math::Vector3 _2dPos = Math::Vector3::Zero;

	_spCamera->ConvertWorldToScreenDetail(_3DPos, _2dPos);

	if (!m_Timer) return;

	//(分)(：)(秒の十の位)(秒の一の位)の順に描画
	for (int i = 0; i < MaxDigits; ++i)
	{
		Math::Rectangle Rect = { CharSize * Digits[i], 0, CharSize, CharSize };

		KdShaderManager::Instance().m_spriteShader.DrawTex(m_Timer, _2dPos.x + (i * CharSpacing), _2dPos.y, CharSize, CharHeight, &Rect);
	}

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_RestUi, _2dPos.x - 100, _2dPos.y, RestCharSize, CharHeight);
}