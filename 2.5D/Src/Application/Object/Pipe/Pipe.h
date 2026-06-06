#pragma once

class Pipe : public KdGameObject
{

public:

	Pipe() {}
	~Pipe() {}

	void Init() override;

	void Update() override;

	void DrawLit() override;

private:

	std::shared_ptr<KdModelData> m_PipeModel;

	Math::Vector3 m_pos = {};  //座標

};