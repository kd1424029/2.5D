#pragma once

class Player;

class Timer;

class Score : public KdGameObject
{
public:

	Score() {}
	~Score() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	void SetPlayer(Player* player) { m_pPlayer = player; }

	void SetTimer(Timer* timer) { m_pTimer = timer; }

	// Playerが存在しない場面（ResultSceneなど）で、固定のスコアを表示するために使う
	void SetFixedScore(unsigned long score) { m_score = score; }

	void SetGoalPosY(float posy) { GoalPosY = posy; }

	void SetPtGoalPosY(float posy) { PtGoalPosY = posy; }

	void SetScorePosY(float posy) { ScorePosY = posy; }

	void SetPtPosY(float posy) { PtPosY = posy; }

	void SetWidth(float width) { Width = width; }

	void SetHeight(float height) { Height = height; }

	void SetPtWidth(float width) { PtWidth = width; }

	void SetPtHeight(float height) { PtHeight = height; }

	void SetInterval(float interval) { Interval = interval; }

	void SetScorePosX(float posx) { ScorePosX = posx; }

	void SetPtPosX(float posx) { PtPosX = posx; }

	bool IsNewRecord() const { return IsNewRecordFlg; }

	unsigned long LoadHighScore() const; //外部ファイルからハイスコアを読み込む

private:

	void SaveHighScore();          //ハイスコアより高い場合のみ外部ファイルへ保存

	std::shared_ptr<KdTexture> m_Score;

	std::shared_ptr<KdTexture> m_ScorePt;

	Player* m_pPlayer = nullptr;

	Timer* m_pTimer = nullptr;

	bool HasSavedHighScore = false; //1ゲームにつき1回だけ保存するためのフラグ

	bool IsNewRecordFlg = false; //今回のプレイで新記録が出たか

	// ハイスコア保存先
	static constexpr const char* HighScoreFilePath = "Asset/SaveData/HighScore.txt";


	//座標
	float ScorePosX;

	float PtPosX = 240;

	float PtPosY;

	float PtGoalPosY = 260;

	float PtWidth = 60;

	float PtHeight = 101;

	const float MaxPosY = 560;

	const float PtMaxPosY = 540;

	float GoalPosY;

	const float MoveSpeed = 20.0;

	float ScorePosY;

	const float ScoreUiPosX = -310;
	const float ScoreUiPosY = 290;

	float Interval = 84;

	//画像の大きさ
	float Width;
	float Height;

	//画像の切り取り間隔
	const long CuttingInterval = 64;
	const long CuttingWidth = 64;
	const long CuttingHeight = 100;

	//表示する桁数
	static const int maxDigits = 5;

	unsigned long m_score = 0;
	int m_digits[maxDigits] = {}; //各桁の数値を格納

	const float MaxScore = 99999;
};