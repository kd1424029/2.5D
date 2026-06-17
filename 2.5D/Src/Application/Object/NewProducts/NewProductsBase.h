#pragma once

enum Label
{
	Label_DefectiveProduct,
	Label_NewProductBasket,
	Label_NewProductVolley,
};

class NewProductsBase : public KdGameObject
{
public:

	NewProductsBase() {}
	~NewProductsBase() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

	void SetModel(std::shared_ptr<KdTexture> texture) { m_NewProducts = texture; }

private:

	Math::Vector3 m_pos = { -1000 , 150, 0 };

	const float MoveSpeed = 5; 

	const float MaxPosX = 1000;

protected:

	std::shared_ptr<KdTexture> m_NewProducts;

	Label BallLabel;

};