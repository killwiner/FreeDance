import QtQuick 2.3
import QtQuick.Dialogs 1.2

FileDialog {
    title: "Please choose a file"
    onAccepted: {
        busy.running = true
        console.log("You chose: " + openDialog.fileUrls)
        interf.receiveFromQml_loadFile(openDialog.fileUrl);
        button_play_pause.iconSource = "imgs/pause.png"
    }
    onRejected: {
        console.log("Canceled")
    }
    Component.onCompleted: {
        visible = false
    }
}
