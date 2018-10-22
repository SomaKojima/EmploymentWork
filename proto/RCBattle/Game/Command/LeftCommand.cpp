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
	float degree = -1.0f;

	Vector3 upDir = Vector3::Transform(Vector3::Up, entity.GetTrans().GetDir());

	Vector3 forward = Vector3::Forward;
	Vector3 entityForward = Vector3::Transform(forward, entity.GetTrans().GetDir());
	float cos_ = forward.Dot(entityForward);
	float currentRot = acos(cos_);

	Vector3 right = Vector3::Right;
	float rightFlag = right.Dot(entityForward);
	Quaternion dir = Quaternion::Identity;
	if (rightFlag <= 0)
	{
		dir = Quaternion::CreateFromAxisAngle(upDir, currentRot - XMConvertToRadians(degree));
	}
	else
	{
		dir = Quaternion::CreateFromAxisAngle(upDir, -currentRot - XMConvertToRadians(degree));
	}

	entity.GetTrans().SetDir(dir);
}
