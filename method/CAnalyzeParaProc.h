#ifndef CANALYZEPARAPROC_H
#define CANALYZEPARAPROC_H
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

using namespace std;
using namespace SVS;

#define MAX_ARG_NUM 16
#define CMD_STR_ERR		-1
#define ARG_STR_ERR		-2
#define CMD_DISABLE		-3
#define XML_SAVE_ERR	-4
#define PROC_SUCCESS	0

typedef enum{
	CHNSYS_VID_CAP_OP = 0,
	CHNSYS_VID_ENC_OP,
	CHNSYS_VID_DEC_OP,
	CHNSYS_VID_OUT_OP,
	CHNSYS_VID_COMP_OP,
	CHNSYS_NET_RECV_OP,		//5
	CHNSYS_NET_SEND_OP,	
	CHNSYS_PCI_VID_IN_OP,
	CHNSYS_PCI_VID_OUT_OP,
	CHNSYS_PCI_AUD_IN_OP,
	CHNSYS_PCI_AUD_OUT_OP,	//10
	CHNSYS_AUD_CAP_OP,
	CHNSYS_AUD_ENC_OP,
	CHNSYS_AUD_DEC_OP,
	CHNSYS_AUD_OUT_OP,
	CHNSYS_HDMI_AUD_OUT_OP,	//15
	CHNSYS_H323H_OP,
	CHNSYS_SIP_OP,
	CHNSYS_REC_OP,
	CHNSYS_DEMUX_OP,
	CHNSYS_SCREENSHOT_OP,
	CHNSYS_ETH_OP,			//20
	CHNSYS_MOSAIC_OP,
	CHNSYS_NM_OP,
	CHNSYS_MN_OP,
	CHNSYS_CORE_GET,
	CHNSYS_VM_OP,			//25

	CHNSYS_DEV_NOCHECK_STA_FLAG,

	CHNSYS_SYSLOG_OP,
	CHNSYS_SYS_OP,
	CHNSYS_TDC_OP,
	CHNSYS_DEL_OP,			//30
	CHNSYS_RZK_OP,
	CHNSYS_AM_OP,	
	CHNSYS_DVC_GET,

	CHNSYS_LINKS_GET,
	CHNSYS_STATUS_GET,		//35
	CHNSYS_ENCRYPT_GET,
	CHNSYS_WEB_GET, //web

	CHNSYS_BACK_PIC_OP,
	CHNSYS_NTP_OP,
	CHNSYS_AUDIO_INFO__OP,	//40

	CHNSYS_RTMP_RECV_SEND_OP,
	CHNSYS_RTMP_RECV_RECV_OP,
	CHNSYS_RTMP_SEND_RECV_OP,
	CHNSYS_RTMP_SEND_SEND_OP,

	CHNSYS_DEV_NOCHECK_END_FLAG,
}OPERTE_G;

/* 保存多个指令的结构，字符串数组从0开始赋值*/  
typedef struct {  
	int number;        /*分割的字符串个数*/  
	char** string;        /*字符串数组*/  
}StringTab; 

typedef struct{
    int    RtspId;
    string RtspUrl;
    int    RtspMode;
    string   RtspProtol;

}CRtspNode, *PRtspNode;

class CAnalyzeParaProc
{
public:
    //转换String为需求的CJSON格式
    bool ConvertSTRING2CJSONGetHostConfig(CData &oResult, char *cResult, cJSON *network, cJSON *sysinfo, cJSON *diskinfo, cJSON *decnum);

    bool ConvertSTRING2CJSONGetHostDecInfo(CData &oResult, char *cResult, cJSON *rtspdec, cJSON *h323dec,cJSON *sipdec);

    bool ConvertSTRING2CJSONGetHostChnInfo(CData &oResult, char *cResult, cJSON* result, cJSON *node[], cJSON* _addressList, string Method, int ChnNum);

