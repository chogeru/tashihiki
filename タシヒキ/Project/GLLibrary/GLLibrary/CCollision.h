#pragma once

#include "CMatrix.h"
#include "CRect.h"
/*!
 *	@brief		AABBクラス
 *
 *	OBBのパラメータクラス
 */
class CAABB {
public:
	CVector3D min;
	CVector3D max;
	CAABB() {
	}
	CAABB(const CVector3D& imin, const CVector3D &imax) {
		min = imin;
		max = imax;
	}
	void Draw(const CVector4D& color);
};
/*!
 *	@brief		OBBクラス
 *	
 *	OBBのパラメータクラス
 */
class COBB {
public:
	CVector3D m_center;		//中心座標
	CVector3D m_axis[3];	//各軸ベクトル
	CVector3D	 m_length;	//各軸の長さ
	COBB() {
	}
	COBB(const CVector3D& center, const CVector3D& axis_x, const CVector3D& axis_y, const CVector3D& axis_z, const CVector3D& length) {
		m_center = center;
		m_axis[0] = axis_x;m_axis[1] = axis_y;m_axis[2] = axis_z;
		m_length = length;
	}
	//OBBに行列を反映
	void Transeform(const CMatrix &mat);
	/*
		@brief	判定テスト用OBBの表示
		@retval	無し
	*/
	void Draw(const CVector4D& color);
};

/*!
 *	@brief		衝突判定クラス
 *
 */
class CCollision {
private:
	/*!
		@brief	separate軸上に投影したOBB同士が接触しているか調べる
		@param	A			[in] 衝突対象OBB
		@param	B			[in] 衝突対象OBB
		@param	distVec		[in] Aの中心からBの中心までのベクトル
		@param	separate	[in] 分離軸、投影を行う軸
		@retval	結果:true接触 false非接触
	**/
	static bool CompareLength(const COBB &A,const COBB &B,const CVector3D &distVec,const CVector3D &separate,float *length=NULL);
public:
	/*!
	@brief	矩形同士の衝突判定
	@param	rect1		[in] １つ目の矩形
	@param	rect2		[in] ２つ目の矩形
	@retval	結果:true接触 false非接触
	**/
	static bool CollisionRect(const CRect &rect1, const CRect &rect2);
	/*!
	@brief	矩形と点との衝突判定
	@param	rect		[in] 矩形
	@param	point		[in] 点
	@retval	結果:true接触 false非接触
	**/
	static bool CollisionRectPoint(const CRect &rect, const CVector2D point);
	/*!
		@brief	球同士の衝突判定
		@param	centerA		[in] １つ目の球の中心位置
		@param	radiusA		[in] １つ目の球の半径
		@param	centerB		[in] ２つ目の球の中心位置
		@param	radiusB		[in] ２つ目の球の半径
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionShpere(const CVector3D &centerA,float radiusA,const CVector3D &centerB,float radiusB);
	static bool CollisionShpere(const CVector2D& centerA, float radiusA, const CVector2D& centerB, float radiusB);
	/*!
		@brief	AABB同士の衝突判定
		@param	minA		[in] １つ目のAABBの最小位置
		@param	maxA		[in] １つ目のAABBの最大位置
		@param	minB		[in] ２つ目のAABBの最小位置
		@param	maxB		[in] ２つ目のAABBの最大位置
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionAABB(const CVector3D &minA,const CVector3D &maxA,const CVector3D &minB,const CVector3D &maxB);
	static bool CollisionAABB(const CAABB &A, const CAABB& B) {
		return CollisionAABB(A.min,A.max,B.min,B.max);
	}
	/*!
	@brief	AABBと点の衝突判定
	@param	min		[in] AABBの最小位置
	@param	max		[in] AABBの最大位置
	@param	point		[in] 点の座標
	@retval	結果:true接触 false非接触
	**/
	static bool CollisionAABBPoint(const CVector3D &min, const CVector3D &max, const CVector3D &point);
	static bool CollisionAABBPoint(const CAABB &AABB, const CVector3D &point) {
		return CollisionAABBPoint(AABB.min, AABB.max, point);
	}

