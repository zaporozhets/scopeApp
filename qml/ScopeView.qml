import QtQuick 2.0
import QtCharts 2.2

ChartView {
    property LineSeries series: lineSeries1

    function setMarkerXPosition(x) {
        markerX.clear()
        markerX.append(x, axisY.min)
        markerX.append(x, axisY.max)
    }

    function setMarkerYPosition(y) {
        markerY.clear()
        markerY.append(axisX.min, y)
        markerY.append(axisX.max, y)
    }

    id: chartView

    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    legend.visible: false

    ValueAxis {
        id: axisX
        min: 0
        max: 1024
    }

    ValueAxis {
        id: axisY
        min: -1.5
        max: +1.5
    }

    LineSeries {
        id: lineSeries1
        axisX: axisX
        axisY: axisY
    }

    LineSeries {
        id: markerX
        style: Qt.DotLine
        color: "red"
        axisX: axisX
        axisY: axisY
    }

    LineSeries {
        id: markerY
        style: Qt.DotLine
        color: "red"
        axisX: axisX
        axisY: axisY
    }
}
