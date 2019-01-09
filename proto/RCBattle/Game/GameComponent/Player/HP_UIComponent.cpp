#include "../../../pch.h"
#include "HP_UIComponent.h"
#include "../../Object/EntityVector.h"
#include "../../Component/Draw/UIRenderer.h"
#include "../../Object/SpriteData.h"
#include "../BaseObject/StatusComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

HP_UIComponent::HP_UIComponent(StatusComponent* status)
	:
	m_status(status),
	m_lastHp(0),
	m_time(0),
	m_flashTime(0)
{
	if (m_status)
	{
		m_lastHp = m_status->GetHP();
	}
}

HP_UIComponent::~HP_UIComponent()
{
}

void HP_UIComponent::Initialize()
{
	if (!m_status) return;

	EntityVector* entityVector = EntityVector::GetInstance();
	Entity* entity = nullptr;

	// スプライトデータの読み込み
	SpriteData* spriteData = SpriteData::GetInstance();

	m_life[2] = new Entity();
	m_life[2]->AddComponent(new UIRenderer(spriteData->GetLifeOne(), RECT{ 0,0,800,100 }, 0.1f));
	m_life[2]->SetParent(m_me);
	entityVector->Add(m_life[2]);


	m_life[1] = new Entity();
	m_life[1]->AddComponent(new UIRenderer(spriteData->GetLifeTwo(), RECT{ 0,0,800,100 }, 0.1f));
	m_life[1]->SetParent(m_me);
	entityVector->Add(m_life[1]);

	m_life[0] = new Entity();
	m_life[0]->AddComponent(new UIRenderer(spriteData->GetLifeThree(), RECT{ 0,0,800,100 }, 0.1f));
	m_life[0]->SetParent(m_me);
	entityVector->Add(m_life[0]);

	entity = new Entity();
	entity->AddComponent(new UIRenderer(spriteData->GetLifeBone(), RECT{ 0,0,800,100 }, 0.1f));
	entity->SetParent(m_me);
	entityVector->Add(entity);
}

void HP_UIComponent::Update(DX::StepTimer const & timer)
{
	if (m_status)
	{
		// HPに合わせてUIを非表示にする
		UIRenderer* ui = nullptr;
		int hp = m_status->GetHP();
		switch (hp)
		{
		case 0:
			ui = m_life[0]->GetComponent<UIRenderer>();
			break;
		case 1:
			ui = m_life[1]->GetComponent<UIRenderer>();
			break;
		case 2:
			ui = m_life[2]->GetComponent<UIRenderer>();
			break;
		}
		if (ui)
		{
			ui->SetVisible(false);
		}

		// UIの点滅
		if (hp != m_lastHp &&
			hp <= 2)
		{
			// UIの点滅
			m_flashTime++;
			if (m_flashTime > 3)
			{
				m_flashTime = 0;
				for (int i = 0; i < m_lastHp - 1; i++)
				{
					UIRenderer* ui = nullptr;
					ui = m_life[i]->GetComponent<UIRenderer>();
					if (ui)
					{
						ui->SetVisible(!ui->GetVisible());
					}
				}
			}

			// 時間経過
			m_time++;
			if (m_time > 45)
			{
				m_flashTime = 0;
				m_time = 0;
				for (int i = 0; i < m_lastHp-1; i++)
				{
					UIRenderer* ui = nullptr;
					ui = m_life[i]->GetComponent<UIRenderer>();
					if (ui)
					{
						ui->SetVisible(true);
					}
				}
				m_lastHp = hp;
			}
		}
	}
}
