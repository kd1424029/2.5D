#pragma once

#include "../../Object/Ball/BallBase.h"

static float RandRange(float range)
{
	return ((rand() % 100) / 100.0f - 0.5f) * range;
}

class BallGenerate;

class Player : public KdGameObject
{
public:

	Player() {};
	~Player() {};

	void Init() override;

	void PreUpdate() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;

	void GenerateDepthMapFromLight() override;

	void OnHit(BallKind ballKind);

	int GetGoldCnt() { return GoldCnt; }

	int GetBoxType() { return static_cast<int>(m_BoxType); }

	void SetBallGenerate(BallGenerate* gen) { m_pBallGenerate = gen; }

private:

	void UpdateCollider(); //当たり判定用

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
		TrashBox,
	};

	BallGenerate* m_pBallGenerate = nullptr;

	BoxType m_BoxType = BoxType::BasketBallBox; //初期状態はバスケットボール

	//モデルやテクスチャはポインタで管理
	std::shared_ptr<KdModelData> m_BasketBallBoxModel;

	std::shared_ptr<KdModelData> m_ValleyBallBoxModel;
	
	std::shared_ptr<KdModelData> m_SoccerBallBoxModel;

	std::shared_ptr<KdModelData> m_TrashBoxModel;

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

	//スコア用
	int Score;     //合計スコア

	const int Addition = 100;

	const int FeverAddition = 200;

	const int Subtraction = 100;

	//ゴールドボール用
	int GoldCnt;

	const int MaxGoldCnt = 20;

	const int MaxFeverCnt = 10;

	int FeverCount;     //フィーバー中のヒット数

	bool FeverFlg;      //フィーバー中かどうか

	//ボールスピード用
	float NormalBallMoveSpeed;
	float NormalBallRotationSpeed;

	float MaxBallMoveSpeed;
	float MaxBallRotationSpeed;

	//スケールアニメーション用
	float Scale;        
	float ScaleSpeed;  

	float OneFrame;

	float MaxFrame;

	const float MaxScale = 1.5f;
	const float NormalScale = 1.0f;
	const float SmallScale = 0.5f;

	//エフェクト用
	const int   EffectCount = 20;
	const float EffectSpeed = 0.2f;
	const float EffectLifeSpan = 30.0f;

	const Math::Color EffectColorGreen = { 0, 1, 0, 1 }; // 緑
	const Math::Color EffectColorRed = { 1, 0, 0, 1 }; // 赤
};