/********************************************************
* interfaceDefines.h
* 定义接口信息
*
* Copyright (c) 2019, Tyvis
* All rights reserved.
*
* @version		V1.00
* @author		es
* @date			2019-5-17
 *******************************************************/
#ifndef INTERFACEDEFINES_H
#define INTERFACEDEFINES_H

/********************************************************
 * headers
 *******************************************************/
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
#include <boost/format.hpp>

/********************************************************
 * lib headers
 *******************************************************/
#include <log.h>
#include <TransmitClient.h>
#include <xmlParser.h>
#include <LibXML.h>
#include <Server.h>

#include "MPSClientDefine.h"

using namespace std;
using namespace SVS;

//caseid max len
#define REQUEST_PARAMS_NODE_CASEID_LEN  100
/********************************************************
 * request json
 *******************************************************/
//test node
#define REQUEST_TEST_NODE_DEBUG "TEST_DEBUG" /*测试节点*/

// request node name
#define REQUEST_NODE_METHOD     "method"
#define REQUEST_NODE_PARAMS     "params"
#define REQUEST_NODE_CHANNELNUM "channelNum"
#define REQUEST_NODE_RTSPDECNUM "DECID"
#define REQUEST_NODE_H323DECNUM "H323DecNum"
#define REQUEST_NODE_CHNNUM     "ChannelNum"
#define REQUEST_NODE_RTMPNUM    "RtmpCliPushNum"


// request params node name
// method hostInit
#define REQUEST_PARAMS_NODE_CASEID     "caseid"
/********************************************************
 * response json
 *******************************************************/
// resposne node name
#define RESPONSE_NODE_ERROR      "error" /* string # 错误描述 */
#define RESPONSE_NODE_CODE       "code" /* int # 0：成功，!0：失败. */
#define RESPONSE_NODE_FLAG       "flag" /* string # 1：成功，0：失败. */
#define RESPONSE_NODE_RESULTS    "results" /* json # 返回信息 */

// resposne node flag
#define RESPONSE_NODE_FLAG_SUCCESS       "1" /* 成功 */
#define RESPONSE_NODE_FLAG_FAILED        "0" /* 失败 */


/********************************************************
 * method
 *******************************************************/
#define METHOD_HOST_INIT                    "hostInit"
#define METHOD_HOST_START                   "hostStart"
#define METHOD_HOST_PAUSE                   "hostPause"
#define METHOD_HOST_RESUME                  "hostResume"
#define METHOD_HOST_STOP                    "hostStop"
#define METHOD_HOST_CLOSE                   "hostClose"
#define METHOD_HOST_STATUS                  "hostStatus"
#define METHOD_HOST_REBOOT                  "reboot"
#define METHOD_HOST_SHUTDOWN                "shutdown"
#define METHOD_HOST_SETPOINT                "setpoint"
#define METHOD_GET_CHANNEL_CONTENTS         "getChannelContents"
#define METHOD_GET_TASK_CONTENTS            "getTaskContents"
#define METHOD_SET_TASK_DELETE              "setTaskDelete"
#define METHOD_GET_SYS_CONFIG               "getSysConfig"
#define METHOD_GET_HOST_CONFIG              "GetHostConfig"
#define METHOD_GET_HOST_DECINFO             "GetHostDecInfo"
#define METHOD_GET_HOST_CHNINFO             "GetHostChnInfo"

#define METHOD_SET_START_OSD                "SetOSD"
#define METHOD_SET_STOP_OSD                 "DelOSD"

#define METHOD_SET_PUTNOTEFILE              "PutNoteFile"

#define METHOD_SET_START_DEC                "SetStartDec"
#define METHOD_SET_STOP_DEC                 "SetStopDec"
#define METHOD_SET_START_REC                "StartRecord"
#define METHOD_SET_STOP_REC                 "StopRecord"
#define METHOD_SET_TASKDEL_REC              "SetTaskDelete"
#define METHOD_SET_START_DISCIPLINE         "SetStartDiscipline"
#define METHOD_SET_STOP_DISCIPLINE          "SetStopDiscipline"
#define METHOD_SET_START_DISCIPLINE         "SetStartDiscipline"
#define METHOD_GET_STATUS_DISCIPLINE        "GetDiscipLineStatus"

#define METHOD_GET_INFOLIST_REC             "GetRecInfo"

#define METHOD_SET_RTMPPUSH_STREAM          "SetRtmpCliPush"
#define METHOD_SET_OPEN_STREAM              "SetOpenStream"
#define METHOD_SET_CLOSE_STREAM             "SetCloseStream"

#define METHOD_SET_CONTROL_POWER            "SetSysCmd"
#define METHOD_SEND_CONSOLE_CMD             "SetConsoleCmd"
#define METHOD_SEND_SERIAL_CMD              "SetSerialCmd"

#define METHOD_HOST_DEC_STATUS              "hostDecStatus"

