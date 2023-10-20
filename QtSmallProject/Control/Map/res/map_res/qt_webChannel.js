// 显示信息
function outputMsg(msg) {
    var textArea = document.getElementById("textArea");
    if (textArea) {
        textArea.innerHTML = textArea.innerHTML + msg + "\n";
        textArea.scrollTop = textArea.scrollHeight;
    }
}
// 发送按钮点击
function senBtnClicked() {
    // 获取输出标签
    var lineEdit = document.getElementById('lineEdit');
    // 调用Qt对象函数
    WebTransport.msgToQt(lineEdit.value);
    // 显示
    outputMsg("发送信息到Qt:" + lineEdit.value);
}
// 清空
function clearBtnClicked() {
    document.getElementById("textArea").innerHTML = "";
}
// 初始化
window.onload = function init() {
    if (typeof qt !== "undefined") {
        //创建 QWebChannel 来与 C++ 通信
        new QWebChannel(qt.webChannelTransport, function(channel) {
            // 获取Qt注册的对象,设置到主窗口（这里的webTransport就是Qt端注册时的字符串id）
            window.WebTransport = channel.objects.WebTransport;
            // 绑定注册对象的信号
            WebTransport.msgToJs.connect(function(msg) {
                outputMsg("接收Qt信息：" + msg);
            });

            //给Qt发送一条消息
            WebTransport.msgToQt("初始化channel成功！");
        });
    } else {
        alert("初始化qwebchannel失败")
    }
}
