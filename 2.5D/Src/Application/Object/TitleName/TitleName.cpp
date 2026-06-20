#include "TitleName.h"

void TitleName::Init()
{
	m_TitleName = std::make_shared<KdTexture>();
	m_TitleName->Load("Asset/Textures/TitleName/TitleName.png");
}

void TitleName::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_TitleName, PosX,PosY);
}
