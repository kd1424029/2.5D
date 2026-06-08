#pragma once

enum BallMove
{
	FirstMove,		//最初の移動
	SecondMove,		//2回目の移動
	ThirdMove,		//3回目の移動
};

enum Position
{
	First,
	Second,
	Third,
	Fourth,
	Fifth,
	None,
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
		

	void SetPos(const Math::Vector3& pos) { m_pos = pos; }

private:

	void DecisionPosition();

	float Gravity;

	float TargetX;

	float GoalTargetX;

	float RotationX;

	float RotationZ;

	int Count;

	int NextCount;

	BallMove MoveState;//移動状態

	Position PositionState;//位置状態

	const float MoveSpeed = 0.04f; //移動速度

	const float GravitySpeed = 0.005f; //重力の加速度

	const float RotationSpeed = 3.0f;

	const float MaxPosZ = 12.3f; //最初の移動での最大のZ座標

	const float FirstFromTheLeftPos = -4;  //2回目の左から1番目の位置

	const float SecondFromTheLeftPos = -2; //2回目の左から2番目の位置

	const float ThirdFromTheLeftPos = 0;   //2回目の左から3番目の位置

	const float FourthFromTheLeftPos = 2;  //2回目の左から4番目の位置

	const float FifthFromTheLeftPos = 4;   //2回目の左から5番目の位置

protected:

	std::shared_ptr<KdModelData> m_BallModel;

	Math::Vector3 m_pos;
};