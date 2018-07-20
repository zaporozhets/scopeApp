#pragma once

#include <QObject>
#include <QtGui/QtGui>
#include <QtCharts/QLineSeries>


#include <gnuradio/filter/firdes.h>
#include <gnuradio/constants.h>
#include <gnuradio/hier_block2.h>
#include <gnuradio/io_signature.h>
#include <gnuradio/top_block.h>
#include <gnuradio/types.h>


#include <osmosdr/source.h>

#include "SpectrumSink.h"

QT_CHARTS_USE_NAMESPACE




class FreqDisplayForm : public QObject {
    Q_OBJECT

public:
    explicit FreqDisplayForm(int nplots = 1, QObject* parent = nullptr);
    ~FreqDisplayForm();

    //    FrequencyDisplayPlot* getPlot();

    int getFFTSize() const;
    float getFFTAverage() const;
    gr::filter::firdes::win_type getFFTWindowType() const;

    // Trigger methods
    gr::trigger_mode getTriggerMode() const;
    float getTriggerLevel() const;
    int getTriggerChannel() const;
    std::string getTriggerTagKey() const;

    // returns the frequency that was last double-clicked on by the user
    float getClickedFreq() const;

    // checks if there was a double-click event; reset if there was
    bool checkClicked();

    void plot(const std::vector<double*> dataPoints, const uint64_t numDataPoints);
    QLineSeries *m_series;
public slots:
    void setSeries(QLineSeries* series);

    void customEvent(QEvent* e);

    void setSampleRate(const QString& samprate);
    void setFFTSize(const int);
    void setFFTAverage(const float);
    void setFFTWindowType(const gr::filter::firdes::win_type);

    void setFrequencyRange(const double centerfreq,
        const double bandwidth);
    void setYaxis(double min, double max);
    void setYLabel(const std::string& label,
        const std::string& unit = "");
    void setYMax(const QString& m);
    void setYMin(const QString& m);
    void autoScale(bool en);
    void autoScaleShot();
    void setPlotPosHalf(bool half);
    void clearMaxHold();
    void clearMinHold();

    // Trigger slots
    void updateTrigger(gr::trigger_mode mode);
    void setTriggerMode(gr::trigger_mode mode);
    void setTriggerLevel(QString s);
    void setTriggerLevel(float level);
    void setTriggerChannel(int chan);
    void setTriggerTagKey(QString s);
    void setTriggerTagKey(const std::string& s);

    void setupControlPanel(bool en);
    void setupControlPanel();
    void teardownControlPanel();

    void notifyYAxisPlus();
    void notifyYAxisMinus();
    void notifyYRangePlus();
    void notifyYRangeMinus();
    void notifyFFTSize(const QString& s);
    void notifyFFTWindow(const QString& s);
    void notifyMaxHold(bool en);
    void notifyMinHold(bool en);
    void notifyTriggerMode(const QString& mode);
    void notifyTriggerLevelPlus();
    void notifyTriggerLevelMinus();

signals:
    void signalFFTSize(int size);
    void signalFFTWindow(gr::filter::firdes::win_type win);
    void signalClearMaxData();
    void signalClearMinData();
    void signalSetMaxFFTVisible(bool en);
    void signalSetMinFFTVisible(bool en);
    void signalTriggerMode(gr::trigger_mode mode);
    void signalTriggerLevel(float level);
    void signalReplot();

private slots:
    void newData(const QEvent* updateEvent);
    void onPlotPointSelected(const QPointF p);

private:
    gr::top_block_sptr tb;
    osmosdr::source::sptr m_sdrSrc;
    gr::SpectumSink::sptr m_fft;

    double m_samplingFreq = 10 * 1000 * 1000;

    uint64_t d_num_real_data_points;
    QIntValidator* d_int_validator;

    double d_samp_rate, d_center_freq;
    int d_fftsize;
    float d_fftavg;
    gr::filter::firdes::win_type d_fftwintype;
    double d_units;

    bool d_clicked;
    double d_clicked_freq;

    //    QMenu* d_triggermenu;
    //    TriggerModeMenu* d_tr_mode_menu;
    //    PopupMenu* d_tr_level_act;
    //    TriggerChannelMenu* d_tr_channel_menu;
    //    PopupMenu* d_tr_tag_key_act;

    gr::trigger_mode d_trig_mode;
    float d_trig_level;
    int d_trig_channel;
    std::string d_trig_tag_key;

    QAction* d_controlpanelmenu;
    //    FreqControlPanel* d_controlpanel;
};
