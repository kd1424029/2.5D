#include "Line.h"

#include "../Player/Player.h"

void Line::Init()
{
	m_Line = std::make_shared<KdTexture>();
	m_Line->Load("Asset/Textures/Line/Line.png");

	//Playerのenum class BoxType と同じ順番で登録
	m_PosList.push_back(NormalBoxPos);
	m_PosList.push_back(TrashBoxPos);

	m_CurrentPos = NormalBoxPos; //Playerの初期値と合わせる

}

void Line::Update()
{
	if (m_pPlayer == nullptr) return;

	//Playerの現在BoxTypeをインデックスとして使う
	int index = m_pPlayer->GetBoxType();
	m_CurrentPos = m_PosList[index];
}

void Line::PostUpdate()
{}

void Line::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_Line, m_CurrentPos.x, m_CurrentPos.y);
}
