#pragma once

#include <vector>
#include "../../StepTimer.h"
#include "../../Game.h"
#include "../Utility/Utility.h"
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


class EntityVector : public SingletonBase<EntityVector>
{
public:
	EntityVector();
	~EntityVector();

	void Initialize();
	void Update(DX::StepTimer const& timer);
	void Render(Game* game);
	void Finalize();

	void Add(Entity* entity);
	void AddDestory(Entity* entity);

	Entity* GetEntity(char* name);
	Entity* CheckChildList(std::list<Entity*>* childList, char* name);

private:
	
	// ���̂̃R���e�i
	EntityCell* m_vector;
	// ���̂̃R���e�i
	EntityCell* m_destroy;
};