#define METHOD_HOST_START_DISCIPLINE        "hostStartDiscipline"
#define METHOD_HOST_STOP_DISCIPLINE         "hostStopDiscipline"
#define METHOD_HOST_GET_DISCIPLINE_STATUS   "hostDiscipLineStatus"

/********************************************************
 * hostInit method & params & response
 *******************************************************/
#define HOSTNIT_PARAMS_CHANNELNUM           REQUEST_NODE_CHANNELNUM /*params*/
#define HOSTNIT_PARAMS_CASEID               "caseid" /*params*/

/********************************************************
 * hostStop method & params & response
 *******************************************************/
#define HOSTSTOP_PARAMS_CHANNELNUM           REQUEST_NODE_CHANNELNUM /*params*/
#define HOSTSTOP_PARAMS_TURBO                "turboMode" /*params*/

/********************************************************
 * setpoint method & params & response
 *******************************************************/
#define SETPOINT_PARAMS_CHANNELNUM       REQUEST_NODE_CHANNELNUM /*params*/
#define SETPOINT_RES_DURATION            "duration" /*response*/
#define SETPOINT_RES_FILEPATH            "filePath" /*response*/

/********************************************************
 * hostStatus method & params & response
 *******************************************************/
#define HOST_STATUS_PARAMS_CHANNELNUM       REQUEST_NODE_CHANNELNUM /*params*/
#define HOST_STATUS_RES_CH_STATUS           "channelStatus" /*response*/
#define HOST_STATUS_RES_CH_CASEID           "caseid" /*response*/
#define HOST_STATUS_RES_DISK_USED_PCT       "diskUsedPct" /*response*/
#define HOST_STATUS_RES_DISK_ALARM          "diskAlarm" /*response*/

/********************************************************
 * getChannelContents method & params & response
 *******************************************************/
#define GET_CHANNEL_CONTENTS_PARAMS_START_DATE          "startDate" /*params 开始时间*/
#define GET_CHANNEL_CONTENTS_PARAMS_END_DATE            "endDate" /*params 结束时间*/
#define GET_CHANNEL_CONTENTS_RES_CASETOTAL              "caseTotal" /*response 文件个数*/
#define GET_CHANNEL_CONTENTS_RES_CASELIST               "caseList" /*response 存放案件数组，包含以下节点videoFiles、caseid*/
#define GET_CHANNEL_CONTENTS_RES_CASEID                 "caseid" /*response 唯一的任务标识，案件ID*/
#define GET_CHANNEL_CONTENTS_RES_TITLE                  "title" /*response */
#define GET_CHANNEL_CONTENTS_RES_STATUS                 "status" /*response 工作状态。0代表未开始；1代表正在工作；2代表暂停；3代表结束；4代表关闭；5代表异常*/
#define GET_CHANNEL_CONTENTS_RES_ALLOWDELETE            "allowDelete" /*response 是否允许删除；0：不允许，1：允许*/
#define GET_CHANNEL_CONTENTS_RES_MONTH                  "month" /*response 录制年月*/
#define GET_CHANNEL_CONTENTS_RES_STARTTIME              "startTime" /*response 录制开始时间*/
#define GET_CHANNEL_CONTENTS_RES_ENDTIME                "endTime" /*response 录制结束时间*/
#define GET_CHANNEL_CONTENTS_RES_VIDEOFILE              "videoFiles" /*response 存放同一个案件下的文件数组，包含以下节点：caseid、filename、size、filePath、startTime、endTime、channelnum、channelDesc、ftpPath、vodurlrtsp、vodurlrtmp、filesort*/

/********************************************************
 * getTeskContents method & params & response
 *******************************************************/
#define GET_TESK_CONTENTS_PARAMS_CASEID       "caseid" /*params*/
#define GET_TESK_CONTENTS_RES_ALLOWDELETE     "allowDelete" /*response results- 是否允许删除 bool*/
#define GET_TESK_CONTENTS_RES_TOTAL           "total" /*response results- 获取的文件数量 int*/
#define GET_TESK_CONTENTS_RES_VIDEO_FILES     "videoFiles" /*response results- 获取的文件列表 table*/
#define GET_TESK_CONTENTS_RES_VF_CASEID       "caseid" /*response results-videoFiles- 文件对应的caseid string*/
#define GET_TESK_CONTENTS_RES_VF_FILENAME     "fileName" /*response results-videoFiles- 文件名称 string*/
#define GET_TESK_CONTENTS_RES_VF_SIZE         "size" /*response results-videoFiles- 文件大小 int */
#define GET_TESK_CONTENTS_RES_VF_FILEPATH     "filePath" /*response results-videoFiles- 文件在主机上的路径 string*/
#define GET_TESK_CONTENTS_RES_VF_STARTTIME    "startTime" /*response results-videoFiles- 文件开始时间(2016-07-05 15:07:01) string*/
#define GET_TESK_CONTENTS_RES_VF_ENDTIME      "endTime" /*response results-videoFiles- 文件结束时间(2016-07-05 15:09:01) string*/
#define GET_TESK_CONTENTS_RES_VF_CH_NUM       "channelNum" /*response results-videoFiles- 录制文件的通道号 int*/
#define GET_TESK_CONTENTS_RES_VF_CH_DESC      "channelDesc" /*response results-videoFiles- 录制文件的通道描述符 string*/
#define GET_TESK_CONTENTS_RES_VF_FTPPATH      "ftpPath" /*response results-videoFiles- 录制文件的ftp路径 string*/
#define GET_TESK_CONTENTS_RES_VF_VODURL_RTSP  "vodurlRtsp" /*response results-videoFiles-   string*/
#define GET_TESK_CONTENTS_RES_VF_VODURL_RTMP  "vodurlRtmp" /*response results-videoFiles-   string*/
#define GET_TESK_CONTENTS_RES_VF_FILESORT     "fileSort" /*response results-videoFiles- 文件序列号  string*/


