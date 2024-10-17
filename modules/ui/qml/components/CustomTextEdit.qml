import QtQuick 2.6

Rectangle {
    id: root

    property bool word_wrap: true
    property bool clear_when_checked: true
    property bool acceptable_input: true

    property int text_edit_index: 0
    property int border_width: 0
    property string init_text: ""
    property string border_color
    property var regular_expression: RegExpValidator {
        regExp: /.*/
    }
    property string input_mask: ""
    property alias background_color: root.color
    property string text: ""
    property alias text_color: text_input.color
    property alias font_size: text_input.font.pixelSize
    property alias font_family: text_input.font.family
    property alias font_bold: text_input.font.bold
    property alias read_only: text_input.readOnly
    property alias maximum_length: text_input.maximumLength
    property alias text_input_focus: text_input.focus
    property alias focuse: text_input.focus

    //property int minimun_length: 0;

    //仅用于捕捉文本框当前值
    property string cur_text: ""

    //property string last_text: "";
    signal sendTextEditInfo(int index, string text)

    radius: 6
    clip: true
    color: "#FFFFFF"

    TextInput {
        id: text_input
        text: root.text.length > 0 ? root.text : init_text
        color: "#000000"
        font.family: "Source Han Sans CN"
        font.pixelSize: 10 * ScreenAdapter.minDip
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        clip: true
        selectByMouse: readOnly ? false : true
        readOnly: false
        inputMask: input_mask
        validator: regular_expression
        onTextChanged: {
            if (clear_when_checked && (text_input.text == init_text)) {
                return
            }

            //last_text = cur_text;
            cur_text = text_input.text
            sendTextEditInfo(text_edit_index, text_input.text)
        }
        onAcceptableInputChanged: {
            acceptable_input = acceptableInput
        }
        onFocusChanged: {
            if (clear_when_checked && !read_only) {
                if (focus) {
                    if (text_input.text === init_text) {
                        text_input.text = ""
                    }
                } else {
                    if (text_input.text.length == 0) {
                        text_input.text = init_text
                        cur_text = init_text
                    }
                }
            }
        }
        onVisibleChanged: {
            if (!visible && !read_only) {
                focus = false
            }
        }
    }
    //    //检测文本范围
    //    Rectangle {
    //        anchors.fill: text_input;
    //        color: "#660000FF";
    //    }

    //边框
    Rectangle {
        id: text_edit_border
        color: "#00FFFFFF"
        anchors.fill: parent
        radius: parent.radius
        border.color: border_color
        border.width: border_width
    }

    function setInput(set_text) {
//        console.log("当前设置文字------------" + set_text)
        text_input.text = set_text
    }
}
