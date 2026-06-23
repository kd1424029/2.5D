#pragma once

#include "../../Object/Ball/BallBase.h"

static float RandRange(float range)
{
	return ((float)rand() / RAND_MAX - 0.5f) * range;
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

	void DrawLit() override;

	void GenerateDepthMapFromLight() override;

	void OnHit(BallKind ballKind);

	int GetScore() { return Score; }

	int GetGoldCnt() { return GoldCnt; }

	int GetBoxType() { return static_cast<int>(m_BoxType); }

	bool GetFeverFlg() { return FeverFlg; }

	bool GetGameStopped() const { return GameStopped; }

	void SetGameStopped(bool flg) { GameStopped = flg; }

	void SetBallGenerate(BallGenerate* gen) { m_pBallGenerate = gen; }

	void SetResetGoldCnt() { GoldCnt = 0; }

private:

	void UpdateCollider(); //当たり判定用

	void EndFever(); //フィーバー終了処理（共通化）

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
		NormalBox,
		TrashBox,
	};

	BallGenerate* m_pBallGenerate = nullptr;

	BoxType m_BoxType = BoxType::NormalBox; //初期状態はバスケットボール

	//モデルやテクスチャはポインタで管理
	std::shared_ptr<KdModelData> m_NormalBoxModel;

	std::shared_ptr<KdModelData> m_TrashBoxModel;

	//Box切り替え用
	BoxType m_NextBoxType = BoxType::NormalBox; //次に変更する箱のタイプ

	bool GameStopped = false;

	float BoxPosZ;    //元のZ座標

	const float NormalBoxPosY = 1.5;

	const float DirtyBoxPosY = 1.15;

	const float SwitchDepth = -10.0f; //どれくらい奥に引っ込めるか

	const float SwitchSpeed = 1.5f; //引っ込むスピード

	bool KeyFlg;

	//移動用
	Math::Vector3 m_pos = {};  //座標

	Math::Vector3 m_TargetPos = {};    // 移動先の目標座標

	const float MoveAmount = 2.0f;

	const float MoveMaxAmount = 3.3f;   //移動の最大距離

	const float MoveSpeed = 0.5f;

	bool MoveFlgLeft;   //移動の入力を受け付けるフラグ

	bool MoveFlgRight;

	int MoveCoolDownCount; //クールタイムの残りフレーム数カウント

	const int MoveCoolDownMax = 5;   //移動後に押しっぱなしで次へ進むまでの待ち時間

	PlayerState m_State = PlayerState::Idle;  //プレイヤーの状態を管理する変数

	//スコア用
	int Score;     //合計スコア

	const int MaxScore = 999999;

	const int Addition = 500;

	const int FeverAddition = 1000;

	const int Subtraction = 500;

	//ゴールドボール用
	int GoldCnt;

	bool FeverFlg;      //フィーバー中かどうか

	//ボールスピード用
	float NormalBallMoveSpeed;
	float NormalBallRotationSpeed;

	float MaxBallMoveSpeed;
	float MaxBallRotationSpeed;

	//スケールアニメーション用
	float Scale;

	float OneFrame;

	float MaxFrame;

	bool ScaleFlg;

	const float ScaleSpeed = 0.1;

	const float MaxScale = 1.6f;

	const float NormalScale = 1.0f;

	//エフェクト用(ヒット時の緑パーティクル)
	const int   EffectCount = 15;
	const float EffectSpeed = 0.2f;
	const float EffectLifeSpan = 30.0f;

	const float EffectAdjust = 0.3;

	const float EffectAdjustTrash = 0.8; //ゴミ箱の時はエフェクトの発生Yを高くする

	const float EffectAdjustNormalBox = 0.8; //ゴミ箱の時はエフェクトの発生Yを高くする

	const Math::Color EffectColorGreen = { 0, 1, 0, 1 }; //緑
	const Math::Color EffectColorGray = { 1, 1, 1, 1 };  //黒色（ミス時の煙）

	//ミス時の煙エフェクト用(煙突からボワっと出るイメージ)
	const int   SmokeEffectCount = 15;     //一度のミスで出す煙の数
	const float SmokeRiseSpeed = 0.05f;   //上昇スピード
	const float SmokeLifeSpan = 30.0f;    //煙が消えるまでのフレーム数
	const float SmokeStartScale = 0.3f;   //出てきた瞬間の小ささ
	const float SmokeEndScale = 1.6f;     //消える直前のボワっとした大きさ
	const float SmokeWobble = 0.02f;      //左右の揺らぎ幅
	const float SmokeSpreadXZ = 0.6f;     //発生位置をXZ方向にどれだけ散らばらせるか
	const float SmokeRiseSpeedRange = 0.09f; //上昇スピードの個体差（速い煙/遅い煙ができる）
	const float SmokeXMoveRange = 0.08f;  //上昇しながらX方向にどれだけ流れていくか(個体ごとにランダム)

	//最初の動き用
	bool BeginningFlg;  //最初の動き

	const float MaxBeginningPosZ = -20;

	const float GoalBeginningPosZ = -0.1;

	const float BeginningMoveSpeed = 1.0;
};