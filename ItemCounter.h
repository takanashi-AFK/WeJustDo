#pragma once
#include "Engine/GameObject.h"

//�O�v�錾
class Text;

class ItemCounter : public GameObject
{
	int hPict_;
	Text* pText_;
public:
	//�R���X�g���N�^
	ItemCounter(GameObject* parent);

	//�p��{������,�X�V,�`��,�J��}
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

