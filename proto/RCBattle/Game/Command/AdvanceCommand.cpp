#include "../../pch.h"
#include "AdvanceCommand.h"
#include "../Utility/Utility.h"

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
	Vector3 vel = entity.GetTrans().GetVel();
	vel.z += 0.1f;
	if (vel.z >= 0.2f)
	{
		vel.z = 0.2f;
	}
	entity.GetTrans().SetVel(vel);
}
