
#ifndef SENSOR_MODULE
#define SENSOR_MODULE

class SensorModule {

public:

    SensorModule();

    virtual void Tick();
    virtual int Send();

    virtual float GetData();

private:

    float data;
    int tickTime;

};

#endif
