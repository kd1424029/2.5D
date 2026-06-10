#pragma once

class Back : public KdGameObject
{

public:

	Back() {}
	~Back() override {}

	void Init() override;

	void DrawUnLit() override;

private:

	//板ポリゴン
	KdSquarePolygon m_polygon;
};