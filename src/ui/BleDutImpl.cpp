#include "BleDutImpl.h"

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <glog/logging.h>

BleDutControl::BleDutControl(QObject* parent)
    : QObject(parent)
{

}

BleDutControl::~BleDutControl()
{

}
int BleDutControl::reset()
{
    int retval;
    uint8_t status;
    struct hci_request req;

    req.ogf = OGF_HOST_CTL;
    req.ocf = OCF_RESET;
    req.rparam = &status;
    req.rlen = 1;

    retval = hci_send_req(m_sock, &req, 1000);
    if ((0 > retval) | (status)) {
        LOG(ERROR) << "retval = " << retval;
        LOG(ERROR) << "status = " << (unsigned int)status;
    }
    return retval;
}

int BleDutControl::leTxTest(int freq, int payload, int len)
{
    int retval = 0;
    le_transmitter_test_cp cmd;
    struct hci_request req;
    unsigned char status;

    cmd.frequency = freq;
    cmd.length = len;

    cmd.payload = payload;

    req.ogf = OGF_LE_CTL;
    req.ocf = OCF_LE_TRANSMITTER_TEST;

    req.cparam = &cmd;
    req.clen = LE_TRANSMITTER_TEST_CP_SIZE;

    req.rparam = &status;
    req.rlen = 1;

    retval = hci_send_req(m_sock, &req, 1000);
    if ((0 > retval) | (status)) {
        LOG(ERROR) << "retval = " << retval;
        LOG(ERROR) << "status = " << (unsigned int)status;
    }
    return retval;
}

int BleDutControl::leTestEnd()
{
    int retval = 0;
    le_test_end_rp status;
    struct hci_request req;

    req.ogf = OGF_LE_CTL;
    req.ocf = OCF_LE_TEST_END;

    req.cparam = nullptr;
    req.clen = 0;

    req.rparam = &status;
    req.rlen = LE_TEST_END_RP_SIZE;

    retval = hci_send_req(m_sock, &req, 1000);
    if ((0 > retval) | (status.status)) {
        LOG(ERROR) << "retval = " << retval;
        LOG(ERROR) << "status = " << (unsigned int)status.status;
    }
        LOG(INFO) << "num_pkts = " << (unsigned int)status.num_pkts;
    return retval;
}

int BleDutControl::open(QString name)
{
    int dev_id;
    int ctlSock;

    m_sock = -1;

    dev_id = hci_devid(name.toLatin1().data());

    /* Open HCI socket  */
    if ((ctlSock = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI)) < 0) {
        fprintf(stderr, "Failed to open control HCI socket.");
        return -1;
    }

    /* Up device HCI */
    if (ioctl(ctlSock, HCIDEVUP, dev_id) < 0) {
        if (errno != EALREADY) {
            LOG(ERROR) << "Failed to init device: " << strerror(errno);
            return -1;
        }
    }

    ::close(ctlSock);

    /* Open HCI socket */
    m_sock = hci_open_dev(dev_id);

    if (0 > m_sock) {
        LOG(ERROR) << "Failed to open hci device: " << strerror(errno);
        return m_sock;
    }

    return m_sock;
}

int BleDutControl::close()
{
    ::close(m_sock);
    m_sock = -1;
    return 0;
}
