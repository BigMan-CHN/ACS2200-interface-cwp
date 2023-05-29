#include "CAnalyzeParaProc.h"
#include <boost/lexical_cast.hpp>

int sipID = 0; // 暂时使用，sipid号。手动填写，后续修改自动


/*分割字符串到一个字符串数组中*/  
StringTab CAnalyzeParaProc::StringSplit(char* string,const char* split)  
{  
	StringTab result;  
	/*首先分配一个char*的内存，然后再动态分配剩下的内存*/  
	result.string = (char * * )malloc(sizeof(char *)*1);  
	memset(result.string,0,sizeof(char *)*1);  
	/*无论是否存在该分割串，绝对都会分割到一个字符串*/  
	result.number = 0;  
	/*定义一个遍历用的指针和一个寻找位置用的指针*/  
	char* p = string;  
	char* pos = string;  
	while(*p != '\0')  
	{  
		if (result.number > 8192)
			break;
		char* temp;  
		char* tt;  
		/*查找该字符串*/  
		pos = strstr(p,split);  
		/*结果为0说明剩下的字符串中没有该字符了*/  
		if(pos == 0)  
		{  
			result.string = (char **)realloc(result.string,sizeof(char *)*(result.number+1));  
			result.string[result.number] = p;  

			return result;  
		}  
		/*分配临时字符串空间*/  
		temp = (char *)malloc(sizeof(char)*(pos - p+1));  
		memset(temp,0,sizeof(char)*(pos - p+1));  
		/*设置头指针，以便赋值时使用*/  
		tt = temp;  
		while(p<=pos)  
		{  
			*temp++ = *p++;  
		}  
		/*将字符串结尾置零*/  
		*--temp = '\0';  
		result.string = (char **)realloc(result.string,sizeof(char *)*(result.number+1));  
		result.string[result.number] = tt;  
		/*计数器加一*/  
		result.number++;  
		/*设置下一次遍历时的指针（重要）。当split长度大于1时，不这样设置会多赋值不必要的字符串*/  
		p +=strlen(split)-1;  
	}  
	return result;  
}  

void CAnalyzeParaProc::AnalyParaCmdSplitMessage(char *string, char **top, char **low)
{
	if(NULL == string || NULL == top || NULL == low) {
		printf("string ||  top || low is NULL\n");
		return;
	}
	int i;
	for(i = 0; i < strlen(string); i++)
	{
		if (string[i] == ' ')
		{
			string[i] = '^'; //scanf 遇到空白字符结束
		}
	}
	sscanf(string, "%[^=]=%s", *top, *low);
}

void CAnalyzeParaProc::AnalyParaCmdCommandPartSplit(char *top, char **str)
{
	sscanf(top, "%[^.].%[^.].%[^.].%[^.].%s", str[0], str[1], str[2], str[3], str[4]);
}

void CAnalyzeParaProc::AnalyParaCmdArgumentsPartSplit(char *low, char **arg)
{
	sscanf(low, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s", arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], arg[6], arg[7], arg[8], arg[9]);
}

 void CAnalyzeParaProc::IncBuffer(char **pp)
{
	(*pp)++;
}

 void CAnalyzeParaProc::SubBuffer(unsigned char **pp)
{
	(*pp)--;
}

char* CAnalyzeParaProc::StringCmp( char *str1, const char *str2)
{
	char str_length; 
	char i;

	str_length = strlen(str2);
	for(i=0; i<str_length; i++)
	{   
		if(*str1 == *str2)
		{   
			IncBuffer(&str1);
			str2++;
		}   
		else
		{   
			return NULL;    
		}   
	}   
	return str1;
}


/*********************************************************
 *Function: ipaddr available check
 *Return  : 1(right) 0(fault)
 **********************************************************/
int CAnalyzeParaProc::IpAvalbCheck(char *ascii_buf)
{
	int i;
	int point = 0;

	if (INADDR_NONE == inet_addr(ascii_buf))     
		return 0;//不合法
	else    
	{
		if (!strncmp(ascii_buf, "0.0.0.0", strlen("0.0.0.0")))
			return 0;//不合法
		for(i=0; i<strlen(ascii_buf); i++)
		{
			if (ascii_buf[i] == ' ')
				return 0;//不合法
			else if (ascii_buf[i] == '.')
				point++;
		}
		if (point != 3)
			return 0;//不合法
	}

	return 1;//合法；
}

int CAnalyzeParaProc::AnalyNetRecvPara(int Id, char *NetParaStr, char *NetParaArg)
{
	//printf("str %s arg %s\n", NetParaStr,NetParaArg);
	if (StringCmp(NetParaStr,"url"))
	{
		cArray = cJSON_CreateObject();
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECID,cJSON_CreateNumber(Id-1));
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECURL,cJSON_CreateString(NetParaArg));
		if(strlen(NetParaArg) > 0){
			cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECSTA,cJSON_CreateNumber(1));
		}
		else{
			cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECSTA,cJSON_CreateNumber(0));
		}
	}
/*	else if (StringCmp(NetParaStr,"setup_mode"))
	{
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECSTA,cJSON_CreateNumber(atoi(NetParaArg)));
	}*/
	else if (StringCmp(NetParaStr,"trans_protol"))
	{
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECMODE,cJSON_CreateString(NetParaArg));
		cJSON_AddItemToArray(_rtspdec, cArray);
	}

	return 1;//合法；
}

int CAnalyzeParaProc::AnalyNetH323Para(int Id, char *NetParaStr, char **NetParaArg)
{
	//printf("str %s arg %s\n", NetParaStr,NetParaArg);
	if (StringCmp(NetParaStr,"call"))
	{
		h323cArray = cJSON_CreateObject();
		cJSON_AddItemToObject(h323cArray,GET_HOST_CONFIG_RES_DE_H323ID,cJSON_CreateNumber(Id));
		cJSON_AddItemToObject(h323cArray,GET_HOST_CONFIG_RES_DE_H323STA,cJSON_CreateNumber(atoi(NetParaArg[1])));
		cJSON_AddItemToObject(h323cArray,GET_HOST_CONFIG_RES_DE_H323CALLIP,cJSON_CreateString(NetParaArg[0]));
		cJSON_AddItemToArray(_h323dec, h323cArray);
	}

	return 1;//合法；
}

