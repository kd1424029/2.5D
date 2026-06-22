#include "Effect.h"
#include <cmath>

void Effect::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_Model = std::make_shared<KdModelData>();
	m_Model->Load("Asset/Models/Ball/ParticleBall/Ball.gltf");

}

void Effect::Update()
{
	LifeSpan--;

	if (LifeSpan <= 0)
	{
		m_isExpired = true;
		return;
	}

	//0(発生直後)→1(消える直前)に進む進行度
	float progress = 1.0f - (LifeSpan / MaxLifeSpan);

	if (m_Type == EffectType::Smoke)
	{
		//煙突の煙のように上昇しつつ、サインカーブで左右にゆらゆら揺れる
		m_pos += m_Move;
		m_pos.x += sinf(LifeSpan * 0.3f) * m_Wobble;

		//寿命の前半(0〜ShrinkStartRatio)でボワっと膨らみ、
		//後半は縮みながら消えることで(だんだん薄くなって消える)見た目にする
		const float ShrinkStartRatio = 0.6f; //このタイミングから縮み始める

		float scale;

		if (progress < ShrinkStartRatio)
		{
			//前半 StartScaleからEndScaleまで膨らむ
			float growProgress = progress / ShrinkStartRatio;
			scale = m_StartScale + (m_EndScale - m_StartScale) * growProgress;
		}
		else
		{
			//後半 EndScaleから0まで縮んで消える
			float shrinkProgress = (progress - ShrinkStartRatio) / (1.0f - ShrinkStartRatio);
			scale = m_EndScale * (1.0f - shrinkProgress);
		}

		//サイズだけでなく透明度も下げて、より自然にフェードアウトさせる
		m_Color.A(1.0f - progress);

		Math::Matrix scaleMat = Math::Matrix::CreateScale(scale);
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
		m_mWorld = scaleMat * transMat;
	}
	else
	{
		//毎フレーム移動
		m_pos += m_Move;

		//寿命が尽きるその瞬間に綺麗にサイズを0にする計算
		float scale = LifeSpan / MaxLifeSpan;

		Math::Matrix scaleMat = Math::Matrix::CreateScale(scale);

		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

		m_mWorld = scaleMat * transMat;
	}
}

void Effect::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld, m_Color);
}

void Effect::DrawBright()
{
	//煙は光らせない
	if (m_Type == EffectType::Smoke) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld, m_Color);
}

void Effect::SetParam(Math::Vector3 pos, Math::Vector3 move, float lifeSpan, Math::Color color,
	EffectType type, float startScale, float endScale, float wobble)
{
	m_pos = pos;
	m_Move = move;
	LifeSpan = lifeSpan;
	MaxLifeSpan = lifeSpan;
	m_Color = color;
	m_Type = type;
	m_StartScale = startScale;
	m_EndScale = endScale;
	m_Wobble = wobble;
}