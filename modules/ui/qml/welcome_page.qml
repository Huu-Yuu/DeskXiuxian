import QtQuick 2.0

Item {
    id: welcome_page

    Image {
        id: background
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "../../../res/welcome_background.png"
    }

    Image {
        id: image
        x: 183
        y: 238
        width: 421
        height: 386
        fillMode: Image.PreserveAspectFit
        source: "../../../res/welcome.png"
    }


    Text {
        id: title
        x: 666
        y: 260
        width: 397
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
        x: 710
        y: 353
        width: 309
        height: 44
        text: qsTr("欢迎来到摸鱼修仙世界")
        font.pixelSize: 30
    }


    Rectangle {
        id: go_r
        x: 710
        y: 420
        width: 313
        height: 55
        color: "#ffffff"

        Text {
            id: go_t
            y: 8
            height: 41
            text: qsTr("登录")
            horizontalAlignment: Text.AlignHCenter
            anchors.right: parent.right
            anchors.left: parent.left
            font.pixelSize: 24
            font.bold: false
        }

        MouseArea {
            id: go_ma
            hoverEnabled: true
            anchors.fill: parent
            transformOrigin: Item.Center
            onEntered: {
                // 鼠标进入
                go_t.font.bold = true
//                go_r.color = Qt.lighter(go_r.color, 1.2);
            }
            onExited: {
                // 鼠标退出
//                go_r.color = "#ffffff"
                go_t.font.bold = false
            }
        }
    }


    Rectangle {
        id: register_r
        x: 710
        y: 499
        width: 313
        height: 55
        color: "#ffffff"
        Text {
            id: register_t
            y: 8
            height: 41
            text: qsTr("注册")
            anchors.left: parent.left
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 24
        }

        MouseArea {
            id: mouseArea
            hoverEnabled: true
            anchors.fill: parent
            onEntered: {
                // 鼠标进入
                register_t.font.bold = true
//                register_r.color = Qt.lighter(go_r.color, 1.2);
            }
            onExited: {
                // 鼠标退出
//                register_r.color = "#ffffff"
                register_t.font.bold = false
            }
        }
    }


}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.9;height:800;width:1280}
}
##^##*/
