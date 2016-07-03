import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    width: 393
    height: 35

    property alias sliderNbrPass: sliderHorizontal_np

    Label {
        id: label_np
        x: 8
        y: 8
        width: 70
        height: 14
        color: "#ffffff"
        text: qsTr("Nbr of pass :")
        font.pointSize: 10
    }

    TextField {
        id: textField_np
        x: 314
        y: 4
        width: 66
        height: 22
        style: TextFieldStyle {
            textColor: "#fff"
            font.pointSize: 12
            font.family: "Times New Roman"

            background: Rectangle {
                radius: 2
                implicitWidth: 100
                implicitHeight: 24
                border.color: "#f99"
                border.width: 1
                color: "#555"
            }
        }
        validator: IntValidator { bottom:0; top: 30}

        onTextChanged: {
            interf.receiveFromQml_npt(textField_np.getText(0, 3));
            sliderHorizontal_np.value = textField_np.getText(0, 3);
        }
    }

    Slider {

        id: sliderHorizontal_np
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
            interf.receiveFromQml_nps(sliderHorizontal_np.value);
            textField_np.text = sliderHorizontal_np.value;
        }
    }
}

