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
	CollisionComponent::Update(timer);
}

void SphereCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
	m_sphere.center = Vector3::Transform(m_center, (m_me->GetTrans().world.Get()));
}

/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void SphereCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().world.Get() * Matrix::CreateTranslation(m_center);
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

void SphereCollisionComponent::HitBack(const Collision::Triangle * triangle, DirectX::SimpleMath::Vector3 & hitPos)
{
	// ���x���擾
	Vector3 vec = m_me->GetTrans().vel.GetLocal();

	// �ʂ̖@��
	Vector3 normal(triangle->plane.a, triangle->plane.b, triangle->plane.c);

	// �@���̌����̃x�N�g�����Ȃ���(�v���C���[�̌����ɍ��킹��E���[�J�����W�ɂ���)
	Quaternion q;
	m_me->GetTrans().dir.Get().Conjugate(q);

	// �ǂ���
	Vector3 normal2 = Vector3::Transform(normal, q);

	float l = vec.Dot(normal2);
	Vector3 w_vec;
	if (l <= 0)
	{
		w_vec = vec - l * normal2;
	}
	else
	{
		w_vec = vec;
	}

	// ���W�̍X�V
	Vector3 pos = m_me->GetTrans().pos.Get();
	pos += Vector3::Transform(w_vec, m_me->GetTrans().dir.Get());

	//m_me->GetTrans().SetPos(pos);

	m_me->GetTrans().vel.SetLocal(w_vec);
}

