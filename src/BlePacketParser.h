#pragma once

#include <string>

#include <gnuradio/io_signature.h>
#include <gnuradio/top_block.h>
#include <gnuradio/types.h>
#include <gnuradio/sync_block.h>

class BlePacketParser : virtual public gr::sync_block {
public:
    typedef boost::shared_ptr<BlePacketParser> sptr;

    static sptr make(std::string tagName)
    {
        return gnuradio::get_initial_sptr(new BlePacketParser(tagName));
    }

    BlePacketParser(std::string tagName);
    ~BlePacketParser();

private:
    int work(int ninput_items,
        gr_vector_const_void_star& input_items,
        gr_vector_void_star& output_items);

    void handle_pdus(pmt::pmt_t msg);

    std::string m_tagName;
};
