#pragma once

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

	void SetPlayer(Player* player) { m_pPlayer = player; }

private:

	std::shared_ptr<KdTexture> m_Line;

	Player* m_pPlayer = nullptr;

	const Math::Vector3 NormalBoxPos = { -50 ,-290 ,0 };
	
	const Math::Vector3 TrashBoxPos = { 51 ,-290 ,0 };


	//座標を切り替えるための管理用変数
	std::vector<Math::Vector3> m_PosList;	       //座標の選択肢リスト
	int                        m_CurrentIndex;	   //0→NormalBoxPos 1→TrashBoxPos
	Math::Vector3              m_CurrentPos;       //現在の表示座標
};