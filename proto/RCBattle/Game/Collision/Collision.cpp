/// <summary>
/// Collision.cpp
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "Collision.h"

#include "../Component/ComponentLib.h"

/// <summary>
/// ���O���
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

	// ���S�Ԃ̋����̕������v�Z
	DirectX::SimpleMath::Vector3 d = pos - pos2;
	float dist2 = d.Dot(d);
	// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
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
	// �����n�_�ƕ��ʂ̋������v�Z
	float length = Plane_Length(plane, segment.pos);
	// �����x�N�g���̒�����2����v�Z
	float vec_length = segment.vec.Dot(segment.vec);
	// ��΂ɓ͂��Ȃ��ꍇ�͏I��
	if (vec_length < (length * length)) return false;
	// �����x�N�g���̐��K������
	float vec_length_nomalize = sqrtf(vec_length);
	// cos�Ƃ���ς𗘗p���ċ��߂�
	Vector3 vec = segment.vec * (1.0f / vec_length_nomalize);
	float cos_theta = vec.Dot(Vector3(-plane.a, -plane.b, -plane.c));
	// ���������ʂɓ͂��������v�Z
	float plane_vec_length = length / cos_theta;
	// �͂��Ă��Ȃ�
	if (plane_vec_length > vec_length) return false;
	// ��_���v�Z
	if (hit_pos)
	{
		*hit_pos = segment.pos + (vec * plane_vec_length);
	}
	return true;
}

bool Collision::HitCheck_Segment_Sphere(Segment & segment, Sphere & sphere, DirectX::SimpleMath::Vector3 * hit_pos)
{
	// (2��������) = at^2 + bt + c = 0;
	// 2���������ɂ�����a,b,c���v�Z
	float xa = segment.pos.x - sphere.center.x;
	float ya = segment.pos.y - sphere.center.y;
	float za = segment.pos.z - sphere.center.z;

	// vec = �����̑��x

	// (a) = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	float a = segment.vec.x * segment.vec.x + segment.vec.y * segment.vec.y + segment.vec.z * segment.vec.z;
	// (b) = 2(vec.x * xa + vec.y * ya * vec.z * za);
	float b = 2.0f * (segment.vec.x * xa + segment.vec.y * ya + segment.vec.z * za);
	// (c) = xa^2 + ya^2 + za^2 - radius^2;
	float c = xa * xa + ya * ya + za * za - sphere.radius * sphere.radius;

	// 2���������������Ȃ��Ɣ��f�����Ƃ��͏Փ˂��Ă��Ȃ��Ƃ݂Ȃ�
	float d = b * b - 4.0f * a * c;
	if (d < 0.0f) return false;

	// ���̌���������
	d = sqrtf(d);
	float t0 = (-b + d) / (2.0f * a);
	float t1 = (-b - d) / (2.0f * a);

	float t = 2.0f;
	if ((t0 >= 0.0f) && (t0 <= 1.0f) && (t0 < t)) t = t0;
	if ((t1 >= 0.0f) && (t1 <= 1.0f) && (t1 < t)) t = t1;

	if (t > 1.0f) return false;

	// ��_���v�Z
	if (hit_pos)
	{
		*hit_pos = segment.pos + (segment.vec * t);
	}
	return true;
}

bool Collision::HitCheck_Segment_Triangle(Segment & segment, Triangle & triangle, DirectX::SimpleMath::Vector3 * hit_pos)
{
	// �O�p�`�̕��ʂƃ`�F�b�N
	Vector3 tmp_hit_pos;
	if (!HitCheck_Segment_Plane(segment, triangle.plane, &tmp_hit_pos)) return false;
	if (!Triangle_CheckInner(triangle, tmp_hit_pos))
	{
		// �O��
		return false;
	}
	else
	{
		// ����
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


	//���ςŏ��������t���������ׂ�
	double dot_12 = c1.Dot(c2);
	double dot_13 = c1.Dot(c3);

	if (dot_12 > 0 && dot_13 > 0) {
		//�O�p�`�̓����ɓ_������
		return true;
	}
	return false;

	//// �C�ӓ_����e���_�ւ̃x�N�g���쐬
	//Vector3 vt0 = triangle.pos[0] - point;
	//Vector3 vt1 = triangle.pos[1] - point;
	//Vector3 vt2 = triangle.pos[2] - point;

	//// �O�p�`�̕ӂ̃x�N�g��
	//Vector3 v0 = triangle.pos[1] - triangle.pos[0];
	//Vector3 v1 = triangle.pos[2] - triangle.pos[1];
	//Vector3 v2 = triangle.pos[0] - triangle.pos[2];

	//// �e�O�ς����߂�
	//Vector3 c0 = vt0.Cross(v0);
	//Vector3 c1 = vt1.Cross(v1);
	//Vector3 c2 = vt2.Cross(v2);

	//// �O�ς̌�����������Ă��邩�`�F�b�N(���ׂĊ|���Z�����}�C�i�X�l�ɂȂ��Ă��邩�ǂ���)
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
	
	// ��_���v�Z
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

	// �O�p�`�̕ӂ̓����蔻��
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

	// �����O�p�`�̒����ɂ߂荞�ނ��ǂ���
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
/// �����蔻������߂�
/// </summary>
/// <param name="entity">����</param>
/// <param name="repulsionVel">�������x</param>
/// <returns>�����蔻��</returns>
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
