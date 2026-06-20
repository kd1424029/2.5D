#include "CountDownUi.h"

void CountDownUi::Init()
{
	m_NumberTex = std::make_shared<KdTexture>();
	m_NumberTex->Load("Asset/Textures/Start/CountDown.png");   //Timerと同じシートを流用

	m_StartTex = std::make_shared<KdTexture>();
	m_StartTex->Load("Asset/Textures/Start/Start.png");  

	m_Phase = Phase::Three;
	m_FrameCount = 0;
	m_Finished = false;

	KdAudioManager::Instance().Play("Asset/Sounds/Se/Count.WAV", false);
}

void CountDownUi::Update()
{
	if (m_Finished) return;

	m_FrameCount++;

	if (m_FrameCount >= PhaseFrame)
	{
		m_FrameCount = 0;

		switch (m_Phase)
		{
		case Phase::Three:

			KdAudioManager::Instance().Play("Asset/Sounds/Se/Count.WAV", false);

			m_Phase = Phase::Two;

			break;

		case Phase::Two:

			KdAudioManager::Instance().Play("Asset/Sounds/Se/Count.WAV", false);

			m_Phase = Phase::One;

			break;

		case Phase::One:

			KdAudioManager::Instance().Play("Asset/Sounds/Se/Start.WAV", false);

			m_Phase = Phase::Start;

			break;

		case Phase::Start:

			m_Phase = Phase::Finished;

			m_Finished = true;

			break;
		}
	}
}

void CountDownUi::DrawSprite()
{
	if (m_Finished) return;

	switch (m_Phase)
	{
	case Phase::Three:
	case Phase::Two:
	case Phase::One:
	{
		//CountDown.pngは「3,2,1」の3コマだけのシート
		//→ 数値ではなく何番目のコマかでUVを決める
		int frameIndex = 0;

		if (m_Phase == Phase::Three)      frameIndex = 2;
		else if (m_Phase == Phase::Two)   frameIndex = 1;
		else if (m_Phase == Phase::One)   frameIndex = 0;

		Math::Rectangle Rect = { CharSize * frameIndex, 0, CharSize, CharSize };

		KdShaderManager::Instance().m_spriteShader.DrawTex(m_NumberTex, PosX, PosY, CharSize, CharHeight, &Rect);
		
		break;
	}
	case Phase::Start:

		KdShaderManager::Instance().m_spriteShader.DrawTex(m_StartTex, PosX, PosY, StartWidth, StartHeight, nullptr);
		
		break;
	}
}