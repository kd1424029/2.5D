#pragma once

class Pipe : public KdGameObject
{
public:

	Pipe() { Init(); }
	~Pipe() override{}

	void Init() override;

	void PreUpdate() override;

	void Update() override;

	void DrawLit() override;

private:

	std::shared_ptr<KdModelData> m_PipeModel;
};