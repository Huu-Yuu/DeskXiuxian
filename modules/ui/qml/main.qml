import QtQuick 2.11
import QtQuick.Window 2.10
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import "./"

ApplicationWindow{
    id: mainWindow
    width: 1120
    height: 700
    visible: true
    title: "桌面修仙"
    maximumWidth: 1120
    maximumHeight: 700
    minimumWidth: 1120
    minimumHeight: 700
    property string page_url: "./WelcomePage.qml"
    property var page_stack_listor: []

    // Loader加载不同组件，实现切换页面的功能
    Loader{
        id: pageLoder
        anchors.fill: parent    // 弹出的界面填充到父类窗口
    }
    Component.onCompleted: pageLoder.source = page_url

    //stack界面切换
    function switchPage(source, param_obj) {
        if (source === "qrc:/qml/HomePage.qml") {
            page_stack_listor = [] //清空
        }
        if (param_obj === undefined)
            param_obj = {

            }
        //登陆界面不在返回
        if (source !== "qrc:/qml/subpage/homepage/LoginPasswd.qml")
            page_stack_listor.push({
                                       "source": source,
                                       "param": param_obj
                                   })
        pageLoder.setSource(Qt.resolvedUrl(source), param_obj)
    }

    function returnPage() {
        if (page_stack_listor.length > 0) {
            page_stack_listor.pop()
        }
        if (page_stack_listor.length > 0) {
            var show_obj = page_stack_listor[page_stack_listor.length - 1]
            pageLoder.setSource(Qt.resolvedUrl(show_obj.source), show_obj.param)
            return
        }
        mainWindow.switchPage("qrc:/qml/HomePage.qml")
    }

    function reshowPage() {
        if (page_stack_listor.length > 0) {
            var show_obj = page_stack_listor[page_stack_listor.length - 1]
            pageLoder.setSource(Qt.resolvedUrl(show_obj.source), show_obj.param)
            return
        }
        mainWindow.switchPage("qrc:/qml/HomePage.qml")
    }

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }
}
