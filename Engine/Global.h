#pragma once
#include "Direct3D.h"

using namespace std;

// �J��		////////////////////

//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// ������	////////////////////

//�����ŏ�����
#define ASSIGN(p,t){ p = t;}

//�O�ŏ�����
#define ZERO_ASSIGN(p){p = 0;}

//�P�ŏ�����
#define ONE_ASSIGN(p){p = 1;}

