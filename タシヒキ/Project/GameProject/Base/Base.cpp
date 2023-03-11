#include "Base.h"
std::list<Base*> Base::m_list;
//スクロール値の定義
CVector2D Base::m_scroll(0, 0);

Base::Base(int type) :m_type(type),m_kill(false), m_vec(0,0),m_pos(0,0), m_rad(0) {

}
Base::~Base() {

}
void Base::Update() {
	//仮想関数
	//移動処理などを派生先で記述
}
void Base::Draw() {
	//仮想関数
	//描画処理などを派生先で記述
}
void Base::Collision(Base* b)
{
	//仮想関数
	//bとの衝突判定を派生先で記述
}
void Base::UpdateAll()
{
	//全てのオブジェクトの更新
	for (auto& b : m_list) {
		b->Update();
	}
}

void Base::DrawAll()
{
	//全てのオブジェクトの描画処理
	for (auto& b : m_list) {
		b->Draw();
	}
}

void Base::CollisionAll()
{
	//先頭
	auto it1 = m_list.begin();
	//末尾
	auto last = m_list.end();
	//末尾まで繰り返す
	while (it1 != last) {
		//it1の次の要素
		auto it2 = it1;
		it2++;
		//末尾まで繰り返す
		while (it2 != last) {
			//衝突検証
			(*it1)->Collision(*it2);
			(*it2)->Collision(*it1);
			//次へ
			it2++;
		}
		//次へ
		it1++;
	}
}
void Base::CheckKillAll()
{
	//先頭
	auto it = m_list.begin();
	//末尾
	auto last = m_list.end();
	//末尾まで繰り返す
	while (it != last) {
		if ((*it)->m_kill) {
			//実体を削除
			delete (*it);
			//リストから取り除く
			it = m_list.erase(it);
		} else {
			//次へ
			it++;
		}
	}
}



void Base::Add(Base* b)
{
	//Type順によるソート
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		//追加オブジェクトよりtypeの値が大きいオブジェクトを見つけたら
		if ((*itr)->m_type > b->m_type) {
			//そこに挿入(前に挿入される)
			m_list.insert(itr, b);
			return;
		}
		itr++;
	}
	//オブジェクトbを末尾に追加
	m_list.push_back(b);
}
void Base::KillAll()
{
	//全て削除
	std::list<Base*> ret;
	for (auto& b : m_list) {
		b->SetKill();
	}
}
bool Base::CollisionCircle(Base* b1, Base* b2)
{
	CVector2D v = b1->m_pos - b2->m_pos;
	float l = v.Length();
	if (l < b1->m_rad + b2->m_rad) {
		return true;
	}
	return false;
}

void Base::DrawRect()
{
	//デバッグ用　矩形の表示
	CRect rect = CRect(
		m_pos.x + m_rect.m_left,
		m_pos.y + m_rect.m_top,
		m_pos.x + m_rect.m_right,
		m_pos.y + m_rect.m_bottom);
	Utility::DrawQuad(
		CVector2D(rect.m_left, rect.m_top) - m_scroll,
		CVector2D(rect.m_width, rect.m_height),
		CVector4D(1, 0, 0, 0.5f));
}
bool Base::CollisionRect(Base* b1, Base* b2)
{
	//b1の矩形
	CRect rect1 = CRect(
		b1->m_pos.x + b1->m_rect.m_left,
		b1->m_pos.y + b1->m_rect.m_top,
		b1->m_pos.x + b1->m_rect.m_right,
		b1->m_pos.y + b1->m_rect.m_bottom);
	//b2の矩形
	CRect rect2 = CRect(
		b2->m_pos.x + b2->m_rect.m_left,
		b2->m_pos.y + b2->m_rect.m_top,
		b2->m_pos.x + b2->m_rect.m_right,
		b2->m_pos.y + b2->m_rect.m_bottom);

	//矩形同士の判定
	if (rect1.m_left <= rect2.m_right && rect1.m_right >= rect2.m_left &&
		rect1.m_top <= rect2.m_bottom && rect1.m_bottom >= rect2.m_top)
		return true;

	return false;
}
Base* Base::FindObject(int type)
{
	auto it = m_list.begin();
	auto last = m_list.end();
	while (it != last) {
		if ((*it)->m_type == type) {
			return (*it);
		}
		it++;
	}
	return nullptr;
}

std::list<Base*> Base::FindObjects(int type)
{
	std::list<Base*> ret;
	for (auto& b : m_list) {
		if (b->m_type == type)
			ret.push_back(b);
	}
	return ret;
}
CVector2D Base::GetScreenPos(const CVector2D& pos)
{
	return pos - m_scroll;
}