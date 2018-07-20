import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2


import "."


RowLayout {
    property alias from: slider.from
    property alias to: slider.to
    property alias stepSize: slider.stepSize
    property alias value: slider.value
    property color color: label.color

    signal dataChanged(var value)

    implicitHeight: Math.max(slider.implicitHeight, label.implicitHeight)
    implicitWidth: (slider.implicitWidth + label.implicitWidth)


    Layout.fillWidth: true

    Slider {
        id: slider
        onValueChanged: {
            parent.dataChanged(value)
        }
        Layout.fillWidth: true
    }
    Label {
        id: label
        text: Math.floor(slider.value)
        Layout.fillWidth: true
    }
}
