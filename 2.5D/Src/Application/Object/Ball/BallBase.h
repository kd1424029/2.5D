#pragma once

class BallBase : public KdGameObject
{
public:

	BallBase() {}
	~BallBase() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;
		

private:

protected:

	std::shared_ptr<KdModelData> m_BallModel;

	Math::Vector3 m_pos;

};