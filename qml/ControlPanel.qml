import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    id: root
    default property alias _contentChildren: content.data
    //default property alias _contentChildren: content.data

    width: 150
    Layout.fillHeight: true

    ScrollView {
        anchors.fill: parent
        id: scrollView

        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        ScrollBar.horizontal.interactive: false
        ScrollBar.vertical.interactive: true

        ColumnLayout {
            width: 150
            Layout.fillHeight: true
            id: content
        }
    }
}
