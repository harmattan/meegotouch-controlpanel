import QtQuick 1.1
import com.nokia.controlpanel 0.1

Item {
Column {
     spacing: 30
     anchors.fill: parent
     anchors.margins: 16

     DcpGConfItem {
         id: colorGConf

         // the gconf key that the item represents:
         key: "/apps/duicontrolpanel/qmlexample1/color"

         // the initial value if the gconf path does not exists:
         defaultValue: "gray"

         onValueChanged: console.log ("GConf Item changed to " + value);
     }

     Text {
         text: "You can change the color of this rectangle. " +
               "The current value gets stored in gconf under " +
               colorGConf.key
         width: parent.width
         font.pointSize: 16;
         color: "lightgray"
         wrapMode: Text.Wrap
         horizontalAlignment: Text.AlignJustify
     }

     Rectangle {
         id: rectangle;
         width: 200
         height: 200
         color: rectText.text;
         anchors.centerIn: parent

         Text {
             id: rectText;
             anchors.centerIn: parent
             font.pointSize: 24;

             // this text shows the value of our gconf item:
             text: colorGConf.value
         }

         MouseArea {
             anchors.fill: parent
             onClicked: {
                 console.log ("mouseArea clicked");
                 colorGConf.value =
                     rectText.text == "green" ? "red" : "green";
             }
         }
     }
}
}

