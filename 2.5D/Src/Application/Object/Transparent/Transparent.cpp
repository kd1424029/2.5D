#include "Transparent.h"

void Transparent::Init()
{
	m_Transparent = std::make_shared<KdTexture>();
	m_Transparent->Load("Asset/Textures/Transparent/Transparent.png");

	PosY = MaxPosY;
}

void Transparent::Update()
{
	PosY += MoveSpeed;

	if (PosY > GoalPosY)
	{
		PosY = GoalPosY;
	}
}

void Transparent::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_Transparent, PosX, PosY,nullptr, &color);
}
