#pragma once

class Timer : public KdGameObject
{
public:

	Timer() {}
	~Timer() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	bool GetTimeUp() const { return TimeUpFlg; }  //タイマーが0になったか

	bool IsReadyToChangeScene() const { return SceneChangeFlg; }

	float GetRemainingTime() const { return RemainTime; } //残り秒数を取得

	void SetPaused(bool flg) { PausedFlg = flg; }   //ゲーム開始カウントダウン中だけ呼ぶ

private:

	std::shared_ptr<KdTexture> m_Timer;

	std::shared_ptr<KdTexture> m_RestUi;

	bool PausedFlg = false;

	const int MaxTime = 120.0f;

	const float TimerPosX = 400;

	const float MaxPosY = 560;

	const float GoalPosY = 280;

	const float MoveSpeed = 20.0;

	float TimerPosY;

	//残り時間
	float RemainTime;   

	bool  TimeUpFlg = false;

	bool SceneChangeFlg = false;

	int SceneChangeWaitCount = 0;  //シーン遷移までの残りフレーム数

	const int SceneChangeWaitFrames = 90;

	const float DeltaTime = 1.0f / 60.0f;

	const int SecondsPerMinute = 60; //1分当たりの秒数

	const int DecimalBase = 10;      //十進数の桁取り出し用

	const int ColonIndex = 10;  //コロン用

	const int RoundUp = 1; //切り上げ用

	//表示する桁  分1桁 + コロン + 秒2桁 = 4文字
	static const int MaxDigits = 4;

	int Digits[MaxDigits] = {};   //0 = 分 1 = コロン 2 = 秒十の位 3 = 秒一の位

	//画像のサイズ
	const int CharSize = 64;    //画像の幅

	const int CharRectHeight = 100;    //画像の縦幅

	const int CharHeight = 105; //描画時の高さ

	const int CharSpacing = 60; //文字間隔(px)

	//終了カウント
	float Count;

	bool TimeUpSeFlg;
};