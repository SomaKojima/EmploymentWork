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
#include <vector>
#include <map>
#include <typeinfo>

/// <summary>
/// �O���錾
/// </summary>
class Component;

/// <summary>
/// �R���|�[�l���g�@�\�̃N���X
/// </summary>
class FunctionComponent
{
public:
	// �R���|�[�l���g�̒ǉ�
	template<class T>
	inline void AddComponent(T* component);

	template<class T>
	inline T* GetComponent();

protected:
	std::map<const char*, Component*> m_componentMap;	// �R���|�[�l���g�̃R���e�i
};

template<class T>
inline void FunctionComponent::AddComponent(T* component)
{
	const type_info& id = typeid(component);
	const char* name = id.name();
	m_componentMap[name] = component;
}

template<class T>
inline T * FunctionComponent::GetComponent()
{
	T* sub = nullptr;
	Component* component = nullptr;
	const char* name = typeid(T*).name();
	if (m_componentMap[name] != nullptr)
	{
		component = m_componentMap.find(name)->second;
		sub = dynamic_cast<T*>(component);
		if (sub)
		{
			return sub;
		}
	}
	else
	{
		m_componentMap.erase(name);
	}
	return nullptr;
}
