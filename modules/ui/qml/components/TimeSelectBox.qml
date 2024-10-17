import QtQuick 2.5
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
import "../adapter"
import "../components"

Item {
    property bool minute_init_ok: false
    property int hour: 0
    property int minute: 0
    property string cur_time: {
        var hour_str = hour < 10 ? "0" + hour.toString() : hour.toString()
        var mint_str = minute < 10 ? "0" + minute.toString() : minute.toString()
        return hour_str + ":" + mint_str
    }

    Rectangle {
        anchors.fill: parent
        color: "#FFFFFF"
        radius: 8 * ScreenAdapter.minDip
        border.color: "#707070"
        border.width: 1
    }

    Spinner {
        id: hour_spinner
        x: parent.width / 4
        y: 0
        width: 80 * ScreenAdapter.widthDip
        height: parent.height
        subWidth: parent.height
        subHeight: subWidth
        modelValue: 24
        minValue: 0
        value: hour
        multiple: 1
        font_size: 24 * ScreenAdapter.minDip
        xRatio: 7
        unit: ""
        divisor: 1
        decimals: 0
        onValueChanged: {
            if (minute_init_ok) {
                hour = value
            }
        }
    }

    Text {
        x: hour_spinner.x + 44 * ScreenAdapter.widthDip
        y: hour_spinner.y + parent.height / 2 - 20 * ScreenAdapter.heightDip
        font.pixelSize: 16 * ScreenAdapter.minDip
        
        font.bold: true
        color: "#666666"
        text: qsTr("时")
    }

    Text {
        x: minute_spinner.x + 44 * ScreenAdapter.widthDip
        y: minute_spinner.y + parent.height / 2 - 20 * ScreenAdapter.heightDip
        font.pixelSize: 16 * ScreenAdapter.minDip
        
        font.bold: true
        color: "#666666"
        text: qsTr("分")
    }

    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 3 * ScreenAdapter.heightDip
        height: 178 * ScreenAdapter.heightDip
        source: "file:" + "../res/pic/task_manage/spinner_line.png"
    }

    Spinner {
        id: minute_spinner
        x: parent.width * 5 / 8
        y: 0
        width: 80 * ScreenAdapter.widthDip
        height: parent.height
        subWidth: parent.height
        subHeight: subWidth
        modelValue: 60
        minValue: 0
        value: minute
        multiple: 1
        font_size: 24 * ScreenAdapter.minDip
        xRatio: 7
        unit: ""
        divisor: 1
        decimals: 0
        onValueChanged: {
            minute = value
        }
        Component.onCompleted: parent.minute_init_ok = true
    }
}
