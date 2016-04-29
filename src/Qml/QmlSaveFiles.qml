import QtQuick 2.3
import QtQuick.Dialogs 1.2

FileDialog {
    title: "Please choose a file"
    selectExisting: false
    onAccepted: {
        busy.running = true
        console.log("You chose: " + saveDialog.fileUrls)
        interf.receiveFromQml_saveFile(saveDialog.fileUrl);
    }
    onRejected: {
        console.log("Canceled")
    }
    Component.onCompleted: {
        visible = false
    }
}
