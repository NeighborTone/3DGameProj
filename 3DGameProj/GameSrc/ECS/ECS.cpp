#include "../ECS/ECS.hpp"
void Entity::AddGroup(Group group)
{
	groupBitSet[group] = true;
	manager_.AddGroup(this, group);
}