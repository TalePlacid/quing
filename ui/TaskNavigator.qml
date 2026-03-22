import QtQuick
import "task_navigator"

Rectangle {
    id: root

    required property string headerTitle
    required property var taskNavigatorLines
    property int taskNavigatorRowHeight: 40

    readonly property int taskNavigatorHeight: (root.taskNavigatorLines.length + 1) * root.taskNavigatorRowHeight

    height: root.taskNavigatorHeight
    color: "#f7f7f8"
    border.color: "#d5d7db"
    border.width: 1

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "#d2d7de"
        z: 1
    }

    Column {
        anchors.fill: parent

        Rectangle {
            width: root.width
            height: root.taskNavigatorRowHeight
            color: "transparent"

            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                color: "#d2d7de"
            }

            Text {
                anchors.left: parent.left
                anchors.leftMargin: 26
                anchors.verticalCenter: parent.verticalCenter
                text: root.headerTitle
                font.pixelSize: 15
                font.bold: true
                color: "#5c6f90"
            }
        }

        RootTask {
            visible: root.taskNavigatorLines.length > 0
            width: root.width
            height: root.taskNavigatorRowHeight
            title: root.taskNavigatorLines.length > 0 ? root.taskNavigatorLines[0] : ""
        }

        ParentTask {
            visible: root.taskNavigatorLines.length > 1
            width: root.width
            height: root.taskNavigatorRowHeight
            indentLevel: 1
            title: root.taskNavigatorLines.length > 1 ? root.taskNavigatorLines[1] : ""
        }

        CurrentTask {
            visible: root.taskNavigatorLines.length > 2
            width: root.width
            height: root.taskNavigatorRowHeight
            indentLevel: 2
            title: root.taskNavigatorLines.length > 2 ? root.taskNavigatorLines[2] : ""
            showBottomLine: false
        }
    }
}