int CAnalyzeParaProc::AnalyNetChnSendPara(int Id, char *NetParaStr, char *NetParaArg)
{
	//printf("str %d %s arg %s\n", Id, NetParaStr,NetParaArg);
#if 1
	if (StringCmp(NetParaStr,"name"))
	{
		cArray = cJSON_CreateObject();
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_CH_NCHNID,cJSON_CreateNumber(Id-1));
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString(NetParaArg));
	}
	else if (StringCmp(NetParaStr,"on"))
	{
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_CH_NCHNSTA,cJSON_CreateNumber(atoi(NetParaArg)));
	}
	else if (StringCmp(NetParaStr,"url"))
	{
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_CH_NCHNURL,cJSON_CreateString(NetParaArg));
	}
	else if (StringCmp(NetParaStr,"recording"))
	{
		cJSON_AddItemToObject(cArray,"OldRecStatus",cJSON_CreateNumber(atoi(NetParaArg)));
	}
	else if (StringCmp(NetParaStr,"rec_path"))
	{
		cJSON_AddItemToObject(cArray,"OldRecTaskID",cJSON_CreateString(NetParaArg));
		
	}
	else if (StringCmp(NetParaStr,"rec_current_status"))
	{
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_CH_NCHNRECSTA,cJSON_CreateNumber(atoi(NetParaArg)));
	}
	else if (StringCmp(NetParaStr,"rec_task_id"))
	{
		cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_CH_NCHNRECTASKID,cJSON_CreateString(NetParaArg));
		cJSON_AddItemToArray(_channal, cArray);
	}
#endif 
	return 1;//合法；
}

int CAnalyzeParaProc::AnalyGetRecParaSearch(char *cParaBuf, char *cDealBuf, char *cStartXml, char *cEndXml, int *iOffsetLen)
{
	char *ptr1 = NULL, *ptr2 = NULL;
	int offset1 = 0;
	int offset2 = 0;

	ptr1 = strstr(cParaBuf, cEndXml);
	if (NULL == ptr1) {
		//printf("doesn't contain %s\n", cEndXml);
		return 0;
	}

	offset1 = ptr1 - cParaBuf;
	ptr2 = strstr(cParaBuf, cStartXml);
	if (NULL == ptr2) {
		//printf("doesn't contain %s\n", cStartXml);
		return 0;
	}
	offset2 = ptr2 - cParaBuf;
	if (offset1 - offset2 - strlen(cStartXml) > 4096) {
		//printf("out of range  %s\n", cStartXml);
		return 0;
	}

	*iOffsetLen = offset1 + strlen(cEndXml);
	strncpy(cDealBuf, cParaBuf+offset2+strlen(cStartXml), offset1 - offset2 - strlen(cStartXml));
	return 1;
}

int CAnalyzeParaProc::AnalyGetRecPara(char *cParaBuf, int iLen)
{
	int ret = 0, paranum = 0;
	char dealbuf[128] = {0};
	char *curPos = NULL;
	int  curOffsetLen = 0;
	int  offsetLen = 0;

	if((_videofiles == NULL) && (_recresult == NULL))
	{
		printf("cJSON _videoviles or _recresult == NULL.");
		return false;
	}

#if 0
	for (int i = 0; i < iLen; i++)
    {
		printf("%c", cParaBuf[i]);
    }
	printf("\n");
#endif 
    cParaBuf[iLen] = '\0';
	//printf("AnalyGetRecPara %s\n", cParaBuf);

	//allowDelete
	memset(dealbuf, 0, sizeof(dealbuf));
	curPos = cParaBuf;
	ret = AnalyGetRecParaSearch(curPos, dealbuf, "<allowDelete>", "</allowDelete>", &offsetLen);
	if (ret == 0)
	{
		//printf("AnalyGetRecParaSearch false %s\n", "<allowDelete>");
		return false;
	}
	curOffsetLen = offsetLen;
	//printf("buf %s %d\n", dealbuf, curOffsetLen);
	cJSON_AddItemToObject(_recresult,GET_INFOLIST_RES_ALLOWDELETE,cJSON_CreateBool((strlen(dealbuf)==4)?true:false));
	
	//total
	memset(dealbuf, 0, sizeof(dealbuf));
	curPos = cParaBuf + curOffsetLen;
	ret = AnalyGetRecParaSearch(curPos, dealbuf, "<total>", "</total>", &offsetLen);
	if (ret == 0)
	{
		//printf("AnalyGetRecParaSearch false %s\n", "<total>");
		return false;
	}
	curOffsetLen += offsetLen; 
	//printf("buf %s %d\n", dealbuf, curOffsetLen);
	cJSON_AddItemToObject(_recresult,GET_INFOLIST_RES_TOTAL,cJSON_CreateNumber(atoi(dealbuf)));

#if 1
	paranum = atoi(dealbuf);
	//循环次数
	FileEndIndex = FileEndIndex > paranum ? paranum : FileEndIndex;
	int filenum = (FileEndIndex - FileStartIndex + 1) < paranum ? (FileEndIndex - FileStartIndex + 1) : paranum;
	//printf("paranum %d\n", paranum);
	for (int i = 0; i < filenum; i++)
	{
		//</fileSort>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<fileSort>", "</fileSort>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<fileSort>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cArray = cJSON_CreateObject();
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_FILESORT,cJSON_CreateNumber(atoi(dealbuf)));
		
		//</TaskID>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<TaskID>", "</TaskID>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<TaskID>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_TASKID,cJSON_CreateString(dealbuf));

		//</fileName>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<fileName>", "</fileName>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<fileName>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_FILENAME,cJSON_CreateString(dealbuf));

		//</size>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<size>", "</size>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<size>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_SIZE,cJSON_CreateNumber(atoi(dealbuf)));
		
		//</filePath>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<filePath>", "</filePath>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<filePath>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_FILEPATH,cJSON_CreateString(dealbuf));

		//</startTime>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<startTime>", "</startTime>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<startTime>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_STARTTIME,cJSON_CreateString(dealbuf));

		//</endTime>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<endTime>", "</endTime>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<endTime>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_ENDTIME,cJSON_CreateString(dealbuf));
		
		//</channelNum>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<channelNum>", "</channelNum>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<channelNum>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_CHANNELNUM,cJSON_CreateNumber(atoi(dealbuf)));
	
		//</channelDesc>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<channelDesc>", "</channelDesc>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<channelDesc>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_CHANNELDESC,cJSON_CreateString(dealbuf));
		
		//</ftpPath>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<ftpPath>", "</ftpPath>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<ftpPath>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_FTPPATH,cJSON_CreateString(dealbuf));
		
		//</ftpusr>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<ftpusr>", "</ftpusr>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<ftpusr>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_FTPUSR,cJSON_CreateString(dealbuf));
		
		//</ftppasswd>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<ftppasswd>", "</ftppasswd>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<ftppasswd>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_FTPPASSWD,cJSON_CreateString(dealbuf));
		
		//</vodurlRtsp>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<vodurlRtsp>", "</vodurlRtsp>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<vodurlRtsp>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_VODURLRTSP,cJSON_CreateString(dealbuf));
		//</fileHttpPath>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<fileHttpPath>", "</fileHttpPath>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<vodurlRtmp>");
			mLogError("Failed to run  AnalyGetRecParaSearch(<fileHttpPath>)");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,"fileHttpPath",cJSON_CreateString(dealbuf));
		//</fileUploadStatus>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<fileUploadStatus>", "</fileUploadStatus>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<vodurlRtmp>");
			mLogError("Failed to run  AnalyGetRecParaSearch(<fileUploadStatus>)");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,"fileUploadStatus",cJSON_CreateString(dealbuf));
		//</vodurlRtmp>
		memset(dealbuf, 0, sizeof(dealbuf));
		curPos = cParaBuf + curOffsetLen;
		ret = AnalyGetRecParaSearch(curPos, dealbuf, "<vodurlRtmp>", "</vodurlRtmp>", &offsetLen);
		if (ret == 0)
		{
			//printf("AnalyGetRecParaSearch false %s\n", "<vodurlRtmp>");
			return false;
		}
		curOffsetLen += offsetLen;
		//printf("buf %s %d\n", dealbuf, strlen(dealbuf));
		cJSON_AddItemToObject(cArray,GET_INFOLIST_RES_VODURLRTMP,cJSON_CreateString(dealbuf));
		
		cJSON_AddItemToArray(_videofiles, cArray);
	}
