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
#include "MeshCollisionComponent.h"

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
MeshCollisionComponent::MeshCollisionComponent(wchar_t* file)
	:
	m_file(file)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MeshCollisionComponent::~MeshCollisionComponent()
{
}

void MeshCollisionComponent::Update(DX::StepTimer const & timer)
{
}

void MeshCollisionComponent::LateUpdate(DX::StepTimer const & timer)
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="entity">����</param>
/// <param name="game">�Q�[��</param>
void MeshCollisionComponent::Draw(Game * game)
{
	if (m_obj == nullptr)
	{
		// �f�o�b�O�p�����蔻�胂�f���̍쐬
		m_obj = std::make_unique<DebugMesh>(game->GetDevice(), m_file);
	}
	else
	{
		m_obj->DrawCollision(game->GetContext(), game->GetView(), game->GetProjection());
	}
}

/// <summary>
/// �I��
/// </summary>
/// <param name="entity">����</param>
void MeshCollisionComponent::Finalize()
{
	m_obj.reset();
}