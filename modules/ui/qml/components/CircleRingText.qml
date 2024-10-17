import QtQuick 2.0
import "../adapter"

Rectangle {
   id: root

   property string showTitle: "净水量 (%)"
   property string showContent: "80"
   property int content_font_size: 60 * ScreenAdapter.minDip;
   property int circle_width: (211 - 2*28) * ScreenAdapter.minDip;
   property int circle_border:  18 * ScreenAdapter.minDip;

   color: "#CCF5FF"
   border.color: "#00B5E2"
   border.width: circle_border;
   width: circle_width; height: circle_width;
   radius: circle_width;
   clip: true

   Text {
       id: title
/*      anchors.top: root.top
      anchors.topMargin: (64-28) * ScreenAdapter.minDip*/;
      anchors.verticalCenter: root.verticalCenter
      anchors.verticalCenterOffset: -24 * ScreenAdapter.minDip;
      anchors.horizontalCenter: root.horizontalCenter
      text: showTitle
      font.pixelSize: 20 * ScreenAdapter.minDip;
   }

   Text {
//      anchors.top: root.top
//      anchors.topMargin: (89-28) * ScreenAdapter.minDip;
       anchors.verticalCenter: root.verticalCenter
       anchors.verticalCenterOffset: 15* ScreenAdapter.minDip;
      anchors.horizontalCenter: root.horizontalCenter
      text: showContent
      font.pixelSize: 60 * ScreenAdapter.minDip;
   }
}

