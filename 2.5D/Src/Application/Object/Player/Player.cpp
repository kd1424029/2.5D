#include "Player.h"

#include "../../Scene/SceneManager.h"

#include "../Effect/Effect.h"

#include "../../Object/Ball/BallBase.h"

#include "../Ball/BallGenerate.h"

void Player::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_NormalBoxModel = std::make_shared<KdModelData>();
	m_NormalBoxModel->Load("Asset/Models/Box/Box/Box.gltf");

	m_TrashBoxModel = std::make_shared<KdModelData>();
	m_TrashBoxModel->Load("Asset/Models/Box/TrashBox/TrashBox.gltf");

	BeginningFlg = true;

	m_pos = { 0,1.5,MaxBeginningPosZ };

	MoveCoolDownCount = 0;

	BoxPosZ = -0.1f;

	KeyFlg = false;

	m_TargetPos = m_pos;

	MoveFlgLeft = true;

	MoveFlgRight = true;

	Score = 0;

	Scale = 1;

	ScaleFlg = false;

	OneFrame = 1.0f;

	MaxFrame = 60.0f;

	GoldCnt = 0;

	FeverFlg = false;

	NormalBallMoveSpeed = 0.04;
	NormalBallRotationSpeed = 3.0;

	MaxBallMoveSpeed = 0.08;
	MaxBallRotationSpeed = 6.0;

	UpdateCollider();
}

void Player::PreUpdate()
{}

void Player::Update()
{
	if (GameStopped == true) return;

	if (BeginningFlg)
	{
		m_pos.z += BeginningMoveSpeed;

		if (m_pos.z > GoalBeginningPosZ)
		{
			m_pos.z = GoalBeginningPosZ;

			BeginningFlg = false;
		}

		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
		m_mWorld = transMat;
	}

	if (BeginningFlg == true)return;

	//現在のScoreをデバッグ
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", Score);

	//フィーバー終了判定 決められた個数を出し切りかつ画面上にフィーバーボールが1つも残っていなければ終了
	if (FeverFlg && m_pBallGenerate != nullptr && m_pBallGenerate->IsFeverSpawnFinished())
	{
		bool feverBallRemains = false;

		const auto& objList = SceneManager::Instance().GetObjList();

		for (auto& obj : objList)
		{
			BallBase* ball = dynamic_cast<BallBase*>(obj.get());

			if (ball != nullptr && ball->GetIsFeverBall())
			{
				feverBallRemains = true;
			}
		}

		if (feverBallRemains == false)
		{
			EndFever();

			KdAudioManager::Instance().Play("Asset/Sounds/Bgm/GameBgm.WAV", true);
		}
	}

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

				KdAudioManager::Instance().Play("Asset/Sounds/Se/Slide.WAV", false);
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && MoveFlgRight == true)
			{
				nextTarget.x += MoveAmount;
				inputDetected = true;

				KdAudioManager::Instance().Play("Asset/Sounds/Se/Slide.WAV", false);
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

	//移動範囲の制限
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


	//Box切り替え処理
	if ((GetAsyncKeyState('Z') & 0x8000) || (GetAsyncKeyState('X') & 0x8000))
	{
		//待機状態かつ押しっぱなしロックがかかっていない時だけ受け付ける
		if (KeyFlg == false && m_State == PlayerState::Idle)
		{
			//BoxTypeをintに変換して循環計算する
			int current = static_cast<int>(m_BoxType);

			const int Adjustment = 1;

			const int BoxTypeCount = 2; //Box種類の総数

			if (GetAsyncKeyState('Z') & 0x8000)
			{
				//順送り0→1→0→1
				m_NextBoxType = static_cast<BoxType>((current + Adjustment) % BoxTypeCount);

				KdAudioManager::Instance().Play("Asset/Sounds/Se/Switching.WAV", false);
			}
			else if (GetAsyncKeyState('X') & 0x8000)
			{
				//逆送り1→0→1→0
				m_NextBoxType = static_cast<BoxType>((current + BoxTypeCount - Adjustment) % BoxTypeCount);

				KdAudioManager::Instance().Play("Asset/Sounds/Se/Switching.WAV", false);
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

	if (m_BoxType == BoxType::NormalBox)
	{
		m_pos.y = NormalBoxPosY;
	
	}
	else if (m_BoxType == BoxType::TrashBox)
	{
		m_pos.y = DirtyBoxPosY;
	}

	if (ScaleFlg == true)
	{
		Scale += ScaleSpeed;

		if (Scale > MaxScale)
		{
			ScaleFlg = false;
		}
	}
	else
	{
		Scale -= ScaleSpeed;

		if (Scale < NormalScale)
		{
			Scale = NormalScale;
		}

	}


	//デバッグキー
	if (GetAsyncKeyState('F') & 0x8000)
	{
		GoldCnt = 5;
	}


	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix scaleMat = Math::Matrix::CreateScale(Scale);

	m_mWorld = scaleMat * transMat;

}

void Player::DrawLit()
{
	//現在のタイプに応じて描画するモデルを切り替える！
	if (m_BoxType == BoxType::NormalBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_NormalBoxModel, m_mWorld);
	}

	else if (m_BoxType == BoxType::TrashBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_TrashBoxModel, m_mWorld);
	}
}

void Player::GenerateDepthMapFromLight()
{
	if (m_BoxType == BoxType::NormalBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_NormalBoxModel, m_mWorld);
	}

	else if (m_BoxType == BoxType::TrashBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_TrashBoxModel, m_mWorld);
	}
}

