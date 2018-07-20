#include "GmskDemod.h"

#include <gnuradio/top_block.h>
#include <glog/logging.h>
#include <cmath>

using namespace gr;

GmskDemod::GmskDemod(int samples_per_symbol,
                     double gain_mu,
                     double mu,
                     double omega_relative_limit,
                     double freq_error)
    : hier_block2("gmsk_demod_cc",
          gr::io_signature::make(1, 1, sizeof(gr_complex)),
          gr::io_signature::make(1, 1, sizeof(char)))
    , m_samples_per_symbol(samples_per_symbol)
    , m_gain_mu(gain_mu)
    , m_mu(mu)
    , m_omega_relative_limit(omega_relative_limit)
    , m_freq_error(freq_error)
    , m_differential(false)
{
    if (samples_per_symbol < 2) {
        LOG(INFO) << "samples_per_symbol >= 2, is " << samples_per_symbol;
    }

    m_omega = samples_per_symbol * (1 + m_freq_error);

    //    if not self._gain_mu:
    //        self._gain_mu = 0.175

    m_gain_omega = 0.25 * m_gain_mu * m_gain_mu; // critically damped

    // Demodulate FM
    double sensitivity = (M_PI / 2) / samples_per_symbol;
    m_fmdemod = analog::quadrature_demod_cf::make(1.0 / sensitivity);

    // the clock recovery block tracks the symbol clock and resamples as needed.
    // the output of the block is a stream of soft symbols (float)
    m_clock_recovery = digital::clock_recovery_mm_ff::make(m_omega, m_gain_omega,
        m_mu, m_gain_mu,
        m_omega_relative_limit);

    // slice the floats at 0, outputting 1 bit (the LSB of the output byte) per sample
    m_slicer = digital::binary_slicer_fb::make();

    // Connect & Initialize base class
    connect(self(), 0, m_fmdemod, 0);
    connect(m_fmdemod, 0, m_clock_recovery, 0);
    connect(m_clock_recovery, 0, m_slicer, 0);
    connect(m_slicer, 0, self(), 0);
}

GmskDemod::~GmskDemod() {

}
