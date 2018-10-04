/// <summary>
/// Collision.h
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Object/Entity.h"

/// <summary>
/// 前方宣言
/// </summary>
class SphereCollisionComponent;
class BoxCollisionComponent;
class PlaneCollisionComponent;
enum CollisionType
{
	NONE = 0,
	SPHERE_PLANE = 1 << 1,
	SPHERE_SPHERE = 1 << 2,

	COLLISION_MAX
};

struct CollisionData
{
	DirectX::SimpleMath::Vector3 hitPos;
	int typeFlag;
	SphereCollisionComponent* sphere[2];
	PlaneCollisionComponent* plane[2];
};

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collision
{
public:
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	// 中心座標
		float radius;	// 半径
	};
	struct Segment
	{
		DirectX::SimpleMath::Vector3 pos;		// 始点
		DirectX::SimpleMath::Vector3 vec;		// ベクトル
	};
	struct Plane
	{
		void Set_Plane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point)
		{
			// 法線を正規化しておく
			normal.Normalize();
			a = normal.x;
			b = normal.y;
			c = normal.z;

			// dの計算
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		void Set_Plane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// 法線を決める
			DirectX::SimpleMath::Vector3 vec_a = pos2 - pos1;
			DirectX::SimpleMath::Vector3 vec_b = pos3 - pos2;

			DirectX::SimpleMath::Vector3 normal = vec_a.Cross(vec_b);
			Set_Plane(normal, pos1);
		}
		void Rotation(DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 point, DirectX::SimpleMath::Vector3 angle)
		{
			DirectX::SimpleMath::Vector3 normal(a, b, c);
			DirectX::SimpleMath::Matrix _dir = DirectX::SimpleMath::Matrix::CreateFromYawPitchRoll(angle.y, angle.x, angle.z);
			normal = DirectX::SimpleMath::Vector3::Transform(normal, _dir);

			a = normal.x;
			b = normal.y;
			c = normal.z;

			// dの計算
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		float a, b, c, d;		// ABC　＝　法線
	};
	struct Triangle
	{
		void Set_Triangle(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// 3点を利用した平面を求める
			plane.Set_Plane(pos1, pos2, pos3);
			startPos[0] = pos1;
			startPos[1] = pos2;
			startPos[2] = pos3;
		}
		void MoveRotation(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 angle)
		{
			pos[0] = DirectX::SimpleMath::Vector3::Transform(startPos[0], world);
			pos[1] = DirectX::SimpleMath::Vector3::Transform(startPos[1], world);
			pos[2] = DirectX::SimpleMath::Vector3::Transform(startPos[2], world);

			plane.Rotation(dir, pos[0], angle);
		}
		DirectX::SimpleMath::Vector3 pos[3];
		DirectX::SimpleMath::Vector3 startPos[3];
		Plane plane;
	};

	static bool HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, DirectX::SimpleMath::Vector3* repulsionVel = nullptr);
	// 線分と平面の当たり判定
	static bool HitCheck_Segment_Plane(Segment& segment, Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// 線分と球の当たり判定
	static bool HitCheck_Segment_Sphere(Segment& segment, Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// 線分と三角形の当たり判定
	static bool HitCheck_Segment_Triangle(Segment& segment, Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// 三角形の任意の点が三角形内に存在するかどうか
	static bool Triangle_CheckInner(Triangle& triangle, DirectX::SimpleMath::Vector3& point);
	// 球と平面の当たり判定
	static bool HitCheck_Sphere_Plane(Sphere& sphere, Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// 球と三角形の衝突判定
	static bool HitCheck_Sphere_Triangle(Sphere& sphere, Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Sphere_Triagnles(Triangle triangle[], int triangle_index, Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr);

	/// <summary>
	/// 平面の方程式
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="p">点</param>
	/// <returns>平面と点の距離</returns>
	static float Plane_Length(Plane& plane, DirectX::SimpleMath::Vector3& p)
	{
		float l;
		l = plane.a * p.x + plane.b * p.y + plane.c * p.z + plane.d;
		return l;
	}

public:
	Collision();
	~Collision();
	
public:
	static bool HitCheck(Entity* entity, Entity* entity2, CollisionData *data);
};
