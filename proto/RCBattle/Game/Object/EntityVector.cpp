#include "../../pch.h"
#include "EntityVector.h"
#include "Entity.h"

EntityVector::EntityVector()
	:
	m_vector(new EntityList()),
	m_add(new EntityList()),
	m_destroy(new EntityList())
{
}

EntityVector::~EntityVector()
{
	delete m_vector;
	delete m_destroy;
	delete m_add;
}

void EntityVector::Update(DX::StepTimer const& timer)
{
	EntityOfTree* entity = nullptr;
	Entity* obj = nullptr;

	// �ǉ����X�g�̃I�u�W�F�N�g�̏���(����������)
	while (m_add->GetTop())
	{
		entity = m_add->GetTop();
		obj = entity->GetObj();

		obj->InitializeComponent();
		obj->Initialize();

		// �ʂ̃��X�g�Ɉڂ�
		obj->GetEOF()->Remove();
		m_vector->Add(obj->GetEOF());
	}

	// �f�X�g���C���X�g�̃I�u�W�F�N�g�̏���(�I������)
	FinalizeList(m_destroy);

	// �R���|�[�l���g�̍X�V����
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->UpdateComponent(timer);
		entity = entity->GetNext();
	}

	// �R���|�[�l���g�̒x������
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->LateComponentUpdate(timer);
		entity = entity->GetNext();
	}

	// �����蔻������
	CLiner8TreeManager* cLiner8TreeManager = CLiner8TreeManager::GetInstance();
	cLiner8TreeManager->HitCheck();

	// �I�u�W�F�N�g�̍X�V����
	entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->Update(timer);
		entity = entity->GetNext();
	}
}
 
void EntityVector::Render(Game* game)
{
	// �R���|�[�l���g�̕`�揈��
	EntityOfTree* entity = m_vector->GetTop();
	while (entity)
	{
		entity->GetObj()->DrawCompoennt(game);
		entity = entity->GetNext();
	}
}

void EntityVector::Finalize()
{
	FinalizeList(m_vector);
	FinalizeList(m_destroy);
	FinalizeList(m_add);
}

void EntityVector::Add(Entity * entity)
{
	if (!entity)
	{
		return;
	}
	//m_vector->Add(entity->GetEOF());
	m_add->Add(entity->GetEOF());
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

Entity* EntityVector::GetEntity(char * name)
{
	EntityOfTree* entity = m_vector->GetTop();
	entity = m_vector->GetTop();
	Entity* entity2;
	while (entity)
	{
		if (entity->GetObj()->GetName() == name)
		{
			return entity->GetObj();
		}
		entity2 = CheckChildList(entity->GetObj()->GetChildList(), name);
		if (entity2)
		{
			return entity2;
		}
		entity = entity->GetNext();
	}

	return nullptr;
}

Entity * EntityVector::CheckChildList(std::list<Entity*>* childList, char * name)
{
	for (auto ite = childList->begin(); ite != childList->end(); ite++)
	{
		if ((*ite)->GetName() == name)
		{
			return (*ite);
		}
	}

	Entity* entity = nullptr;
	for (auto ite = childList->begin(); ite != childList->end(); ite++)
	{
		entity = CheckChildList((*ite)->GetChildList(), name);
		if (entity)
		{
			return entity;
		}
	}
	return nullptr;
}

void EntityVector::FinalizeList(EntityList* list)
{
	EntityOfTree* entity = list->GetTop();
	Entity* obj = nullptr;
	while (entity)
	{
		obj = entity->GetObj();
		entity = entity->GetNext();

		obj->FinalizeComponent();
		obj->Finalize();
		delete obj;
	}
}
