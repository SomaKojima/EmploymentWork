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
#include "../Component/SphereCollisionComponent.h"
#include "../Component/BoxCollisionComponent.h"

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

bool Collision::HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, DirectX::SimpleMath::Vector3* repulsionVel)
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

/// <summary>
/// �����蔻������߂�
/// </summary>
/// <param name="entity">����</param>
/// <param name="repulsionVel">�������x</param>
/// <returns>�����蔻��</returns>
bool Collision::HitCheck(Entity * entity, Entity* entity2, Vector3* repulsionVel)
{
	if(!entity || !entity2)
	{
		return false;
	}
	SphereCollisionComponent* sphereCollision = entity->GetComponent<SphereCollisionComponent>();
	SphereCollisionComponent* sphereCollision2 = entity2->GetComponent<SphereCollisionComponent>();

	if (sphereCollision && sphereCollision2)
	{
		return HitCheck_Sphere(entity, *sphereCollision, entity2, *sphereCollision2, repulsionVel);
	}

	return false;
}
