import QtQuick
import QtQuick.Window
import "task_board_body"

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
    readonly property var pendingCards: [
        {
            title: "Write onboarding guide",
            detail: "Draft the first-pass guide for new contributors and collect missing setup notes.",
            dueDate: "2026-03-26",
            accentColor: "#fde68a",
            cardColor: "#fef3c7",
            titleColor: "#92400e",
            isUrgent: false,
            isClosed: false
        },
        {
            title: "Fix crash on launch",
            detail: "Reproduce the startup issue from the latest desktop build and pin the failing branch.",
            dueDate: "2026-03-24",
            accentColor: "#fecaca",
            cardColor: "#fee2e2",
            titleColor: "#991b1b",
            isUrgent: true,
            isClosed: false
        },
        {
            title: "Review naming cleanup",
            detail: "Check whether the proposed task naming matches the board vocabulary before applying it.",
            dueDate: "",
            accentColor: "#fde68a",
            cardColor: "#fef3c7",
            titleColor: "#92400e",
            isUrgent: false,
            isClosed: false
        }
    ]
    readonly property var inProgressCards: [
        {
            title: "Compose board body UI",
            detail: "Match the reference spacing, contrast, and card alignment in the TaskBoard body section.",
            dueDate: "2026-03-28",
            accentColor: "#ddd6fe",
            cardColor: "#ede9fe",
            titleColor: "#4c1d95",
            isUrgent: false,
            isClosed: false
        },
        {
            title: "Refine task navigator",
            detail: "Align breadcrumb sizing with the latest layout pass and verify truncation behavior.",
            dueDate: "",
            accentColor: "#bfdbfe",
            cardColor: "#dbeafe",
            titleColor: "#1e40af",
            isUrgent: false,
            isClosed: false
        }
    ]
    readonly property var completedCards: [
        {
            title: "Lock header layout",
            detail: "Header height and baseline spacing now match the current board prototype.",
            dueDate: "2026-03-22",
            accentColor: "#bbf7d0",
            cardColor: "#dcfce7",
            titleColor: "#166534",
            isUrgent: false,
            isClosed: true
        }
    ]
    readonly property int pendingTaskCount: pendingCards.length
    readonly property int inProgressTaskCount: inProgressCards.length
    readonly property int completedTaskCount: completedCards.length
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

        CardRow {
            anchors.fill: parent
            cards: root.pendingCards
            rowIndex: 0
            contentPadding: root.contentPadding
            rowGap: root.rowGap
            columnGap: root.columnGap
            cardWidth: root.cardWidth
            cardHeight: root.cardHeight
        }

        CardRow {
            anchors.fill: parent
            cards: root.inProgressCards
            rowIndex: 1
            contentPadding: root.contentPadding
            rowGap: root.rowGap
            columnGap: root.columnGap
            cardWidth: root.cardWidth
            cardHeight: root.cardHeight
        }

        CardRow {
            anchors.fill: parent
            cards: root.completedCards
            rowIndex: 2
            contentPadding: root.contentPadding
            rowGap: root.rowGap
            columnGap: root.columnGap
            cardWidth: root.cardWidth
            cardHeight: root.cardHeight
        }
    }
}
