#include "SoccerBallUi.h"

void SoccerBallUi::Init()
{
	m_BoxUi = std::make_shared<KdTexture>();
	m_BoxUi->Load("Asset/Textures/BallUi/SoccerBallUi.png");

}

void SoccerBallUi::Update()
{

}

void SoccerBallUi::PostUpdate()
{}

void SoccerBallUi::DrawSprite()
{
	// 名前テクスチャを描画
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_BoxUi, 0, 200);
}
