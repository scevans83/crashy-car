#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer {
public:
    Accelerometer();
    ~Accelerometer();
    int accel_init();
    void stop();
    int get_x();

private:
    int x_val;
    int file;
};

#endif /* Accelerometer */
