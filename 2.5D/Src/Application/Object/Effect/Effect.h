#pragma once

class Effect : public KdGameObject
{
public:

	Effect() {}
	~Effect() {}

	void Init() override;

	void Update() override;

	void DrawLit() override;

	void SetParam(Math::Vector3 pos, Math::Vector3 move, float lifeSpan, Math::Color color); 

private:

	std::shared_ptr<KdModelData> m_Model;

	Math::Vector3 m_pos;

	Math::Vector3 m_Move;

	Math::Color m_Color; 

	float LifeSpan;
};