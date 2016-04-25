import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    x: 0
    y: 0
    width: 1310
    height: 250
    color: "#aa0000"
    opacity : 0.7
    visible: false

    property alias messageWindow: message_window

    MouseArea {

        id: mouseArea_desable
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        hoverEnabled: true
    }

    Rectangle {
        id: message_window
        border.width: 4
        border.color: "grey"
        x: 512
        y: 104
        width: 287
        height: 108
        color: "white"

        property alias text: text

        Text {
            id: text
            x: 53
            y: 30
            text: stringMessage
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 16
            font.family: "Arial"
            font.bold: true
        }

        Button {
            id: button_ok
            x: 179
            y: 75
            text: qsTr("Ok")
            enabled: true

            onClicked: {
                message.visible = false
            }

            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#000"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#fff" : "#aaa" }
                        GradientStop { position: 1 ; color: control.pressed ? "#f77" : "#333" }
                    }
                }
            }
        }
    }
}
