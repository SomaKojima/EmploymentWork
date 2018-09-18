/// <summary>
/// BoxCollisionComponent.cpp
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../pch.h"
#include "BoxCollisionComponent.h"
#include "SphereCollisionComponent.h"

/// <summary>
/// ���O���
/// </summary>
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoxCollisionComponent::BoxCollisionComponent(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 radius)
	:
	m_center(center),
	m_radius(radius),
	m_obj(nullptr)
{
	m_name = "BoxCollision";
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoxCollisionComponent::~BoxCollisionComponent()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="entity">����</param>
void BoxCollisionComponent::Initialize(Entity & entity)
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="entity">����</param>
/// <param name="timer">����</param>
void BoxCollisionComponent::Update(Entity & entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// �x���X�V
/// </summary>
/// <param name="m_entity">����</param>
/// <param name="timer">����</param>
void BoxCollisionComponent::LateUpdate(Entity & m_entity, DX::StepTimer const & timer)
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void BoxCollisionComponent::Draw(Entity & entity, Game * game)
{
	Matrix world = entity.GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugBox>(game->GetDevice(), m_center, m_radius);
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
void BoxCollisionComponent::Finalize(Entity & entity)
{
}