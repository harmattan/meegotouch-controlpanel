import QtQuick 1.0

Rectangle {
     id: page
     x: 40
     width: 400; height: 400
     color: "lightgray"

     Text {
         id: helloText
         text: "Hello world!"
         y: 30
         anchors.horizontalCenter: page.horizontalCenter
         font.pointSize: 24; font.bold: true
     }
}

