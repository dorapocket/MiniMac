#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <string.h>  // for strcmp

const char *AP_NAME = "MiniMac"; // Web配网模式下的AP-wifi名字

//暂时存储wifi账号密码
char sta_ssid[32] = {0};
char sta_password[64] = {0};
char sta_mode[32] = {0};
char sta_citycode[32] = {0};
void successReturn();
void errorReturn(String msg);
String returnPage(String str);
//配网页面代码
String page_html = R"(
<!DOCTYPE html>
<head>
    <meta charset='UTF-8'>
		<meta name="viewport" content="width=device-width,initial-scale=1.0,maximum-scale=1.0,minimum-scale=1.0,user-scalable=no">
    <title>
        MiniMac 设置
    </title>
    <style>
        *{
            margin:0;
            padding:0;
            outline:0;
        }
    .page,body {
    background-color: #ededed;
}
            .container {
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    overflow: hidden;
    color: rgba(0,0,0,0.9);
        }
        .page__hd {
    padding: 40px;
}
.page__title {
    font-size: 0;
    margin-bottom: 15px;
    text-align: left;
    /* font-size: 20px; */
    font-weight: 400;
}
.page__desc {
    margin-top: 4px;
    color: rgba(0,0,0,0.5);
    text-align: left;
    font-size: 14px;
}
.page{
    padding: 0;
    margin:0;
    outline:0;
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    overflow-y: auto;
    -webkit-overflow-scrolling: touch;
    box-sizing: border-box;
    z-index: 1;
}
.weui-form {
    padding: calc(56px + env(safe-area-inset-top)) env(safe-area-inset-right) env(safe-area-inset-bottom) env(safe-area-inset-left);
    display: flex;
    -webkit-box-orient: vertical;
    -webkit-box-direction: normal;
    flex-direction: column;
    line-height: 1.4;
    min-height: 100%;
    box-sizing: border-box;
    background-color: #fff;
}
.weui-form__text-area {
    padding: 0 32px;
    color: rgba(0,0,0,0.9);
    text-align: center;
}
.weui-form__title {
    font-size: 22px;
    font-weight: 700;
    line-height: 1.36;
}
.weui-form__desc {
    font-size: 17px;
    margin-top: 16px;
}
.weui-form__control-area {
    flex: 1;
    margin: 48px 0;
}
.weui-cells__group:first-child {
    margin-top: 0;
}
.weui-cells__group_form {
    margin-top: 24px;
}
.weui-cells__group {
    border: 0;
}
.weui-cells__group_form:first-child .weui-cells__title {
    margin-top: 0;
}
.weui-cells__group_form .weui-cells__title {
    margin-top: 24px;
    margin-bottom: 8px;
    padding: 0 32px;
}
.weui-cells__title {
    margin-top: 16px;
    margin-bottom: 3px;
    padding-left: 16px;
    padding-right: 16px;
    color: rgba(0,0,0,0.5);
    font-size: 14px;
    line-height: 1.4;
}
.weui-cells__group_form .weui-cells {
    margin-left: 16px;
    margin-right: 16px;
}
.weui-cells__title+.weui-cells {
    margin-top: 0;
}
.weui-cells {
    margin-top: 8px;
    background-color: #fff;
    line-height: 1.41176471;
    font-size: 17px;
    overflow: hidden;
    position: relative;
}
.weui-cells__group_form .weui-cells:before, .weui-cells__group_form .weui-cells:after {
    left: 16px;
    right: 16px;
}
.weui-cells:before {
    content: " ";
    position: absolute;
    left: 0;
    top: 0;
    right: 0;
    height: 1px;
    border-top: 1px solid rgba(0,0,0,0.1);
    color: rgba(0,0,0,0.1);
    -webkit-transform-origin: 0 0;
    transform-origin: 0 0;
    -webkit-transform: scaleY(0.5);
    transform: scaleY(0.5);
    z-index: 2;
}
.weui-cells__group_form .weui-cell:not(.weui-cell_link) {
    color: rgba(0,0,0,0.9);
}

