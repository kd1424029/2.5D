#include "VolleyBallUi.h"

void VolleyBallUi::Init()
{
	m_BoxUi = std::make_shared<KdTexture>();
	m_BoxUi->Load("Asset/Textures/BallUi/VolleyBallUi.png");

}

void VolleyBallUi::Update()
{

}

void VolleyBallUi::PostUpdate()
{}

void VolleyBallUi::DrawSprite()
{
	// 名前テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_BoxUi, 0, 100);
}
