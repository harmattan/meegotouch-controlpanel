import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.1
import "/usr/lib/qt4/imports/com/meego/extras/constants.js" as UI
import com.nokia.controlpanel 0.1

    ListView {
        
         DcpQmlGConfItem {
             id: dcpQmlrectangleColor
             key: "/meegotouch/DcpQmlrectangleColor"
             value: "ASDASD"
             
             onValueChanged: {
                 rectText.text = "green"
                 gconfrectange.color = dcpQmlrectangleColor.value
             }
         }
         
         Rectangle {
             id: gconfrectange;
             x: 0
             y: 0
             width: 200
             height: 200
             color: "#FF0000";
             Text {
                 id: rectText;
                 x: 20
                 y: 20
                 font.pointSize: 24;
                 text: "red";
             }

             MouseArea {
                 x: 0
                 y: 0
                 width: 200
                 height: 200
                 onClicked: {
                     dcpQmlrectangleColor.value = "#00FF00";
                 }
             }
         }         

         ListModel {
            id: listModel

            
            ListElement {
                page: "page2.qml"
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
                onClicked: { Dcp.newPage(page) }
            }
        }

        id: listView
        model: listModel
        delegate: listDelegate
        interactive: false

    // these are to be eliminated:
    Component.onCompleted: theme.inverted = true;
    anchors.margins: UiConstants.DefaultMargin

    x: 10
    width: 460
    height: listModel.count * UI.LIST_ITEM_HEIGHT

    }