.weui-cells__group_form input, .weui-cells__group_form textarea, .weui-cells__group_form label[for] {
    -webkit-tap-highlight-color: rgba(0,0,0,0);
}
.weui-cells__group_form .weui-cell {
    padding: 16px 16px;
}
.weui-cell {
    padding: 16px;
    position: relative;
    display: -webkit-box;
    display: -webkit-flex;
    display: flex;
    -webkit-box-align: center;
    -webkit-align-items: center;
    align-items: center;
}
.weui-cells__group_form .weui-cell__hd {
    padding-right: 16px;
}
.page.form_page .weui-label {
    width: 4.1em;
}
.weui-cells__group_form .weui-label {
    max-width: 5em;
    margin-right: 8px;
}
.weui-label {
    display: block;
    width: 105px;
    word-wrap: break-word;
    word-break: break-all;
}
.weui-cell__bd {
    -webkit-box-flex: 1;
    -webkit-flex: 1;
    flex: 1;
    min-width: 0;
}
.weui-input {
    width: 100%;
    border: 0;
    outline: 0;
    -webkit-appearance: none;
    background-color: transparent;
    font-size: inherit;
    color: inherit;
    height: 1.41176471em;
    line-height: 1.41176471;
}
.weui-form__tips-area, .weui-form__extra-area {
    margin-bottom: 24px;
    padding: 0 32px;
    text-align: center;
}
.weui-form__tips {
    color: rgba(0,0,0,0.5);
    font-size: 14px;
}
.weui-form__opr-area {
    padding: 0 32px;
}
.weui-btn_disabled, .weui-btn[disabled] {
    color: rgba(0,0,0,0.2);
    background-color: #f2f2f2;
}
.weui-btn_primary {
    background-color: #07c160;
}
.weui-btn {
    position: relative;
    display: block;
    width: 184px;
    margin-left: auto;
    margin-right: auto;
    padding: 8px 24px;
    box-sizing: border-box;
    font-weight: 700;
    font-size: 17px;
    text-align: center;
    text-decoration: none;
    color: #fff;
    line-height: 1.88235294;
    border-radius: 8px;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
}
a {
    text-decoration: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
}
.weui-form__opr-area+.weui-form__tips-area {
    margin-top: 16px;
    margin-bottom: 0;
}
.weui-form__tips-area, .weui-form__extra-area {
    margin-bottom: 24px;
    padding: 0 32px;
    text-align: center;
}
.weui-form__tips {
    color: rgba(0,0,0,0.5);
    font-size: 14px;
}
.weui-form__tips-area+.weui-form__extra-area {
    margin-top: 32px;
}
.weui-form__extra-area {
    margin-top: 52px;
}
.weui-form .weui-footer, .weui-form .weui-footer__link {
    font-size: 14px;
}
.weui-footer {
    color: rgba(0,0,0,0.3);
    font-size: 14px;
    line-height: 1.4;
    text-align: center;
}
.weui-footer__text {
    padding: 0 16px;
    font-size: 12px;
}


.weui-check {
    opacity: 0;
    position: absolute;
    width: 0;
    height: 0;
    overflow: hidden;
}

input, textarea {
    caret-color: #07c160;
}
.weui-check__label {
    -webkit-tap-highlight-color: rgba(0,0,0,0);
}
.weui-cells_radio .weui-check+.weui-icon-checked {
    min-width: 16px;
    color: transparent;
}
.weui-cells_radio .weui-check:checked+.weui-icon-checked, .weui-cells_radio .weui-check[aria-checked="true"]+.weui-icon-checked {
    color: #07c160;
    -webkit-mask-image: url(data:image/svg+xml,%3Csvg%20width%3D%2224%22%20height%3D%2224%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%3E%3Cpath%20d%3D%22M8.657%2018.435L3%2012.778l1.414-1.414%204.95%204.95L20.678%205l1.414%201.414-12.02%2012.021a1%201%200%2001-1.415%200z%22%20fill-rule%3D%22evenodd%22%2F%3E%3C%2Fsvg%3E);
    mask-image: url(data:image/svg+xml,%3Csvg%20width%3D%2224%22%20height%3D%2224%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%3E%3Cpath%20d%3D%22M8.657%2018.435L3%2012.778l1.414-1.414%204.95%204.95L20.678%205l1.414%201.414-12.02%2012.021a1%201%200%2001-1.415%200z%22%20fill-rule%3D%22evenodd%22%2F%3E%3C%2Fsvg%3E);
}
[class^="weui-icon-"][class^="weui-icon-"], [class^="weui-icon-"][class*=" weui-icon-"], [class*=" weui-icon-"][class^="weui-icon-"], [class*=" weui-icon-"][class*=" weui-icon-"] {
    display: inline-block;
    vertical-align: middle;
    font-size: 10px;
    width: 2.4em;
    height: 2.4em;
    -webkit-mask-position: 50% 50%;
    mask-position: 50% 50%;
    -webkit-mask-repeat: no-repeat;
    mask-repeat: no-repeat;
    -webkit-mask-size: 100%;
    mask-size: 100%;
    background-color: currentColor;
}
    </style>
