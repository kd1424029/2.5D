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

	float GetRemainingTime() const { return RemainTime; } //残り秒数を取得

private:

	std::shared_ptr<KdTexture> m_Timer;

	std::shared_ptr<KdTexture> m_RestUi;

	const int MaxTime = 120.0f;

	const float TimerPosX = 460;
	const float TimerPosY = 300;

	//RestUi用
	const int RestCharSize = 210;
	const int RestCharHeight = 110;

	//残り時間
	float RemainTime;   //3分00秒

	bool  TimeUpFlg = false;

	const float DeltaTime = 1.0f / 60.0f;

	const int SecondsPerMinute = 60; //1分当たりの秒数

	const int DecimalBase = 10;      //十進数の桁取り出し用

	const int ColonIndex = 10;  //コロン用

	const int RoundUp = 1; //切り上げ用

	//表示する桁  分1桁 + コロン + 秒2桁 = 4文字
	static const int MaxDigits = 4;

	int Digits[MaxDigits] = {};   //0 = 分 1 = コロン 2 = 秒十の位 3 = 秒一の位

	//表示位置オフセット(3D→2D変換後の調整)
	const float PosX = 4.8f;

	const float PosY = 7.7f;

	const float RestAdjustment = 110;

	//画像のサイズ
	const int CharSize = 64;    //画像の幅

	const int CharHeight = 105; //描画時の高さ

	const int CharSpacing = 50; //文字間隔(px)
};