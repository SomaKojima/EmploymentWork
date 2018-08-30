#pragma once

#include <Model.h>

class ModelData
{
public:
	ModelData(ID3D11Device* device);
	~ModelData();

	static void Create(ID3D11Device* device);

	static ModelData* GetInstance();

	static void Lost();

	DirectX::Model* GetBullet() { return m_bulletModel.get(); }
	DirectX::Model* GetCar() { return m_carModel.get(); }
	DirectX::Model* GetRoom() { return m_roomModel.get(); }

private:
	static ModelData* m_sModelFactory;

	std::unique_ptr<DirectX::Model> m_bulletModel;
	std::unique_ptr<DirectX::Model> m_carModel;
	std::unique_ptr<DirectX::Model> m_roomModel;
};
