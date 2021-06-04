#ifndef _TIMEPLATFORM_HPP
#define _TIMEPLATFORM_HPP

namespace Time
{
    class TimePlatform
    {
    public:

        virtual double GetTime() const {return 0;};
        virtual void SetTime(double time) {};
    };
}

#endif //_TIMEPLATFORM_HPP
