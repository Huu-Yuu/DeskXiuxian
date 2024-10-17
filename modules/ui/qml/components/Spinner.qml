

/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
import QtQuick 2.0

Rectangle {
    width: 64
    height: 64
    color: "transparent"
    property alias value: list.currentIndex
    property alias modelValue: list.model
    property alias subWidth: subObject.width
    property alias subHeight: subObject.height
    property alias unit: subObject.unit
    property alias multiple: subObject.multiple
    property alias xRatio: subObject.xRatio
    property alias divisor: subObject.divisor
    property alias decimals: subObject.decimals
    property alias minValue: subObject.minValue
    property int font_size: 24
    Rectangle {
        id: subObject
        anchors.topMargin: 4
        //        anchors.horizontalCenter: parent.horizontalCenter
        height: 64
        width: 64
        color: "transparent"
        property string unit
        property int multiple
        property int xRatio
        property int divisor
        property int decimals
        property int minValue
        ListView {
            id: list
            anchors.fill: parent
            highlightRangeMode: ListView.StrictlyEnforceRange
            preferredHighlightBegin: parent.height / 3
            preferredHighlightEnd: parent.height / 3
            cacheBuffer : 60
            clip: true
            model: 64
            highlightResizeVelocity: 1000
            highlightMoveVelocity: -1
            delegate: Rectangle {
                color: "#00FFFFFF"
                height: 70
                width: 60 //modify 40->60 解决遮挡问题
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: {
                        if (index == list.currentIndex)
                            return font_size * 1.25
                        return font_size
                    }
                    font.bold: index == list.currentIndex
                    color: {
                        if (index == list.currentIndex)
                            return "#002c38"
                        return "#666666"
                    }
                    text: {
                        if (((index + minValue) * multiple * 1.0 / divisor) < 10)
                            "0" + Number((index + minValue) * multiple * 1.0
                                         / divisor).toLocaleString(
                                        'f', decimals) + unit
                        else {
                            Number((index + minValue) * multiple * 1.0 / divisor).toLocaleString(
                                        'f', decimals) + unit
                        }
                    }
                }
            }
        }
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#FF000000"
                }
                GradientStop {
                    position: 0.2
                    color: "#00000000"
                }
                GradientStop {
                    position: 0.8
                    color: "#00000000"
                }
                GradientStop {
                    position: 1.0
                    color: "#FF000000"
                }
            }
        }
    }
}
