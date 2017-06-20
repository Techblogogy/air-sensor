
#ifndef SENSOR_MODULE
#define SENSOR_MODULE

class SensorModule {

public:

    SensorModule(int tickTime);
    ~SensorModule();

    void Tick();
    void Send();

private:

    int data;
    int tickTime;

};

#endif
