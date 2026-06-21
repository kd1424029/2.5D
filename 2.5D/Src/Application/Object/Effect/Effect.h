#pragma once

//エフェクトの種類によってUpdateの挙動を変える
enum class EffectType
{
	Particle, //通常のヒットパーティクル（縮みながら消える）
	Smoke,    //煙突から出る煙のような見た目（膨らみながらフェードアウト＋揺らぎ）
};

class Effect : public KdGameObject
{
public:

	Effect() {}
	~Effect() {}

	void Init() override;

	void Update() override;

	void DrawLit() override;

	void DrawBright() override;

	//startScale/endScale/wobbleはSmoke専用。Particleの場合は無視される
	void SetParam(Math::Vector3 pos, Math::Vector3 move, float lifeSpan, Math::Color color,
		EffectType type = EffectType::Particle, float startScale = 1.0f, float endScale = 1.0f, float wobble = 0.0f);

private:

	std::shared_ptr<KdModelData> m_Model;

	Math::Vector3 m_pos;

	Math::Vector3 m_Move;

	Math::Color m_Color;

	EffectType m_Type = EffectType::Particle;

	float LifeSpan;

	float MaxLifeSpan = 30.0f; //Playerと同じ寿命数値にする!

	//Smoke用パラメータ
	float m_StartScale = 1.0f; //発生直後の小ささ
	float m_EndScale = 1.0f;   //消える直前の膨らみきった大きさ
	float m_Wobble = 0.0f;     //左右に揺れる振れ幅
};