#endif


	return 1;//合法；
}

/* SET 指令处理每一条函数 */
int CAnalyzeParaProc::AnalyParaCmdParseCommandHandle(char **str, char **arg, char *string)
{
	int  cmd_id = -1;
	char *n_ptr = NULL;
	
	//CRtspNode NetRecv;
    const char *CmdTab[] ={"vid_cap","vid_enc","vid_dec","vid_dis_hd","comp","net_recv",	/* 5 */
						 "net_send","pci_vid_in","pci_vid_out","pci_aud_in","pci_aud_out",	/* 10 */
						 "aud_cap","aud_enc","aud_dec","aud_out","hdmi_aud_out",	/* 15 */
						 "h323h","sip","rec","demux","screenshot","eth",	/* 20 */
						 "mosaic","nm","mn","core","vm",	/* 25 */
						 "NO_FLAG","syslog","sys","tdc","del",	/* 30 */
						 "rzk","am","dvc","links","status",	/* 35 */
						 "encrypt","web","back_pic","ntp","audio_info",	/* 40 */
						 "","","","","END_FLAG"
						};


	int cmd_tab_number = sizeof(CmdTab)/sizeof(CmdTab[0]);

	for(int i = 0; i < cmd_tab_number; i++) {
		if((n_ptr = StringCmp(str[0], CmdTab[i]))) {
			cmd_id = i;
			break;
		}
	}

	//模块名不存在
	if(-1 == cmd_id) {
		return false;
	}
    //printf("AnalyParaCmdParseCommandHandle %d %s %s %s\n", cmd_id, str[0], str[1], arg[0]);

#if 1
	if (CHNSYS_ETH_OP == cmd_id)
	{
		if(!strcmp(CMethod.c_str(),"GetWebMosaicList"))
		{
			if (StringCmp(str[1], "conf"))
			{
				if (!IpAvalbCheck(arg[0])) {
					mLogError("GetWebHostConfig ip_avalb_check LogInfo, ip = "<<arg[0]);
					return ARG_STR_ERR;
				}
				if (!IpAvalbCheck(arg[1])) {
					mLogError("GetWebHostConfig ip_avalb_check LogInfo, netmask = "<<arg[1]);
					return ARG_STR_ERR;
				}
				if (!IpAvalbCheck(arg[2])) {
					mLogError("GetWebHostConfig ip_avalb_check LogInfo, gateway = "<<arg[2]);
					return ARG_STR_ERR;
				}		
				//printf("AnalyParaCmdParseCommandHandle %s %s %s\n", arg[0], arg[1], arg[2]);
				_ip = arg[0];
				return true;
			}
		
		}

		if (!IpAvalbCheck(arg[0])) {
			printf("ip_avalb_check LogInfo, ip = %s\n", arg[0]);
			return ARG_STR_ERR;
		}
		if (!IpAvalbCheck(arg[1])) {
			printf("ip_avalb_check LogInfo, netmask = %s\n", arg[1]);
			return ARG_STR_ERR;
		}
		if (!IpAvalbCheck(arg[2])) {
			printf("ip_avalb_check LogInfo, gateway = %s\n", arg[2]);
			return ARG_STR_ERR;
		}		
		//printf("AnalyParaCmdParseCommandHandle %s %s %s\n", arg[0], arg[1], arg[2]);
		if(_network == NULL){
//			printf("cJSON network == NULL.");
			return false;
		}
		cJSON_AddItemToObject(_network,GET_HOST_CONFIG_RES_NW_IP        ,cJSON_CreateString(arg[0]));
		cJSON_AddItemToObject(_network,GET_HOST_CONFIG_RES_NW_GATEWAY   ,cJSON_CreateString(arg[1]));
		cJSON_AddItemToObject(_network,GET_HOST_CONFIG_RES_NW_NETMASK   ,cJSON_CreateString(arg[2]));

	}
	else if (CHNSYS_SYS_OP == cmd_id)
	{
		if(_sysinfo == NULL)
		{
			printf("cJSON _sysinfo == NULL.");
			return false;
		}

		if (StringCmp(str[1], "name"))
		{
			cJSON_AddItemToObject(_sysinfo,GET_HOST_CONFIG_RES_SYS_DEVTYPE ,cJSON_CreateString(arg[0]));
		}
		else if (StringCmp(str[1], "_swver"))
		{
			cJSON_AddItemToObject(_sysinfo,GET_HOST_CONFIG_RES_SYS_SVER,cJSON_CreateString(arg[0]));
		}
		else if (StringCmp(str[1], "_hwver"))
		{
			cJSON_AddItemToObject(_sysinfo,GET_HOST_CONFIG_RES_SYS_HVER,cJSON_CreateString(arg[0]));
		}
		else if (StringCmp(str[1], "sn"))
		{
    		cJSON_AddItemToObject(_sysinfo,GET_HOST_CONFIG_RES_SYS_SN,cJSON_CreateString(arg[0]));
		}
	}
	else if (CHNSYS_STATUS_GET == cmd_id)
	{
		if(_diskinfo == NULL)
		{
			printf("cJSON _diskinfo == NULL.");
			return false;
		}

		if (StringCmp(str[1], "totalsize"))
		{
    		cJSON_AddItemToObject(_diskinfo,GET_HOST_CONFIG_RES_DI_TOTALSIZE,cJSON_CreateNumber(atoi(arg[0])));
		}
		else if (StringCmp(str[1], "freedisk"))
		{
    		cJSON_AddItemToObject(_diskinfo,GET_HOST_CONFIG_RES_DI_FREESIZE,cJSON_CreateNumber(atoi(arg[0])));
		}

	}
	else if (CHNSYS_REC_OP == cmd_id)
	{

		if (StringCmp(str[1], "minifreespace"))
		{
    		cJSON_AddItemToObject(_diskinfo,GET_HOST_CONFIG_RES_DI_AUTODELSIZE,cJSON_CreateNumber(atoi(arg[0])));
		}
		//GetRecordState
		if (StringCmp(str[1], "rec_status_type"))
		{
			cJSON_AddItemToObject(_recresult,"RecState",cJSON_CreateNumber(atoi(arg[0])));
		}
		
		if (StringCmp(str[1], "autorecon"))
	    {
	      cJSON_AddItemToObject(_result, "StartRec", cJSON_CreateNumber(atoi(arg[0])));
	    }
		
		//GetRcrvRecord
	    if (StringCmp(str[1], "close_court_rec_on"))
	    {
	      cJSON_AddItemToObject(_result,"RecOn", cJSON_CreateNumber(atoi(arg[0])));
	    }
	}
	else if (CHNSYS_DVC_GET == cmd_id)
	{
		if(!strcmp(CMethod.c_str(),"GetHostChnInfo"))
		{
			if (StringCmp(str[1], "allrecstatus"))
			{
    			cJSON_AddItemToObject(_result,"AllRecStatus",cJSON_CreateNumber(atoi(arg[0])));
			}

		}
		//GetHostConfig
		if (StringCmp(str[1], "net_recv_max_num"))
		{
    		cJSON_AddItemToObject(_decnum,GET_HOST_CONFIG_RES_DE_RTSPDECNUM,cJSON_CreateNumber(atoi(arg[0])));
		}
		else if (StringCmp(str[1], "h323_num"))
		{
    		cJSON_AddItemToObject(_decnum,GET_HOST_CONFIG_RES_DE_H323DECNUM,cJSON_CreateNumber(atoi(arg[0])));
		}
		else if (StringCmp(str[1], "sip_num"))
		{
    		cJSON_AddItemToObject(_decnum,GET_HOST_CONFIG_RES_DE_SIPDECNUM,cJSON_CreateNumber(atoi(arg[0])));
		}
		else if (StringCmp(str[1], "net_send_max_num"))
		{
    		cJSON_AddItemToObject(_decnum,GET_HOST_CONFIG_RES_CH_CHANNELNUM,cJSON_CreateNumber(atoi(arg[0])));
		}
		else if (StringCmp(str[1], "rtmp_client_send_num"))
		{
    		cJSON_AddItemToObject(_decnum,GET_HOST_CONFIG_RES_CH_RTMPCLIPUSHNUM,cJSON_CreateNumber(atoi(arg[0])));
		}
		else if (StringCmp(str[1], "uart_num"))
		{
    		cJSON_AddItemToObject(_decnum,GET_HOST_CONFIG_RES_CH_SERIALNUM,cJSON_CreateNumber(atoi(arg[0])));
		}
	}
	else if (CHNSYS_NET_RECV_OP == cmd_id)
	{
		if(_rtspdec == NULL)
		{
			printf("_rtspdec == NULL.");
			return false;
		}
		
		int len = strlen(str[0]);
		memcpy(str[0],str[0]+8,len-8);//8:NET_RECV字符数量
		int net_num = atoi(str[0]);//NET_RECV%d,NET_RECV的序号

		//char *cCurPost = str[0] + 8;
		//printf("%s Num %d\n", cCurPost, atoi(cCurPost));
		//AnalyNetRecvPara(atoi(cCurPost), str[1], arg[0]);
		if (StringCmp(str[1],"url"))
		{
			cArray = cJSON_CreateObject();
			cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECID,cJSON_CreateNumber(net_num-1));
			cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECURL,cJSON_CreateString(arg[0]));
			if(strlen(arg[0]) == 0)
			{
				cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECSTA,cJSON_CreateNumber(0));
			}
			else
			{
				cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECSTA,cJSON_CreateNumber(1));
			}
		}
		else if (StringCmp(str[1],"trans_protol"))
		{
			cJSON_AddItemToObject(cArray,GET_HOST_CONFIG_RES_DE_DECMODE,cJSON_CreateString(arg[0]));
			cJSON_AddItemToArray(_rtspdec, cArray);
		}
	}
	else if (CHNSYS_H323H_OP == cmd_id)
	{
		if(_h323dec == NULL)
		{
			printf("_Hh23dec == NULL.");
			return false;
		}
		int len = strlen(str[0]);
		memcpy(str[0],str[0]+5,len-5);//5:h323h字符数量
		int h323h_num = atoi(str[0]);//h323h%d,h323h的序号(目前只有0)
		//char *cCurPost = str[0] + 5;
		//AnalyNetH323Para(atoi(cCurPost), str[1], arg);
		if (StringCmp(str[1],"call"))
		{
			h323cArray = cJSON_CreateObject();
			cJSON_AddItemToObject(h323cArray,GET_HOST_CONFIG_RES_DE_H323ID,cJSON_CreateNumber(0));
			cJSON_AddItemToObject(h323cArray,GET_HOST_CONFIG_RES_DE_H323STA,cJSON_CreateNumber(atoi(arg[1])));
			cJSON_AddItemToObject(h323cArray,GET_HOST_CONFIG_RES_DE_H323CALLIP,cJSON_CreateString(arg[0]));
			cJSON_AddItemToArray(_h323dec, h323cArray);
		}

	}
	else if(CHNSYS_SIP_OP == cmd_id)
	{
		int len = strlen(str[0]);
		memcpy(str[0],str[0]+3,len-3);//3:sip字符数量
		int sip_num = atoi(str[0]);//sip%d,sip的序号
		if (StringCmp(str[1],"call"))
		{
			sipcArray = cJSON_CreateObject();
			cJSON_AddItemToObject(sipcArray,GET_HOST_CONFIG_RES_DE_SIPID,cJSON_CreateNumber(sip_num-1));
			cJSON_AddItemToObject(sipcArray,GET_HOST_CONFIG_RES_DE_SIPSTA,cJSON_CreateNumber(atoi(arg[1])));
			cJSON_AddItemToObject(sipcArray,GET_HOST_CONFIG_RES_DE_SIPCALLIP,cJSON_CreateString(arg[0]));
			cJSON_AddItemToArray(_sipdec, sipcArray);
		}
	}
	else if (CHNSYS_NET_SEND_OP == cmd_id)
	{
		int len = strlen(str[0]);
		memcpy(str[0],str[0]+8,len-8);//7:net_send字符数量
		int send_num = atoi(str[0]);//net_send%d,net_send的序号
		
		if (_cRecStatus != NULL)
		{
			if (StringCmp(str[1], "rec_path"))
			{
				cJSON_AddItemToObject(_cRecStatus,GET_REC_CONFIG_START_TASKID,cJSON_CreateString(arg[0]));
			}

			if (StringCmp(str[1], "recording"))
			{
				cJSON_AddItemToObject(_cRecStatus,GET_REC_CONFIG_START_STATUS,cJSON_CreateNumber(atoi(arg[0])));
			}
				
		}
		if (StringCmp(str[1], "rec_is_select"))
		{
			_arry[send_num] = atoi(arg[0]);
			mLogDebug("#######  _arry"<<send_num<<"="<<_arry[send_num]);
		}
		if(!strcmp(CMethod.c_str(),"GetHostChnInfo"))
		{

			int len = strlen(str[0]);
			memcpy(str[0],str[0]+8,len-8);//7:net_send字符数量
			int num = atoi(str[0]);//net_send%d,net_send的序号
			
			//mLogDebug("GetHostChnInfo net_send = "<<num);
			if(num <= 12)
			{
				if (StringCmp(str[1],"name"))
				{
					cJSON_AddItemToObject(_ParamArry[num],GET_HOST_CONFIG_RES_CH_NCHNNAME,cJSON_CreateString(arg[0]));			
				}
				if (!strcmp(str[1],"rec_current_status"))
				{
					cJSON_AddItemToObject(_ParamArry[num],GET_HOST_CONFIG_RES_CH_NCHNRECSTA,cJSON_CreateNumber(atoi(arg[0])));
				
				}
				if (!strcmp(str[1],"rec_task_id"))
				{	
					cJSON_AddItemToObject(_ParamArry[num],GET_HOST_CONFIG_RES_CH_NCHNRECTASKID,cJSON_CreateString(arg[0]));
				}
				
				if (StringCmp(str[1],"on"))
				{
					cJSON_AddItemToObject(_ParamArry[num],GET_HOST_CONFIG_RES_CH_NCHNID,cJSON_CreateNumber(num));
					cJSON_AddItemToObject(_ParamArry[num],GET_HOST_CONFIG_RES_CH_NCHNSTA,cJSON_CreateNumber(atoi(arg[0])));
				}
				 
				if (StringCmp(str[1],"url"))
				{	
					cJSON_AddItemToObject(_ParamArry[num],"Url",cJSON_CreateString(arg[0]));		
				}
				
				if (StringCmp(str[1],"recording"))
				{
					cJSON_AddItemToObject(_ParamArry[num],"OldRecState",cJSON_CreateNumber(atoi(arg[0])));
				}
				
				if (!strcmp(str[1],"rec_path"))
				{
					cJSON_AddItemToObject(_ParamArry[num],"OldTaskID",cJSON_CreateString(arg[0]));		
				}
			}
		}
		if(!strcmp(CMethod.c_str(),"GetWebMosaicList"))
		{
			int len = strlen(str[0]);
			memcpy(str[0],str[0]+8,len-8);//7:net_send字符数量
			int num = atoi(str[0]);//net_send%d,net_send的序号
			
			//mLogDebug("GetHostChnInfo net_send = "<<num);
			if(num <= 12&&num >=2)
			{
				if (StringCmp(str[1],"url"))
				{	
					cJSON_AddItemToObject(_PArry[num-2],"RtspUrl",cJSON_CreateString(arg[0]));//_PArry[0]存放本地通道1的RtspUrl	
				}
			}
		}
#if 0		
		if (_channal != NULL)
		{
			char *cCurPost = str[0] + 8;
			AnalyNetChnSendPara(atoi(cCurPost), str[1], arg[0]);
		}
#endif		
	}
	else if (CHNSYS_DEMUX_OP == cmd_id)
	{
		if(_statusinfo == NULL)
		{
			printf("_statusinfo == NULL.");
			return false;
		}

		if (StringCmp(str[1], "total_time"))
		{
    		cJSON_AddItemToObject(_statusinfo,GET_HOST_CONFIG_DS_DISCIPLINESTATUS,cJSON_CreateBool((atoi(arg[0])>0)?true:false));
		}

	}
	else if (CHNSYS_MOSAIC_OP == cmd_id)
	{
		mLogDebug("CHNSYS_MOSAIC_OP cmd_id="<<cmd_id);

		int len = strlen(str[0]);
		memcpy(str[0],str[0]+6,len-6);//2:mosaic%d中mosaic字符个数
		int num = atoi(str[0]);//mosaic%d,mosaic的序号
		if(!strcmp(CMethod.c_str(),"GetWebMosaicList"))
		{
			if (StringCmp(str[1], "s_display"))
			{			
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicDisplay", cJSON_CreateNumber(atoi(arg[0])));
			}
		
			if (StringCmp(str[1], "channel"))
			{
			  if((num-1)%4 == 0)
			  {
				  cJSON_AddItemToObject(_PArry[(num-1)/4], "MosaicChn", cJSON_CreateString(arg[0]));
			  
			  }
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicNum", cJSON_CreateNumber(num));
			}
		
			if (StringCmp(str[1], "mode"))
			{
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicType", cJSON_CreateNumber(atoi(arg[0])));
			}
			if (StringCmp(str[1], "win"))
			{//arg={win_x,win_y,win_w,win_h=1/3,1/3,1/3,1/3}
			  char WinX[16]={0};
			  sscanf(arg[3], "%[^=]=%s", WinX, arg[3]);
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicWinX", cJSON_CreateString(arg[3]));
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicWinY", cJSON_CreateString(arg[4]));
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicWinW", cJSON_CreateString(arg[5]));
			  cJSON_AddItemToObject(_ParamArry[num], "MosaicWinH", cJSON_CreateString(arg[6]));
			  mLogDebug("CHNSYS_MOSAIC_OP num="<<num);
			}
		
		}
	
	}
	else if (CHNSYS_VID_CAP_OP == cmd_id)
	{
		mLogDebug("CHNSYS_VID_CAP_OP cmd_id="<<cmd_id);
		if(!strcmp(CMethod.c_str(),"GetWebMosaicList"))
		{
			int len = strlen(str[0]);
			memcpy(str[0],str[0]+7,len-7);//7:vid_cap字符数量
			int num = atoi(str[0]);//vid_cap%d,vid_cap的序号

			if (StringCmp(str[3], "content"))
			{
				cJSON_AddItemToObject(_PArry[num-1], "OsdContent", cJSON_CreateString(arg[0]));
			}
		}
	}

