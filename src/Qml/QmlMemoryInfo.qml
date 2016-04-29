import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    visible: false
    property alias timer: timer
    property alias buttonStop: button_stop

    width: 256
    height: 182
    color: "#000000"

    Label {
        x: 64
        y: 8
        width: 70
        height: 14
        color: "#ffffff"
        text: qsTr("Memory info")
        font.bold: true
        font.pointSize: 14
    }
    Label {
        x: 8
        y: 55
        width: 70
        height: 14
        color: "#ffffff"
        text: qsTr("Memory total :")
        font.pointSize: 12
    }
    Label {
        x: 8
        y: 85
        width: 70
        height: 14
        color: "#ffffff"
        text: qsTr("Memory free :")
        font.pointSize: 12
    }
    Label {
        x: 8
        y: 115
        width: 70
        height: 14
        color: "#ffffff"
        text: qsTr("Free space :")
        font.pointSize: 12
    }
    Text {
        id: mem_total
        x: 139
        y: 55
        width: 109
        height: 14
        color: "#ff00ff"
        font.pointSize: 12
        text: stringMemTotal
    }
    Text {
        id: mem_free
        x: 139
        y: 85
        width: 109
        height: 14
        color: "#ff00ff"
        font.pointSize: 12
        text: stringMemFree
    }
    Text {
        id: ration
        x: 139
        y: 115
        width: 109
        height: 14
        color: "#ff00ff"
        font.pointSize: 12
        text: stringMemRatio + " %"
    }
    Button {
        id: button_stop
        x: 78
        y: 149
        text: qsTr("Stop")
        enabled: true

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

    Timer {
        id: timer
        interval: 1000
        repeat: true
        running: false
        onTriggered: {
            interf.receiveFromQml_getMemInfo()
        }
    }
}
