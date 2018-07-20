import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: button

    property string text: "Option: "
    property variant items: ["first"]
    property int currentSelection: 0
    signal selectionChanged(variant selection)

    signal clicked

    implicitWidth: buttonText.implicitWidth + 5
    implicitHeight: buttonText.implicitHeight


    Button {
        id: buttonText
        width: parent.width
        height: parent.height

        text: button.text + button.items[currentSelection]
        onClicked: {
            currentSelection = (currentSelection + 1) % items.length;
            selectionChanged(button.items[currentSelection]);
        }
    }
}
