#include "NewProductsBase.h"

void NewProductsBase::Init()
{
	m_NewProducts = nullptr;
}

void NewProductsBase::Update()
{
	m_pos.x += MoveSpeed;

	if (m_pos.x > MaxPosX)
	{
		m_isExpired = true;
	}
}

void NewProductsBase::DrawSprite()
{
	if (m_NewProducts)
	{
		//テクスチャを描画
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_NewProducts, m_pos.x, m_pos.y);
	}
}
