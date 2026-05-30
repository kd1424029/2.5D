#pragma once

class Pipe;

class Ball : public KdGameObject
{
public:

	Ball() { Init(); }
	~Ball() override{}

	void Init() override;

	void PreUpdate() override;

	void Update() override;

	void DrawLit() override;


	void SetPipe(Pipe* pipe) { m_Pipe = pipe; }

private:

	std::shared_ptr<KdModelData> m_BallModel;

	Pipe* m_Pipe = nullptr;
};