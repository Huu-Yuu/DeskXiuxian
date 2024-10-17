import QtQuick 2.0
import QtQuick.Controls 1.3
import "./adapter"
import "./components"

Item {
    width: 1120
    height: 700
    id: welcome_page
    anchors.fill: parent
    Component.onCompleted: {console.log("GOGOGO")}
    onWidthChanged: console.log("welcome width = " + welcome_page.width)
    Image {
        id: background
        anchors.fill: parent

        fillMode: Image.Stretch
        source: "../../../res/welcome_background.png"
        onWidthChanged: console.log("background width = " + background.width)
    }

    Row {
        id: row
//        width: parent.width
        height: 462
        layoutDirection: Qt.RightToLeft
        spacing: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Column {
            id: column
            width: parent.width / 2
            height: row.height
            transformOrigin: Item.Center
            anchors.verticalCenter: parent.verticalCenter
            spacing: 20

            Text {
                id: title
                width: column.width
                height: 85
                text: "桌面修仙"
                font.bold: true
                lineHeight: 1
                fontSizeMode: Text.FixedSize
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 60
            }

            Text {
                id: subtitle
                width: column.width
                height: 44
                text: qsTr("欢迎来到摸鱼修仙世界")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 30
            }

            Button {
                id: go_r
                width: column.width
                height: 55

                Text {
                    id: go_t
                    y: 8
                    height: 41
                    text: qsTr("登录")
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
//                    anchors.right: parent.right
//                    anchors.left: parent.left
                    font.pixelSize: 24
                    font.bold: false
                }
            }

            Button {
                id: register_r
                width: column.width
                height: 55
                Text {
                    id: register_t
                    y: 8
                    height: 41
                    text: qsTr("注册")
                    anchors.horizontalCenter: parent.horizontalCenter
//                    anchors.left: parent.left
//                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 24
                }
            }
        }
        Image {
            id: image
            width: row.height
            height: row.height
            fillMode: Image.Stretch
            source: "../../../res/welcome.png"
        }
    }
}
