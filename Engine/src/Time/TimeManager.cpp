#include "Time/TimeManager.hpp"
#include "Time/TimePlatform.hpp"

using namespace Time;

TimeManager::~TimeManager()
{
    delete _timePlatform;
}

void TimeManager::Init(TimePlatform* timePlatform)
{
    _timePlatform = timePlatform;
}

void TimeManager::Update()
{
    _deltaTime = _timePlatform->GetTime() - _time;
    _time = _timePlatform->GetTime();
}

double TimeManager::GetTime() const
{
    return _time;
}

double TimeManager::GetDeltaTime() const
{
    return _deltaTime;
}