    bool ConvertSTRING2CJSONSetDecCtrl(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONSetOsdCtrl(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONSetPutNoteFileCtrl(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONSetRecCtrl(CData &oResult, char *cResult, cJSON *cRecStatus);

    bool ConvertSTRING2CJSONSetDiscipLineCtrl(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONGetDiscipLineCtrl(CData &oResult, char *cResult, cJSON *statusinfo);

    bool ConvertSTRING2CJSONSetStreamCtrl(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONSetPowerCtrl(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONSendConsoleCmd(CData &oResult, char *cResult);

    bool ConvertSTRING2CJSONGetRecCtrl(CData &oResult, char *cResult, cJSON *videofiles, cJSON *recresult, int StartIndex, int EndIndex);
	bool ConvertSTRING2CJSONGetRecordState(CData &oResult, char *cResult, cJSON *videofiles, cJSON *recresult);
	bool ConvertSTRING2CJSONGetDefRecChns(CData &oResult, char *cResult, int *DefRecChns);
	bool ConvertSTRING2CJSONGetParam(CData& oResult, char* cResult, cJSON* result, cJSON* ParamList,cJSON* node[], string Method, string &ip, int ParamNum);
	bool ConvertSTRING2CJSONGetWebParam(CData& oResult, char* cResult, cJSON* result, cJSON* ParamList,cJSON* node[], string Method, string &ip, int ParamNum);
	bool ConvertSTRING2CJSONGetCwpParam(CData& oResult, char* cResult, cJSON* result, cJSON* ParamList[],cJSON* node[], string Method, string &ip, int ParamNum);

private:

    /**
     * @brief ConvertParaProcessing 参数处理函数
     * @param cParaBuf
     * @param iLen
     */
    bool ConvertParaProcessing(char *cParaBuf, int iLen);

    /**
     * @brief StringSplit 分割字符串到数组中
     * @param string
     * @param split
     */
    StringTab StringSplit(char* string,const char* split);

    /**
     * @brief AnalyParaMessage 处理单条指令
     * @param string
     */
    int AnalyParaMessage(char *string);

    /**
     * @brief AnalyParaCmdSplitMessage 分割指令内容
     * @param string
     * @param top
     * @param low
     */
    void AnalyParaCmdSplitMessage(char *string, char **top, char **low);

    /**
     * @brief AnalyParaCmdSplitMessage 指令解析
     * @param top
     * @param low
     * @param string
     */
    int AnalyParaCmdExtracMessage(char *top, char *low, char *string);

    /**
     * @brief AnalyParaCmdCommandPartSplit 按'.'分割指令内容部分 
     * @param top
     * @param str
     */
    void AnalyParaCmdCommandPartSplit(char *top, char **str);

    /**
     * @brief AnalyParaCmdArgumentsPartSplit 根据需求。按‘，’分割参数内容部分
     * @param low
     * @param arg
     */
    void AnalyParaCmdArgumentsPartSplit(char *low, char **arg);

    /**
     * @brief AnalyParaCmdParseCommandHandle 网管协议指令处理
     * @param top
     * @param low
     * @param string
     */
    int AnalyParaCmdParseCommandHandle(char **str, char **arg, char *string);

    /**
     * @brief IncBuffer 字符串比较查找函数
     * @param pp
     */
    void IncBuffer(char **pp);

    /**
     * @brief SubBuffer 字符串比较查找函数
     * @param pp
     */
    void SubBuffer(unsigned char **pp);

    /**
     * @brief StringCmp 字符串比较查找函数
     * @param str1
     * @param str2
     */
    char* StringCmp( char *str1, const char *str2);

    /**
     * @brief IpAvalbCheck IP相关地址校验核对
     * @param ascii_buf
     */
    int IpAvalbCheck(char *ascii_buf);

    /**
     * @brief AnalyNetPara 解析网络接收参数
     * @param NetParaStr
     * @param NetParaArg
     */
    int AnalyNetRecvPara(int Id, char *NetParaStr, char *NetParaArg);

    /**
     * @brief AnalyNetH323Para 解析H323接收参数
     * @param NetParaStr
     * @param NetParaArg
     */
    int AnalyNetH323Para(int Id, char *NetParaStr, char **NetParaArg);

    /**
     * @brief AnalyNetChnSendPara 解析ChnSend接收参数
     * @param NetParaStr
     * @param NetParaArg
     */
    int AnalyNetChnSendPara(int Id, char *NetParaStr, char *NetParaArg);

    /**
     * @brief AnalyGetRecPara 解析ChnSend接收参数
     * @param cParaBuf
     * @param iLen
     */
    int AnalyGetRecPara(char *cParaBuf, int iLen);

    /**
     * @brief AnalyGetRecPara 解析ChnSend接收参数
     * @param cParaBuf
     * @param iLen
     */
    int AnalyGetRecParaSearch(char *cParaBuf, char *cDealBuf, char *cStartXml, char *cEndXml, int *iOffsetLen);
private:
    cJSON *_network;
    cJSON *_sysinfo;
    cJSON *_diskinfo;
    cJSON *_decnum;

    cJSON *_rtspdec;
    cJSON *_h323dec;
	cJSON *_sipdec;

    cJSON *_channal;
    cJSON *_statusinfo;

    cJSON *cArray;
	cJSON *h323cArray;
	cJSON *sipcArray;

    cJSON *_cRecStatus;

    cJSON *_videofiles;
    cJSON *_recresult;
	
	cJSON* _result;
	cJSON* _ParamList;
	cJSON* _ParamKnod;
	cJSON **_ParamArry;
	cJSON **_PArry;
	string _Param;
	string CMethod;
    string _ip;//ip地址
    int _port;//端口号
    int *_arry;
	int Param;
	int FileStartIndex;
	int FileEndIndex;
};

#endif // CANALYZEPARAPROC_H
