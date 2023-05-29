#include "CSendSerialCmd.h"

CSendSerialCmd::CSendSerialCmd(string ip, int port, int timeOut)
    :_ip(ip)
    ,_port(port)
    ,_timeOut(timeOut)
    ,_client(new MPSClient(ip,port,timeOut))
{

}

bool CSendSerialCmd::GetSerialConfig(int SerialID, string Cmd, CData &oResult, char *cResult)
{
    mLogDebug("run GetSerialConfig(...)");
    //获取状态

    //add fwb 20201119
    int  cCmdLength   = 0;
    char cCmdSend[1024]   = {0};

    cCmdLength = strlen(Cmd.c_str());
    memcpy(cCmdSend, Cmd.c_str(), strlen(Cmd.c_str()));

    MPSOperationRes opResCode = eMPSResultOK;
    ResponseCode resCode = _client->GetSerialNew(SerialID, cCmdSend, cCmdLength, opResCode, oResult,cResult);
    if(resCode != eResponseCodeSuccess){
        mLogError("GetConsoleNew(...) error:"<<resCode);
        return false;
    }

    return true;
}

bool CSendSerialCmd::ComposeResult(cJSON *result)
{
    if(_result == NULL || result == NULL){
        mLogError("cJSON result == NULL.");
        result = NULL;
        return false;
    }

    return true;
}

string CSendSerialCmd::ComposeResult()
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

InterfaceResCode CSendSerialCmd::SendSerialCmd(string sResult, int SerialID, string Cmd)
{
    mLogInfo("发送串口透传指令...");
    CData oResult = SVSMAP();
    char cResult[8192] = {0};
#if 1
    if(GetSerialConfig(SerialID, Cmd, oResult, cResult) == false){
        mLogError("Failed to run  GetConsoleConfig(...)");
        return eInterfaceResCodeError;
    }
#endif 
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("SendConsoleCmd\n");
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

    if( _AnalyParas.ConvertSTRING2CJSONSendConsoleCmd(oResult, cResult) == false){
        mLogError("Failed to run  ConvertSTRING2CJSONSendConsoleCmd(...)");
        return eInterfaceResCodeError;
    }
#endif 
    sResult = ComposeResult();
    return eInterfaceResCodeSuccess;
}
