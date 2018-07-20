import QtQuick 2.9
import QtQuick.VirtualKeyboard 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id: item1
    width: 1024
    height: 768
    property alias triggetSlider: triggetSlider
    property alias freqArea: freqArea
    //    property alias freqArea: freqArea
    property alias scopeView: scopeView
    property alias stateBtn: stateBtn
    property alias modeBtn: modeBtn

    RowLayout {
        anchors.fill: parent

        ScopeView {
            id: scopeView

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        ControlPanel {
            Label {
                id: label
                text: qsTr("Label")
            }

            MultiButton {
                id: stateBtn
                text: "State: "
                Layout.fillWidth: true
            }

            MultiButton {
                id: modeBtn
                text: "Mode:"
                Layout.fillWidth: true
            }

            NumberField {
                id: freqArea
                text: "Freq: "
                Layout.fillWidth: true
                defaultValue: "2402"
            }
            SliderWithText {
                id: ifGainSlider
                from: 0
                to: 40
                value: 16
                stepSize: 8
                color: Style.text

                Layout.fillWidth: true
            }

            SliderWithText {
                id: bbGainSlider
                from: 0
                to: 62
                value: 16
                stepSize: 2
                Layout.fillWidth: true
            }

            DoubleSpinBox {
                id: triggetSlider
                decimals: 2
                value: 0.5
                stepSize: 0.1
                from: 0
                to: 2

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: false
            }
        }
    }
}
