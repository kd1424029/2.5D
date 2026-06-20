#pragma once

class CountDownUi : public KdGameObject
{
public:

	CountDownUi() {}
	~CountDownUi() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	bool IsFinished() const { return m_Finished; }   //カウントダウン終了したか

private:

	enum class Phase
	{
		Three,
		Two,
		One,
		Start,
		Finished
	};

	Phase m_Phase = Phase::Three;

	std::shared_ptr<KdTexture> m_NumberTex;  //Timerと同じ数字シート(3,2,1用)
	std::shared_ptr<KdTexture> m_StartTex;   //START表示用

	int m_FrameCount = 0;   //現在フェーズの経過フレーム

	bool m_Finished = false;

	const float PosX = 0;
	const float PosY = 100;

	//数字
	const int CharSize = 64;
	const int CharHeight = 105;

	//1フェーズあたりの表示フレーム数（60 = 1秒）
	const int PhaseFrame = 30;

	//START画像の描画サイズ
	const float StartWidth = 300;
	const float StartHeight = 150;
};