/********************************************************
 * setOSD method & params & response
 *******************************************************/
#define SET_CONFIG_ADD_OSD_OSDMODE                "OsdMode" /*params*/
#define SET_CONFIG_ADD_OSD_CHANNELID              "ChannelID" /*params*/
#define SET_CONFIG_ADD_OSD_TITLE                  "Title" /*params*/
#define SET_CONFIG_DEL_OSD_OSDMODE                "OsdMode" /*params*/
#define SET_CONFIG_DEL_OSD_CHANNELID              "ChannelID" /*params*/

/********************************************************
 * PutNoteFile method & params & response
 *******************************************************/
#define SET_CONFIG_PUTNOTEFILE_TRIALID                "TrialId" /*params*/
#define SET_CONFIG_PUTNOTEFILE_CONTENT                "Content" /*params*/
#define SET_CONFIG_PUTNOTEFILE_FILENAME               "FileName" /*params*/
#define SET_CONFIG_PUTNOTEFILE_FILESIZE               "FileSIZE" /*params*/

/********************************************************
 * getHostConfig method & params & response
 *******************************************************/
#define GET_HOST_CONFIG_RES_SYSINFO              "SysInfo" /*response */
#define GET_HOST_CONFIG_RES_SYS_DEVTYPE          "Devtype" /*response */
#define GET_HOST_CONFIG_RES_SYS_HVER             "HVer" /*response */
#define GET_HOST_CONFIG_RES_SYS_SVER             "SVer" /*response */
#define GET_HOST_CONFIG_RES_SYS_SN               "SN" /*response */
#define GET_HOST_CONFIG_RES_SYS_CHANNELNUM       "ChannelNum" /*response */

#define GET_HOST_CONFIG_RES_NETWORK             "NetInfo" /*response */
#define GET_HOST_CONFIG_RES_NW_IP               "IP" /*response */
#define GET_HOST_CONFIG_RES_NW_GATEWAY          "Gateway" /*response */
#define GET_HOST_CONFIG_RES_NW_NETMASK          "Netmask" /*response */

#define GET_HOST_CONFIG_RES_DISKINFO            "DiskInfo" /*response */
#define GET_HOST_CONFIG_RES_DI_TOTALSIZE        "TOTALSIZE" /*response */
#define GET_HOST_CONFIG_RES_DI_FREESIZE         "FreeSize" /*response */
#define GET_HOST_CONFIG_RES_DI_AUTODELSIZE      "AutoDelSize" /*response */

#define GET_HOST_CONFIG_RES_DECNUM             "NumInfo" /*response */
#define GET_HOST_CONFIG_RES_DE_RTSPDECNUM      "RTSPDecNum" /*response */
#define GET_HOST_CONFIG_RES_DE_DECID           "DECID"/*response */
#define GET_HOST_CONFIG_RES_DE_DECSTA          "DecStatus"/*response */
#define GET_HOST_CONFIG_RES_DE_DECURL          "DecUrl"/*response */
#define GET_HOST_CONFIG_RES_DE_DECMODE         "DecMode"/*response */


#define GET_HOST_CONFIG_RES_CHN                 "Channel" /*response */
#define GET_HOST_CONFIG_RES_CH_CHANNELNUM       "ChannelNum"/*response */
#define GET_HOST_CONFIG_RES_CH_RTMPCLIPUSHNUM   "RtmpCliPushNum"/*response */
#define GET_HOST_CONFIG_RES_CH_NCHNID           "ChannelID"/*response */
#define GET_HOST_CONFIG_RES_CH_NCHNNAME         "ChannelName"/*response */
#define GET_HOST_CONFIG_RES_CH_NCHNSTA          "ChannelStatus"/*response */
#define GET_HOST_CONFIG_RES_CH_NCHNURL          "Url"/*response */
#define GET_HOST_CONFIG_RES_CH_NCHNRECSTA       "RecStatus"/*response */
#define GET_HOST_CONFIG_RES_CH_NCHNRECTASKID    "RecTaskID"/*response */

