import QtGraphicalEffects 1.0
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Popup {
    modal: true
    dim: false
    focus: true
    margins : 0
    padding: 0
    background: Rectangle {
        id: backgroundRect
        radius: Qt.platform.os === 'windows' ? 0 : 10
//        border.width: 1
//        border.color: "#EBEDF0"
        color: "transparent"
        layer.enabled: true
//        border.width: 0
        layer.effect: DropShadow {
            width: backgroundRect.width
            height: backgroundRect.height
            x: backgroundRect.x - 2
            y: backgroundRect.y - 2
            visible: backgroundRect.visible
            source: backgroundRect
            horizontalOffset: 0
            verticalOffset: 0
            radius: 16
            samples: 33
//            color: "#1917171a"
            color: "transparent"
//            opacity: 0.8
        }
    }
}
