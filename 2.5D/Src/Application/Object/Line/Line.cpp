#include "Line.h"

#include "../Player/Player.h"

void Line::Init()
{
	m_Line = std::make_shared<KdTexture>();
	m_Line->Load("Asset/Textures/Line/Line.png");

	//Playerのenum class BoxType と同じ順番で登録
	m_PosList.push_back(BasketBallPos);
	m_PosList.push_back(TrashBoxPos);

	m_CurrentPos = BasketBallPos; //Playerの初期値と合わせる

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
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

	if (_spCamera)
	{
		Math::Vector3 _3DPos = GetPos();
		_3DPos = m_CurrentPos;

		//2D座標(3D座標->2D座標への変換作業)
		Math::Vector3 _2dPos = Math::Vector3::Zero;
		_spCamera->ConvertWorldToScreenDetail(_3DPos, _2dPos);

		KdShaderManager::Instance().m_spriteShader.DrawTex(m_Line, _2dPos.x, _2dPos.y);
	}
}
