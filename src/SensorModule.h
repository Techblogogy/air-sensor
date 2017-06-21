
#ifndef SENSOR_MODULE
#define SENSOR_MODULE

class SensorModule {

public:

    SensorModule(int tickTime);

    virtual void Tick();
    virtual void Send();

    virtual float GetData();

private:

    float data;
    int tickTime;

};

#endif
