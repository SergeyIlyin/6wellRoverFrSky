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
    pilotData.trottle = map(sBusData.ch[chTrottle], minAxis, maxAxis, 0, 100);

    // ROLL
    pilotData.roll = map(sBusData.ch[chRoll], minAxis, maxAxis, -90, 90);
}