</head>
<body style="margin:0;padding:0;outline:0;">
    <div class="container">
        <div class="page">
            <div class="weui-form">
                <div class="weui-form__text-area">
                    <h2 class=""weui-form__title>欢迎</h2>
                    <div class="weui-form__desc">
                        欢迎使用MiniMac，你可以在这里配置网络信息，虽然它还有bug，但。。心意重要嘛！！生日快乐！！
                    </div>
                </div>
                <div class="weui-form__control-area">
                    <div class="weui-cells__group weui-cells__group_form">
                        <div class="weui-cells__title">
                            Wifi连接模式选择
                        </div>
                        <div class="weui-cells weui-cells_radio">
                            <label id="labelNormal" for="mode-normal" class="weui-cell weui-cell_active weui-check__label">
                                <div class="weui-cell__bd">
                                    <p>正常模式(仅需wifi验证)</p>
                                </div>
                                <div class="weui-cell__ft">
                                    <input type="radio" class="weui-check" name = "mode" value="normal" id="mode-normal">
                                    <span class="weui-icon-checked"></span>
                                </div>
                            </label>
                        
                        </div>
                    </div>
                    <div class="weui-cells__group weui-cells__group_form">
                        <div class="weui-cells__title">
                            Wifi信息配置
                        </div>
                        <div class="weui-cells">
                            <label for="username" class="weui-cell weui-cell_active">
                                <div class="weui-cell__hd">
                                    <span class="weui-label">Wifi名称</span>
                                </div>
                                <div class="weui-cell__bd">
                                    <input id="username" name="username" class="weui-input" placeholder="请填写Wifi SSID">
                                </div>
                            </label>
                        </div>
                        <div class="weui-cells">
                            <label for="password" class="weui-cell weui-cell_active">
                                <div class="weui-cell__hd">
                                    <span class="weui-label">Wifi密码</span>
                                </div>
                                <div class="weui-cell__bd">
                                    <input id="password" type="password" name="password" class="weui-input" placeholder="请填写Wifi密码">
                                </div>
                            </label>
                        </div>
                    </div>
                   
                </div>
                <div class="weui-form__tips-area">
                    <p class="weui-form__tips">提交后，MiniMac将重启，若连接失败会重新进入配网模式</p>
                </div>
                <div class="weui-form__opr-area">
                    <a id="submitBtn" role="button" wah-hotarea="click" aria-disabled="true" class="weui-btn weui-btn_primary weui-btn_disabled" >确定</a>
                </div>
                <div class="weui-form__tips-area">
                    <p class="weui-form__tips"></p>
                </div>
                <div class="weui-form__extra-area">
                    <div class="weui-footer">
                        <p class="weui-footer__text">MiniMac
                        </p>
                    </div>
                </div>
            </div>
        </div>

    </div>
    <script>
       window.loginmode='normal';
        document.getElementById('labelNormal').addEventListener('click',function(){
            setMode('normal');
        })
        document.getElementById('submitBtn').addEventListener('click',function(){
            let mode = window.loginmode;
            let ssid = document.getElementById('username').value;
            let password = document.getElementById('password').value;

            if(ssid==""){alert('请输入Wifi名称');return;}

            location.href="/setInfo"+"?mode="+encodeURI(loginmode)+"&ssid="+encodeURI(ssid)+"&password="+encodeURI(password);
        })
    </script>
</body>
)";

