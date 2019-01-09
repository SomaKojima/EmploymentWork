#pragma once

#include <Model.h>
#include "../Utility/Utility.h"

class ModelData : public SingletonBase<ModelData>
{
public:
	ModelData();
	~ModelData();

	void Create(ID3D11Device* device);

	DirectX::Model* GetBullet() { return m_bulletModel.get(); }
	DirectX::Model* GetCar() { return m_carModel.get(); }
	DirectX::Model* GetCarBody() { return m_carBodyModel.get(); }
	DirectX::Model* GetCarCannon() { return m_carCannonModel.get(); }
	DirectX::Model* GetRoom() { return m_roomModel.get(); }
	DirectX::Model* GetSphere() { return m_sphere.get(); }

	DirectX::Model* GetBullet2() { return m_bulletModel2.get(); }

private:

	std::unique_ptr<DirectX::Model> m_bulletModel;
	std::unique_ptr<DirectX::Model> m_carModel;
	std::unique_ptr<DirectX::Model> m_carBodyModel;
	std::unique_ptr<DirectX::Model> m_carCannonModel;
	std::unique_ptr<DirectX::Model> m_roomModel;
	std::unique_ptr<DirectX::Model> m_sphere;
	std::unique_ptr<DirectX::Model> m_bulletModel2;
};
