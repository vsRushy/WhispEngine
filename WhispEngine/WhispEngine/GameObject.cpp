#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "Application.h"

GameObject::GameObject(GameObject * parent) : parent(parent)
{
	if (parent != nullptr)
		parent->children.push_back(this);

	CreateComponent(ComponentType::TRANSFORM);
	SetName("GameObject");
}

GameObject::~GameObject()
{
	for (auto comp = components.begin(); comp != components.end(); ++comp) {
		delete *comp;
		*comp = nullptr;
	}
	components.clear();

	for (auto i = children.begin(); i != children.end(); i++) {
		delete *i;
		*i = nullptr;
	}
	children.clear();

	if (this == App->object_manager->GetSelected())
		App->object_manager->SetSelected(nullptr);
}

void GameObject::Update()
{
	for (auto i = components.begin(); i != components.end(); ++i) {
		if ((*i)->IsActive())
			(*i)->Update();
	}
	if (components_to_delete.size() > 0) {
		for (auto c = components_to_delete.begin(); c != components_to_delete.end(); c++) {
			components.erase(std::find(components.begin(), components.end(), *c));
			delete *c;
		}
		components_to_delete.clear();
	}

	if (see_bounding_box) {
		glColor3f(0.f, 1.f, 0.f);

		glBegin(GL_LINES);

		glVertex3f(aabb.MinX(), aabb.MinY(), aabb.MinZ());
		glVertex3f(aabb.MaxX(), aabb.MinY(), aabb.MinZ());

		glVertex3f(aabb.MinX(), aabb.MinY(), aabb.MinZ());
		glVertex3f(aabb.MinX(), aabb.MinY(), aabb.MaxZ());

		glVertex3f(aabb.MinX(), aabb.MinY(), aabb.MinZ());
		glVertex3f(aabb.MinX(), aabb.MaxY(), aabb.MinZ());


		glVertex3f(aabb.MaxX(), aabb.MaxY(), aabb.MaxZ());
		glVertex3f(aabb.MaxX(), aabb.MinY(), aabb.MaxZ());

		glVertex3f(aabb.MaxX(), aabb.MaxY(), aabb.MaxZ());
		glVertex3f(aabb.MinX(), aabb.MaxY(), aabb.MaxZ());

		glVertex3f(aabb.MaxX(), aabb.MaxY(), aabb.MaxZ());
		glVertex3f(aabb.MaxX(), aabb.MaxY(), aabb.MinZ());


		glEnd();
	}
}

Component * GameObject::CreateComponent(const ComponentType & type)
{
	switch (type)
	{
	case TRANSFORM: {
		ComponentTransform * comp = new ComponentTransform(this);
		components.push_back(comp);
		return comp;
	}
		break;
	case MESH: {
		ComponentMesh* comp = new ComponentMesh(this);
		components.push_back(comp);
		return comp;
	}
		break;
	case MATERIAL: {
		ComponentMaterial* comp = new ComponentMaterial(this);
		components.push_back(comp);
		return comp;
	}
		break;
	case LIGHT:
		break;
	default:
		LOG("Not declared Component type with id: %d", type);
		break;
	}

	return nullptr;
}

void GameObject::DeleteComponent(Component * comp)
{
	components_to_delete.push_back(comp);
}

Component * GameObject::GetComponent(const ComponentType & type)
{
	for (auto i = components.cbegin(); i != components.cend(); ++i) {
		if (*i != nullptr)
			if ((*i)->GetType() == type)
				return *i;
	}
	return nullptr;
}

bool GameObject::HasComponent(const ComponentType & type)
{
	for (auto comp = components.begin(); comp != components.end(); comp++)
		if ((*comp)->GetType() == type)
			return true;

	return false;
}

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::SetActive(const bool & to_active)
{
	active = to_active;
}

const char * GameObject::GetName() const
{
	return name.data();
}

void GameObject::SetName(const char * name)
{
	this->name.assign(name);
}


ObjectSelected GameObject::GetSelect() const
{
	return obj_selected;
}

void GameObject::Select()
{
	obj_selected = ObjectSelected::SELECTED;

	if (parent != nullptr)
	{
		if (parent->obj_selected != ObjectSelected::NONE)
			obj_selected = ObjectSelected::CHILD_FROM_PARENT_SELECTED;		
	}
	
	for (auto i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Select();
	}
}

void GameObject::Deselect()
{
	obj_selected = ObjectSelected::NONE;

	for (auto i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Deselect();
	}
}

void GameObject::Detach()
{
	parent->children.erase(std::find(parent->children.begin(), parent->children.end(), this));
	parent = nullptr;
}

void GameObject::Attach(GameObject * parent)
{
	this->parent = parent;
	parent->children.push_back(this);
}

bool GameObject::HasChild(GameObject * child)
{
	bool ret = false;
	for (auto it_child = children.begin(); it_child != children.end(); it_child++) {
		if ((*it_child) == child)
			ret = true;
		if (ret)
			break;
		if (!(*it_child)->children.empty())
			ret = (*it_child)->HasChild(child);
	}
	return ret;
}

void GameObject::GetBBox(math::AABB& aabb)
{
	ComponentMesh* component_mesh = (ComponentMesh*)GetComponent(ComponentType::MESH);
	
	if (component_mesh != nullptr)
	{
		component_mesh->InitAABB();
		aabb = component_mesh->mesh->aabb;
		aabb.maxPoint = aabb.maxPoint.Max(component_mesh->mesh->aabb.maxPoint);
		aabb.minPoint = aabb.minPoint.Min(component_mesh->mesh->aabb.minPoint);
	}
}