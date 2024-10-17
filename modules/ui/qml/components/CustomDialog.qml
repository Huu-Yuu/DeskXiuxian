import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import "./"
import "../adapter"

Item {
    id: root
    width: 1280 * ScreenAdapter.widthDip
    height: 800 * ScreenAdapter.heightDip
    x: 0 //backgroundRect.x
    y: 0 //backgroundRect.y

    property alias text: title.text
    property alias description: description.text
    property string confirmText: qsTr('OK')
    property string cancelText: qsTr('Cancel')
    property bool showCancel: true

    signal confirm
    signal cancel
    Rectangle {
        anchors.fill: parent
        color: "#2A2A2A"
        opacity: 0.8
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {

        }
    }
    Dialog {
        id: dialog
        closePolicy: Popup.CloseOnEscape
        width: 400 * ScreenAdapter.widthDip
        height: 260 * ScreenAdapter.heightDip
        modal: false
        dim: false
        padding: 0
        margins: 0
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        background: Rectangle {
            id: backgroundRect
            radius: Qt.platform.os === 'windows' ? 0 : 10
            border.width: 1
            border.color: "#EBEDF0"
            layer.enabled: true
            layer.effect: DropShadow {
                width: backgroundRect.width
                height: backgroundRect.height
                x: backgroundRect.x
                y: backgroundRect.y
                visible: backgroundRect.visible
                source: backgroundRect
                horizontalOffset: 0
                verticalOffset: 2
                radius: 8
                samples: 16
                color: "#1917171a"
                //                color: "#2A2A2A"
            }
        }

        onClosed: {
            // When created dynamically, is called when the dialog is closed only but the parent object is not destroyed
            root.destroy()
        }

        Label {
            id: title
            width: parent.width
            font.pixelSize: 30 * ScreenAdapter.minDip
            wrapMode: Text.WrapAnywhere
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Label {
            id: description
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: 30
            anchors.top: title.bottom
            anchors.topMargin: 60 * ScreenAdapter.minDip
            font.pixelSize: 30 * ScreenAdapter.minDip
            wrapMode: Text.WrapAnywhere
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        CustomToolSeparator {
            visible: confirmText.length > 0
            width: parent.width
            anchors.left: parent.left
            anchors.bottom: confirm.top
        }

        ToolSeparator {
            visible: confirmText.length > 0
            anchors.top: confirm.top
            anchors.left: confirm.right
            anchors.leftMargin: 1
            orientation: Qt.Vertical
            padding: 0
            spacing: 0
            contentItem: Rectangle {
                implicitWidth: 1
                implicitHeight: confirm.height
                color: "#EBEDF0"
            }
            //            Component.onCompleted: console.log("分割的高度" + height)
        }

        CustomButton {
            id: confirm
            visible: confirmText.length > 0
            anchors.left: parent.left
            anchors.leftMargin: showCancel ? 1 : (parent.width / 2 - confirm.width / 2)
            anchors.bottom: parent.bottom
            width: showCancel ? (parent.width / 2 - 2) : parent.width
            height: 44
            text: confirmText
            buttonRadius: Qt.platform.os === 'windows' ? 1 : 8
            borderColor: "#FFFFFF"
            normalTextColor: "#337EFF"
            borderSize: 0
            font.pixelSize: 24 * ScreenAdapter.minDip
            onClicked: {
                root.confirm()
                dialog.close()
                //                root.destroy()
            }
        }

        CustomButton {
            id: cancel
            visible: showCancel && confirmText.length > 0
            anchors.right: parent.right
            anchors.rightMargin: 1
            anchors.bottom: parent.bottom
            width: parent.width / 2 - 2
            height: 44
            text: cancelText
            buttonRadius: Qt.platform.os === 'windows' ? 1 : 8
            borderColor: "#FFFFFF"
            normalTextColor: "#333333"
            borderSize: 0
            font.pixelSize: 24 * ScreenAdapter.minDip
            onClicked: {
                root.cancel()
                dialog.close()
                //                root.destroy()
            }
        }
        Component.onCompleted: {
            console.log("width,height:", width, height)
        }
    }

    function open() {
        dialog.open()
    }
}
