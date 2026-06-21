#include "TimeUp.h"

void TimeUp::Init()
{
	m_TimeUp = std::make_shared<KdTexture>();
	m_TimeUp->Load("Asset/Textures/TimeUp/TimeUp.png");

}

void TimeUp::DrawSprite()
{

	KdShaderManager::Instance().m_spriteShader.DrawTex(m_TimeUp, PosX, PosY);
}
