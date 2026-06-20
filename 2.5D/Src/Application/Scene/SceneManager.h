#pragma once

class BaseScene;

class SceneManager : public KdGameObject
{
public:

	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
		Result
	};

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// 次のシーンをセット (次のフレームから切り替わる)
	void SetNextScene(SceneType _nextScene)
	{
		if (m_fadeState != FadeState::None)
		{
			return;
		}

		m_nextSceneType = _nextScene;
	}

	// 現在のシーンのオブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();

	// 現在のシーンにオブジェクトを追加
	void AddObject(const std::shared_ptr<KdGameObject>& _obj);

	// 最終スコアを保存する（PlayScene終了時、ResultSceneへ遷移する前に呼ぶ）
	void SetFinalScore(unsigned long _score) { m_finalScore = _score; }

	// 保存しておいた最終スコアを取得する（ResultSceneで使用）
	unsigned long GetFinalScore() const { return m_finalScore; }

	void SetIsNewRecord(bool isNewRecord) { IsNewRecord = isNewRecord; }

	bool GetIsNewRecord() const { return IsNewRecord; }

private:

	//暗転の状態
	enum class FadeState
	{
		None,     //フェードしていない通常時
		FadeOut,  //画面を暗くしていく
		FadeIn    //暗い画面から明るくしていく
	};

	// マネージャーの初期化
	// インスタンス生成(アプリ起動)時にコンストラクタで自動実行
	void Init()
	{
		// 開始シーンに切り替え
		ChangeScene(m_currentSceneType);
	}

	// シーン切り替え関数
	void ChangeScene(SceneType _sceneType);

	//フェードの状態を更新する
	void UpdateFade();

	// 現在のシーンのインスタンスを保持しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;

	// 現在のシーンの種類を保持している変数
	SceneType m_currentSceneType = SceneType::Title;

	// 次のシーンの種類を保持している変数
	SceneType m_nextSceneType = m_currentSceneType;

	FadeState m_fadeState = FadeState::None;

	float m_fadeAlpha = 0.0f;   //暗転画像の透明度

	const float FadeSpeed = 0.04f;  //アルファ変化量

	const int ScreenWidth = 1280;

	const int ScreenHeight = 720;

	// PlayScene終了時のスコアを保持しておき、ResultSceneで表示するために使う
	unsigned long m_finalScore = 0;

	bool IsNewRecord = false;

private:

	SceneManager() { Init(); }
	~SceneManager() {}

public:

	// シングルトンパターン
	// 常に存在する && 必ず1つしか存在しない(1つしか存在出来ない)
	// どこからでもアクセスが可能で便利だが
	// 何でもかんでもシングルトンという思考はNG
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};
