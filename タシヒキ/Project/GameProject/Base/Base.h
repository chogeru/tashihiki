#pragma once
#include <GLLibrary.h>
enum {
	eType_Field,
	eType_Player,
	eType_Enemy,
	eType_Player_Bullet,
	eType_Enemy_Bullet,
	eType_Goal,
	eType_Effect,
	eType_UI,
	eType_UI2,
	eType_Scene,
	eType_Trap,
	eType_ArrowTrap,
	eType_Manual,
	eType_Arrow,
	eType_GameClear,
	eType_GameOver,
};

//重力加速度
#define GRAVITY (9.8f/20)

class Base {
public:
	//オブジェクトの種類
	int m_type;
	//座標
	CVector2D m_pos;
	//移動前の座標
	CVector2D m_pos_old;
	//移動ベクトル
	CVector2D m_vec;
	//回転値
	float m_ang;
	//半径
	float m_rad;
	//矩形
	CRect m_rect;
	//ヒットID
	int	m_hit_id;
	//削除フラグ
	bool m_kill;
	//スクロール値
	static CVector2D m_scroll;

	//オブジェクトリスト
	static std::list<Base*> m_list;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">オブジェクトの種類</param>
	/// <returns></returns>
	Base(int type);

	/// <summary>
	/// デストラクタ
	/// </summary>
	/// <returns></returns>
	virtual ~Base();


	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();


	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 削除フラグON
	/// </summary>
	void SetKill() {
		m_kill = true;
	}
	/// <summary>
	/// 当たり判定検証
	/// </summary>
	/// <param name="b">判定対象オブジェクト</param>
	virtual void Collision(Base* b);

	/// <summary>
	/// 全てのオブジェクトの更新
	/// </summary>
	static void UpdateAll();

	/// <summary>
	/// 全てのオブジェクトの描画
	/// </summary>
	static void DrawAll();

	/// <summary>
	/// 全てのオブジェクトの衝突チェック
	/// </summary>
	static void CollisionAll();

	/// <summary>
	/// 全てのオブジェクトの削除チェック
	/// </summary>
	static void CheckKillAll();

	/// <summary>
	/// 全てのオブジェクトを削除
	/// </summary>
	static void KillAll();

	/// <summary>
	/// オブジェクトの追加
	/// </summary>
	/// <param name="b">追加するオブジェクト</param>
	static void Add(Base* b);

	/// <summary>
	/// 円同士の判定
	/// </summary>
	/// <param name="b1">判定オブジェクト１</param>
	/// <param name="b2">判定オブジェクト２</param>
	/// <returns>true:接触</returns>
	static bool CollisionCircle(Base* b1, Base* b2);

	/// <summary>
	/// 矩形同士の判定
	/// </summary>
	/// <param name="b1">判定オブジェクト１</param>
	/// <param name="b2">判定オブジェクト２</param>
	/// <returns>true:接触</returns>
	static bool CollisionRect(Base* b1, Base* b2);

	/// <summary>
	/// 矩形の表示
	/// </summary>
	void DrawRect();



	/// <summary>
	/// オブジェクトの検索
	/// </summary>
	/// <param name="type">検索するオブジェクトの種類</param>
	/// <returns>一番初めに見つけたオブジェクトへのポインタ</returns>
	static Base* FindObject(int type);

	/// <summary>
	/// オブジェクトの検索
	/// </summary>
	/// <param name="type">検索するオブジェクトの種類</param>
	/// <returns>見つけたオブジェクトのリスト</returns>
	static std::list<Base*> FindObjects(int type);


	/// <summary>
	/// スクロール値を反映した画面上での位置を取得
	/// </summary>
	/// <param name="pos">ワールド座標</param>
	/// <returns>スクリーン座標</returns>
	static CVector2D GetScreenPos(const CVector2D& pos);
};

