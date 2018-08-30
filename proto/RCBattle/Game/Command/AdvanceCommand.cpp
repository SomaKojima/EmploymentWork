#include "../../pch.h"
#include "AdvanceCommand.h"
#include "../Utility/Utility.h"
#include "../Component//PhysicsComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
AdvanceCommand::AdvanceCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
AdvanceCommand::~AdvanceCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void AdvanceCommand::Excute(Entity & entity)
{
	Vector3 vel = Vector3(entity.GetVel().x, entity.GetVel().y, 0.1f);
	entity.SetVel(vel);
}
