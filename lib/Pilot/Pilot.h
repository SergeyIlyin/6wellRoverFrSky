#ifndef Pilot_h
#define Pilot_h

#include <Arduino.h>
#include <sbus.h>

struct PilotData
{
    int roll;
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
    void Convert();
};

#endif