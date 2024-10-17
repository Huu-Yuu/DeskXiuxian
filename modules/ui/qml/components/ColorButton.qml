import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2

Button {
    property bool font_bold: false;

    property int button_index: -1;
    property int button_radius: 0;
    property int border_width: 0;
    property int font_size: 0;

    property string button_color;
    property string button_color_press;
    property string text_color;
    property string text_color_press;
    property string border_color;
    property string border_color_press;
    property string shadow_color: "#30000000";
    property string font_family: "Source Han Sans CN";
    property string page_name: "";
    property string button_name: "";

    property int left_shadow: 0
    property int top_shadow: 0
    property int normal_mode: 0

    //按钮序号发送
    signal sendButtonValue(int button_value);

    //页面及按钮名称发送
    signal sendPageButtonInfo(string page_name, string button_name);

    id: button_bg;
    text: "";
    style: ButtonStyle {
        property bool down: control.pressed ||
                            (control.checkable && control.checked);
        background: Item {
            Rectangle {
                //阴影
                anchors.fill: parent;
                anchors.bottomMargin: {
                    if (normal_mode)
                        return -2
                    return down ? 0 : -2
                }
                anchors.rightMargin: {
                    if (normal_mode)
                        return -2
                    return down ? 0 : -2;
                }

                anchors.leftMargin: left_shadow
                anchors.topMargin: top_shadow
                color: shadow_color
                radius: baserect.radius;
            }

            Rectangle {
                id: baserect;
                color: down ? button_color_press : button_color;
                radius: button_radius;
                anchors.fill: parent;
                border.width: border_width;
//                border.color: control.activeFocus ? border_color_press :
//                                                    border_color;
                border.color: control.pressed ? border_color_press :
                                                border_color;
                //悬停变色效果
//                Rectangle {
//                    anchors.fill: parent;
//                    radius: parent.radius;
//                    color: control.activeFocus ? border_color_press :
//                                                 border_color;
//                    opacity: control.hovered ||
//                                     control.activeFocus ? 0.1 : 0;
//                    Behavior on opacity {
//                        NumberAnimation{ duration: 100 }
//                    }
//                }
            }
        }

        /*! This defines the label of the button.    */
        label: Item {
            implicitWidth: row.implicitWidth;
            implicitHeight: row.implicitHeight;
            baselineOffset: row.y + text.y + text.baselineOffset;
            clip: true;

            Row {
                id: row;
                anchors.centerIn: parent;
                spacing: 2;
                Image {
                    source: control.iconSource;
                    anchors.verticalCenter: parent.verticalCenter;
                }

                Text {
                    id: button_text;
                    style: down ? Text.Sunken : Text.PlainText;
                    renderType: Text.NativeRendering;
                    anchors.verticalCenter: parent.verticalCenter;
                    font.family: font_family;
                    font.pixelSize: font_size;
                    font.bold: font_bold;
                    font.weight: Font.Medium
                    text: button_bg.text;
                    color: down ? text_color_press : text_color;
                    //自动换行
                    //width: button_bg.width
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    fontSizeMode: Text.FixedSize
                    minimumPixelSize: 15
                }
            }
        }
    }
    onClicked: {
        if (visible) {
//            console.log("color button press -> page_name:", page_name,
//                        ", button_name:", button_name,
//                        ", button_index", button_index);
//            if (button_index > -1) {
                sendButtonValue(button_index);
//            }
            if ((page_name.length > 0) && (button_name.length > 0)) {
                sendPageButtonInfo(page_name, button_name);
            }
        }
    }
}
