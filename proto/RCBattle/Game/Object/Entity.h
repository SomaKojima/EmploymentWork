/// <summary>
/// Entity.h
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
#include <vector>
#include <map>
#include <typeinfo>
#include "../../StepTimer.h"
#include "../Collision/CCell.h"

#include "Function/FunctionComponent.h"
#include "../Utility/BidirectionalList.h"

/// <summary>
/// �N���X�̐錾
/// </summary>
class Game;
class Component;
class EntityOfTree;

// �ό`�̏��
class Transform
{
	friend Entity;
public:
	Transform() :
		m_angle(DirectX::SimpleMath::Vector3::Zero),
		m_dir(DirectX::SimpleMath::Quaternion::Identity),
		m_vel(DirectX::SimpleMath::Vector3::Zero),
		m_trans(DirectX::SimpleMath::Vector3::Zero),
		m_radius(0.0f),
		m_world(DirectX::SimpleMath::Matrix::Identity),
		m_local(DirectX::SimpleMath::Matrix::Identity)
	{};

	~Transform() {};
public:
	void SetDir(DirectX::SimpleMath::Quaternion dir) { m_dir = dir; }
	void SetAngle(DirectX::SimpleMath::Vector3 &angle)
	{
		m_angle = angle;
		m_dir = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_angle.z) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), m_angle.y) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(1.0f, 0.0f, 0.0f), m_angle.x);
	}
	void SetVel(DirectX::SimpleMath::Vector3 &vel) { m_vel = vel; }
	void SetTrans(DirectX::SimpleMath::Vector3 trans) { m_trans = trans; }
	void SetRadius(float radius) { m_radius = radius; }
	void SetWorld(DirectX::SimpleMath::Matrix& world) { m_world = world; }
	void SetLocal(DirectX::SimpleMath::Matrix& local) { m_local = local; }

	DirectX::SimpleMath::Quaternion GetDir() { return m_dir; }
	DirectX::SimpleMath::Vector3 GetAngle() { return m_angle; }
	DirectX::SimpleMath::Vector3 GetVel() { return m_vel; }
	DirectX::SimpleMath::Vector3 GetTrans() { return m_trans; }
	float GetRadius() { return m_radius; }
	DirectX::SimpleMath::Matrix GetWorld() { return m_world; }
	DirectX::SimpleMath::Matrix GetLocal() { return m_local; }

private:
	DirectX::SimpleMath::Quaternion m_dir;		// ����
	DirectX::SimpleMath::Vector3 m_angle;		// �p�x				
	DirectX::SimpleMath::Vector3 m_vel;			// ���x
	DirectX::SimpleMath::Vector3 m_trans;		// �ړ�
	float m_radius;

	DirectX::SimpleMath::Matrix m_world;		// ���[���h���W
	DirectX::SimpleMath::Matrix m_local;		// ���[�J�����W
};

/// <summary>
///�I�u�W�F�N�g�N���X 
/// </summary>
class Entity : public FunctionComponent
{
public:
	Entity();
	~Entity();

	// ������
	void Initialize();
	// �X�V
	bool Update(DX::StepTimer const& timer);
	// �I��
	void Finalize();
	// ����
	void Destroy();

	// �q�̒ǉ�
	Entity* AddChild(Entity* entity);
	// �q�̍폜
	void DeleteChild();

	// �}�g���N�X�̍X�V
	void UpdateMatrix();

	//�@�v���p�e�B
	// �Z�b�^�[
	void SetParent(Entity* parent) { m_parent = parent; }

	// �Q�b�^�[
	Transform& GetTrans() { return m_transform; }
	Entity& GetParent() { return *m_parent; }
	OBJECT_FOR_TREE* GetOFT() { return m_pOFT; }
	EntityOfTree* GetEOF() { return m_pEOF; }

private:
	Transform m_transform;						// �ό`�̏��

	Entity* m_parent;							// �e�̃|�C���^

	std::vector<Entity*> m_childVector;			// �q�̃R���e�i

	OBJECT_FOR_TREE* m_pOFT;					// �����蔻��p
	EntityOfTree* m_pEOF;						// ���̂����X�g�ŉ񂷗p
};