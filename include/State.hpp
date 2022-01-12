#pragma once

namespace Engine
{

    class State
    {

    public:
        State() {}
        virtual ~State() {}
        virtual void Init() = 0;
        virtual void InputProcess() = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
    };
}