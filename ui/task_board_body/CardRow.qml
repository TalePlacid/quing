import QtQuick
import "add_card"
import "card"

Item {
    id: root

    required property var cards
    required property int rowIndex
    required property int contentPadding
    required property int rowGap
    required property int columnGap
    required property int cardWidth
    required property int cardHeight

    function getRowY() {
        return root.contentPadding + root.rowIndex * (root.cardHeight + root.rowGap)
    }

    function getCardX(index) {
        return root.contentPadding + index * (root.cardWidth + root.columnGap)
    }

    function getAddCardX() {
        return root.contentPadding + root.cards.length * (root.cardWidth + root.columnGap)
    }

    Repeater {
        model: root.cards

        delegate: Item {
            required property int index
            required property var modelData

            x: root.getCardX(index)
            y: root.getRowY()
            width: root.cardWidth
            height: root.cardHeight

            Card {
                anchors.fill: parent
                cardData: modelData
            }
        }
    }

    AddCardButton {
        x: root.getAddCardX()
        y: root.getRowY()
        width: root.cardWidth
        height: root.cardHeight
    }
}
