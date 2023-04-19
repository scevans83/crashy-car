#ifndef ACCELEROMETER_THREAD_H
#define ACCELEROMETER_THREAD_H

#include "accel.h"
#include <QObject>
#include <QThread>
#include <QTimer>

class AccelerometerThread : public QThread {
    Q_OBJECT

signals:
    void xValueChanged(int value);

public:
    AccelerometerThread(int threshold, QObject* parent = nullptr);

protected:
    void run() override;

private slots:
    void readAccelerometer();

private:
    Accelerometer* m_accelerometer;
    QTimer* m_timer;
    int m_threshold;
};

#endif // ACCELEROMETER_THREAD_H
