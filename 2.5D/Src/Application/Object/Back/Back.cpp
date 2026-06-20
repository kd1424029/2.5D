#include "Back.h"

void Back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Back/Back.png");

	//板ポリの原点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	PosY = -45;

	Scale = 225.0f;
}

void Back::Update()
{
	//サイズ拡大
	m_polygon.SetScale(Scale);

	// ワールド行列の更新
	m_mWorld = Math::Matrix::CreateTranslation(1, PosY, 100);
}

void Back::DrawUnLit()
{
	//背景描画
	//背景に陰影がつくのはおかしいので、DrawLit()で描画する
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
