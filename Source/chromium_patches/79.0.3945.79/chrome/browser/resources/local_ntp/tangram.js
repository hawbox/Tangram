tangram.ipcMessage__("NEW_TAB_PAGE_LOADED", "", "");

tangram.onMessageReceived = function (e) {
    if (e.to == "system" && e.extra == "__getElementById__") {
        var id = e.payload;
        var htmlElement = document.getElementById(id);
        var htmlInnerHTML = htmlElement.innerHTML;
        tangram.sendMessage("system@" + e.from, htmlInnerHTML, "__getElementById__", e.msgId);
    }
}

//alert(111);