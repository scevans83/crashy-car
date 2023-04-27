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
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &AccelerometerThread::readAccelerometer);
}

void AccelerometerThread::run()
{
    //bool m_stopThread = false;
    //m_timer = new QTimer();
    m_accelerometer->accel_init();
    // Read the accelerometer and then sleep for 50ms until thread is stopped
    while (true) {
        readAccelerometer(); 
        QThread::msleep(50);
    }
    //connect(m_timer, &QTimer::timeout, this, &AccelerometerThread::readAccelerometer, Qt::QueuedConnection);
    //m_timer->start(25);
}

void AccelerometerThread::readAccelerometer()
{
    int xValue = m_accelerometer->get_x();
    emit xValueChanged(xValue);

}