const byte DNS_PORT = 53;       // DNS端口号
IPAddress apIP(192, 168, 4, 1); // esp32-AP-IP地址
DNSServer dnsServer;            //创建dnsServer实例
WebServer server(80);           //创建WebServer

void handleRoot()
{ //访问主页回调函数
  server.send(200, "text/html", page_html);
}

void handleRootPost()
{ // Post回调函数
  Serial.println("handleRootPost");
  if (server.hasArg("ssid"))
  { //判断是否有账号参数
    Serial.print("got ssid:");
    strcpy(sta_ssid, server.arg("ssid").c_str()); //将账号参数拷贝到sta_ssid中
    Serial.println(sta_ssid);
  }
  else
  { //没有参数
    Serial.println("error, not found ssid");
    errorReturn("没有找到Wifi SSID字段，重新输一下看看吧！");
    //server.send(200, "text/html", "<meta charset='UTF-8'>提示：请输入WiFi名称"); //返回错误页面
    return;
  }
  //密码与账号同理
  if (server.hasArg("password"))
  {
    Serial.print("got password:");
    strcpy(sta_password, server.arg("password").c_str());
    Serial.println(sta_password);
  }
  else
  {
    Serial.println("error, not found password");
    errorReturn("没有找到Wifi密码字段，重新输一下看看吧！");
    return;
  }

  // 国科大模式
  if (server.hasArg("mode"))
  {
    Serial.print("got mode:");
    strcpy(sta_mode, server.arg("mode").c_str());
    Serial.println(sta_mode);
  }
  else
  {
    Serial.println("error, not found mode");
    errorReturn("请先选择连接模式哦~");
    return;
  }

  if (server.hasArg("citycode"))
  {
    Serial.print("got citycode:");
    strcpy(sta_citycode, server.arg("citycode").c_str());
    Serial.println(sta_citycode);
  }

  preferences.begin("wifi", false);
  preferences.putString("ssid", sta_ssid);
  preferences.putString("password", sta_password);
  preferences.putString("citycode", sta_citycode);
  preferences.end();
  successReturn();
  delay(2000);
  //连接wifi
  // connectNewWifi();

  ESP.restart(); //重启ESP32
}

void initBasic(void)
{ //初始化基础
  // Serial.begin(115200);
  // WiFi.hostname("Smart-ESP32");//设置ESP32设备名
}

void initSoftAP(void)
{ //初始化AP模式
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  if (WiFi.softAP(AP_NAME))
  {
    Serial.println("ESP32 SoftAP is right");
  }
}

void initWebServer(void)
{ //初始化WebServer
  // server.on("/",handleRoot);
  //上面那行必须以下面这种格式去写否则无法强制门户
  server.on("/", HTTP_GET, handleRoot);      //设置主页回调函数
  server.on("/setInfo", HTTP_GET, handleRootPost);      //设置主页回调函数
  server.onNotFound(handleRoot);             //设置无法响应的http请求的回调函数
  server.begin();                            //启动WebServer
  Serial.println("WebServer started!");
}

void initDNS(void)
{ //初始化DNS服务器
  if (dnsServer.start(DNS_PORT, "*", apIP))
  { //判断将所有地址映射到esp8266的ip上是否成功
    Serial.println("start dnsserver success.");
  }
  else
    Serial.println("start dnsserver failed.");
}

void connectNewWifi(void)
{
  WiFi.mode(WIFI_STA);                                //切换为STA模式
                                                      // WiFi.setAutoConnect(true);//设置自动连接
  WiFi.begin(PrefSSID.c_str(), PrefPassword.c_str()); //连接上一次连接成功的wifi
  Serial.println("");
  Serial.print("Connect to wifi");
  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    count++;
    if (count > 20)
    { //如果10秒内没有连上，就开启Web配网 可适当调整这个时间
      initSoftAP();
      initWebServer();
      initDNS();
      break; //跳出 防止无限初始化
    }
    Serial.print(".");
  }
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WIFI Connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.stop();
  }
}

