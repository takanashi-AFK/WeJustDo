#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Text;

class Timer : public GameObject
{
private:
	int frame_;	//時間(フレーム)
	bool limitActive_;//カウントダウン実行中かどうか
	bool countActive_;//カウントアップ実行中かどうか
	
	Text* pText_;	//テキスト
	int hTimerFlame_;	//画像

	int drawPosX_;//描画位置X
	int drawPosY_;//描画位置Y
	float drawSize_;//描画サイズ

	bool isDraw_;	//描画フラグ
public:
	//コンストラクタ
	Timer(GameObject* obj);
	
	//継承{初期化,更新,描画,開放}
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Release()override;

	/// <summary>
	/// タイマーを開始
	/// </summary>
	/// <param name="_flag">true(カウントダウン),false(カウントアップ)</param>
	void Start(bool _flag);

	/// <summary>
	/// タイマーを停止
	/// </summary>
	/// <param name="_flag">true(カウントダウン),false(カウントアップ)</param>
	void Stop(bool _flag);
	
	/// <summary>
	/// カウントダウンが終了したかどうかを返す関数
	/// </summary>
	/// <returns>終了していたらtrue</returns>
	bool IsFinished();

	/// <summary>
	/// カウントアップが終了したかどうかを返す関数
	/// </summary>
	/// <param name="_s">終了時間</param>
	/// <returns>終了していたらtrue</returns>
	bool IsFinished(int _s);


public:
	//取得：タイマーの動作状態
	bool isMove() { return limitActive_ || countActive_; }

	//取得：時間(フレーム)
	int GetTime_Frame() { return frame_; }

	//取得：時間(秒)
	int GetTime_Seconds() { return frame_ / 60; }

	//設定：時間(フレーム)
	void SetTime_Frame(int _f) { frame_ = _f; }

	//設定：時間(秒)
	void SetTime_Seconds(int _s) { frame_ = _s * 60; }

	//設定：描画位置
	void SetDrawPosition(int _x, int _y) { drawPosX_ = _x; drawPosY_ = _y; }
	
	//設定：描画位置(x座標)
	void SetDrawPositionX(int _x) { drawPosX_ = _x; }

	//設定：描画位置(y座標)
	void SetDrawPositionY(int _y) { drawPosX_ = _y; }

	//取得：描画サイズ
	float GetDrawSize() { return drawSize_; }

	//設定：描画サイズ
	void SetDrawSize(float _size);

	//設定：タイマーを表示するかどうか
	void IsDraw(bool _flag) { isDraw_ = _flag; }

};