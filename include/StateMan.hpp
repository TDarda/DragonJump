#pragma once

#include <memory>
#include <stack>

#include <SFML/Audio.hpp>

#include "State.hpp"

namespace Engine
{

    class StateMan
    {
        bool m_isAdd = false;
        bool m_isRemoved = false;

        std::stack<std::unique_ptr<State>> m_stack;
        std::unique_ptr<State> m_newState;

    public:
        StateMan();
        ~StateMan();

        void StateChange();
        void AddState(std::unique_ptr<State> newState);
        void RemoveState();
        std::unique_ptr<State> &CurrentState();
    };
}