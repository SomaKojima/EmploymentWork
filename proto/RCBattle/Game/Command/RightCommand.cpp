/// <summary>
/// RecessionCommand.cpp
/// 
/// 制作日:2018/7/5
/// 制作日:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "RightCommand.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
RightCommand::RightCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
RightCommand::~RightCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void RightCommand::Excute(Entity & entity)
{
	Vector3 angle = entity.GetTrans().GetAngle();

	if (entity.GetTrans().GetVel().z >= 0.0f)
	{
		angle.y += XMConvertToRadians(-1.0f);
	}
	else if (entity.GetTrans().GetVel().z < 0.0f)
	{
		angle.y += XMConvertToRadians(1.0f);
	}

	entity.GetTrans().SetAngle(angle);
}
