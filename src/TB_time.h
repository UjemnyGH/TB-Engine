#pragma once

namespace tbe
{
    class TB_Time
    {
    private:
        double currentFrame;
        double lastFrame;

        float deltaFrame;

    public:
        //time between last and current frame
        float deltaTime();
        //existing time
        double time();

        TB_Time();
    };

    typedef TB_Time Time;
}