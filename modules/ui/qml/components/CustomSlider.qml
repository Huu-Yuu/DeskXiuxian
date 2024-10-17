import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2
import "../adapter"
import "../components"

Item {

    property double slider_step_size: 0.001
    property alias slider_value: slider.value
    property int slider_x: 0
    property int slider_y: 0
    property int slider_width: 0
    property int slider_height: 0
    property string unit: ""
    property int fixed: 0
    property double slider_min_value: 0
    property double slider_max_value: 1
    Slider {
        id: slider
        x: slider_x
        y: slider_y
        width: slider_width
        height: slider_height
        stepSize: slider_step_size
        value: slider_value
        minimumValue: slider_min_value
        maximumValue: slider_max_value
        style: SliderStyle {
            groove: Rectangle {
                color: "#72878d"
                implicitHeight: slider.height
                implicitWidth: slider.width
                radius: 10 * ScreenAdapter.widthDip
                Rectangle {
                    implicitWidth: (slider.value - slider.minimumValue)
                                   / (slider.maximumValue - slider.minimumValue) * slider.width
                    implicitHeight: parent.height
                    radius: parent.radius
                    color: "#00b5e2"
                }
            }
            handle: Rectangle {
                visible: enabled
                width: 36 * ScreenAdapter.minDip
                height: width
                radius: width
                color: "#FFFFFF"
                border.width: 1
                border.color: "#C9C9C9"
            }
        }
        MultiPointTouchArea {
            anchors.fill: parent
            touchPoints: [
                TouchPoint {
                    id: point_1
                }
            ]
            onTouchUpdated: {
                var temp_point_x = point_1.x
                if (temp_point_x < 0)
                    temp_point_x = 0
                if (temp_point_x > slider.width)
                    temp_point_x = slider.width
                slider.value = temp_point_x / slider.width * (slider.maximumValue-slider.minimumValue) + slider.minimumValue
                //                real_value = (min_value + slider.value * (1 - min_value)) * multiple
            }
        }
    }
    Text {
        text: slider.maximumValue.toFixed(fixed).toString() + unit
        x: slider.x + slider.width + 10
        y: slider.y
        font.weight: Font.Medium

        font.pixelSize: 16 * ScreenAdapter.minDip
        color: "#002c38"
    }
    Text {
        text: slider.minimumValue.toFixed(fixed).toString() + unit
        x: slider.x - width - 10
        y: slider.y
        font.weight: Font.Medium

        font.pixelSize: 16 * ScreenAdapter.minDip
        color: "#002c38"
    }
    Text {
        visible: enabled
        text: slider.value.toFixed(fixed).toString() + unit
        x: slider.x + (slider.value - slider.minimumValue)
           / (slider.maximumValue - slider.minimumValue) * (slider.width - width)
        y: slider.y - height - 8 * ScreenAdapter.heightDip
        font.weight: Font.Medium

        font.pixelSize: 16 * ScreenAdapter.minDip
        color: "#002c38"
    }
}
