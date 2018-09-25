/// <summary>
/// BoxCollisionComponent.cpp
/// 
/// �����:2018/7/12
/// �����:���� �D�V
/// </summary>

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include "../../../pch.h"
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
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoxCollisionComponent::~BoxCollisionComponent()
{
}


/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void BoxCollisionComponent::Draw(Game * game)
{
	Matrix world = m_me->GetTrans().GetWorld() * Matrix::CreateTranslation(m_center);
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		//m_obj = std::make_unique<DebugBox>(game->GetDevice(), m_center, m_radius);
	}
	else
	{
		m_obj->Draw(game->GetContext(), *game->GetStates(), world, game->GetView(), game->GetProjection());
	}
}
