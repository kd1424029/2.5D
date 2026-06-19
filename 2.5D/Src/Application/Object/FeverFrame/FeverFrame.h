#pragma once

#include <random>

class Player;

//===================================================
//
// フィーバータイム中、画面の縁（フレーム）を
// 虹色グラデーション×脈動で光らせるUI
//
//===================================================
class FeverFrame : public KdGameObject
{
public:

	FeverFrame() {}
	~FeverFrame() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	//現在の演出用の色を計算する（色相を回転させつつ、明るさをsin波で脈動させる）
	Math::Color CalcFrameColor() const;

	//現在のシェイク量(横方向のオフセット)を更新する
	void UpdateShake();

	//HSV(色相・彩度・明度)からRGBへ変換するヘルパー
	static Math::Color HsvToColor(float hue, float saturation, float value, float alpha);

	Player* m_pPlayer = nullptr;

	float Time = 0.0f; //演出用の経過時間（秒）

	const float FrameTime = 1.0f / 60.0f;

	//--- シェイク（左右にガクガク震える演出）用 ---
	std::mt19937 m_ShakeRng{ std::random_device{}() }; //シェイク用の乱数エンジン

	float ShakeOffsetX = 0.0f; //現在の横方向シェイク量（ピクセル）

	int ShakeFrameCounter = 0; //次に乱数を更新するまでのフレーム数カウント

	const int ShakeUpdateInterval = 3; //何フレームごとに新しいシェイク値へ切り替えるか（小さいほどガクガクが速い）

	const float ShakeAmplitude = 6.0f; //シェイクの振れ幅（ピクセル、左右にこの値まで動く）

	//画面解像度（固定値）
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;

	//枠の太さ（ピクセル）
	const int FrameThickness = 8;

	//色相が1周する速さ（秒）。値が小さいほど色の変化が速い
	const float HueCycleSeconds = 2.0f;

	//明るさが脈動する速さ（Hz相当のイメージ。値が大きいほど点滅が速い）
	const float PulseSpeed = 3.0f;

	//明るさの脈動の振れ幅（0.0〜1.0）。大きいほど暗くなる瞬間が増える
	const float PulseAmplitude = 0.35f;

	//明るさの脈動の基準値（中心値）
	const float PulseBase = 0.65f;

	//彩度（鮮やかさ）。1.0で最も鮮やか
	const float FrameSaturation = 1.0f;

	//透明度
	float Alpha = 1.0f;

	const float AlphaSpeed = 0.01f;
};
