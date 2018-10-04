/// <summary>
/// Collision.cpp
/// 
/// 制作日:2018/7/12
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "Collision.h"

#include "../Component/ComponentLib.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX::SimpleMath;

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, Vector3* repulsionVel)
{
	Vector3 pos = Vector3::Transform(sphere.GetCenter(), entity->GetTrans().GetWorld());
	Vector3 pos2 = Vector3::Transform(sphere2.GetCenter(), entity2->GetTrans().GetWorld());

	// 中心間の距離の平方を計算
	DirectX::SimpleMath::Vector3 d = pos - pos2;
	float dist2 = d.Dot(d);
	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = sphere.GetRadius() + sphere2.GetRadius();
	if (dist2 < radiusSum * radiusSum)
	{
		if (repulsionVel)
		{
			float l = (sphere.GetRadius() + sphere2.GetRadius()) - sqrtf(dist2);
			d.Normalize();
			*repulsionVel += (d * l);
		}
		return true;
	}
	return false;
}

bool Collision::HitCheck_Segment_Plane(Segment & segment, Plane & plane, DirectX::SimpleMath::Vector3 * hit_pos)
{
	// 線分始点と平面の距離を計算
	float length = Plane_Length(plane, segment.pos);
	// 線分ベクトルの長さの2乗を計算
	float vec_length = segment.vec.Dot(segment.vec);
	// 絶対に届かない場合は終了
	if (vec_length < (length * length)) return false;
	// 線分ベクトルの正規化する
	float vec_length_nomalize = sqrtf(vec_length);
	// cosθを内積を利用して求める
	Vector3 vec = segment.vec * (1.0f / vec_length_nomalize);
	float cos_theta = vec.Dot(Vector3(-plane.a, -plane.b, -plane.c));
	// 線分が平面に届く距離を計算
	float plane_vec_length = length / cos_theta;
	// 届いていない
	if (plane_vec_length > vec_length) return false;
	// 交点を計算
	if (hit_pos)
	{
		*hit_pos = segment.pos + (vec * plane_vec_length);
	}
	return true;
}

bool Collision::HitCheck_Segment_Sphere(Segment & segment, Sphere & sphere, DirectX::SimpleMath::Vector3 * hit_pos)
{
	// (2次方程式) = at^2 + bt + c = 0;
	// 2次方程式におけるa,b,cを計算
	float xa = segment.pos.x - sphere.center.x;
	float ya = segment.pos.y - sphere.center.y;
	float za = segment.pos.z - sphere.center.z;

	// vec = 線分の速度

	// (a) = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	float a = segment.vec.x * segment.vec.x + segment.vec.y * segment.vec.y + segment.vec.z * segment.vec.z;
	// (b) = 2(vec.x * xa + vec.y * ya * vec.z * za);
	float b = 2.0f * (segment.vec.x * xa + segment.vec.y * ya + segment.vec.z * za);
	// (c) = xa^2 + ya^2 + za^2 - radius^2;
	float c = xa * xa + ya * ya + za * za - sphere.radius * sphere.radius;

	// 2次方程式が解けないと判断したときは衝突していないとみなす
	float d = b * b - 4.0f * a * c;
	if (d < 0.0f) return false;

	// 解の公式を解く
	d = sqrtf(d);
	float t0 = (-b + d) / (2.0f * a);
	float t1 = (-b - d) / (2.0f * a);

	float t = 2.0f;
	if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t)) t = t0;
	if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t)) t = t1;

	if (t > 1.0f) return false;

	// 交点を計算
	if (hit_pos)
	{
		*hit_pos = segment.pos + (segment.vec * t);
	}
	return true;
}

bool Collision::HitCheck_Segment_Triangle(Segment & segment, Triangle & triangle, DirectX::SimpleMath::Vector3 * hit_pos)
{
	// 三角形の平面とチェック
	Vector3 tmp_hit_pos;
	if (!HitCheck_Segment_Plane(segment, triangle.plane, &tmp_hit_pos)) return false;
	if (!Triangle_CheckInner(triangle, tmp_hit_pos))
	{
		// 外部
		return false;
	}
	else
	{
		// 内部
		if (hit_pos)
		{
			*hit_pos = tmp_hit_pos;
		}
		return true;
	}
}

bool Collision::Triangle_CheckInner(Triangle & triangle, DirectX::SimpleMath::Vector3& point)
{
	Vector3 AB = triangle.pos[1] - triangle.pos[0];
	Vector3 BP = point - triangle.pos[1];

	Vector3 BC = triangle.pos[2] - triangle.pos[1];
	Vector3 CP = point - triangle.pos[2];

	Vector3 CA = triangle.pos[0] - triangle.pos[2];
	Vector3 AP = point - triangle.pos[0];

	Vector3 c1 = AB.Cross(BP);
	Vector3 c2 = BC.Cross(CP);
	Vector3 c3 = CA.Cross(AP);


	//内積で順方向か逆方向か調べる
	double dot_12 = c1.Dot(c2);
	double dot_13 = c1.Dot(c3);

	if (dot_12 > 0 && dot_13 > 0) {
		//三角形の内側に点がある
		return true;
	}
	return false;

	//// 任意点から各頂点へのベクトル作成
	//Vector3 vt0 = triangle.pos[0] - point;
	//Vector3 vt1 = triangle.pos[1] - point;
	//Vector3 vt2 = triangle.pos[2] - point;

	//// 三角形の辺のベクトル
	//Vector3 v0 = triangle.pos[1] - triangle.pos[0];
	//Vector3 v1 = triangle.pos[2] - triangle.pos[1];
	//Vector3 v2 = triangle.pos[0] - triangle.pos[2];

	//// 各外積を求める
	//Vector3 c0 = vt0.Cross(v0);
	//Vector3 c1 = vt1.Cross(v1);
	//Vector3 c2 = vt2.Cross(v2);

	//// 外積の向きがそろっているかチェック(すべて掛け算をしマイナス値になっているかどうか)
	//float dot0 = c0.Dot(c1);
	//float dot1 = c1.Dot(c2);
	//float dot2 = c2.Dot(c0);

	/*if ((dot0 <= 0.0f && dot1 <= 0.0f && dot2 <= 0.0f) ||
		(dot0 >= 0.0f && dot1 >= 0.0f && dot2 >= 0.0f))
	{
		return true;
	}
	else
	{
		return false;
	}*/
	//if ((dot0 * dot1) <= 0.0f)
	/*if (dot0 >= 0.0f && dot1 >= 0.0f)
	{
		return true;
	}
	else
	{
  		return false;
	}*/
}

