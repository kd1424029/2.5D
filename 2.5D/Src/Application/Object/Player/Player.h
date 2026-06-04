#pragma once

enum class PlayerState
{
	Idle,    // 待機状態
	Moving,  // 移動状態
	CoolDown // クールダウン状態
};

class Player : public KdGameObject
{
public:

	Player() { Init(); };
	~Player() {};

	void Init() override;

	void PreUpdate() override;

	void Update() override;

	void DrawLit() override;

private:

	//モデルやテクスチャはポインタで管理
	std::shared_ptr<KdModelData> m_PlayerModel;

	Math::Vector3 m_TargetPos = { 0, 0, 0 };    // 移動先の目標座標
	
	const float MoveAmount = 2.3f;

	const float MoveMaxAmount = 4.6f;   //移動の最大距離

	const float MoveSpeed  = 0.5f;

	bool MoveFlgLeft;   //移動の入力を受け付けるフラグ
	bool MoveFlgRight;

	int MoveCoolDownCount; //クールタイムの残りフレーム数カウント

	const int MoveCoolDownMax = 5;   //移動後に押しっぱなしで次へ進むまでの待ち時間

	PlayerState m_State = PlayerState::Idle;  //プレイヤーの状態を管理する変数
};