#define GET_HOST_CONFIG_RES_DE_H323DECNUM      "H323DecNum" /*response */
#define GET_HOST_CONFIG_RES_DE_H323ID          "H323ID"/*response */
#define GET_HOST_CONFIG_RES_DE_H323STA         "H323Status"/*response */
#define GET_HOST_CONFIG_RES_DE_H323CALLIP      "H323CallIp"/*response */

#define GET_HOST_CONFIG_RES_DE_SIPDECNUM      "SipDecNum" /*response */
#define GET_HOST_CONFIG_RES_DE_SIPID          "SipID"/*response */
#define GET_HOST_CONFIG_RES_DE_SIPSTA         "SipStatus"/*response */
#define GET_HOST_CONFIG_RES_DE_SIPCALLIP      "SipCallIp"/*response */


#define GET_HOST_CONFIG_DISCIPLINE_STATUSINFO    "StatusInfo" /*response */
#define GET_HOST_CONFIG_DS_DISCIPLINESTATUS      "DisciplineStatus" /*response */

#define GET_HOST_CONFIG_RES_CHANNELS            "channels" /*response */
#define GET_HOST_CONFIG_RES_CH_CHANNELNUM       "channelNum" /*response */
#define GET_HOST_CONFIG_RES_CH_CHANNELNAME      "channelName" /*response */
#define GET_HOST_CONFIG_RES_CH_CHANNELSTATUS    "channelStatus" /*response */
#define GET_HOST_CONFIG_RES_CH_CHANNELENABLE    "channelEnable" /*response */
#define GET_HOST_CONFIG_RES_CH_RTSPURL          "rtspUrl" /*response */
#define GET_HOST_CONFIG_RES_CH_RTSPENABLE       "rtspEnable" /*response */
#define GET_HOST_CONFIG_RES_CH_RTMPURL          "rtmpUrl" /*response */
#define GET_HOST_CONFIG_RES_CH_RTMPENABLE       "rtmpEnable" /*response */

#define GET_HOST_CONFIG_RES_CH_SERIALNUM           "SerialNum" /*response */

#define GET_REC_CONFIG_START_TASKID             "TaskID" /*response */
#define GET_REC_CONFIG_START_STATUS              "Status" /*response */

/********************************************************
 * SetSerialCmd method & params & response
 *******************************************************/
#define SEND_SERILAL_PARAMS_CMD                  "Cmd" /*params*/
#define SEND_SERILAL_PARAMS_SERIALID             "SerialID" /*params*/

/********************************************************
 * sendConsoleCmd method & params & response
 *******************************************************/
#define SEND_CONSOLE_PARAMS_CMD             "Cmd" /*params*/

/********************************************************
 * hostStartDec method & params & response
 *******************************************************/
#define HOST_START_DEC_PARAMS_CHANNEL           "channel" /*params*/
#define HOST_START_DEC_PARAMS_URL               "url" /*params*/
#define HOST_START_DEC_PARAMS_CACHE_TIME        "cacheTime" /*params*/
#define HOST_START_DEC_PARAMS_TCP_MODE          "tcpMode" /*params*/

/********************************************************
 * SetStartDec method & params & response
 *******************************************************/
#define SET_START_DEC_PARAMS_DECTYPE           "DecType" /*params*/
#define SET_START_DEC_PARAMS_CHANNEL           "DECID" /*params*/
#define SET_START_DEC_PARAMS_ADDR              "DecUrl" /*params*/
#define SET_START_DEC_PARAMS_CACHETIME         "CacheTime" /*params*/
#define SET_START_DEC_PARAMS_TCPMODE           "TcpMode" /*params*/

/********************************************************
 * SetStartDiscipline method & params & response
 *******************************************************/
#define SET_START_DISCIPLINE_PARAMS_LOOPFLAG           "LoopFlag" /*params*/
#define SET_START_DISCIPLINE_PARAMS_PLAYLIST           "PlayList" /*params*/

/********************************************************
 * StartRecord method & params & response
 *******************************************************/
#define SET_START_REC_PARAMS_RECMODE           "RecMode" /*params*/
#define SET_START_REC_PARAMS_CHNAME            "ChannelID" /*params*/
#define SET_START_REC_PARAMS_TASKID            "TaskID" /*params*/
#define SET_START_REC_PARAMS_DESRIPTOR         "Title" /*params*/

/********************************************************
 * GetRecordList method & params & response
 *******************************************************/
#define GET_INFOLIST_REC_PARAMS_GETMODE           "GetMode" /*params*/
#define GET_INFOLIST_REC_PARAMS_TASKID            "TaskID" /*params*/
#define GET_INFOLIST_REC_PARAMS_STARTTIME         "StartTime" /*params*/
#define GET_INFOLIST_REC_PARAMS_ENDTIME           "EndTime" /*params*/

