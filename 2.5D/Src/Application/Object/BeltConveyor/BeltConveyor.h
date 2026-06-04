#pragma once

class BeltConveyor : public KdGameObject
{

public:

	BeltConveyor(int index) { Init(index); }
	~BeltConveyor() {}

	void Init(int index);

	void PreUpdate() override;

	void Update() override;

	void DrawLit() override;

private:

	std::shared_ptr<KdModelData> m_BeltConveyorModel;

	int IndexObject = 2;	//ベルトコンベアの中心が左から3番目なのでindexは2

};