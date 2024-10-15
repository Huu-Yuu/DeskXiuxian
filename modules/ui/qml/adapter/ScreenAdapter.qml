pragma Singleton
import QtQuick 2.0
import QtQuick.Window 2.0

Item {
    width: Screen.width;
    height: Screen.height;
    visible: false;

    property real widthDip: Screen.width/1280
    property real heightDip: Screen.height/800
    property real minDip: widthDip > heightDip ? heightDip : widthDip
    Component.onCompleted: {
        console.log("screen width: " + Screen.width + ", screen height: " + Screen.height)
    }
}
