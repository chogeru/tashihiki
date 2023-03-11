#pragma once

#include"../Base/Base.h"

class Title :public Base {
	//画像オブジェクト
	CImage m_img;
	
public:
	Title();
	~Title();
	void Updata();
	void Draw();
};