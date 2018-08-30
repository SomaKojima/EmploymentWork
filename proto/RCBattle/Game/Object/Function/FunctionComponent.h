/// <summary>
/// FunctionComponent.h
/// 
/// 制作日:2018/8/25
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include <vector>
#include <map>
#include <typeinfo>

/// <summary>
/// 前方宣言
/// </summary>
class Component;

/// <summary>
/// コンポーネント機能のクラス
/// </summary>
class FunctionComponent
{
public:
	// コンポーネントの追加
	template<class T>
	inline void AddComponent(T* component);

	template<class T>
	inline T* GetComponent();

protected:
	std::map<const char*, Component*> m_componentMap;	// コンポーネントのコンテナ
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