#define GET_INFOLIST_RES_VIDEOFILE              "VideoFiles" /*response */
#define GET_INFOLIST_RES_ALLOWDELETE            "AllowDelete" /*response */
#define GET_INFOLIST_RES_TOTAL                  "Total" /*response */

#define GET_INFOLIST_RES_FILESORT               "FileSort" /*response */
#define GET_INFOLIST_RES_TASKID                 "TaskID" /*response */
#define GET_INFOLIST_RES_FILENAME               "FileName" /*response */
#define GET_INFOLIST_RES_SIZE                   "Size" /*response */
#define GET_INFOLIST_RES_FILEPATH               "FilePath" /*response */
#define GET_INFOLIST_RES_STARTTIME              "StartTime" /*response */
#define GET_INFOLIST_RES_ENDTIME                "EndTime" /*response */
#define GET_INFOLIST_RES_CHANNELNUM             "ChannelNum" /*response */
#define GET_INFOLIST_RES_CHANNELDESC            "ChannelDesc" /*response */
#define GET_INFOLIST_RES_FTPPATH                "FtpPath" /*response */
#define GET_INFOLIST_RES_FTPUSR                 "Ftpusr" /*response */
#define GET_INFOLIST_RES_FTPPASSWD              "Ftppasswd" /*response */
#define GET_INFOLIST_RES_VODURLRTSP             "VodurlRtsp" /*response */
#define GET_INFOLIST_RES_VODURLRTMP             "VodurlRtmp" /*response */

/********************************************************
 * SetRtmpCliPush method & params & response
 *******************************************************/
#define SET_START_REC_PARAMS_RTMPID           "RtmpID" /*params*/
#define SET_START_REC_PARAMS_RTMPADDR         "Addr" /*params*/
#define SET_START_REC_PARAMS_RTMPCHANNEL      "Channel" /*params*/

/********************************************************
 * SetOpenStream method & params & response
 *******************************************************/
#define SET_START_REC_PARAMS_OPENALLFLAG           "AllFlag" /*params*/
#define SET_START_REC_PARAMS_OPENCHANNELID         "ChannelID" /*params*/

/********************************************************
 * SetCloseStream method & params & response
 *******************************************************/
#define SET_START_REC_PARAMS_CLOSEALLFLAG           "AllFlag" /*params*/
#define SET_START_REC_PARAMS_CLOSECHANNELID         "ChannelID" /*params*/

/********************************************************
 * SetSysCmd method & params & response
 *******************************************************/
#define SET_START_POWER_PARAMS_CMD           "Cmd" /*params*/

/********************************************************
 * hostStopDec method & params & response
 *******************************************************/
#define HOST_STOP_DEC_PARAMS_CHANNEL            "channel" /*params*/
 
/********************************************************
 * hostDecStatus method & params & response
 *******************************************************/
#define HOST_DEC_STATUS_PARAMS_CHANNEL          "channel" /*params*/
#define HOST_DEC_STATUS_RES_DEC_STATUS          "decodeStatus" /*response */

/********************************************************
 * hostDecStatus method & params & response
 *******************************************************/
#define HOST_DEC_INFO_PARAMS_RTSP_CHANNEL REQUEST_NODE_RTSPDECNUM /*params*/
#define HOST_DEC_INFO_PARAMS_H323_CHANNEL REQUEST_NODE_H323DECNUM /*params*/

/********************************************************
 * hostChnStatus method & params & response
 *******************************************************/
#define HOST_DEC_INFO_PARAMS_CHN_CHANNEL  REQUEST_NODE_CHNNUM /*params*/
#define HOST_DEC_INFO_PARAMS_RTMP_CHANNEL REQUEST_NODE_RTMPNUM /*params*/

/********************************************************
 * hostDisciplineStatus method & params & response
 *******************************************************/
#define HOST_GET_DISCIPLINE_STATUS_RES_DCPL_STATUS          "disciplineStatus" /*response*/

/********************************************************
 * typedef
 *******************************************************/
// channel status
typedef enum CHStatus{
    eCHStatusClose	= 0, //空闲 无直播流 无录制
    eCHStatusReady = 1, //有直播流 无录制
    eCHStatusRunning = 2, //录制中 有直播流
//    eCHStatusPaused = 3, //暂停录制 有直播流
    eCHStatusStopped = 3, //已经停止录制 有直播流
    eCHStatusSize
}CHStatus;

static string getCHStatusStr(CHStatus & s){
    switch (s){
        case eCHStatusClose:return "空闲,无直播流,无录制";
        case eCHStatusReady:return "有直播流,无录制";
        case eCHStatusRunning:return "录制中,有直播流";
//        case eCHStatusPaused:return "暂停录制,有直播流";
        case eCHStatusStopped:return "已经停止录制,有直播流";
        default:return "无此状态";
    }
}

