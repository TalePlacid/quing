import QtQuick
import QtQuick.Window
import QtTest
import "../../../ui"
import "../SaveSnapshot.js" as SaveSnapshot
import "../component"

TestCase {
    name: "Test_TaskNavigator"
    when: windowShown

    property var taskNavigator: null
    property var testWindow: null
    property var testRoot: null
    property bool snapshotSaved: false

    Fixture_TaskNavigatorViewModel {
        id: taskNavigatorViewModelFixture
    }

    Component {
        id: testWindowComponent

        Window {
            width: Screen.width
            height: Screen.height
            visible: true

            Item {
                id: testRootItem
                anchors.fill: parent
            }
        }
    }

    Component {
        id: taskNavigatorComponent

        TaskNavigator {
            width: 400
            taskNavigatorViewModel: taskNavigatorViewModelFixture
        }
    }

    function prepareTaskNavigator(titles) {
        taskNavigatorViewModelFixture.titles = titles

        if (testWindow === null) {
            testWindow = createTemporaryObject(testWindowComponent, null, {})
            verify(testWindow !== null, "테스트 윈도우 생성 실패")
            testRoot = testWindow.contentItem.children[0]
            verify(testRoot !== null, "테스트 루트 생성 실패")
            wait(0)
        }

        if (taskNavigator !== null) {
            taskNavigator.destroy()
            taskNavigator = null
        }

        taskNavigator = createTemporaryObject(taskNavigatorComponent, testRoot, {
            "x": 0,
            "y": 0
        })
        verify(taskNavigator !== null, "TaskNavigator 생성 실패")
        wait(0)
    }

    function collectTaskTitles(item, titles) {
        var i = 0

        if (item === null || item === undefined) {
            return
        }

        if (item.title !== undefined) {
            titles.push(item.title)
        }

        if (item.children === undefined) {
            return
        }

        while (i < item.children.length) {
            collectTaskTitles(item.children[i], titles)
            i++
        }
    }

    function verifyTaskNavigator(titles) {
        var expectedLength = titles.length
        var expectedHeight = (expectedLength + 1) * taskNavigator.taskNavigatorRowHeight
        var renderedTitles = []

        tryCompare(taskNavigatorViewModelFixture, "length", expectedLength, 5000, "ViewModel length mismatch")
        tryCompare(taskNavigator, "taskNavigatorHeight", expectedHeight, 5000, "TaskNavigator height mismatch")

        collectTaskTitles(taskNavigator, renderedTitles)

        compare(taskNavigatorViewModelFixture.length, expectedLength, "ViewModel length mismatch")
        compare(taskNavigator.taskNavigatorHeight, expectedHeight, "TaskNavigator height mismatch")
        compare(renderedTitles.length, expectedLength, "Rendered task count mismatch")
        compare(renderedTitles, titles, "Rendered task titles mismatch")
    }

    function saveCurrentSnapshot(fileName) {
        snapshotSaved = false

        SaveSnapshot.saveSnapshot(
            taskNavigator,
            Qt.resolvedUrl("../snap_shot/tst_TaskNavigator/" + fileName),
            function() {
                snapshotSaved = true
            })

        tryVerify(function() {
            return snapshotSaved
        }, 5000, "Snapshot save failed")
    }

    function init() {
        prepareTaskNavigator([])
    }

    function cleanup() {
        if (taskNavigator !== null) {
            taskNavigator.destroy()
            taskNavigator = null
        }

        snapshotSaved = false
    }

    function cleanupTestCase() {
        if (testWindow !== null) {
            testWindow.destroy()
            testWindow = null
            testRoot = null
        }
    }

    function test_01_empty() {
        prepareTaskNavigator([])
        verifyTaskNavigator([])
        saveCurrentSnapshot("tst_TaskNavigator01.png")
    }

    function test_02_oneTask() {
        prepareTaskNavigator(["1단계"])
        verifyTaskNavigator(["1단계"])
        saveCurrentSnapshot("tst_TaskNavigator02.png")
    }

    function test_03_twoTasks() {
        prepareTaskNavigator(["1단계", "2단계"])
        verifyTaskNavigator(["1단계", "2단계"])
        saveCurrentSnapshot("tst_TaskNavigator03.png")
    }

    function test_04_threeTasks() {
        prepareTaskNavigator(["1단계", "2단계", "3단계"])
        verifyTaskNavigator(["1단계", "2단계", "3단계"])
        saveCurrentSnapshot("tst_TaskNavigator04.png")
    }

    function test_05_fourTasks() {
        prepareTaskNavigator(["1단계", "2단계", "3단계", "4단계"])
        verifyTaskNavigator(["1단계", "2단계", "3단계", "4단계"])
        saveCurrentSnapshot("tst_TaskNavigator05.png")
    }

    function test_06_fiveTasks() {
        prepareTaskNavigator(["1단계", "2단계", "3단계", "4단계", "5단계"])
        verifyTaskNavigator(["1단계", "2단계", "3단계", "4단계", "5단계"])
        saveCurrentSnapshot("tst_TaskNavigator06.png")
    }
}
