import QtQuick 2.4
import GeneralTimeImpl 1.1

GeneralTimeForm {
    objectName: "GeneralTimeForm"

    Component.onCompleted: {
        dataSource.setSeries(scopeView.series)
        dataSource.setMode(modeBtn.currentSelection)
    }

    Component.onDestruction: {
        dataSource.stop()
    }

    GeneralTimeImpl {
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

    modeBtn.items: ["Power", "FSK"]
    modeBtn.onSelectionChanged: {
        if ("Power" === modeBtn.items[modeBtn.currentSelection]) {
            dataSource.setMode(GeneralTimeImpl.MODE_POWER)
        } else {
            dataSource.setMode(GeneralTimeImpl.MODE_FSK)
        }
    }

    freqArea.validator: DoubleValidator {
        bottom: 0
        top: 6000
        decimals: 1
        notation: DoubleValidator.StandardNotation
    }

    freqArea.onValueChanged: {
        dataSource.setCarrierFreq(value * 1e6)
    }

    triggetSlider.onChanged: {
        scopeView.setMarkerYPosition(value)
        dataSource.setTriggerLevel(value)
    }
}