static CHStatus CovertMediaStatus(MPSMediaStatus &s){
    switch (s){
        case eMPSStatusClose:return eCHStatusClose;//"无此事件或已经结束";
        case eMPSStatusReady:return eCHStatusReady;//"准备就绪";
        case eMPSStatusRunning:return eCHStatusRunning;//"正在工作";
//        case eMPSStatusPaused:return eCHStatusPaused;//"暂停";
                case eMPSStatusPaused:return eCHStatusSize;//"暂停";
        case eMPSStatusStopped:return eCHStatusStopped;//"已经停止";
        default:return eCHStatusSize;//"无此状态";
    }
}

//---- channel status

// 自定义服务反馈给客户端的消息code

typedef enum InterfaceResCode
{
    eInterfaceResCodeSuccess = 0,                   // 成功
    eInterfaceResCodeError = 111,                   // 出错

    eInterfaceResCodeRequestError = 400,            // 错误请求
    eInterfaceResCodeReqNoMethod = 401,             // 不存在此方法
    eInterfaceResCodeRequErrorParam = 402,          // 缺少参数或参数类型不正确

    eInterfaceResCodeErrorLocal = 500,              // 服务器错误
    eInterfaceResCodeErrorLocalDataConvert = 501,   // 本地数据转换出错
    eInterfaceResCodeErrorLocalStatus = 502,        // 服务器错误工作状态
    eInterfaceResCodeErrorTransmit = 504,           // 请求上游服务器出错
    eInterfaceResCodeErrorNoConnected = 505,        // 尚没有连接到上游服务器
    eInterfaceResCodeErrorTransmitTimeOut = 506,	// 请求上游服务器超时
    eInterfaceResCodeErrorSend = 507,               // 发送数据到上游服务器出错
    eInterfaceResCodeErrorRecv = 508,				// 接收上游服务器数据出错
    eInterfaceResCodeErrorTransmitNoModule= 511,    // 请求上游服务器,不存在此模块
    eInterfaceResCodeErrorTransmitNoMethod = 512,   // 请求上游服务器,不存在此方法

    eInterfaceResCodeErrorMPS = 600,                // 上游服务器(MPS)错误
    eInterfaceResCodeErrorMAX = 700,                //
} InterfaceResCode;