bool Collision::HitCheck_Sphere_Plane(Sphere & sphere, Plane & plane, DirectX::SimpleMath::Vector3* hit_pos)
{
	float length = Plane_Length(plane, sphere.center);
	if (length > sphere.radius) return false;
	
	// 交点を計算
	if (hit_pos)
	{
		length = sphere.radius - length;
		*hit_pos = Vector3(plane.a, plane.b, plane.c) * length;
	}
	return true;
}

bool Collision::HitCheck_Sphere_Triangle(Sphere & sphere, Triangle & triangle, DirectX::SimpleMath::Vector3 * hit_pos)
{
	if (!HitCheck_Sphere_Plane(sphere, triangle.plane, hit_pos)) return false;

	// 三角形の辺の当たり判定
	Vector3 vec;
	vec = triangle.pos[1] - triangle.pos[0];
	Segment segment = Segment{Vector3(triangle.pos[0]), Vector3(vec)};
	if (HitCheck_Segment_Sphere(segment, sphere, hit_pos))
	{
		Game::AddText(L"Hit1");
		return true;
	}

	vec = triangle.pos[2] - triangle.pos[1];
	segment = Segment{ Vector3(triangle.pos[1]), Vector3(vec) };
	if (HitCheck_Segment_Sphere(segment, sphere, hit_pos)) 
	{
		Game::AddText(L"Hit2");
		return true;
	}

	vec = triangle.pos[0] - triangle.pos[2];
	segment = Segment{ Vector3(triangle.pos[2]), Vector3(vec) };
	if (HitCheck_Segment_Sphere(segment, sphere, hit_pos))
	{
		Game::AddText(L"Hit3");
		return true;
	}

	// 球が三角形の中央にめり込むかどうか
	vec = Vector3(-triangle.plane.a * sphere.radius, -triangle.plane.b * sphere.radius, -triangle.plane.c * sphere.radius);
	segment = Segment{ Vector3(sphere.center), Vector3(vec) };
	if (HitCheck_Segment_Triangle(segment, triangle, hit_pos))
	{
		Game::AddText(L"Hit4");
		return true;
	}

	return false;
}

bool Collision::HitCheck_Sphere_Triagnles(Triangle triangle[], int triangle_index, Sphere & sphere, DirectX::SimpleMath::Vector3 * hit_pos)
{
	for (int i = 0; i < triangle_index; i++)
	{
		if (HitCheck_Sphere_Triangle(sphere, triangle[i], hit_pos))
		{
			
			return true;
		}
	}
	return false;
}

/// <summary>
/// 当たり判定を求める
/// </summary>
/// <param name="entity">実体</param>
/// <param name="repulsionVel">反発速度</param>
/// <returns>当たり判定</returns>
bool Collision::HitCheck(Entity * entity, Entity* entity2, CollisionData *data)
{
	if(!entity || !entity2)
	{
		return false;
	}
	SphereCollisionComponent* sphereCollision = entity->GetComponent<SphereCollisionComponent>();
	SphereCollisionComponent* sphereCollision2 = entity2->GetComponent<SphereCollisionComponent>();

	PlaneCollisionComponent* planeCollision = entity->GetComponent<PlaneCollisionComponent>();
	PlaneCollisionComponent* planeCollision2 = entity2->GetComponent<PlaneCollisionComponent>();

	if (sphereCollision)
	{
		data->sphere[0] = sphereCollision;
		if (sphereCollision2)
		{
			data->sphere[1] = sphereCollision2;
			if (HitCheck_Sphere(entity, *sphereCollision, entity2, *sphereCollision2, &data->hitPos))
			{
				data->typeFlag = CollisionType::SPHERE_SPHERE;
				return true;
			}
		}
		if (planeCollision2)
		{
			data->plane[1] = planeCollision2;
			if (HitCheck_Sphere_Triagnles(planeCollision2->GetTriangle(), planeCollision2->GetTriangleIndex(), sphereCollision->GetSphere(), &data->hitPos))
			{
				data->typeFlag = CollisionType::SPHERE_PLANE;
				return true;
			}
		}
	}

	if (planeCollision)
	{
		data->plane[0] = planeCollision;
		if (sphereCollision2)
		{
			data->sphere[1] = sphereCollision2;
			if (HitCheck_Sphere_Triagnles(planeCollision->GetTriangle(), planeCollision->GetTriangleIndex(), sphereCollision2->GetSphere(), &data->hitPos))
			{

				data->typeFlag = CollisionType::SPHERE_PLANE;
				return true;
			}
		}
	}

	return false;
}
