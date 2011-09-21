import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.1
import com.nokia.controlpanel 0.1
import "/usr/lib/qt4/imports/com/meego/UIConstants.js" as UI1
import "/usr/lib/qt4/imports/com/meego/extras/constants.js" as UI2

Page {
    id: listPage
    anchors.margins: UiConstants.DefaultMargin
    anchors.fill: parent

    orientationLock: PageOrientation.LockPortrait

    tools: DcpToolBar {
        viewMenu: Menu {
            visualParent: pageStack

            MenuLayout {
                MenuItem {
                    text: "Add several items to the list"
                    onClicked: {
                        for (var i=0; i<10; i++) {
                            pagesModel.append ({ title: "some item " + i });
                        }
                    }
                }
            }
        }

    }

    function openFile(file) {
        var component = Qt.createComponent(file)

        if (component.status == Component.Ready)
            pageStack.push(component);
        else
            console.log("Error loading component:", component.errorString());
    }

Flickable {
    id: flickable
    anchors.fill: parent
    flickableDirection: Flickable.VerticalFlick

    DcpPageTitle {
        id: titleLabel
        text: "Qml Window Example"
        onVisibleChanged: {
            if (visible = "true") {
                titleLabel.text = "Qml Window Example " + pageStack.depth
            }
        }
    }

    Label {
        id: descriptionText
        anchors.top: titleLabel.bottom
        anchors.left: titleLabel.left
        anchors.topMargin: UI1.MARGIN_XLARGE

        text: "This example show how to have full control over the page flow " +
              "of control panel from Qml: open several pages, handle a view "+
              "menu, pop up dialogs and sheets. Just use the widgets offered "+
              "by qt-components!"
        width: parent.width
        wrapMode: Text.Wrap
        horizontalAlignment: Text.AlignJustify
    }

    ListView {
        id: listView
        anchors.top: descriptionText.bottom
        anchors.left: descriptionText.left
        anchors.topMargin: UI1.MARGIN_XLARGE

        width: parent.width
        model: pagesModel
        height: pagesModel.count * UI2.LIST_ITEM_HEIGHT
        interactive: false

        delegate:  ListDelegate {
            Image {
                source: "image://theme/icon-m-common-drilldown-arrow-inverse"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked: { listPage.openFile(page) }
        }
    }

    contentHeight: listView.height + titleLabel.height + descriptionText.height
}

    ListModel {
        id: pagesModel
        ListElement {
            page: "ListPage.qml"
            title: "This page"
            subtitle: "open this page again"
        }
        ListElement {
            page: "DialogPage.qml"
            title: "Dialog"
            subtitle: "open a dialog"
        }
        ListElement {
            page: "SheetPage.qml"
            title: "Sheet"
            subtitle: "open a sheet"
        }
    }

    ScrollDecorator {
        flickableItem: flickable
    }

}


