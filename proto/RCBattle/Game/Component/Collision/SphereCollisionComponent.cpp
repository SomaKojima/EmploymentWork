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
	// �x�N�g�����擾�i�����̌v�Z�ς܂���j
	Vector3 vec = Vector3::Transform(m_me->GetTrans().GetVel(), m_me->GetTrans().GetDir());

	// �ʂ̖@��
	Vector3 normal(plane->GetTriangle()->plane.a, plane->GetTriangle()->plane.b, plane->GetTriangle()->plane.c);

	Vector3 hitPosVec = m_sphere.center - hitPos;
	hitPosVec.Normalize();
	Vector3 a = m_sphere.center - (hitPosVec * m_sphere.radius) - hitPos;
	float length = a.Length();

	// �@���̌����̃x�N�g�����Ȃ���
	Vector3 w = vec - vec.Dot(normal) * normal;

	Quaternion inverse;
	m_me->GetTrans().GetDir().Inverse(inverse);

	Vector3 vel = Vector3::Transform(w + (hitPosVec * length), inverse);

	m_me->GetTrans().SetVel(vel);


	// �ǂɂЂ���

	return Vector3::Zero;
}

