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
    int arm = sBusData.ch[CH_ARM] ;
    int R = sBusData.ch[CH_REVERSE];
    int T = sBusData.ch[CH_TROTTLE];
    int X = sBusData.ch[CH_X];
    int Y = sBusData.ch[CH_Y];

    Serial.print("\tA/T/X/Y/R=");
    Serial.print(arm);
    Serial.print("/");
    Serial.print(T);
    Serial.print("/");
    Serial.print(X);
    Serial.print("/");
    Serial.print(Y);
    Serial.print("/");
    Serial.print(R);
    // TROTTLE
    int reverse=R>1000?-1:1;
    pilotData.trottle = reverse* map(T, AXISMIN, AXISMAX, 0, 100);

    // ROLL
    pilotData.x = map(X, AXISMIN, AXISMAX, -100, 100);

    pilotData.y = map(Y, AXISMIN, AXISMAX, -100, 100);

    pilotData.arm= arm >1000;
}
