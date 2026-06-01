#pragma once

class Pipe;

class BallBase : public KdGameObject
{
public:
	BallBase() {}
	~BallBase() override {}

	// InitやDrawLitは共通化できる
	void Init() override;

	void PreUpdate() override;
	
	void DrawLit() override;

	//ゲッター
	bool IsAlive() const { return AliveFlg; }

	//セッター
	void SetPipe(Pipe* pipe) { m_Pipe = pipe; }

	void Destroy() //外部や自身から消滅させるための関数
	{
		m_isExpired = true;
	}   

protected:

	virtual void ChildClassInit() = 0; //純粋仮想関数にして子クラスでそれぞれの初期化をさせる

	std::shared_ptr<KdModelData> m_BallModel = nullptr;

	Math::Matrix TransMat = Math::Matrix::Identity;

	Math::Matrix RotationXMat = Math::Matrix::Identity;

	Pipe* m_Pipe = nullptr;

	float RotationX;

	bool AliveFlg = true;
};