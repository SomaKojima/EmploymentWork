#pragma once

#include <vector>
#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Utility/BidirectionalList.h"

class Entity;

class EntityOfTree : public BidirectionalList<EntityOfTree, Entity>
{
public:
	EntityOfTree(Entity* obj) : BidirectionalList(obj) {}
	~EntityOfTree() {}

};

class EntityCell : public BidirectionalList<EntityOfTree, Entity>::RegisterTo
{
public:
	EntityCell() {}
	~EntityCell() {}
};


class EntityVector
{
public:
	EntityVector();
	~EntityVector();

	void Initialize();
	void Update(DX::StepTimer const& timer);
	void Render(Game* game);
	void Finalize();

	void Add(Entity* entity);
	/*void AddDestory(Entity* entity);

	Entity* GetVector() { return m_vector; }
	void SetVector(Entity* _vector) { m_vector = _vector; }*/

	static EntityVector* GetInstance();
	static void Lost();

private:
	static EntityVector* m_sEntityVector;
	
	// 実体のコンテナ
	//Entity* m_vector;
	EntityCell* m_vector;
	// 実体のコンテナ
	//Entity* m_destroy;
	//EntityCell* m_destroy;
};