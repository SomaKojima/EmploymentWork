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
	Quaternion dir = Quaternion::Identity;
	float degree = 1.0f;

	Vector3 upDir = Vector3::Transform(Vector3::Up, entity.GetTrans().dir.Get());

	dir = Quaternion::CreateFromAxisAngle(upDir, -XMConvertToRadians(degree));

	entity.GetTrans().dir.Set(entity.GetTrans().dir.Get() * dir);
}
