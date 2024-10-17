import QtQuick 2.0
import QtGraphicalEffects 1.0
import "../adapter"
import "../components"

Item {
    id: select_clean_mode_item
    visible: false
    x: 0
    y: 0
    width: 1280 * ScreenAdapter.widthDip
    height: 800 * ScreenAdapter.heightDip

    property int select_index: 0
    property var radio_model: [{
            "nor": "",
            "press": ""
        }]
    property int box_width: 570 * ScreenAdapter.widthDip
    property int box_height: 380 * ScreenAdapter.heightDip
    property int box_x: 355 * ScreenAdapter.widthDip
    property int box_y: 210 * ScreenAdapter.heightDip
    property string box_title: qsTr("请选择清洁模式")
    property int box_value: 0
    property int radio_image_width: 130 * ScreenAdapter.widthDip
    property int radio_margin: 40 * ScreenAdapter.widthDip
    property int radio_left: 50 * ScreenAdapter.widthDip
    property int radio_top: 110 * ScreenAdapter.heightDip
    Rectangle {
        anchors.fill: parent
        color: "#33000000"
    }
    Rectangle {
        x: box_x
        y: box_y
        width: box_width
        height: box_height
        color: "#FFFFFF"
        radius: 8 * ScreenAdapter.minDip
        Text {
            id: title
            anchors.horizontalCenter: parent.horizontalCenter
            y: 30 * ScreenAdapter.heightDip
            color: "#0e2124"
            
            font.pixelSize: 30 * ScreenAdapter.minDip
            font.weight: Font.Medium
            text: box_title
        }

        Repeater {
            id: radio_repeater
            model: radio_model.length
            Image {
                x: radio_left + index * (radio_image_width + radio_margin)
                y: radio_top
                width: radio_image_width
                height: width
                source: {
                    if (index == select_index)
                        return radio_model[index].press
                    return radio_model[index].nor
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        select_index = index
                    }
                }
            }
        }

        ColorButton {
            button_color: "#E2E2E2"
            button_color_press: "#00B1E5"
            font_size: 24 * ScreenAdapter.minDip
            text_color: "#002c38"
            text_color_press: "#FFFFFF"
            text: qsTr("取消")
            button_radius: 8 * ScreenAdapter.minDip
            x: parent.width / 2 - 158 * ScreenAdapter.widthDip
            y: 290 * ScreenAdapter.heightDip
            width: 138 * ScreenAdapter.widthDip
            height: 60 * ScreenAdapter.heightDip
            onSendButtonValue: {
                box_value = 1
            }
        }

        ColorButton {
            button_color: "#00b5e2"
            button_color_press: "#00B1E5"
            font_size: 24 * ScreenAdapter.minDip
            text_color: "#FFFFFF"
            text_color_press: "#FFFFFF"
            text: qsTr("确定")
            button_radius: 8 * ScreenAdapter.minDip
            x: parent.width / 2 + 20 * ScreenAdapter.widthDip
            y: 290 * ScreenAdapter.heightDip
            width: 138 * ScreenAdapter.widthDip
            height: 60 * ScreenAdapter.heightDip
            onSendButtonValue: {
                box_value = 2
            }
        }
    }
    onVisibleChanged: {
        if (!visible)
            box_value = 0
    }
}
