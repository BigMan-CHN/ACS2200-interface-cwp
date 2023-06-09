/********************************************************
* MPSClientDefine.h
* 主机信息定义
*
* Copyright (c) 2019, Tyvis
* All rights reserved.
*
* @version		V1.00
* @author		es
* @date			2019-5-23
 *******************************************************/
#ifndef MPSCLIENTDEFINE_H
#define MPSCLIENTDEFINE_H
/********************************************************
 * public c/c++ standard headers
 *******************************************************/
#include <stdio.h>
#include <iostream>
#include <string.h>

/********************************************************
 * boost usart headers
 *******************************************************/
#include <boost/asio.hpp>
#include <boost/bind.hpp>

/********************************************************
 * lib headers
 *******************************************************/
#include <log.h>
#include <TransmitClient.h>
#include <xmlParser.h>
#include <LibXML.h>
#include <Server.h>

#define MPS_IP      "127.0.0.1"
//#define MPS_PORT    5231
//add fwb 20201026
#define MPS_PORT   6180 
#define MPS_TIMEOUT 15000

using namespace std;
using namespace SVS;

#define RES_BUF_MAXLEN 8192
#define REQ_BODY_MAXLEN 1024
#define REQ_CMD_MAXLEN 4096

/********************************************************
 * response
 *******************************************************/
#define RES_SUCCESS_FLAG            "flag"  /*0:success,1:failed*/
#define IS_SUCCESS_RES_LONG_FLAG(x)      (x==0?true:false) /* 判断返回flag正确与否 */
#define IS_SUCCESS_RES_BOOL_FLAG(x)      (x==1?true:false) /* 判断返回flag正确与否 */

/********************************************************
 * module
 *******************************************************/
#define MODULE_CONFIG                       "Config"
#define MODULE_MEDIA                        "Media"
#define MODULE_PACKAGE                      "Package"
#define MODULE_CONTROL                      "Control"
#define MODULE_MONITOR                      "Monitor"

/********************************************************
 * method common & params & response
 *******************************************************/
#define METHOD_PARAMS_WORKNUM               "worknumber"
#define METHOD_PARAMS_KEYID                 "keyID"
#define METHOD_RES_KEYID                    "keyID"
/********************************************************
 * Config method & params & response
 *******************************************************/
//GetSysConfig
#define CONFIG_METHOD_GETCONFIG             "GetConfig"/*method*/
//GetSysConfig
#define CONFIG_METHOD_GETSYSCONFIG          "GetSysConfig"/*method*/
//SetInterRtsp
#define CONFIG_METHOD_SET_INTER_RTSP        "SetInterRtsp" /*method*/
#define CONFIG_SET_INTER_RTSP_PARAMS_ID     "id" /*params*/
#define CONFIG_SET_INTER_RTSP_PARAMS_RTSPURL    "rtspurl" /*params*/
#define CONFIG_SET_INTER_RTSP_PARAMS_RTSPENABLE "rtspenable" /*params*/

/********************************************************
 * media method & params & response
 *******************************************************/
