#pragma once

class BoxUiBase : public KdGameObject
{
public:

	BoxUiBase() {}
	~BoxUiBase() {}

	void Init() override;

	void DrawSprite() override;

private:

	

protected:

	std::shared_ptr<KdTexture> m_BoxUi;

	Math::Vector2 m_pos;

	const float PosY = 1;

};