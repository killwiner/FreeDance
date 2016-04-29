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

            menuFile.visible = false
        }
        menuText: qsTr("Create Skeleton")
    }
}
