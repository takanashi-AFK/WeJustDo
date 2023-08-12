#include "PlayerObject.h"
#include "Engine/Model.h"
using namespace std;

//jsonヘッダーのインクルード
#include "Engine/json.hpp"
using json = nlohmann::json;//jsonデータインスタンスを格納

//ファイルストリームをインクルード
#include <fstream>


PlayerObject::PlayerObject(GameObject* parent)
	:GameObject(parent,"PlayerObject"),hModel_(-1)
{
}

void PlayerObject::Initialize()
{
	//モデルのロード
	hModel_ = Model::Load("DebugCollision/BoxCollider.fbx");
	assert(hModel_ <= 0);

	SavePosition(transform_);
}

void PlayerObject::Update()
{
}

void PlayerObject::Draw()
{
	//モデルの描画
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void PlayerObject::Release()
{
}

void PlayerObject::SavePosition(Transform& transform)
{
	//ファイル名を定義
	char fileName[MAX_PATH] = "無題.json";

	//書き込み用のjsonオブジェクトを定義
	json json_object;

	//Player
	json_object["Player"]["Position"] = { transform.position_.x,transform.position_.y,transform.position_.z };
	json_object["Player"]["Scale"] = { transform.scale_.x,transform.scale_.y,transform.scale_.z };

	//実験用１
	json_object["Enemy"]["Position"] = { transform.position_.x+2,transform.position_.y,transform.position_.z };
	json_object["Enemy"]["Scale"] = { transform.scale_.x+2,transform.scale_.y,transform.scale_.z };

	//実験用２
	json_object["Chara1"]["Position"] = { transform.position_.x + 2,transform.position_.y,transform.position_.z };
	json_object["Chara1"]["Scale"] = { transform.scale_.x + 2,transform.scale_.y,transform.scale_.z };

	//書き込み
	std::ofstream output_file(fileName);
	output_file << json_object;
	output_file.close();

}

