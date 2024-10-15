var component
function createNoticeObject(fileName, root, attribute){
    component = Qt.createComponent(fileName)
    if(component.status === Component.Ready ||
    component.status === Component.Error){
        return finishCreation(root, attribute)
    }else{
        console.log("error component create")
//        component.statusChanged.connect(finishCreation)
    }   
}
function finishCreation(root, attribute) {
    if(component.status === Component.Ready){
        var createObj = component.createObject(root, attribute)
        if(createObj === null){
            console.log("error creating obj")
        }
        return createObj
    }else{
        console.log("error loading component:", component.errorString())
    }
    return null
}
