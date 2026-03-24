import QtQuick

Item {
    id: root

    required property string textValue
    required property color textColor

    Text {
        anchors.fill: parent
        text: root.textValue
        color: root.textColor
        font.pixelSize: 12
        wrapMode: Text.WordWrap
        clip: true
    }
}
