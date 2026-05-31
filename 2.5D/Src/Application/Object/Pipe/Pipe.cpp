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

			RandomColor = rand() % 3 + 1; //1から3のランダムな整数を生成

			RandomPos = rand() % 3 + 1;

			if (RandomColor == 1)
			{
				m_State = PipeState::Red;
				m_color = { 1, 0, 0, 1 };
			}
			else if (RandomColor == 2)
			{
				m_State = PipeState::Blue;
				m_color = { 0, 0, 1, 1 };
			}
			else if (RandomColor == 3)
			{
				m_State = PipeState::Green;
				m_color = { 0, 1, 0, 1 };
			}

			break;

		case PipeState::Red:

			if (RandomPos == 1)
			{
				m_pos.x = SecondFromLeftPos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			else if (RandomPos == 2)
			{
				m_pos.x = MiddlePos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			else if (RandomPos == 3)
			{
				m_pos.x = FourthFromLeftPos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			
			break;
		case PipeState::Blue:

			if (RandomPos == 1)
			{
				m_pos.x = MiddlePos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			else if (RandomPos == 2)
			{
				m_pos.x = FourthFromLeftPos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			else if (RandomPos == 3)
			{
				m_pos.x = FifthFromLeftPos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			
			break;
		case PipeState::Green:

			if (RandomPos == 1)
			{
				m_pos.x = MaxLeftPos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}

			}
			else if (RandomPos == 2)
			{
				m_pos.x = SecondFromLeftPos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			else if (RandomPos == 3)
			{
				m_pos.x = MiddlePos;

				if (MoveUpFlg == false)
				{
					m_pos.y -= MoveSpeed;

					if (m_pos.y < MaxBottomPos)
					{
						m_pos.y = MaxBottomPos;

						MoveUpCount++;//MoveUpCountを足していく

						if (MoveUpCount >= 60.0f) //1秒経ったら
						{
							MoveUpFlg = true;
							MoveUpCount = 0;
						}
					}
				}

				if (MoveUpFlg == true)
				{
					m_pos.y += MoveSpeed;

					if (m_pos.y > 10.0f)
					{
						m_pos.y = 10.0f;

						m_State = PipeState::None;

						MoveUpFlg = false;
					}
				}
			}
			
			break;
	}


	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;  

}

void Pipe::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_PipeModel, m_mWorld, m_color);
}
