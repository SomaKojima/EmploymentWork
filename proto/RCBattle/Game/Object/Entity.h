/// <summary>
/// Entity.h
/// 
/// 制作日:2018/7/4
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
#include "../../StepTimer.h"
#include "../Collision/CCell.h"

#include "Function/FunctionComponent.h"
#include "../Utility/BidirectionalList.h"

#include "../Data/Data.h"

#include "Transform.h"

/// <summary>
/// クラスの宣言
/// </summary>
class Game;
class Component;
class EntityOfTree;

/// <summary>
///オブジェクトクラス 
/// </summary>
class Entity : public FunctionComponent
{
	
public:
	Entity();
	~Entity();

	// 初期化
	void Initialize();
	// 更新
	bool Update(DX::StepTimer const& timer);
	// 終了
	void Finalize();
	// 消す
	void Destroy();

	// 子の追加
	Entity* AddChild(Entity* entity);
	// 子の削除
	void DeleteChild();

	//　プロパティ
	// セッター
	void SetName(char* name) { m_name = name; }
	void SetTag(Tag tag) { m_tag = tag; }
	void SetParent(Entity* parent) { m_parent = parent; }

	// ゲッター
	char* GetName() { return m_name; }
	Tag GetTag() { return m_tag; }
	Transform& GetTrans() { return m_transform; }
	Entity* GetParent() { return m_parent; }
	std::list<Entity*>* GetChildList() { return &m_childlist; }
	Entity* GetChild(char* name);
	OBJECT_FOR_TREE* GetOFT() { return m_pOFT; }
	EntityOfTree* GetEOF() { return m_pEOF; }

private:
	char* m_name;								// 名前
	Tag m_tag;									// タグ
	Transform m_transform;						// 変形の情報

	Entity* m_parent;							// 親のポインタ

	std::list<Entity*> m_childlist;				// 子のコンテナ

	OBJECT_FOR_TREE* m_pOFT;					// 当たり判定用
	EntityOfTree* m_pEOF;						// 実体をリストで回す用
};

