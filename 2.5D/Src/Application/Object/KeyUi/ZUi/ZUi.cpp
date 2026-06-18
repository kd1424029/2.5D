#include "ZUi.h"

void ZUi::Init()
{
	m_KeyUi = std::make_shared<KdTexture>();
	m_KeyUi->Load("Asset/Textures/KeyUi/Z.png");

}

void ZUi::DrawSprite()
{
	//テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_KeyUi, PosX, PosY);
}
