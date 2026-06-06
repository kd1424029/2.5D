#pragma once

enum BallMove
{
	FirstMove,		//最初の移動
	SecondMove,		//2回目の移動
};

class BallBase : public KdGameObject
{
public:

	BallBase() {}
	~BallBase() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;
		

private:

protected:

	std::shared_ptr<KdModelData> m_BallModel;

	Math::Vector3 m_pos;

	float Gravity;

	int Count;

	BallMove MoveState;//移動状態

	const Math::Vector3 FirstLeftPos  = { -6.4,5.9,-5 };//最初の左側の位置

	const Math::Vector3 FirstRightPos = { 6.4,5.9,-5 }; //最初の右側の位置

	const Math::Vector3 FirstFromTheLeftPos = { 0,5,5 };  //2回目の左から1番目の位置

	const Math::Vector3 SecondFromTheLeftPos = { 0,5,5 }; //2回目の左から2番目の位置

	const Math::Vector3 ThirdFromTheLeftPos = { 0,5,11 }; //{ 0,3.7,11 };  //2回目の左から3番目の位置

	const Math::Vector3 FourthFromTheLeftPos = { 0,5,5 }; //2回目の左から4番目の位置

	const Math::Vector3 FifthFromTheLeftPos = { 0,5,5 };  //2回目の左から5番目の位置

};