/// <summary>
/// SphereCollisionComponent.cpp
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
#include "SphereCollisionComponent.h"
#include "BoxCollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="center">���S���W</param>
/// <param name="radius">���a</param>
SphereCollisionComponent::SphereCollisionComponent(DirectX::SimpleMath::Vector3 center, float radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_sphere.radius = radius;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SphereCollisionComponent::~SphereCollisionComponent()
{

}

void SphereCollisionComponent::Update(DX::StepTimer const & timer)
{
}

void SphereCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
	m_sphere.center = Vector3::Transform(m_center, (m_me->GetTrans().GetWorld()));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void SphereCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugSphere>(game->GetDevice(), m_center, m_radius);
	}
	else
	{
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
void SphereCollisionComponent::Finalize()
{
	m_obj.reset();
}

DirectX::SimpleMath::Vector3 SphereCollisionComponent::HitPlanePosToVec(PlaneCollisionComponent* plane, DirectX::SimpleMath::Vector3& hitPos)
{
	// ���x���擾
	Vector3 vec = m_me->GetTrans().GetVel();
	Vector3 accel = m_me->GetTrans().GetAccel();

	// �ʂ̖@��
	Vector3 normal(plane->GetTriangle()->plane.a, plane->GetTriangle()->plane.b, plane->GetTriangle()->plane.c);

	Vector3 hitPosVec = m_sphere.center - hitPos;
	hitPosVec.Normalize();
	Vector3 a = m_sphere.center - (hitPosVec * m_sphere.radius) - hitPos;
	float length = a.Length();

	// �@���̌����̃x�N�g�����Ȃ���
	Quaternion inverse;
	m_me->GetTrans().GetDir().Inverse(inverse);
	Vector3 normal2 = Vector3::Transform(normal, inverse);

	Vector3 w_vec = vec - vec.Dot(normal2) * normal2;
	Vector3 w_accel = accel - accel.Dot(normal) * normal;

	Vector3 vec2 = w_vec;
	Vector3 accel2 = w_accel + (hitPosVec * length);

	m_me->GetTrans().SetVel(vec2);
	m_me->GetTrans().SetAccel(accel2);

	// �ǂɂЂ���
	return Vector3::Zero;
}

