import QtQuick 2.0

import "../QtQuick/VirtualKeyboard"

Item {
    id: keyboardContainer;

    property int keyboard_index: 0;

    VirtualKeyBoard {
        id: virtural_keyboard;
        visible: keyboardContainer.visible;
        anchors.fill: parent;
    }
}
