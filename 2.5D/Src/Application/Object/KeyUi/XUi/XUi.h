#pragma once

#include "../KeyUiBase.h"

class KdCamera;

class XUi : public KeyUiBase
{
public:

	XUi() {}
	~XUi() {}

	void Init() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

private:

	std::weak_ptr<KdCamera>   m_wpCamera;


	const float PosX = 1.7;
	const float PosY = 1.23;
};