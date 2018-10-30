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
#include <list>
#include "../Object/Entity.h"
//#include "../Component/Collision/CollisionComponent.h"

/// <summary>
/// 前方宣言
/// </summary>
class CollisionComponent;
class SphereCollisionComponent;
class BoxCollisionComponent;
class PlaneCollisionComponent;

/// <summary>
/// 当たり判定クラス
/// </summary>
class Collision
{
	/// <summary>
	/// 形状の定義
	/// </summary>
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
		void Set_Plane(DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 point)
		{
			DirectX::SimpleMath::Vector3 normal = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::Forward, dir);

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
		void Set_Triangle(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Quaternion dir)
		{
			pos[0] = DirectX::SimpleMath::Vector3::Transform(startPos[0], world);
			pos[1] = DirectX::SimpleMath::Vector3::Transform(startPos[1], world);
			pos[2] = DirectX::SimpleMath::Vector3::Transform(startPos[2], world);

			plane.Set_Plane(dir, pos[0]);
		}
		DirectX::SimpleMath::Vector3 pos[3];
		DirectX::SimpleMath::Vector3 startPos[3];
		Plane plane;
	};

	/// <summary>
	/// データの定義
	/// </summary>
public:

	enum CollisionType
	{
		NONE = 0,
		SPHERE = 1 << 1,
		PLANE = 1 << 2,
		TRIANGLE = 1 << 3,

		COLLISION_MAX
	};

	struct CollisionData
	{
		DirectX::SimpleMath::Vector3 hitPos;
		int typeFlag;
		Sphere* sphere;
		Segment* segment;
		Plane* plane;
		Triangle* triangle;
	};

	union ShapeType
	{
		Sphere* sphere;
		Segment* segment;
		Plane* plane;
		Triangle* triangle;
	};

	struct CollisionData2
	{
		int typeFlag;
		ShapeType shape;
	};

public:

	// 球と球の当たり判定
	static bool HitCheck_Sphere_Sphere(const Sphere& sphere, const Sphere& sphere2, DirectX::SimpleMath::Vector3* hit_pos = nullptr);

	// 線分と平面の当たり判定
	static bool HitCheck_Segment_Plane(const Segment& segment, const Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Segment_Plane(const Plane& plane, const Segment& segment, DirectX::SimpleMath::Vector3* hit_pos = nullptr)
	{
		return HitCheck_Segment_Plane(segment, plane, hit_pos);
	}

	// 線分と球の当たり判定
	static bool HitCheck_Segment_Sphere(const Segment& segment, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Segment_Sphere(const Sphere& sphere, const Segment& segment, DirectX::SimpleMath::Vector3* hit_pos = nullptr)
	{
		return HitCheck_Segment_Sphere(segment, sphere, hit_pos);
	}

	// 線分と三角形の当たり判定
	static bool HitCheck_Segment_Triangle(const Segment& segment, const Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Segment_Triangle(const Triangle& triangle, const Segment& segment, DirectX::SimpleMath::Vector3* hit_pos = nullptr)
	{
		return HitCheck_Segment_Triangle(segment, triangle, hit_pos);
	}

	// 三角形の任意の点が三角形内に存在するかどうか
	static bool Triangle_CheckInner(const Triangle& triangle, DirectX::SimpleMath::Vector3& point);

	// 球と平面の当たり判定
	static bool HitCheck_Sphere_Plane(const Sphere& sphere, const Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Sphere_Plane(const Plane& plane, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr)
	{
		return HitCheck_Sphere_Plane(sphere, plane, hit_pos);
	}

	// 球と三角形の衝突判定
	static bool HitCheck_Sphere_Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Sphere_Triangle(const Triangle& triangle, const Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr)
	{
		return HitCheck_Sphere_Triangle(sphere, triangle, hit_pos);
	}

	/// <summary>
	/// 平面の方程式
	/// </summary>
	/// <param name="plane">平面</param>
	/// <param name="p">点</param>
	/// <returns>平面と点の距離</returns>
	static float Plane_Length(const Plane& plane, const DirectX::SimpleMath::Vector3& p)
	{
		float l;
		l = plane.a * p.x + plane.b * p.y + plane.c * p.z + plane.d;
		return l;
	}

public:
	Collision();
	~Collision();
	
private:
	static bool Check(CollisionComponent* collision, CollisionComponent* collision2, CollisionData* data);

public:
	static bool HitCheck(Entity* entity, Entity* entity2, CollisionData* data, CollisionData* data2);
};
