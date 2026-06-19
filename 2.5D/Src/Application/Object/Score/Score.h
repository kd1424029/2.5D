#pragma once

class Player;

class Score : public KdGameObject
{
public:

	Score() {}
	~Score() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	std::shared_ptr<KdTexture> m_Score;

	std::shared_ptr<KdTexture> m_ScoreUi;

	Player* m_pPlayer = nullptr;

	//座標
	const float ScorePosX = -170;
	const float ScorePosY = 290;

	const float ScoreUiPosX = -310;
	const float ScoreUiPosY = 290;

	const float Interval = 84;

	//画像の大きさ
	const float Width = 110;
	const float Height = 110;

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