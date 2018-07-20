import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

//import QtQuick.VirtualKeyboard 2.2
//import QtQuick.VirtualKeyboard.Settings 2.0


// Style
import "."

ApplicationWindow {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Scope")
    color: Style.background



    SlideMenu {
        id: slideMenu
        height: pageLoader.height
        width: 300
        x: -width
        y: 0

        currentIndex: 0

        modelMenu: ListModel {
            ListElement {
                item: "Time Measurements"
                icon: "qrc:/images/icon_game.png"
                form: "GeneralTime.qml"
            }
            ListElement {
                item: "Spectrum WIP"
                icon: "qrc:/images/icon_game.png"
                form: "GeneralSpectrum.qml"
            }
            ListElement {
                item: "Ble Rx"
                icon: "qrc:/images/bt.png"
                form: "BleRx.qml"
            }
            ListElement {
                item: "Ble DUT"
                icon: "qrc:/images/bt.png"
                form: "BleDut.qml"
            }
            ListElement {
                item: "Settings"
                icon: "qrc:/images/icon_settings.png"
                form: "Settings.qml"
            }
            ListElement {
                item: "About"
                icon: "qrc:/images/icon_info.png"
                form: "About.qml"
            }
        }
        onMenuItemClicked: {
            pageLoader.source = modelMenu.get(index).form
        }
    }

    ColumnLayout {
        spacing: 0
        anchors.fill: parent
        Loader {
            id: pageLoader
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: "About.qml"
            //source: "BleRx.qml"
        }
        RowLayout {
            id: statusBar
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.fillHeight: false
            Layout.fillWidth: true


            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Button {
                text: "Menu"
                width: 250

                onClicked: {
                    slideMenu.togleMenu()
                }
            }
        }
    }

//    InputPanel {
//        id: inputPanel
//        z: 89
//        y: active ? (parent.height - inputPanel.height) : parent.height
//        anchors.left: parent.left
//        anchors.right: parent.right
//    }

}
