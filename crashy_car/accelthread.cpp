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
    bool m_stopThread = false;
//    printf("Accelerometer thread running.\n");
    m_timer = new QTimer();
    m_accelerometer->accel_init();
    while (!m_stopThread) {
        readAccelerometer(); // read the accelerometer data and emit the signal
        QThread::msleep(50); // sleep for 50 milliseconds
    }
    connect(m_timer, &QTimer::timeout, this, &AccelerometerThread::readAccelerometer, Qt::QueuedConnection);
    m_timer->start(25); // read accelerometer every 25ms
}

void AccelerometerThread::readAccelerometer()
{
    int xValue = m_accelerometer->get_x();
    emit xValueChanged(xValue);

}
