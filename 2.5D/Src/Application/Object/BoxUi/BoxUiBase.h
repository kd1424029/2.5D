#pragma once

class BoxUiBase : public KdGameObject
{
public:

	BoxUiBase() {}
	~BoxUiBase() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;

private:

	

protected:

	std::shared_ptr<KdTexture> m_BoxUi;

	Math::Vector2 m_pos;

	const float TopPosY = 7.7;

	const float SecondTopPosY = 6.8;

	const float PosY = 1;

	const float BottomPosY = 4.9;
};