//GetStatus
#define MEDIA_METHOD_GETSTATUS              "GetStatus" /*method*/
#define MEDIA_GETSTATUS_PARAMS_WORKNUM      METHOD_PARAMS_WORKNUM /*params*/
#define MEDIA_GETSTATUS_RES_STATUSMPS       "statusMPS" /*response*/
//Prepare
#define MEDIA_METHOD_PREPARE                "Prepare_worknumber" /*method*/
#define MEDIA_PREPARE_PARAMS_WORKNUM        METHOD_PARAMS_WORKNUM /*params*/
#define MEDIA_PREPARE_PARAMS_KEYID          METHOD_PARAMS_KEYID /*params*/
#define MEDIA_PREPARE_RES_KEYID             METHOD_RES_KEYID /*response*/
//Start
#define MEDIA_METHOD_START                "Start_worknumber" /*method*/
#define MEDIA_START_PARAMS_WORKNUM        METHOD_PARAMS_WORKNUM /*params*/
#define MEDIA_START_PARAMS_KEYID          METHOD_PARAMS_KEYID /*params*/
//Stop
#define MEDIA_METHOD_STOP               "Stop_worknumber" /*method*/
#define MEDIA_STOP_PARAMS_WORKNUM       METHOD_PARAMS_WORKNUM /*params*/
#define MEDIA_STOP_PARAMS_CLOSE         "close" /*params*/
#define MEDIA_STOP_PARAMS_KEYID         METHOD_PARAMS_KEYID /*params*/
//Close
#define MEDIA_METHOD_CLOSE              "Close_worknumber" /*method*/
#define MEDIA_CLOSE_PARAMS_WORKNUM      METHOD_PARAMS_WORKNUM /*params*/
#define MEDIA_CLOSE_PARAMS_CLOSEDSP     "closeDSP" /*params*/
//SetPoint
#define MEDIA_METHOD_SET_POINT          "SetPoint" /*method*/
#define MEDIA_SET_POINT_PARAMS_CHANNEL  "channel" /*params*/
#define MEDIA_SET_POINT_RES_DURATION    "duration" /*response 开始录制到当前的时间，单位秒*/
#define MEDIA_SET_POINT_RES_FILEPATH    "filename" /*response 录制视频在主机上的全路径*/
//startProofSave
#define MEDIA_METHOD_START_PROOF_SAVE   "StartProofSave" /*method*/
//stopProofSave
#define MEDIA_METHOD_STOP_PROOF_SAVE    "StopProofSave" /*method*/
//StartInteRtsp
#define MEDIA_METHOD_START_INTE_RTSP    "StartInteRtsp" /*method*/
#define MEDIA_START_INTE_RTSP_PARAMS_ID "id" /*params*/
//StopInteRtsp
#define MEDIA_METHOD_STOP_INTE_RTSP     "StopInteRtsp" /*method*/
#define MEDIA_STOP_INTE_RTSP_PARAMS_ID  "id" /*params*/
//StartInterRtsp_Api
#define MEDIA_METHOD_START_INTER_RTSP_API               "StartInteRtsp" /*method*/
#define MEDIA_START_INTER_RTSP_API_PARAMS_DEC_NUM       "decodenumber" /*params*/
#define MEDIA_START_INTER_RTSP_API_PARAMS_URL           "url" /*params*/
#define MEDIA_START_INTER_RTSP_API_PARAMS_CACHE_TIME    "cachetime" /*params*/
#define MEDIA_START_INTER_RTSP_API_PARAMS_USE_TCP       "use_tcp" /*params*/
//StopInterRtsp_Api
#define MEDIA_METHOD_STOP_INTER_RTSP_API                "StopInteRtsp" /*method*/
#define MEDIA_STOP_INTER_RTSP_API_PARAMS_DEC_NUM        "decodenumber" /*params*/
//GetInterRtsp_Api
#define MEDIA_METHOD_GET_INTER_RTSP_API                 "GetStatusInteRtsp" /*method*/
#define MEDIA_GET_INTER_RTSP_API_PARAMS_DEC_NUM         "decodenumber" /*params*/
#define MEDIA_GET_INTER_RTSP_API_RES_STATUS             "status" /*response*/
//StartDiscipline
#define MEDIA_METHOD_START_DISCIPLINE                   "StartDiscipline" /*method*/
//StaopDiscipline
#define MEDIA_METHOD_STOP_DISCIPLINE                    "StopDiscipline" /*method*/
//GetStatusDiscipline
#define MEDIA_METHOD_GET_STATUS_DISCIPLINE              "GetStatusDiscipline" /*method*/
#define MEDIA_GET_STATUS_DISCIPLINE_RES_STATUS          "status" /*response*/

/********************************************************
 * package method & params & response
 *******************************************************/
//GetPackage
#define PACKAGE_METHOD_GET_PACKAGE              "GetPackage" /*method*/
#define PACKAGE__GET_PACKAGE_PARAMS_KEYID       METHOD_PARAMS_KEYID /*params*/
//GetPackageList
#define PACKAGE_METHOD_GET_PACKAGE_LIST         "GetPackageList" /*method*/
//UpdatePackageFlag
#define PACKAGE_METHOD_UPDATE_PACKAGE_FLAG          "UpdatePackageFlag" /*method*/
#define PACKAGE_UPDATE_PACAKGE_FLAG_PARAMS_CASEID   METHOD_PARAMS_KEYID /*params*/

/********************************************************
 * Control method & params & response
 *******************************************************/
#define CONTROL_METHOD_SENDCMD                  "SendCmd" /*method*/
#define CONTROL_SENDCMD_PARAMS_CMD              "cmd" /*params*/
#define CONTROL_SENDCMD_PARAMS_DEVICEID         "deviceID" /*params*/

/********************************************************
 * Monitor method & params & response
 *******************************************************/
#define MONITOR_METHOD_GET_SYSTEM_STATUS        "GetSystemStatus" /*method*/

/********************************************************
 * add interface method & params & response
 *******************************************************/
