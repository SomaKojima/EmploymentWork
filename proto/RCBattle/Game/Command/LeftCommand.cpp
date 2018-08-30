/// <summary>
/// LeftCommand.cpp
/// 
/// 制作日:2018/7/5
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "LeftCommand.h"

/// <summary>
/// 名前空間
/// </summary>
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
LeftCommand::LeftCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
LeftCommand::~LeftCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void LeftCommand::Excute(Entity & entity)
{
	Vector3 angle = entity.GetAngle();
	angle.y += XMConvertToRadians(1.0f);

	entity.SetAngle(angle);

	//Vector3 vel = Vector3(0.1f, entity.GetVel().y, entity.GetVel().z);
	//entity.SetVel(vel);
}
