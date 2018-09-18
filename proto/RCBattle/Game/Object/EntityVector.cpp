#include "../../pch.h"
#include "EntityVector.h"
#include "Entity.h"

EntityVector::EntityVector()
	:
	m_vector(new EntityCell()),
	m_destroy(new EntityCell())
{
}

EntityVector::~EntityVector()
{
	delete m_vector;
	delete m_destroy;
}

void EntityVector::Initialize()
{
	EntityOfTree* entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->Initialize();
		entity = entity->GetNext();
	}
}

void EntityVector::Update(DX::StepTimer const& timer)
{

	EntityOfTree* entity = nullptr;
	EntityOfTree* entityBuf = nullptr;

	// 追加リストのオブジェクトを加える
	entity = m_destroy->GetTop();
	Entity* obj = nullptr;
	while (entity)
	{
		entityBuf = entity->GetNext();
		obj = entity->GetObj();
		entity = entityBuf;

		obj->Finalize();
		delete obj;
	}

	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->UpdateComponent(*entity->GetObj(), timer);
		entity = entity->GetNext();
	}

	// 当たり判定を取る
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->HitCheck();

	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->LateComponentUpdate(*entity->GetObj(), timer);
		entity = entity->GetNext();
	}
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->Update(timer);
		entity = entity->GetNext();
	}
}
 
void EntityVector::Render(Game* game)
{
	EntityOfTree* entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->Draw(game);
		entity = entity->GetNext();
	}
}

void EntityVector::Finalize()
{
	EntityOfTree* entity = m_vector->GetTop();
	EntityOfTree* entityBuf;
	Entity* obj = nullptr;
	while (entity)
	{
		entityBuf = entity->GetNext();
		obj = entity->GetObj();
		entity = entityBuf;

		obj->Finalize();
		delete obj;
	}

	// 追加リストのオブジェクトを加える
	entity = m_destroy->GetTop();
	while (entity)
	{
		entityBuf = entity->GetNext();
		obj = entity->GetObj();
		entity = entityBuf->GetNext();

		obj->Finalize();
		delete obj;
	}
}

void EntityVector::Add(Entity * entity)
{
	if (!entity)
	{
		return;
	}
	m_vector->Add(entity->GetEOF());
}

void EntityVector::AddDestory(Entity * entity)
{
	if (!entity)
	{
		return;
	}
	entity->GetEOF()->Remove();
	m_destroy->Add(entity->GetEOF());
}