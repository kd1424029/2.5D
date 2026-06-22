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

	//以下3つは即生成ではなく「要求をキューに積むだけ」になる
	void Generate();

	//フィーバー終了時に保留していた新商品ラベルがあれば要求をキューに積む（毎フレーム呼ぶ）
	void CheckPendingGenerate();

	//フィーバー用の要求をキューに積む
	void FeverGenerate();

	//毎フレーム呼ぶ。間隔を空けてキューから1個だけ生成して返す（無ければnullptr）
	std::shared_ptr<NewProductsBase> Update();

	void SetTarget(BallGenerate* ballgenerate) { m_BallGenerate = ballgenerate; }

	void SetPlayer(Player* player) { m_Player = player; }

private:

	//ウェーブレベルに応じた新商品ラベルを生成する共通処理
	std::shared_ptr<NewProductsBase> CreateProductByWaveLevel(int waveLevel);

	//どの種類のラベルを生成する要求かを表す
	enum class ProductRequestType
	{
		Wave,	//ウェーブ変化（or保留分）の商品ラベル
		Fever	//フィーバー用ラベル
	};

	struct ProductRequest
	{
		ProductRequestType type;
		int waveLevel = 0; //typeがWaveの時のみ使用
	};

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

	//生成待ちの要求キュー
	std::queue<ProductRequest> m_RequestQueue;

	//次の1個を生成するまでの残りフレーム数
	int m_IntervalTimer = 0;

	//ラベル同士を出す間隔(フレーム数)
	static constexpr int kDisplayInterval = 150;

};