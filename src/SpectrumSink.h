#pragma once

#include <gnuradio/fft/fft.h>
#include <gnuradio/filter/firdes.h>
#include <gnuradio/high_res_timer.h>

#include <gnuradio/constants.h>
#include <gnuradio/hier_block2.h>
#include <gnuradio/io_signature.h>
#include <gnuradio/sync_block.h>
#include <gnuradio/top_block.h>
#include <gnuradio/types.h>

class FreqDisplayForm;

namespace gr {

enum trigger_mode {
    TRIG_MODE_FREE,
    TRIG_MODE_AUTO,
    TRIG_MODE_NORM,
    TRIG_MODE_TAG,
};

enum trigger_slope {
    TRIG_SLOPE_POS,
    TRIG_SLOPE_NEG,
};

class SpectumSink : virtual public gr::sync_block {
private:
    void initialize();

    int d_fftsize;
    int d_tmpbuflen;
    float d_fftavg;
    filter::firdes::win_type d_wintype;
    std::vector<float> d_window;
    double d_center_freq;
    double d_bandwidth;
    std::string d_name;
    int d_nconnections;

    const pmt::pmt_t d_port;

    bool d_shift;
    fft::fft_complex* d_fft;

    int d_index;
    std::vector<gr_complex*> d_residbufs;
    std::vector<double*> d_magbufs;
    double* d_pdu_magbuf;
    float* d_fbuf;
    float* d_tmpbuf;

    FreqDisplayForm* d_main_gui;

    gr::high_res_timer_type d_update_time;
    gr::high_res_timer_type d_last_time;

    bool windowreset();
    void buildwindow();
    bool fftresize();
    void check_clicked();
    void fft(float* data_out, const gr_complex* data_in, int size);

    // Handles message input port for setting new center frequency.
    // The message is a PMT pair (intern('freq'), double(frequency)).
    void handle_set_freq(pmt::pmt_t msg);

    // Handles message input port for displaying PDU samples.
    void handle_pdus(pmt::pmt_t msg);

    // Members used for triggering scope
    trigger_mode d_trigger_mode;
    float d_trigger_level;
    int d_trigger_channel;
    pmt::pmt_t d_trigger_tag_key;
    bool d_triggered;
    int d_trigger_count;

    void _reset();
    void _gui_update_trigger();
    void _test_trigger_tags(int start, int nitems);
    void _test_trigger_norm(int nitems, std::vector<double*> inputs);

public:
    typedef boost::shared_ptr<SpectumSink> sptr;

    static sptr make(int size, int wintype,
        double fc, double bw,
        const std::string& name,
        int nconnections,
        FreqDisplayForm* fdf = 0)
    {
        return gnuradio::get_initial_sptr(new SpectumSink(size, wintype, fc, bw, name, nconnections, fdf));
    }

    SpectumSink(int size, int wintype,
        double fc, double bw,
        const std::string& name,
        int nconnections,
        FreqDisplayForm* fdf);
    ~SpectumSink();

    bool check_topology(int ninputs, int noutputs);

    void exec_();
//    QWidget* qwidget();

#ifdef ENABLE_PYTHON
    PyObject* pyqwidget();
#else
    void* pyqwidget();
#endif

    void set_fft_size(const int fftsize);
    int fft_size() const;
    void set_fft_average(const float fftavg);
    float fft_average() const;
    void set_fft_window(const filter::firdes::win_type win);
    filter::firdes::win_type fft_window();

    void set_frequency_range(const double centerfreq, const double bandwidth);
    void set_y_axis(double min, double max);

    void set_update_time(double t);

    void set_title(const std::string& title);
    void set_y_label(const std::string& label, const std::string& unit);
    void set_line_label(int which, const std::string& label);
    void set_line_color(int which, const std::string& color);
    void set_line_width(int which, int width);
    void set_line_style(int which, int style);
    void set_line_marker(int which, int marker);
    void set_line_alpha(int which, double alpha);
    void set_trigger_mode(trigger_mode mode,
        float level, int channel,
        const std::string& tag_key = "");

    std::string title();
    std::string line_label(int which);
    std::string line_color(int which);
    int line_width(int which);
    int line_style(int which);
    int line_marker(int which);
    double line_alpha(int which);

    void set_size(int width, int height);

    void enable_menu(bool en);
    void enable_grid(bool en);
    void enable_autoscale(bool en);
    void enable_control_panel(bool en);
    void enable_max_hold(bool en);
    void enable_min_hold(bool en);
    void clear_max_hold();
    void clear_min_hold();
    void disable_legend();
    void reset();
    void enable_axis_labels(bool en);

    int work(int noutput_items,
        gr_vector_const_void_star& input_items,
        gr_vector_void_star& output_items);
};
} /* namespace gr */
