import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Item {
    width: 640
    height: 480

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1

    RowLayout {
        anchors.verticalCenterOffset: -109
        anchors.horizontalCenterOffset: 6
        anchors.centerIn: parent

        Button {
            id: button1
            text: qsTr("Press Me 1")
        }

        Button {
            id: button2
            text: qsTr("Press Me 2")
        }

        Button {
            id: button3
            text: qsTr("Press Me 3")
        }
    }

    Button {
        id: buttonrecord
        x: 168
        y: 162
        text: qsTr("开始记录")
        tooltip: qsTr("从当前时间开始记录一个事件")

    }
    ListView {
        id: timelist
        x: 168
        y: 194
        width: 228
        height: 278

        Text {
            id: text1
            x: 46
            y: 39
            text: qsTr("Text")
            font.pixelSize: 12
        }

        Text {
            id: text2
            x: 46
            y: 90
            text: qsTr("Text")
            font.pixelSize: 12
        }

        Text {
            id: text3
            x: 46
            y: 139
            text: qsTr("Text")
            font.pixelSize: 12
        }

    }
}
