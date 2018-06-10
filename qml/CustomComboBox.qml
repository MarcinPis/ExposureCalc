import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import QtQuick.Controls.impl 2.2
import QtQuick.Templates 2.2 as T
import QtQuick.Controls.Material 2.2

T.ComboBox {
    id: root
    focusPolicy: Qt.NoFocus
    property string displayValue: ""
    property bool popupStatus: false

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                                         contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                                          Math.max(contentItem.implicitHeight,
                                                   indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)

    leftPadding: 0; rightPadding: 0

    delegate: ItemDelegate {
        background: Item{} // items are not highlighted
        width: parent.width
        height: 40 // controls item height on the list
        leftPadding: 0; rightPadding: 0; topPadding: 0; bottomPadding: 0

        contentItem: Text {
            leftPadding: 0; rightPadding: 0; topPadding: 0; bottomPadding: 0
            height: 40
            text: root.textRole ? (Array.isArray(root.model) ? modelData[root.textRole] : model[root.textRole]) : modelData
            font: root.font
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }

    contentItem: Text {

        leftPadding: 0; rightPadding: 0; topPadding: 0; bottomPadding: 0
        text: root.enabled ? root.displayText : displayValue
        enabled: root.editable
        font: root.font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    background: Rectangle {
        // Background properties of ComboBox
        radius: 10
        implicitWidth: 100
        implicitHeight: 40 // height of labal text
        color: root.enabled ? "white" : "lightgrey"
        border.color: Material.accent
        border.width: !root.enabled ? 2 : 0
        visible: !root.flat || root.down
    }

    popup: T.Popup {
        modal: true // dim the background
        y: root.height - root.implicitHeight
        width: root.width
        implicitHeight: 300 // height of whole list

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: root.popup.visible ? root.delegateModel : null
            currentIndex: root.highlightedIndex
            boundsBehavior: Flickable.StopAtBounds
            highlightMoveDuration: 0

            T.ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            radius: 10
        }
    }
}
