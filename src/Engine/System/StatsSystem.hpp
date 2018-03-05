#pragma once

#include "System.hpp"
#include "Component/EnemyComponents/EnemyComponent.hpp"

// static class
class StatsSystem {
    friend Scene;
    
    public:

    static constexpr SystemID ID = SystemID::stats;

    public:

    static void init() {};

    static void update(float dt);

    private:

    static const Vector<EnemyComponent *> & s_enemyComponents;
};