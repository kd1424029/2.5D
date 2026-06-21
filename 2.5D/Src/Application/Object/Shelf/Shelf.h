#pragma once

class Player;

class Shelf : public KdGameObject
{

public:

	Shelf() {}
	~Shelf() {}

	void Init() override;

	void Update() override;

	void DrawLit() override;

	void GenerateDepthMapFromLight() override;

	void SetPos(const Math::Vector3& pos)override { m_pos = pos; }

	void SetTarget(Player* player) { m_TargetPlayer = player; }

private:

	std::shared_ptr<KdModelData> m_ShelfModel;

	Player* m_TargetPlayer = nullptr;

	Math::Vector3 m_pos = {15,1.5,10 };  //座標

	float Scale;

	const float ScaleSpeed = 0.08;

	const float MaxScale = 1.5;

	const float MiddleScale = 1.0;

	bool ScaleFlg;

};