#define INTERFACERES_UNKNOWN_ERROR_MSG  "未知错误"
static string GetInterfaceResError(InterfaceResCode e)
{
    boost::format fmter("%1%,code:%2%");
    if( e == eInterfaceResCodeSuccess ){
        fmter%"成功无错误"%e;
    }else if( eInterfaceResCodeSuccess < e && e < eInterfaceResCodeError){
        //(100,111) 未归类基本错误
        switch(e){
        case eInterfaceResCodeSuccess:
            fmter%"成功无错误"%eInterfaceResCodeSuccess;//return "成功无错误";
            break;
        default:
            fmter%INTERFACERES_UNKNOWN_ERROR_MSG%e;//return "未知错误,code:(100,111)";
            break;
        }
    }else if( eInterfaceResCodeError <= e && e < eInterfaceResCodeRequestError){
        //[111,400) 未归类错误
        switch(e){
        case eInterfaceResCodeSuccess:
            fmter%"成功无错误"%e;//return "成功无错误";
            break;
        case eInterfaceResCodeError:
            fmter%"错误"%e;//return "错误,code:111";
            break;
        default:
            fmter%INTERFACERES_UNKNOWN_ERROR_MSG%e;//return "未知错误,code:[111,400)";
            break;
        }
    }else if( eInterfaceResCodeRequestError <= e && e < eInterfaceResCodeErrorLocal){
        //[400,500) 请求错误
        switch(e){
        case eInterfaceResCodeRequestError:
            fmter%"错误请求"%e;//return "错误请求";
            break;
        case eInterfaceResCodeReqNoMethod:
            fmter%"不存在此方法"%e;//return "不存在此方法";
            break;
        case eInterfaceResCodeRequErrorParam:
            fmter%"缺少参数或参数类型不正确"%e;//return "缺少参数或参数类型不正确";
            break;
        default:
            fmter%INTERFACERES_UNKNOWN_ERROR_MSG%e;//return "未知错误,code:[400,500)";
            break;
        }
    }else if( eInterfaceResCodeErrorLocal <= e && e < eInterfaceResCodeErrorMPS){
        //[500,600) 本地服务器错误
        switch(e){
        case eInterfaceResCodeErrorLocal:
            fmter%"服务器错误"%e;//return "服务器错误";
            break;
        case eInterfaceResCodeErrorLocalDataConvert:
            fmter%"服务器数据转换出错"%e;//return "服务器数据转换出错";
            break;
        case eInterfaceResCodeErrorLocalStatus:
            fmter%"服务器错误工作状态"%e;//return "服务器错误工作状态";
            break;
        case eInterfaceResCodeErrorTransmit:
            fmter%"请求上游服务器出错"%e;//return "请求上游服务器出错";
            break;
        case eInterfaceResCodeErrorNoConnected:
            fmter%"尚没有连接到上游服务器"%e;//return "尚没有连接到上游服务器";
            break;
        case eInterfaceResCodeErrorTransmitTimeOut:
            fmter%"请求上游服务器超时"%e;//return "请求上游服务器超时";
            break;
        case eInterfaceResCodeErrorSend:
            fmter%"发送数据到上游服务器出错"%e;//return "发送数据到上游服务器出错";
            break;
        case eInterfaceResCodeErrorRecv:
            fmter%"接收上游服务器数据出错"%e;//return "接收上游服务器数据出错";
            break;
        case eInterfaceResCodeErrorTransmitNoModule:
            fmter%"请求上游服务器,不存在此模块"%e;//return "请求上游服务器,不存在此模块";
            break;
        case eInterfaceResCodeErrorTransmitNoMethod:
            fmter%"请求上游服务器,不存在此方法"%e;//return "请求上游服务器,不存在此方法";
            break;
        default:
            fmter%INTERFACERES_UNKNOWN_ERROR_MSG%e;//return "未知错误,code:[500,600)";
            break;
        }
    }else if( eInterfaceResCodeErrorMPS <= e && e < eInterfaceResCodeErrorMAX){
        //[600,700) 上游服务器（MPS）错误
        int resCode = (int)e - (int)eInterfaceResCodeErrorMPS;
        string resH = "上游服务器(MPS)-";
        string resMsg;
        //获取mps错误信息
        if(e != eInterfaceResCodeErrorMPS){
            MPSOperationRes s= (MPSOperationRes)resCode;
            resMsg = getMPSOperationResStr(s);
        }else{
            resMsg = "错误";
        }
        fmter%(resH+resMsg)%e;
        /*
        switch(resCode){
        case 0: fmter%"上游服务器(MPS)错误"%e;//return "上游服务器(MPS)错误";
        case (int)(eMPSResultErrorGeneric): fmter%"上游服务器(MPS):普通错误，常见无法连接或传输出错"%e;//return "普通错误，常见无法连接或传输出错";
        case (int)(eMPSErrorStatusInvalid): fmter%"上游服务器(MPS):状态无效"%e;//return "状态无效";
        case (int)(eMPSErrorReadfile): fmter%"上游服务器(MPS):读取文件出错"%e;//return "读取文件出错";
        case (int)(eMPSErrorDeletefile): fmter%"上游服务器(MPS):删除文件出错"%e;//return "删除文件出错";
        case (int)(eMPSErrorException): fmter%"上游服务器(MPS):抛出异常，常见解析数据出错"%e;//return "抛出异常，常见解析数据出错";
        case (int)(eMPSErrorReceiverCreate): fmter%"上游服务器(MPS):无法创建接收类，供调试用，正常情况不出现"%e;//return "无法创建接收类，供调试用，正常情况不出现";
        case (int)(eMPSErrorWorkPackageCreate): fmter%"上游服务器(MPS):无法创建工作Package，供调试用，正常情况不出现"%e;//return "无法创建工作Package，供调试用，正常情况不出现";
        case (int)(eMPSErrorWorkfileSave): fmter%"上游服务器(MPS):无法保存工作文件，供调试用，正常情况不出现"%e;//return "无法保存工作文件，供调试用，正常情况不出现";
        case (int)(eMPSErrorPackagelistUpdate): fmter%"上游服务器(MPS):无法更新记录列表，供调试用，正常情况不出现"%e;//return "无法更新记录列表，供调试用，正常情况不出现";
        case (int)(eMPSErrorDspNotWork): fmter%"上游服务器(MPS):DSP没有正常工作"%e;//return "DSP没有正常工作";
        case (int)(eMPSErrorDspStatusInvalid): fmter%"上游服务器(MPS):DSP状态无效"%e;//return "DSP状态无效";
        case (int)(eMPSErrorDsp1Generic): fmter%"上游服务器(MPS):DSP1一般错误"%e;//return "DSP1一般错误";
        case (int)(eMPSErrorDsp2Generic): fmter%"上游服务器(MPS):DSP2一般错误"%e;//return "DSP2一般错误";
        case (int)(eMPSErrorNetworkMount): fmter%"上游服务器(MPS):无法挂载网络存储，常见存储服务异常"%e;//return "无法挂载网络存储，常见存储服务异常";
        case (int)(eMPSErrorNetworkUnmount): fmter%"上游服务器(MPS):卸载网络存储出错"%e;//return "卸载网络存储出错";
        case (int)(eMPSErrorNetworkCreateDirs): fmter%"上游服务器(MPS):无法在网络存储上创建文件夹结构，常见没有写权限或者存储已满"%e;//return "无法在网络存储上创建文件夹结构，常见没有写权限或者存储已满";
        case (int)(eMPSErrorLiverCreate): fmter%"上游服务器(MPS):无法创建直播类，常见网络地址设置错误"%e;//return "无法创建直播类，常见网络地址设置错误";
        case (int)(eMPSErrorLocalfileCreate): fmter%"上游服务器(MPS):无法创建本地文件"%e;//return "无法创建本地文件";
        case (int)(eMPSErrorNetworkfileCreate): fmter%"上游服务器(MPS):无法创建网络存储文件"%e;//return "无法创建网络存储文件";
        case (int)(eMPSErrorNoBackupfile): fmter%"上游服务器(MPS):不存在备份配置文件，常见没有备份就恢复的情况"%e;//return "不存在备份配置文件，常见没有备份就恢复的情况";
        case (int)(eMPSErrorInitMP3Encoder): fmter%"上游服务器(MPS):mp3编码器初始化失败"%e;//return "mp3编码器初始化失败";
        case (int)(eMPSErrorNetworkInvalid): fmter%"上游服务器(MPS):网络存储在上次开庭过程中异常，必须重启"%e;//return "网络存储在上次开庭过程中异常，必须重启";
        default: fmter%"上游服务器(MPS):未知错误"%e;//return "未知错误,code:[600,700)";
        }
        //*/
    }else{
        fmter%INTERFACERES_UNKNOWN_ERROR_MSG%e;
    }
    return fmter.str();
}

