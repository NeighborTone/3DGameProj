#include "ThiefComponent.h"
#include <iterator>
std::unique_ptr<EnemyData> ThiefComponent::AddEnemy()
{
	return std::make_unique<EnemyData>();
}

void ThiefComponent::LifeCheck()
{
	for (auto& it : data)
	{
		if (it->life <= 0)
		{
			it->isActive = false;
		}
	}
}

void ThiefComponent::Create()
{
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	{
		data.emplace_back(AddEnemy());
		Random rand;
		
		data.at(data.size()-1)->mesh.GetMaterial().Load("Resource/Shader/hoge.hlsl");
		data.at(data.size()-1)->mesh.GetMaterial().SetTexture(0, &tex);
		data.at(data.size()-1)->mesh.CreateSphere();
		data.at(data.size()-1)->isActive = true;
		data.at(data.size()-1)->life = 3;
		data.at(data.size()-1)->velocity = 0.3f;
		data.at(data.size()-1)->mesh.scale = radius * 2;
		data.at(data.size()-1)->mesh.pos.x = rand.GetRand(0.0f, 100.0f);
		data.at(data.size()-1)->mesh.pos.y = rand.GetRand(10.0f, 100.0f);
		data.at(data.size()-1)->mesh.pos.z = rand.GetRand(100.0f, 200.0f);
	}

}

void ThiefComponent::Executioners()
{
	data.erase(std::remove_if(std::begin(data), std::end(data),
		[](const std::unique_ptr<EnemyData> &data)
	{
		return !data->isActive;
	}),
		std::end(data));
}

ThiefComponent::ThiefComponent(const int num, const float r)
{
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	for (auto i(0); i < num; ++i)
	{
		data.emplace_back(AddEnemy());
	}

	for (auto& it : data)
	{
		it->mesh.GetMaterial().Load("Resource/Shader/hoge.hlsl");
		it->mesh.GetMaterial().SetTexture(0, &tex);
		radius = r;
	}
}

void ThiefComponent::Initialize()
{
	Random rand;
	for (auto& it : data)
	{
		it->mesh.CreateSphere();
		it->isActive = true;
		it->life = 3;
		it->velocity = 0.3f;
		it->mesh.scale = radius * 2;
		it->mesh.pos.x = rand.GetRand(0.0f, 100.0f);
		it->mesh.pos.y = rand.GetRand(10.0f, 100.0f);
		it->mesh.pos.z = rand.GetRand(100.0f, 200.0f);
	}
}

void ThiefComponent::UpDate()
{
	Create();
	LifeCheck();
	//Test
	for (auto& it : data)
	{

		if (it->isActive)
		{
			it->mesh.pos.z -= it->velocity.z;
		}
	}
	//
	Executioners();
}

void ThiefComponent::Draw3D()
{
	for (auto& it : data)
	{
		if (it->isActive)
		{
			it->mesh.Draw();
		}
	}
}

void ThiefComponent::Draw2D()
{

}

const std::vector<std::unique_ptr<EnemyData>>& ThiefComponent::Get() const
{
	return data;
}


