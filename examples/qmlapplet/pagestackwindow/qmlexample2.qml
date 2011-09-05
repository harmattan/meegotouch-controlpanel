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
                pageStack.pop();
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
            MenuItem { text: "List title #4" }
            MenuItem { text: "List title #5" }
            MenuItem { text: "List title #6" }
            MenuItem { text: "List title #7" }
            MenuItem { text: "List title #8" }
            MenuItem { text: "List title #9" }
            MenuItem { text: "List title #10" }
            MenuItem { text: "List title #11" }
            MenuItem { text: "List title #12" }
            MenuItem { text: "List title #14" }
            MenuItem { text: "List title #15" }
            MenuItem { text: "List title #16" }
            MenuItem { text: "List title #17" }
            MenuItem { text: "List title #18" }
            MenuItem { text: "List title #19" }
            MenuItem { text: "Very long and extremely verbose ListTitle #20" }
        }
    }

    Component.onCompleted: {
        theme.inverted = true;
    }
}

