import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 1024
    height: 768
    property alias payloadLength: payloadLength
    property alias leTestEndBtn: leTestEndBtn
    property alias leTxTestBtn: leTxTestBtn
    property alias resetBtn: resetBtn
    property alias pattern: pattern
    property alias channel: channel
    RowLayout {
        anchors.leftMargin: 0
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        ControlPanel {

            Label {
                id: label
                text: qsTr("Ble DUT ")
            }
            Label {
                text: "Channel"
            }
            SpinBox {
                id: channel
                from: 0
                to: 39
                stepSize: 1
            }
            Label {
                text: "Pattern"
            }

            ComboBox {
                id: pattern
            }

            Label {
                text: "Length"
            }
            SpinBox {
                id: payloadLength
                from: 1
                to: 20
                stepSize: 1
            }

            Button {
                id: resetBtn
                text: "Reset"
                Layout.fillWidth: true
            }

            Button {
                id: leTxTestBtn
                text: "Start"
                Layout.fillWidth: true
            }

            Button {
                id: leTestEndBtn
                text: "Stop"
                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: false
            }
        }
    }
}
