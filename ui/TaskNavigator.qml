import QtQuick
import "task_navigator"

Rectangle {
    id: root

    required property var taskNavigatorViewModel
    property int taskNavigatorRowHeight: 40

    readonly property int taskNavigatorHeight: (root.taskNavigatorViewModel.length + 1) * root.taskNavigatorRowHeight

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

        RootTask {
            width: root.width
            height: root.taskNavigatorRowHeight
        }

        Repeater {
            model: root.taskNavigatorViewModel.length

            delegate: Loader {
                property int pathIndex: index
                property int pathIndentLevel: index + 1
                property string pathTitle: root.taskNavigatorViewModel.titles[index]

                width: root.width
                height: root.taskNavigatorRowHeight

                sourceComponent: pathIndex < root.taskNavigatorViewModel.length - 1 ? parentTaskComponent : currentTaskComponent
            }
        }
    }

    Component {
        id: parentTaskComponent

        ParentTask {
            width: root.width
            height: root.taskNavigatorRowHeight
            indentLevel: pathIndentLevel
            title: pathTitle
        }
    }

    Component {
        id: currentTaskComponent

        CurrentTask {
            width: root.width
            height: root.taskNavigatorRowHeight
            indentLevel: pathIndentLevel
            title: pathTitle
            showBottomLine: false
        }
    }
}
