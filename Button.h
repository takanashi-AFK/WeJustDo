#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	bool Finished(); // ButtonÇ™èIÇÌÇ¡ÇΩÇÁtrue
	void SetImage(std::string normal, std::string pushed);
	void SetPosition(int x, int y);
	void Push(bool pushed);
	bool MouseInArea(XMFLOAT3 mousePos);
private:
	int hImage;
	int hPush;
	bool pushed;
	XMFLOAT3 center;
	XMFLOAT3 size;
};