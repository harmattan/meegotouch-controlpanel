import QtQuick 1.1
import com.nokia.TimeExample 1.0 // import types from the plugin

Item {
    Time { // this class is defined in C++ (time_plugin.cpp)
        id: time
    }

Column {
     spacing: 30
     anchors.fill: parent
     anchors.margins: 16

     Text {
         text: "This example shows how to write the logic of the Qml applet " +
               "in C++ and extend the capabilities of Qml through a shared " +
               "library."
         width: parent.width
         font.pointSize: 16;
         color: "lightgray"
         wrapMode: Text.Wrap
         horizontalAlignment: Text.AlignJustify
     }

     Text {
         id: rectText;
         anchors.centerIn: parent
         font.pointSize: 24;
         color: "lightgray"

         // this text shows the value our "business logic" provides:
         text: "The time is: " + time.text
     }
}
}

