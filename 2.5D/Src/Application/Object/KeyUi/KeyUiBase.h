#pragma once

class KeyUiBase : public KdGameObject
{
public:

	KeyUiBase() {}
	~KeyUiBase() {}

	void Init() override;

	void DrawSprite() override;

private:

	

protected:

	std::shared_ptr<KdTexture> m_KeyUi;

	Math::Vector2 m_pos;

	
};