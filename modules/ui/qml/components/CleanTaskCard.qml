import QtQuick 2.7
import QtGraphicalEffects 1.0
import "../adapter"

Item {
    id: root
    property int checked: 0
    property string clean_name: "工作日上午清洗"
    property string clean_mode: "中洗"
    property double clean_surplustime: 46.5
    property int clean_linenum: 3
    property double clean_area: 463.5
    property string map_name: "保利国际广场1楼, 保利国际广场2楼"
    property string clean_type: "周一、周二、周三、周四 <font color=\"#00B5E2\">    09:00</font>"
    signal clicked
    Rectangle {
        id: background_rect
        anchors.fill: parent
        border.color: checked ? "#FF00B5E2" : "#80ffffff"
        border.width: checked ? 3 * ScreenAdapter.minDip : 0
        radius: checked ? 0 : 8 * ScreenAdapter.minDip
        color: "#80FFFFFF"
    }

    Text {
        //        anchors.fill: parent
        anchors.left: root.left
        anchors.leftMargin: 30 * ScreenAdapter.widthDip
        anchors.top: root.top
        anchors.topMargin: 17 * ScreenAdapter.heightDip
        horizontalAlignment: Text.AlignLeft
        text: clean_name
//        color: "#0E2124"
        color: "#00B5E2"
        font.pixelSize: 24 * ScreenAdapter.minDip
        font.weight: Font.Bold
    }

    Rectangle {
        anchors.top: parent.top
        anchors.topMargin: 3 * ScreenAdapter.minDip
        anchors.right: parent.right
        anchors.rightMargin: 3 * ScreenAdapter.minDip
        id: clean_mode_rect
        width: 98 * ScreenAdapter.widthDip
        height: 45 * ScreenAdapter.heightDip
        color: "#FFFFFF"
        radius: 6
        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: clean_mode
            color: "#000000"
            font.pixelSize: 18 * ScreenAdapter.minDip
            font.weight: Font.Bold
        }
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            radius: 6.0
            verticalOffset: 3
            horizontalOffset: 3
            color: "#28000000"
        }
    }

    Rectangle {
        id: clean_stastic1
        anchors.left: root.left
        anchors.leftMargin: 28 * ScreenAdapter.widthDip
        anchors.top: root.top
        anchors.topMargin: 75 * ScreenAdapter.heightDip
        width: 104 * ScreenAdapter.widthDip
        height: 70 * ScreenAdapter.heightDip
        opacity: 1
        color: "transparent"
        Text {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: "耗时: (min)"
            font.pixelSize: 12 * ScreenAdapter.minDip
            color: "#666666"
        }
        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: clean_surplustime
            font.pixelSize: 24 * ScreenAdapter.minDip
            font.weight: Font.Bold
            color: "#0E2124"
        }
    }

    Rectangle {
        id: clean_stastic2
        anchors.horizontalCenter: root.horizontalCenter
        anchors.top: clean_stastic1.top
        width: 104 * ScreenAdapter.widthDip
        height: 70 * ScreenAdapter.heightDip
        opacity: 1
        color: "transparent"
        Text {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: "路线:"
            font.pixelSize: 12 * ScreenAdapter.minDip
            color: "#666666"
        }
        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: clean_linenum.toString()
            font.pixelSize: 24 * ScreenAdapter.minDip
            font.weight: Font.Bold
            color: "#0E2124"
        }
    }

    Rectangle {
        id: clean_stastic3
        anchors.right: root.right
        anchors.rightMargin: 28 * ScreenAdapter.widthDip
        anchors.top: clean_stastic2.top
        width: 104 * ScreenAdapter.widthDip
        height: 70 * ScreenAdapter.heightDip
        opacity: 1
        color: "transparent"
        Text {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: "面积: (m²)"
            font.pixelSize: 12 * ScreenAdapter.minDip
            color: "#666666"
        }
        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            text: clean_area.toString()
            font.pixelSize: 24 * ScreenAdapter.minDip
            font.weight: Font.Bold
            color: "#0E2124"
        }
    }

    Text {
        id: map_name_lable
        x: /*root.x + */ (107 - 77) * ScreenAdapter.widthDip
        y: /*root.y + */ (345 - 165) * ScreenAdapter.heightDip
        horizontalAlignment: Text.AlignLeft
        text: "地图:  "
        font.pixelSize: 12 * ScreenAdapter.minDip
        color: "#666666"
    }

    Text {
        id: map_name_content
        anchors.left: map_name_lable.right
        anchors.top: map_name_lable.top
        horizontalAlignment: Text.AlignLeft
        text: map_name
        font.pixelSize: 12 * ScreenAdapter.minDip
        font.weight: Font.Medium
        color: "#0E2124"
    }

    Text {
        id: clean_type_lable
        x: /*root.x + */ (107 - 77) * ScreenAdapter.widthDip
        y: /*root.y + */ (369 - 165) * ScreenAdapter.heightDip
        horizontalAlignment: Text.AlignLeft
        text: "类型:  "
        font.pixelSize: 12 * ScreenAdapter.minDip
        color: "#666666"
    }

    Text {
        id: clean_type_contet
        anchors.left: clean_type_lable.right
        anchors.top: clean_type_lable.top
        horizontalAlignment: Text.AlignLeft
        text: clean_type
        font.pixelSize: 12 * ScreenAdapter.minDip
        font.weight: Font.Medium
        color: "#0E2124"
    }

    Component.onCompleted: {

    }

    MouseArea {
        anchors.fill: root
        onClicked: {
            root.clicked()
        }
    }
}
