#ifndef Pilot_h
#define Pilot_h

#include <Arduino.h>
#include <sbus.h>

#define AXISMIN 172
#define AXISMAX 1811

#define CH_TROTTLE 0x2
#define CH_X 0x1
#define CH_Y 0x0
#define CH_ARM 0x4
#define CH_REVERSE 0x5
#define CH_BREAK 0x6


struct PilotData
{
    int trottle;
    int x;
    int y;
    bool arm;
    bool handbreak;
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
