#pragma once
#include "Direct3D.h"

using namespace std;

// 開放		////////////////////

//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

// 初期化	////////////////////

//引数で初期化
#define ASSIGN(p,t){ p = t;}

//０で初期化
#define ZERO_ASSIGN(p){p = 0;}

//１で初期化
#define ONE_ASSIGN(p){p = 1;}