String returnPage(String iconName,String bigtitle,String desc,String onclick,String btnStr){

  String htmltemplate = R"(<!DOCTYPE html>
<head>
    <meta charset='UTF-8'>
		<meta name="viewport" content="width=device-width,initial-scale=1.0,maximum-scale=1.0,minimum-scale=1.0,user-scalable=no">
    <title>
        MiniMac 操作结果
    </title>
    <style>
        * {
            margin:0;
            padding:0;
            outline:0;
        }
        .container {
    position: absolute;
    top: 0;
    right: 0;
    bottom: 0;
    left: 0;
    overflow: hidden;
    color: #ededed;
}
.weui-msg {
    padding-top: 48px;
    padding: calc(48px + constant(safe-area-inset-top)) constant(safe-area-inset-right) constant(safe-area-inset-bottom) constant(safe-area-inset-left);
    padding: calc(48px + env(safe-area-inset-top)) env(safe-area-inset-right) env(safe-area-inset-bottom) env(safe-area-inset-left);
    text-align: center;
    line-height: 1.4;
    min-height: 100%;
    box-sizing: border-box;
    display: -webkit-box;
    display: -webkit-flex;
    display: flex;
    -webkit-box-orient: vertical;
    -webkit-box-direction: normal;
    -webkit-flex-direction: column;
    flex-direction: column;
    background-color: #fff;
}
.weui-msg__icon-area {
    margin-bottom: 32px;
}
.weui-icon_msg.weui-icon_msg {
    width: 6.4em;
    height: 6.4em;
}
[class^="weui-icon-"][class^="weui-icon-"], [class^="weui-icon-"][class*=" weui-icon-"], [class*=" weui-icon-"][class^="weui-icon-"], [class*=" weui-icon-"][class*=" weui-icon-"] {
    display: inline-block;
    vertical-align: middle;
    font-size: 10px;
    -webkit-mask-position: 50% 50%;
    mask-position: 50% 50%;
    -webkit-mask-repeat: no-repeat;
    mask-repeat: no-repeat;
    -webkit-mask-size: 100%;
    mask-size: 100%;
    background-color: currentColor;
}
.weui-icon-success {
    color: #07c160;
}
.weui-icon-success {
    -webkit-mask-image: url(data:image/svg+xml,%3Csvg%20width%3D%2224%22%20height%3D%2224%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%3E%3Cpath%20d%3D%22M12%2022C6.477%2022%202%2017.523%202%2012S6.477%202%2012%202s10%204.477%2010%2010-4.477%2010-10%2010zm-1.177-7.86l-2.765-2.767L7%2012.431l3.119%203.121a1%201%200%20001.414%200l5.952-5.95-1.062-1.062-5.6%205.6z%22%2F%3E%3C%2Fsvg%3E);
    mask-image: url(data:image/svg+xml,%3Csvg%20width%3D%2224%22%20height%3D%2224%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%3E%3Cpath%20d%3D%22M12%2022C6.477%2022%202%2017.523%202%2012S6.477%202%2012%202s10%204.477%2010%2010-4.477%2010-10%2010zm-1.177-7.86l-2.765-2.767L7%2012.431l3.119%203.121a1%201%200%20001.414%200l5.952-5.95-1.062-1.062-5.6%205.6z%22%2F%3E%3C%2Fsvg%3E);
}
.weui-msg__text-area {
    margin-bottom: 32px;
    padding: 0 32px;
    -webkit-box-flex: 1;
    -webkit-flex: 1;
    flex: 1;
    line-height: 1.6;
    word-wrap: break-word;
    -webkit-hyphens: auto;
    hyphens: auto;
}
.weui-msg__title {
    margin-bottom: 16px;
    font-weight: 500;
    font-size: 22px;
    color: rgba(0,0,0,0.9);
}
.weui-msg__desc {
    font-size: 17px;
    font-weight: 400;
    color: rgba(0,0,0,0.9);
    margin-bottom: 16px;
}
.weui-msg__opr-area {
    margin-bottom: 16px;
}
.weui-btn_primary {
    background-color: #07c160;
}
.weui-btn {
    position: relative;
    display: block;
    width: 184px;
    margin-left: auto;
    margin-right: auto;
    padding: 8px 24px;
    box-sizing: border-box;
    font-weight: 700;
    font-size: 17px;
    text-align: center;
    text-decoration: none;
    color: #fff;
    line-height: 1.88235294;
    border-radius: 8px;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
}
a {
    text-decoration: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
}
.weui-msg__opr-area+.weui-msg__tips-area {
    margin-bottom: 48px;
}
.weui-msg__tips-area {
    margin-bottom: 16px;
    padding: 0 40px;
    word-wrap: break-word;
    -webkit-hyphens: auto;
    hyphens: auto;
}
.weui-msg__tips {
    font-size: 12px;
    color: rgba(0,0,0,0.5);
}
.weui-msg__extra-area {
    margin-bottom: 24px;
    padding: 0 32px;
    box-sizing: border-box;
    font-size: 12px;
    color: rgba(0,0,0,0.5);
}
.weui-footer {
    color: rgba(0,0,0,0.3);
    font-size: 14px;
    line-height: 1.4;
    text-align: center;
}
.weui-footer__text {
    padding: 0 16px;
    font-size: 12px;
}
.weui-icon_msg.weui-icon_msg.weui-icon-warn {
    color: #fa5151;
}
.weui-icon-warn {
    color: #fa5151;
}
.weui-icon-warn {
    -webkit-mask-image: url(data:image/svg+xml,%3Csvg%20width%3D%2224%22%20height%3D%2224%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%3E%3Cpath%20d%3D%22M12%2022C6.477%2022%202%2017.523%202%2012S6.477%202%2012%202s10%204.477%2010%2010-4.477%2010-10%2010zm-.763-15.864l.11%207.596h1.305l.11-7.596h-1.525zm.759%2010.967c.512%200%20.902-.383.902-.882%200-.5-.39-.882-.902-.882a.878.878%200%2000-.896.882c0%20.499.396.882.896.882z%22%2F%3E%3C%2Fsvg%3E);
    mask-image: url(data:image/svg+xml,%3Csvg%20width%3D%2224%22%20height%3D%2224%22%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%3E%3Cpath%20d%3D%22M12%2022C6.477%2022%202%2017.523%202%2012S6.477%202%2012%202s10%204.477%2010%2010-4.477%2010-10%2010zm-.763-15.864l.11%207.596h1.305l.11-7.596h-1.525zm.759%2010.967c.512%200%20.902-.383.902-.882%200-.5-.39-.882-.902-.882a.878.878%200%2000-.896.882c0%20.499.396.882.896.882z%22%2F%3E%3C%2Fsvg%3E);
}
    </style>
</head>
<body>
    <div class="container">
        <div class="weui-msg">
            <div class="weui-msg__icon-area">
                <i class="weui-icon-)";
htmltemplate=htmltemplate+iconName;
htmltemplate=htmltemplate+R"( weui-icon_msg"></i>
            </div>
            <div class="weui-msg__text-area">
                <h2 class="weui-msg__title">)";
