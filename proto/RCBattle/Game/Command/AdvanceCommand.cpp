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
	const float accelerator = 1.0f;
	const float InitialVelocity = 1.0f;
	Vector3 accel = entity.GetTrans().GetAccel();
	
	accel.z = 0.03f;

	entity.GetTrans().SetAccel(accel);
}
