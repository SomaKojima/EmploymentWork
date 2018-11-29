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
	
	//// 初速度
	//float firstVec = 0.01f;
	//// 加速度
	//float accel = (vel.z * vel.z) - (firstVec * firstVec);
	//// 距離
	//float distance = firstVec + 
	accel.z = 0.01f;

	/*if (vel.z >= 0.2f)
	{
		vel.z = 0.2f;
	}*/

	entity.GetTrans().SetAccel(accel);
}
