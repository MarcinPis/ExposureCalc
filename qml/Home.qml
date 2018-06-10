import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import QtQuick.Controls.Material 2.2


Page {
    id: root
    title: qsTr("Exposure Calculator")

    Component.onCompleted:
    {
        getCurrentExosure();
        getTargetExposure();
        FilterModel.dataChangedEmiter();
    }

    StackView.onActivating:
    {

        if(comboIso.currentText == "")
        {
            currentIndexIso = comboIso.count - 1;
            targetIndexIso = comboIso.count - 1;
        }

        if(comboAperture.currentText == "")
        {
            currentIndexAperture = comboAperture.count - 1;
            targetIndexAperture = comboAperture.count - 1;
        }

        if(comboShutter.currentText == "")
        {
            currentIndexShutter = comboShutter.count - 1;
            targettIndexShutter = comboShutter.count - 1;
        }

        getCurrentExosure();
        getTargetExposure();
    }


    /******************************************* Global properties START *******************************************/
    property int radioSwitchPosition: 1

    property alias currentIndexIso: comboIso.currentIndex
    property alias currentIndexShutter: comboShutter.currentIndex
    property alias currentIndexAperture: comboAperture.currentIndex

    property alias targetIndexIso: comboTargetIso.currentIndex
    property alias targettIndexShutter: comboTargetShutter.currentIndex
    property alias targetIndexAperture: comboTargetAperture.currentIndex

    /******************************************* Global properties END *********************************************/

    /******************************************* Global functions START ********************************************/
    function getCurrentExosure()
    {
        // Calculate the Exposure Value
        /*
        * stopValue == 100
        * precise == 101
        * nominal == 102
        stopInfo == 103
        */

        myCalculatorTest.calculateExposureValue(
                    comboAperture.model.data(comboAperture.model.index(comboAperture.currentIndex, 0),101),
                    comboShutter.model.data(comboShutter.model.index(comboShutter.currentIndex, 0), 101),
                    comboIso.model.data(comboIso.model.index(comboIso.currentIndex, 0), 101))
    }

    function getTargetExposure()
    {
        var filterSum = comboNd1.model.data(comboNd1.model.index(comboNd1.currentIndex, 0), 100)
                + comboNd2.model.data(comboNd2.model.index(comboNd2.currentIndex, 0), 100)
                + comboNd3.model.data(comboNd3.model.index(comboNd3.currentIndex, 0), 100)

        if (radioSwitchPosition === 1)
        {
            // calculate aperture value
            myCalculatorTest.calculateAparature(comboTargetShutter.model.data(
                                                    comboTargetShutter.model.index(comboTargetShutter.currentIndex, 0), 100),
                                                comboTargetIso.model.data(
                                                    comboTargetIso.model.index(comboTargetIso.currentIndex, 0), 100), filterSum)
        }
        else if (radioSwitchPosition === 2)
        {
            // calculate shutter value
            myCalculatorTest.calculateShutterValue(comboTargetAperture.model.data(
                                                       comboTargetAperture.model.index(comboTargetAperture.currentIndex, 0), 100),
                                                   comboTargetIso.model.data(comboTargetIso.model.index(
                                                                                 comboTargetIso.currentIndex, 0), 100), filterSum)
        }
        else if (radioSwitchPosition === 3)
        {
            // calculate iso value
            myCalculatorTest.calculateIsoValue(comboTargetAperture.model.data(
                                                   comboTargetAperture.model.index(comboTargetAperture.currentIndex, 0), 100),
                                               comboTargetShutter.model.data(comboTargetShutter.model.index(
                                                                                 comboTargetShutter.currentIndex, 0), 100), filterSum)
        }
    }
    /******************************************* Global functions END ********************************************/


    /******************************************* Global connections START ********************************************/
    Connections {
        target: myCalculatorTest
        onExposureValueChanged: {
            exposureValue.text = Value
        }
    }

    Connections {
        target: myCalculatorTest
        onApertureValueChanged: {

            comboTargetAperture.displayValue = Value
            errorLabel.text = Msg
        }
    }

    Connections {
        target: myCalculatorTest
        onShutterValueChanged: {
            comboTargetShutter.displayValue = Value
            errorLabel.text = Msg
        }
    }

    Connections {
        target: myCalculatorTest
        onIsoValueChanged: {
            comboTargetIso.displayValue = Value
            errorLabel.text = Msg
        }
    }

    Connections {
        target: FilterModel
        onFilterSettingsChanged: {
            comboNd1.textRole = Value
            comboNd2.textRole = Value
            comboNd3.textRole = Value
        }
    }

    /******************************************* Global connections END *********************************************/


    /******************************************* Home UI START ******************************************************/
    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: root.width
        contentHeight:  (currentRectangle.height + targetRectangle.height + 70)
        boundsBehavior: Flickable.StopAtBounds


        Rectangle {
            id: currentRectangle
            color: "#1Affffff" // partialy transparent
            radius: 10
            border.color: "lightgray"
            anchors.left: parent.left
            anchors.right:  parent.right
            anchors.top: parent.top
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 10
            height: currentExosureText.height + currentExposureRow.height

            // Current Exposure Label starts here ------------------------------------------------------------------------
            RowLayout {
                id: currentExosureText
                anchors.left: parent.left
                anchors.right:  parent.right
                spacing: 0

                Label {
                    id: currentLabel
                    text: qsTr("Current Exposure Value: ")
                    font.bold: true
                    anchors.centerIn: parent
                    Layout.topMargin: 15
                }

                Label {
                    id: exposureValue
                    anchors.left: currentLabel.right
                    anchors.top: currentLabel.top
                }
            }

            // Current Exposure starts here ------------------------------------------------------------------------
            RowLayout {
                id: currentExposureRow
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: currentExosureText.bottom
                spacing: 5

                ColumnLayout {
                    Layout.margins: 10
                    Layout.fillWidth: true

                    Label {
                        id: apertureLabel
                        text: qsTr("Aperature")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                    }

                    CustomComboBox {
                        id: comboAperture
                        enabled: true
                        model: CustomProxyAperture
                        Layout.fillWidth: true
                        textRole: "apertureNominal"
                        currentIndex: 0

                        onActivated: {
                            getCurrentExosure();
                            getTargetExposure();
                        }
                    }
                }

                ColumnLayout {
                    Layout.margins: 15
                    Layout.fillWidth: true

                    Label {
                        id: shutterLabel
                        text: qsTr("Shutter")
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }

                    CustomComboBox {
                        id: comboShutter
                        enabled: true
                        model: CustomProxyShutter
                        Layout.fillWidth: true
                        textRole: "shutterNominal"
                        currentIndex: 0

                        onActivated: {
                            getCurrentExosure();
                            getTargetExposure();
                        }
                    }
                }

                ColumnLayout {

                    Layout.margins: 15
                    Layout.fillWidth: true

                    Label {
                        id: isoLabel
                        text: qsTr("ISO")
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }

                    CustomComboBox {
                        id: comboIso
                        enabled: true
                        model: CustomProxyIso
                        Layout.fillWidth: true
                        textRole: "isoNominal"
                        currentIndex: 0

                        onActivated: {
                            getCurrentExosure();
                            getTargetExposure();
                        }
                    }
                }
            }
        }

        Rectangle {
            id: targetRectangle
            color: "#1Affffff" // partialy transparent
            border.color: "lightgray"
            radius: 10
            anchors.left: parent.left
            anchors.right:  parent.right
            anchors.top: currentRectangle.bottom
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.topMargin: 50
            height: targetExosureText.height + targetExposureRow.height + labelErrorLayout.height + ndFilterRow.height

            // Target Exposure Label starts here ------------------------------------------------------------------------
            RowLayout {
                id: targetExosureText
                anchors.left: parent.left
                anchors.right:  parent.right
                spacing: 0

                Label {
                    id: targetLabel
                    text: qsTr("Target Exposure: ")
                    font.bold: true
                    anchors.centerIn: parent
                    Layout.topMargin: 15
                }

                Label {
                    id: targetExposureValue
                    anchors.left: targetLabel.right
                    anchors.top: targetLabel.top
                }
            }

            // Target Exposure starts here ------------------------------------------------------------------------
            RowLayout {
                id: targetExposureRow
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: targetExosureText.bottom
                spacing: 5


                ButtonGroup { id: targetRadioButtons }

                ColumnLayout {
                    Layout.margins: 10
                    Layout.fillWidth: true


                    Label {
                        id: targetApertureLabel
                        text: qsTr("Aperature")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                    }

                    CustomComboBox {
                        id: comboTargetAperture
                        model: CustomProxyAperture
                        textRole: "apertureNominal"
                        Layout.fillWidth: true
                        enabled: !radioAperture.checked
                        currentIndex: 0

                        onActivated: {
                            getTargetExposure();
                        }
                    }

                    RadioButton {
                        id: radioAperture
                        ButtonGroup.group: targetRadioButtons
                        Layout.fillWidth: true
                        checked: true
                        onToggled: {
                            radioSwitchPosition = 1
                            getTargetExposure();
                        }
                    }
                }

                ColumnLayout {
                    Layout.margins: 15
                    Layout.fillWidth: true

                    Label {
                        id: targetShutterLabel
                        text: qsTr("Shutter")
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }

                    CustomComboBox {
                        id: comboTargetShutter
                        model: CustomProxyShutter
                        textRole: "shutterNominal"
                        Layout.fillWidth: true
                        enabled: !radioShutter.checked
                        currentIndex: 0

                        onActivated: {
                            getTargetExposure();
                        }
                    }

                    RadioButton {
                        id: radioShutter
                        ButtonGroup.group: targetRadioButtons
                        Layout.fillWidth: true
                        onToggled: {
                            radioSwitchPosition = 2
                            getTargetExposure();
                        }
                    }
                }

                ColumnLayout {
                    Layout.margins: 15
                    Layout.fillWidth: true

                    Label {
                        id: targetIsoLabel
                        text: qsTr("ISO")
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }

                    CustomComboBox {
                        id: comboTargetIso
                        model: CustomProxyIso
                        textRole: "isoNominal"
                        Layout.fillWidth: true
                        enabled: !radioIso.checked
                        currentIndex: 0

                        onActivated: {
                            getTargetExposure();
                        }
                    }

                    RadioButton {
                        id: radioIso
                        Layout.fillWidth: true
                        ButtonGroup.group: targetRadioButtons
                        onToggled: {
                            radioSwitchPosition = 3;
                            getTargetExposure();
                        }
                    }
                }
            }

            // Error label section starts here ------------------------------------------------------------------------
            RowLayout {
                id: labelErrorLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: targetExposureRow.bottom
                anchors.topMargin: -10
                spacing: 0

                Label {
                    id: errorLabel
                    color: "red"
                    anchors.centerIn: parent
                }
            }

            // ND Filters section starts here ------------------------------------------------------------------------
            RowLayout {
                id: ndFilterRow
                anchors.left: parent.left
                anchors.right:  parent.right
                spacing: 5
                anchors.top: labelErrorLayout.bottom

                ColumnLayout {
                    Layout.margins: 10
                    Layout.fillWidth: true

                    Label {
                        id: nd1Label
                        text: qsTr("ND1")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                    }

                    CustomComboBox {
                        id: comboNd1
                        enabled: true
                        model: FilterModel
                        textRole: "filterCokin"
                        Layout.fillWidth: true

                        onActivated: {
                            getTargetExposure();
                        }
                    }
                }

                ColumnLayout {
                    Layout.margins: 15
                    Layout.fillWidth: true

                    Label {
                        id: nd2Label
                        text: qsTr("ND2")
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true

                    }

                    CustomComboBox {
                        id: comboNd2
                        model: FilterModel
                        textRole: "filterCokin"
                        Layout.fillWidth: true

                        onActivated: {
                            getTargetExposure();
                        }
                    }
                }

                ColumnLayout {
                    Layout.margins: 15
                    Layout.fillWidth: true

                    Label {
                        id: nd3Label
                        text: qsTr("ND3")
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.fillWidth: true
                    }

                    CustomComboBox {
                        id: comboNd3
                        model: FilterModel
                        textRole: "filterCokin"
                        Layout.fillWidth: true

                        onActivated: {
                            getTargetExposure();
                        }
                    }
                }
            }
        }
    }
}
