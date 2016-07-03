import QtQuick 2.3

Rectangle {
    width: 120
    height: 20

    property alias menuText: text.text
    property alias menuArea: mouseArea

    MouseArea {

        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        hoverEnabled: true

    }

    color: mouseArea.containsMouse ? "#bbbbff" : "#aaaaaa"

    Text {
        id: text
        x: 16
        y: 3
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 14
        font.family: "Times New Roman"
    }
}
