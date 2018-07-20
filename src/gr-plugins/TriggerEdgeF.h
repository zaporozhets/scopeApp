#pragma once

#include <gnuradio/msg_accepter.h>
#include <gnuradio/sync_block.h>
#include <pmt/pmt.h>

class TriggerEdgeF : public virtual gr::sync_block {
public:
    typedef boost::shared_ptr<TriggerEdgeF> sptr;

    static sptr make(float thresh, int length, int lookback, int guard)
    {
        return gnuradio::get_initial_sptr(new TriggerEdgeF(thresh, length, lookback, guard));
    }

    TriggerEdgeF(float thresh, int length, int lookback, int guard = 1);
    ~TriggerEdgeF();

    void set_thresh(float thresh);

private:
    int work(int noutput_items,
        gr_vector_const_void_star& input_items,
        gr_vector_void_star& output_items);

    int d_guard;
    uint64_t d_lasttrigger;

    float d_thresh = 0.0;
    float d_lastval;

    unsigned long long d_time;

    // event sizing parameters around the trigger moment
    unsigned int d_length;
    unsigned int d_lookback;
};
