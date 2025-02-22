#include "Pilot.h"

Pilot::Pilot()
{
}

void Pilot::begin()
{
    while (!Serial)
    {
    }
    sbus_rx.Begin();
}

bool Pilot::Read()
{
    bool readed = sbus_rx.Read();
    if (readed)
    {
        sBusData = sbus_rx.data();
        Convert();
    }
    return readed;
}

void Pilot::Convert()
{
    pilotData = PilotData();
    
    // TROTTLE
    pilotData.trottle = map(sBusData.ch[CH_TROTTLE], AXISMIN, AXISMAX, 0, 100);

    // ROLL
    pilotData.x = map(sBusData.ch[CH_X], AXISMIN, AXISMAX, -100, 100);

    pilotData.y  = map(sBusData.ch[CH_Y], AXISMIN, AXISMAX, -100, 100);
}
