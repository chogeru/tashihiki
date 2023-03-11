#include "Title.h"
#include"../h.h"
Title::Title():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("Title",CImage);
}

Title::~Title()
{
	
}

void Title::Updata()
{

}

void Title::Draw()
{
	m_img.Draw();
    m_img.SetSize(1920, 1080);
}
