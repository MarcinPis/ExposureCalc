import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2


ApplicationWindow {
    id: window
    visible: true

    width: 400
    height: 650
    title: qsTr("Exposure Calc")

    minimumWidth: 250
    minimumHeight: 300

    onClosing: {
        if (Qt.platform.os == "android")
        {
            if (stackView.depth > 1)
            {
                close.accepted = false;
                stackView.pop();
            }
            else
            {
                close.accepted = true;
            }
        }
    }


    header: ToolBar {
        id: myToolBar
        contentHeight: toolButton.implicitHeight

        Label {
            text: stackView.currentItem.title
            font.bold: true
            anchors.centerIn: parent
        }

        ToolButton {
            id: toolButton
            anchors.right: parent.right
            property string settingsIcon: "graphics/settingsIcon.svg"
            property string backIcon: "graphics/backIcon.svg"

            Image {
                id: icon
                fillMode: Image.PreserveAspectFit
                anchors.centerIn: parent
                sourceSize.height: toolButton.background.height - 6
                height: sourceSize.height
                source: stackView.depth > 1 ? toolButton.backIcon : toolButton.settingsIcon
            }

            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.5
        height: window.height
        edge: Qt.RightEdge

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Settings")
                width: parent.width
                onClicked: {
                    stackView.push("qrc:/qml/Settings.qml")
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("About")
                width: parent.width
                onClicked: {
                    aboutDialog.open();
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "qrc:/qml/Home.qml"
        anchors.fill: parent
    }


    // About dialog ------------------------------------------------------------------------------------------------
    Dialog {
        id: aboutDialog
        modal: true
        focus: true
        title: qsTr("Exposure Calc")
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        contentHeight: aboutColumn.height

        Column {
            id: aboutColumn
            spacing: 15

            Label {
                width: aboutDialog.availableWidth
                text: qsTr("Thank you for using the Exposure Calc.")
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: qsTr("Please feel free to rate the app in the store ")
                      + qsTr("and share your thoughts.")
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                id: versionNumber
                width: aboutDialog.availableWidth
                text: qsTr("Exposure Calc v. 1.0")
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: qsTr("Author: Marcin Pisarski")
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }
        }
    }
}
