import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Button {
    id: root
    property string normalImage: ""
    property string hoveredImage: ""
    property string pushedImage: ""
    property string disableImage: ""
    property string show_text: ""
    property string text_color: "black"
    property int text_halign: 0
    property double text_padding_ratio: 0.12
    background: Rectangle {
        implicitWidth: parent.width
        implicitHeight: parent.height
        border.width: 0
        color: "transparent"
        Image {
            anchors.fill: parent
            source: root.enabled ? (root.hovered ? hoveredImage : normalImage) : (disableImage === "" ? normalImage : disableImage)
        }
    }
    Text {
        anchors.fill: parent
        font: root.font
        text: show_text
        color: root.text_color
        //        color: "transparent"
        //        verticalAlignment: text_halign? Text.AlignTop: Text.AlignBottom
        //        y: root.y + text_padding_ratio*root.height
        horizontalAlignment: Text.AlignHCenter
        //        bottomPadding: text_padding_ratio *parent.height
        topPadding: text_padding_ratio * parent.height
    }
}
