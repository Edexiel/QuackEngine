#ifndef _TIMEMANAGER_HPP
#define _TIMEMANAGER_HPP

namespace Time
{
    class TimePlatform;

    class TimeManager
    {
        TimePlatform* _timePlatform {nullptr};

        double _time{0.};
        double _deltaTime{0.};
    public:
        void SetDeltaTime(double deltaTime);

    public:
        ~TimeManager();

        void Init(TimePlatform* timePlatform);
        void Update();

        double GetTime() const;
        double GetDeltaTime() const;

    };
}

#endif //_TIMEMANAGER_HPP
