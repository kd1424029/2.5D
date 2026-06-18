#include "XUi.h"

void XUi::Init()
{
	m_KeyUi = std::make_shared<KdTexture>();
	m_KeyUi->Load("Asset/Textures/KeyUi/X.png");

}

void XUi::DrawSprite()
{

	//テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_KeyUi, PosX, PosY);

}