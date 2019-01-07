#include "../../../pch.h"
#include "ButtonComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ButtonComponent::ButtonComponent()
	:
	uiRenderer(nullptr)
{
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::Initialize()
{
	uiRenderer = m_me->GetComponent<UIRenderer>();
}

void ButtonComponent::Update(DX::StepTimer const & timer)
{
	//ShowCursor(TRUE);
	if (uiRenderer)
	{
		auto state = Mouse::Get().GetState();

		m_tracker.Update(state);
		Vector3 pos = Vector3::Transform(Vector3::Zero, m_me->GetTrans().world.Get());
		RECT rect = RECT{
			static_cast<LONG>(pos.x),
			static_cast<LONG>(pos.y),
			static_cast<LONG>(pos.x) + uiRenderer->GetRECT().right - uiRenderer->GetRECT().left,
			static_cast<LONG>(pos.y) + uiRenderer->GetRECT().bottom - uiRenderer->GetRECT().top
		};
		
		if (rect.left <= state.x &&
			rect.right >= state.x &&
			rect.top <= state.y &&
			rect.bottom >= state.y)
		{
			// マウスの左ボタンが押された
			if (m_tracker.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
			{
				for (auto ite = m_pressList.begin(); ite != m_pressList.end(); ite++)
				{
					(*ite)->Press();
				}
			}
			else if (m_tracker.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
			{
			}
			// マウスのボタンが押されていたら
			if (state.leftButton)
			{
			}
		}
	}
}

void ButtonComponent::Finalize()
{
	for (auto ite = m_pressList.begin(); ite != m_pressList.end(); ite++)
	{
		delete (*ite);
	}
	m_pressList.clear();
}

void ButtonComponent::AddFunc(ButtonFunc* func)
{
	m_pressList.push_back(func);
}

