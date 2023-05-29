#include "CGetHostChnInfo.h"
#include <boost/lexical_cast.hpp>

CGetHostChnInfo::CGetHostChnInfo(string ip, int port, int timeOut)
    :_result(cJSON_CreateObject())
    ,_channal(cJSON_CreateArray())
    ,_ip(ip)
    ,_port(port)
    ,_timeOut(timeOut)
    ,_client(new MPSClient(ip,port,timeOut))
    ,_AnalyParas()
{

}

bool CGetHostChnInfo::getChnConfig(int ChnNum,CData &oResult, char *cResult)
{
    mLogDebug("run getChnConfig(...)");
    //获取状态

    //add fwb 20201104
    //int  i = 0;
    //int  itmplen   = 0;
    //char cChnTmpbuf[512] = {0};
    char cChnCmd[4096]   = {0};

    //sprintf(cChnCmd,INTERFACE_GETHOSTCHNINFO_SENDCMD,ChnNum+1);
#if 1	
	int VidCapNum;
	char *ReqBody = NULL;
	//ChnNum大于13，返回所有（13组）通道信息
	if(ChnNum > 12)
	{
		
		sprintf(cChnCmd,"net_send%d.app_info\ndvc.allrecstatus\n", ChnNum);
		//sprintf(cChnCmd,INTERFACE_GETHOSTCHNINFO_SENDCMD, ChnNum);
		for(int i = 1; i <= 12; i++)
		{
			ReqBody = cChnCmd + strlen(cChnCmd);
			sprintf(ReqBody,"net_send%d.rec_current_status\nnet_send%d.rec_task_id\n", i, i);
		}
	}//ChnNum小于等于8，返回对应的通道信息
	else if(ChnNum <= 12)
	{

//		sprintf(cChnCmd,INTERFACE_GETHOSTCHNINFO_SENDCMD, ChnNum);
//		ReqBody = cChnCmd + strlen(cChnCmd);
//		sprintf(ReqBody,"net_send%d.rec_current_status\nnet_send%d.rec_task_id\ndvc.allrecstatus\n", ChnNum, ChnNum);
		
		sprintf(cChnCmd,"net_send%d.app_info\nnet_send%d.rec_current_status\nnet_send%d.rec_task_id\ndvc.allrecstatus\n", ChnNum, ChnNum, ChnNum);
	}
#endif
#if 0
    for (i = 1; i < RtspNum + 1; i++)
    {
        sprintf(cChnTmpbuf,INTERFACE_GETHOSTCHNINFO_SENDCMD,i,i,i,i,i);
        //printf("%d RtspNum %d ctmpbuff %s", i, RtspNum, cChnTmpbuf);
        memcpy(cChnCmd + itmplen, cChnTmpbuf, strlen(cChnTmpbuf));
        itmplen += strlen(cChnTmpbuf);
    }
    //printf("len %d \n%s", strlen(cDecCmd), cDecCmd);
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 2; //获取参数指令（GET）
    cHeadCmd[2] = strlen(cChnCmd) >> 8;  
    cHeadCmd[3] = strlen(cChnCmd) & 0xff;

    memcpy(cCmdSend, cHeadCmd, 4);
    memcpy(cCmdSend+4, cChnCmd, strlen(cChnCmd));

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->GetConfigNew(cCmdSend,cCmdLength,opResCode,oResult,cResult);
    if(resCode != eResponseCodeSuccess){
        mLogError("GetConfig(...) error:"<<resCode);
        return false;
    }

    return true;
}

bool CGetHostChnInfo::ComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    if(_channal == NULL){
        mLogWarn("cJSON network == NULL.");
        return false;
    }

    //result中添加节点
    cJSON_AddItemToObject(_result,GET_HOST_CONFIG_RES_CHN,_channal);
    return true;
}

string CGetHostChnInfo::ComposeResult()
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
bool CGetHostChnInfo::GetDefaultRecChnnels(CData &oResult, char *cResult)
{
		mLogDebug("run GetDefaultRecChnnels(...)");
		//获取状态
	
		//add fwb 20201110
		char cChnCmd[4096] = {0};
		char *ReqBody;
#if 1
		memset(cChnCmd, 0, 4096);
		for(int i = 1; i <= 13; i++)
		{
			ReqBody = cChnCmd + strlen(cChnCmd);
			sprintf(ReqBody, "net_send%d.rec_is_select\n", i);
		}

#endif 
	
		//add fwb 20201110
		char cCmdSend[1024] = {0};
		char cHeadCmd[4] = {0};
		//char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
		int  cCmdLength = 0;
		memset(cCmdSend, 0, sizeof(1024)); 
	
		cCmdLength = strlen(cChnCmd) + 4;
		cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
		cHeadCmd[1] = 2; //获取参数指令（GET）
		cHeadCmd[2] = strlen(cChnCmd) >> 8;  
		cHeadCmd[3] = strlen(cChnCmd) & 0xff;
	
		memcpy(cCmdSend, cHeadCmd, 4);
		memcpy(cCmdSend+4, cChnCmd, strlen(cChnCmd));
	
		MPSOperationRes opResCode = eMPSResultOK;
		ResponseCode resCode = _client->GetConfigNew(cCmdSend,cCmdLength,opResCode,oResult,cResult);
		if(resCode != eResponseCodeSuccess){
			mLogError("GetConfig(...) error:"<<resCode);
			return false;
		}
	
		return true;

}