void Player::OnHit(BallKind ballKind)
{
	//BallTypeとBoxTypeの対応チェック
	bool Match = false;

	bool GoldMatch = false;

	if (ballKind == BallKind::Kind_NormalBall && m_BoxType == BoxType::NormalBox)
	{
		Match = true;
	}

	else if (ballKind == BallKind::Kind_DirtySoccerBall && m_BoxType == BoxType::TrashBox)
	{
		Match = true;
	}

	else if (ballKind == BallKind::Kind_GoldBall)
	{
		Match = true;
		GoldMatch = true;
	}

	if (Match)
	{
		KdAudioManager::Instance().Play("Asset/Sounds/Se/Match.WAV", false);

		if (FeverFlg == true)
		{
			Score += FeverAddition;
		}
		else
		{
			Score += Addition;
		}

		GoldCnt++;

		ScaleFlg = true;

		if (GoldMatch)
		{
			KdAudioManager::Instance().PauseAllSound();

			KdAudioManager::Instance().Play("Asset/Sounds/Se/GoldMatch.WAV", false);

			KdAudioManager::Instance().Play("Asset/Sounds/Bgm/FeverBgm.WAV", true);
			//GoldBall取得→フィーバー開始
			FeverFlg = true;

			m_pBallGenerate->SetStartFever();//フィーバーボールを抽選

			const auto& objList = SceneManager::Instance().GetObjList();
			
			for (auto& obj : objList)
			{
				BallBase* ball = dynamic_cast<BallBase*>(obj.get());
				if (ball != nullptr)
				{
					ball->SetMoveSpeed(MaxBallMoveSpeed);
					ball->SetRotationSpeed(MaxBallRotationSpeed);
				}
			}

			//以降生成されるボールにも反映
			if (m_pBallGenerate != nullptr)
			{
				m_pBallGenerate->SetMoveSpeed(MaxBallMoveSpeed);
				m_pBallGenerate->SetRotationSpeed(MaxBallRotationSpeed);
			}
		}

		//エフェクト(緑)
		for (int i = 0; i < EffectCount; i++)
		{
			auto effect = std::make_shared<Effect>();
			effect->Init();
			Math::Vector3 move = { RandRange(EffectSpeed), RandRange(EffectSpeed), RandRange(EffectSpeed) };
			effect->SetParam(Math::Vector3(m_pos.x, m_pos.y + EffectAdjust, m_pos.z), move, EffectLifeSpan, EffectColorGreen);
			SceneManager::Instance().AddObject(effect);
		}
	}
	else  //ミス
	{
		KdAudioManager::Instance().Play("Asset/Sounds/Se/Miss.WAV", false);

		Score -= Subtraction;

		if (Score < 0)
		{
			Score = 0;
		}

		GoldCnt++;//ミスでもGoldCntは増やす

		const auto& objList = SceneManager::Instance().GetObjList();

		//エフェクト(赤)
		for (int i = 0; i < EffectCount; i++)
		{
			auto effect = std::make_shared<Effect>();
			effect->Init();
			Math::Vector3 move = { RandRange(EffectSpeed), RandRange(EffectSpeed), RandRange(EffectSpeed) };
			effect->SetParam(Math::Vector3(m_pos.x, m_pos.y + EffectAdjust, m_pos.z), move, EffectLifeSpan, EffectColorRed);
			SceneManager::Instance().AddObject(effect);
		}
	}
}

void Player::EndFever()
{
	FeverFlg = false;
	GoldCnt = 0;

	KdAudioManager::Instance().StopAllSound();

	//スピードを通常に戻す
	const auto& objList = SceneManager::Instance().GetObjList();
	for (auto& obj : objList)
	{
		BallBase* ball = dynamic_cast<BallBase*>(obj.get());
		if (ball) ball->SetMoveSpeed(NormalBallMoveSpeed);
		if (ball) ball->SetRotationSpeed(NormalBallRotationSpeed);
	}

	if (m_pBallGenerate)
	{
		m_pBallGenerate->SetMoveSpeed(NormalBallMoveSpeed);
		m_pBallGenerate->SetRotationSpeed(NormalBallRotationSpeed);
	}
}

void Player::UpdateCollider()
{
	m_pCollider = std::make_unique<KdCollider>();

	if (m_BoxType == BoxType::NormalBox)
	{
		m_pCollider->RegisterCollisionShape(
			"NormalBoxModelCollision",
			m_NormalBoxModel,
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
