#include "BleRxImpl.h"

#include <QFile>
#include <glog/logging.h>

using namespace gr;

BleRxImpl::BleRxImpl(QObject* parent)
    : QObject(parent)
{
    m_tb = gr::make_top_block("scope");


    setChannel(0);
    m_signalSource.setSamplingRate(m_samplingFreq);
    m_signalSource.setRxGain(0);

    int squelch_threshold = -20;
    m_analogSimpleSquelch = analog::simple_squelch_cc::make(squelch_threshold, 0.1);

    std::vector<float> taps = filter::firdes::low_pass(1, m_samplingFreq, 850e3, 300e3, filter::firdes::WIN_HAMMING, 6.76);
    m_lowpassFilter = filter::freq_xlating_fir_filter_ccf::make(1, taps, -m_freqOffset, m_samplingFreq);

    int gmsk_sps = 4; //(m_samplingFreq / data_rate);
    double gmsk_omega_limit = 0.035;
    double gmsk_mu = 0.5;
    double gmsk_gain_mu = 0.7;
    m_digitalGfskDemod = GmskDemod::make(gmsk_sps, gmsk_gain_mu, gmsk_mu, gmsk_omega_limit, 0.0);

    m_correlate = digital::correlate_access_code_tag_bb::make("01101011011111011001000101110001", 0, "tag");

    m_parser = BlePacketParser::make("tag");

    // Connections
    m_tb->connect(m_signalSource.getGrPtr(), 0, m_analogSimpleSquelch, 0);
    m_tb->connect(m_analogSimpleSquelch, 0, m_lowpassFilter, 0);
    m_tb->connect(m_lowpassFilter, 0, m_digitalGfskDemod, 0);
    m_tb->connect(m_digitalGfskDemod, 0, m_correlate, 0);
    m_tb->connect(m_correlate, 0, m_parser, 0);

}

BleRxImpl::~BleRxImpl()
{
    stop();
}

int BleRxImpl::setAccessCode(BleRxImpl::AccessCodeType type)
{
    if(ACC_TEST == type) {
        // bin    : 01110001011101100100000100101001
        // rev bin: 10010100100000100110111010001110
        // rev hex: 0x94826E8E
        // #define TEST_SYNC_WORD			0x71764129
        m_accessCodeBits = "10010100100000100110111010001110";
    } else {
        // bin    : 10001110100010011011111011010110
        // rev bin: 01101011011111011001000101110001
        // rev hex: 0x6B7D9171
        #define ADVERTISING_SYNC_WORD	0x8e89bed6
        m_accessCodeBits = "01101011011111011001000101110001";
    }

    m_correlate->set_access_code(m_accessCodeBits);

    return 0;
}

void BleRxImpl::start()
{
    if (true == m_isRunning) {
        LOG(ERROR) << "Alreaddy running!";
        return;
    }

    m_tb->start();
    m_isRunning = true;
}

void BleRxImpl::stop()
{
    if (false == m_isRunning) {
        return;
    }
    m_tb->stop();
    m_tb->wait();
    m_isRunning = false;
}

int BleRxImpl::setChannel(int channel)
{
    double freq = 2402e6 + (channel * 2e6) + m_freqOffset;
    m_signalSource.setCarrierFreq(freq);

    m_channel = channel;

    return 0;
}

int BleRxImpl::getChannel()
{
    return m_channel;
}

//void BleRxForm::setSeries(QLineSeries* series)
//{
//    m_series = series;

//    m_testSink->setSeries(m_series);
//}
