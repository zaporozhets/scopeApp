#include "TriggerEdgeF.h"

#include <glog/logging.h>

TriggerEdgeF::TriggerEdgeF(float thresh, int length, int lookback, int guard)
    : d_guard(guard)
    , d_lasttrigger(0)
    , d_thresh(thresh)
    , gr::sync_block("TriggerEdgeF",
          gr::io_signature::make(0, 1, sizeof(float)),
          gr::io_signature::make(0, 1, sizeof(float)))
{
    d_time = 0;
    d_length = length;
    d_lookback = lookback;


    set_history(512);
    declare_sample_delay(history()-1);

}

TriggerEdgeF::~TriggerEdgeF()
{
}

void TriggerEdgeF::set_thresh(float thresh)
{
    d_thresh = thresh;
}

int TriggerEdgeF::work(int noutput_items,
    gr_vector_const_void_star& input_items,
    gr_vector_void_star& output_items)
{
    const float* in = static_cast<const float*>(input_items[0]);

    int itemsize = input_signature()->sizeof_stream_item(1);
    float* oi = static_cast<float*>(output_items[0]);
    memcpy(oi, in, noutput_items * itemsize);

    d_lastval = (d_time == 0) ? in[0] : d_lastval;
    if (d_time == 0) {
        d_lastval = in[0];
    }

    for (int i = 0; i < noutput_items; i++) {
        //printf("in[i]=%f, d_thresh=%f, d_lastval=%f\n", in[i], d_thresh, d_lastval);
        if ((in[i] > d_thresh) && (d_lastval < d_thresh) && ((d_lasttrigger == 0) || (d_lasttrigger + d_guard <= d_time + i))) {
            // create an event at the appropriate time,
            //  factoring lookback and event length specified in constructor
            if (i + d_time < d_lookback) {
                printf("WARNING: d_time < d_lookback, spawning event at time zero.\n");
            }

            //            //pmt_t e1 = event_create( event_type(0), d_time-d_lookback, d_length );
            uint64_t event_time = (i + d_time) > d_lookback ? i + d_time - d_lookback : 0;


            pmt::pmt_t d_len_tag_key = pmt::string_to_symbol("yo");
            pmt::pmt_t d_packet_len_pmt = pmt::from_long(1024);

            add_item_tag(0, event_time, d_len_tag_key, d_packet_len_pmt);

            // record our last trigger
            d_lasttrigger = event_time;
        }
        d_lastval = in[i];
        //d_time++;
    }

    // consume the current input items
    d_time += noutput_items;
    return noutput_items;
}
