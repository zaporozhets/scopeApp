import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

import "."

Item {
    id: root
    signal menuItemClicked(var index)

    property bool m_active: false

    property ListModel modelMenu
    property color backgroundColor: background.color

    property int currentIndex: listViewMenu.currentIndex
    z: 3

    function togleMenu() {
        m_active = !m_active
        x = m_active ? 0 : -width
    }

    Behavior on x { NumberAnimation { duration: 500; easing.type: Easing.OutQuad } }
    onXChanged: {

    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: "white"
    }

    Rectangle {
        id: logoWtapper
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width
        height: width*0.5
        color: Style.primary
        clip: true
        Image {
            id: imgLogo
            source: "qrc:/images/background.jpg"
            height: parent.height
            width: parent.width
            antialiasing: true
            smooth: true
            anchors.top: parent.top
            anchors.left: parent.left
            opacity: 0.5
        }
    }

    ListView {
        id: listViewMenu
        anchors.top: logoWtapper.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        model: modelMenu
        delegate: componentDelegate
    }

    Component {
        id: componentDelegate

        Rectangle {
            id: wrapperItem
            height: 60
            width: parent.width
            color: wrapperItem.ListView.isCurrentItem || ma.pressed ? Style.currentHighlightItem : "transparent"
            Image {
                id: imgItem
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 0.5*imgItem.width
                height: parent.height*0.5
                width: height
                source: icon
                visible: icon != ""
                smooth: true
                antialiasing: true
            }

            Label {
                id: textItem
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: imgItem.right
                anchors.leftMargin: 0.7*imgItem.width
                text: item
                font.pixelSize: parent.height*0.3
                color: wrapperItem.ListView.isCurrentItem ? Style.darkPrimary : Style.primaryText
            }


            MouseArea {
                id: ma
                anchors.fill: parent
                enabled: m_active
                onClicked: {
                    listViewMenu.currentIndex = index
                    root.menuItemClicked(index)
                    root.togleMenu()
                }
            }
        }
    }
}
