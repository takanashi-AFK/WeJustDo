#include "Transform.h"



Transform::Transform(): pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
	
}


Transform::~Transform()
{
}

void Transform::Calclation()
{
	//ÚŽsń
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//ń]sń
	XMMATRIX rotateX, rotateY, rotateZ;

	//XYZ˛đSÉń]ˇé
	rotateX = XMMatrixRotationAxis(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(rotate_.y));	
	rotateZ = XMMatrixRotationAxis(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), XMConvertToRadians(rotate_.z));
	//rotateAny = XMMatrixRotationAxis(axis_, XMConvertToRadians(angle_));

	matRotate_ = rotateZ * rotateX * rotateY;

	//gĺkŹ
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	if (pParent_)
	{
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}

XMMATRIX Transform::GetParentWorldMatrix()
{
	if (!pParent_) return XMMatrixIdentity();
	return pParent_->GetWorldMatrix();
}

