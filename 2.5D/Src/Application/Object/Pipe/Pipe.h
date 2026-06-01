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
	void SetReachBottom() { ReachBottomFlg = false; }

	//===== ゲッター =====
	Math::Color GetColor() const { return m_color; }

	Math::Vector3 GetPos() const { return m_pos; }
	
	bool GetReachBottom() const { return ReachBottomFlg; }

private:

	std::shared_ptr<KdModelData> m_PipeModel;

	const float MoveSpeed = 0.1f;

	const float MaxTopPos = 9.0f;

	const float MaxBottomPos = 5.0f;

	const float MaxLeftPos = -3.9f;

	const float SecondFromLeftPos = -2.0f;

	const float FourthFromLeftPos = 1.9f;

	const float FifthFromLeftPos = 3.8f;

	const float MiddlePos = -0.1f;

	const float MaxCount = 60.0f; //1秒間のカウント

	int RandomColor;//パイプの色をランダムで決めるための変数

	int RandomPos; //パイプの位置をランダムで決めるための変数

	float BeforeColor;   //前回の色を保存するための変数
	float BeforePosX;    //前回のX座標を保存するための変数

	float NextX;        //次のX座標を計算して入れる変数

	float MoveUpCount;    //移動を開始するまでの時間をカウントする変数

	bool MoveUpFlg;       //移動を受け付けるフラグ

	bool ReachBottomFlg; //底に到達したかどうかを管理するフラグ

	PipeState m_State = PipeState::None;  //パイプの状態を管理する変数
};