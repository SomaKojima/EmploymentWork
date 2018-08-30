#include "../../pch.h"
#include "EntityVector.h"
#include "Entity.h"

EntityVector* EntityVector::m_sEntityVector = nullptr;

EntityVector::EntityVector()
	:
	m_vector(nullptr),
	m_destroy(nullptr)
{
}

EntityVector::~EntityVector()
{
}

void EntityVector::Initialize()
{
	Entity* entity = m_vector;
	while (entity)
	{
		entity->Initialize();
		entity = entity->GetNext();
	}
}

void EntityVector::Update(DX::StepTimer const& timer)
{

	Entity* entity = nullptr;
	Entity* entityBuf = nullptr;

	// 追加リストのオブジェクトを加える
	entity = m_destroy;
	while (entity)
	{
		entityBuf = entity;
		entity = entity->GetNext();

		entityBuf->SetPre(nullptr);
		entityBuf->SetNext(nullptr);

		entityBuf->Finalize();
		delete entityBuf;
	}
	m_destroy = nullptr;

	entity = m_vector;
	while (entity)
	{
		entity->UpdateComponent(timer);
		entity = entity->GetNext();
	}

	// 当たり判定を取る
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->HitCheck();

	entity = m_vector;
	while (entity)
	{
		entity->LateComponentUpdate(timer);
		entity = entity->GetNext();
	}
	entity = m_vector;
	while (entity)
	{
		entity->Update(timer);
		entity = entity->GetNext();
	}
}
 
void EntityVector::Render(Game* game)
{
	Entity* entity = m_vector;
	while (entity)
	{
		entity->Draw(game);
		entity = entity->GetNext();
	}
}

void EntityVector::Finalize()
{
	Entity* entity = m_vector;
	Entity* entityBuf;
	while (entity)
	{
		entityBuf = entity;
		entity = entityBuf->GetNext();
		entityBuf->Finalize();
		delete entityBuf;
	}
}

void EntityVector::Add(Entity * entity)
{
	if (!entity)
	{
		return;
	}

	if (m_vector)
	{
		entity->SetNext(m_vector);
		m_vector->SetPre(entity);
	}
	m_vector = entity;
	entity->Initialize();
}

void EntityVector::AddDestory(Entity * entity)
{
	if (!entity)
	{
		return;
	}

	if (m_destroy)
	{
		entity->SetNext(m_destroy);
		m_destroy->SetPre(entity);
	}
	m_destroy = entity;
}

EntityVector* EntityVector::GetInstance()
{
	if (!m_sEntityVector)
	{
		m_sEntityVector = new EntityVector();
	}
	return m_sEntityVector;
}

void EntityVector::Lost()
{
	delete m_sEntityVector;
}