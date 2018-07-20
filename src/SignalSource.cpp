#include "SignalSource.h"

SignalSource::SignalSource(QObject *parent)
    : QObject(parent)
{
#if 0
    std::string sourceArgs = "hackrf=0";
#else
    std::string sampleFullFileName = "/home/taras/Dropbox/ble_iq_4M_2403.bin";

    std::string sourceArgs = "file='" + sampleFullFileName + "',"
        + "rate=4e6,"
        + "repeat=true,"
        + "throttle=true";

#endif

    m_sdrSrc = osmosdr::source::make(sourceArgs);

    m_sdrSrc->set_freq_corr(0, 0);
    m_sdrSrc->set_dc_offset_mode(0, 0);
    m_sdrSrc->set_iq_balance_mode(0, 0);
    m_sdrSrc->set_antenna("", 0);
    m_sdrSrc->set_bandwidth(0, 0);
}

int SignalSource::setSamplingRate(double rate)
{
    m_sdrSrc->set_sample_rate(rate);
    return 0;   // TODO: add correct retval!
}

double SignalSource::getSamplingRate()
{
    return m_sdrSrc->get_sample_rate();
}

int SignalSource::setCarrierFreq(double freq)
{
    m_sdrSrc->set_center_freq(freq);
    return 0;   // TODO: add correct retval!
}

double SignalSource::getCarrierFreq()
{
    return m_sdrSrc->get_center_freq();
}

int SignalSource::setRxGain(double gain)
{
    (void)gain;
    // TODO: Recalculate optimal gain
    m_sdrSrc->set_gain(0, "RF"); // 0-14/14
    m_sdrSrc->set_gain(16, "IF"); // 0-40/8
    m_sdrSrc->set_gain(18, "BB"); // 0-62/2
    return 0;   // TODO: add correct retval!
}

double SignalSource::getRxGain()
{
    // TODO: Recalculate gain from IF + BB + ...
    return 0;
}

int SignalSource::setTxAttenuation(double att)
{
    (void)att;
    return 0;   // TODO: add correct retval!
}

double SignalSource::getTxAttenuation()
{
    return 0;   // TODO: add correct retval!
}

osmosdr::source::sptr SignalSource::getGrPtr()
{
    return m_sdrSrc;
}
