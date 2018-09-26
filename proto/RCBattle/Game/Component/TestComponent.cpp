#include "../../pch.h"
#include "TestComponent.h"
#include "../Scene/SceneManager.h"

using namespace DirectX::SimpleMath;

TestComponent::TestComponent()
	:
	count(0)
{
}

TestComponent::~TestComponent()
{
}

void TestComponent::Update(DX::StepTimer const & timer)
{
	Game::SetPosText(Vector3::Transform(Vector3::Zero, (m_me->GetTrans().GetWorld())));
}
