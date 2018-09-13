#include "../../pch.h"
#include "EntityVector.h"
#include "Entity.h"

EntityVector* EntityVector::m_sEntityVector = nullptr;

EntityVector::EntityVector()
	:
	m_vector(new EntityCell())//,m_destroy(nullptr)
{
}

EntityVector::~EntityVector()
{
	delete m_vector;
}

void EntityVector::Initialize()
{
	int a = 0;
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
	/*entity = m_destroy->GetTop()->GetObj();
	while (entity)
	{
		entityBuf = entity;
		entity = entity->GetNext();

		entityBuf->SetPre(nullptr);
		entityBuf->SetNext(nullptr);

		entityBuf->Finalize();
		delete entityBuf;
	}
	m_destroy = nullptr;*/

	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->UpdateComponent(timer);
		entity = entity->GetNext();
	}

	// 当たり判定を取る
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->HitCheck();

	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->LateComponentUpdate(timer);
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
	while (entity)
	{
		entityBuf = entity;
		entity = entityBuf->GetNext();
		entityBuf->Remove();
		entityBuf->GetObj()->Finalize();
		delete entityBuf->GetObj();
	}
}

void EntityVector::Add(Entity * entity)
{
	if (!entity)
	{
		return;
	}
	m_vector->Add(entity->GetEOF());
	entity->Initialize();
}

//void EntityVector::AddDestory(Entity * entity)
//{
//	if (!entity)
//	{
//		return;
//	}
//
//	m_destroy->SetTop(entity);
//
//	if (m_destroy)
//	{
//		entity->SetNext(m_destroy);
//		m_destroy->SetPre(entity);
//	}
//	m_destroy = entity;
//}

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