#pragma once

class Score;

class TitleUi : public KdGameObject
{
public:

	TitleUi() {}
	~TitleUi() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

private:

	std::shared_ptr<KdTexture> m_StartUi;

	std::shared_ptr<KdTexture> m_BestScoreUi;

	std::shared_ptr<KdTexture> m_Pick;

	std::shared_ptr<Score> m_pBestScoreDisplay;

	bool ShowBestScore = false; //暗転＋スコア表示中かどうか

	const float DarkAlpha = 0.8f; //暗転の濃さ

	const int ScreenWidth = 1280;

	const int ScreenHeight = 720;

	const float PosX = 0;
	const float BestScorePosX = 50;
	const float StartPosY = -100;

	const float BestScorePosY = -250;

	float StartAlpha;

	float BestScoreAlpha;

	const float AlphaSpeed = 0.02;

	const float MaxAlpha = 1;

	const float BottomAlpha = 0.3;

	bool StartAlphaFlg;

	bool BestScoreAlphaFlg;

	int NowPick;

	const float PickX = -250;

	float PickY;

	bool KeyFlg;

	bool KeySpaceFlg;
};