	/*!
	@brief	AABBと線の衝突判定
	@param	cross	[in] 接触点
	@param	length	[in] 距離
	@param	min		[in] AABBの最小位置
	@param	max		[in] AABBの最大位置
	@param	point	[in] 線上の点
	@param	dir		[in] 線の方向
	@retval	結果:true接触 false非接触
	**/
	static bool CollisionAABBRay(CVector3D *cross, float* length, const CVector3D& min, const CVector3D& max, const CVector3D& point, const CVector3D& dir);
	/*!
		@brief	OBB同士の衝突判定
		@param	A			[in] １つ目のOBB
		@param	B			[in] ２つ目のOBB
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionOBB(const COBB &A,const COBB &B);
	/*!
	@brief	OBBと球の衝突判定
	@param	A			[in] OBB
	@param	cneter		[in] 球の中心
	@param	radius		[in] 球の半径
	@param	axis		[in] 接触方向
	@retval	結果:true接触 false非接触
	**/
	static bool CollisionOBBShpere(const COBB &A, const CVector3D &cener, float radius, CVector3D *axis=nullptr,float *length=nullptr);

	/*!
		@brief	カプセルと球の衝突判定
		@param　c_top		[in] カプセル開始地点
		@param　c_bottom	[in] カプセル終了地点
		@param	c_radius	[in] カプセルの半径
		@param	s_cneter	[in] 球の中心
		@param	s_radius	[in] 球の半径
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionCapsuleShpere(const CVector3D &c_top,const CVector3D &c_bottom,float c_radius,const CVector3D &s_center , float s_radius);
	static bool CollisionCapsuleShpere(const CVector2D& c_top, const CVector2D& c_bottom, float c_radius, const CVector2D& s_center, float s_radius);

	/*!
		@brief	カプセル同士の衝突判定
		@param　top1		[in] カプセル開始地点
		@param　bottom1		[in] カプセル終了地点
		@param	radius1		[in] カプセルの半径
		@param　top2		[in] カプセル開始地点
		@param　bottom2		[in] カプセル終了地点
		@param	radius2		[in] カプセルの半径
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionCapsule(const CVector3D &top1,const CVector3D &bottom1,float radius1,const CVector3D &top2,const CVector3D &bottom2,float radius2);
	static bool CollisionCapsule(const CVector2D& top1, const CVector2D& bottom1, float radius1, const CVector2D& top2, const CVector2D& bottom2, float radius2);

	/*!
		@brief	点Cが三角形ポリゴン上にあるか調べる
		@param	C			[in] 点の座標
		@param	V0			[in] 三角形ポリゴンの頂点1
		@param	V1			[in] 三角形ポリゴンの頂点2
		@param	V2			[in] 三角形ポリゴンの頂点3
		@param	N			[in] 三角形ポリゴンの法線
		@retval	結果:true接触 false非接触
	**/
	static bool TriangleIntersect(const CVector3D &c,const CVector3D &v0,const  CVector3D &v1, const CVector3D &v2,const CVector3D &n);
	/*!
		@brief	線分と三角形ポリゴンとの衝突判定
		@param	C			[out] 接触地点
		@param	S			[in] 線分の開始位置
		@param	E			[in] 線分の終了位置
		@param	V0			[in] 三角形ポリゴンの頂点1
		@param	V1			[in] 三角形ポリゴンの頂点2
		@param	V2			[in] 三角形ポリゴンの頂点3
		@retval	結果:true接触 false非接触
	**/
	static bool IntersectTriangleRay(CVector3D *corss,const CVector3D &p1,const  CVector3D &p2,const CVector3D& v0,const  CVector3D &v1,const  CVector3D &v2,float *dist);
	static bool IntersectTriangleRay(CVector3D *corss, const CVector3D &p1, const  CVector3D &p2, const CVector3D& v0, const  CVector3D &v1, const  CVector3D &v2, const  CVector3D &normal, float *dist);

	/*!
		@brief	pointから近いv0→v1線上の点を調べる
		@param	V0			[in] 線分の開始位置
		@param	V1			[in] 線分の終了位置
		@param	point		[in] 点
		@retval	結果:true接触 false非接触
	**/
	static CVector3D PointOnLineSegmentNearestPoint(const CVector3D &v0,const CVector3D &v1,const CVector3D &point);
	
