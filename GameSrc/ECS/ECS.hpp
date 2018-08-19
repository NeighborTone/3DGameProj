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
private:
	friend class Entity;	//Entityによって殺されたいのでこうなった
	bool active = true;
	void DeleteThis() { active = false; }
public:
	Entity* entity;
	virtual void Initialize() = 0;
	virtual void UpDate() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;
	virtual ~Component() {}
	//このコンポーネントが生きているか返します
	virtual bool IsActive() const final { return active; }

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
	 void RefreshComponent()
	{
		components.erase(std::remove_if(std::begin(components), std::end(components),
			[](const std::unique_ptr<Component> &pCom)
		{
			return !pCom->IsActive();
		}),
			std::end(components));
	}
public:

	Entity(EntityManager& manager) : manager_(manager) {}

	//このEntityについているComponentの初期化処理を行います
	void Initialize()
	{
		for (auto& c : components) c->Initialize();
	}
	//このEntityについているComponentの更新処理を行います
	void UpDate()
	{
		RefreshComponent();
		for (auto& c : components) c->UpDate();
	}
	//このEntityについているComponentの3D描画処理を行います
	void Draw3D() 
	{
		for (auto& c : components) c->Draw3D();
	}
	//このEntityについているComponentの2D描画処理を行います
	void Draw2D()
	{
		for (auto& c : components) c->Draw2D();
	}
	//Entityの生存状態を返します
	bool IsActive() const { return active; }
	//Entityを殺します
	void Destroy() { active = false; }
	//Entityが指定したグループに登録されているか返します
	bool HasGroup(Group group)
	{
		return groupBitSet[group];
	}
	//Entityをグループに登録します
	void AddGroup(Group group);
	//Entityをグループから消します
	void DeleteGroup(Group group)
	{
		groupBitSet[group] = false;
	}
	//Entityに指定したComponentがあるか返します
	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	//コンポーネントの追加メソッド
	//追加されたらコンポーネントの初期化メソッドが呼ばれます
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

	//指定したコンポーネントを削除します
	template<typename T> void DeleteComponent()
	{
		if (HasComponent<T>())
		{
			GetComponent<T>().DeleteThis();
			componentBitSet[GetComponentTypeID<T>()] = false;
		}
	}

	//登録したコンポーネントを取得します
	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

//Entity統括クラス
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
	//アクティブでないものを削除します
	void Refresh()
	{
		entityes.erase(std::remove_if(std::begin(entityes), std::end(entityes),
			[](const std::unique_ptr<Entity> &pEntity)
		{
			return !pEntity->IsActive();
		}),
			std::end(entityes));
	}
	//指定したグループに登録されているEntity達を返します
	std::vector<Entity*>& GetGroup(Group group)
	{
		return groupedEntities[group];
	}
	//Entityを指定したグループに登録します
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