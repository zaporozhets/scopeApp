#include "BlePacketParser.h"

#include <boost/circular_buffer.hpp>
#include <glog/logging.h>

extern "C" {
#include "btbb.h"
}

using namespace gr;

BlePacketParser::BlePacketParser(std::string tagName)
    : sync_block("time_sink_f",
          io_signature::make(0, 1, sizeof(unsigned char)),
          io_signature::make(0, 0, 0))
    , m_tagName(tagName)
{
    set_history(8 + 32 + 1);
}

BlePacketParser::~BlePacketParser()
{
}

template <typename T>
std::string int_to_hex(T i)
{
    std::stringstream stream;
    stream << "0x"
           << std::setfill('0') << std::setw(sizeof(T) * 2)
           << std::hex << i;
    return stream.str();
}

int BlePacketParser::work(int ninput_items,
    gr_vector_const_void_star& input_items,
    gr_vector_void_star& output_items)
{
    (void)output_items;

    //grab all "rx time" tags in this work call
    const uint64_t samp0_count = this->nitems_read(0);
    std::vector<gr::tag_t> rx_time_tags;
    pmt::pmt_t d_len_tag_key = pmt::string_to_symbol(m_tagName);
    get_tags_in_range(rx_time_tags, 0, samp0_count, samp0_count + ninput_items, d_len_tag_key);

    if (!rx_time_tags.empty()) {
        const uint64_t offset = rx_time_tags[0].offset - samp0_count;

        const uint8_t* dataPtr = static_cast<const uint8_t*>(input_items[0]);

        size_t pktLen = 1 + 4 + 2; //std::min((samp0_count - off))


        std::vector<uint8_t> packet;
        for (size_t i = 0; i < pktLen; i++) {
            uint8_t data = 0;
            for (int j = 0; j < 8; j++) {
                data |= (dataPtr[(i * 8) + j + offset]) ? (1 << j) : 0;
            }
            if(6 == i) {
                pktLen += (data & 0x3f) + 3;    // 3 - crc len
            }
            packet.push_back(data);
        }

        // Decode
        lell_packet *pkt;
        lell_allocate_and_decode(&packet[1], 2402, 0, &pkt);
        lell_print(pkt);
        lell_packet_unref(pkt);
    }
    return ninput_items;
}

void BlePacketParser::handle_pdus(pmt::pmt_t msg)
{
    (void)msg;
}