	/*!
		@brief	pointから近いv0→v1線上の点を調べる（二次元用）
		@param	V0			[in] 線分の開始位置
		@param	V1			[in] 線分の終了位置
		@param	point		[in] 点
		@retval	結果:true接触 false非接触
	**/
	static CVector2D PointOnLineSegmentNearestPoint(const CVector2D &v0,const CVector2D &v1,const CVector2D &point);

	/*!
		@brief	三角ポリゴンと球の衝突判定
		@param	V0			[in] 三角形ポリゴンの頂点1
		@param	V1			[in] 三角形ポリゴンの頂点2
		@param	V2			[in] 三角形ポリゴンの頂点3
		@param	cneter		[in] 球の中心
		@param	rudius		[in] 球の半径
		@param	cross		[out] 最短接触点
		@param	length		[out] 最短距離
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionTriangleSphere(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &center,float radius,CVector3D *cross=0,float *length = 0);
	static bool CollisionTriangleSphere(const CVector3D &v0, const CVector3D &v1, const CVector3D &v2, const CVector3D &normal,const CVector3D &center, float radius, CVector3D *cross = 0, float *length = 0);

	/*!
		@brief	三角ポリゴンとカプセルの衝突判定
		@param	V0			[in] 三角形ポリゴンの頂点1
		@param	V1			[in] 三角形ポリゴンの頂点2
		@param	V2			[in] 三角形ポリゴンの頂点3
		@param	cneter		[in] 球の中心
		@param	rudius		[in] 球の半径
		@param	cross		[out] 最短接触点
		@param	length		[out] 最短距離
		@retval	結果:true接触 false非接触
	**/
	static bool CollisionTriangleCapsule(const CVector3D &v0,const CVector3D &v1,const CVector3D &v2,const CVector3D &top,const CVector3D &bottom,float radius,CVector3D *cross=0,float *length = 0);
	static bool CollisionTriangleCapsule(const CVector3D &v0, const CVector3D &v1, const CVector3D &v2, const CVector3D &normal,const CVector3D &top, const CVector3D &bottom, float radius, CVector3D *cross = 0, float *length = 0);


	/*!
		@brief	2線分間の距離
		@param	s1			[in] 線分１の開始地点
		@param	e1			[in] 線分１の終了地点
		@param	s2			[in] 線分２の開始地点
		@param	e2			[in] 線分２の終了地点
		@param	c1			[out] 線分１上での最短地点（未実装）
		@param	c2			[out] 線分２上での最短地点（未実装）
		@retval	距離
	**/
	static float DistanceLine(const CVector3D &s1,const CVector3D &e1,const CVector3D &s2,const CVector3D &e2,CVector3D *c1=NULL,CVector3D *c2=NULL);
	static float DistanceLine(const CVector2D& s1, const CVector2D& e1, const CVector2D& s2, const CVector2D& e2, CVector2D* c1 = NULL, CVector2D* c2 = NULL);


	/*!
	@brief	2線分間の交差
	@param	s1			[in] 線分１の開始地点
	@param	e1			[in] 線分１の終了地点
	@param	s2			[in] 線分２の開始地点
	@param	e2			[in] 線分２の終了地点
	@retval	距離
	**/
	static bool CollitionLine(const CVector2D &s1, const CVector2D &e1, const CVector2D &s2, const CVector2D &e2);


	/*!
		@brief	点と線の距離
		@param	v0			[in] 線分の開始地点
		@param	v1			[in] 線分の終了地点
		@param	p			[in] 点
		@retval　距離
	**/
	static float DistancePointToLine(const CVector3D &v0,const CVector3D &v1,const CVector3D &p);
	static float DistancePointToLine(const CVector2D &v0, const CVector2D &v1, const CVector2D &p);
	/*!
		@brief	点と線の距離の二乗
		@param	v0			[in] 線分の開始地点
		@param	v1			[in] 線分の終了地点
		@param	p			[in] 点
		@retval　距離の二乗
	**/
	static float DistancePointToLineSq(const CVector3D &v0,const CVector3D &v1,const CVector3D &p);
	static float DistancePointToLineSq(const CVector2D& v0, const CVector2D& v1, const CVector2D& p);

};