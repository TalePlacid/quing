import QtQuick

Rectangle {
    id: root

    required property string title
    required property int indentLevel
    property int indentWidth: 34
    property bool showBottomLine: true

    color: "#fbfbfc"
    border.width: 0

    Rectangle {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: "#d2d7de"
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 1
        color: root.showBottomLine ? "#d2d7de" : "transparent"
    }

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 24 + (root.indentLevel - 1) * root.indentWidth
        spacing: 14

        Item {
            width: 12
            height: parent.height

            Rectangle {
                width: 7
                height: 7
                radius: 3.5
                anchors.centerIn: parent
                color: "#b7bec8"
            }
        }

        Text {
            text: root.title
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            font.bold: true
            color: "#5c6f90"
            elide: Text.ElideRight
            width: root.width - (96 + (root.indentLevel - 1) * root.indentWidth)
        }
    }
}
