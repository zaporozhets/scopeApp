#include "TimeSink.h"

TimeSink::TimeSink(int size,
    const std::string& name,
    int nconnections)
    : sync_block("time_sink_f",
          gr::io_signature::make(0, nconnections, sizeof(float)),
          gr::io_signature::make(0, 0, 0))
    , d_size(size)
    , d_buffer_size(2 * size)
    , d_name(name)
    , d_nconnections(nconnections)
{
    if (nconnections > 24)
        throw std::runtime_error("time_sink_f only supports up to 24 inputs");

    // setup PDU handling input port
    message_port_register_in(pmt::mp("in"));
    set_msg_handler(pmt::mp("in"), boost::bind(&TimeSink::handle_pdus, this, _1));
}

void TimeSink::setSeries(QLineSeries* series)
{
    m_series = series;
}

int TimeSink::work(int ninput_items,
    gr_vector_const_void_star& input_items,
    gr_vector_void_star& output_items)
{


    //grab all "rx time" tags in this work call
    const uint64_t samp0_count = this->nitems_read(0);
    std::vector<gr::tag_t> rx_time_tags;

    if(0) {
        pmt::pmt_t d_len_tag_key = pmt::string_to_symbol("yo");
        get_tags_in_range(rx_time_tags, 0, samp0_count, samp0_count + ninput_items, d_len_tag_key);
    }
    else {
        gr::tag_t tag;
        tag.offset = samp0_count;
        rx_time_tags.push_back(tag);
    }
    if(!rx_time_tags.empty()) {
        int samplesCount = std::min(ninput_items, 1024);

        const uint64_t offset = rx_time_tags[0].offset  - samp0_count;

        if (m_series) {
            QXYSeries* xySeries = static_cast<QXYSeries*>(m_series);

            QVector<QPointF> pack(samplesCount);

            const float* dataPtr = static_cast<const float*>(input_items[0]);
            for (int x = 0; x < samplesCount; x++) {
                qreal y = dataPtr[x + offset];
                pack[x] = QPointF(x, y);
            }

            xySeries->replace(pack);
        }
    }

    return ninput_items;
}

void TimeSink::handle_pdus(pmt::pmt_t msg)
{
    (void)msg;
}
