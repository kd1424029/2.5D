#pragma once

#include "NewProductsBase.h"
#include <queue>

class BallGenerate;
class Player;

class NewProductsGenerate
{
public:

	NewProductsGenerate();
	~NewProductsGenerate() {}

	// 要求をキューに積む関数
	void Generate();

	// フィーバー終了時に保留していた新商品ラベルがあれば要求をキューに積む（毎フレーム呼ぶ）
	void CheckPendingGenerate();

	// フィーバー用の要求をキューに積む
	void FeverGenerate();

	// 毎フレーム呼ぶ。間隔を空けてキューから1個だけ生成して返す（無ければnullptr）
	std::shared_ptr<NewProductsBase> Update();

	void SetTarget(BallGenerate* ballgenerate) { m_BallGenerate = ballgenerate; }
	void SetPlayer(Player* player) { m_Player = player; }

private:

	// ボールタイプ（BallType）に応じた新商品ラベルを生成する共通処理
	std::shared_ptr<NewProductsBase> CreateProductByBallType(int ballType);

	// どの種類のラベルを生成する要求かを表す
	enum class ProductRequestType
	{
		Wave,	// ウェーブ変化（or保留分）の商品ラベル
		Fever	// フィーバー用ラベル
	};

	struct ProductRequest
	{
		ProductRequestType type;
		int ballType = 0; // typeがWaveの時のみ使用
	};

	std::shared_ptr<KdTexture> m_DefectiveProduct;
	std::shared_ptr<KdTexture> m_NewProductBasketBall;
	std::shared_ptr<KdTexture> m_NewProductVolleyBall;
	std::shared_ptr<KdTexture> m_NewFeverBall;

	BallGenerate* m_BallGenerate = nullptr;
	Player* m_Player = nullptr;

	std::queue<ProductRequest> m_RequestQueue;

	int m_IntervalTimer = 0;

	// 表示間隔（フレーム数）
	const int kDisplayInterval = 150;

	// 【修正】フィーバー中に新商品通知が複数回来ても全て保留できるようキュー化
	// （bool m_HasPending / int m_PendingBallType は廃止）
	std::queue<int> m_PendingBallTypes;
};