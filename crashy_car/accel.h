#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer {
public:
    Accelerometer();
    ~Accelerometer();
    int accel_init();
    void stop();
    int get_x();
    //int get_y();
    //int get_z();
private:
    int x_val;
    // int y_val;
    // int z_val;
    int file;
};

#endif /* Accelerometer */
