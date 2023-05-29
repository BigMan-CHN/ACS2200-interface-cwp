#include "CGetHostDecInfo.h"
#include <boost/lexical_cast.hpp>

CGetHostDecInfo::CGetHostDecInfo(string ip, int port, int timeOut)
    :_result(cJSON_CreateObject())
    ,_rtspdec(cJSON_CreateArray())
    ,_h323dec(cJSON_CreateArray())
    ,_sipdec(cJSON_CreateArray())
    ,_ip(ip)
    ,_port(port)
    ,_timeOut(timeOut)
    ,_client(new MPSClient(ip,port,timeOut))
    ,_AnalyParas()
{

}

bool CGetHostDecInfo::getDecConfig(int DecId,CData &oResult, char *cResult)
{
    mLogDebug("run getDecConfig(...)");
    //获取状态

    //add fwb 20201104
    int  i = 0;
    int  itmplen   = 0;
    char cDecTmpbuf[128] = {0};
    char cDecCmd[1024]   = {0};
	 memset(cDecCmd, 0, sizeof(1024));
	
    sprintf(cDecCmd,INTERFACE_GETHOSTDECRTSP_SENDCMD, DecId+1);

#if 0
    for (i = 1; i < RtspNum + 1; i++)
    {
        sprintf(cDecTmpbuf,INTERFACE_GETHOSTDECRTSP_SENDCMD,i,i,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, RtspNum, cDecTmpbuf);
        memcpy(cDecCmd + itmplen, cDecTmpbuf, strlen(cDecTmpbuf));
        itmplen += strlen(cDecTmpbuf);
    }
    for (i = 1; i < H323Num + 1; i++)
    {
        sprintf(cDecTmpbuf,INTERFACE_GETHOSTDECH323_SENDCMD,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, H323Num, cDecTmpbuf);
        memcpy(cDecCmd + itmplen, cDecTmpbuf, strlen(cDecTmpbuf));
        itmplen += strlen(cDecTmpbuf);
    }
    //printf("len %d \n%s", strlen(cDecCmd), cDecCmd);
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cDecCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 2; //获取参数指令（GET）
    cHeadCmd[2] = strlen(cDecCmd) >> 8;  
    cHeadCmd[3] = strlen(cDecCmd) & 0xff;

    memcpy(cCmdSend, cHeadCmd, 4);
    memcpy(cCmdSend+4, cDecCmd, strlen(cDecCmd));

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->GetConfigNew(cCmdSend,cCmdLength,opResCode,oResult,cResult);
    if(resCode != eResponseCodeSuccess){
        mLogError("GetConfig(...) error:"<<resCode);
        return false;
    }

    return true;
}

bool CGetHostDecInfo::getH323DecConfig(int DecId,CData &oResult, char *cResult)
{
    mLogDebug("run getDecConfig(...)");
    //获取状态

    //add fwb 20201104
    int  i = 0;
    int  itmplen   = 0;
    char cDecTmpbuf[128] = {0};
    char cDecCmd[1024]   = {0};

	 memset(cDecCmd, 0, sizeof(1024)); 
    sprintf(cDecCmd,INTERFACE_GETHOSTDECH323_SENDCMD, DecId+1);

#if 0
    for (i = 1; i < RtspNum + 1; i++)
    {
        sprintf(cDecTmpbuf,INTERFACE_GETHOSTDECRTSP_SENDCMD,i,i,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, RtspNum, cDecTmpbuf);
        memcpy(cDecCmd + itmplen, cDecTmpbuf, strlen(cDecTmpbuf));
        itmplen += strlen(cDecTmpbuf);
    }
    for (i = 1; i < H323Num + 1; i++)
    {
        sprintf(cDecTmpbuf,INTERFACE_GETHOSTDECH323_SENDCMD,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, H323Num, cDecTmpbuf);
        memcpy(cDecCmd + itmplen, cDecTmpbuf, strlen(cDecTmpbuf));
        itmplen += strlen(cDecTmpbuf);
    }
    //printf("len %d \n%s", strlen(cDecCmd), cDecCmd);
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cDecCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 2; //获取参数指令（GET）
    cHeadCmd[2] = strlen(cDecCmd) >> 8;  
    cHeadCmd[3] = strlen(cDecCmd) & 0xff;

    memcpy(cCmdSend, cHeadCmd, 4);
    memcpy(cCmdSend+4, cDecCmd, strlen(cDecCmd));

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->GetConfigNew(cCmdSend,cCmdLength,opResCode,oResult,cResult);
    if(resCode != eResponseCodeSuccess){
        mLogError("GetConfig(...) error:"<<resCode);
        return false;
    }

    return true;
}

