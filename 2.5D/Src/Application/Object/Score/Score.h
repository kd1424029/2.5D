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

	std::weak_ptr<KdCamera>   m_wpCamera;

	Player* m_pPlayer = nullptr;


	//表示する桁数
	static const int maxDigits = 5;

	unsigned long m_score = 0;
	int m_digits[maxDigits] = {}; //各桁の数値を格納
};