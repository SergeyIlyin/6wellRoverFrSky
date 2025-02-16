#ifndef Pilot_h
#define Pilot_h

#include <Arduino.h>
#include <sbus.h>

#define AXISMIN 172;
#define AXISMAX 1811;

#define CH_TROTTLE 0;
#define CH_ROLL 1;

struct PilotData
{
    int16_t roll;
    int trottle;
};

class Pilot
{
public:
    Pilot();
    void begin();
    bool Read();
    inline PilotData data() const { return pilotData; }

private:
    PilotData pilotData;
    bfs::SbusRx sbus_rx = bfs::SbusRx(&Serial, true);
    bfs::SbusData sBusData;

    int minAxis=AXISMIN;
    int maxAxis=AXISMAX;

    int chTrottle = CH_TROTTLE;
    int chRoll = CH_ROLL;
    void Convert();
 
};

#endif