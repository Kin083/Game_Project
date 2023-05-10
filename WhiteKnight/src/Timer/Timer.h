#ifndef TIMER_H
#define TIMER_H

#include <iostream>

const int TARGET_FPS = 60;
const double TARGET_DELTATIME = 1.5f;

class Timer
{
    public:
        void Tick();
        inline double GetDeltaTime() {return m_DeltaTime;}
        inline static Timer* GetInstance() {return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();}
        bool Wait(double time, double& x);

    private:
        Timer(){}
        static Timer* s_Instance;
        double m_DeltaTime;
        double m_LastTime;
        double m_tmp = 0;
};

#endif // TIMER_H
