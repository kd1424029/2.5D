#pragma once

class BeltConveyor : public KdGameObject
{

public:

	BeltConveyor() {}
	~BeltConveyor() {}

	void Init();

	void Update() override;

	void DrawLit() override;

	void SetPos(const Math::Vector3& pos)override { m_pos = pos; }

private:

	std::shared_ptr<KdModelData> m_BeltConveyorModel;

	Math::Vector3 m_pos = {};  //座標

	int IndexObject = 2;	//ベルトコンベアの中心が左から3番目なのでindexは2

};