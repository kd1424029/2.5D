#pragma once

class Back : public KdGameObject
{

public:

	Back() {}
	~Back() override {}

	void Init() override;

	void Update() override;

	void DrawUnLit() override;

	void SetPosY(float posy) { PosY = posy; }

	void SetScale(float scale) { Scale = scale; }

private:

	//板ポリゴン
	KdSquarePolygon m_polygon;

	float Scale;

	float PosY;
};