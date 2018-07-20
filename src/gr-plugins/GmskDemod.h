#pragma once

#include <gnuradio/hier_block2.h>
#include <gnuradio/types.h>

#include <gnuradio/analog/quadrature_demod_cf.h>
#include <gnuradio/digital/binary_slicer_fb.h>
#include <gnuradio/digital/clock_recovery_mm_ff.h>

class GmskDemod : virtual public gr::hier_block2 {
public:
    typedef boost::shared_ptr<GmskDemod> sptr;

    static sptr make(int samples_per_symbol,
        double gain_mu,
        double mu,
        double omega_relative_limit,
        double freq_error)
    {
        return gnuradio::get_initial_sptr(new GmskDemod(samples_per_symbol,
            gain_mu,
            mu,
            omega_relative_limit,
            freq_error));
    }

    GmskDemod(int samples_per_symbol,
        double gain_mu,
        double mu,
        double omega_relative_limit,
        double freq_error);

    ~GmskDemod();

private:
    int work(int noutput_items,
        gr_vector_const_void_star& input_items,
        gr_vector_void_star& output_items);

    gr::analog::quadrature_demod_cf::sptr m_fmdemod;
    gr::digital::clock_recovery_mm_ff::sptr m_clock_recovery;
    gr::digital::binary_slicer_fb::sptr m_slicer;

    int m_samples_per_symbol;
    double m_gain_mu;
    double m_mu;
    double m_omega_relative_limit;
    double m_freq_error;
    bool m_differential;

    double m_omega;
    double m_gain_omega;
};
