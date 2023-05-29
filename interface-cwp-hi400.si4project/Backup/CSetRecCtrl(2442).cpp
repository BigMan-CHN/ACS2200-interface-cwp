#include "CSetRecCtrl.h"
#include <boost/lexical_cast.hpp>

CSetRecCtrl::CSetRecCtrl(string ip, int port, int timeOut)
    :_result(cJSON_CreateObject())
    ,_VideoFiles(cJSON_CreateArray())
    ,_ip(ip)
    ,_port(port)
    ,_timeOut(timeOut)
    ,_client(new MPSClient(ip,port,timeOut))
    ,_AnalyParas()
{

}

bool CSetRecCtrl::SetRecStart(int RecMode,int ChannelID, string TaskId, string Title, CData &oResult, char *cResult)
{
    mLogDebug("run SetRecStart(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
	char *ReqBody;
	int flag = 0;
#if 1
	int ChnID,Chn;
	ChannelID = ChannelID+1;
	switch(ChannelID)
	{
		case 1:
			ChnID = 3;
			break;
		case 2:
			ChnID = 4;
			break;
		case 3:
			ChnID = 5;
			break;
		case 4:
			ChnID = 6;
			break;
		case 5:
			ChnID = 7;
			break;
		case 6:
			ChnID = 8;
			break;
		case 7:
			ChnID = 9;
			break;
		case 8:
			ChnID = 10;
			break;
		case 9:
			ChnID = 1;
			break;
		case 10:
			ChnID = 2;
			break;
		case 11:
			ChnID = 11;
			break;
		case 12:
			ChnID = 12;
			break;
		case 13:
			ChnID = 13;
			break;
	}

    if (RecMode == 0)
    {
		sprintf(cChnCmd,INTERFACE_SETRECORDSTART_DEFAULT_SENDCMD, 1, TaskId.c_str(), Title.c_str());
		
		for(int i = 1; i <= 13; i++)
		{
		mLogDebug("DefRecChns"<<i<<"="<<DefRecChns[i]);
			if((DefRecChns[i] == 1)&&(flag < 4))
			{
			
				switch(i)
				{
					case 1:
						Chn = 3;
						break;
					case 2:
						Chn = 4;
						break;
					case 3:
						Chn = 5;
						break;
					case 4:
						Chn = 6;
						break;
					case 5:
						Chn = 7;
						break;
					case 6:
						Chn = 8;
						break;
					case 7:
						Chn = 9;
						break;
					case 8:
						Chn = 10;
						break;
					case 9:
						Chn = 1;
						break;
					case 10:
						Chn = 2;
						break;
					case 11:
						Chn = 11;
						break;
					case 12:
						Chn = 12;
						break;
					case 13:
						Chn = 13;
						break;
				}
				ReqBody = cChnCmd + strlen(cChnCmd);
				sprintf(ReqBody, "net_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=%s\n", Chn, 1, Chn, TaskId.c_str());
				flag++;
				mLogDebug("############################SetRecStart Chn="<<Chn);
			}
		}
    }
    else if(RecMode == 1)
    {
        sprintf(cChnCmd,"rec.app_start=%d,%s,%s\nnet_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=%s\n", ChnID, TaskId.c_str(), Title.c_str(), ChnID, 1, ChnID, TaskId.c_str()); 
		//sprintf(cChnCmd,INTERFACE_SETRECORDSTART_SENDCMD, ChannelID+1, TaskId.c_str(), Title.c_str());
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
    cHeadCmd[1] = 3; //获取参数指令（GET）
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
bool CSetRecCtrl::ResumeRecordInner(int RecMode,int ChannelID, string TaskId, string Title, CData &oResult, char *cResult)
{
    mLogDebug("run SetRecStart(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
	char *ReqBody;
	int flag = 0;
#if 1
	int ChnID,Chn;
	ChannelID = ChannelID+1;
	switch(ChannelID)
	{
		case 1:
			ChnID = 3;
			break;
		case 2:
			ChnID = 4;
			break;
		case 3:
			ChnID = 5;
			break;
		case 4:
			ChnID = 6;
			break;
		case 5:
			ChnID = 7;
			break;
		case 6:
			ChnID = 8;
			break;
		case 7:
			ChnID = 9;
			break;
		case 8:
			ChnID = 10;
			break;
		case 9:
			ChnID = 1;
			break;
		case 10:
			ChnID = 2;
			break;
		case 11:
			ChnID = 11;
			break;
		case 12:
			ChnID = 12;
			break;
		case 13:
			ChnID = 13;
			break;
	}

    if (RecMode == 0)
    {
		sprintf(cChnCmd,INTERFACE_SETRECORDSTART_DEFAULT_SENDCMD, 1, TaskId.c_str(), Title.c_str());
		for(int i = 1; i <= 13; i++)
		{
			if((DefRecChns[i] == 1)&&(flag < 4))
			{
				switch(i)
				{
					case 1:
						Chn = 3;
						break;
					case 2:
						Chn = 4;
						break;
					case 3:
						Chn = 5;
						break;
					case 4:
						Chn = 6;
						break;
					case 5:
						Chn = 7;
						break;
					case 6:
						Chn = 8;
						break;
					case 7:
						Chn = 9;
						break;
					case 8:
						Chn = 10;
						break;
					case 9:
						Chn = 1;
						break;
					case 10:
						Chn = 2;
						break;
					case 11:
						Chn = 11;
						break;
					case 12:
						Chn = 12;
						break;
					case 13:
						Chn = 13;
						break;
				}
				ReqBody = cChnCmd + strlen(cChnCmd);
				sprintf(ReqBody, "net_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=%s\n", Chn, 1, Chn, TaskId.c_str());
				flag++;
				mLogDebug("############################ResumeRecordInner Chn="<<Chn);
			}
		}
    }
    else if(RecMode == 1)
    {
        sprintf(cChnCmd,"rec.app_start=%d,%s,%s\nnet_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=%s\n", ChnID, TaskId.c_str(), Title.c_str(), ChnID, 1, ChnID, TaskId.c_str()); 
		//sprintf(cChnCmd,INTERFACE_SETRECORDSTART_SENDCMD, ChannelID+1, TaskId.c_str(), Title.c_str());
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
    cHeadCmd[1] = 3; //获取参数指令（GET）
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

bool CSetRecCtrl::SetRecStop(int RecMode, string TaskId, int ChannelID, CData &oResult, char *cResult)
{
    mLogDebug("run getChnConfig(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
	char *ReqBody;
	int flag = 0;
	int ChnID,Chn;
#if 1
	ChannelID = ChannelID+1;
	switch(ChannelID)
	{
		case 1:
			ChnID = 3;
			break;
		case 2:
			ChnID = 4;
			break;
		case 3:
			ChnID = 5;
			break;
		case 4:
			ChnID = 6;
			break;
		case 5:
			ChnID = 7;
			break;
		case 6:
			ChnID = 8;
			break;
		case 7:
			ChnID = 9;
			break;
		case 8:
			ChnID = 10;
			break;
		case 9:
			ChnID = 1;
			break;
		case 10:
			ChnID = 2;
			break;
		case 11:
			ChnID = 11;
			break;
		case 12:
			ChnID = 12;
			break;
		case 13:
			ChnID = 13;
			break;
	}	

    if (RecMode == 0)
    {
        sprintf(cChnCmd,INTERFACE_SETRECORDSTOP_DEFAULT_SENDCMD, TaskId.c_str());
		for(int i = 1; i <= 13; i++)
		{
			if((DefRecChns[i] == 1)&&(flag < 4))
			{
				switch(i)
				{
					case 1:
						Chn = 3;
						break;
					case 2:
						Chn = 4;
						break;
					case 3:
						Chn = 5;
						break;
					case 4:
						Chn = 6;
						break;
					case 5:
						Chn = 7;
						break;
					case 6:
						Chn = 8;
						break;
					case 7:
						Chn = 9;
						break;
					case 8:
						Chn = 10;
						break;
					case 9:
						Chn = 1;
						break;
					case 10:
						Chn = 2;
						break;
					case 11:
						Chn = 11;
						break;
					case 12:
						Chn = 12;
						break;
					case 13:
						Chn = 13;
						break;
				}
				ReqBody = cChnCmd + strlen(cChnCmd);
				sprintf(ReqBody, "net_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=\n", Chn, 0, Chn);
				flag++;
				mLogDebug("############################SetRecStop Chn="<<Chn);
			}
		}
    }
    else if(RecMode == 1)
    {
            sprintf(cChnCmd,"rec.app_stop=%s\nnet_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=\n", TaskId.c_str(), ChnID, 0, ChnID);   
			//sprintf(cChnCmd,INTERFACE_SETRECORDSTOP_SENDCMD, TaskId.c_str()); 
    }
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（GET）
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

bool CSetRecCtrl::PauseRecordInner(int RecMode, string TaskId, int ChannelID, CData &oResult, char *cResult)
{
    mLogDebug("run getChnConfig(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
	char *ReqBody;
	int flag = 0;
#if 1
	int ChnID,Chn;
	ChannelID = ChannelID+1;
	switch(ChannelID)
	{
		case 1:
			ChnID = 3;
			break;
		case 2:
			ChnID = 4;
			break;
		case 3:
			ChnID = 5;
			break;
		case 4:
			ChnID = 6;
			break;
		case 5:
			ChnID = 7;
			break;
		case 6:
			ChnID = 8;
			break;
		case 7:
			ChnID = 9;
			break;
		case 8:
			ChnID = 10;
			break;
		case 9:
			ChnID = 1;
			break;
		case 10:
			ChnID = 2;
			break;
		case 11:
			ChnID = 11;
			break;
		case 12:
			ChnID = 12;
			break;
		case 13:
			ChnID = 13;
			break;
	}

    if (RecMode == 0)
    {
        sprintf(cChnCmd,INTERFACE_SETRECORDSTOP_DEFAULT_SENDCMD, TaskId.c_str());
		for(int i = 1; i <= 13; i++)
		{
			if((DefRecChns[i] == 1)&&(flag < 4))
			{
				switch(i)
				{
					case 1:
						Chn = 3;
						break;
					case 2:
						Chn = 4;
						break;
					case 3:
						Chn = 5;
						break;
					case 4:
						Chn = 6;
						break;
					case 5:
						Chn = 7;
						break;
					case 6:
						Chn = 8;
						break;
					case 7:
						Chn = 9;
						break;
					case 8:
						Chn = 10;
						break;
					case 9:
						Chn = 1;
						break;
					case 10:
						Chn = 2;
						break;
					case 11:
						Chn = 11;
						break;
					case 12:
						Chn = 12;
						break;
					case 13:
						Chn = 13;
						break;
				}
				ReqBody = cChnCmd + strlen(cChnCmd);
				sprintf(ReqBody, "net_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=%s\n", Chn, 2, Chn, TaskId.c_str());
				flag++;
				mLogDebug("############################PauseRecordInner Chn="<<Chn);
			}
		}
    }
    else if(RecMode == 1)
    {
            sprintf(cChnCmd,"rec.app_stop=%s\nnet_send%d.rec_current_status=%d\nnet_send%d.rec_task_id=%s\n", TaskId.c_str(), ChnID, 2, ChnID, TaskId.c_str());   
			//sprintf(cChnCmd,INTERFACE_SETRECORDSTOP_SENDCMD, TaskId.c_str()); 
    }
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（GET）
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

bool CSetRecCtrl::GetRecInfoList(int GetMode,string TaskId, string StartTime, string EndTime, int StartIndex, int EndIndex, CData &oResult, char *cResult)
{
    mLogDebug("run SetRecStart(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
#if 1
	sprintf(cChnCmd,"<LFS_head><search>%d</search><dirname>%s</dirname><starttime>%s</starttime><endtime>%s</endtime><startindex>%d</startindex><endindex>%d</endindex></LFS_head>\n", GetMode, TaskId.c_str(),StartTime.c_str(),EndTime.c_str(), StartIndex, EndIndex);
    //sprintf(cChnCmd,INTERFACE_GETRECINFOLIST_SENDCMD, GetMode, TaskId.c_str(),StartTime.c_str(),EndTime.c_str());
#endif 

    //add fwb 20201110
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 7; //获取参数指令（GET）
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

bool CSetRecCtrl::SetRecTaskDel(string TaskId, CData &oResult, char *cResult)
{
    mLogDebug("run getChnConfig(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
#if 1
    sprintf(cChnCmd,INTERFACE_SETRECODELETE_SENDCMD, TaskId.c_str());    
#endif 

    //add fwb 20201027
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（GET）
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

bool CSetRecCtrl::ComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    return true;
}

string CSetRecCtrl::ComposeResult()
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

bool CSetRecCtrl::GetComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    cJSON_AddItemToObject(_result, GET_INFOLIST_RES_VIDEOFILE, _VideoFiles);
    return true;
}

string CSetRecCtrl::GetComposeResult()
{
    cJSON * result = cJSON_CreateObject();
    if(GetComposeResult(result) == false){
        cJSON_Delete(result);
        return "";
    }else{
        char *cRes = cJSON_Print(_result);
        string res = cRes;
        cJSON_Delete(result);
        return res;
    }
}
bool CSetRecCtrl::GetDefaultRecChnnels(CData &oResult, char *cResult)
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

InterfaceResCode CSetRecCtrl::SetRecCtrlStart(string &sResult,int RecMode,int ChannelID, string TaskId, string Title)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
	char Result[4096] = {0};
    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
#if 1
	if(RecMode == 0)
	{
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
	}

    if(SetRecStart(RecMode, ChannelID, TaskId, Title, oResult, cResult) == false){
        mLogError("Failed to run  SetRecCtrlStart(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
    ;
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("SetRecCtrlStart\n");
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

#if 1
    if( _AnalyParas.ConvertSTRING2CJSONSetRecCtrl(oResult, cResult, _result) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}

InterfaceResCode CSetRecCtrl::ResumeRecord(string &sResult,int RecMode,int ChannelID, string TaskId, string Title)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
	char Result[4096] = {0};
    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
#if 1
	if(RecMode == 0)
	{
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
	}

    if(ResumeRecordInner(RecMode, ChannelID, TaskId, Title, oResult, cResult) == false){
        mLogError("Failed to run  SetRecCtrlStart(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
    ;
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("SetRecCtrlStart\n");
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

#if 1
    if( _AnalyParas.ConvertSTRING2CJSONSetRecCtrl(oResult, cResult, _result) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}

InterfaceResCode CSetRecCtrl::SetRecCtrlStop(string &sResult,int RecMode, string TaskId, int ChannelID)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
	char Result[4096] = {0};
	int i;
    //printf("SetRecCtrlStop RecMode %d ChnID %d TaskId %s\n", RecMode, ChnID, TaskId.c_str());
#if 1
	if(RecMode == 0)
	{
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
	}

    if(SetRecStop(RecMode, TaskId, ChannelID, oResult, cResult) == false){
        mLogError("Failed to run  SetRecStop(...)");
        return eInterfaceResCodeError;
    }
	if(cResult[4] == 0 && cResult[5] == 4){
		return eInterfaceResCodeError;
	}
//	 system("echo ""socketSendNew""> test.txt");
//	printf("SetRecCtrlStop : %s\n",cResult);
//	for(i = 0; i< 16; i++)
//		{
//		printf("cResult[%d]==%s\n ",i,cResult);
//	}
#endif 
    
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

#if 1
    if( _AnalyParas.ConvertSTRING2CJSONSetRecCtrl(oResult, cResult,_result) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
InterfaceResCode CSetRecCtrl::PauseRecord(string &sResult,int RecMode, string TaskId, int ChannelID)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
	char Result[4096] = {0};
	int i;
    //printf("SetRecCtrlStop RecMode %d ChnID %d TaskId %s\n", RecMode, ChnID, TaskId.c_str());
#if 1
	if(RecMode == 0)
	{
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
	}

    if(PauseRecordInner(RecMode, TaskId, ChannelID, oResult, cResult) == false){
        mLogError("Failed to run  SetRecStop(...)");
        return eInterfaceResCodeError;
    }
	if(cResult[4] == 0 && cResult[5] == 4){
		return eInterfaceResCodeError;
	}
//	 system("echo ""socketSendNew""> test.txt");
//	printf("SetRecCtrlStop : %s\n",cResult);
//	for(i = 0; i< 16; i++)
//		{
//		printf("cResult[%d]==%s\n ",i,cResult);
//	}
#endif 
    
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

#if 1
    if( _AnalyParas.ConvertSTRING2CJSONSetRecCtrl(oResult, cResult,_result) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}

InterfaceResCode CSetRecCtrl::GetRecCtrlInfoList(string &sResult,int GetMode,string TaskId, string StartTime, string EndTime)
{
    //TODO
    mLogInfo("GetRecCtrlInfoList...");
    CData oResult = SVSMAP();
    //char cResult[INFO_LIST_MAX_BUFF] = {0};
     char *cResult;
	cResult = (char*)malloc(INFO_LIST_MAX_BUFF);
    memset(cResult, 0, INFO_LIST_MAX_BUFF);
	int StartIndex = 1;
	int EndIndex = 1500;
    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
#if 1
    if(GetRecInfoList(GetMode, TaskId, StartTime, EndTime, StartIndex, EndIndex, oResult, cResult) == false){
        mLogError("Failed to run  SetRecCtrlStart(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
#if 0
    unsigned int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("GetRecCtrlInfoList %d\n", iRecvLength);
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

#if 1
    if( _AnalyParas.ConvertSTRING2CJSONGetRecCtrl(oResult, cResult, _VideoFiles, _result, StartIndex, EndIndex) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = GetComposeResult();
    return eInterfaceResCodeSuccess;
}

InterfaceResCode CSetRecCtrl::SetRecCtrlTaskDel(string &sResult, string TaskId)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
    //printf("SetRecCtrlTaskDel TaskId %s\n", TaskId.c_str());
#if 1
    if(SetRecTaskDel(TaskId, oResult, cResult) == false){
        mLogError("Failed to run  SetRecStop(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
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

#if 0
    if( _AnalyParas.ConvertSTRING2CJSONSetRecCtrl(oResult, cResult) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
bool CSetRecCtrl::GetRecordStateInner(CData &oResult, char *cResult)
{
		mLogDebug("run GetRecordStateInner(...)");
		//获取状态
	
		//add fwb 20201110
		char cChnCmd[4096] = {0};
#if 1
		sprintf(cChnCmd,"rec.rec_status_type\n");
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

InterfaceResCode CSetRecCtrl::GetRecordState(string &sResult)
{
    //TODO
    mLogInfo("GetRecordState...");
    CData oResult = SVSMAP();
    //char cResult[INFO_LIST_MAX_BUFF] = {0};
     char *cResult;
	cResult = (char*)malloc(INFO_LIST_MAX_BUFF);
    memset(cResult, 0, INFO_LIST_MAX_BUFF);
    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
#if 1
    if(GetRecordStateInner(oResult, cResult) == false){
        mLogError("Failed to run  SetRecCtrlStart(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
#if 0
    unsigned int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("GetRecCtrlInfoList %d\n", iRecvLength);
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

#if 1
    if( _AnalyParas.ConvertSTRING2CJSONGetRecordState(oResult, cResult, _VideoFiles, _result) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONGetRecCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
bool CSetRecCtrl::SetWebRcrvRecordInner(CData &oResult, char *cResult, int RecOn)
{
			mLogDebug("run SetWebRcrvRecordInner(...)");
			//获取状态
		
			
			char cChnCmd[4096] = {0};
#if 1
			sprintf(cChnCmd,"rec.close_court_rec_on=%d\n", RecOn);	 
#endif 
		
			
			char cCmdSend[1024] = {0};
			char cHeadCmd[4] = {0};
			//char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
			int  cCmdLength = 0;
			memset(cCmdSend, 0, sizeof(1024)); 
		
			cCmdLength = strlen(cChnCmd) + 4;
			cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
			cHeadCmd[1] = 3; //获取参数指令（GET）
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

InterfaceResCode CSetRecCtrl::SetWebRcrvRecord(string &sResult,int RecOn)
{
			//TODO
			mLogInfo("SetWebRcrvRecord...");
			CData oResult = SVSMAP();
			char cResult[4096] = {0};
			//printf("SetRecCtrlTaskDel TaskId %s\n", TaskId.c_str());
#if 1
			if(SetWebRcrvRecordInner(oResult, cResult, RecOn) == false){
				mLogError("Failed to run  GetWebRecSegModelInner(...)");
				return eInterfaceResCodeError;
			}
#endif 
			
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
		
#if 0
			if( _AnalyParas.ConvertSTRING2CJSONGetWebRecSegModel(oResult, cResult, _result) == false){
				mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
				return eInterfaceResCodeError;
			}
#endif 
		
			sResult = ComposeResult();
			cJSON_Delete(_result);
			return eInterfaceResCodeSuccess;

}

bool CSetRecCtrl::GetWebRcrvRecordInner(CData &oResult, char *cResult)
{
			mLogDebug("run GetWebRcrvRecordInner(...)");
			//获取状态
		
			
			char cChnCmd[4096] = {0};
#if 1
			sprintf(cChnCmd,"rec.close_court_rec_on\n");	 
#endif 
		
			
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

InterfaceResCode CSetRecCtrl::GetWebRcrvRecord(string &sResult)
{
			//TODO
			mLogInfo("SetWebRcrvRecord...");
			CData oResult = SVSMAP();
			char cResult[4096] = {0};
			string CMethod = "GetRcrvRecord";
			string ip;
			//printf("SetRecCtrlTaskDel TaskId %s\n", TaskId.c_str());
#if 1
			if(GetWebRcrvRecordInner(oResult, cResult) == false){
				mLogError("Failed to run  GetWebRcrvRecordInner(...)");
				return eInterfaceResCodeError;
			}
#endif 
			
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
		
#if 1
			if( _AnalyParas.ConvertSTRING2CJSONGetParam(oResult, cResult, _result, _VideoFiles, NULL, CMethod, ip, 0) == false){
				mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
				return eInterfaceResCodeError;
			}
#endif 
		
			sResult = ComposeResult();
			cJSON_Delete(_result);
			return eInterfaceResCodeSuccess;

}
bool CSetRecCtrl::GetWebStartAutoRecInner(CData& oResult, char* cResult)
{
			mLogDebug("run GetWebMosaicListParamInner(...)");
		
			//InterfaceResCode resCode = eInterfaceResCodeSuccess;
		
			//1. 封装业务请求
			char szReqBody[1024] = { 0 };
			
			sprintf(szReqBody, "rec.autorecon\n");
			int realBodySize = strlen(szReqBody);
		
			char szReqCmd[1024] = { 0 };
			szReqCmd[0] = 0;  //不加密
			szReqCmd[1] = 2;  //Get请求, 3是SET, 4是SYS
			szReqCmd[2] = realBodySize >> 8;
			szReqCmd[3] = realBodySize;
			memcpy(&szReqCmd[4], szReqBody, realBodySize);
		
#if 1
			//2. 发送socket请求
			MPSOperationRes opResCode = eMPSResultOK; //??
			ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
			if (resCode != eResponseCodeSuccess) {
				mLogError("GetConfig(...) error:" << resCode);
				return false;
			}
#else
			//dummy response
#endif
		
			return true;

}

InterfaceResCode CSetRecCtrl::GetWebStartAutoRec(string &sResult)
{
	   //TODO
			mLogInfo("GetWebStartAutoRec...");

			int masic_num;
			
			char cResult[1024] = { 0 };
			CData oResult = SVSMAP();
			string CMethod = "GetStartAutoRec";
			string ip;
			   //1. 调用类内部方法进一步封装业务请求
			   if (!GetWebStartAutoRecInner(oResult, cResult))
			   {
				 mLogError("Failed to run  GetWebStartAutoRecInner(...)");
				 return eInterfaceResCodeError;
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
		
				//2. 解析响应,存入类型为cJson对象的成员变量中
				if (!_AnalyParas.ConvertSTRING2CJSONGetParam(oResult, cResult, _result, _VideoFiles, NULL, CMethod, ip, 0))
			   {
				mLogError("Failed to run  ConvertSTRING2CJSONGetWebMosaicListParam(...)");
				return eInterfaceResCodeError;
			   }
			 //cJSON_AddItemToObject(_result, "total", cJSON_CreateNumber((masic_num-1)));
			//3. 将step2中获取的响应格式化为Json字符串
			sResult = ComposeResult();
			cJSON_Delete(_result);
			return eInterfaceResCodeSuccess;

}
bool CSetRecCtrl::SetWebStartAutoRecInner(CData& oResult, char* cResult, int StartRec)
{
			mLogDebug("run SetWebStartAutoRecInner(...)");
		
			//InterfaceResCode resCode = eInterfaceResCodeSuccess;
		
			//1. 封装业务请求
			char szReqBody[1024] = { 0 };
			
			sprintf(szReqBody, "rec.autorecon=%d\n", StartRec);
			int realBodySize = strlen(szReqBody);
		
			char szReqCmd[1024] = { 0 };
			szReqCmd[0] = 0;  //不加密
			szReqCmd[1] = 3;  //2Get请求, 3是SET, 4是SYS
			szReqCmd[2] = realBodySize >> 8;
			szReqCmd[3] = realBodySize;
			memcpy(&szReqCmd[4], szReqBody, realBodySize);
		
#if 1
			//2. 发送socket请求
			MPSOperationRes opResCode = eMPSResultOK; //??
			ResponseCode resCode = _client->GetConfigNew(szReqCmd, 4 + realBodySize, opResCode, oResult, cResult);
			if (resCode != eResponseCodeSuccess) {
				mLogError("GetConfig(...) error:" << resCode);
				return false;
			}
#else
			//dummy response
#endif
		
			return true;

}

InterfaceResCode CSetRecCtrl::SetWebStartAutoRec(string &sResult, int StartRec)
{
	   //TODO
			mLogInfo("SetWebStartAutoRec...");
			
			char cResult[1024] = { 0 };
			CData oResult = SVSMAP();

			
			   //1. 调用类内部方法进一步封装业务请求
			   if (!SetWebStartAutoRecInner(oResult, cResult, StartRec))
			   {
				 mLogError("Failed to run  SetWebStartAutoRecInner(...)");
				 return eInterfaceResCodeError;
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
		

			//3. 将step2中获取的响应格式化为Json字符串
			sResult = ComposeResult();
			cJSON_Delete(_result);
			return eInterfaceResCodeSuccess;

}
bool CSetRecCtrl::SetRecUploadStateInner(CData &oResult, char *cResult, string TaskID)
{
			mLogDebug("run SetRecUploadStateInner(...)");
			//获取状态
		
			
			char cChnCmd[4096] = {0};
#if 1
			sprintf(cChnCmd,"<UPFILE_head><dirname>%s</dirname></UPFILE_head>\n", TaskID.c_str());	 
#endif 
		
			
			char cCmdSend[1024] = {0};
			char cHeadCmd[4] = {0};
			//char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
			int  cCmdLength = 0;
			memset(cCmdSend, 0, sizeof(1024)); 
		
			cCmdLength = strlen(cChnCmd) + 4;
			cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
			cHeadCmd[1] = 7; //获取参数指令（SET）
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

InterfaceResCode CSetRecCtrl::SetRecUploadState(string &sResult, string TaskID)
{
			//TODO
			mLogInfo("SetRecUploadState...");
			CData oResult = SVSMAP();
			char cResult[4096] = {0};
			//printf("SetRecCtrlTaskDel TaskId %s\n", TaskId.c_str());
#if 1
			if(SetRecUploadStateInner(oResult, cResult, TaskID) == false){
				mLogError("Failed to run  SetRecUploadStateInner(...)");
				return eInterfaceResCodeError;
			}
#endif 
			
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
		
#if 0
			if( _AnalyParas.ConvertSTRING2CJSONGetWebRecSegModel(oResult, cResult, _result) == false){
				mLogError("Failed to run  ConvertSTRING2CJSONSetRecCtrl(...)");
				return eInterfaceResCodeError;
			}
#endif 
		
			sResult = ComposeResult();
			cJSON_Delete(_result);
			return eInterfaceResCodeSuccess;

}



