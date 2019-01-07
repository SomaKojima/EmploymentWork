#include "../../pch.h"
#include "Entity.h"
#include "../Component/Component.h"
#include "EntityVector.h"

#include < wchar.h > 

using namespace std;
using namespace DirectX::SimpleMath;

Entity::Entity()
	:
	m_name(""),
	m_tag(Tag::Default),
	m_transform(Transform(this)),
	m_parent(nullptr),
	m_pOFT(new OBJECT_FOR_TREE(this)),
	m_pEOF(new EntityOfTree(this)),
	FunctionComponent(this)
{
}

Entity::~Entity()
{
	m_pOFT->Remove();
	m_pEOF->Remove();
	delete m_pOFT;
	delete m_pEOF;
}

void Entity::Initialize()
{
	// 初期移動
	Matrix local = Matrix::CreateFromQuaternion(m_transform.dir.Get()) * Matrix::CreateTranslation(m_transform.pos.Get());
	m_transform.local.Set(local);

	//UpdateMatrix();

	// 初期空間登録
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
}

bool Entity::Update(DX::StepTimer const & timer)
{
	// マトリクス/座標の更新
	Vector3 vel = m_transform.vel.Get() + m_transform.accel.Get();
	m_transform.vel.Set(vel);
	m_transform.accel.Set(Vector3::Zero);

	Vector3 pos = m_transform.pos.Get() + m_transform.vel.Get();
	m_transform.pos.Set(pos);

	Matrix local = Matrix::CreateFromQuaternion(m_transform.dir.Get()) * Matrix::CreateTranslation(m_transform.pos.Get());
	m_transform.local.Set(local);

	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);

	return false;
}

void Entity::Finalize()
{
	for (auto ite = m_childlist.begin(); ite != m_childlist.end(); ite++)
	{
		(*ite)->Destroy();
	}
}

void Entity::Destroy()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	
	entityVector->AddDestory(this);
}

Entity* Entity::AddChild(Entity * entity)
{
	entity->SetParent(this);
	m_childlist.push_back(entity);
	return entity;
}

void Entity::DeleteChild()
{
}

Entity * Entity::GetChild(char * name)
{
	for (auto ite = m_childlist.begin(); ite != m_childlist.end(); ite++)
	{
		if ((*ite)->GetName() == name) return (*ite);

		Entity* entity = (*ite)->GetChild(name);
		if (entity) return entity;
	}

	return nullptr;
}
