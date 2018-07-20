import QtQuick 2.4
import BleRxImpl 1.1

BleRxForm {
    objectName: "BleRx"

    BleRxImpl {
        id: dataSource
    }

    stateBtn.items: ["stopped", "running"]
    stateBtn.onSelectionChanged: {
        if ("running" === stateBtn.items[stateBtn.currentSelection]) {
            dataSource.start()
        } else {
            dataSource.stop()
        }
    }
    accessCode.model: ["test", "adv"]
    accessCode.onCurrentIndexChanged: {
        if ("test" === accessCode.items[accessCode.currentSelection]) {
            dataSource.setAccessCode(BleRxImpl.ACC_TEST)
        } else {
            dataSource.setAccessCode(BleRxImpl.ACC_ADVERTISING)
        }
    }

    Component.onCompleted: {
        console.log("onCompleted: " + objectName)
    }

    Component.onDestruction: {
        console.log("onDestruction: " + objectName)
    }
}
