/// <summary>
/// FunctionComponent.h
/// 
/// �����:2018/8/25
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
#include <typeinfo>
#include "../../../StepTimer.h"

/// <summary>
/// �O���錾
/// </summary>
class Component;
class Entity;
class Game;
class CollisionData;

/// <summary>
/// �R���|�[�l���g�@�\�̃N���X
/// </summary>
class FunctionComponent
{
public:
	FunctionComponent(Entity* me) : m_me(me){}
	virtual ~FunctionComponent() { m_me = nullptr; }
public:
	void InitializeComponent();
	// �R���|�[�l���g�̍X�V
	bool UpdateComponent(DX::StepTimer const& timer);
	// �R���|�[�l���g�̒x���X�V
	bool LateComponentUpdate(DX::StepTimer const& timer);
	// �����蔻��̏���
	void OnCollideComponent(Entity& entity, CollisionData& data);
	// �R���|�[�l���g�̕`��
	void DrawCompoennt(Game* game);
	// �R���|�[�l���g�̏I��
	void FinalizeComponent();

	// �R���|�[�l���g�̒ǉ�
	void AddComponent(Component* component);

	template<class T>
	inline T* GetComponent();

protected:
	std::list<Component*> m_componentlist;	// �R���|�[�l���g�̃R���e�i

private:
	Entity* m_me;
};

template<class T>
inline T * FunctionComponent::GetComponent()
{
	T* sub = nullptr;
	for (auto ite = m_componentlist.begin(); ite != m_componentlist.end(); ite++)
	{
		sub = dynamic_cast<T*>((*ite));
		if (sub)
		{
			return sub;
		}
	}
	return nullptr;
}
