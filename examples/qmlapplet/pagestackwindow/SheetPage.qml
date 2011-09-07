import QtQuick 1.1
import Qt.labs.components 1.1
import com.nokia.meego 1.0

Page {
    id: sheetPage
    anchors.margins: UiConstants.DefaultMargin
    anchors.fill: parent

    tools: DcpToolBar {}

    Flickable {
        anchors.fill: parent
        contentWidth: col.width
        contentHeight: col.height
        flickableDirection: Flickable.VerticalFlick

        Column {
            id: col
            spacing: 30

            DcpPageTitle {
                text: "Page About Sheets"
            }

            Button {
                text: "Launch Sheet"
                onClicked: sheet.open()
            }

            Button {
                text: "Launch empty Sheet"
                onClicked: emptySheet.open()
            }

            Label {
                id: label
            }
        }
    }

    Sheet {
        id: sheet
        
        acceptButtonText: "Save"
        rejectButtonText: "Cancel"
        rejectButton.enabled: !disableCancelButton.checked

        title: BusyIndicator {
            anchors.centerIn: parent; running: sheet.status == DialogStatus.Open;
        }
        
        content: Flickable {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.topMargin: 10
            contentWidth: col2.width
            contentHeight: col2.height
            flickableDirection: Flickable.VerticalFlick

            Column {
                id: col2
                anchors.top: parent.top
                spacing: 10
                Button {
                    id: disableCancelButton
                    text: "Disable cancel button"
                    checkable: true
                }
                Button {
                    text: "Three"
                }
                Button {
                    text: "Four"
                }
                Button {
                    text: "Five"
                }
                TextField {
                    text: "Six"
                }
                Button {
                    text: "Seven"
                }
                Button {
                    text: "Eight"
                }
                Button {
                    text: "Nine"
                }
                TextField {
                    text: "Ten"
                }

            }
        }        
        onAccepted: label.text = "Accepted!"
        onRejected: label.text = "Rejected!"
    }    

    Sheet {
        id: emptySheet

        acceptButtonText: "Accept"
        rejectButtonText: "Cancel"

        title: BusyIndicator {
            anchors.centerIn: parent; running: emptySheet.status == DialogStatus.Open;
        }

        content: Rectangle {
                anchors.fill: parent
                Label {
                    id: labelEmpty
                    text: "Empty sheet"
                }
        }

        onAccepted: label.text = "Accepted!"
        onRejected: label.text = "Rejected!"
    }
}

