#pragma once

#include <QObject>

#include <osmosdr/source.h>

class SignalSource : public QObject {

public:
    explicit SignalSource(QObject* parent = nullptr);

    int setSamplingRate(double rate);
    double getSamplingRate();

    int setCarrierFreq(double freq);
    double getCarrierFreq();

    int setRxGain(double gain);
    double getRxGain();

    int setTxAttenuation(double att);
    double getTxAttenuation();

    osmosdr::source::sptr getGrPtr();
private:

    osmosdr::source::sptr m_sdrSrc;
};
