import QtQuick 2.3

import "../"

Item {
    width: 120
    height: 60
    visible: false

    QmlButton {
        id: menuButtonConnectKinect
        x: 0
        y: 0
        menuArea.onClicked: {
            interf.receiveFromQml_connectKinect()
        }
        menuText: qsTr("Connect Kinect")
    }

    QmlButton {
        id: menuButtonCapture
        x: 0
        y: 20
        menuArea.onClicked: {

        }
        menuText: qsTr("Capture")
    }
}