htmltemplate=htmltemplate+bigtitle;
htmltemplate=htmltemplate+R"(</h2>
                <p class="weui-msg__desc">)";
htmltemplate=htmltemplate+desc;
htmltemplate=htmltemplate+R"(</p>
            </div>
            <div class="weui-msg__opr-area">
                <p class="weui-btn-area">
                    <a onclick=")";  
htmltemplate=htmltemplate+onclick;
htmltemplate=htmltemplate+R"(" role="button" class="weui-btn weui-btn_primary">)";
htmltemplate=htmltemplate+btnStr;
htmltemplate=htmltemplate+R"(</a>

                </p>
            </div>
            <div class="weui-msg__tips-area">
                <p class="weui-msg__tips">
                    ≥ω≤
                </p>
            </div>
            <div class="weui-msg__extra-area">
                <div class="weui-footer">
                    <p class="weui-footer__text">
                        MiniMac
                    </p>
                </div>
            </div>
        </div>
    </div>
    <script>
        function goback(){
            location.href="/";
        }
        function close(){
            try {
       window.opener = window;
       var win = window.open("","_self");
       win.close();
       //frame的时候
       top.close();
   } catch (e) {
 
   }
        }
    </script>
</body>)";
 return htmltemplate;
}
void successReturn(){
  String page = returnPage("success","操作成功","MiniMac已收到连接信息，正在重启，可以使用啦~","close()","关闭本页");
  server.send(200, "text/html", page);
}
void errorReturn(String msg){
  String page = returnPage("warn","操作失败",msg,"goback()","重新填写");
  server.send(200, "text/html", page);
}
