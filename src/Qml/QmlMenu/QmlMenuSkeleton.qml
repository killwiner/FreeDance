import QtQuick 2.3

Item {
    width: 120
    height: 60
    visible: false

    QmlButton {
        id: menuButtonCreateSkeleton
        x: 0
        y: 0
        menuArea.onClicked: {
            busy.running = true
            menuSkeleton.visible = false
            progressBar.timer.running = true
            interf.receiveFromQml_createSkeleton();
        }
        menuText: qsTr("Create Skeleton")
    }

    QmlButton {
        id: menuButtonExportSkeleton
        x: 0
        y: 20
        menuArea.onClicked: {
            menuSkeleton.visible = false
            interf.receiveFromQml_exportSkeleton();
        }
        menuText: qsTr("Export Skeleton")
    }
}
