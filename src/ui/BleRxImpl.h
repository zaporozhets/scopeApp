#pragma once

#include <QObject>

#include <gnuradio/analog/simple_squelch_cc.h>

#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/fir_filter_ccf.h>
#include <gnuradio/filter/freq_xlating_fir_filter_ccf.h>
#include "gr-plugins/GmskDemod.h"

#include <gnuradio/digital/correlate_access_code_tag_bb.h>

#include <gnuradio/blocks/unpacked_to_packed_bb.h>
#include "BlePacketParser.h"

#include <gnuradio/blocks/tag_debug.h>


#include <gnuradio/constants.h>
#include <gnuradio/io_signature.h>
#include <gnuradio/top_block.h>
#include <gnuradio/types.h>

#include "SignalSource.h"


class BleRxImpl : public QObject
{
    Q_OBJECT
public:
    explicit BleRxImpl(QObject *parent = nullptr);

    ~BleRxImpl();

    enum AccessCodeType
    {
        ACC_TEST = 0,
        ACC_ADVERTISING = 1
    };
    Q_ENUMS(AccessCodeType)


    int setChannel(int channel);
    int getChannel();

Q_SIGNALS:


public slots:
//    void setSeries(QLineSeries *series);
    int setAccessCode(AccessCodeType type);
    void start();
    void stop();
private:



    gr::top_block_sptr m_tb;

    SignalSource m_signalSource;

    gr::analog::simple_squelch_cc::sptr m_analogSimpleSquelch;

    gr::filter::freq_xlating_fir_filter_ccf::sptr m_lowpassFilter;
    GmskDemod::sptr m_digitalGfskDemod;

    gr::digital::correlate_access_code_tag_bb::sptr m_correlate;

    BlePacketParser::sptr m_parser;


    std::string m_accessCodeBits = "";

    bool m_isRunning = false;


    int m_channel = 0;
    double m_samplingFreq = 4e6;
    double m_freqOffset = 1e6;
};
