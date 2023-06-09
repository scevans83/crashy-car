#include <QThread>
#include <QTimer>
#include "accel.h"
#include "accelthread.h"
#include <QDebug>

AccelerometerThread::AccelerometerThread(int threshold, QObject* parent)
    : QThread(parent)
    , m_threshold(threshold)
{
    m_accelerometer = new Accelerometer();
}

// This function runs after the thread is started.
void AccelerometerThread::run()
{
    m_accelerometer->accel_init();
    // Read the accelerometer and then sleep for 50ms until thread is stopped
    while (true) {
        readAccelerometer(); 
        QThread::msleep(50);
    }
}

// Sends a signal to the Player class to move the player object
void AccelerometerThread::readAccelerometer()
{
    int xValue = m_accelerometer->get_x();
    emit xValueChanged(xValue);
}
