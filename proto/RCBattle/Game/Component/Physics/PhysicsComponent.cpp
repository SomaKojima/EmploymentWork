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
	m_isFriction(true),
	m_isGravity(true),
	sphere(nullptr),
	box(nullptr)
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
	SphereCollisionComponent* buffSphere = m_me->GetComponent<SphereCollisionComponent>();
	BoxCollisionComponent* buffBox = m_me->GetComponent<BoxCollisionComponent>();
	if (buffSphere)
	{
		sphere = buffSphere;
	}
	if (buffBox)
	{
		box = buffBox;
	}
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
		vel.x *= 0.9f;
		vel.z *= 0.9f;
	}
	if(m_isGravity)
	{
		vel.y -= (m_gravity / (60 * 60));
	}

	Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().GetWorld()) + vel;
	if (pos.y <= 1.5f)
	{
		m_me->GetTrans().SetWorld(m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(Vector3(0.0f, -pos.y + 1.5f, 0.0f)));
		vel.y = 0.0f;
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
	Vector3 pos = m_me->GetTrans().GetPos();

	pos += m_repulsionVel;
	m_me->GetTrans().SetPos(pos);
	m_repulsionVel = Vector3::Zero;
}

void PhysicsComponent::OnCollide(Entity& collide, CollisionData& data)
{
	//Collision::HitCheck(m_me, &collide, &m_repulsionVel);
}