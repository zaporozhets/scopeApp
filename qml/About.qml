import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    objectName: "About"
    anchors.fill: parent

    Rectangle {
        color: "red"
        anchors.fill: parent
    }

    Component.onCompleted: {
        console.log("onCompleted: " + objectName)
    }

    Component.onDestruction: {
        console.log("onDestruction: " + objectName)
    }
}
