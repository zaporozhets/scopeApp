import QtQuick 2.3
import QtCharts 2.2
import QtQuick.VirtualKeyboard 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 1024
    height: 768
    property alias scopeView: scopeView
    property alias stateBtn: stateBtn
    property alias d_maxhold_check: d_maxhold_check

    RowLayout {
        anchors.fill: parent
        id: rowLayout0

        ScopeView {
            id: scopeView

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ControlPanel {

            Label {
                id: label
                text: qsTr("Spectrum")
            }

            MultiButton {
                id: stateBtn
                text: "State: "
                Layout.fillWidth: true
            }

            CheckBox {
                id: d_maxhold_check
                text: qsTr("Max Hold")
                Layout.fillWidth: true
            }

            CheckBox {
                id: d_minhold_check
                text: qsTr("Min Hold")
                Layout.fillWidth: true
            }

            SpinBox {
                id: d_avg_slider
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("FFT")
            }

            //                ComboBox {
            //                    id: d_fft_box
            //                    model: ["32", "64", "128", "256", "512", "1024", "2048", "4096"]
            //                    Layout.fillWidth: true
            //                }

            //                ComboBox {
            //                    id: d_fft_win_combo
            //                    model: ["None", "Hamming", "Hann", "Blackman", "Blackman-harris", "Rectangular", "Kaiser", "Flat-top"]
            //                    Layout.fillWidth: true
            //                }

            //                Label {
            //                    text: qsTr("Trigger")
            //                }

            //                ComboBox {
            //                    id: d_trigger_mode_combo
            //                    model: ["Free", "Auto", "Normal", "Tag"]
            //                    Layout.fillWidth: true
            //                }
        }
    }
}