bool CGetHostDecInfo::getSIPDecConfig(int DecId,CData &oResult, char *cResult)
{
    mLogDebug("run getDecConfig(...)");
    //获取状态

    //add fwb 20201104
    int  i = 0;
    int  itmplen   = 0;
    char cDecTmpbuf[128] = {0};
    char cDecCmd[1024]   = {0};


    sprintf(cDecCmd,INTERFACE_GETHOSTDECSIP_SENDCMD, DecId+1);

#if 0
    for (i = 1; i < RtspNum + 1; i++)
    {
        sprintf(cDecTmpbuf,INTERFACE_GETHOSTDECRTSP_SENDCMD,i,i,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, RtspNum, cDecTmpbuf);
        memcpy(cDecCmd + itmplen, cDecTmpbuf, strlen(cDecTmpbuf));
        itmplen += strlen(cDecTmpbuf);
    }
    for (i = 1; i < H323Num + 1; i++)
    {
        sprintf(cDecTmpbuf,INTERFACE_GETHOSTDECH323_SENDCMD,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, H323Num, cDecTmpbuf);
        memcpy(cDecCmd + itmplen, cDecTmpbuf, strlen(cDecTmpbuf));
        itmplen += strlen(cDecTmpbuf);
    }
    //printf("len %d \n%s", strlen(cDecCmd), cDecCmd);
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cDecCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 2; //获取参数指令（GET）
    cHeadCmd[2] = strlen(cDecCmd) >> 8;  
    cHeadCmd[3] = strlen(cDecCmd) & 0xff;

    memcpy(cCmdSend, cHeadCmd, 4);
    memcpy(cCmdSend+4, cDecCmd, strlen(cDecCmd));

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->GetConfigNew(cCmdSend,cCmdLength,opResCode,oResult,cResult);
    if(resCode != eResponseCodeSuccess){
        mLogError("GetConfig(...) error:"<<resCode);
        return false;
    }

    return true;
}

bool CGetHostDecInfo::ComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    if(_rtspdec == NULL){
        mLogWarn("cJSON network == NULL.");
        return false;
    }
    if(_h323dec == NULL){
        mLogWarn("cJSON channels == NULL.");
        return false;
    }
	if(_sipdec == NULL){
        mLogWarn("cJSON channels == NULL.");
        return false;
    }

    //result中添加节点
    //cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_RTSPDECNUM,_rtspdec);
    //cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_H323DECNUM,_h323dec);
	//cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_SIPDECNUM,_sipdec);

    return true;
}

string CGetHostDecInfo::ComposeResult()
{
    cJSON * result = cJSON_CreateObject();
    if(ComposeResult(result) == false){
        cJSON_Delete(result);
        return "";
    }else{
        char *cRes = cJSON_Print(_result);
        string res = cRes;
        cJSON_Delete(result);
        return res;
    }
}

InterfaceResCode CGetHostDecInfo::GetHostDecInfo(string &sResult,int DecId)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[8192] = {0};
	memset(cResult, 0, 8192);
    //printf("GetHostDecInfo RtspNum %d H323Num %d\n", RtspNum, H323Num);
#if 1
    if(getDecConfig(DecId, oResult, cResult) == false){
        mLogError("Failed to run  getMPSConfig(...)");
        return eInterfaceResCodeError;
    }
#endif 

    //getDecConfig(RtspNum, H323Num, oResult, cResult);
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("GetHostDecInfo\n");
    for (int i = 0; i < iRecvLength; i++)
    {
	    if (i < 4)
	    {
		    printf("%d", cResult[i]);
	    }
	    else 
	    {
		    printf("%c", cResult[i]);
	    }
    }
