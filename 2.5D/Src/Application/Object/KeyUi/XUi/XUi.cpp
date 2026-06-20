#include "XUi.h"

void XUi::Init()
{
	m_KeyUi = std::make_shared<KdTexture>();
	m_KeyUi->Load("Asset/Textures/KeyUi/X.png");

	PosY = MaxPosY;
}

void XUi::Update()
{
	PosY += MoveSpeed;

	if (PosY > GoalPosY)
	{
		PosY = GoalPosY;
	}

}

void XUi::DrawSprite()
{

	//テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_KeyUi, PosX, PosY);

}