#endif 
	return true;
}

int CAnalyzeParaProc::AnalyParaCmdExtracMessage(char *top, char *low, char *string)
{
	if(NULL == string || NULL == top || NULL == low) {
		printf("arg is NULL\n");
		return false;
	}
	int i, rt;

	/* 申请资源 */
	char *str[MAX_ARG_NUM] = {};
	char *arg[MAX_ARG_NUM] = {};
	for (i = 0; i < MAX_ARG_NUM; i ++){
		str[i] = (char *)calloc(1, strlen(top)+1);
		if(NULL == str[i]) {
			printf("calloc is error\n");
			goto clean;
		}
		arg[i] = (char *)calloc(1, strlen(low)+1);
		if(NULL == arg[i]) {
			printf("calloc is error\n");
			goto clean;
		}
	}

	//printf("top = \"%s\", low = \"%s\"\n", top, low);

	/* 按'.'分割指令内容部分 */
	AnalyParaCmdCommandPartSplit(top, str);

	/* 根据需求。按‘，’分割参数内容部分 */
	AnalyParaCmdArgumentsPartSplit(low, arg);

	/* 网管协议指令处理 */
	rt = AnalyParaCmdParseCommandHandle(str, arg, string);
	if(rt < 0){
		printf("set cmd %s=%s error, rt=%d  :[-1 CMD_STR_ERR; -2 ARG_STR_ERR; -3 CMD_DISABLE; -4 XML_SAVE_ERR]\n",top, low, rt);
	}


clean:
	/* 释放资源 */
	for (i = 0; i < MAX_ARG_NUM; i ++){		
		if( str[i] != NULL ) {
			free(str[i]);
			str[i] = NULL;
		}
		if( arg[i] != NULL ) {
			free(arg[i]);
			arg[i] = NULL;
		}
	}

	return rt;
}

