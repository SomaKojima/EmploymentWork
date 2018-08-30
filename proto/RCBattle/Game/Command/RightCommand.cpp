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
	Vector3 angle = entity.GetAngle();
	Vector3 vel = entity.GetVel();
	angle.y -= XMConvertToRadians(1.0f);
	//if (vel.z >= -0.001f)
	//{
	//}
	//else
	//{
	//	angle.y += XMConvertToRadians(1.0f);
	//}

	entity.SetAngle(angle);

	//Vector3 vel = Vector3(-0.1f, entity.GetVel().y, entity.GetVel().z);
	//entity.SetVel(vel);
}