InterfaceResCode CGetHostChnInfo::GetHostChnInfo(string &sResult,int ChnNum)
{
    //TODO
    mLogDebug("GetHostChnInfo...");
    CData oResult = SVSMAP();
    char cResult[8192] = {0};
	char Result[8192] = {0};
	cJSON* temList[15];
	string Method = "GetHostChnInfo";
//	ChnNum = ChnNum+1;//CWP默认通道从0开始，需要加1
    //printf("GetHostChnInfo ChnNum %d RtmpNum %d\n", ChnNum, RtmpNum);
#if 0
	if(GetDefaultRecChnnels( oResult, Result) == false)
	{
    	mLogError("Failed to run  GetDefaultRecChnnels(...)");
    	return eInterfaceResCodeError;
	}
	if( _AnalyParas.ConvertSTRING2CJSONGetDefRecChns(oResult, Result, DefRecChns) == false)
	{
    	mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
    	return eInterfaceResCodeError;
	}
	
#endif 

    if(getChnConfig(ChnNum, oResult, cResult) == false){
        mLogError("Failed to run  getChnConfig(...)");
        return eInterfaceResCodeError;
    }


   	for(int i = 1; i <= 13; i++)
	{//用于生成节点，存储解析后的参数
		temList[i] = cJSON_CreateObject();
	}
   

#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("getMPSConfig\n");
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

    if( _AnalyParas.ConvertSTRING2CJSONGetHostChnInfo(oResult, cResult, _result, temList, _channal, Method, ChnNum) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetHostDecInfo(...)");
        return eInterfaceResCodeError;
    }
	
	if(ChnNum > 12)
    {
   		for(int i = 1; i <= 12; i++)
		{
			cJSON *OldRecState = cJSON_GetObjectItem(temList[i],"OldRecState");
			cJSON *OldTaskID = cJSON_GetObjectItem(temList[i],"OldTaskID");
			cJSON *RecStatus  = cJSON_GetObjectItem(temList[i],"RecStatus");
			cJSON *RecTaskID = cJSON_GetObjectItem(temList[i],"RecTaskID");
#if 0
			if((DefRecChns[i] == 1)&&(OldRecState->valueint == 1))
			{
				cJSON_AddItemToObject(_result,"AllRecStatus",cJSON_CreateNumber(1));

			}
			else if((DefRecChns[i] == 1)&&(RecStatus->valueint == 2))
			{
				cJSON_AddItemToObject(_result,"AllRecStatus",cJSON_CreateNumber(1));
			}
#endif				
			if(OldRecState->valueint == 1)
			{
				cJSON_DeleteItemFromObject(temList[i],"RecStatus");
				cJSON_AddItemToObject(temList[i],"RecStatus",cJSON_CreateNumber(1));
				cJSON_DeleteItemFromObject(temList[i],"RecTaskID");
				cJSON_AddItemToObject(temList[i],"RecTaskID",cJSON_CreateString(OldTaskID->valuestring));
			}
			
			if((OldRecState->valueint == 0)&&(RecStatus->valueint != 2))
			{
				cJSON_DeleteItemFromObject(temList[i],"RecStatus");
				cJSON_AddItemToObject(temList[i],"RecStatus",cJSON_CreateNumber(0));
				cJSON_DeleteItemFromObject(temList[i],"RecTaskID");
				cJSON_AddItemToObject(temList[i],"RecTaskID",cJSON_CreateString(OldTaskID->valuestring));
			}
			cJSON_AddItemToArray(_channal, temList[i]);
		}
    }
	else
    {
//		switch(ChnNum)
//		{
//			case 1:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp1"));
//				break;
//			case 2:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp2"));
//				break;
//			case 3:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp3"));
//				break;
//			case 4:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp4"));
//				break;
//			case 5:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp5"));
//				break;
//			case 6:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp6"));
//				break;
//			case 7:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp7"));
//				break;
//			case 8:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp8"));
//				break;
//			case 9:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp8"));
//				break;
//			case 10:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp10"));
//				break;
//			case 11:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp11"));
//				break;
//			case 12:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp12"));
//				break;
//			case 13:
//				cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString("server_rtsp13"));
//				break;
//		}
		cJSON *OldRecState = cJSON_GetObjectItem(temList[ChnNum],"OldRecState");
		cJSON *OldTaskID = cJSON_GetObjectItem(temList[ChnNum],"OldTaskID");
		cJSON *RecStatus  = cJSON_GetObjectItem(temList[ChnNum],"RecStatus");
		cJSON *RecTaskID = cJSON_GetObjectItem(temList[ChnNum],"RecTaskID");
		
		if(OldRecState->valueint == 1)
		{
			cJSON_DeleteItemFromObject(temList[ChnNum],"RecStatus");
			cJSON_AddItemToObject(temList[ChnNum],"RecStatus",cJSON_CreateNumber(1));
			cJSON_DeleteItemFromObject(temList[ChnNum],"RecTaskID");
			cJSON_AddItemToObject(temList[ChnNum],"RecTaskID",cJSON_CreateString(OldTaskID->valuestring));
		}
		
		if((OldRecState->valueint == 0)&&(RecStatus->valueint != 2))
		{
			cJSON_DeleteItemFromObject(temList[ChnNum],"RecStatus");
			cJSON_AddItemToObject(temList[ChnNum],"RecStatus",cJSON_CreateNumber(0));
			cJSON_DeleteItemFromObject(temList[ChnNum],"RecTaskID");
			cJSON_AddItemToObject(temList[ChnNum],"RecTaskID",cJSON_CreateString(OldTaskID->valuestring));
		}

//		cJSON_AddItemToObject(temList[ChnNum],GET_HOST_CONFIG_RES_CH_NCHNID,cJSON_CreateNumber(ChnNum-1));	
		cJSON_AddItemToArray(_channal, temList[ChnNum]);
	}


    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}


