/// <summary>
/// Collision.h
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../Object/Entity.h"

/// <summary>
/// �O���錾
/// </summary>
class SphereCollisionComponent;
class BoxCollisionComponent;
class PlaneCollisionComponent;

enum CollisionType
{
	Sphere_Sphere,
	Sphere_Plane,

	CollisionType_Max
};

struct CollisionData
{
	DirectX::SimpleMath::Vector3 hit_pos;
	CollisionType type;
	Component* component1;
	Component* component2;
};
/// <summary>
/// �����蔻��N���X
/// </summary>
class Collision
{
public:
	struct Sphere
	{
		DirectX::SimpleMath::Vector3 center;	// ���S���W
		float radius;	// ���a
	};
	struct Segment
	{
		DirectX::SimpleMath::Vector3 pos;		// �n�_
		DirectX::SimpleMath::Vector3 vec;		// �x�N�g��
	};
	struct Plane
	{
		void Set_Plane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point)
		{
			// �@���𐳋K�����Ă���
			normal.Normalize();
			a = normal.x;
			b = normal.y;
			c = normal.z;

			// d�̌v�Z
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		void Set_Plane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// �@�������߂�
			DirectX::SimpleMath::Vector3 vec_a = pos2 - pos1;
			DirectX::SimpleMath::Vector3 vec_b = pos3 - pos2;

			DirectX::SimpleMath::Vector3 normal = vec_a.Cross(vec_b);
			Set_Plane(normal, pos1);
		}
		void Rotation(DirectX::SimpleMath::Quaternion dir, DirectX::SimpleMath::Vector3 point)
		{
			DirectX::SimpleMath::Vector3 normal = DirectX::SimpleMath::Vector3(a, b, c);
			normal = DirectX::SimpleMath::Vector3::Transform(normal, dir);
			a = normal.x;
			b = normal.y;
			c = normal.z;

			// d�̌v�Z
			d = -((normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z));
		}
		float a, b, c, d;		// ABC�@���@�@��
	};
	struct Triangle
	{
		void Set_Triangle(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3)
		{
			// 3�_�𗘗p�������ʂ����߂�
			plane.Set_Plane(pos1, pos2, pos3);
			startPos[0] = pos1;
			startPos[1] = pos2;
			startPos[2] = pos3;
		}
		void MoveRotation(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Quaternion dir)
		{
			pos[0] = DirectX::SimpleMath::Vector3::Transform(startPos[0],world * DirectX::SimpleMath::Matrix::CreateFromQuaternion(dir));
			pos[1] = DirectX::SimpleMath::Vector3::Transform(startPos[1], world * DirectX::SimpleMath::Matrix::CreateFromQuaternion(dir));
			pos[2] = DirectX::SimpleMath::Vector3::Transform(startPos[2], world * DirectX::SimpleMath::Matrix::CreateFromQuaternion(dir));

			plane.Rotation(dir, pos[0]);
		}
		DirectX::SimpleMath::Vector3 pos[3];
		DirectX::SimpleMath::Vector3 startPos[3];
		Plane plane;
	};


protected:
	Collision();
	~Collision();
	static bool HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, DirectX::SimpleMath::Vector3* repulsionVel = nullptr);
	// �����ƕ��ʂ̓����蔻��
	static bool HitCheck_Segment_Plane(Segment& segment, Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// �����Ƌ��̓����蔻��
	static bool HitCheck_Segment_Sphere(Segment& segment, Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// �����ƎO�p�`�̓����蔻��
	static bool HitCheck_Segment_Triangle(Segment& segment, Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// �O�p�`�̔C�ӂ̓_���O�p�`���ɑ��݂��邩�ǂ���
	static bool Triangle_CheckInner(Triangle& triangle, DirectX::SimpleMath::Vector3& point);
	// ���ƕ��ʂ̓����蔻��
	static bool HitCheck_Sphere_Plane(Sphere& sphere, Plane& plane, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	// ���ƎO�p�`�̏Փ˔���
	static bool HitCheck_Sphere_Triangle(Sphere& sphere, Triangle& triangle, DirectX::SimpleMath::Vector3* hit_pos = nullptr);
	static bool HitCheck_Sphere_Triagnles(Triangle triangle[], int triangle_index, Sphere& sphere, DirectX::SimpleMath::Vector3* hit_pos = nullptr);

	/// <summary>
	/// ���ʂ̕�����
	/// </summary>
	/// <param name="plane">����</param>
	/// <param name="p">�_</param>
	/// <returns>���ʂƓ_�̋���</returns>
	static float Plane_Length(Plane& plane, DirectX::SimpleMath::Vector3& p)
	{
		float l;
		l = plane.a * p.x + plane.b * p.y + plane.c * p.z + plane.d;
		return l;
	}

public:
	static bool HitCheck(Entity* entity, Entity* entity2, CollisionData* data = nullptr);
};
