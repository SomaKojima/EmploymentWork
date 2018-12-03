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
	m_transform(Transform()),
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
	// �����ړ�
	Matrix local = Matrix::CreateFromQuaternion(m_transform.dir.Get()) * Matrix::CreateTranslation(m_transform.pos.Get());
	m_transform.local.Set(local);

	//UpdateMatrix();

	// ������ԓo�^
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
}

bool Entity::Update(DX::StepTimer const & timer)
{
	// �}�g���N�X/���W�̍X�V
	Vector3 vel = m_transform.vel.Get() + m_transform.accel.Get();
	m_transform.vel.Set(vel);

	Vector3 accel = Vector3::Zero;
	m_transform.accel.Set(accel);

	Vector3 pos = m_transform.pos.Get() + m_transform.vel.Get();
	m_transform.pos.Set(pos);

	Matrix local = Matrix::CreateFromQuaternion(m_transform.dir.Get()) * Matrix::CreateTranslation(m_transform.pos.Get());
	m_transform.local.Set(local);

	//UpdateMatrix();

	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->Register(this);
	return false;
}

void Entity::Finalize()
{
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

void Entity::UpdateMatrix()
{
	/*if (m_parent)
	{
		m_transform.world.Set(m_parent->GetTrans().world.Get() * m_transform.world.Get());
	}
	else
	{
		m_transform.m_world = m_transform.m_local;
	}
	for (auto ite = m_childlist.begin(); ite != m_childlist.end(); ite++)
	{
		(*ite)->UpdateMatrix();
	}*/
}

