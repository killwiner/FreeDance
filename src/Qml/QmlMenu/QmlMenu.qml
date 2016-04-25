import QtQuick 2.3
import "QmlMenuFile"
import "QmlMenuKinect"

Item {
    width: 240
    height: 20

    property alias menuFile: menuFile
    property alias menuKinect: menuKinect

    QmlMenuFile {
        id: menuFile
        x: 0
        y: 30
    }

    QmlMenuKinect {
        id: menuKinect
        x: 80
        y: 30
    }

    QmlButton {
        id: file
        width: 80
        x: 0
        y: 0
        menuArea.onClicked: {
            menuFile.visible = true
            menuKinect.visible = false
        }
        menuText: qsTr("File")
    }

    QmlButton {
        id: kinect
        width: 80
        x: 80
        y: 0
        menuArea.onClicked: {
            menuFile.visible = false
            menuKinect.visible = true
        }
        menuText: qsTr("Kinect")
    }

    QmlButton {
        id: skeleton
        width: 80
        x: 160
        y: 0
        //menuArea.onClicked: {  }
        menuText: qsTr("Skeleton")
    }
}

