#pragma once

#include "../BoxUiBase.h"

class KdCamera;

class NormalBoxUi : public BoxUiBase
{
public:

	NormalBoxUi() {}
	~NormalBoxUi() {}

	void Init() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

private:

	std::weak_ptr<KdCamera>   m_wpCamera;

	const float PosX = 0.58;
};