#pragma once

#include <QtCharts/QAreaSeries>
#include <QtCharts/QLineSeries>

#include <gnuradio/constants.h>
#include <gnuradio/hier_block2.h>
#include <gnuradio/io_signature.h>
#include <gnuradio/sync_block.h>
#include <gnuradio/top_block.h>
#include <gnuradio/types.h>

#include <glog/logging.h>

QT_CHARTS_USE_NAMESPACE

class TimeSink : virtual public gr::sync_block {
public:
    typedef boost::shared_ptr<TimeSink> sptr;

    static sptr make(int size, const std::string& name, int nconnections)
    {
        return gnuradio::get_initial_sptr(new TimeSink(size, name, nconnections));
    }

    TimeSink(int size, const std::string& name, int nconnections);

    void setSeries(QLineSeries* series);

    int work(int ninput_items, gr_vector_const_void_star& input_items, gr_vector_void_star& output_items);

    void handle_pdus(pmt::pmt_t msg);

private:
    int d_size, d_buffer_size;
    std::string d_name;
    int d_nconnections;

    int d_index, d_start, d_end;
    std::vector<float*> d_fbuffers;
    std::vector<double*> d_buffers;

    QLineSeries* m_series;
};
