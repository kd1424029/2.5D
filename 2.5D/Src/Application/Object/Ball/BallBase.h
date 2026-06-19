#pragma once

#include "BallType.h"

#include <vector>
#include <random>

class Player;

enum BallMove
{
	FirstMove,		//最初の移動
	SecondMove,		//2回目の移動
	ThirdMove,		//3回目の移動
	ScaleFaze,      //消滅処理
};

class BallBase : public KdGameObject, public BallType
{
public:

	BallBase() {}
	~BallBase() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;

	float GetMoveSpeed() const { return MoveSpeed; }

	float GetRotationSpeed() const { return RotationSpeed; }

	void SetPos(const Math::Vector3& pos) { m_pos = pos; }

	void SetMoveSpeed(float move) { MoveSpeed = move; }

	void SetRotationSpeed(float rotationspeed) { RotationSpeed = rotationspeed; }

	void SetTarget(Player* player) { m_TargetPlayer = player; }

	void SetModel(std::shared_ptr<KdModelData> model) { m_BallModel = model; }

	void SetSecondPosition(int pos) { SecondPosition = pos; }

	//フィーバー中に生成されたボールかどうか（フィーバー終了判定で使用）
	void SetIsFeverBall(bool flg) { m_IsFeverBall = flg; }

	bool GetIsFeverBall() const { return m_IsFeverBall; }

private:

	Player* m_TargetPlayer = nullptr;

	float Scale;

	bool ScaleFlg;

	bool ScaleGrowFlg; // true 拡大　false 縮小

	const float ScaleMax = 1.6f;   //拡大の最大値

	const float ScaleSpeed = 0.1f; //スケールスピード

	const float PosY = 1.9;
	
	const float PosZ = 0.5;

	float Gravity;

	float TargetX;

	float GoalTargetX;

	float RotationX;

	float RotationZ;

	int SecondPosition;

	bool m_IsFeverBall = false; //フィーバー中に生成されたボールかどうか

	const int PositionCount = 5;

	BallMove MoveState;//移動状態

	float MoveSpeed;//移動速度

	float RotationSpeed;

	const float MaxBottom = 0;

	const float GravitySpeed = 0.005f; //重力の加速度

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