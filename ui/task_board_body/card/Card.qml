import QtQuick

Rectangle {
    id: root

    required property var cardData

    radius: 10
    color: root.cardData.cardColor
    border.width: 1
    border.color: Qt.darker(root.cardData.accentColor, 1.05)

    Item {
        id: cardHeaderLine
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.leftMargin: 14
        anchors.rightMargin: 12
        anchors.topMargin: 12
        height: 22

        Item {
            id: markArea
            width: 16
            height: 16
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            Rectangle {
                visible: root.cardData.isClosed
                width: 8
                height: 8
                radius: 4
                anchors.centerIn: parent
                color: root.cardData.titleColor
            }

            Canvas {
                visible: !root.cardData.isClosed
                anchors.fill: parent

                onPaint: {
                    var context = getContext("2d")
                    var strokeColor = root.cardData.isUrgent ? "#b91c1c" : root.cardData.titleColor
                    var fillColor = root.cardData.isUrgent ? "#fee2e2" : "transparent"

                    context.reset()
                    context.beginPath()
                    context.moveTo(width / 2, 1)
                    context.lineTo(width - 1, height - 1)
                    context.lineTo(1, height - 1)
                    context.closePath()
                    context.fillStyle = fillColor
                    context.fill()
                    context.lineWidth = 1
                    context.strokeStyle = strokeColor
                    context.stroke()
                }
            }

            Text {
                visible: !root.cardData.isClosed
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 2
                text: "!"
                font.pixelSize: 10
                font.bold: true
                color: root.cardData.isUrgent ? "#b91c1c" : root.cardData.titleColor
            }
        }

        Row {
            id: cardActions
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

            CardMoreActionPart {
                width: 14
                height: 18
            }

            CardCloseActionPart {
                width: 14
                height: 18
            }
        }

        CardTitleInputPart {
            anchors.left: markArea.right
            anchors.leftMargin: 10
            anchors.right: cardActions.left
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            textValue: root.cardData.title
            textColor: root.cardData.titleColor
        }
    }

    CardDetailInputPart {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: cardHeaderLine.bottom
        anchors.bottom: dueDateRow.top
        anchors.leftMargin: 12
        anchors.rightMargin: 12
        anchors.topMargin: 6
        anchors.bottomMargin: 6
        textValue: root.cardData.detail
        textColor: "#4b5563"
    }

    CardDueDatePart {
        id: dueDateRow
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 12
        anchors.bottomMargin: 10
        width: parent.width - 24
        height: 16
        dueDateText: root.cardData && root.cardData.dueDate ? root.cardData.dueDate : "Select date"
    }
}
