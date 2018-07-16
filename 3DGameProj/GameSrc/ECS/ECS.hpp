#pragma once
#include <bitset>
#include <array>
#include <memory>
#include <vector>

#define STUB override {}

class Entity;
class Component;
class EntityManager;


using ComponentID = std::size_t;
using Group = std::size_t;


inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0;
	return ++lastID;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t MaxComponents = 32;
constexpr std::size_t MaxGroups = 32;

using ComponentBitSet = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxComponents>;
using GroupBitSet = std::bitset<MaxGroups>;

class Component
{
public:
	
	Entity* entity;
	virtual void Initialize() = 0;
	virtual void UpDate() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;
	virtual ~Component() {}
};

class Entity
{
private:
	EntityManager & manager_;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray  componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
public:

	Entity(EntityManager& manager) : manager_(manager) {}

	void Initialize()
	{
		for (auto& c : components) c->Initialize();
	}
	void UpDate()
	{
		for (auto& c : components) c->UpDate();
	}
	void Draw3D() 
	{
		for (auto& c : components) c->Draw3D();
	}
	void Draw2D()
	{
		for (auto& c : components) c->Draw2D();
	}
	bool IsActive() const { return active; }

	void Destroy() { active = false; }

	bool HasGroup(Group group)
	{
		return groupBitSet[group];
	}

	void AddGroup(Group group);

	void DeleteGroup(Group group)
	{
		groupBitSet[group] = false;
	}

	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	//コンポーネントの追加メソッド
	//追加されたらコンポーネントの初期化メソッドが呼ばれる
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... args)
	{
		//Tips: std::forward
		//関数テンプレートの引数を転送する。
		//この関数は、渡された引数をT&&型にキャストして返す。（注：Tが左辺値参照の場合にはT&&も左辺値参照になり、それ以外の場合にT&&は右辺値参照になる。）
		//この関数は、主に転送関数（forwarding function）の実装を単純化する目的で使われる：
		T* c(new T(std::forward<TArgs>(args)...));	
		c->entity = this;
		std::unique_ptr<Component> uPtr(c);
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Initialize();
		return *c;
	}

	//登録したコンポーネントを取得する
	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

//Entity統括クラス。このクラスはUnityで例えるとHierarchyに当たる部分
class EntityManager
{
private:
	std::vector<std::unique_ptr<Entity>> entityes;
	std::array<std::vector<Entity*>, MaxGroups> groupedEntities;

public:
	void Initialize()
	{
		for (auto& e : entityes) e->Initialize();
	}
	void UpDate()
	{
		for (auto& e : entityes) e->UpDate();
	}
	void Draw3D()
	{
		for (auto& e : entityes) e->Draw3D();
	}
	void Draw2D()
	{
		for (auto& e : entityes) e->Draw2D();
	}
	//アクティブでないものを削除する
	void Refresh()
	{
		entityes.erase(std::remove_if(std::begin(entityes), std::end(entityes),
			[](const std::unique_ptr<Entity> &pEntity)
		{
			return !pEntity->IsActive();
		}),
			std::end(entityes));

		entityes.erase(std::remove_if(std::begin(entityes), std::end(entityes),
			[](const std::unique_ptr<Entity> &pEntity)
		{
			return !pEntity->IsActive();
		}),
			std::end(entityes));
	}

	std::vector<Entity*>& GetGroup(Group group)
	{
		return groupedEntities[group];
	}

	void AddGroup(Entity* pEntity, Group group)
	{
		groupedEntities[group].emplace_back(pEntity);
	}

	//Entityを生成しそのポインタを返すファクトリメソッド
	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr(e);
		entityes.emplace_back(std::move(uPtr));
		return *e;
	}
};