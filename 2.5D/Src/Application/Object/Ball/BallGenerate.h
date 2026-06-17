#pragma once
#include "BallBase.h"
#include <vector>
#include <random>

class Player;

class BallGenerate
{
public:

	BallGenerate();
	~BallGenerate() {}

	//ランダムなボールを1つ生成して返す
	std::shared_ptr<BallBase> Generate();

	int GetWaveLevel() { return WaveLevel; }

	//ウェーブレベルが前回から変わったかを判定する
	//（NewProductsGenerateがラベルを1回だけ出すタイミング検知に使用）
	//ウェーブ1はラベル対象外（NewProductsGenerate::Generateも何も返さない）なので、
	//ウェーブ1への変化（ゲーム開始直後の初回判定含む）はtrueにしない
	bool IsWaveChanged()
	{
		int currentWave = CalcCurrentWave();

		if (currentWave != m_LastLabelWave)
		{
			m_LastLabelWave = currentWave;

			if (currentWave == 1)
			{
				return false;
			}

			return true;
		}

		return false;
	}

	void SetTarget(Player* player) { m_TargetPlayer = player; }

	void ResetGoldFlg() { GoldFlg = false; }

	void SetMoveSpeed(float move) { MoveSpeed = move; }

	void SetRotationSpeed(float rotationspeed) { RotationSpeed = rotationspeed; }

	void SetRemainingTime(int time) { RemainingTime = time; }

	void SetStartFever()
	{
		int waveMax = CalcCurrentWave();

		std::uniform_int_distribution<int> dist(0, waveMax - 1);
		FeverBallType = dist(m_Rng);
	}

private:

	std::shared_ptr<KdModelData> m_BasketBallModel;

	std::shared_ptr<KdModelData> m_VolleyBallModel;

	std::shared_ptr<KdModelData> m_SoccerBallModel;

	std::shared_ptr<KdModelData> m_DirtySoccerBallModel;

	std::shared_ptr<KdModelData> m_GoldBallModel;

	Player* m_TargetPlayer = nullptr;

	//ウェーブ設定を定数で管理
	const int WaveTime1 = 100; //100秒以上 → SoccerBallのみ
	const int WaveTime2 = 85;  //85秒以上 → + DirtySoccerBall
	const int WaveTime3 = 55;  //55秒以上 → + BasketBall
	const int WaveTime4 = 45;  //45秒以上 → + VolleyBall

	int RemainingTime = 120;

	int WaveLevel = 0;

	int LastWaveLevel = -1; // 前回のウェーブレベル(デッキ再構築判定用)

	// デッキをシャッフルして先頭から配り直す
	void ShuffleDeck();

	void ShuffleLaneDeck(); //レーン配置用デッキシャッフル

	//RemainingTimeから現在のウェーブレベルを計算する（副作用なし）
	//ShuffleDeck・Generate・IsWaveChangedで共通利用
	int CalcCurrentWave()
	{
		if (RemainingTime >= WaveTime1)
		{
			return 1;
		}
		else if (RemainingTime >= WaveTime2)
		{
			return 2;
		}
		else if (RemainingTime >= WaveTime3)
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}

	int m_LastLabelWave = -1; //ラベル表示用：前回判定したウェーブレベル

	const int BallCount = 4;

	const int MaxGoldCnt = 5;

	bool GoldFlg = false;

	const int Left = 1;
	const int Right = 0;
	const int None = -1;

	const Math::Vector3 FirstLeftPos = { -6, 3.23f, -2 };
	const Math::Vector3 FirstRightPos = { 6, 3.23f, -2 };

	// --- シャッフルデッキ用 ---
	std::mt19937            m_Rng;       //乱数エンジン
	std::vector<int>        m_Deck;      //今のデッキ（BallTypeのint値が入る）
	int                     DeckIndex;   //次に配るインデックス

	//レーン配置用（0〜4のレーン番号が入る）
	std::vector<int>        m_LaneDeck;
	int                     m_LaneDeckIndex;

	const int MaxLane = 5;

	//出現位置用
	int m_lastPosType; //前回の位置 (0:左 / 1:右 / -1:未設定)

	//BallSpeed用
	float MoveSpeed = 0.04f;
	float RotationSpeed = 3.0f;

	//フィーバータイムのボールを決めるよう
	int FeverBallType = -1;
};
