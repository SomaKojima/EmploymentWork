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

/// <summary>
/// �����蔻��N���X
/// </summary>
class Collision
{
protected:
	Collision();
	~Collision();
	static bool HitCheck_Sphere(Entity* entity, SphereCollisionComponent& sphere, Entity* entity2, SphereCollisionComponent& sphere2, DirectX::SimpleMath::Vector3* repulsionVel = nullptr);

public:
	static bool HitCheck(Entity* entity, Entity* entity2, DirectX::SimpleMath::Vector3* repulsionVel = nullptr);
};
