#pragma once

enum class PipeState
{
	Red,    //赤パイプ
	Blue,   //青パイプ
	Green,  //緑パイプ
	None,   //なし
};


class Pipe : public KdGameObject
{
public:

	Pipe() { Init(); }
	~Pipe() override{}

	void Init() override;

	void PreUpdate() override;

	void Update() override;

	void DrawLit() override;


	//===== セッター =====

	//===== ゲッター =====
	Math::Color GetColor() const { return m_color; }
	
private:

	std::shared_ptr<KdModelData> m_PipeModel;

	const float MoveSpeed = 0.1f;

	const float MaxTopPos = 9.0f;

	const float MaxBottomPos = 5.0f;

	const float MaxLeftPos = -3.9f;

	const float SecondFromLeftPos = -2.0f;

	const float FourthFromLeftPos = 1.9f;

	const float FifthFromLeftPos = 3.6f;

	const float MiddlePos = -0.1f;

	int RandomColor = rand() % 3 + 1;

	int RandomPos = rand() % 3 + 1;

	float MoveUpCount;    //移動を開始するまでの時間をカウントする変数

	bool MoveUpFlg;       //移動を受け付けるフラグ

	PipeState m_State = PipeState::None;  //パイプの状態を管理する変数
};