#include "Player.h"

//インクルード
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/Transition.h"
#include "Engine/Image.h"
#include "Engine/Debug.h"
#include "Engine/Camera.h"
#include "AudioManager.h"
#include "Engine/Audio.h"
#include "Engine/SceneManager.h"
#include "StartCount.h"
#include "FuelGauge.h"


//コンストラクタ
Player::Player(GameObject* _parent, string _modelFileName)
	:SolidObject(_parent,_modelFileName,"Player")
	,hDebugBox_(-1),pJet(nullptr),pState_(nullptr),hGroundModel_(0)
	,acceleration_(0),isAddGravity_(false),isMove_(false),speed_(0)
	,RandEffectData_(),DeadEffectData(),PlusOneEffectData()
{
	//プレイヤーの状態を「立ち状態」で初期化
	ASSIGN(pState_,new PlayerStateManager);
}

//初期化
void Player::ChildInitialize()
{
	//状態の初期化
	ASSIGN(pState_->playerState_, pState_->pStanding_);

	//モデルのロード-debug用
	ASSIGN(hDebugBox_, Model::Load("Models/defaultModel.fbx"));

	//位置の初期化
	SetPositionY(1.0f);
	SetRotateY(90);

	//初期状態の開始処理
	pState_->Enter(this);

	//各エフェクトの初期化
	{
		InitDeadEffect();
		InitRandEffect();
		InitPlusOneEffect();
		InitBombEffect();
		InitGetEffect();

		pJet = new PolyLine(0.4, 10);
		pJet->Load("Effects/Fire.png");
	}

	//ゲージの初期化
	pGauge_ = Instantiate<FuelGauge>(this);

	//前フレームの移動量初期化
	currentPos_.position_ = { 0, 0, 0 };



	//カメラの初期化
	Camera::SetPosition(transform_.position_.x + 5, transform_.position_.y + 3, -13.0f);
	Camera::SetTarget(transform_.position_.x + 5, transform_.position_.y + 3, 0.0f);
}
//更新
void Player::ChildUpdate()
{
	static float camX = 0;
	//かいだカメラ
	{
		static float camMoveY = defCamY;	//地面の下が見えないギリギリのライン
		static float camMoveZ = defCamZ;

		//カメラ座標Zの計算
		camMoveZ = CalcCamPositionZ(transform_);

		//カメラ座標Yの計算
		camMoveY = CalcCamPositionY(transform_);

		//カメラ移動
		Camera::SetPosition(transform_.position_.x + 5, camMoveY, camMoveZ);
		Camera::SetTarget(transform_.position_.x + 5, camMoveY - 0.5f, 0.0f);
	}
	
	
	StartCount pSt = (StartCount*)FindObject("StartCount");
	if (pSt.IsFinished())
	{
	if (Input::IsKeyDown(DIK_RETURN))
	{
		SetAcceleration(0);
		SetIsMove(false);
		bombEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z -2);
		int a = VFX::Start(bombEffectData);
		AudioManager::Play_BombSound();
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}
	}

	//Gauge
	pGauge_->SetFuel(Global::gFireWood / 5, maxfireWood_);


	//ゴールしたら...
	if (isGoal()) {
		//movie状態に移行する
		pState_->ChangeState(pState_->pMovie_, this);
	}

	//falseなら動作処理を行わずreturn
	if (!isMove_)return;

	//camX+= 0.05f;

	//ジェット時のエフェクト位置を調整
	{
		pJet->AddPosition(XMFLOAT3(
			transform_.position_.x - (PLAYER_MODEL_SIZE.x / 4),	//x
			transform_.position_.y - (PLAYER_MODEL_SIZE.x / 4),	//y
			transform_.position_.z));							//z
	}


	if (Input::IsKeyDown(DIK_RETURN))
	{
		SetIsMove(false);
		AudioManager::Play_BombSound(); 
		bombEffectData.position = XMFLOAT3(transform_.position_.x + 5, transform_.position_.y , 0.0f);
		int a = VFX::Start(bombEffectData);
		SceneManager* pScM = (SceneManager*)FindObject("SceneManager");
		pScM->ChangeScene(SCENE_ID_RESULT, TID_WHITEOUT);
	}

	//重力を加える
	AddGravity(&transform_);

	//地形(Stage)との判定時の処理
	TerrainInteraction();

	//状態ごとの更新(※StageRayCast()より後に処理するとバグる)
	pState_->Update(this);

	//ステージとの当たり判定
	//StageRayCast();

	RayNeo();
}

