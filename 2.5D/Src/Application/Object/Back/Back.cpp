#include "Back.h"

void Back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Back/Back.png");

	//サイズ拡大
	m_polygon.SetScale(220.0f);

	//板ポリの原点 (真ん中下段を指定)
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// ワールド行列の更新
	m_mWorld = Math::Matrix::CreateTranslation(0, -45, 100);
}
void Back::DrawUnLit()
{
	//背景描画
	//背景に陰影がつくのはおかしいので、DrawLit()で描画する
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
