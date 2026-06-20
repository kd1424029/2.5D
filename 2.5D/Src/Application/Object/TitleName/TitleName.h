#pragma once

class TitleName : public KdGameObject
{
public:

	TitleName() {}
	~TitleName() {}

	void Init() override;

	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_TitleName;

	const float PosX = 0;
	const float PosY = 250;

};