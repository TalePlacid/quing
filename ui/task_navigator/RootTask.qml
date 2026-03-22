import QtQuick

Rectangle {
    id: root

    color: "#fbfbfc"
    border.width: 0

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "#d2d7de"
    }

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 24
        spacing: 0

        Text {
            text: "Task Board"
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            font.bold: true
            color: "#5c6f90"
            elide: Text.ElideRight
            width: root.width - 96
        }
    }
}
