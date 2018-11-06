/// <summary>
/// SphereCollisionComponent.h
/// 
/// �����:2018/7/4
/// �����:���� �D�V
/// </summary>

/// <summary>
/// ���d�C���N���[�h�̖h�~
/// </summary>
#pragma once

/// <summary>
/// �w�b�_�̃C���N���[�h
/// </summary>
#include <list>
#include "CollisionComponent.h"
#include "../../DebugCollision/DebugMesh.h"
#include "../../Collision/Collision.h"

/// <summary>
/// ���̓����蔻��̃R���|�[�l���g�N���X
/// </summary>
class MeshCollisionComponent : public CollisionComponent
{
public:
	MeshCollisionComponent(wchar_t* file);
	~MeshCollisionComponent();

	// �X�V
	void Update(DX::StepTimer const& timer) override;
	// �x���X�V
	void LateUpdate(DX::StepTimer const& timer) override;
	// �`��
	void Draw(Game* game) override;
	// �I��
	void Finalize() override;

	const std::list<Collision::Triangle>* GetTriangleList() override { return &m_triangles; }

	Collision::CollisionType GetShapeType() { return Collision::CollisionType::TRIANGLE; }

private:
	wchar_t* m_file;
	std::list<Collision::Triangle> m_triangles;

	// �����蔻��̕\���p�I�u�W�F�N�g
	std::unique_ptr<DebugMesh> m_obj;
};