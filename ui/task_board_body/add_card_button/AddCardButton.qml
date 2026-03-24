import QtQuick

Item {
    id: root

    Rectangle {
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: 12
        color: "transparent"
        border.width: 2
        border.color: "#26000000"
        border.pixelAligned: true
        antialiasing: true

        Rectangle {
            anchors.centerIn: parent
            width: 36
            height: 36
            radius: 18
            color: "#12000000"

            Rectangle {
                anchors.centerIn: parent
                width: 16
                height: 2
                color: "#666666"
            }

            Rectangle {
                anchors.centerIn: parent
                width: 2
                height: 16
                color: "#666666"
            }
        }
    }
}