#define INTERFACE_GETHOSTCONFIG_SENDCMD           "sys.name\nsys._hwver\nsys._swver\nsys.sn\neth1.conf\nstatus.totalsize\nstatus.freedisk\nrec.minifreespace\ndvc.net_recv_max_num\ndvc.h323_num\ndvc.sip_num\ndvc.net_send_max_num\ndvc.rtmp_client_send_num\ndvc.uart_num\n"
#define INTERFACE_GETHOSTDECRTSP_SENDCMD          "net_recv%d.app_info\n"//"net_recv%d.url\nnet_recv%d.trans_protol\n"
#define INTERFACE_GETHOSTDECH323_SENDCMD          "h323h%d.call\n"
#define INTERFACE_GETHOSTDECSIP_SENDCMD          "sip%d.call\n"

#define INTERFACE_GETHOSTCHNINFO_SENDCMD          "net_send%d.app_info\n"//"net_send%d.name\nnet_send%d.on\nnet_send%d.url\nnet_send%d.recording\nnet_send%d.rec_path\n"
#define INTERFACE_SETDECSTART_RTSP_SENDCMD        "net_recv%d.url=%s\nnet_recv%d.cache=%d\nnet_recv%d.trans_protol=%s\n"
#define INTERFACE_SETDECSTART_H323_SENDCMD        "h323h%d.call=%s,1\n"
#define INTERFACE_SETDECSTART_SIP_SENDCMD         "sip%d.call=sip:1000@%s\n"
#define INTERFACE_SETDECSTOP_RTSP_SENDCMD         "net_recv%d.url=\n"
#define INTERFACE_SETDECSTOP_H323_SENDCMD         "h323h%d.hangup\n"
#define INTERFACE_SETDECSTOP_SIP_SENDCMD          "sip%d.hangup\n"
#define INTERFACE_SETRECORDSTART_DEFAULT_SENDCMD   "rec.app_defrec=%d,%s,%s\n" //"rec.app_start=%d,%s,%s\n"
#define INTERFACE_SETRECORDSTART_SENDCMD          "rec.app_start=%d,%s,%s\n"
#define INTERFACE_SETRECORDSTOP_SENDCMD           "rec.app_stop=%s\n"
#define INTERFACE_SETRECORDSTOP_DEFAULT_SENDCMD   "rec.app_defrec=0,%s\n"
#define INTERFACE_SETRECODELETE_SENDCMD           "rec.fdel=%s\n"
#define INTERFACE_SETSTARTDISCIPLINE_SENDCMD        "demux1.url=/mnt/HD0/demux/ms-man.mp4\n"
#define INTERFACE_SETSTOPDISCIPLINE_SENDCMD         "demux1.stop\n"
#define INTERFACE_GETSTOPDISCIPLINESTATUS_SENDCMD   "demux1.total_time\n"
#define INTERFACE_SETSTREAM_RTMPPUSH_SENDCMD        "net_recv%d.url=%s\n"
#define INTERFACE_SETSTREAM_OPEN_SENDCMD            "net_send%d.on=1\n"
#define INTERFACE_SETSTREAM_CLOSE_SENDCMD           "net_send%d.on=0\n"
#define INTERFACE_GETRECINFOLIST_SENDCMD            "<LFS_head><search>%d</search><dirname>%s</dirname><starttime>%s</starttime><endtime>%s</endtime></LFS_head>\n"
#define INTERFACE_SETADDOSD_SENDCMD                 "vid_enc%d.osd1.s_display=1\nvid_enc%d.osd1.type=0\nvid_enc%d.osd1.content=%s\n"
#define INTERFACE_SETDELOSD_SENDCMD                 "vid_enc%d.osd1.s_display=0\n"
#define INTERFACE_SETPUTENOTEFILE_SENDCMD            "<WTF_head><dirname>%s</dirname><filename>%s</filename><filesize>%d</filesize></WTF_head>"

// mps media Discipline work state 播放法庭纪律状态
typedef enum MPSMediaDisciplineStatus{
    eMPSDisciplineStatusStop = 0, //停止播放法庭纪律
    eMPSDisciplineStatusStart = 1, //正在播放法庭纪律
    eMPSDisciplinetatusSize
}MPSMediaDisciplineStatus;

// mps media decode work state 解码状态
typedef enum MPSMediaDecodeStatus{
    eMPSDecodeStatusStop = 0, //停止解码
    eMPSDecodeStatusStart= 1, //正在解码
    eMPSDecodetatusSize
}MPSMediaDecodeStatus;

// mps media work state
typedef enum MPSMediaStatus{
    eMPSStatusClose	= 0, //无此事件或已经结束
    eMPSStatusReady = 1, //准备就绪
    eMPSStatusRunning = 2, //正在工作
    eMPSStatusPaused = 3, //暂停
    eMPSStatusStopped = 4, //已经停止
    eMPSStatusSize
}MPSMediaStatus;

