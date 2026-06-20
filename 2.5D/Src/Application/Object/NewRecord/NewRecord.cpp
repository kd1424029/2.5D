#include "NewRecord.h"

void NewRecord::Init()
{
	m_NewRecord = std::make_shared<KdTexture>();
	m_NewRecord->Load("Asset/Textures/NewRecord/NewRecord.png");

	PosY = MaxPosY;
}

void NewRecord::Update()
{
	PosY -= MoveSpeed;

	if (PosY < GoalPosY)
	{
		PosY = GoalPosY;
	}
}

void NewRecord::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_NewRecord, PosX, PosY);
}
