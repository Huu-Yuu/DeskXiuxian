import QtQuick 2.0
import QtQuick.Window 2.10

Window{
    id: root
    width: 1280
    height: 800
    visible: true
    //    maximumWidth: 1280
    //    maximumHeight: 800
    //    minimumWidth: 1280
    //    minimumHeight: 800
    onWidthChanged: console.log("root width = " + root.width)
    Item {
        id: welcome_page
        anchors.fill: parent
        Component.onCompleted: {console.log("GOGOGO")}
        onWidthChanged: console.log("welcome width = " + welcome_page.width)
        Image {
            id: background
            anchors.rightMargin: 0

            anchors.fill: parent
            fillMode: Image.Stretch
            source: "../../../res/welcome_background.png"
            onWidthChanged: console.log("background width = " + background.width)
        }

        Row {
            id: row
            x: 95
            y: 168
            width: 1094
            height: 462
            anchors.verticalCenter: parent.verticalCenter

            Column {
                id: column
                width: 392
                height: row.height
                anchors.right: parent.right
                anchors.rightMargin: 10
                rotation: 0
                scale: 1
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

                Rectangle {
                    id: go_r
                    width: column.width
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
                    width: column.width
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
                            register_r.color = Qt.lighter(go_r.color, 1.2);
                        }
                        onExited: {
                            // 鼠标退出
                            register_r.color = "#ffffff"
                            register_t.font.bold = false
                        }
                    }
                }
            }

            Image {
                id: image
                width: row.height
                height: row.height
                anchors.leftMargin: 0
                anchors.left: parent.left
                fillMode: Image.Stretch
                source: "../../../res/welcome.png"
            }

        }
    }
}
