#include "BallBase.h"

#include "../../Scene/SceneManager.h"

#include "../../Object/Player/Player.h" //当たり判定で必要

void BallBase::Init()
{
	m_BallModel = nullptr;

	MoveState = BallMove::FirstMove;

	PositionState = Position::Fifth;

	Gravity = 0.0f;

	TargetX = 0.0f;

	GoalTargetX = 0.0f;

	RotationX = 0.0f;

	RotationZ = 0.0f;

	Count = 0;

	//デバッグ用：KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void BallBase::Update()
{
	switch (MoveState)	
	{
	case FirstMove:

		m_pos.z += MoveSpeed;

		RotationZ = 0;

		RotationX -= RotationSpeed;

		if (m_pos.z > MaxPosZ)
		{
			m_pos.z = MaxPosZ;

			DecisionPosition();

			MoveState = BallMove::SecondMove;
		}

		break;

	case SecondMove:

		RotationX = 0;

		switch (PositionState)
		{
		case Position::First:	

			TargetX = FirstFromTheLeftPos;

			break; 
		case Position::Second:	

			TargetX = SecondFromTheLeftPos;
			
			break;
		case Position::Third:	
			
			TargetX = ThirdFromTheLeftPos;
			
			break; 
		case Position::Fourth:	
			
			TargetX = FourthFromTheLeftPos;
			
			break;
		case Position::Fifth:	
			
			TargetX = FifthFromTheLeftPos;
			
			break; 
		}

		//現在のX座標から目標のX座標への距離と向きを計算する
		GoalTargetX = TargetX - m_pos.x;       //目標までの残りの距離（方向付き）

		//1フレームの移動量が残り距離を超えないように制御して移動する 
		if (fabs(GoalTargetX) <= MoveSpeed) //マイナスの値をプラスに変換する関数
		{
			//残り距離が移動速度より小さければピッタリ目標座標に到着
			m_pos.x = TargetX;

			//次の移動状態へ
			MoveState = BallMove::ThirdMove;
		}
		else
		{
			//目標に向かって符号（プラスマイナス）を判定して進む
			if (GoalTargetX > 0)
			{
				m_pos.x += MoveSpeed; //目標が右側にあるなら右へ

				RotationZ += RotationSpeed;
			}
			else
			{
				m_pos.x -= MoveSpeed; //目標が左側にあるなら左へ

				RotationZ -= RotationSpeed;
			}
		}

		break;

	case ThirdMove:

		m_pos.z -= MoveSpeed;

		RotationZ = 0;

		RotationX += RotationSpeed;

		break;

	}

	m_pos.y -= Gravity;
	Gravity += GravitySpeed;

	if (m_pos.y < -10)
	{
		m_isExpired = true;
	}

}

void BallBase::PostUpdate()
{
	// ======================= 球（スフィア）判定だけ ============================
	KdCollider::SphereInfo sphere;

	sphere.m_sphere.Center = m_pos;

	sphere.m_sphere.Radius = 0.3f;

	sphere.m_type = KdCollider::TypeGround;

	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

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

	Math::Matrix scaleMat = Math::Matrix::CreateScale(0.6f);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix rotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(RotationX));

	Math::Matrix rotationZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(RotationZ));

	m_mWorld =scaleMat * rotationZMat * rotationXMat * transMat;


	// ======================= Box（プレイヤー）との判定 ============================
	KdCollider::SphereInfo damageSphere;

	damageSphere.m_sphere.Center = m_pos;
	damageSphere.m_sphere.Radius = 0.3f;
	damageSphere.m_type = KdCollider::TypeDamage; //TypeDamageで探す

	std::list<KdCollider::CollisionResult> retDamageList;

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		retDamageList.clear();

		if (obj->Intersects(damageSphere, &retDamageList))
		{
			auto* player = dynamic_cast<Player*>(obj.get());

			if (player)
			{
				player->OnHit(ballKind);
			}

			m_isExpired = true;
			break;
		}
	}
}

void BallBase::DrawLit()
{
	if (m_BallModel)
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
	}
}

void BallBase::DecisionPosition()
{
	//ポジションの種類数（Noneが5番目なので0〜4の全部で5種類）
	const int PositionCount = static_cast<int>(Position::None);

	Position PositionType;

	do
	{
		//0〜4の乱数を生成
		PositionType = static_cast<Position>(rand() % PositionCount);
	} 
	while (PositionType == PositionState); //前回と同じなら選び直す

	PositionState = PositionType; //今回の種類を記憶
}