static InterfaceResCode CovertResponseCode(ResponseCode &e){
    switch (e){
    case eResponseCodeSuccess:return eInterfaceResCodeSuccess;
    case eResponseCodeNoModule:return eInterfaceResCodeErrorTransmitNoModule;
    case eResponseCodeNoMethod:return eInterfaceResCodeErrorTransmitNoMethod;
    case eResponseCodeNoConnected:return eInterfaceResCodeErrorNoConnected;
    case eResponseCodeErrorParamType:return eInterfaceResCodeErrorTransmit;
    case eResponseCodeErrorParam:return eInterfaceResCodeErrorTransmit;
    case eResponseCodeErrorServiceDataConvert:return eInterfaceResCodeErrorTransmit;
    case eResponseCodeErrorLocalDataConvert:return eInterfaceResCodeErrorLocalDataConvert;
    case eResponseCodeErrorSend:return eInterfaceResCodeErrorSend;
    case eResponseCodeErrorRecv:return eInterfaceResCodeErrorRecv;
    case eResponseCodeErrorTransmit:return eInterfaceResCodeErrorTransmit;
    default:return eInterfaceResCodeError;
    }
}

static InterfaceResCode CovertMPSOperationCode(MPSOperationRes &e){
    switch (e){
        case eMPSResultOK:
        return eInterfaceResCodeSuccess; //"成功无错误";
        case eMPSResultErrorGeneric: //return "普通错误，常见无法连接或传输出错";
        case eMPSErrorStatusInvalid: //return "状态无效";
        case eMPSErrorReadfile: //return "读取文件出错";
        case eMPSErrorDeletefile: //return "删除文件出错";
        case eMPSErrorException: //return "抛出异常，常见解析数据出错";
        case eMPSErrorReceiverCreate: //return "无法创建接收类，供调试用，正常情况不出现";
        case eMPSErrorWorkPackageCreate: //return "无法创建工作Package，供调试用，正常情况不出现";
        case eMPSErrorWorkfileSave: //return "无法保存工作文件，供调试用，正常情况不出现";
        case eMPSErrorPackagelistUpdate: //return "无法更新记录列表，供调试用，正常情况不出现";
        case eMPSErrorDspNotWork: //return "DSP没有正常工作";
        case eMPSErrorDspStatusInvalid: //return "DSP状态无效";
        case eMPSErrorDsp1Generic: //return "DSP1一般错误";
        case eMPSErrorDsp2Generic: //return "DSP2一般错误";
        case eMPSErrorNetworkMount: //return "无法挂载网络存储，常见存储服务异常";
        case eMPSErrorNetworkUnmount: //return "卸载网络存储出错";
        case eMPSErrorNetworkCreateDirs: //return "无法在网络存储上创建文件夹结构，常见没有写权限或者存储已满";
        case eMPSErrorLiverCreate: //return "无法创建直播类，常见网络地址设置错误";
        case eMPSErrorLocalfileCreate: //return "无法创建本地文件";
        case eMPSErrorNetworkfileCreate: //return "无法创建网络存储文件";
        case eMPSErrorNoBackupfile: //return "不存在备份配置文件，常见没有备份就恢复的情况";
        case eMPSErrorInitMP3Encoder: //return "mp3编码器初始化失败";
        case eMPSErrorNetworkInvalid: //return "网络存储在上次开庭过程中异常，必须重启";
        break;
        default:
        return eInterfaceResCodeErrorMPS; //"无此返回值";
    }
    int resCode = (int)eInterfaceResCodeErrorMPS +(int)e;
    return (InterfaceResCode)resCode;
}

//---- 自定义服务反馈给客户端的消息code

#endif // INTERFACEDEFINES_H

