import QtQuick 2.4
import GeneralSpectrumImpl 1.1

GeneralSpectrumForm {
    objectName: "GeneralSpectrum"

    Component.onCompleted: {
        dataSource.setSeries(scopeView.series)
    }

    Component.onDestruction: {
    }

    GeneralSpectrumImpl {
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


    function toggleGrid() {}
    function toggleAxisLabels() {}
    function toggleMaxHold(en) {
        d_maxhold_check.checkState = en ? Qt.Checked : Qt.Unchecked
    }
    function toggleMinHold(en) {
        d_minhold_check.checkState = en ? Qt.Checked : Qt.Unchecked
    }
    function notifyAvgSlider() {}
    function setFFTAverage() {}
    function toggleFFTSize() {}
    function toggleFFTWindow() {}
    function toggleTriggerMode() {}
    function toggleStopButton() {}
}
