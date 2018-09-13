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
	DirectX::Model* GetRoom() { return m_roomModel.get(); }

private:

	std::unique_ptr<DirectX::Model> m_bulletModel;
	std::unique_ptr<DirectX::Model> m_carModel;
	std::unique_ptr<DirectX::Model> m_roomModel;
};
