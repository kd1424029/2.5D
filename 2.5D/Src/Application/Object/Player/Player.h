#pragma once

class Player : public KdGameObject
{
public:

	Player() {};
	~Player() {};

	void Init() override;

	void PreUpdate() override;

	void Update() override;

	void DrawLit() override;

	void GenerateDepthMapFromLight() override;

private:

	enum class PlayerState
	{
		Idle,      //待機状態
		Moving,    //移動状態
		CoolDown,  //クールダウン状態
		SwitchOut, //切り替えのために後ろに下がる状態
		SwitchIn   //切り替えが終わって前に戻る状態
	};

	enum class BoxType
	{
		BasketBallBox, 
		VolleyBallBox,
		SoccerBallBox,
	};

	BoxType m_BoxType = BoxType::BasketBallBox; //初期状態はバスケットボール

	//モデルやテクスチャはポインタで管理
	std::shared_ptr<KdModelData> m_BasketBallBoxModel;
	std::shared_ptr<KdModelData> m_ValleyBallBoxModel;
	std::shared_ptr<KdModelData> m_SoccerBallBoxModel;

	//Box切り替え用
	BoxType m_NextBoxType = BoxType::BasketBallBox; //次に変更する箱のタイプ

	float BoxPosZ;    //元のZ座標

	const float SwitchDepth = -10.0f; //どれくらい奥に引っ込めるか
	
	const float SwitchSpeed = 1.0f; //引っ込むスピード

	bool KeyFlg;

	//移動用
	Math::Vector3 m_pos = {};  //座標

	Math::Vector3 m_TargetPos = {};    // 移動先の目標座標
	
	const float MoveAmount = 2.0f;

	const float MoveMaxAmount = 3.3f;   //移動の最大距離

	const float MoveSpeed  = 0.5f;

	bool MoveFlgLeft;   //移動の入力を受け付けるフラグ
	bool MoveFlgRight;

	int MoveCoolDownCount; //クールタイムの残りフレーム数カウント

	const int MoveCoolDownMax = 5;   //移動後に押しっぱなしで次へ進むまでの待ち時間

	PlayerState m_State = PlayerState::Idle;  //プレイヤーの状態を管理する変数
};