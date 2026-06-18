#include "Transparent.h"

void Transparent::Init()
{
	m_Transparent = std::make_shared<KdTexture>();
	m_Transparent->Load("Asset/Textures/Transparent/Transparent.png");

}

void Transparent::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_Transparent, PosX, PosY,nullptr, &color);
}
