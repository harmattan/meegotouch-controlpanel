import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.controlpanel 0.1

ToolBarLayout {
    property Menu viewMenu

    ToolIcon {
        iconSource: (pageStack.depth == 1 && dcp.isStandalone) ?
                    "image://theme/icon-l-settings-main-view" :
                    "image://theme/icon-m-toolbar-back-white";
        onClicked: {
            if (parent.viewMenu != null) {
                parent.viewMenu.close();
            }
            if (pageStack.depth > 1) {
                pageStack.pop();
            } else if (dcp.isStandalone) {
                dcp.popupMainPageAlone();
            } else {
                Qt.quit();
            }
        }
    }

    ToolIcon {
        id: viewMenuButton
        iconSource: "image://theme/icon-m-toolbar-view-menu-white"

        visible: false

        onClicked: {
            if (parent.viewMenu.status == DialogStatus.Closed) {
                parent.viewMenu.open();
            } else {
                parent.viewMenu.close();
            }
        }
    }

    onViewMenuChanged: {
        if (!viewMenuButton.visible) viewMenuButton.visible = true;
    }
}

