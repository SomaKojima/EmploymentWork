#include "../../pch.h"
#include "Entity.h"
#include "../Component/Component.h"
#include "EntityVector.h"

#include < wchar.h > 

using namespace std;
using namespace DirectX::SimpleMath;

Entity::Entity()
	:
	m_transform(Transform()),
	m_parent(nullptr),
	m_pOFT(new OBJECT_FOR_TREE(this)),
	m_pEOF(new EntityOfTree(this)),
	FunctionComponent(this)
{
}

Entity::~Entity()
{
}

void Entity::Initialize()
{
	// 初期移動
	m_transform.m_local = Matrix::CreateFromQuaternion(m_transform.m_dir) * Matrix::CreateTranslation(m_transform.m_trans);

	UpdateMatrix();

	// 初期空間登録
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
}

bool Entity::Update(DX::StepTimer const & timer)
{
	// マトリクス/座標の更新
	m_transform.m_trans += Vector3::Transform(m_transform.m_vel, m_transform.m_dir);
	m_transform.m_local = Matrix::CreateFromQuaternion(m_transform.m_dir) * Matrix::CreateTranslation(m_transform.m_trans);

	UpdateMatrix();

	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
	return false;
}

void Entity::Finalize()
{
	m_pOFT->Remove();
	m_pEOF->Remove();

	delete m_pOFT;
	delete m_pEOF;
}

void Entity::Destroy()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	
	entityVector->AddDestory(this);
}

Entity* Entity::AddChild(Entity * entity)
{
	entity->SetParent(this);
	m_childVector.push_back(entity);
	return entity;
}

void Entity::DeleteChild()
{
}

void Entity::UpdateMatrix()
{
	if (m_parent)
	{
		m_transform.m_world = m_transform.m_local * m_parent->GetTrans().GetWorld();
	}
	else
	{
		m_transform.m_world = m_transform.m_local;
	}
	for (auto ite = m_childVector.begin(); ite != m_childVector.end(); ite++)
	{
		(*ite)->UpdateMatrix();
	}
}

