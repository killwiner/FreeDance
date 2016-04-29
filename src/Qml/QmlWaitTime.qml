import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    width: 393
    height: 35

    property alias sliderWaitTime: sliderHorizontal_wt

    Label {
        id: label_wt
        x: 8
        y: 8
        width: 70
        height: 14
        color: "#ffffff"
        text: qsTr("Wait time :")
        font.pointSize: 10
    }

    TextField {
        id: textField_wt
        x: 314
        y: 4
        width: 66
        height: 22

        validator: IntValidator { bottom:0; top: 30}

        onTextChanged: {
            sliderHorizontal_wt.value = textField_wt.getText(0, 3);
        }
    }

    Slider {

        id: sliderHorizontal_wt
        x: 97
        y: 9
        minimumValue : 0
        maximumValue : 30

        style: SliderStyle {
            groove: Rectangle {
                implicitWidth: 200
                implicitHeight: 8
                color: "#555"
                radius: 4
            }
            handle: Rectangle {
                anchors.centerIn: parent
                color: control.pressed ? "white" : "red"
                border.color: "gray"
                border.width: 2
                implicitWidth: 12
                implicitHeight: 12
                radius: 6
            }
        }

        onValueChanged: {
            textField_wt.text = sliderHorizontal_wt.value;
        }
    }
}

