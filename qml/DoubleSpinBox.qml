import QtQuick 2.0

import QtQuick.Controls 2.1

Item {
    id: root
    property int decimals: 2
    property real value: 0.0
    property real from: 0.0
    property real to: 100.0
    property real stepSize: 1.0

    width: spinbox.width
    height: spinbox.height


    signal changed(real value)

    SpinBox{
        property real factor: Math.pow(10, root.decimals)
        id: spinbox

        stepSize: root.stepSize*factor
        value: root.value*factor
        to : root.to*factor
        from : root.from*factor

        validator: DoubleValidator {
            bottom: Math.min(spinbox.from, spinbox.to)*spinbox.factor
            top:  Math.max(spinbox.from, spinbox.to)*spinbox.factor
        }

        textFromValue: function(value, locale) {
            return Number(value / 100).toLocaleString(locale, 'f', root.decimals)
        }

        valueFromText: function(text, locale) {
            return Number.fromLocaleString(locale, text) * 100
        }

        onValueFromTextChanged: {
            console.log("onValueFromTextChanged")
        }

        onValueChanged: {
            root.changed(spinbox.value/100)
        }
    }
}
