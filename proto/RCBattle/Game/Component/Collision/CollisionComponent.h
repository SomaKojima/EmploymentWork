/// <summary>
/// CollisionComponent.h
/// 
/// 制作日:2018/10/26
/// 制作者:小嶋 颯天
/// </summary>

/// <summary>
/// 多重インクルードの防止
/// </summary>
#pragma once

/// <summary>
/// ヘッダのインクルード
/// </summary>
#include "../Component.h"
#include "../../Collision/Collision.h"

/// <summary>
/// 球の当たり判定のコンポーネントクラス
/// </summary>
class CollisionComponent : public Component
{
public:
	CollisionComponent() :isHit(false) {};
	~CollisionComponent() {};

	// 更新
	void Update(DX::StepTimer const& timer) override;

	// 壁ずり等の処理
	virtual void HitBack(const Collision::Triangle* triangle, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Sphere* sphere, DirectX::SimpleMath::Vector3& hitPos) {};
	virtual void HitBack(const Collision::Plane* sphere, DirectX::SimpleMath::Vector3& hitPos) {};

	void SetHit(bool flag) { isHit = flag; }
	bool IsHit() { return isHit; }

	Collision::CollisionType GetShape(
		const Collision::Sphere** sphere = nullptr,
		const Collision::Plane** plane = nullptr,
		const Collision::Triangle** triangle = nullptr,
		const std::list<Collision::Triangle>** triangleList = nullptr)
	{

		if (sphere)		*sphere = &GetSphere();
		if (plane)		*plane = &GetPlane();
		if (triangle)		*triangle = &GetTriangle();
		if (triangleList)	*triangleList = &GetTriangleList();

		if (*sphere) return Collision::CollisionType::SPHERE;
		if (*plane)return Collision::CollisionType::PLANE;
		if (*triangle)return Collision::CollisionType::TRIANGLE;
		if (*triangleList)return Collision::CollisionType::TRIANGLE;

		return Collision::CollisionType::NONE;
	}

	virtual Collision::CollisionData2 GetShape() {};

protected:
	// 球の取得
	virtual const Collision::Sphere& GetSphere() { Collision::Sphere* sphere = nullptr; return *sphere; }
	// 面の取得
	virtual const Collision::Plane& GetPlane() { Collision::Plane* plane = nullptr; return *plane; }
	// 三角形の取得
	virtual const Collision::Triangle& GetTriangle() { Collision::Triangle* triangle = nullptr; return *triangle; }

	virtual const std::list<Collision::Triangle>& GetTriangleList() 
	{ std::list<Collision::Triangle>* triangleList = nullptr; return *triangleList; }

private:
	bool isHit;
};
