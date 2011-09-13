import QtQuick 1.1
import com.nokia.meego 1.0

ToolBarLayout {
    property Menu viewMenu

    ToolIcon {
        iconId: "toolbar-back";
        onClicked: {
            if (parent.viewMenu != null) {
                parent.viewMenu.close();
            }
            if (pageStack.depth > 1) {
                pageStack.pop();
            } else {
                Qt.quit();
            }
        }
    }

    ToolIcon {
        id: viewMenuButton
        iconId: "toolbar-view-menu"

        visible: false

        onClicked: {
            if (parent.viewMenu.status == DialogStatus.Closed) {
                parent.viewMenu.open();
            } else {
                parent.viewMenu.close();
            }
        }
    }

    onViewMenuChanged: if (!viewMenuButton.visible) viewMenuButton.visible = true;
}

