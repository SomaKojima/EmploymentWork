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
#include <list>
#include "../../StepTimer.h"
#include "../Collision/CCell.h"

#include "Function/FunctionComponent.h"
#include "../Utility/BidirectionalList.h"

#include "../Data/Data.h"

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
		m_dir(DirectX::SimpleMath::Quaternion::Identity),
		m_vel(DirectX::SimpleMath::Vector3::Zero),
		m_accel(DirectX::SimpleMath::Vector3::Zero),
		m_pos(DirectX::SimpleMath::Vector3::Zero),
		m_radius(0.0f),
		m_world(DirectX::SimpleMath::Matrix::Identity),
		m_local(DirectX::SimpleMath::Matrix::Identity)
	{};

	~Transform() {};
public:
	// setter
	void SetDir(DirectX::SimpleMath::Quaternion dir) { m_dir = dir; }
	void SetAngle(DirectX::SimpleMath::Vector3 &angle) 
	{ 
		m_dir = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(angle.y, angle.x, angle.z); 
	}
	//void SetVel(DirectX::SimpleMath::Vector3 &vel) { m_vel = vel; }
	void SetLocalVel(DirectX::SimpleMath::Vector3 &vel) { 
		m_vel = DirectX::SimpleMath::Vector3::Transform(vel, m_dir); 
	}
	void SetAccel(DirectX::SimpleMath::Vector3 &accel) { m_accel = accel; }
	void SetPos(DirectX::SimpleMath::Vector3 pos) { m_pos = pos; }
	void SetRadius(float radius) { m_radius = radius; }
	void SetWorld(DirectX::SimpleMath::Matrix& world) {
		m_world = world;
		m_pos = m_world.Translation();
	}
	void SetLocal(DirectX::SimpleMath::Matrix& local) { m_local = local; }

	// getter
	DirectX::SimpleMath::Quaternion& GetDir() { return m_dir; }
	//DirectX::SimpleMath::Vector3& GetVel() { return m_vel; }
	DirectX::SimpleMath::Vector3& GetLocalVel() { 
		DirectX::SimpleMath::Quaternion q;
		m_dir.Conjugate(q);
		return DirectX::SimpleMath::Vector3::Transform(m_vel, q); 
	}
	DirectX::SimpleMath::Vector3& GetAccel() { return m_accel; }
	DirectX::SimpleMath::Vector3& GetPos() { return m_pos; }
	float& GetRadius() { return m_radius; }
	DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	DirectX::SimpleMath::Matrix& GetLocal() { return m_local; }

private:
	DirectX::SimpleMath::Quaternion m_dir;		// ����			
	DirectX::SimpleMath::Vector3 m_vel;			// ���x
	DirectX::SimpleMath::Vector3 m_accel;		// �����x
	DirectX::SimpleMath::Vector3 m_pos;			// ���W
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
	void SetName(char* name) { m_name = name; }
	void SetTag(Tag tag) { m_tag = tag; }
	void SetParent(Entity* parent) { m_parent = parent; }

	// �Q�b�^�[
	char* GetName() { return m_name; }
	Tag GetTag() { return m_tag; }
	Transform& GetTrans() { return m_transform; }
	Entity& GetParent() { return *m_parent; }
	std::list<Entity*>* GetChildList() { return &m_childlist; }
	OBJECT_FOR_TREE* GetOFT() { return m_pOFT; }
	EntityOfTree* GetEOF() { return m_pEOF; }

private:
	char* m_name;								// ���O
	Tag m_tag;									// �^�O
	Transform m_transform;						// �ό`�̏��

	Entity* m_parent;							// �e�̃|�C���^

	std::list<Entity*> m_childlist;				// �q�̃R���e�i

	OBJECT_FOR_TREE* m_pOFT;					// �����蔻��p
	EntityOfTree* m_pEOF;						// ���̂����X�g�ŉ񂷗p
};