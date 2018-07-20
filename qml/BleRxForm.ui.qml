import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 1024
    height: 768
    property alias channel: channel
    property alias accessCode: accessCode

    property alias stateBtn: stateBtn
    RowLayout {
        anchors.leftMargin: 0
        anchors.fill: parent

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        ControlPanel {

            Label {
                text: qsTr("Label")
            }

            MultiButton {
                id: stateBtn
                text: "State: "
                Layout.fillWidth: true
            }
            Label {
                text: qsTr("Channel:")
            }

            SpinBox {
                id: channel
                to: 39
                from: 0
                value: 0
            }

            Label {
                text: qsTr("Access code:")
            }

            ComboBox {
                id: accessCode
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: false
            }
        }
    }
}
