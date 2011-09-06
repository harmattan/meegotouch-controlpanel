import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: rootWindow

    initialPage: ListPage { }

    ToolBarLayout {
        id: commonTools
        visible: false

        ToolIcon {
            iconId: "toolbar-back";
            onClicked: {
                myMenu.close();
                if (pageStack.depth > 1) {
                    pageStack.pop();
                } else {
                    Qt.quit();
                }
            }
        }

        ToolIcon {
            iconId: "toolbar-view-menu";
            onClicked: (myMenu.status == DialogStatus.Closed) ?
                        myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu
        MenuLayout {
            MenuItem { text: "List title #1" }
            MenuItem { text: "List title #2" }
            MenuItem { text: "List title #3" }
        }
    }

    Component.onCompleted: {
        theme.inverted = true;
        screen.allowedOrientations = Screen.Portrait;
    }

    rotation: 90
}

