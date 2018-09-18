#include "../../pch.h"
#include "HPComponnet.h"

#include "../Component/Draw/UIRenderer.h"

HPComponent::HPComponent()
{
}

HPComponent::~HPComponent()
{
}

void HPComponent::Update(Entity & entity, DX::StepTimer const & timer)
{
	UIRenderer* ui = entity.GetComponent<UIRenderer>();

	EntityVector* entityVector = EntityVector::GetInstance();

	Entity* _entity = entityVector->GetEntity("Player");
	if (_entity->GetComponent<HPComponent>()->GetHp() <= 50)
	{

	}

	ui->SetRECT(RECT{1,1,_entity->GetComponent<HPComponent>()->GetHp(),1});
}

void HPComponent::OnCollide(Entity & entity, Entity & collide)
{
	collide.GetComponent<HPComponent>()->sethp(10);
	hp -= 10;
}
