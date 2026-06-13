#include "BasketBallUi.h"

void BasketBallUi::Init()
{
	m_BoxUi = std::make_shared<KdTexture>();
	m_BoxUi->Load("Asset/Textures/BallUi/BasketBallUi.png");

}

void BasketBallUi::Update()
{
	
}

void BasketBallUi::PostUpdate()
{}

void BasketBallUi::DrawSprite()
{
	// 名前テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_BoxUi, 0,0);
}
