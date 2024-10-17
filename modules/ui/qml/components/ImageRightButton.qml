import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import "../adapter"

Button {
    id: root
    property string normalImage: ""
    property string hoveredImage: ""
    property string pushedImage: ""
    property string disableImage: ""
    property string show_text: ""
    property int image_width: root.height - 5 * ScreenAdapter.minDip
    property int text_margin: root.height - 5 * ScreenAdapter.minDip

    background: Rectangle {
        anchors.fill: root
        color: root.hovered ? "#FFF8F8F8" : Qt.rgba(0 / 255.0, 44 / 255.0,
                                                    56 / 255.0, 0.1)
    }
    Row {
        BorderImage {
            id: bord_image
            width: image_width
            height: image_width
            source: root.enabled ? (root.hovered ? hoveredImage : normalImage) : disableImage


            /*            border.right: 20 * ScreenAdapter.minDip
            border.left: 20 * ScreenAdapter.minDip*/
        }
        Text {
            font: root.font
            text: show_text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            //            leftPadding: 15 * ScreenAdapter.minDip
        }
    }
    Rectangle {
        implicitWidth: root.width
        implicitHeight: 1 * ScreenAdapter.minDip
        color: "#FFFFFF"
    }
}
