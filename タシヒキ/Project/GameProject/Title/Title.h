#pragma once

#include"../Base/Base.h"

class Title :public Base {
	//�摜�I�u�W�F�N�g
	CImage m_img;
	
public:
	Title();
	~Title();
	void Updata();
	void Draw();
};