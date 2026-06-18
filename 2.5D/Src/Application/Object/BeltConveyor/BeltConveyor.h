#pragma once

class BeltConveyor : public KdGameObject
{

public:

	BeltConveyor() {}
	~BeltConveyor() {}

	void Init() override;

	void DrawLit() override;

	void GenerateDepthMapFromLight() override;

	void SetPos(const Math::Vector3& pos)override { m_pos = pos; }

private:

	std::shared_ptr<KdModelData> m_BeltConveyorModel;

	Math::Vector3 m_pos = {0,2,6.5};  //座標

	int IndexObject = 2;	//ベルトコンベアの中心が左から3番目なのでindexは2

};