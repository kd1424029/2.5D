#pragma once

#include "../BoxUiBase.h"

class KdCamera;

class TrashBoxUi : public BoxUiBase
{
public:

	TrashBoxUi() {}
	~TrashBoxUi() {}

	void Init() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

private:

	std::weak_ptr<KdCamera>   m_wpCamera;

	const float PosX = 50;
	const float PosY = -290;
};