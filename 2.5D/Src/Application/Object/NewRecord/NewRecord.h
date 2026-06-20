#pragma once

class NewRecord : public KdGameObject
{
public:

	NewRecord() {}
	~NewRecord() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_NewRecord;

	const float PosX = 0;

	const float GoalPosY = 250;

	const float MaxPosY = 710;

	const float MoveSpeed = 20.0;

	float PosY;

};