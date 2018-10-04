/// <summary>
/// PhysicsComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "PhysicsComponent.h"
#include "../../Collision/Collision.h"

#include "../ComponentLib.h"

/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="entityVector">���̂̃R���e�i�̃|�C���^</param>
PhysicsComponent::PhysicsComponent()
	:
	m_gravity(9.8f),
	m_friction(Vector3(0.9f, 1.0f, 0.9f)),
	m_gravityDir(Vector3::Down),
	m_isFriction(true),
	m_isGravity(true)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PhysicsComponent::~PhysicsComponent()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="entity">����</param>
void PhysicsComponent::Initialize()
{
	m_spherelist = m_me->GetComponentList<SphereCollisionComponent>();
	m_planelist = m_me->GetComponentList<PlaneCollisionComponent>();
	int a = 0;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="entity">����</param>
/// <param name="timer">����</param>
void PhysicsComponent::Update(DX::StepTimer const& timer)
{
	Vector3 vel = m_me->GetTrans().GetVel();

	if(m_isFriction)
	{
		vel *= m_friction;
	}
	
	if(m_isGravity)
	{
		Quaternion inverse;
		m_me->GetTrans().GetDir().Inverse(inverse);
		Vector3 gravity = (m_gravityDir * (m_gravity / (60 * 60)));
		gravity = Vector3::Transform(gravity, inverse);
		vel += gravity;
	}

	m_me->GetTrans().SetVel(vel);
}

/// <summary>
/// �x���X�V
/// </summary>
/// <param name="m_entity">����</param>
/// <param name="timer">����</param>
void PhysicsComponent::LateUpdate(DX::StepTimer const & timer)
{
}

void PhysicsComponent::OnCollide(Entity& collide, CollisionData* data)
{
	PhysicsComponent* collidePhysics = collide.GetComponent<PhysicsComponent>();
	/// //////////////////////////////
	//���˕Ԃ���v�Z
	/// //////////////////////////////

	//// ���Ɩ�
	//if (data->typeFlag & CollisionType::SPHERE_PLANE)
	//{
	//	SphereCollisionComponent* sphere = CheckSphereList(m_me ,data);
	//	PlaneCollisionComponent* collidePlane = nullptr;
	//	if (sphere)
	//	{
	//		collidePlane = CheckPlaneList(&collide, data);
	//		// �v�Z
	//		Vector3 hitPosVec = sphere->HitPlanePosToVec(collidePlane, data->hitPos);
	//	}
	//	else
	//	{
	//		sphere = CheckSphereList(&collide, data);
	//		collidePlane = CheckPlaneList(m_me, data);
	//		// �v�Z
	//	}
	//}

	//// ���Ƌ�
	//if (data->typeFlag & CollisionType::SPHERE_SPHERE)
	//{
	//	SphereCollisionComponent* sphere = CheckSphereList(m_me, data);
	//	/*if ()
	//	{

	//	}*/
	//}
	//SphereCollisionComponent* sphere = CheckSphereList(m_me, data);
	//if (sphere)
	//{
	//	Vector3 hitPosVec = sphere->HitPosToVec(data->hitPos);
	//	//Vecctor3 diffVec = m_me->GetTrans().GetVel() - hitPosVec;
	//	//m_me->GetTrans().SetVel(-hitPosVec);
	//}
}

SphereCollisionComponent * PhysicsComponent::CheckSphereList(Entity* entity, CollisionData * data)
{
	SphereCollisionComponent* sphere = entity->GetComponent<SphereCollisionComponent>(data->sphere[0]);
	if (!sphere)
	{
		sphere = entity->GetComponent<SphereCollisionComponent>(data->sphere[1]);
	}
	return sphere;
}

PlaneCollisionComponent * PhysicsComponent::CheckPlaneList(Entity* entity, CollisionData * data)
{
	PlaneCollisionComponent* plane = entity->GetComponent<PlaneCollisionComponent>(data->plane[0]);
	if (!plane)
	{
		plane = entity->GetComponent<PlaneCollisionComponent>(data->plane[1]);
	}
	return plane;
}
