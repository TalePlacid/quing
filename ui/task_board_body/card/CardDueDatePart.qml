import QtQuick

Item {
    id: root

    required property string dueDateText

    Text {
        anchors.fill: parent
        text: root.dueDateText
        font.pixelSize: 11
        color: "#6b7280"
        elide: Text.ElideLeft
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
    }
}
