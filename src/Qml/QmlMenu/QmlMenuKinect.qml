import QtQuick 2.3

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
            menuKinect.visible = false
        }
        menuText: qsTr("Connect Kinect")
    }

    QmlButton {
        id: menuButtonRunKinect
        x: 0
        y: 20
        menuArea.onClicked: {
            interf.receiveFromQml_runKinect()
            menuKinect.visible = false
        }
        menuText: qsTr("Run Kinect")
    }

    QmlButton {
        id: menuButtonStartCapture
        x: 0
        y: 40
        menuArea.onClicked: {
            interf.receiveFromQml_startCapture()
        }
        menuText: qsTr("Start capture")
    }

    QmlButton {
        id: menuButtonStop
        x: 0
        y: 60
        menuArea.onClicked: {

        }
        menuText: qsTr("Stop")
    }
}
