#pragma once

class KdCamera;

class Player;

class Score : public KdGameObject
{
public:

	Score() {}
	~Score() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	std::shared_ptr<KdTexture> m_Score;

	std::shared_ptr<KdTexture> m_ScoreUi;

	std::weak_ptr<KdCamera>   m_wpCamera;

	Player* m_pPlayer = nullptr;

	//座標
	const float PosX = 1.9;
	const float PosY = 8;

	const float Interval = 84;

	const float ScoreUiAdjustment = 160;

	//画像の大きさ
	const float Width = 120;
	const float Height = 120;

	const float ScoreUiWidth = 220;
	const float ScoreUiHeight = 110;

	//画像の切り取り間隔
	const long CuttingInterval = 64;
	const long CuttingWidth = 64;
	const long CuttingHeight = 64;

	//表示する桁数
	static const int maxDigits = 5;

	unsigned long m_score = 0;
	int m_digits[maxDigits] = {}; //各桁の数値を格納

	const float MaxScore = 99999;
};