pragma Singleton
import QtQuick 2.0

Item {
    id: json_phase

    property string nextPageName_: "kInitPage"
    property string prefixPageName_: ""
    property int buttonValue_: -1
    property string buttonName_: ""
    property string verifySuccessPageName_: ""

    function setVerifySuccessPageName(pageName){
        verifySuccessPageName_ = pageName
    }

    function vefifySuccessPageName(){
        return verifySuccessPageName_
    }

    function prefixPageName(){
        return prefixPageName_
    }
    function setNextPageName(nextPageName){
        if(nextPageName !== nextPageName_){
            prefixPageName_ = nextPageName_
            nextPageName_ = nextPageName
        }
//        console.log("page name changed nextPageName:", nextPageName, "prefixPage:", prefixPageName_)
    }
    function setPrefixPageName(prefixPageName){
//        prefixPageName_ = prefixPageName
    }

    function setButtonValue(buttonValue){
        buttonValue_ = buttonValue
    }
    function setButtonName(buttonName){
        buttonName_ = buttonName
    }

    function buttonValue(){
        return buttonValue_
    }
    function buttonName(){
        return buttonName_
    }

    signal nextPageNameChanged(string nextPageName)
    signal prefixPageNameChanged(string prefixPageName)
    signal buttonValueChanged(int buttonValue)

    onNextPageName_Changed: {
        nextPageNameChanged(nextPageName_)
//        nextPageName_ = ""
    }
    onPrefixPageName_Changed: {
        prefixPageNameChanged(prefixPageName_)
//        prefixPageName_ = ""
    }
    onButtonValue_Changed: {
        buttonValueChanged(buttonValue_)
//        buttonValue_ = -1
    }

    //json数据解析、分发
    property string json_data: qmlAdapter.data2Qml
    //存储注册qml模型
    property var modelMap: ({})

    Connections{
        target: qmlAdapter
        onData2QmlChanged:{
            //console.log("data in:", json_data)
            //json数据解析
            var obj = JSON.parse(json_data)
            //console.log("data for:", obj.pageName)
            //这里设置完页面名称在main.qml会动态加载对应的qml页面，
            //下面调用jsonDataParse()把具体数据呈现到页面
            if ((obj.pageName !== "kStatusPage") && (obj.pageName !== "kNoticePage") &&
                (obj.pageName !== "kSecondaryPage")
		&& (obj.pageName !== "kFaceExpressionPage")) {
                setNextPageName(obj.pageName)
            }
            //json数据分发到页面
            if(modelMap.hasOwnProperty(obj.pageName))
                modelMap[obj.pageName].jsonDataParse(obj.pageMsg)
        }
    }
    //注册qml数据模型
    function registerPage(pageName, object){
        modelMap[pageName] = object
    }
    //json转发到c++
    function jsonDataOut(data_out){
        //console.log("data out:", data_out)
        qmlAdapter.data2Cpp = data_out
    }
}
