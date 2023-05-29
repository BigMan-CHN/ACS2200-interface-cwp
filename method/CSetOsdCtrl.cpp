#include "CSetOsdCtrl.h"
#include <boost/lexical_cast.hpp>

CSetOsdCtrl::CSetOsdCtrl(string ip, int port, int timeOut)
    :_result(cJSON_CreateObject())
    ,_ip(ip)
    ,_port(port)
    ,_timeOut(timeOut)
    ,_client(new MPSClient(ip,port,timeOut))
    ,_AnalyParas()
{

}

bool CSetOsdCtrl::SetOsdStart(int OsdMode,int ChannelID,string Title,CData &oResult,char *cResult)
{
    mLogDebug("run getChnConfig(...)");
    //获取状态
    char cChnCmd[4096] = {0};
	ChannelID = ChannelID + 1;//CWP通道从0开始
#if 1
    if (OsdMode == 0)
    {
        sprintf(cChnCmd,"comp1.osd_on=1\ncomp1.osd1.type=0\ncomp1.osd1.s_display=1\ncomp1.osd1.char_set=UTF-8\ncomp1.osd1.content=%s\ncomp1.osd1.color=2\ncomp1.osd1.size=32\ncomp1.osd1.position=1\n", Title.c_str());
		//sprintf(cChnCmd,INTERFACE_SETADDOSD_SENDCMD, 1, 1, 1, Title.c_str());
    }
    else 
    {
		switch(ChannelID)
		{
			case 1:
				sprintf(cChnCmd,"comp%d.osd_on=1\ncomp%d.osd1.type=0\ncomp%d.osd1.s_display=1\ncomp%d.osd1.char_set=UTF-8\ncomp%d.osd1.content=%s\ncomp%d.osd1.color=2\ncomp%d.osd1.size=32\ncomp%d.osd1.position=1\n",
					ChannelID, ChannelID, ChannelID, ChannelID, ChannelID, Title.c_str(), ChannelID, ChannelID, ChannelID);
				//sprintf(cChnCmd,"comp%d.osd_on=%d\ncomp%d.osd1.type=%d\ncomp%d.osd1.s_display=%d\ncomp%d.osd1.content=%s\ncomp%d.osd1.position=%d\n",
					//ChannelID, 1, ChannelID, 0, ChannelID, 1,ChannelID, Title.c_str(), ChannelID, 1);
				break;
//			case 2:
//				sprintf(cChnCmd,"comp%d.osd_on=1\ncomp%d.osd1.type=0\ncomp%d.osd1.s_display=1\ncomp%d.osd1.char_set=UTF-8\ncomp%d.osd1.content=%s\ncomp%d.osd1.color=2\ncomp%d.osd1.size=32\ncomp%d.osd1.position=1\n",
//					ChannelID, ChannelID, ChannelID, ChannelID, ChannelID, Title.c_str(), ChannelID, ChannelID, ChannelID);
//				break;
			default:
				sprintf(cChnCmd,"vid_cap%d.ch1.osd_on=1\nvid_cap%d.ch1.osd1.char_set=UTF-8\nvid_cap%d.ch1.osd1.s_display=1\nvid_cap%d.ch1.osd1.content=%s\nvid_cap%d.ch1.osd%d.position=1\n", 
					ChannelID-1, ChannelID-1, ChannelID-1, ChannelID-1, Title.c_str(), ChannelID-1);
				break;				
		}
		//sprintf(cChnCmd,INTERFACE_SETADDOSD_SENDCMD, ChannelID, ChannelID, ChannelID, Title.c_str());

    }
#endif 
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（SET）
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

bool CSetOsdCtrl::SetOsdStop(int OsdMode,int ChannelID,CData &oResult,char *cResult)
{
    mLogDebug("run getChnConfig(...)");
    //获取状态
    char cChnCmd[4096] = {0};
	ChannelID = ChannelID + 1;//CWP通道从0开始
#if 1
    if (OsdMode == 0)
    {
		sprintf(cChnCmd,"comp1.osd1.s_display=0\n", ChannelID);
		//sprintf(cChnCmd,INTERFACE_SETDELOSD_SENDCMD, 1);   
    }
    else 
    {
		switch(ChannelID)
		{
			case 1:
				sprintf(cChnCmd,"comp%d.osd1.s_display=0\n", ChannelID);
				break;
//			case 2:
//				sprintf(cChnCmd,"comp%d.osd1.s_display=0\n", ChannelID);
//				break;
			default:
				sprintf(cChnCmd,"vid_cap%d.ch1.osd1.s_display=0\n", ChannelID-1);
				//sprintf(cChnCmd,INTERFACE_SETDELOSD_SENDCMD, ChannelID);
				break;				
		}

		//sprintf(cChnCmd,INTERFACE_SETDELOSD_SENDCMD, ChannelID+1);
    }
#endif 
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（SET）
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

bool CSetOsdCtrl::ComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    return true;
}

string CSetOsdCtrl::ComposeResult()
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

InterfaceResCode CSetOsdCtrl::SetOsdCtrlStart(string &sResult,int OsdMode,int ChannelID,string Title)
{
    //TODO
    mLogInfo("获取主机网络配置和通道配置信息...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
    //printf("SetDecCtrlStart OsdMode %d ChannelID %d Title %s\n", OsdMode, ChannelID, Title.c_str());
#if 1
    if(SetOsdStart(OsdMode, ChannelID, Title, oResult, cResult) == false){
        mLogError("Failed to run  getMPSConfig(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
    ;
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
    if( _AnalyParas.ConvertSTRING2CJSONSetOsdCtrl(oResult, cResult) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetOsdCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}

InterfaceResCode CSetOsdCtrl::SetOsdCtrlStop(string &sResult,int OsdMode,int ChannelID)
{
    //TODO
    mLogInfo("SetOsdCtrlStop...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
    //printf("SetDecCtrlStop OsdMode %d ChannelID %d\n", OsdMode, ChannelID);
#if 1
    if(SetOsdStop(OsdMode, ChannelID, oResult, cResult) == false){
        mLogError("Failed to run  SetOsdStop(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
    ;
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
    if( _AnalyParas.ConvertSTRING2CJSONSetOsdCtrl(oResult, cResult) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSetOsdCtrl(...)");
        return eInterfaceResCodeError;
    }
#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
bool CSetOsdCtrl::SetCwpOsdInner( int OverlayDisplay, int Chn, int Post, int Num, int Type, string Content, int Color, int FontSize, int TimeORText, CData &oResult, char *cResult)
{
    mLogDebug("run SetCwpOsdInner(...)");
    //获取状态

    //add fwb 20201110
    char cChnCmd[4096] = {0};
	char *ReqBody;
	string Enctype;
//	Type = 1;
	Num = 2;
//	OverlayDisplay = 1;
	switch(Type)
	{
		case 1:
			Enctype = "UTF-8";
			break;
		case 2:
			Enctype = "GB2312";
			break;
		default:
		    mLogError("SetCwpOsdInner  Enctype error:"<<Type);
            return false;
	}
	
	if(Chn >= 1)
	{
//		Chn = Chn - 1;
		sprintf(cChnCmd,"vid_cap%d.ch1.osd_on=%d\nvid_cap%d.ch1.osd%d.type=%d\nvid_cap%d.ch1.osd%d.char_set=%s\nvid_cap%d.ch1.osd%d.s_display=%d\nvid_cap%d.ch1.osd%d.content=%s\nvid_cap%d.ch1.osd%d.color=%d\nvid_cap%d.ch1.osd%d.size=%d\nvid_cap%d.ch1.osd%d.position=%d\n", \
			Chn, 1, Chn, Num, TimeORText, Chn, Num, Enctype.c_str(),Chn, Num, OverlayDisplay, Chn, Num, Content.c_str(), Chn, Num, Color, Chn, Num, FontSize, Chn, Num, Post);
//		sprintf(cChnCmd,"vid_cap%d.ch1.osd_on=%d\nvid_cap%d.ch1.osd%d.type=%d\nvid_cap%d.ch1.osd%d.s_display=%d\nvid_cap%d.ch1.osd%d.content=%s\n", \
//			Chn, 1, Chn, Num, TimeORText, Chn, Num, OverlayDisplay, Chn, Num, Content.c_str());

	}
	else if(Chn == 0)
	{
		Chn = Chn + 1;
		sprintf(cChnCmd,"comp%d.osd_on=%d\ncomp%d.osd%d.type=%d\ncomp%d.osd%d.s_display=%d\ncomp%d.osd%d.char_set=%s\ncomp%d.osd%d.content=%s\ncomp%d.osd%d.color=%d\ncomp%d.osd%d.size=%d\ncomp%d.osd%d.position=%d\n", \
		Chn, 1, Chn, Num, TimeORText, Chn, Num, OverlayDisplay, Chn, Num, Enctype.c_str(), Chn, Num, Content.c_str(), Chn, Num, Color, Chn, Num, FontSize,Chn, Num, Post);
//		sprintf(cChnCmd,"comp%d.osd_on=%d\ncomp%d.osd%d.type=%d\ncomp%d.osd%d.s_display=%d\ncomp%d.osd%d.content=%s\n", \
//		Chn, 1, Chn, Num, TimeORText, Chn, Num, OverlayDisplay, Chn, Num, Content.c_str());

		mLogDebug("cChnCmd = "<<cChnCmd);

	}

#if 0	
	else if(SelectType == 2)
	{
		sprintf(cChnCmd, "vid_enc%d.osd_on=%d\nvid_enc%d.osd%d.s_display=%d\nvid_enc%d.osd%d.char_set=%s\nvid_enc%d.osd%d.type=%d\nvid_enc%d.osd%d.color=%d\nvid_enc%d.osd%d.size=%d\nvid_enc%d.osd%d.content=%s\nvid_enc%d.osd%d.position=%d\n", \
			Chn, 1, Chn, Num, OverlayDisplay, Chn, Num, Enctype.c_str(), Chn, Num, 0, Chn, Num, Color, Chn, Num, FontSize, Chn, Num, Content.c_str(),Chn, Num, Post);

		ReqBody = cChnCmd + strlen(cChnCmd);
		
		sprintf(ReqBody, "vid_enc%d.substream.osd_on=%d\nvid_enc%d.superstream.osd_on=%d\n",Chn, 1, Chn, 1);
	}


    //sprintf(cChnCmd,INTERFACE_SETWEBEXTEFFECT_SENDCMD, Chn, Num, Enctype.c_str(),Chn, Num, OverlayDisplay, Chn, Num, Post, Chn, Num, Content.c_str(), Chn, Num, Color, Chn, Num, FontSize);
	//sprintf(cChnCmd,"vid_cap%d.ch1.osd%d.char_set=%s\nvid_cap%d.ch1.osd%d.s_display=%d\nvid_cap%d.ch1.osd%d.position=%d\nvid_cap%d.ch1.osd%d.content=%s\nvid_cap%d.ch1.osd%d.color=%d\nvid_cap%d.ch1.osd%d.size=%d\n",\
	//Chn, Num, Enctype.c_str(),Chn, Num, OverlayDisplay, Chn, Num, Post, Chn, Num, Content.c_str(), Chn, Num, Color, Chn, Num, FontSize);

#endif 

    //add fwb 20201110
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（2GET）
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

InterfaceResCode CSetOsdCtrl::SetCwpOsd(string &sResult,int Chn, int Post,int Num, int Type, string Content, int OverlayDisplay, int Color, int FontSize, int TimeORText)
{
    //TODO
    mLogInfo("SetCwpOsd...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
    //printf("SetRecCtrlStart RecMode %d ChnID %d TaskId %s Title %s\n", RecMode, ChnID, TaskId.c_str(), Title.c_str());
#if 1
    if(SetCwpOsdInner( OverlayDisplay, Chn, Post, Num, Type, Content, Color, FontSize, TimeORText, oResult, cResult) == false){
        mLogError("Failed to run  SetCwpOsdInner(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
    
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
	if (cResult[5] != 0)
	{
		mLogError("error:"<<cResult[5]);
		return eInterfaceResCodeError;
	}

#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
bool CSetOsdCtrl::SetCwpOsdDelInner(int ChannelID, int OsdChnID, CData &oResult,char *cResult)
{
    mLogDebug("run SetCwpOsdDelInner(...)");
    //获取状态
    char cChnCmd[4096] = {0};
//	ChannelID = ChannelID + 1;//CWP通道从0开始
#if 1
	OsdChnID = 2;

	switch(ChannelID)
	{
		case 0:
			sprintf(cChnCmd,"comp%d.osd%d.s_display=0\n", ChannelID+1,OsdChnID);
			break;
		case 1:
			sprintf(cChnCmd,"comp%d.osd%d.s_display=0\n", ChannelID+1,OsdChnID);
			break;
		default:
			sprintf(cChnCmd,"vid_cap%d.ch1.osd%d.s_display=0\n", ChannelID-1,OsdChnID);
			//sprintf(cChnCmd,INTERFACE_SETDELOSD_SENDCMD, ChannelID);
			break;				
	}

    
#endif 
    char cCmdSend[1024] = {0};
    char cHeadCmd[4] = {0};
    //char *cTmpCmd = INTERFACE_GETHOSTCONFIG_SENDCMD;
    int  cCmdLength = 0;
    memset(cCmdSend, 0, sizeof(1024)); 

    cCmdLength = strlen(cChnCmd) + 4;
    cHeadCmd[0] = 0; //当Buf[0]为0x00时，表示网管协议不加密,当Buf[0]为0x01时，表示网管协议加密
    cHeadCmd[1] = 3; //获取参数指令（SET）
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

InterfaceResCode CSetOsdCtrl::SetCwpOsdDel(string &sResult,int ChannelID, int OsdChnID)
{
    //TODO
    mLogInfo("SetCwpOsdDel...");
    CData oResult = SVSMAP();
    char cResult[4096] = {0};
    //printf("SetDecCtrlStop OsdMode %d ChannelID %d\n", OsdMode, ChannelID);
#if 1
    if(SetCwpOsdDelInner(ChannelID, OsdChnID, oResult, cResult) == false){
        mLogError("Failed to run  SetCwpOsdDelInner(...)");
        return eInterfaceResCodeError;
    }
#endif 
    
    ;
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
	if (cResult[5] != 0)
	{
		mLogError("error:"<<cResult[5]);
		return eInterfaceResCodeError;
	}

#endif 

    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}