//開放
void Player::ChildRelease()
{
	SAFE_DELETE(pState_);
	pJet->Release();
}

//描画
void Player::ChildDraw()
{
	//debug-UnlitBoxDraw
	{
		/*Direct3D::SetShader(Direct3D::SHADER_UNLIT);
		Transform t_Box; t_Box.position_ = transform_.position_; t_Box.position_.y + 0.5f;
		Model::SetTransform(hBox_, t_Box);Model::Draw(hBox_);*/

	}
	
}

void Player::StageRayCast()
{
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//上方向
	{
		//UpRight
		RayCastData upDataRight; {
			//レイの開始地点を設定
			upDataRight.start = transform_.position_;
			upDataRight.start.x += ((PLAYER_MODEL_SIZE.x / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&upDataRight.dir, XMVectorSet(0, 1, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &upDataRight);
		}
		if (upDataRight.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
			//めり込み分戻す処理
			XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(upDataRight.dist),0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);

		}

		//Up+eft
		RayCastData upDataLeft; {
			//レイの開始地点を設定
			upDataLeft.start = transform_.position_;
			upDataLeft.start.x -= ((PLAYER_MODEL_SIZE.x / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&upDataLeft.dir, XMVectorSet(0, 1, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &upDataLeft);
		}
		if (upDataLeft.dist <= (PLAYER_MODEL_SIZE.y / 2)) {
			//めり込み分戻す処理
			XMVECTOR length = { 0,(PLAYER_MODEL_SIZE.y / 2) - std::abs(upDataLeft.dist),0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);

		}
	}

	//StandingState,RunningStateときのみ行うからState内で処理を行う
	//下方向
	{
		//downRight
		RayCastData downDataRight; {
			//レイの開始地点を設定
			downDataRight.start = transform_.position_;
			downDataRight.start.x += ((PLAYER_MODEL_SIZE.x / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&downDataRight.dir, XMVectorSet(0, -1, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &downDataRight);
		}
		if (downDataRight.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//状態遷移：->Standing
			pState_->ChangeState(pState_->pStanding_, this);
		}
		else
			IsAddGravity(true);

	}

	//左方向の当たり判定
	{
		//LeftTop
		RayCastData leftDataTop; {
			//レイの開始地点を設定
			leftDataTop.start = transform_.position_;
			leftDataTop.start.y += ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&leftDataTop.dir, XMVectorSet(-1, 0, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &leftDataTop);
		}
		if (leftDataTop.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分戻す処理
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(leftDataTop.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + length);
		}

		//LeftBottom
		RayCastData leftDataBottom; {
			//レイの開始地点を設定
			leftDataBottom.start = transform_.position_;
			leftDataBottom.start.y -= ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&leftDataBottom.dir, XMVectorSet(-1, 0, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &leftDataBottom);
		}
		if (leftDataBottom.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分戻す処理
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(leftDataBottom.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) + length);
		}
	}

	//右方向のあたり判定
	{
		//RightTop
		RayCastData rightDataTop; {
			//レイの開始地点を設定
			rightDataTop.start = transform_.position_;
			rightDataTop.start.y += ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&rightDataTop.dir, XMVectorSet(1, 0, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &rightDataTop);
		}
		if (rightDataTop.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分戻す処理
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(rightDataTop.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);
		}

		//RightBottom
		RayCastData rightDataBottom; {
			//レイの開始地点を設定
			rightDataBottom.start = transform_.position_;
			rightDataBottom.start.y -= ((PLAYER_MODEL_SIZE.y / 2) - 0.1f);

			//レイの発射方向を設定
			XMStoreFloat3(&rightDataBottom.dir, XMVectorSet(1, 0, 0, 0));

			//レイを発射
			Model::RayCast(hGroundModel_, &rightDataBottom);
		}
		if (rightDataBottom.dist <= (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分戻す処理
			XMVECTOR length = { (PLAYER_MODEL_SIZE.x / 2) - std::abs(rightDataBottom.dist),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - length);
		}
	}
}

void Player::AddGravity(Transform* _transform)
{
	//加えないならreturn
	if (!isAddGravity_)return;

	//重力を加える
	_transform->position_ = Transform::Float3Add(_transform->position_, VectorToFloat3((XMVectorSet(0, -1, 0, 0) / 10) * acceleration_));
	acceleration_ += GRAVITY_ADDITION;
}


void Player::OnWoodPickup(Stage* pS)
{
	//プレイヤーの位置が１or２なら...
	if (pS->AtItem(this, 1) || pS->AtItem(this,2)) {

		//薪を1本(*5)取得する
		Global::gFireWood += 5;

		//エフェクト
		PlusOneEffectData.position = (XMFLOAT3(transform_.position_.x - 0.5, transform_.position_.y + 0.5, 0));
		ItemGetEffectData.position = transform_.position_;
		VFX::Start(PlusOneEffectData);
		VFX::Start(ItemGetEffectData);

		AudioManager::Play_WoodSound();

		//その場所の薪を消して空気に変換
		pS->SetItem(round(transform_.position_.x), round(transform_.position_.y), 0);
	}
}

const float GOAL_POINT = 285.0f;

bool Player::isGoal()
{
	return transform_.position_.x >= GOAL_POINT;
}

void Player::TerrainInteraction()
{
	//ステージ情報を取得
	Stage* pS = (Stage*)(FindObject("Stage"));

	//薪を取得する
	OnWoodPickup(pS);

	//足場が泥の時
	if (pS->AtItem(this, 2))
	{
		//※うまく行かない(検討中)
	}
	else SetSpeed(0.1f);
}

void Player::PolyDraw()
{
	//ジェット状態の時、ポリラインを描画(ジェット噴射effect)
	if (pState_->playerState_ == pState_->pJet_)pJet->Draw();
}

void Player::SetDrawTransform()
{
	//シェーダーを設定
	Direct3D::SetShader(Direct3D::SHADER_3D);
	
	//描画位置を修正(ziro_move.fbxの足元の座標が{0,0,0}の為ずらす必要がある)
	Transform t_Draw; {
		t_Draw = transform_;
		t_Draw.position_.y -= 0.5f;
		t_Draw.scale_ = { 0.1f,0.1f,0.1f };
	}
	Model::SetTransform(hModel_, t_Draw);
}

void Player::InitDeadEffect()
{
	//エフェクト情報を設定
	DeadEffectData.textureFileName = "Effects/cloudA.png";
	DeadEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	DeadEffectData.delay = 0;
	DeadEffectData.number = 1;
	DeadEffectData.lifeTime = 60;
	DeadEffectData.gravity = -0.002f;
	DeadEffectData.direction = XMFLOAT3(0, 1, 0);
	DeadEffectData.directionRnd = XMFLOAT3(0, 0, 0);
	DeadEffectData.speed = 0.01f;
	DeadEffectData.speedRnd = 0.0;
	DeadEffectData.size = XMFLOAT2(1,10);
	DeadEffectData.sizeRnd = XMFLOAT2(0.4, 0.4);
	DeadEffectData.scale = XMFLOAT2(1.01, 1.01);
	DeadEffectData.color = XMFLOAT4(0, 0, 1, 1);
	DeadEffectData.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
}

void Player::InitBombEffect()
{
	bombEffectData.textureFileName = "Image/bomb.png";
	bombEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	bombEffectData.delay = 0;
	bombEffectData.number = 1;
	bombEffectData.lifeTime = 25;
	bombEffectData.speed = 0.05f;
	bombEffectData.speedRnd = 0.0;
	bombEffectData.size = XMFLOAT2(5,5);
	bombEffectData.scale = XMFLOAT2(1.01, 1.01);
	bombEffectData.color = XMFLOAT4(1, 0, 0, 1);

}

void Player::InitRandEffect()
{	
	//エフェクト情報を設定
	RandEffectData_.textureFileName = "Effects/RandSmoke2.png";
	RandEffectData_.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2,0);
	RandEffectData_.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	RandEffectData_.delay = 0;
	RandEffectData_.number = 1;
	RandEffectData_.lifeTime = 40;
	RandEffectData_.speed = 0.01f;
	RandEffectData_.speedRnd = 0.0;
	RandEffectData_.size = XMFLOAT2(1,0.5);
	RandEffectData_.scale = XMFLOAT2(1.01, 1.01);
	RandEffectData_.color = XMFLOAT4(1,1,1,1);
	RandEffectData_.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}

void Player::InitPlusOneEffect()
{
	PlusOneEffectData.textureFileName = "Effects/PlusOneR.png";
	PlusOneEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	PlusOneEffectData.delay = 0;
	PlusOneEffectData.number = 1;
	PlusOneEffectData.lifeTime = 25;
	PlusOneEffectData.speed = 0.05f;
	PlusOneEffectData.speedRnd = 0.0;
	PlusOneEffectData.size = XMFLOAT2(0.75, 0.75);
	PlusOneEffectData.scale = XMFLOAT2(1.01, 1.01);
	PlusOneEffectData.color = XMFLOAT4(1, 1, 1, 1);
}

void Player::InitGetEffect()
{
	ItemGetEffectData.textureFileName = "Effects/kira.png";
	ItemGetEffectData.position = XMFLOAT3(transform_.position_.x, transform_.position_.y - 0.2, 0);
	ItemGetEffectData.positionRnd = XMFLOAT3(0.1, 0, 0.1);
	ItemGetEffectData.delay = 0;
	ItemGetEffectData.number = 1;
	ItemGetEffectData.lifeTime = 40;
	ItemGetEffectData.speed = 0.01f;
	ItemGetEffectData.speedRnd = 0.0;
	ItemGetEffectData.size = XMFLOAT2(1, 0.5);
	ItemGetEffectData.scale = XMFLOAT2(1.01, 1.01);
	ItemGetEffectData.color = XMFLOAT4(1, 1, 1, 1);
	ItemGetEffectData.deltaColor = XMFLOAT4(0, 0, 0, -0.1);
}

float Player::CalcCamPositionY(Transform _plPos)
{
	float result = 0.0f;
	//Player と床の平均をとる。で、平均が、デフォルト設定値以上なら動かす
	if ((_plPos.position_.y + stageBottom / 2) >= defCamY)
	{
		//Player と床の平均がカメラの最大高度以上ならば
		if (_plPos.position_.y + stageBottom / 2 >= maxCamY)
		{
			//カメラ高度は最大に
			return (maxCamY) - 2;//なぜか2を引かないとガクガクする。
		}
		else
		{
			//そうでなければPlayerと床の平均値を高さに
			result = ((_plPos.position_.y + stageBottom) / 2 ) + 2;//なぜか2を足さないとガクガクする。
			return(result);
		}
	}
	else{//平均がデフォルト位置よりも小さかった時はデフォルト値を返す
		return (defCamY);
	}
}

float Player::CalcCamPositionZ(Transform _plPos)
{
	float result = 0.0f;
	//Playerの座標がカメラのデフォルトY座標以上だった時、その分カメラを引かせる
	if (_plPos.position_.y >= defCamY)
	{
		result = (camZBottom - _plPos.position_.y) + defCamZ;
		return (result);

	}
	else//デフォルトY座標未満ならデフォルトY座標をそのまま使う
	{
		result = defCamZ;
		return (result);
	}
}

void Player::RayNeo()
{
	ASSIGN(hGroundModel_, dynamic_cast<Stage*>(FindObject("Stage"))->GetStageModelHandle(m_Ground));

	//上方向
	{
		RayCastData upDataL; {
			//当たっているか確認
			upDataL.start = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2), 
									 transform_.position_.y + (PLAYER_MODEL_SIZE.y / 2), 
									 transform_.position_.z);
			XMStoreFloat3(&upDataL.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_, &upDataL);
		}
		RayCastData upDataR; {
			//当たっているか確認
			upDataR.start = XMFLOAT3(transform_.position_.x + (PLAYER_MODEL_SIZE.x / 2), 
									 transform_.position_.y + (PLAYER_MODEL_SIZE.y / 2),
									 transform_.position_.z);
			XMStoreFloat3(&upDataR.dir, XMVectorSet(0, 1, 0, 0));
			Model::RayCast(hGroundModel_, &upDataR);
		}
		//レイの長さが1.0以下だったら...
		if (upDataR.dist < (PLAYER_MODEL_SIZE.y / 2)&& upDataL.dist < (PLAYER_MODEL_SIZE.y / 2)) {
			//めり込み分、位置を戻す
			XMVECTOR length = { 0, (PLAYER_MODEL_SIZE.y / 2) + ((upDataR.dist + upDataL.dist)/2),0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(0, 1, 0, 0) - length));
			SetAcceleration(2);
		}
	}

	//StandingState,RunningStateときのみ行うからState内で処理を行う
	//下方向のあたり判定
	{
		RayCastData downDataL; {
			//当たっているか確認
			downDataL.start = XMFLOAT3(transform_.position_.x,
								       transform_.position_.y ,
									   transform_.position_.z);
			XMStoreFloat3(&downDataL.dir, XMVectorSet(0, -1, 0, 0));
			Model::RayCast(hGroundModel_, &downDataL);
			downData_ = downDataL;
		}
		if (downDataL.dist < (PLAYER_MODEL_SIZE.y / 2) ) {
			//状態を"Standing"に変更
			pState_->ChangeState(pState_->pStanding_, this);
		}
		else
			isAddGravity_ = true;
	}
	
	//左方向の当たり判定
	{

		RayCastData leftDataTop; {
			leftDataTop.start = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2), 
										 transform_.position_.y + (PLAYER_MODEL_SIZE.x / 2), 
										 transform_.position_.z);
			XMStoreFloat3(&leftDataTop.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftDataTop);
		}
		RayCastData leftDataBottom; {
			leftDataBottom.start = XMFLOAT3(transform_.position_.x - (PLAYER_MODEL_SIZE.x / 2), 
											transform_.position_.y - (PLAYER_MODEL_SIZE.x / 2),
											transform_.position_.z);
			XMStoreFloat3(&leftDataBottom.dir, XMVectorSet(-1, 0, 0, 0));
			Model::RayCast(hGroundModel_, &leftDataBottom);
		}
		if (leftDataBottom.dist < (PLAYER_MODEL_SIZE.x / 2)&& leftDataTop.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分、位置を戻す
			XMVECTOR length = { (((-leftDataBottom.dist + -leftDataTop.dist)/2 - (PLAYER_MODEL_SIZE.x / 2))-0.1),0,0};
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(-1, 0, 0, 0) - length));
		}
	}

		//右方向のあたり判定
	{
		RayCastData rightDataTop; {
			//当たっているかを確認
			rightDataTop.start = XMFLOAT3(transform_.position_.x + (PLAYER_MODEL_SIZE.x / 2),
										  transform_.position_.y + (PLAYER_MODEL_SIZE.x / 2),
										  transform_.position_.z);					//発射位置の指定
			XMStoreFloat3(&rightDataTop.dir, XMVectorSet(1, 0, 0, 0));	//発射方向の指定
			Model::RayCast(hGroundModel_, &rightDataTop);				//レイを発射
		}
		RayCastData rightDataBottom; {
			//当たっているかを確認
			rightDataBottom.start = XMFLOAT3(transform_.position_.x + (PLAYER_MODEL_SIZE.x / 2),
											 transform_.position_.y - (PLAYER_MODEL_SIZE.x / 2), 
											 transform_.position_.z);				//発射位置の指定
			XMStoreFloat3(&rightDataBottom.dir, XMVectorSet(1, 0, 0, 0));	//発射方向の指定
			Model::RayCast(hGroundModel_, &rightDataBottom);				//レイを発射
		}
		//レイの長さが1.0以下だったら...
		if (rightDataBottom.dist < (PLAYER_MODEL_SIZE.x / 2)&& rightDataTop.dist < (PLAYER_MODEL_SIZE.x / 2)) {
			//めり込み分、位置を戻す
			//戻し分をちょっと増やすために+0.1する
			//0.1以上になると、角にスナップするようになってしまう
			XMVECTOR length = { ((rightDataBottom.dist +rightDataTop.dist)/2 + (PLAYER_MODEL_SIZE.x / 2)+0.1),0,0 };
			XMStoreFloat3(&transform_.position_, XMLoadFloat3(&transform_.position_) - (XMVectorSet(1, 0, 0, 0) - length));
		}
	}
}
