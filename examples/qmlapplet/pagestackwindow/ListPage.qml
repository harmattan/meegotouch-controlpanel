import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.1

Page {
    id: listPage
    anchors.margins: UiConstants.DefaultMargin

    tools: commonTools

    function openFile(file) {
        var component = Qt.createComponent(file)

        if (component.status == Component.Ready)
            pageStack.push(component);
        else
            console.log("Error loading component:", component.errorString());
    }


    ListView {
        id: listView
        anchors.fill: parent
        model: pagesModel

        delegate:  ListDelegate {
            Image {
                source: "image://theme/icon-m-common-drilldown-arrow-inverse"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }

            onClicked: { listPage.openFile(page) }
        }
    }

    ListModel {
        id: pagesModel
        ListElement {
            page: "ListPage.qml"
            title: "This page"
            subtitle: "open this page again"
        }
        ListElement {
            page: "LabelPage.qml"
            title: "Dialog"
            subtitle: "open a dialog"
        }
        ListElement {
            page: "1.qml"
            title: "Sheet"
            subtitle: "open a sheet"
        }
        ListElement {
            page: "1.qml"
            title: "example button 2"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 3"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 4"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 5"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 6"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 7"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 8"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 9"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 10"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 11"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 12"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 13"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 14"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 15"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 16"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 17"
            subtitle: "no subtitle"
        }
        ListElement {
            page: "1.qml"
            title: "example button 18"
            subtitle: "no subtitle"
        }
    }

    ScrollDecorator {
        flickableItem: listView
    }

}


