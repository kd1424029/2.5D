#include "Player.h"

#include "../../Scene/SceneManager.h"

#include "../Effect/Effect.h"

void Player::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BasketBallBoxModel = std::make_shared<KdModelData>();
	m_BasketBallBoxModel->Load("Asset/Models/Box/BasketBallBox/BasketBallBox.gltf");

	m_ValleyBallBoxModel = std::make_shared<KdModelData>();
	m_ValleyBallBoxModel->Load("Asset/Models/Box/VolleyBallBox/VolleyBallBox.gltf");

	m_SoccerBallBoxModel = std::make_shared<KdModelData>();
	m_SoccerBallBoxModel->Load("Asset/Models/Box/SoccerBallBox/SoccerBallBox.gltf");

	m_TrashBoxModel = std::make_shared<KdModelData>();
	m_TrashBoxModel->Load("Asset/Models/Box/TrashBox/TrashBox.gltf");

	m_pos = { 0,1.9,-0.1 };

	MoveCoolDownCount = 0;

	BoxPosZ = -0.1f;

	KeyFlg = false;

	m_TargetPos = m_pos; 

	MoveFlgLeft = true;

	MoveFlgRight = true;

	Score = 0;

	Scale = 1;

	ScaleSpeed = 5.0;

	OneFrame = 1.0f;

	MaxFrame = 60.0f;

	UpdateCollider();
}

void Player::PreUpdate()
{
}

void Player::Update()
{
	//現在のScoreをデバッグ
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", Score);

	{//移動中の処理
		switch (m_State)
		{
		case PlayerState::Idle:
		{
			Math::Vector3 nextTarget = m_pos;
			bool inputDetected = false;

			if (GetAsyncKeyState(VK_LEFT) & 0x8000 && MoveFlgLeft == true)
			{
				nextTarget.x -= MoveAmount;
				inputDetected = true;
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && MoveFlgRight == true)
			{
				nextTarget.x += MoveAmount;
				inputDetected = true;
			}

			if (inputDetected == true)
			{
				m_TargetPos = nextTarget;
				m_State = PlayerState::Moving; //移動状態へ遷移
			}
		}
		break;

		case PlayerState::Moving:
		{
			Math::Vector3 moveDir = m_TargetPos - m_pos;
			float distance = moveDir.Length();

			if (distance <= MoveSpeed)
			{
				m_pos = m_TargetPos;
				MoveCoolDownCount = MoveCoolDownMax;
				m_State = PlayerState::CoolDown; //クールタイム状態へ遷移
			}
			else
			{
				moveDir.Normalize();
				m_pos += moveDir * MoveSpeed;
			}
		}
		break;

		case PlayerState::CoolDown:
		{
			MoveCoolDownCount--;

			if (MoveCoolDownCount <= 0)
			{
				m_State = PlayerState::Idle; //入力待ち状態へ遷移
			}
		}
		break;

		case PlayerState::SwitchOut:
		{
			m_pos.z -= SwitchSpeed; //奥へ引っ込む

			if (m_pos.z < SwitchDepth)
			{
				m_pos.z = SwitchDepth;

				//確定した次のタイプを代入する
				m_BoxType = m_NextBoxType;

				m_State = PlayerState::SwitchIn; //前に戻る状態へ
			}
		}
		break;

		case PlayerState::SwitchIn:
		{
			m_pos.z += SwitchSpeed; //手前へ戻る

			if (m_pos.z > BoxPosZ)
			{
				m_pos.z = BoxPosZ;

				UpdateCollider();

				m_State = PlayerState::Idle; //待機状態へ
			}
		}
		break;
		}
	}

	{//移動範囲の制限
		if (m_pos.x >= MoveMaxAmount)
		{
			MoveFlgRight = false;
		}
		else
		{
			MoveFlgRight = true;
		}

		if (m_pos.x <= -MoveMaxAmount)
		{
			MoveFlgLeft = false;
		}
		else
		{
			MoveFlgLeft = true;
		}
	}

	//Box切り替え処理
	if ((GetAsyncKeyState('Z') & 0x8000) || (GetAsyncKeyState('X') & 0x8000))
	{
		//待機状態かつ押しっぱなしロックがかかっていない時だけ受け付ける
		if (KeyFlg == false && m_State == PlayerState::Idle)
		{
			//BoxTypeをintに変換して循環計算する
			int current = static_cast<int>(m_BoxType);

			const int Adjustment = 1;

			const int BoxTypeCount = 4; //Box種類の総数

			if (GetAsyncKeyState('Z') & 0x8000)
			{
				//順送り0→1→2→3→0
				m_NextBoxType = static_cast<BoxType>((current + Adjustment) % BoxTypeCount);
			}
			else if (GetAsyncKeyState('X') & 0x8000)
			{
				//逆送り0→3→2→1→0
				m_NextBoxType = static_cast<BoxType>((current + BoxTypeCount - Adjustment) % BoxTypeCount);
			}

			//すでに同じBoxなら切り替え不要
			if (m_BoxType != m_NextBoxType)
			{
				m_State = PlayerState::SwitchOut; //後ろに下がる状態へ
				KeyFlg = true;                    //押しっぱなし防止ロック
			}
		}
	}
	else
	{
		//Z X どちらも押されていない時だけロック解除
		KeyFlg = false;
	}

	//もしScaleがNormalScaleより大きければ毎フレーム少しずつ小さくしてNormalScaleに近づける
	if (Scale > NormalScale)
	{
		//経過時間(秒)を使って滑らかに減算（1秒間に ScaleSpeed 分小さくなる）
		Scale -= ScaleSpeed * (OneFrame / MaxFrame); 

		//行き過ぎて1.0未満にならないようにガード
		if (Scale < NormalScale)
		{
			Scale = NormalScale;
		}
	}
	//Match失敗時に小さくする演出も入れる
	else if (Scale < NormalScale)
	{
		Scale += ScaleSpeed * (OneFrame / MaxFrame);

		if (Scale > NormalScale)
		{
			Scale = NormalScale;
		}
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix scaleMat = Math::Matrix::CreateScale(Scale);

	m_mWorld = scaleMat * transMat;

}

void Player::PostUpdate()
{
	
}

void Player::DrawLit()
{
	//現在のタイプに応じて描画するモデルを切り替える！
	if (m_BoxType == BoxType::BasketBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BasketBallBoxModel, m_mWorld);
	}
	else if(m_BoxType == BoxType::VolleyBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ValleyBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::SoccerBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_SoccerBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::TrashBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_TrashBoxModel, m_mWorld);
	}
}

