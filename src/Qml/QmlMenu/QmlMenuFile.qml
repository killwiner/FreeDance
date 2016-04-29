import QtQuick 2.3

Item {
    width: 120
    height: 60
    visible: false

    QmlButton {
        id: menuButtonOpenFile
        x: 0
        y: 0
        menuArea.onClicked: {
            openFile.trigger()
            menuFile.visible = false
        }
        menuText: qsTr("Load Motion")
    }

    QmlButton {
        id: menuButtonSaveFile
        x: 0
        y: 20
        menuArea.onClicked: {
            saveFile.trigger()
            menuFile.visible = false
        }
        menuText: qsTr("Save Motion")
    }

    QmlButton {
        id: menuButtonQuit
        x: 0
        y: 40

        menuText: qsTr("Quit")
    }

}
