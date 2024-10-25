#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include <algorithm>

class Component;
class Entity;
class Manager;

using Component_ID = std::size_t;
using Group = std::size_t;

inline Component_ID Get_New_Component_Type_ID() {
    static Component_ID lastID = 0u;
    return lastID++;
}

template <typename T>
inline Component_ID Get_Component_Type_ID() noexcept {
    static Component_ID type_ID = Get_New_Component_Type_ID();
    return type_ID;
}

constexpr std::size_t max_Components = 32;
constexpr std::size_t max_Grops = 32;

using Component_Bit_Set = std::bitset<max_Components>;
using Group_Bit_Set = std::bitset<max_Grops>;

using Component_Array = std::array<Component*, max_Components>;

class Component {
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() = default; // Dodaj default destruktor
};

class Entity {
private:
    Manager& manager;

    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    Component_Array component_array{};
    Component_Bit_Set component_bit_set;
    Group_Bit_Set group_bit_set;

public:
    Entity(Manager& m_Manager) : manager(m_Manager) {

    }
    void update() {
        for (auto& c : components) c->update();
    }

    void draw() { // Dodaj draw metodu
        for (auto& c : components) c->draw();
    }

    bool is_active() const { return active; }
    void destroy() { active = false; }

    bool has_Group(Group m_Group) {
        return group_bit_set[m_Group];

    }

    void Add_Group(Group m_Group);
    void Del_Group(Group m_Group) {
        group_bit_set[m_Group] = false;
    }

    template <typename T>
    bool has_component() const {
        return component_bit_set[Get_Component_Type_ID<T>()];
    }

    template <typename T, typename... Targs>
    T& Add_Component(Targs&&... m_Args) {
        T* c(new T(std::forward<Targs>(m_Args)...));

        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        component_array[Get_Component_Type_ID<T>()] = c;
        component_bit_set[Get_Component_Type_ID<T>()] = true;

        c->init();
        return *c;
    }

    template <typename T>
    T& get_Component() const {
        auto ptr = component_array[Get_Component_Type_ID<T>()];
        return *static_cast<T*>(ptr);
    }
};

class Manager {
public:
    void update() {
        for (auto& e : entities) {
            e->update();
        }
    }

    void draw() {
        for (auto& e : entities) {
            e->draw();
        }
    }

    void refresh() {
        for (auto i(0u); i < max_Grops; i++) {
            auto& v(grouped_Entities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v),
                    [i](Entity* m_Entity)
                    {
                        return !m_Entity->is_active() || !m_Entity->has_Group(i);
                    }),
                std::end(v));
        }


        entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
                [](const std::unique_ptr<Entity>& mEntity) {
                    return !mEntity->is_active();
                }),
            std::end(entities)
        );
    }

    void Add_To_Group(Entity* m_Entity, Group m_Group) {
        grouped_Entities[m_Group].emplace_back(m_Entity);
    }

    std::vector<Entity*>& get_Group(Group m_Group) {
        return grouped_Entities[m_Group];
    }

    Entity& Add_Entity() {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

    std::vector<Entity*> get_entities() {
        std::vector<Entity*> raw_entities;
        for (const auto& entity : entities) {
            raw_entities.push_back(entity.get());
        }
        return raw_entities;
    }


private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, max_Grops> grouped_Entities;
};