void Player::GenerateDepthMapFromLight()
{
	if (m_BoxType == BoxType::BasketBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BasketBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::VolleyBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ValleyBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::SoccerBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_SoccerBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::TrashBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_TrashBoxModel, m_mWorld);
	}
}

void Player::OnHit(BallKind ballKind)
{
	// BallTypeとBoxTypeの対応チェック
	bool Match = false;

	if (ballKind == BallKind::Kind_BasketBall && m_BoxType == BoxType::BasketBallBox)
	{
		Match = true;
	}

	else if (ballKind == BallKind::Kind_VolleyBall && m_BoxType == BoxType::VolleyBallBox)
	{
		Match = true;
	}

	else if (ballKind == BallKind::Kind_SoccerBall && m_BoxType == BoxType::SoccerBallBox)
	{
		Match = true;
	}

	else if (ballKind == BallKind::Kind_DirtySoccerBall && m_BoxType == BoxType::TrashBox)
	{
		Match = true;
	}

	if (Match)
	{
		Score++;

		Scale = MaxScale;

		for (int i = 0; i < 20; i++)
		{
			auto effect = std::make_shared<Effect>();
			effect->Init();

			Math::Vector3 move = {
				((rand() % 100) / 100.0f - 0.5f) * 0.3f,
				((rand() % 100) / 100.0f) * 0.3f,
				((rand() % 100) / 100.0f - 0.5f) * 0.3f
			};

			effect->SetParam(m_pos, move, 30.0f, Math::Color(0, 1, 0, 1));
			SceneManager::Instance().AddObject(effect); 
		}
	}
	else
	{
		Score--;

		Scale = SmallScale;

		for (int i = 0; i < 20; i++)
		{
			auto effect = std::make_shared<Effect>();
			effect->Init();

			Math::Vector3 move = {
				((rand() % 100) / 100.0f - 0.5f) * 0.3f,
				((rand() % 100) / 100.0f) * 0.3f,
				((rand() % 100) / 100.0f - 0.5f) * 0.3f
			};
			
			effect->SetParam(m_pos, move, 30.0f, Math::Color(1, 0, 0, 1));
			SceneManager::Instance().AddObject(effect);
		}
	}
}

void Player::UpdateCollider()
{
	m_pCollider = std::make_unique<KdCollider>();

	if (m_BoxType == BoxType::BasketBallBox)
	{
		m_pCollider->RegisterCollisionShape(
			"BasketBallBoxModelCollision",
			m_BasketBallBoxModel,
			KdCollider::TypeDamage
		);
	}
	else if (m_BoxType == BoxType::VolleyBallBox)
	{
		m_pCollider->RegisterCollisionShape(
			"VolleyBallBoxModelCollision",
			m_ValleyBallBoxModel,
			KdCollider::TypeDamage
		);
	}
	else if (m_BoxType == BoxType::SoccerBallBox)
	{
		m_pCollider->RegisterCollisionShape(
			"SoccerBallBoxModelCollision",
			m_SoccerBallBoxModel,
			KdCollider::TypeDamage
		);
	}
	else if (m_BoxType == BoxType::TrashBox)
	{
		m_pCollider->RegisterCollisionShape(
			"TrashBoxModelCollision",
			m_TrashBoxModel,
			KdCollider::TypeDamage
		);
	}
}
