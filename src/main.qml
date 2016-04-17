import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.1

Item {
    id: qml_zone
    x: 0
    y: 0
    width: 1310
    height: 250

    MouseArea {

        id: mouseArea_qml_zone
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        hoverEnabled: true

            onClicked: { item_file_menu.visible = false }
    }

    Rectangle {
        id: rect_qml_zone
        visible: true
        width: 1310
        height: 250
        color: "#333333"
/*
        Interf {
            id: interf;
          }
*/
/*
        Connections {
            target: interf
*/
            /*
            onSendToQml_fbt: {
                textField1.text = val
            }
            onSendToQml_fbs: {
                sliderHorizontal1.value = val
            }
            */
//        }

        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            onAccepted: {
                console.log("You chose: " + fileDialog.fileUrls)
                onTriggered: interf.receiveFromQml_menuBar(0, fileDialog.fileUrl);
                button_play_pause.iconSource = "imgs/pause.png"
            }
            onRejected: {
                console.log("Canceled")
            }
            Component.onCompleted: visible = false
        }

        Action {
            id : openFile
            onTriggered: {
                fileDialog.title = "Load the motion"
                fileDialog.nameFilters = ["Video File (*.avi)"]
                fileDialog.visible = true
            }
        }

        Slider {

            id: sliderHorizontal_fb
            x: 92
            y: 118
            minimumValue : 0
            maximumValue : 255

            style: SliderStyle {
                groove: Rectangle {
                    implicitWidth: 200
                    implicitHeight: 8
                    color: "#555"
                    radius: 4
                }
                handle: Rectangle {
                    anchors.centerIn: parent
                    color: control.pressed ? "white" : "red"
                    border.color: "gray"
                    border.width: 2
                    implicitWidth: 12
                    implicitHeight: 12
                    radius: 6
                }
            }

            onValueChanged: {
                interf.receiveFromQml_fbs(sliderHorizontal_fb.value);
                textField_fb.text = sliderHorizontal_fb.value;
            }
        }

        ProgressBar {
            id: progressBar
            x: 1100
            y: 114

            style: ProgressBarStyle {
                    background: Rectangle {
                        radius: 2
                        color: "#faa"
                        border.color: "gray"
                        border.width: 1
                        implicitWidth: 200
                        implicitHeight: 24
                    }
                    progress: Rectangle {
                        color: "#faa"
                        border.color: "steelblue"
                    }
                }
        }

        Label {
            id: label_progress
            x: 989
            y: 122
            color: "#ffffff"
            text: qsTr("Progress :")
            font.pointSize: 10
            styleColor: "#000000"
        }

        Label {
            id: label_fb
            x: 22
            y: 118
            width: 70
            height: 14
            color: "#ffffff"
            text: qsTr("Blue filter :")
            font.pointSize: 10
        }

        TextField {
            id: textField_fb
            x: 305
            y: 114
            width: 66
            height: 22
            placeholderText: "0"

            validator: IntValidator { bottom:0; top: 255}

            onTextChanged: {
                interf.receiveFromQml_fbt(textField_fb.getText(0, 3));
                sliderHorizontal_fb.value = textField_fb.getText(0, 3);
            }
        }

        Button {
            id: button_go
            x: 1200
            y: 211
            text: qsTr("Go")
            enabled: true

            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 25
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#000"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#fff" : "#aaa" }
                        GradientStop { position: 1 ; color: control.pressed ? "#f77" : "#333" }
                    }
                }
            }
        }

        Item {
            id: item_menu
            x: 11
            y: 8
            width: 823
            height: 20
            //groupBox2.visible = true

            Rectangle {
                id: a
                x: 0
                y: 0
                width: 90
                height: 20

                MouseArea {

                    id: mouseArea_file
                    anchors.rightMargin: 0
                    anchors.bottomMargin: 0
                    anchors.leftMargin: 0
                    anchors.topMargin: 0
                        anchors.fill: parent
                        hoverEnabled: true

                        onClicked: { item_file_menu.visible = true }
                }

                color: mouseArea_file.containsMouse ? "#bbbbff" : "#aaaaaa"

                Text {
                    id: text_file
                    x: 35
                    y: 3
                    text: qsTr("File")
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 12
                }

                Item {
                    id: item_file_menu
                    x: 0
                    y: 20
                    width: 176
                    height: 208
                    visible: false

                    Rectangle {
                        id: rectangle_load_motion
                        x: 0
                        y: 0
                        width: 176
                        height: 20

                        MouseArea {

                            id: mouseArea_file_menu
                            anchors.rightMargin: 0
                            anchors.bottomMargin: 0
                            anchors.leftMargin: 0
                            anchors.topMargin: 0
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked: {
                                openFile.trigger()
                                item_file_menu.visible = false
                            }
                        }

                        color: mouseArea_file_menu.containsMouse ? "#bb77ff" : "#aa55aa"

                        Text {
                            id: text_load_motion
                            x: 35
                            y: 3
                            text: qsTr("Load Motion")
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: 12
                        }
                    }
                }
            }
        }

        Rectangle {
            x: 989
            y:204
            width: 152
            height: 32
            color: "#333333"
            RowLayout {
                height: 32
                    //anchors.fill: parent
                ToolButton {
                    id: button_play_pause
                    width: 32
                    height: 32
                        iconSource: "imgs/play.png"
                    }
                ToolButton {
                    id: button_record
                    width: 32
                    height: 32
                        iconSource: "imgs/record.png"
                    }
                ToolButton {
                    id: button_stop
                    width: 32
                    height: 32
                        iconSource: "imgs/stop.png"
                    }
                ToolButton {
                    id: button_preview
                    width: 32
                    height: 32
                        iconSource: "imgs/preview.png"
                    }
                }
            }
    }
}
