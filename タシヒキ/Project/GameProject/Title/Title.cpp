#include "Title.h"

Title::Title():Base(eType_Scene)
{
	m_img = COPY_RESOURCE("Title",CImage);
}

Title::~Title()
{
	//KillAll();
	//Base::Add(new Game());
}

void Title::Updata()
{//ƒ{ƒ^ƒ“‚P‚Å”jŠü
	/*if (PUSH(CInput::eButton1)) {
		m_kill = true;
	}*/
}

void Title::Draw()
{
	m_img.Draw();
	m_img.SetSize(1920, 1080);
}