int CAnalyzeParaProc::AnalyParaMessage(char *string)
{
	if(NULL == string) {
		printf("string is NULL\n");
		return false;
	}
	int rt;
	//用于保存等号的前半部，代表命令字段
	char *top = (char *)calloc(1, strlen(string)+1);
	if(NULL == top) {
		printf("calloc is error\n");
		return false;
	}
	//用于保存等号的后半部，代表参数字段
	char *low = (char *)calloc(1, strlen(string)+1);
	if(NULL == low) {
		printf("calloc is error\n");
		if(NULL != top){
			free(top);
			top = NULL;
		}		
		return false;
	}


	/* 获取命令字段部分和参数字段部分 */
	AnalyParaCmdSplitMessage(string, &top, &low);

	/* 指令解析 */
	rt = AnalyParaCmdExtracMessage(top, low,string);

	/* 释放资源 */
	if(NULL != top){
		free(top);
		top = NULL;
	}
	if(NULL != low){
		free(low);
		low = NULL;
	}
	return rt;
}

bool CAnalyzeParaProc::ConvertParaProcessing(char *cParaBuf, int iLen)
{
    int i,count = 0;
	int ret = 0, result = 0;
    StringTab array = {0};
#if 0
    printf("ConvertParaProcessing\n");
    for (int i = 0; i < iLen; i++)
    {
		printf("%c", cParaBuf[i]);
    }
#endif 
    cParaBuf[iLen] = '\0';
    //指令拆分，以回车符分割指令
    array = StringSplit(cParaBuf,"\n");
	for(i = 0; i < array.number; i ++){  
		if (strlen(array.string[i]) > 1){
			count++;
			mLogDebug("######array.string["<<i<<"]: "<<array.string[i]<<"######");  
			/* 处理拆分后的每一条SET指令 */
			result = AnalyParaMessage(array.string[i]);
			if (result < 0) {
				ret = result;
			}
		}	
	}

	if(array.string != NULL){
		free(array.string);
		array.string = NULL;
	}	

    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONGetHostConfig(CData &oResult, char *cResult, cJSON *network, cJSON *sysinfo, cJSON *diskinfo, cJSON *decnum)
{
    _network  = network;
    _sysinfo  = sysinfo;
    _diskinfo = diskinfo;
	_decnum   = decnum;

#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("ConvertSTRING2CJSONGetHostConfig\n");

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
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
    ConvertParaProcessing(ParaBuf, iParaLen);

    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONGetHostDecInfo(CData &oResult, char *cResult, cJSON *rtspdec, cJSON *h323dec,cJSON *sipdec)
{
    _rtspdec  = rtspdec;
    _h323dec  = h323dec;
	_sipdec   = sipdec;
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("ConvertSTRING2CJSONGetHostDecInfo\n");

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
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
    ConvertParaProcessing(ParaBuf, iParaLen);

    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONGetHostChnInfo(CData &oResult, char *cResult, cJSON* result, cJSON *node[], cJSON* _addressList, string Method, int ChnNum)
{
    CMethod = Method;
	_ParamArry = node;
	Param = ChnNum;
	_result = result;

#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("ConvertSTRING2CJSONGetHostDecInfo\n");

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
	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	//printf("ConvertSTRING2CJSONGetHostDecInfo Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetOsdCtrl(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSetOsdCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	
	if (cResult[5] != 0)
	{
		printf("error:%d\n", cResult[5]);
		return false;
	}
*/
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	printf("ConvertSTRING2CJSONSetOsdCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetPutNoteFileCtrl(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSetPutNoteFileCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	*/
	if (cResult[5] != 0)
	{
		//printf("error:%d\n", cResult[5]);
		return false;
	}
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	printf("ConvertSTRING2CJSONSetPutNoteFileCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetDecCtrl(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSetDecCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	*/
	if (cResult[5] != 0)
	{
		printf("error:%d\n", cResult[5]);
		return false;
	}
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	printf("ConvertSTRING2CJSONSetDecCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetRecCtrl(CData &oResult, char *cResult, cJSON *cRecStatus)
{
	_cRecStatus = cRecStatus;
#if 0
    //printf("ConvertSTRING2CJSONSetRecCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	*/
	if (cResult[5] != 0)
	{
		printf("error:%d\n", cResult[5]);
		return false;
	}
#else 	

/*
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("ConvertSTRING2CJSONSetRecCtrl\n");

    for (int i = 0; i < iRecvLength; i++)
    {
	    if (i < 4)
	    {
		    printf("%d", cResult[i]);
			mLogInfo("%d"<<cResult[i]);
	    }
	    else 
	    {
		    printf("%c", cResult[i]);
			mLogInfo("%d"<<cResult[i]);
	    }
    }
*/
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	//printf("ConvertSTRING2CJSONSetRecCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetPowerCtrl(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSetPowerCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	*/
	if (cResult[5] != 0)
	{
		printf("error:%d\n", cResult[5]);
		return false;
	}
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	//printf("ConvertSTRING2CJSONSetPowerCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetDiscipLineCtrl(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSetDiscipLineCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	*/
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	printf("ConvertSTRING2CJSONSetRecCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONGetDiscipLineCtrl(CData &oResult, char *cResult, cJSON *statusinfo)
{
	_statusinfo = statusinfo;
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("ConvertSTRING2CJSONSetDiscipLineCtrl\n");
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
	printf("\n");
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	//printf("ConvertSTRING2CJSONGetDiscipLineCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSetStreamCtrl(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSetStreamCtrl\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");

	if (cResult[5] != 0)
	{
		printf("error:%d\n", cResult[5]);
		return false;
	}
*/
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	printf("ConvertSTRING2CJSONSetStreamCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONSendConsoleCmd(CData &oResult, char *cResult)
{
#if 1
    //printf("ConvertSTRING2CJSONSendConsoleCmd\n");
	/*
    for (int i = 0; i < 6; i++)
    {
		printf("%d", cResult[i]);
    }
	printf("\n");
	*/
	if (cResult[5] != 0)
	{
		printf("error:%d\n", cResult[5]);
		return false;
	}
#else 	
    int  iParaLen = (cResult[2] << 8) + cResult[3];
    char *ParaBuf = &cResult[4];
	printf("ConvertSTRING2CJSONSendConsoleCmd Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ConvertParaProcessing(ParaBuf, iParaLen);
#endif 
    return true;
}

bool CAnalyzeParaProc::ConvertSTRING2CJSONGetRecCtrl(CData &oResult, char *cResult, cJSON *videofiles, cJSON *recresult, int StartIndex, int EndIndex)
{
	int ret = true;
	_videofiles = videofiles;
	_recresult = recresult;
	FileStartIndex = StartIndex;
	FileEndIndex = EndIndex;
#if 0
    int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
    printf("ConvertSTRING2CJSONGetRecCtrl\n");
	printf("iRecvLength = %d\n",iRecvLength);
    for (int i = 0; i < iRecvLength; i++)
    {
	    if (i < 4)
	    {
		    printf("%d\n", cResult[i]);
			 //mLogInfo("%d"<<cResult[i]);
	    }
	    else 
	    {
		    printf("%c", cResult[i]);
			 //mLogInfo("%c"<<cResult[i]);
	    }
    }
	printf("\n");
#else 	
    //int  iParaLen = (cResult[2] << 8) + cResult[3];
    //char *ParaBuf = &cResult[4];
	int  iParaLen = (cResult[2] << 16) + (cResult[3] << 8) + cResult[4] + 5 ;
    char *ParaBuf = &cResult[5];
	if(iParaLen == 24 )
	{
		char *Buff = &cResult[5];
		if(!strcmp(Buff,"The search is empty"))
		{
			mLogDebug("ConvertSTRING2CJSONGetRecCtrl cResult[5]="<<Buff<<"iParaLen"<<iParaLen);
			return ret;
		}
	}
	//printf("ConvertSTRING2CJSONGetRecCtrl Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
    ret = AnalyGetRecPara(ParaBuf, iParaLen);
#endif 
    return ret;
}
bool CAnalyzeParaProc::ConvertSTRING2CJSONGetRecordState(CData &oResult, char *cResult, cJSON *videofiles, cJSON *recresult)
{
	_videofiles = videofiles;
	_recresult = recresult;
	
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("ConvertSTRING2CJSONGetHostDecInfo\n");
	
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
		
		int  iParaLen = (cResult[2] << 8) + cResult[3];
		char *ParaBuf = &cResult[4];
		//printf("ConvertSTRING2CJSONGetHostDecInfo Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
		ConvertParaProcessing(ParaBuf, iParaLen);
	
		return true;

}
bool CAnalyzeParaProc::ConvertSTRING2CJSONGetDefRecChns(CData &oResult, char *cResult, int *DefRecChns)
{
	 _arry = DefRecChns;
#if 0
		int iRecvLength = (cResult[2] << 8) + cResult[3] + 4;
		printf("ConvertSTRING2CJSONGetHostDecInfo\n");
	
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
		
		int  iParaLen = (cResult[2] << 8) + cResult[3];
		char *ParaBuf = &cResult[4];
		//printf("ConvertSTRING2CJSONGetHostDecInfo Len %d bufLen %d\n", iParaLen, strlen(ParaBuf));
		ConvertParaProcessing(ParaBuf, iParaLen);
		
		return true;

}
bool CAnalyzeParaProc::ConvertSTRING2CJSONGetParam(CData& oResult, char* cResult, cJSON* result, cJSON* ParamList,cJSON* node[], string Method, string &ip, int ParamNum)
{
	_result = result;
	_ParamList = ParamList;
	_ParamArry = node;
	CMethod = Method;
	int nRespLen = (cResult[2] << 8) + cResult[3];
	char* szRespBuf = &cResult[4];

	//进一步解析响应
#if 0 //XML
	return AnalyGetWebRtspParam(szRespBuf, nRespLen);
#else	

	//解析获得的一组通道的信息
	ConvertParaProcessing(szRespBuf, nRespLen);
	ip = _ip;
	//cJSON_Delete(_taskList);
	return true;

#endif
}
bool CAnalyzeParaProc::ConvertSTRING2CJSONGetWebParam(CData& oResult, char* cResult, cJSON* result, cJSON* ParamList,cJSON* node[], string Method, string &ip, int ParamNum)
{
	_result = result;
	_ParamList = ParamList;
	_ParamArry = node;
	CMethod = Method;
	int nRespLen = (cResult[2] << 8) + cResult[3];
	char* szRespBuf = &cResult[4];

	//进一步解析响应
#if 0 //XML
	return AnalyGetWebRtspParam(szRespBuf, nRespLen);
#else	

	//解析获得的一组通道的信息
	ConvertParaProcessing(szRespBuf, nRespLen);
	ip = _ip;
	//cJSON_Delete(_taskList);
	return true;

#endif
}
bool CAnalyzeParaProc::ConvertSTRING2CJSONGetCwpParam(CData& oResult, char* cResult, cJSON* result, cJSON* ParamList[],cJSON* node[], string Method, string &ip, int ParamNum)
{
	_result = result;
	_PArry = ParamList;
	_ParamArry = node;
	CMethod = Method;
	int nRespLen = (cResult[2] << 8) + cResult[3];
	char* szRespBuf = &cResult[4];
	Param = ParamNum;

	//进一步解析响应
#if 0 //XML
	return AnalyGetWebRtspParam(szRespBuf, nRespLen);
#else	

	//解析获得的一组通道的信息
	ConvertParaProcessing(szRespBuf, nRespLen);
	ip = _ip;
	char httpAddr[128]={0};
	char strosd[128];
		if(ParamNum > 8)
		{			
			for(int i = 0; i < 8; i++)
			{
					memset(httpAddr, 0, 128);
					memset(strosd, 0, 128);
					switch(i)
					{
					case 0:
						sprintf(httpAddr,"http://%s:9696/live/vl1-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 1:
						sprintf(httpAddr,"http://%s:9696/live/vl2-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 2:
						sprintf(httpAddr,"http://%s:9696/live/vl3-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 3:
						sprintf(httpAddr,"http://%s:9696/live/vl4-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 4:
						sprintf(httpAddr,"http://%s:9696/live/vl5-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 5:
						sprintf(httpAddr,"http://%s:9696/live/vl6-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 6:
						sprintf(httpAddr,"http://%s:9696/live/vl7-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					case 7:
						sprintf(httpAddr,"http://%s:9696/live/vl8-1.flv", _ip.c_str());
						cJSON_AddItemToObject(ParamList[i], "HttpUrl", cJSON_CreateString(httpAddr));
						break;
					}
			}
		}
		else
		{
			switch(ParamNum)
			{
			case 1:
				sprintf(httpAddr,"http://%s:9696/live/vl1-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 2:
				sprintf(httpAddr,"http://%s:9696/live/vl2-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 3:
				sprintf(httpAddr,"http://%s:9696/live/vl3-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 4:
				sprintf(httpAddr,"http://%s:9696/live/vl4-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 5:
				sprintf(httpAddr,"http://%s:9696/live/vl5-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 6:
				sprintf(httpAddr,"http://%s:9696/live/vl6-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 7:
				sprintf(httpAddr,"http://%s:9696/live/vl7-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;
			case 8:
				sprintf(httpAddr,"http://%s:9696/live/vl8-1.flv", _ip.c_str());
				cJSON_AddItemToObject(ParamList[ParamNum-1], "HttpUrl", cJSON_CreateString(httpAddr));
				break;

			}	
		}

	return true;

#endif
}


