#include "XUi.h"

void XUi::Init()
{
	m_KeyUi = std::make_shared<KdTexture>();
	m_KeyUi->Load("Asset/Textures/KeyUi/X.png");

}

void XUi::DrawSprite()
{
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

	if (_spCamera)
	{
		Math::Vector3 _3DPos = GetPos();
		_3DPos.x += PosX;
		_3DPos.y += PosY;

		//画面中に表示させたい2D座標(3D座標->2D座標への変換作業)
		Math::Vector3 _2dPos = Math::Vector3::Zero;
		_spCamera->ConvertWorldToScreenDetail(_3DPos, _2dPos);

		//テクスチャを描画
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_KeyUi, _2dPos.x, _2dPos.y);
	}
}
