import QtQuick 2.4
import BleDutImpl 1.1

BleDutForm {
    objectName: "BleDut"

    BleDutImpl {
        id: dataSource
    }

    pattern.model: ["PRBS9", "11110000", "10101010", "PRBS15", "11111111", "00000000", "00001111", "01010101"]
    Component.onCompleted: {
        console.log("onCompleted: " + objectName)
    }

    Component.onDestruction: {
        console.log("onDestruction: " + objectName)
    }

    resetBtn.onClicked: {
        dataSource.close()
        dataSource.open("hci0")
        dataSource.reset()
    }

    leTxTestBtn.onClicked: {
        dataSource.leTxTest(channel.value, pattern.currentIndex, payloadLength.value)
    }

    leTestEndBtn.onClicked: {
        dataSource.leTestEnd()
    }
}