static string getMPSStatusStr(MPSMediaStatus & s){
    switch (s){
        case eMPSStatusClose:return "无此事件或已经结束";
        case eMPSStatusReady:return "准备就绪";
        case eMPSStatusRunning:return "正在工作";
        case eMPSStatusPaused:return "暂停";
        case eMPSStatusStopped:return "已经停止";
        default:return "无此状态";
    }
}
//---- mps media work state

// mps Operation response
typedef enum MPSOperationRes{
    eMPSResultOK  = 0, //成功无错误
    eMPSResultErrorGeneric  = 1, //普通错误，常见无法连接或传输出错
    eMPSErrorStatusInvalid  = 2, //状态无效
    eMPSErrorReadfile  = 3, //读取文件出错
    eMPSErrorDeletefile  = 4, //删除文件出错
    eMPSErrorException  = 5, //抛出异常，常见解析数据出错
    eMPSErrorReceiverCreate  = 6, //无法创建接收类，供调试用，正常情况不出现
    eMPSErrorWorkPackageCreate  = 7, //无法创建工作Package，供调试用，正常情况不出现
    eMPSErrorWorkfileSave  = 8, //无法保存工作文件，供调试用，正常情况不出现
    eMPSErrorPackagelistUpdate  = 9, //无法更新记录列表，供调试用，正常情况不出现
    eMPSErrorDspNotWork  = 10, //DSP没有正常工作
    eMPSErrorDspStatusInvalid  = 11, //DSP状态无效
    eMPSErrorDsp1Generic  = 12, //DSP1一般错误
    eMPSErrorDsp2Generic  = 13, //DSP2一般错误
    eMPSErrorNetworkMount  = 14, //无法挂载网络存储，常见存储服务异常
    eMPSErrorNetworkUnmount  = 15, //卸载网络存储出错
    eMPSErrorNetworkCreateDirs  = 16, //无法在网络存储上创建文件夹结构，常见没有写权限或者存储已满
    eMPSErrorLiverCreate  = 17, //无法创建直播类，常见网络地址设置错误
    eMPSErrorLocalfileCreate  = 18, //无法创建本地文件
    eMPSErrorNetworkfileCreate  = 19, //无法创建网络存储文件
    eMPSErrorNoBackupfile  = 20, //不存在备份配置文件，常见没有备份就恢复的情况
    eMPSErrorInitMP3Encoder  = 21, //mp3编码器初始化失败
    eMPSErrorNetworkInvalid  = 22, //网络存储在上次开庭过程中异常，必须重启
}MPSOperationRes;

#define MPS_OPERATION_UNKNOWN_RES_MSG   "未知错误"
static string getMPSOperationResStr(MPSOperationRes s){
    switch (s){
        case eMPSResultOK: return "成功无错误";
        case eMPSResultErrorGeneric: return "普通错误，常见无法连接或传输出错";
        case eMPSErrorStatusInvalid: return "状态无效，当前状态下不可使用此接口";
        case eMPSErrorReadfile: return "读取文件出错";
        case eMPSErrorDeletefile: return "删除文件出错";
        case eMPSErrorException: return "抛出异常，常见解析数据出错";
        case eMPSErrorReceiverCreate: return "无法创建接收类，供调试用，正常情况不出现";
        case eMPSErrorWorkPackageCreate: return "无法创建工作Package，供调试用，正常情况不出现";
        case eMPSErrorWorkfileSave: return "无法保存工作文件，供调试用，正常情况不出现";
        case eMPSErrorPackagelistUpdate: return "无法更新记录列表，供调试用，正常情况不出现";
        case eMPSErrorDspNotWork: return "DSP没有正常工作";
        case eMPSErrorDspStatusInvalid: return "DSP状态无效";
        case eMPSErrorDsp1Generic: return "DSP1一般错误";
        case eMPSErrorDsp2Generic: return "DSP2一般错误";
        case eMPSErrorNetworkMount: return "无法挂载网络存储，常见存储服务异常";
        case eMPSErrorNetworkUnmount: return "卸载网络存储出错";
        case eMPSErrorNetworkCreateDirs: return "无法在网络存储上创建文件夹结构，常见没有写权限或者存储已满";
        case eMPSErrorLiverCreate: return "无法创建直播类，常见网络地址设置错误";
        case eMPSErrorLocalfileCreate: return "无法创建本地文件";
        case eMPSErrorNetworkfileCreate: return "无法创建网络存储文件";
        case eMPSErrorNoBackupfile: return "不存在备份配置文件，常见没有备份就恢复的情况";
        case eMPSErrorInitMP3Encoder: return "mp3编码器初始化失败";
        case eMPSErrorNetworkInvalid: return "网络存储在上次开庭过程中异常，必须重启";
        default:return MPS_OPERATION_UNKNOWN_RES_MSG;
    }
}
//---- mps Operation response
#endif // MPSClient_H
