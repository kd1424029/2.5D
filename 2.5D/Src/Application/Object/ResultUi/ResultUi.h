#pragma once

class Score;

class ResultUi : public KdGameObject
{
public:

	ResultUi() {}
	~ResultUi() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_ResultUi;

	const float PosX = 0;
	const float PosY = -150;
	
	float Alpha;

	const float AlphaSpeed = 0.02;

	const float MaxAlpha = 1;

	const float BottomAlpha = 0.3;

	bool AlphaFlg;

	bool KeyFlg;

};