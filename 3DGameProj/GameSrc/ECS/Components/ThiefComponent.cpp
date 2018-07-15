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
	
	//Test
	if (KeyBoard::Down(KeyBoard::Key::KEY_Z))
	//
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
		
		GameController::GetParticle().Play("app", Vec3(data.at(data.size() - 1)->mesh.pos));
		sound.PlaySE();
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

void ThiefComponent::SetListenerPos(Pos&& pos)
{
	if (!data.empty())
	{
		sound.UpDate3DSound(Vec3(data.at(data.size() - 1)->mesh.pos), Vec3(pos.x, pos.y, pos.z));
	}
}

ThiefComponent::ThiefComponent(const float r)
{
	tex.Load("Resource/Texture/stonewall_diff.jpg");
	sound.Load("Resource/Sounds/steam_long.wav",true);
	radius = r;
}

void ThiefComponent::Initialize()
{
	if (data.empty())
	{
		return;
	}
	for (auto& it : data)
	{
		it->isActive = false;
	}
	Executioners();
}

void ThiefComponent::UpDate()
{
	Create();
	if (data.empty())
	{
		return;
	}
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
	if (data.empty())
	{
		return;
	}
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


