import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.1
import "/usr/lib/qt4/imports/com/meego/extras/constants.js" as UI

ListView {
 ListModel {
    id: listModel

    ListElement {
        page: "PageStackWindowPage.qml"
        title: "Pop up sheet"
        subtitle: "pops up an example sheet"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
    ListElement {
        page: "1.qml"
        title: "Example element"
        subtitle: "pam pam"
    }
}

Component {
    id: listDelegate
    ListDelegate {
        Image {
            source: "image://theme/icon-m-common-drilldown-arrow-inverse"
            anchors.right: parent.right;
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}

        id: listView
        model: listModel
        delegate: listDelegate

    // these are to be eliminated:
    Component.onCompleted: theme.inverted = true;
    anchors.margins: UiConstants.DefaultMargin

    x: 10
    width: 460
    height: listModel.count * UI.LIST_ITEM_HEIGHT
}

