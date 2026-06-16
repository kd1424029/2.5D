#include "TrashBoxUi.h"

void TrashBoxUi::Init()
{
	m_BoxUi = std::make_shared<KdTexture>();
	m_BoxUi->Load("Asset/Textures/BoxUi/TrashBoxUi.png");

}

void TrashBoxUi::DrawSprite()
{
	std::shared_ptr<KdCamera> _spCamera = m_wpCamera.lock();

	if (_spCamera)
	{
		// 名前を表示させたいキャラクターの3D座標
		Math::Vector3 _3DPos = GetPos();
		_3DPos.y += PosY;
		_3DPos.x += PosX;

		// 画面中に名前を表示させたい2D座標(3D座標->2D座標への変換作業)
		Math::Vector3 _2dPos = Math::Vector3::Zero;
		_spCamera->ConvertWorldToScreenDetail(_3DPos, _2dPos);

		// 名前テクスチャを描画
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_BoxUi, _2dPos.x, _2dPos.y);
	}
}
