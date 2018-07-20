import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import QtQuick.VirtualKeyboard.Settings 2.2

// Style
import "."


Item {
    id: root

//    color: "#404040"

    property alias text: labelArea.text
    property alias defaultValue: textArea.text

    property alias validator: textArea.validator

    signal valueChanged(var value)

    implicitHeight: Math.max(labelArea.implicitHeight, textArea.implicitHeight)
    implicitWidth: (labelArea.implicitWidth + textArea.implicitWidth)

    RowLayout {
        anchors.fill: parent
        spacing: 6

        id: row

        Label {
            id: labelArea
            clip: false
            //Layout.preferredWidth: parent.width / 2
            color: "white"
            text: "Number"
            wrapMode: Text.NoWrap
            transformOrigin: Item.Center
        }


        TextField {
            id: textArea
            Layout.fillHeight: false
            Layout.fillWidth: true


            text: "0.0"
            horizontalAlignment: Text.AlignRight
            onPressed: {
                VirtualKeyboardSettings.locale = "en_DIGITS"
            }

            onAcceptableInputChanged: {
                //color = acceptableInput ? Style.inputText : "red"
            }

            onAccepted: {
                var d = Number.fromLocaleString(Qt.locale(), textArea.text);
                root.valueChanged(d)
            }
        }
    }
}
