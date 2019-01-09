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

class EntityList : public BidirectionalList<EntityOfTree, Entity>::RegisterTo
{
public:
	EntityList() {}
	~EntityList() {}
};


class EntityVector : public SingletonBase<EntityVector>
{
public:
	EntityVector();
	~EntityVector();

	void Update(DX::StepTimer const& timer);
	void Render(Game* game);
	void Finalize();

	void Add(Entity* entity);
	void AddDestory(Entity* entity);

	Entity* GetEntity(char* name);
	Entity* CheckChildList(std::list<Entity*>* childList, char* name);

private:
	void FinalizeList(EntityList* list);
private:
	
	// ���̂̃R���e�i
	EntityList* m_vector;
	// ���̂̃R���e�i
	EntityList* m_add;
	// ���̂̃R���e�i
	std::list<Entity*> m_destroybuf;
	EntityList* m_destroy;
};