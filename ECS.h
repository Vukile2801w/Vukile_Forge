#pragma once
#include <vector>
#include <memory>
#include <bitset>
#include <array>
#include <algorithm>

class Component;
class Entity;

using Component_ID = std::size_t;

inline Component_ID Get_Component_Type_ID() {
    static Component_ID lastID = 0;
    return lastID++;
}

template <typename T>
inline Component_ID Get_Component_Type_ID() noexcept {
    static Component_ID type_ID = Get_Component_Type_ID();
    return type_ID;
}

constexpr std::size_t max_Components = 32;

using Component_Bit_Set = std::bitset<max_Components>;
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
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    Component_Array component_array{};
    Component_Bit_Set component_bit_set;

public:
    void update() {
        for (auto& c : components) c->update();
    }

    void draw() { // Dodaj draw metodu
        for (auto& c : components) c->draw();
    }

    bool is_active() const { return active; }
    void destroy() { active = false; }

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
        entities.erase(
            std::remove_if(std::begin(entities), std::end(entities),
                [](const std::unique_ptr<Entity>& mEntity) {
                    return !mEntity->is_active();
                }),
            std::end(entities)
        );
    }

    Entity& Add_Entity() {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
};
