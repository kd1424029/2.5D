#include "ResultUi.h"

#include "../../Scene/SceneManager.h"

void ResultUi::Init()
{
	m_ResultUi = std::make_shared<KdTexture>();
	m_ResultUi->Load("Asset/Textures/ResultUi/ResultUi.png");

	Alpha = MaxAlpha;

	AlphaFlg = true;

	KeyFlg = false;
}

void ResultUi::Update()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!KeyFlg)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/Se/Click.WAV", false);

			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
			KeyFlg = true;
		}
	}
	else
	{
		KeyFlg = false;
	}

	if (AlphaFlg == true)
	{
		Alpha -= AlphaSpeed;

		if (Alpha < BottomAlpha)
		{
			AlphaFlg = false;
		}
	}
	else
	{
		Alpha += AlphaSpeed;

		if (Alpha > MaxAlpha)
		{
			AlphaFlg = MaxAlpha;

			AlphaFlg = true;
		}
	}
}

void ResultUi::DrawSprite()
{
	Math::Color color = { 1,1,1,Alpha };

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_ResultUi, PosX, PosY, nullptr,&color);

}
