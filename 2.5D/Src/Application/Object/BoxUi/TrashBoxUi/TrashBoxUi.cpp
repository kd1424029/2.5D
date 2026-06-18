#include "TrashBoxUi.h"

void TrashBoxUi::Init()
{
	m_BoxUi = std::make_shared<KdTexture>();
	m_BoxUi->Load("Asset/Textures/BoxUi/TrashBoxUi.png");

}

void TrashBoxUi::DrawSprite()
{
	// 名前テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_BoxUi, PosX, PosY);
}
