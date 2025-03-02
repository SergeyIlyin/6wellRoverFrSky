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
    int T=sBusData.ch[CH_TROTTLE];
    int X=sBusData.ch[CH_X];
    int Y=sBusData.ch[CH_Y];
    Serial.print("\tT/X/Y=");
    Serial.print(T);
    Serial.print("/");
    Serial.print(X);
    Serial.print("/");
    Serial.print(Y);
    // TROTTLE
    pilotData.trottle = map(T, AXISMIN, AXISMAX, 0, 100);

    // ROLL
    pilotData.x = map(X, AXISMIN, AXISMAX, -100, 100);

    pilotData.y  = map(Y, AXISMIN, AXISMAX, -100, 100);
}
