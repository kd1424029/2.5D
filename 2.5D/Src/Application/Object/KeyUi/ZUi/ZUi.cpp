#include "ZUi.h"

void ZUi::Init()
{
	m_KeyUi = std::make_shared<KdTexture>();
	m_KeyUi->Load("Asset/Textures/KeyUi/Z.png");

	PosY = MaxPosY;
}

void ZUi::Update()
{
	PosY += MoveSpeed;

	if (PosY > GoalPosY)
	{
		PosY = GoalPosY;
	}

}

void ZUi::DrawSprite()
{
	//テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_KeyUi, PosX, PosY);
}
