/*************************************************************************/
/* This file is part of Tron.                                            */
/*                                                                       */
/*  Tron is free software: you can redistribute it and/or modify         */
/*  it under the terms of the GNU General Public License as published by */
/*  the Free Software Foundation, either version 3 of the License, or    */
/*  (at your option) any later version.                                  */
/*                                                                       */
/*  Tron is distributed in the hope that it will be useful,              */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/*  GNU General Public License for more details.                         */
/*                                                                       */
/*  You should have received a copy of the GNU General Public License    */
/*  along with Tron.  If not, see <http://www.gnu.org/licenses/>.        */
/*************************************************************************/

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import "Qml"
import "Qml/QmlMenu"

Item {
    id: qml_zone
    x: 0
    y: 0
    width: 1284
    height: 250

    property var stringMessage: "message"
    property var stringMemTotal: "------"
    property var stringMemFree: "------"
    property var stringMemRatio: "------"

    QmlOpenFiles {id: openDialog}
    QmlSaveFiles {id: saveDialog}

    MouseArea {

        id: mouseArea_qml_zone
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            qmlMenu.menuFile.visible = false
            qmlMenu.menuKinect.visible = false
        }
    }

    // action to open the file
    Action {

        id: openFile
        onTriggered: {
            openDialog.nameFilters = ["Video File (*.avi)"]
            openDialog.visible = true
        }

    }

    // action to save the file
    Action {
        id: saveFile
        onTriggered: {
            saveDialog.visible = true
        }
    }

    Rectangle {
        id: rect_qml_zone
        visible: true
        width: 1310
        height: 250
        color: "#333333"

        BusyIndicator {
            id: busy
            x : 623
            y: 97
            width: 64
            height: 64
            running: false
        }

        Connections {
            target: interf

            onSendToQml_play_pause: {
                play_pause ? button_play_pause.iconSource = "imgs/pause.png" : button_play_pause.iconSource = "imgs/play.png"
            }

            onSendToQml_loaded_saved: {
                busy.running = false;
                progressBar.timer.running = false;
                progressBar.value = 0;
            }

            onSendToQml_smoth_s: {
                smoth.sliderSmoth.value = val;
            }

            onSendToQml_escapeFs: {
                escapeF.sliderEscpaeF.value = val;
            }

            onSendToQml_fbs: {
                filterBlue.sliderBlue.value = val;
            }

            onSendToQml_fgs: {
                filterGreen.sliderGreen.value = val;
            }

            onSendToQml_frs: {
                filterRed.sliderRed.value = val;
            }

            onSendToQml_nps: {
                nbrPass.sliderNbrPass.value = val;
            }

            onSendToQml_wts: {
                waitTime.sliderWaitTime.value = val;
            }

            onSendToQml_kinectOn: {
                img_kinect.visible = true;
            }

            onSendToQml_message: {
                stringMessage = val;
                message.visible = true;
                qmlMenu.menuFile.visible = false
                qmlMenu.menuKinect.visible = false
            }

            onSendToQml_stopWatch: {
                stopWatch.visible = true;
                stopWatch.timer.running = true;
                qmlMenu.menuKinect.visible = false
            }

            onSendToQml_memInfo: {
                stringMemTotal = mem_total;
                stringMemFree = mem_free;
                stringMemRatio = mem_ratio;
            }

            onSendToQml_loadFile: {
                openFile.trigger();
            }

            onSendToQml_progress: {
                progressBar.value = val;
            }

            onSendToQml_exportBVH: {
                saveDialog.nameFilters = ["Video File (*.bvh)"]
                saveFile.trigger()
            }
        }

        ProgressBar {
            id: progressBar
            x: 1067
            y: 114
            property alias timer: timer

            style: ProgressBarStyle {
                background: Rectangle {
                    radius: 2
                    color: "#999999"
                    border.color: "black"
                    border.width: 1
                    implicitWidth: 200
                    implicitHeight: 24
                }
                progress: Rectangle {
                    color: "#ff5555"
                    border.color: "black"
                }
            }
            Timer {
                id: timer
                interval: 1000
                repeat: true
                running: false
                onTriggered: {
                    interf.receiveFromQml_getProgress();
                }
            }
        }

        Label {
            id: label_progress
            x: 983
            y: 118
            color: "#ffffff"
            text: qsTr("Progress :")
            font.pointSize: 10
            styleColor: "#000000"
        }

        QmlFilterBlue {
            id: filterBlue
            x: 22
            y: 100
        }

        QmlFilterGreen {
            id: filterGreen
            x: 22
            y: 125
        }

        QmlFilterRed {
            id: filterRed
            x: 22
            y: 150
        }

        QmlWaitTime {
            id: waitTime
            x: 22
            y: 175
        }

        QmlNbrPass {
            id: nbrPass
            x: 22
            y: 200
        }

        QmlSmoth {
            id: smoth
            x: 500
            y: 175
        }


        QmlEscapeFrames {
            id: escapeF
            x: 500
            y: 200
        }

        Button {
            id: button_go
            x: 1167
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

        QmlMenu {
            id: qmlMenu
            x: 4
            y: 4
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
                    onClicked: interf.receiveFromQml_play_pause();
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
                    onClicked: interf.receiveFromQml_stop();
                }
                ToolButton {
                    id: button_preview
                    width: 32
                    height: 32
                    iconSource: "imgs/preview.png"
                    onClicked: interf.receiveFromQml_preview();
                }
            }
        }

        Image {
            id: img_kinect
            x: 1203
            y: 8
            width: 64
            height: 64
            source: "imgs/kinect.png"
            visible: false
        }

        QmlMessage {
            id: message
        }

        QmlStopWatch {
            id: stopWatch
            x: 575
            y: 101
        }
        QmlMemoryInfo {
            id:memInfo
            x: 500
            y: 60
            buttonStop.onClicked: {
                timer.running = false
                visible = false
                interf.receiveFromQml_play();
            }
        }
    }
}

