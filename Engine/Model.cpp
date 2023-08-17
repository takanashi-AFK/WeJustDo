#include "Global.h"
#include "Model.h"
#include <algorithm> // For std::sort

//3Dモデル（FBXファイル）を管理する
namespace Model
{
	//ロード済みのモデルデータ一覧
	std::vector<ModelData*>	_datas;

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//モデルをロード
	int Load(std::string fileName)
	{
			ModelData* pData = new ModelData;


			//開いたファイル一覧から同じファイル名のものが無いか探す
			bool isExist = false;
			for (int i = 0; i < _datas.size(); i++)
			{
				//すでに開いている場合
				if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
				{
					pData->pFbx = _datas[i]->pFbx;
					isExist = true;
					break;
				}
			}

			//新たにファイルを開く
			if (isExist == false)
			{
				pData->pFbx = new Fbx;
				if (FAILED(pData->pFbx->Load(fileName)))
				{
					//開けなかった
					SAFE_DELETE(pData->pFbx);
					SAFE_DELETE(pData);
					return -1;
				}

				//無事開けた
				pData->fileName = fileName;
			}

			//使ってない番号が無いか探す
			for (int i = 0; i < _datas.size(); i++)
			{
				if (_datas[i] == nullptr)
				{
					_datas[i] = pData;
					return i;
				}
			}

			//新たに追加
			_datas.push_back(pData);
			return (int)_datas.size() - 1;
	}



	//描画
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//アニメーションを進める
		_datas[handle]->nowFrame += _datas[handle]->animSpeed;

		//最後までアニメーションしたら戻す
		if (_datas[handle]->nowFrame > (float)_datas[handle]->endFrame)
			_datas[handle]->nowFrame = (float)_datas[handle]->startFrame;



		if (_datas[handle]->pFbx)
		{
			_datas[handle]->pFbx->Draw(_datas[handle]->transform, (int)_datas[handle]->nowFrame);
		}
	}


	//任意のモデルを開放
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//同じモデルを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && i != handle && _datas[i]->pFbx == _datas[handle]->pFbx)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false )
		{
			SAFE_DELETE(_datas[handle]->pFbx);
		}


		SAFE_DELETE(_datas[handle]);
	}


	//全てのモデルを解放
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] != nullptr)
			{
				Release(i);
			}
		}
		_datas.clear();
	}


	//アニメーションのフレーム数をセット
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
	{
		_datas[handle]->SetAnimFrame(startFrame, endFrame, animSpeed);
	}


	//現在のアニメーションのフレームを取得
	int GetAnimFrame(int handle)
	{
		return (int)_datas[handle]->nowFrame;
	}


	//任意のボーンの位置を取得
	XMFLOAT3 GetBonePosition(int handle, std::string boneName)
	{
		XMFLOAT3 pos = _datas[handle]->pFbx->GetBonePosition(boneName);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _datas[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform & transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->transform = transform;
	}

	//レイキャスト判定を設定
	void SetRayFlag(int handle, bool flag)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->isRay = flag;
	}

	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		return _datas[handle]->transform.GetWorldMatrix();
	}


	//レイキャスト（レイを飛ばして当たり判定）
	void RayCast(int handle, RayCastData *data)
	{
		RayCastData tmp;
		{
			tmp.start = data->start;
			tmp.dir = data->dir;
			tmp.normal = data->normal;
			tmp.hit = false;
		};

		XMFLOAT3 target = Transform::Float3Add(data->start, data->dir);
		XMMATRIX matInv = XMMatrixInverse(nullptr, _datas[handle]->transform.GetWorldMatrix());
		XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
		XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
		XMVECTOR vecDir = XMVector3Normalize(vecTarget - vecStart);

		XMStoreFloat3(&data->start, vecStart);
		XMStoreFloat3(&data->dir, vecDir);

		_datas[handle]->pFbx->RayCast(data);

		data->start = tmp.start;
		data->dir = tmp.dir;
		data->normal = data->normal;
	}

	// distの昇順でソートするための比較関数
	bool CompareByDist(const RayCastData& a, const RayCastData& b)
	{
		return a.dist < b.dist;
	}

	// 一番distが近いモノレイキャストデータを取得
	RayCastData GetNeardistRayData(RayCastData data)
	{
		//ヒットしたレイデータをリストとして取得
		std::vector<RayCastData> hitList;
		for (int i = 0; i < _datas.size(); ++i) {
			if (_datas[i]->isRay) {
				RayCast(i, &data);
				if (data.hit) {
					hitList.push_back(data);
				}
			}
		}

		//dist順に昇順ソート
		if (hitList.empty()) {
			std::sort(hitList.begin(), hitList.end(), CompareByDist);
		}

		//ソートされたリストの先頭要素を返す（もしくは、必要に応じて返り値を調整）
		if (!hitList.empty()) {
			return hitList[0];
		}
		else {
			// ヒットしなかった場合の適切な処理を行う
			// 例: ヒットしなかったことを示す適当なRayCastDataを作成して返す
			return data;
		}
	}

}