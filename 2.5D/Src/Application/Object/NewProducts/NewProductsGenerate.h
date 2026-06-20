#pragma once

#include "NewProductsBase.h"

class BallGenerate;

class Player;

class NewProductsGenerate
{
public:

	NewProductsGenerate();
	~NewProductsGenerate() {}

	std::shared_ptr<NewProductsBase> Generate();

	//フィーバー終了時に保留していた新商品ラベルがあれば生成する（毎フレーム呼ぶ）
	std::shared_ptr<NewProductsBase> CheckPendingGenerate();

	//フィーバー用
	std::shared_ptr<NewProductsBase> FeverGenerate();

	void SetTarget(BallGenerate* ballgenerate) { m_BallGenerate = ballgenerate; }

	void SetPlayer(Player* player) { m_Player = player; }

private:

	//ウェーブレベルに応じた新商品ラベルを生成する共通処理
	std::shared_ptr<NewProductsBase> CreateProductByWaveLevel(int waveLevel);

	std::shared_ptr<KdTexture> m_DefectiveProduct;

	std::shared_ptr<KdTexture> m_NewProductBasketBall;

	std::shared_ptr<KdTexture> m_NewProductVolleyBall;

	std::shared_ptr<KdTexture> m_NewFeverBall;

	BallGenerate* m_BallGenerate = nullptr;

	Player* m_Player = nullptr;

	//フィーバー中に出せなかったラベルを保留するための情報
	bool m_IsPending = false;

	bool m_PrevFeverFlg = false;

	int m_PendingWaveLevel = 0;

};