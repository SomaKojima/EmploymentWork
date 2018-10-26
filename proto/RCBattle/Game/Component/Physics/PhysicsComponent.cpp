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
	//Vector3 accel = m_me->GetTrans().GetAccel();

	if(m_isFriction)
	{
		vel *= m_friction;
		//accel *= m_friction;
	}
	
	if(m_isGravity)
	{
		//Quaternion inverse;
		//m_me->GetTrans().GetDir().Inverse(inverse);
		Vector3 gravity = (m_gravityDir * (m_gravity / (60 * 60)));
		Quaternion q;
		m_me->GetTrans().GetDir().Conjugate(q);
		gravity = Vector3::Transform(gravity, q);
		//gravity = Vector3::Transform(gravity, inverse);
		vel += gravity;
	}

	m_me->GetTrans().SetVel(vel);
	//_me->GetTrans().SetAccel(accel);
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

	// �����̏����擾
	SphereCollisionComponent* sphere = m_me->GetComponent<SphereCollisionComponent>();
	PlaneCollisionComponent* plane = m_me->GetComponent<PlaneCollisionComponent>();
	MeshCollisionComponent* mesh = m_me->GetComponent<MeshCollisionComponent>();
	/// //////////////////////////////
	//���˕Ԃ���v�Z
	/// //////////////////////////////

	// ���Ɩ�
	if (data->typeFlag & CollisionType::PLANE)
	{
		// ����̏����擾
		PlaneCollisionComponent* plane2 = collide.GetComponent<PlaneCollisionComponent>();
		// �v�Z
		if(sphere)sphere->HitBackExecution(plane2->GetTriangle(), data->hitPos);
	}
}
