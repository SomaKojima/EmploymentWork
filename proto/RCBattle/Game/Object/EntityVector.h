#pragma once

#include <vector>
#include "../../StepTimer.h"
#include "../../Game.h"

class Entity;

class EntityVector
{
public:
	EntityVector();
	~EntityVector();

	void Initialize();
	void Update(DX::StepTimer const& timer);
	void Render(Game* game);
	void Finalize();

	void Add(Entity* entity);
	void AddDestory(Entity* entity);

	Entity* GetVector() { return m_vector; }
	void SetVector(Entity* _vector) { m_vector = _vector; }

	static EntityVector* GetInstance();
	static void Lost();

private:
	static EntityVector* m_sEntityVector;
	
	// ���̂̃R���e�i
	Entity* m_vector;
	// ���̂̃R���e�i
	Entity* m_destroy;
};