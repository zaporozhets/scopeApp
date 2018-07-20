#include "GeneralTimeImpl.h"

#include <QFile>

GeneralTimeImpl::GeneralTimeImpl(QObject* parent)
    : QObject(parent)
{
    m_tb = gr::make_top_block("scope");


    m_samplingFreq = 4e6;
    m_signalSource.setSamplingRate(m_samplingFreq);
    m_signalSource.setCarrierFreq(m_carierFreq);
    m_signalSource.setRxGain(0);


    // Low pass filter
    double cutoff_freq = 2e6;
    double transition_width = 500e3;
    const std::vector<float> taps = filter::firdes::low_pass(1, m_samplingFreq, cutoff_freq, transition_width);
    m_filter = filter::freq_xlating_fir_filter_ccf::make(1, taps, 0, m_samplingFreq);

    // Power Time
    m_powerTimeSrc = blocks::complex_to_mag_squared::make();

    int samplesPerSymbol = m_samplingFreq / 1000000;
    float sensitivity = (M_PI / 2.0f) / samplesPerSymbol;
    m_fskTimeSrc = analog::quadrature_demod_cf::make(1.0f / sensitivity);

    m_thr = blocks::throttle::make(sizeof(float), 50000);

    m_trigger = TriggerEdgeF::make(0.5, 1024, 0, 1);


    // Create sink
    m_testSink = TimeSink::make(1, "yo", 1);

    fskTime();
}

GeneralTimeImpl::~GeneralTimeImpl()
{
    LOG(INFO) << __PRETTY_FUNCTION__;
}

void GeneralTimeImpl::powerTime()
{
    m_tb->disconnect_all();

    // Connect the graph
    m_tb->connect(m_signalSource.getGrPtr(), 0, m_filter, 0);

    m_tb->connect(m_filter, 0, m_powerTimeSrc, 0);

    m_tb->connect(m_powerTimeSrc, 0, m_trigger, 0);

    m_tb->connect(m_trigger, 0, m_thr, 0);

    m_tb->connect(m_thr, 0, m_testSink, 0);
}

void GeneralTimeImpl::fskTime()
{
    m_tb->disconnect_all();

    // Connect the graph
    m_tb->connect(m_signalSource.getGrPtr(), 0, m_filter, 0);

    m_tb->connect(m_filter, 0, m_fskTimeSrc, 0);

    m_tb->connect(m_fskTimeSrc, 0, m_trigger, 0);

    m_tb->connect(m_trigger, 0, m_thr, 0);

    m_tb->connect(m_thr, 0, m_testSink, 0);
}

void GeneralTimeImpl::setSeries(QLineSeries* series)
{
    m_series = series;

    m_testSink->setSeries(m_series);
}

void GeneralTimeImpl::start()
{
    if (true == m_isRunning) {
        return;
    }
    m_tb->start();
    m_isRunning = true;
}

void GeneralTimeImpl::stop()
{
    if (false == m_isRunning) {
        return;
    }
    m_tb->stop();
    m_tb->wait();
    m_isRunning = false;
}

void GeneralTimeImpl::setMode(Mode mode)
{
    bool isRunned = m_isRunning;
    stop();

    switch (mode) {
    case (MODE_POWER): {
        powerTime();
        break;
    }
    case (MODE_FSK): {
        fskTime();
        break;
    }
    }

    // Restore previous state.
    if (isRunned) {
        start();
    }
}

void GeneralTimeImpl::setCarrierFreq(double val) {
    m_signalSource.setCarrierFreq(val);
}

void GeneralTimeImpl::setRxGain(double val) {
    m_signalSource.setRxGain(val);
}

void GeneralTimeImpl::setTriggerLevel(float level) {
    m_trigger->set_thresh(level);
}

