#include "Pipe.h"

void Pipe::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_PipeModel = std::make_shared<KdModelData>();
	m_PipeModel->Load("Asset/Models/Object/Pipe/Pipe.gltf");

	m_pos = { -0.1,10,0 };

	m_color = { 0,0,0,1 };

	MoveUpFlg = false;

	MoveUpCount = 0;

	BeforeColor = 0;
	BeforePosX = 0;

	NextX = 0;

	ReachBottomFlg = false;

	SpikeReachBottomFlg = false;

	srand((unsigned)time(NULL)); //ランダム初期化
}

void Pipe::PreUpdate()
{

}

void Pipe::Update()
{
	switch (m_State)
	{
	case PipeState::None:
		
		NextX = 0.0f; //次のX座標入れる変数

		do //位置をランダムで決める
		{
			RandomPos = rand() % 3 + 1;//1～3をランダムで決める

			SpikeRandomPos = rand() % 4 + 1;//針用

			do //色をランダムで決める（前回と違う色になるまでループ）
			{
				RandomColor = rand() % 4 + 1;
			}
			while (RandomColor == BeforeColor);

			//色と位置番号の組み合わせとX座標の代入
			if (RandomColor == 1) //赤
			{
				if (RandomPos == 1)
				{
					NextX = SecondFromLeftPos;
				}
				else if (RandomPos == 2)
				{
					NextX = MiddlePos;
				}
				else if (RandomPos == 3)
				{
					NextX = FourthFromLeftPos;
				}
			}
			else if (RandomColor == 2) //青
			{
				if (RandomPos == 1)
				{
					NextX = MiddlePos;
				}
				else if (RandomPos == 2)
				{
					NextX = FourthFromLeftPos;
				}
				else if (RandomPos == 3)
				{
					NextX = FifthFromLeftPos;
				}
			}
			else if (RandomColor == 3) //緑
			{
				if (RandomPos == 1)
				{
					NextX = MaxLeftPos;
				}
				else if (RandomPos == 2)
				{
					NextX = SecondFromLeftPos;
				}
				else if (RandomPos == 3)
				{
					NextX = MiddlePos;
				}
			}			
			else if (RandomColor == 4) //針用
			{
				if (SpikeRandomPos == 1)
				{
					NextX = MaxLeftPos;
				}
				else if (SpikeRandomPos == 2)
				{
					NextX = SecondFromLeftPos;
				}
				else if (SpikeRandomPos == 3)
				{
					NextX = FourthFromLeftPos;
				}
				else if (SpikeRandomPos == 4)
				{
					NextX = FifthFromLeftPos;
				}
			}
		} 
		while (NextX == BeforePosX);//もし計算した結果が前回のX座標と同じならもう一度最初から抽選し直し！

		BeforeColor = RandomColor;//被らない色が見つかったらそれを今回の値として確定し保存する

		BeforePosX = NextX;

		//色に反映
		if (RandomColor == 1)
		{
			m_State = PipeState::Red;   m_color = { 1, 0, 0, 1 }; 
		}
		if (RandomColor == 2)
		{
			m_State = PipeState::Blue;  m_color = { 0, 0, 1, 1 }; 
		}
		if (RandomColor == 3) 
		{ 
			m_State = PipeState::Green; m_color = { 0, 1, 0, 1 }; 
		}
		if (RandomColor == 4)
		{
			m_State = PipeState::Spike; m_color = { 1, 0, 1, 1 };
		}

		m_pos.x = NextX; // 確定したX座標を代入

		break;
	}

	//共通で行う移動処理
	if (m_State != PipeState::None && m_State != PipeState::Spike)
	{
		if (MoveUpFlg == false)
		{
			m_pos.y -= MoveSpeed;
			if (m_pos.y < MaxBottomPos)
			{
				m_pos.y = MaxBottomPos;
				if (!ReachBottomFlg && MoveUpCount == 0)
				{
					ReachBottomFlg = true;
				}

				MoveUpCount++; // カウントアップ
				if (MoveUpCount >= MaxCount) // 1秒経ったら
				{
					MoveUpFlg = true;
					MoveUpCount = 0;
				}
			}
		}
		else //MoveUpFlg == true 
		{
			ReachBottomFlg = false;
			m_pos.y += MoveSpeed;
			if (m_pos.y > MaxTopPos)
			{
				m_pos.y = MaxTopPos;
				m_State = PipeState::None; // 状態をリセットして次のランダムへ
				MoveUpFlg = false;
			}
		}
	}

	if (m_State != PipeState::None && m_State == PipeState::Spike)
	{
		if (MoveUpFlg == false)
		{
			m_pos.y -= MoveSpeed;
			if (m_pos.y < MaxBottomPos)
			{
				m_pos.y = MaxBottomPos;
				if (!SpikeReachBottomFlg && MoveUpCount == 0)
				{
					SpikeReachBottomFlg = true;
				}

				MoveUpCount++; // カウントアップ
				if (MoveUpCount >= MaxCount) // 1秒経ったら
				{
					MoveUpFlg = true;
					MoveUpCount = 0;
				}
			}
		}
		else //MoveUpFlg == true 
		{
			SpikeReachBottomFlg = false;
			m_pos.y += MoveSpeed;
			if (m_pos.y > MaxTopPos)
			{
				m_pos.y = MaxTopPos;
				m_State = PipeState::None; // 状態をリセットして次のランダムへ
				MoveUpFlg = false;
			}
		}
	}


	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;  

}

void Pipe::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_PipeModel, m_mWorld, m_color);
}