#endif 
    if( _AnalyParas.ConvertSTRING2CJSONGetHostDecInfo(oResult, cResult, _rtspdec, _h323dec, _sipdec) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }

	//msleep(200);
	memset(cResult, 0, 8192);
	if(getH323DecConfig(DecId, oResult, cResult) == false){
        mLogError("Failed to run  getMPSConfig(...)");
        return eInterfaceResCodeError;
    }
	if( _AnalyParas.ConvertSTRING2CJSONGetHostDecInfo(oResult, cResult, _rtspdec, _h323dec,_sipdec) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }	

	if(getSIPDecConfig(DecId, oResult, cResult) == false){
        mLogError("Failed to run  getMPSConfig(...)");
        return eInterfaceResCodeError;
    }
	if( _AnalyParas.ConvertSTRING2CJSONGetHostDecInfo(oResult, cResult, _rtspdec, _h323dec,_sipdec) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }	
	cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_RTSPDECNUM,_rtspdec);
    cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_H323DECNUM,_h323dec);
	cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_SIPDECNUM,_sipdec);
    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
InterfaceResCode CGetHostDecInfo::GetHostRTSPDecInfo(string &sResult,int DECID)
{
    //TODO
    mLogInfo("GetHostRTSPDecInfo...");
    CData oResult = SVSMAP();
    char cResult[8192] = {0};
	memset(cResult, 0, 8192);
    //printf("GetHostDecInfo RtspNum %d H323Num %d\n", RtspNum, H323Num);
#if 1
    if(getDecConfig(DECID, oResult, cResult) == false){
        mLogError("Failed to run  getDecConfig(...)");
        return eInterfaceResCodeError;
    }
#endif 

    //getDecConfig(RtspNum, H323Num, oResult, cResult);
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("GetHostDecInfo\n");
    for (int i = 0; i < iRecvLength; i++)
    {
	    if (i < 4)
	    {
		    printf("%d", cResult[i]);
	    }
	    else 
	    {
		    printf("%c", cResult[i]);
	    }
    }
#endif 
    if( _AnalyParas.ConvertSTRING2CJSONGetHostDecInfo(oResult, cResult, _rtspdec, _h323dec, _sipdec) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }	
	cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_RTSPDECNUM,_rtspdec);
    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
InterfaceResCode CGetHostDecInfo::GetHostH323DecInfo(string &sResult,int DECID)
{
    //TODO
    mLogInfo("GetHostH323DecInfo...");
    CData oResult = SVSMAP();
    char cResult[8192] = {0};
	memset(cResult, 0, 8192);
	
	if(getH323DecConfig(DECID, oResult, cResult) == false){
        mLogError("Failed to run  getH323DecConfig(...)");
        return eInterfaceResCodeError;
    }
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("GetHostDecInfo\n");
    for (int i = 0; i < iRecvLength; i++)
    {
	    if (i < 4)
	    {
		    printf("%d", cResult[i]);
	    }
	    else 
	    {
		    printf("%c", cResult[i]);
	    }
    }
#endif 


	if( _AnalyParas.ConvertSTRING2CJSONGetHostDecInfo(oResult, cResult, _rtspdec, _h323dec,_sipdec) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }	
	cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_H323DECNUM,_h323dec);
    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}

InterfaceResCode CGetHostDecInfo::GetHostSIPDecInfo(string &sResult,int DECID)
{
    //TODO
    mLogInfo("GetHostSIPDecInfo...");
    CData oResult = SVSMAP();
    char cResult[8192] = {0};
	memset(cResult, 0, 8192);
	
	if(getSIPDecConfig(DECID, oResult, cResult) == false){
        mLogError("Failed to run  getSIPDecConfig(...)");
        return eInterfaceResCodeError;
    }

#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("GetHostDecInfo\n");
    for (int i = 0; i < iRecvLength; i++)
    {
	    if (i < 4)
	    {
		    printf("%d", cResult[i]);
	    }
	    else 
	    {
		    printf("%c", cResult[i]);
	    }
    }
#endif 
	if( _AnalyParas.ConvertSTRING2CJSONGetHostDecInfo(oResult, cResult, _rtspdec, _h323dec,_sipdec) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }	
	cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_DE_SIPDECNUM,_sipdec);
    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}


