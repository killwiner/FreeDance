import QtQuick 2.0

Item {
    property int startTime: waitTime.sliderWaitTime.value
    property alias timer: timer
    visible: false

    width: 160
    height: 62

    Text {
        id: text2
        x: 8
        y: 19
        color: "white"
        text: "Start in : " + startTime + " sec"
        font.bold: true
        font.pixelSize: 22
    }

    Timer {
        id: timer
        interval: 1000
        repeat: true
        running: false
        onTriggered: {

            if(!startTime) {
                visible = false
                interf.receiveFromQml_recordCapture()
                memInfo.visible = true;
                memInfo.timer.running = true;
            }

            startTime = startTime - 1
         }
    }
}
