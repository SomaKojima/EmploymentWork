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
		entity->GetObj()->InitializeComponent();
		entity->GetObj()->Initialize();
		entity = entity->GetNext();
	}
}

void EntityVector::Update(DX::StepTimer const& timer)
{

	EntityOfTree* entity = nullptr;
	EntityOfTree* entityBuf = nullptr;

	// デストロイリストのオブジェクトの処理
	entity = m_destroy->GetTop();
	Entity* obj = nullptr;
	while (entity)
	{
		entityBuf = entity->GetNext();
		obj = entity->GetObj();
		entity = entityBuf;

		obj->FinalizeComponent();
		obj->Finalize();
		delete obj;
	}

	// コンポーネントの更新処理
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->UpdateComponent(timer);
		entity = entity->GetNext();
	}

	// 当たり判定を取る
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->HitCheck();

	// コンポーネントの遅延処理
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->LateComponentUpdate(timer);
		entity = entity->GetNext();
	}

	// オブジェクトの更新処理
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->Update(timer);
		entity = entity->GetNext();
	}
}
 
void EntityVector::Render(Game* game)
{
	// コンポーネントの描画処理
	EntityOfTree* entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->DrawCompoennt(game);
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

		obj->FinalizeComponent();
		obj->Finalize();
		delete obj;
	}

	// デストロイリストに残っているオブジェクトの終了処理
	entity = m_destroy->GetTop();
	while (entity)
	{
		entityBuf = entity->GetNext();
		obj = entity->GetObj();
		entity = entityBuf->GetNext();

		obj->FinalizeComponent();
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