#pragma once

#include "../BoxUiBase.h"

class KdCamera;

class SoccerBallUi : public BoxUiBase
{
public:

	SoccerBallUi() {}
	~SoccerBallUi() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;

	void SetCamera(std::shared_ptr<KdCamera> camera) { m_wpCamera = camera; }

private:

	std::weak_ptr<KdCamera>   m_wpCamera;

};