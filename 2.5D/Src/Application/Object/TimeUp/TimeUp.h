#pragma once

class TimeUp : public KdGameObject
{
public:

	TimeUp() {}
	~TimeUp() {}

	void Init() override;

	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_TimeUp;

	const float PosX = 0;

	const float PosY = 100;

};