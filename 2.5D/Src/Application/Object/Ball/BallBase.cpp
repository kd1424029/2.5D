#include "BallBase.h"

#include "../../Scene/SceneManager.h"

void BallBase::Init()
{
	m_BallModel = nullptr;

	MoveState = BallMove::FirstMove;
	Gravity = 0.0f;

	Count = 0;

	//デバッグ用：KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void BallBase::Update()
{
	switch (MoveState)	
	{
	case FirstMove:

		m_pos.z += 0.05f;

		if (m_pos.z >  10)
		{
			m_pos = ThirdFromTheLeftPos;
			MoveState = BallMove::SecondMove;
		}

		break;

	case SecondMove:

		Count++;

		if (Count >= 60 && Count <= 120)
		{
			//重力反映
			m_pos.y -= Gravity;
			Gravity += 0.005f;
		}

		else if (Count > 60 &&Count >= 120)
		{
			m_pos.z -= 0.05f;

			//重力反映
			m_pos.y -= Gravity;
			Gravity += 0.005f;
		}

		break;

	}
}

void BallBase::PostUpdate()
{
	// ======================= 球（スフィア）判定だけ ============================
	KdCollider::SphereInfo sphere;

	sphere.m_sphere.Center = m_pos;

	sphere.m_sphere.Radius = 0.3f;

	sphere.m_type = KdCollider::TypeGround;

	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	std::list<KdCollider::CollisionResult> retSphereList;

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}

	float maxOverlap = 0;

	bool hit = false;

	Math::Vector3 hitDir;

	for (auto& ret : retSphereList)
	{
		if (maxOverlap < ret.m_overlapDistance)
		{
			maxOverlap = ret.m_overlapDistance;

			hitDir = ret.m_hitDir;

			hit = true;
		}
	}

	if (hit == true)
	{
		//Z方向の無効化をなくし、ぶつかった方向に100%正しく押し戻す
		//もし地面に当たったら hitDir は「真上」を向くので、勝手に重力もリセットできる
		if (hitDir.y > 0.5f)
		{
			Gravity = 0.0f; // 上向きの押し戻しが発生＝接地した、なので重力を止める
		}

		// 押し戻し処理
		m_pos += hitDir * maxOverlap;
	}

	m_mWorld.Translation(m_pos);
}

void BallBase::DrawLit()
{
	if (m_BallModel)
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
	}
}
