import QtQuick 2.0
import "../adapter"

Rectangle {
    id: root
    property string show_text: ""
    property string normalColor: ""
    property string pressedColor: ""
    property string disableColor: "#95A5A6"
    property string textColor: ""
    property alias font: show_text_id.font
    property int down: control_area.pressed
    signal clicked
    width: 138 * ScreenAdapter.widthDip
    height: 60 * ScreenAdapter.heightDip
    color: {
        if (root.enabled == false)
            return disableColor
        if (normalColor === "") {
//            if (root.down)
//                return "#00ffff"
//            else
                return "#00B5E2"
        } else {
            if (root.down)
                return root.pressedColor
            else
                return root.normalColor
        }
    }
    radius: 6
    Text {
        id: show_text_id
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        y: 95 * ScreenAdapter.heightDip
        text: show_text
        font.pixelSize: 24 * ScreenAdapter.minDip
        color: textColor === "" ? "white" : textColor
    }
    MouseArea {
        id: control_area
        anchors.fill: parent
        onClicked: {
            root.clicked()
        }
    }
}
