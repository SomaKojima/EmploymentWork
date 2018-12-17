/// <summary>
/// ShotCommand.cpp
/// 
/// 制作日:2018/7/13
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../../pch.h"
#include "ShotCommand.h"
#include "../Object/Factory/BulletFactory.h"
#include "../Object/EntityVector.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
ShotCommand::ShotCommand()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ShotCommand::~ShotCommand()
{
}

/// <summary>
/// 実行
/// </summary>
/// <param name="entity">実体</param>
void ShotCommand::Excute(Entity & entity)
{
	// 実体のコンテナ
	EntityVector* entityVector = EntityVector::GetInstance();

	// 弾の作成
	BulletFactory* bulletFactory = BulletFactory::GetInstance();
	Entity* _entity = bulletFactory->CreateBullet();

	_entity->GetTrans().dir.Set(entity.GetTrans().dir.Get());
	_entity->GetTrans().vel.SetLocal(Vector3(0.0f, 0.0f, 0.5f));

	Vector3 pos = Vector3::Transform(Vector3::Zero, entity.GetTrans().world.Get());
	pos += Vector3::Transform(Vector3(0.0f, -0.1f, 2.0f), entity.GetTrans().dir.Get());
	_entity->GetTrans().pos.Set(pos);

	_entity->SetName("Bullet");

	// プレイヤーの弾の設定
	_entity->SetTag(Tag::Player1);
	
	entityVector->Add(_entity);
}
