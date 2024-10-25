#include "ECS.h"

void Entity::Add_Group(Group m_Group)
{
	group_bit_set[m_Group] = true;
	manager.Add_To_Group(this, m_Group);
}
