import QtQuick
import QtQuick.Window

Window {
    id: root

    readonly property int rowCount: 3
    readonly property int taskNavigatorRowHeight: 40
    readonly property int contentPadding: 24
    readonly property int rowGap: 20
    readonly property int columnGap: 16
    readonly property int cardWidth: 190
    readonly property int cardHeight: 170
    readonly property int initialContentHeight: contentPadding * 2 + rowCount * cardHeight + (rowCount - 1) * rowGap
    readonly property int pendingTaskCount: 3
    readonly property int inProgressTaskCount: 2
    readonly property int completedTaskCount: 1
    readonly property int totalTaskCount: pendingTaskCount + inProgressTaskCount + completedTaskCount

    width: 1365
    height: taskNavigator.height + initialContentHeight
    visible: true
    title: qsTr("Quing")

    TaskNavigator {
        id: taskNavigator
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        taskNavigatorViewModel: taskBoardViewModel.taskNavigatorViewModel
    }

    Rectangle {
        id: contentArea
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: taskNavigator.bottom
        anchors.bottom: parent.bottom
        color: "#fbfcfe"
        clip: true

        Item {
            anchors.fill: parent
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            y: root.contentPadding + 0 * (root.cardHeight + root.rowGap)
            x: 0
            height: root.cardHeight
            color: "transparent"
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            y: root.contentPadding + 1 * (root.cardHeight + root.rowGap)
            x: 0
            height: root.cardHeight
            color: "transparent"
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            y: root.contentPadding + 2 * (root.cardHeight + root.rowGap)
            x: 0
            height: root.cardHeight
            color: "transparent"
        }
    }
}
