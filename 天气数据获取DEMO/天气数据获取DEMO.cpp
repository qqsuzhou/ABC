
/**************天气数据获取DEMO.cpp**************
 * 
 * 功能：1.实现网络通讯
 *       2.实现访问“心知”提供的天气预报API
 *       3.实现接收API返回的JSON
 *       4.实现JSON解析和显示
 *       5.实现JSON文件的读写
 *
 * 输入：城市名（全拼或中文）
 * 
 * 输出：城市名   当前温度    当前天气
 * 
 ***********************************************/

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>                       //网路头文件
#include "cJSON/cJSON.h"
#pragma comment(lib,"ws2_32.lib")           //网络库文件
#pragma execution_character_set("utf-8")    //解决终端显示汉字乱码("utf-8")   ("gbk")

const char* host = "api.seniverse.com";     //主机名
const char* key = "S-LVaLFypOiS0F4TG";      //私钥
const char* location = "ip";                //查询的城市
const char* language = "zh-Hans";           //中文

char gurl[100] = { 0 };                     //最终请求的URL
const char* gCity = "当地";
const char* gTemp = "";
const char* gWeather = "";
const char* gDate = "";
const char* gTest[5] ;


void initSocket();
char* generateUrl(char* key, char* loc, char* lang);
SOCKET connectToHost(const char* host, unsigned short port);
void parseJson(const char* jsonData);
void jsonFileSave(const char* buf);
void showNemu();

int main()
{
    system("chcp 65001");                       //解决终端显示汉字乱码

    // 1.初始化网络
    initSocket();                               
    SOCKET fd = connectToHost(host, 80);            //链接服务器connectToHost("116.62.81.138", 80)
    if (fd != INVALID_SOCKET) {
         printf("连接 OK\n");
    }
           
    // 2.发送心知API请求
    char* url = generateUrl((char*)key, (char*)location, (char*)language);
    if (0 >= send(fd, url, strlen(url), 0)) {
        printf("发送失败,%d\n", WSAGetLastError());
    }
  
    
    // 3.成功返回数据、生成JSON文件
    char buf[BUFSIZ] = { 0 };
    if (0 >= recv(fd, buf, BUFSIZ, 0)) {
        printf("服务器返回错误,%d\n", WSAGetLastError());
    }
    else {
        jsonFileSave(buf);
    }

    // 4.显示内容
    showNemu();
    system("pause");

    // 5.释放资源
    closesocket(fd);
    
    return 0;

}



//初始化网路库
void initSocket() {
    WSADATA data;
    if (0 != WSAStartup(MAKEWORD(2, 2), &data)) {
        printf("WSAStartup failed,%d\n", WSAGetLastError());
    }
}

//拼接访问API服务器字符串
char* generateUrl(char* key, char* loc, char* lang) {
    //sprintf(gurl, "/v3/weather/now.json?key=%s&location=%s&language=%s&unit=c", key, loc, lang);  //格式化
    //格式：GET 资源\r\n\r\n 
    sprintf(gurl, "GET /v3/weather/now.json?key=%s&location=%s&language=%s&unit=c\r\n\r\n", key, loc, lang);  //格式化
    return gurl;
}

//连接心知API服务器
SOCKET connectToHost(const char* host, unsigned short port) {
    //1.创建SOCKET
    SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == INVALID_SOCKET) {
        printf("socket failed,%d\n", WSAGetLastError());
        return INVALID_SOCKET;
    }

    //2.准备IP地址和端口
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.S_un.S_addr = inet_addr(host);

    //根据域名获取ip地址 DNS解析
    HOSTENT* hostent = gethostbyname(host);
    if (hostent) {
        //printf("%s\n", hostent->h_name);
        //printf("%s\n", hostent->h_addr_list[0]);
        memcpy(&addr.sin_addr, hostent->h_addr_list[0], sizeof(addr.sin_addr));
    }
    else {
        printf("域名解析失败\n");
        return INVALID_SOCKET;
    }

    //3.连接服务器
    if (0 != connect(fd, (SOCKADDR*)&addr, sizeof(addr))) {
        printf("connect failed,%d \n", WSAGetLastError);
        return INVALID_SOCKET;
    }

    return fd;
}

//解析心知的气象JSON
void parseJson(const char* jsonData) {
    //使用第三方库：c语言的json解析库，cJSON
    //(https://github.com/DaveGamble/cJSON/archive/refs/heads/master.zip)

    cJSON* json = cJSON_Parse(jsonData);

    if (!json) {
        printf("json处理失败\n");
    }
    else {
        cJSON* object = NULL;
        cJSON* item = NULL;
        cJSON* arrItem = cJSON_GetObjectItem(json, "results");

        if (arrItem) {
            int size = cJSON_GetArraySize(arrItem);
            if ((object = cJSON_GetArrayItem(arrItem, 0)) != NULL) {

                if ((item = cJSON_GetObjectItem(object, "now")) != NULL) {

                    if (item = cJSON_GetObjectItem(item, "text")) {
                        //puts(item->valuestring);
                        gWeather = (char*)item->valuestring;
                    }
                }
                if ((item = cJSON_GetObjectItem(object, "location")) != NULL) {

                    if (item = cJSON_GetObjectItem(item, "name")) {
                        //puts(item->valuestring);
                        gCity = (char*)item->valuestring;
                    }

                }
                if ((item = cJSON_GetObjectItem(object, "now")) != NULL) {

                    if (item = cJSON_GetObjectItem(item, "temperature")) {
                        //puts(item->valuestring);
                        gTemp = (char*)item->valuestring;
                        gTest[0] = (char*)item->valuestring;
                    }
                }
                if ((item = cJSON_GetObjectItem(object, "last_update")) != NULL) {
                    gDate = (char*)item->valuestring;
                }

            }
        }
    }


}

//保存内容json文件
void jsonFileSave(const char* buf) {
    FILE* fp = fopen("weather.json", "w");

    if (!fp) {
        perror("创建文件错误\n");
    }
    else {
        parseJson(buf);
        fwrite(buf, sizeof(char), strlen(buf), fp);
        fclose(fp);
    }
}

//显示内容
void showNemu() {
    system("cls");
    printf("**************天气数据获取DEMO**************\n");
    printf("***\n");
    printf("***城 市 名：%s\n", gCity);
    printf("***\n");
    printf("***实时温度：%s 度\n", gTemp);
    printf("***\n");
    printf("***实时天气：%s\n", gWeather);
    printf("***\n");
    printf("***实时时间：%s\n", gDate);
    printf("***\n");
    printf("********************************************\n");
}
