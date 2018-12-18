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

#include "Transform.h"

/// <summary>
/// �N���X�̐錾
/// </summary>
class Game;
class Component;
class EntityOfTree;

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

	//�@�v���p�e�B
	// �Z�b�^�[
	void SetName(char* name) { m_name = name; }
	void SetTag(Tag tag) { m_tag = tag; }
	void SetParent(Entity* parent) { m_parent = parent; }

	// �Q�b�^�[
	char* GetName() { return m_name; }
	Tag GetTag() { return m_tag; }
	Transform& GetTrans() { return m_transform; }
	Entity* GetParent() { return m_parent; }
	std::list<Entity*>* GetChildList() { return &m_childlist; }
	Entity* GetChild(char* name);
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

