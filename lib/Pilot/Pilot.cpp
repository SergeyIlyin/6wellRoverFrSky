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
    else
    {
    }

    return readed;
}

void Pilot::Convert()
{
    pilotData = PilotData();
    pilotData.roll = 0;
    pilotData.trottle = 0;
}