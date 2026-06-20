#pragma once

class Transparent : public KdGameObject
{
public:

	Transparent() {}
	~Transparent() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_Transparent;

	float Alpha = 0.5;

	float PosX = 0;

	const float GoalPosY = -290;

	const float MaxPosY = -580;

	const float MoveSpeed = 20;

	float PosY;

	Math::Color color = { 1,1,1,Alpha };

};