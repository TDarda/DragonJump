#include "StateMan.hpp"

Engine::StateMan::StateMan()
{
}

Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::StateChange()
{
    if (m_isRemoved && (!m_stack.empty()))
    {
        m_stack.pop();
        m_isRemoved = false;
    }
   
};
void Engine::StateMan::AddState(std::unique_ptr<State> newState)
{
    m_stack.push(std::move(newState));
    m_isAdd = true;
    m_stack.top()->Init();
};
void Engine::StateMan::RemoveState()
{
    m_isRemoved = true;
}
std::unique_ptr<Engine::State> &Engine::StateMan::CurrentState()
{
    return m_stack.top();
}