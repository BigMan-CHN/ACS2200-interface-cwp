#ifndef CSETRECCTRL_H
#define CSETRECCTRL_H
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
#include <cJSON.h>
#include <ctime>

#include "interfaceDefines.h"
#include "MPSClient.h"
#include "CAnalyzeParaProc.h"

#define INFO_LIST_MAX_BUFF  2*1024*1024

class CSetRecCtrl
{
public:
    CSetRecCtrl(string ip=MPS_IP, int port=MPS_PORT, int timeOut=MPS_TIMEOUT);

    /**
     * @brief SetRecCtrlStart 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode SetRecCtrlStart(string &sResult,int RecMode, string ChannelID, string TaskId, string Title);

    /**
     * @brief SetRecCtrlStop 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode SetRecCtrlStop(string &sResult,int RecMode, string TaskId, string ChannelID);

    /**
     * @brief GetRecCtrlInfoList 获取主机配置信息
     * @param GetMode
     * @param TaskId
     * @param StartTime
     * @param EndTime
     * @return true：成功，false：失败.
     */
    InterfaceResCode GetRecCtrlInfoList(string &sResult,int GetMode,string TaskId, string StartTime, string EndTime);

    /**
     * @brief SetRecCtrlTaskDel 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode SetRecCtrlTaskDel(string &sResult, string TaskId);
	    /**
     * @brief SetRecCtrlTaskDel 获取主机的网络配置信息和通道配置信息
     * @param sResult
     * @return 0：成功，!0：失败.
     */
    InterfaceResCode GetRecordState(string &sResult);
	InterfaceResCode PauseRecord(string &sResult,int RecMode, string TaskId, string ChannelID);
	InterfaceResCode ResumeRecord(string &sResult,int RecMode, string ChannelID, string TaskId, string Title);
	InterfaceResCode SetWebStartAutoRec(string &sResult, int StartRec);
	InterfaceResCode GetWebStartAutoRec(string &sResult);
	InterfaceResCode GetWebRcrvRecord(string &sResult);
	InterfaceResCode SetWebRcrvRecord(string &sResult,int RecOn);
	InterfaceResCode SetRecUploadState(string &sResult, string TaskID);
private:
    /**
     * @brief ComposeResult 合并结果
     * @param result
     * @return true：成功，false：失败.
     */
    bool ComposeResult(cJSON * result);
    /**
     * @brief ComposeResult 合并结果
     */
    string ComposeResult();
    /**
     * @brief ComposeResult 合并结果
     * @param result
     * @return true：成功，false：失败.
     */
    bool GetComposeResult(cJSON * result);
    /**
     * @brief ComposeResult 合并结果
     */
    string GetComposeResult();
    /**
     * @brief SetRecStart 获取主机配置信息
     * @param RtspNum
     * @param H323Num
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool SetRecStart(int RecMode, string ChannelID, string TaskId, string Title, CData &oResult, char *cResult);

    /**
     * @brief SetRecStop 获取主机配置信息
     * @param RtspNum
     * @param H323Num
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool SetRecStop(int RecMode, string TaskId, string ChannelID, CData &oResult, char *cResult);

    /**
     * @brief GetRecCtrlInfoList 获取主机配置信息
     * @param sResult
     * @param GetMode
     * @param TaskId
     * @param StartTime
     * @param EndTime
     * @return true：成功，false：失败.
     */
    bool GetRecInfoList(int GetMode,string TaskId, string StartTime, string EndTime, int StartIndex, int EndIndex, CData &oResult, char *cResult);
    /**
     * @brief SetRecTaskDel 获取主机配置信息
     * @param TaskId
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool SetRecTaskDel(string TaskId, CData &oResult, char *cResult);
	    /**
     * @brief SetRecTaskDel 获取主机配置信息
     * @param TaskId
     * @param oResult
     * @param cResult
     * @return true：成功，false：失败.
     */
    bool GetRecordStateInner(CData &oResult, char *cResult);
	bool PauseRecordInner(int RecMode, string TaskId, string ChannelID, CData &oResult, char *cResult);	
	bool ResumeRecordInner(int RecMode, string ChannelID, string TaskId, string Title, CData &oResult, char *cResult);
	bool GetDefaultRecChnnels(CData &oResult, char *cResult);
	
	bool SetWebStartAutoRecInner(CData& oResult, char* cResult, int StartRec);
	
	bool GetWebStartAutoRecInner(CData& oResult, char* cResult);
	
	bool GetWebRcrvRecordInner(CData &oResult, char *cResult);
	
	bool SetWebRcrvRecordInner(CData &oResult, char *cResult, int RecOn);
	
	bool SetRecUploadStateInner(CData &oResult, char *cResult, string TaskID);
private:
    //待控制设备ip,端口号,超时时间
    string _ip;
    int _port;
    int _timeOut;
	int DefRecChns[20];

    MPSClient *_client;
    CAnalyzeParaProc _AnalyParas;

    //用于存储结果
    cJSON *_result;
    cJSON *_VideoFiles;
};

#endif // CSETRECCTRL_H
