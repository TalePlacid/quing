import QtQuick

Rectangle {
    id: root

    required property string title

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
        spacing: 14

        Item {
            width: 16
            height: parent.height

            Canvas {
                width: 12
                height: 8
                anchors.centerIn: parent
                onPaint: {
                    var context = getContext("2d")

                    context.reset()
                    context.beginPath()
                    context.moveTo(1, 2)
                    context.lineTo(width / 2, height - 1)
                    context.lineTo(width - 1, 2)
                    context.lineWidth = 1.5
                    context.strokeStyle = "#7c8798"
                    context.stroke()
                }
            }
        }

        Text {
            text: root.title
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 15
            font.bold: true
            color: "#5c6f90"
            elide: Text.ElideRight
            width: root.width - 96
        }
    }
}
