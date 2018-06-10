import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Qt.labs.settings 1.0


Page {
    id: root
    title: qsTr("Settings")

    // GLOBAL properties ***************************************
    readonly property int sidePageMargin: 10
    readonly property int horizontalInsideMargin: 15
    readonly property int defaultRadius: 10
    readonly property int sliderSideMargins: 20
    // *********************************************************

    StackView.onActivating: {
        radioStopFull.checked = stopSettings.stopScaleIndex == 1;
        radioStopHalf.checked = stopSettings.stopScaleIndex == 2;
        radioStopThird.checked = stopSettings.stopScaleIndex == 3;

        radioFilterCokin.checked = stopSettings.filterScaleIndex == 1;
        radioFilterLee.checked = stopSettings.filterScaleIndex == 2;
        radioFilterStops.checked = stopSettings.filterScaleIndex == 3;
    }

    function updateSettings() {
        IsoModel.dataChangedEmiter();
        ShutterModel.dataChangedEmiter();
        ApertureModel.dataChangedEmiter();
        FilterModel.dataChangedEmiter();
    }

    StackView.onDeactivating:  {
        updateSettings();
    }


    // Settings starts here ----------------------------------------------------------
    Settings {
        id: exposureSettings
        category: "exposureTriangle"
        property alias apertureMin: minApertureSlider.value
        property alias apertureMax: maxApertureSlider.value
        property variant aperMinStop: minApertureList.get(apertureMin).value
        property variant aperMaxStop: maxApertureList.get(apertureMax).value
        property variant aperMinVal: minApertureList.get(apertureMin).name
        property variant aperMaxVal: maxApertureList.get(apertureMax).name

        property alias isoMin: minIsoSlider.value
        property alias isoMax: maxIsoSlider.value
        property variant isoMinStop: minIsoList.get(isoMin).value
        property variant isoMaxStop: maxIsoList.get(isoMax).value
        property variant isoMinVal: minIsoList.get(isoMin).name
        property variant isoMaxVal: maxIsoList.get(isoMax).name

        property alias shutterMax: maxShutterSlider.value
        property variant shutterMaxStop: maxShutterList.get(shutterMax).value
        property variant shutterMaxVal: maxShutterList.get(shutterMax).name
    }

    Settings {
        id: stopSettings
        category: "scales"
        property int stopScaleIndex: 3
        property int filterScaleIndex: 3
    }

    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: root.width
        contentHeight:  (stopScaleRectangle.height + filterScaleRectangle.height
                        + apertureSlidersRectangle.height + isoSlidersRectangle.height + shutterSlidersRectangle.height + 70)
        boundsBehavior: Flickable.StopAtBounds


        // Stop scale settings starts here -----------------------------------------------
        Rectangle {
            id: stopScaleRectangle
            color: "#11000000"
            border.color: "lightgray"
            radius: defaultRadius
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.leftMargin: sidePageMargin
            anchors.rightMargin: sidePageMargin
            anchors.topMargin: 10
            height: stopScaleLayout.height + stopScaleButtons.height

            RowLayout {
                id: stopScaleLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: parent.top
                spacing: 0

                Label {
                    id: stopScaleLabel
                    text: qsTr("Stop Scale")
                    font.bold: true
                    anchors.centerIn: parent
                    Layout.topMargin: horizontalInsideMargin
                }
            }

            RowLayout {
                id: stopScaleButtons
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: stopScaleLayout.bottom
                anchors.leftMargin: -15
                anchors.rightMargin: -15
                spacing: 0

                ButtonGroup { id: stopScaleGroup }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: -10

                    RadioButton {
                        id: radioStopFull
                        ButtonGroup.group: stopScaleGroup
                        Layout.fillWidth: true

                        onToggled: stopSettings.stopScaleIndex = 1
                    }

                    Label {
                        id: labelStopFull
                        text: qsTr("1")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.topMargin: -10
                        Layout.bottomMargin: horizontalInsideMargin
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: -10

                    RadioButton {
                        id: radioStopHalf
                        ButtonGroup.group: stopScaleGroup
                        Layout.fillWidth: true

                        onToggled: stopSettings.stopScaleIndex = 2
                    }

                    Label {
                        id: labelStopHalf
                        text: qsTr("1/2")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.topMargin: -10
                        Layout.bottomMargin: horizontalInsideMargin
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: -10

                    RadioButton {
                        id: radioStopThird
                        ButtonGroup.group: stopScaleGroup
                        Layout.fillWidth: true

                        onToggled: stopSettings.stopScaleIndex = 3
                    }

                    Label {
                        id: labelStopThird
                        text: qsTr("1/3")
                        Layout.fillWidth: true

                        horizontalAlignment: Qt.AlignHCenter
                        Layout.topMargin: -10
                        Layout.bottomMargin: horizontalInsideMargin
                    }
                }
            }
        }


        // ND scale settings starts here -----------------------------------------------
        Rectangle {
            id: filterScaleRectangle
            color: "#11000000"
            border.color: "lightgray"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: stopScaleRectangle.bottom
            anchors.leftMargin: sidePageMargin
            anchors.rightMargin: sidePageMargin
            anchors.topMargin: 10
            height: filterScaleLayout.height + filterScaleButtons.height
            radius: defaultRadius

            RowLayout {
                id: filterScaleLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.margins: 20
                spacing: 0

                Label {
                    id: filterScaleLabel
                    text: qsTr("ND Filter Scale")
                    font.bold: true
                    anchors.centerIn: parent
                    Layout.topMargin: horizontalInsideMargin
                }
            }

            RowLayout {
                id: filterScaleButtons
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: filterScaleLayout.bottom
                anchors.leftMargin: -15
                anchors.rightMargin: -15
                spacing: 0

                ButtonGroup { id: filterSettings }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: -10

                    RadioButton {
                        id: radioFilterCokin
                        ButtonGroup.group: filterSettings
                        Layout.fillWidth: true

                        onToggled: stopSettings.filterScaleIndex = 1
                    }

                    Label {
                        id: labelFilterCokin
                        text: qsTr("ND2")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.topMargin: -10
                        Layout.bottomMargin: horizontalInsideMargin
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: -10

                    RadioButton {
                        id: radioFilterLee
                        ButtonGroup.group: filterSettings
                        Layout.fillWidth: true

                        onToggled: stopSettings.filterScaleIndex = 2
                    }

                    Label {
                        id: labelFilterLee
                        text: qsTr("0.3ND")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.topMargin: -10
                        Layout.bottomMargin: horizontalInsideMargin
                    }
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: -10

                    RadioButton {
                        id: radioFilterStops
                        ButtonGroup.group: filterSettings
                        Layout.fillWidth: true

                        onToggled: stopSettings.filterScaleIndex = 3
                    }

                    Label {
                        id: labelFilterStops
                        text: qsTr("Stop")
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.topMargin: -10
                        Layout.bottomMargin: horizontalInsideMargin
                    }
                }
            }
        }


        // Aperture max Slider setup starts here ----------------------------------
        Rectangle {
            id: apertureSlidersRectangle
            color: "#11000000"
            border.color: "lightgray"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: filterScaleRectangle.bottom
            anchors.leftMargin: sidePageMargin
            anchors.rightMargin: sidePageMargin
            anchors.topMargin: 10
            height: apertureMaxLayout.height + apertureMinLayout.height
            radius: defaultRadius

            RowLayout {
                id: apertureMaxLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.leftMargin: sliderSideMargins
                anchors.rightMargin: sliderSideMargins
                spacing: 0

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: horizontalInsideMargin

                    RowLayout {
                        Label {
                            id: maxApertureLabel
                            text: qsTr("Max Aperture:")
                            font.bold: true
                            horizontalAlignment: Qt.AlignHCenter
                        }

                        Label {
                            id: maxApertureValueLabel
                            text: maxApertureList.get(maxApertureSlider.value).name
                            horizontalAlignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                        }
                    }

                    Slider {
                        id: maxApertureSlider
                        from: 0
                        to: 6
                        stepSize: 1
                        Layout.fillWidth: true
                        snapMode: Slider.SnapAlways
                        Layout.topMargin: -5

                    }

                    ListModel {
                        id: maxApertureList
                        ListElement {name: "1.0"; value: 0}
                        ListElement {name: "1.4"; value: 1}
                        ListElement {name: "2.0"; value: 2}
                        ListElement {name: "2.8"; value: 3}
                        ListElement {name: "4.0"; value: 4}
                        ListElement {name: "5.6"; value: 5}
                        ListElement {name: "8.0"; value: 6}
                    }
                }
            }

            // Aperture min slider setup starts here ----------------------------------
            RowLayout {
                id: apertureMinLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: apertureMaxLayout.bottom
                anchors.leftMargin: sliderSideMargins
                anchors.rightMargin: sliderSideMargins
                spacing: 0

                ColumnLayout {
                    Layout.fillWidth: true

                    RowLayout {
                        Label {
                            id: minApertureLabel
                            text: qsTr("Min Aperture:")
                            font.bold: true
                            horizontalAlignment: Qt.AlignHCenter
                        }

                        Label {
                            id: minApertureValueLabel
                            text: minApertureList.get(minApertureSlider.value).name
                            horizontalAlignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                        }
                    }

                    Slider {
                        id: minApertureSlider
                        from: 0
                        to: 8
                        stepSize: 1
                        Layout.fillWidth: true
                        snapMode: Slider.SnapAlways
                        Layout.topMargin: -5
                    }

                    ListModel {
                        id: minApertureList
                        ListElement {name: "16"; value: 8}
                        ListElement {name: "22"; value: 9}
                        ListElement {name: "32"; value: 10}
                        ListElement {name: "45"; value: 11}
                        ListElement {name: "64"; value: 12}
                        ListElement {name: "90"; value: 13}
                        ListElement {name: "128"; value: 14}
                        ListElement {name: "180"; value: 15}
                        ListElement {name: "256"; value: 16}
                    }
                }
            }
        }

        // ISO max Slider setup starts here ----------------------------------
        Rectangle {
            id: isoSlidersRectangle
            color: "#11000000"
            border.color: "lightgray"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: apertureSlidersRectangle.bottom
            anchors.leftMargin: sidePageMargin
            anchors.rightMargin: sidePageMargin
            anchors.topMargin: 10
            height: isoMaxLayout.height + isoMinLayout.height
            radius: defaultRadius

            RowLayout {
                id: isoMinLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.leftMargin: sliderSideMargins
                anchors.rightMargin: sliderSideMargins
                spacing: 0

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: horizontalInsideMargin

                    RowLayout {

                        Label {
                            id: minIsoLabel
                            text: qsTr("Min ISO:")
                            font.bold: true
                            horizontalAlignment: Qt.AlignHCenter
                        }

                        Label {
                            id: minIsoValueLabel
                            text: minIsoList.get(minIsoSlider.value).name
                            horizontalAlignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                        }
                    }

                    Slider {
                        id: minIsoSlider
                        Layout.topMargin: -5
                        from: 0
                        to: 8
                        stepSize: 1
                        Layout.fillWidth: true
                        value: 7 // default value

                        snapMode: Slider.SnapAlways
                    }

                    ListModel {
                        id: minIsoList
                        ListElement {name: "0.8"; value: -7}
                        ListElement {name: "1.6"; value: -6}
                        ListElement {name: "3"; value: -5}
                        ListElement {name: "6"; value: -4}
                        ListElement {name: "12"; value: -3}
                        ListElement {name: "25"; value: -2}
                        ListElement {name: "50"; value: -1}
                        ListElement {name: "100"; value: 0}
                        ListElement {name: "200"; value: 1}
                    }
                }
            }

            // Aperture min slider setup starts here ----------------------------------
            RowLayout {
                id: isoMaxLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.top: isoMinLayout.bottom
                anchors.leftMargin: sliderSideMargins
                anchors.rightMargin: sliderSideMargins
                spacing: 0

                ColumnLayout {
                    Layout.fillWidth: true

                    RowLayout {
                        Label {
                            id: maxIsoLabel
                            text: qsTr("Max ISO:")
                            font.bold: true
                            horizontalAlignment: Qt.AlignHCenter
                        }

                        Label {
                            id: maxIsoValueLabel
                            text: maxIsoList.get(maxIsoSlider.value).name
                            horizontalAlignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                        }
                    }

                    Slider {
                        id: maxIsoSlider
                        from: 0
                        to: 9
                        stepSize: 1
                        Layout.fillWidth: true
                        Layout.topMargin: -5
                        value: 1 // default value
                        snapMode: Slider.SnapAlways
                    }

                    ListModel {
                        id: maxIsoList
                        ListElement {name: "6400"; value: 6}
                        ListElement {name: "12800"; value: 7}
                        ListElement {name: "25600"; value: 8}
                        ListElement {name: "51200"; value: 9}
                        ListElement {name: "102K"; value: 10}
                        ListElement {name: "204K"; value: 11}
                        ListElement {name: "409K"; value: 12}
                        ListElement {name: "820K"; value: 13}
                        ListElement {name: "1.6M"; value: 14}
                        ListElement {name: "3.2M"; value: 15}
                    }
                }
            }
        }

        // Shutter min Slider setup starts here ----------------------------------
        Rectangle {
            id: shutterSlidersRectangle
            color: "#11000000"
            border.color: "lightgray"
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: isoSlidersRectangle.bottom
            anchors.leftMargin: sidePageMargin
            anchors.rightMargin: sidePageMargin
            anchors.topMargin: 10
            height: shutterMaxLayout.height
            radius: defaultRadius

            RowLayout {
                id: shutterMaxLayout
                anchors.left: parent.left
                anchors.right:  parent.right
                anchors.leftMargin: sliderSideMargins
                anchors.rightMargin: sliderSideMargins
                spacing: 0

                ColumnLayout {
                    Layout.fillWidth: true
                    Layout.topMargin: horizontalInsideMargin

                    RowLayout {
                        Label {
                            id: maxShutterLabel
                            text: qsTr("Max Shutter:")
                            font.bold: true
                            horizontalAlignment: Qt.AlignHCenter
                        }

                        Label {
                            id: maxShutterValueLabel
                            text: maxShutterList.get(maxShutterSlider.value).name
                            horizontalAlignment: Qt.AlignHCenter
                            Layout.leftMargin: 10
                        }
                    }

                    Slider {
                        id: maxShutterSlider
                        from: 0
                        to: 5
                        stepSize: 1
                        Layout.fillWidth: true
                        value: 3 // default value
                        snapMode: Slider.SnapAlways
                        Layout.topMargin: -5
                    }

                    ListModel {
                        id: maxShutterList
                        ListElement {name: "1000"; value: -10}
                        ListElement {name: "2000"; value: -11}
                        ListElement {name: "4000"; value: -12}
                        ListElement {name: "8000"; value: -13}
                        ListElement {name: "16000"; value: -14}
                        ListElement {name: "32000"; value: -15}
                    }
                }
            }
        }
    }
}
