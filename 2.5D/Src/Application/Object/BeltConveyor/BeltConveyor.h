#pragma once

class Player;

class BeltConveyor : public KdGameObject
{

public:

	BeltConveyor() {}
	~BeltConveyor() {}

	void Init() override;

	void Update() override;

	void DrawLit() override;

	void GenerateDepthMapFromLight() override;

	void SetPos(const Math::Vector3& pos)override { m_pos = pos; }

	void SetTarget(Player* player) { m_TargetPlayer = player; }

private:

	std::shared_ptr<KdModelData> m_BeltConveyorModel;

	std::shared_ptr<KdModelData> m_ArrowUpModel;

	std::shared_ptr<KdModelData> m_ArrowDownModel;

	Player* m_TargetPlayer = nullptr;

	Math::Vector3 m_pos = {0,2,6.5};  //座標

	float ArrowUpV;

	float ArrowDownV;

	const float ArrowUpSpeed = 0.001;

	const float ArrowUpFeverSpeed = 0.002;

	const float ArrowDownSpeed = 0.0009;

	const float ArrowDownFeverSpeed = 0.00185;

	const float MaxV = 1;
};