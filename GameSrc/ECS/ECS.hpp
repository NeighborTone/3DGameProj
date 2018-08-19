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
	friend class Entity;	//Entity�ɂ���ĎE���ꂽ���̂ł����Ȃ���
	bool active = true;
	void DeleteThis() { active = false; }
public:
	Entity* entity;
	virtual void Initialize() = 0;
	virtual void UpDate() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;
	virtual ~Component() {}
	//���̃R���|�[�l���g�������Ă��邩�Ԃ��܂�
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

	//����Entity�ɂ��Ă���Component�̏������������s���܂�
	void Initialize()
	{
		for (auto& c : components) c->Initialize();
	}
	//����Entity�ɂ��Ă���Component�̍X�V�������s���܂�
	void UpDate()
	{
		RefreshComponent();
		for (auto& c : components) c->UpDate();
	}
	//����Entity�ɂ��Ă���Component��3D�`�揈�����s���܂�
	void Draw3D() 
	{
		for (auto& c : components) c->Draw3D();
	}
	//����Entity�ɂ��Ă���Component��2D�`�揈�����s���܂�
	void Draw2D()
	{
		for (auto& c : components) c->Draw2D();
	}
	//Entity�̐�����Ԃ�Ԃ��܂�
	bool IsActive() const { return active; }
	//Entity���E���܂�
	void Destroy() { active = false; }
	//Entity���w�肵���O���[�v�ɓo�^����Ă��邩�Ԃ��܂�
	bool HasGroup(Group group)
	{
		return groupBitSet[group];
	}
	//Entity���O���[�v�ɓo�^���܂�
	void AddGroup(Group group);
	//Entity���O���[�v��������܂�
	void DeleteGroup(Group group)
	{
		groupBitSet[group] = false;
	}
	//Entity�Ɏw�肵��Component�����邩�Ԃ��܂�
	template <typename T> bool HasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}

	//�R���|�[�l���g�̒ǉ����\�b�h
	//�ǉ����ꂽ��R���|�[�l���g�̏��������\�b�h���Ă΂�܂�
	template <typename T, typename... TArgs> T& AddComponent(TArgs&&... args)
	{
		//Tips: std::forward
		//�֐��e���v���[�g�̈�����]������B
		//���̊֐��́A�n���ꂽ������T&&�^�ɃL���X�g���ĕԂ��B�i���FT�����Ӓl�Q�Ƃ̏ꍇ�ɂ�T&&�����Ӓl�Q�ƂɂȂ�A����ȊO�̏ꍇ��T&&�͉E�Ӓl�Q�ƂɂȂ�B�j
		//���̊֐��́A��ɓ]���֐��iforwarding function�j�̎�����P��������ړI�Ŏg����F
		T* c(new T(std::forward<TArgs>(args)...));	
		c->entity = this;
		std::unique_ptr<Component> uPtr(c);
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Initialize();
		return *c;
	}

	//�w�肵���R���|�[�l���g���폜���܂�
	template<typename T> void DeleteComponent()
	{
		if (HasComponent<T>())
		{
			GetComponent<T>().DeleteThis();
			componentBitSet[GetComponentTypeID<T>()] = false;
		}
	}

	//�o�^�����R���|�[�l���g���擾���܂�
	template<typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

//Entity�����N���X
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
	//�A�N�e�B�u�łȂ����̂��폜���܂�
	void Refresh()
	{
		entityes.erase(std::remove_if(std::begin(entityes), std::end(entityes),
			[](const std::unique_ptr<Entity> &pEntity)
		{
			return !pEntity->IsActive();
		}),
			std::end(entityes));
	}
	//�w�肵���O���[�v�ɓo�^����Ă���Entity�B��Ԃ��܂�
	std::vector<Entity*>& GetGroup(Group group)
	{
		return groupedEntities[group];
	}
	//Entity���w�肵���O���[�v�ɓo�^���܂�
	void AddGroup(Entity* pEntity, Group group)
	{
		groupedEntities[group].emplace_back(pEntity);
	}
	//Entity�𐶐������̃|�C���^��Ԃ��t�@�N�g�����\�b�h
	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr(e);
		entityes.emplace_back(std::move(uPtr));
		return *e;
	}
};