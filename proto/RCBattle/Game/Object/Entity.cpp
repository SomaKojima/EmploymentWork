#include "../../pch.h"
#include "Entity.h"
#include "../Component/Component.h"
#include "EntityVector.h"

#include < wchar.h > 

using namespace std;
using namespace DirectX::SimpleMath;

Entity::Entity()
	:
	m_angle(Vector3::Zero),
	m_dir(Quaternion::Identity),
	m_vel(Vector3::Zero),
	m_radius(0.0f),
	m_world(Matrix::Identity),
	m_local(Matrix::Identity),
	m_parent(nullptr),
	m_pOFT(new OBJECT_FOR_TREE(this)),
	m_pEOF(new EntityOfTree(this))
{
	m_componentMap.clear();
}

Entity::~Entity()
{
	m_pOFT->Remove();
	delete m_pOFT;
}

void Entity::Initialize()
{
	for (auto ite = m_componentMap.begin(); ite != m_componentMap.end(); ite++)
	{
		ite->second->Initialize(*this);
	}

	// 初期移動
	m_local = Matrix::CreateFromQuaternion(m_dir) * Matrix::CreateTranslation(m_trans);

	UpdateMatrix();

	// 初期空間登録
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
}

void Entity::OnCollide(Entity & entity)
{
	for (auto ite = m_componentMap.begin(); ite != m_componentMap.end(); ite++)
	{
		ite->second->OnCollide(*this, entity);
	}
}

bool Entity::Update(DX::StepTimer const & timer)
{
	// マトリクス/座標の更新
	m_trans += Vector3::Transform(m_vel, m_dir);
	m_local = Matrix::CreateFromQuaternion(m_dir) * Matrix::CreateTranslation(m_trans);

	UpdateMatrix();

	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
	return false;
}

void Entity::Draw(Game * game)
{
	for (auto ite = m_componentMap.begin(); ite != m_componentMap.end(); ite++)
	{
		ite->second->Draw(*this, game);
	}
}

void Entity::Finalize()
{

	for (auto ite = m_componentMap.begin(); ite != m_componentMap.end(); ite++)
	{
		ite->second->Finalize(*this);
		delete ite->second;
	}

	m_componentMap.clear();
}

void Entity::Destroy()
{
	EntityVector* entityVector = EntityVector::GetInstance();
	/*if (m_pPre)
	{
		m_pPre->SetNext(m_pNext);
	}
	else
	{
		entityVector->SetVector(m_pNext);
	}

	if (m_pNext)
	{
		m_pNext->SetPre(m_pPre);
	}
	m_pPre = nullptr;
	m_pNext = nullptr;
	entityVector->AddDestory(this);*/

	m_pOFT->Remove();
}

void Entity::DeleteComponent()
{

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
		m_world = m_local * m_parent->GetWorld();
	}
	else
	{
		m_world = m_local;
	}
	for (auto ite = m_childVector.begin(); ite != m_childVector.end(); ite++)
	{
		(*ite)->UpdateMatrix();
	}
}

