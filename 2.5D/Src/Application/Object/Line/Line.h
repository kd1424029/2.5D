#pragma once

class KdCamera;

class Player;

class Line : public KdGameObject
{
public:

	Line() {}
	~Line() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	std::shared_ptr<KdTexture> m_Line;

	std::weak_ptr<KdCamera>   m_wpCamera;

	Player* m_pPlayer = nullptr;

	const Math::Vector3 SoccerBallPos = { -6.69 ,7.7 ,0 };

	const Math::Vector3 VolleyBallPos = { -6.7 ,6.78 ,0 };

	const Math::Vector3 BasketBallPos = { -0.6 ,1.23 ,0 };

	const Math::Vector3 TrashBoxPos = { 0.6 ,1.23 ,0 };


	//座標を切り替えるための管理用変数
	std::vector<Math::Vector3> m_PosList;	       //座標の選択肢リスト
	int                        m_CurrentIndex; //0→SoccerBallPos 1→VolleyBallPos 2→BasketBallPos 3→TrashBoxPos
	Math::Vector3              m_CurrentPos;       //現在の表示座標
};