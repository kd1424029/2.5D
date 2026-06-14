#pragma once

#include "../KeyUiBase.h"

class KdCamera;

class ZUi : public KeyUiBase
{
public:

	ZUi() {}
	~ZUi() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

private:

	std::weak_ptr<KdCamera>   m_wpCamera;


	const float PosX = 6.7;
	const float PosY = 8.7;
};