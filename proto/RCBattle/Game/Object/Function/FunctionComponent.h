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
#include <list>
#include <typeinfo>
#include "../../../StepTimer.h"

/// <summary>
/// 前方宣言
/// </summary>
class Component;
class Entity;
class Game;
class CollisionData;

/// <summary>
/// コンポーネント機能のクラス
/// </summary>
class FunctionComponent
{
public:
	FunctionComponent(Entity* me) : m_me(me){}
	virtual ~FunctionComponent() { m_me = nullptr; }
public:
	void InitializeComponent();
	// コンポーネントの更新
	bool UpdateComponent(DX::StepTimer const& timer);
	// コンポーネントの遅延更新
	bool LateComponentUpdate(DX::StepTimer const& timer);
	// 当たり判定の処理
	void OnCollideComponent(Entity& entity, CollisionData& data);
	// コンポーネントの描画
	void DrawCompoennt(Game* game);
	// コンポーネントの終了
	void FinalizeComponent();

	// コンポーネントの追加
	void AddComponent(Component* component);

	template<class T>
	inline T* GetComponent();

protected:
	std::list<Component*> m_componentlist;	// コンポーネントのコンテナ

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
