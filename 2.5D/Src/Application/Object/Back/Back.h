#pragma once

class Back : public KdGameObject
{
public:

	Back() {}
	~Back() override{}

	void Init() override;

	void DrawLit() override;

private:

	std::shared_ptr<KdSquarePolygon> m_BackPolygon;

	Math::Vector3 m_pos = {};  //座標
};