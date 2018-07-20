#pragma once

#include <QObject>
#include <QtCharts/QLineSeries>

#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/freq_xlating_fir_filter_ccf.h>

#include <gnuradio/blocks/complex_to_mag_squared.h>
#include <gnuradio/analog/quadrature_demod_cf.h>

#include <gnuradio/blocks/throttle.h>


#include <gnuradio/constants.h>
#include <gnuradio/hier_block2.h>

#include <gnuradio/io_signature.h>
#include <gnuradio/top_block.h>
#include <gnuradio/types.h>

#include "gr-plugins/TriggerEdgeF.h"

#include "TimeSink.h"


#include "SignalSource.h"


QT_CHARTS_USE_NAMESPACE
using namespace gr;

class GeneralTimeImpl : public QObject
{
    Q_OBJECT
public:
    explicit GeneralTimeImpl(QObject *parent = nullptr);

    ~GeneralTimeImpl();
    enum Mode
    {
        MODE_POWER = 0,
        MODE_FSK = 1
    };
    Q_ENUMS(Mode)

Q_SIGNALS:


public slots:
    void setSeries(QLineSeries *series);

    void start();
    void stop();
    void setMode(Mode mode);

    void setCarrierFreq(double val);
    void setRxGain(double val);

    void setTriggerLevel(float level);
private:

    void powerTime(void);
    void fskTime(void);


    QLineSeries *m_series;


    gr::top_block_sptr m_tb;
    SignalSource m_signalSource;

    gr::filter::freq_xlating_fir_filter_ccf::sptr m_filter;
    gr::blocks::complex_to_mag_squared::sptr m_powerTimeSrc;
    gr::analog::quadrature_demod_cf::sptr m_fskTimeSrc;
    gr::blocks::throttle::sptr m_thr;
    TriggerEdgeF::sptr m_trigger;

    TimeSink::sptr m_testSink;

    double m_carierFreq = 2402.0e6;
    double m_samplingFreq = 10e6;

    bool m_isRunning = false;

};
