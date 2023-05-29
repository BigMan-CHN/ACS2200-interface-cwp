TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    cgiAnalysis.h \
    interfaceParams.h \
    interfaceProcess.h \
    InterfaceResponse.h \
    interfaceDefines.h \
    MPSClient.h \
    MPSClientDefine.h \
    method/CAnalyzeParaProc.h \
    method/GetTaskContent.h \
    method/CGetHostStatus.h \
    method/CGetChannelContents.h \
    common/CTimeCvt.h \
    method/CGetSysConfig.h \
    config.h \
    method/CGetHostConfig.h \ 
    method/CGetHostDecInfo.h \
    method/CGetHostChnInfo.h \   
    method/CSetTaskDelete.h \
    method/CSetDecCtrl.h \
    method/CSetOsdCtrl.h \
    method/CSetPutNoteFileCtrl.h \
    method/CSetRecCtrl.h \
    method/CDisciplineCtrl.h \
    method/CStreamCtrl.h \
    method/CSetPowerCtrl.h \
    method/CSendConsoleCmd.h \
    method/CSendSerialCmd.h \
    method/CHostControlDec.h \
    method/CHostControlDiscipline.h \
    method/CHostControl.h \
method/CGetWebMosaicList.h\
method/CSetWebNewMosaic.h\
    method/CSetpoint.h

SOURCES += main.cpp \
    cgiAnalysis.cpp \
    interfaceParams.cpp \
    interfaceProcess.cpp \
    InterfaceResponse.cpp \
    MPSClient.cpp \
    method/GetTaskContent.cpp \
    method/CGetHostStatus.cpp \
    method/CGetChannelContents.cpp \
    common/CTimeCvt.cpp \
    method/CAnalyzeParaProc.cpp \
    method/CGetSysConfig.cpp \
    method/CGetHostConfig.cpp \ 
    method/CGetHostDecInfo.cpp \
    method/CGetHostChnInfo.cpp \
    method/CSetTaskDelete.cpp \
    method/CSetDecCtrl.cpp \
    method/CSetOsdCtrl.cpp \
    method/CSetPutNoteFileCtrl.cpp \
    method/CSetRecCtrl.cpp \
    method/CDisciplineCtrl.cpp \
    method/CStreamCtrl.cpp \
    method/CSetPowerCtrl.cpp \
    method/CSendConsoleCmd.cpp \
    method/CSendSerialCmd.cpp \
    method/CHostControlDec.cpp \
    method/CHostControlDiscipline.cpp \
    method/CHostControl.cpp \
method/CGetWebMosaicList.cpp\
method/CSetWebNewMosaic.cpp\
    method/CSetpoint.cpp

DISTFILES += \
    readMe.txt

#creat .cgi file
TARGET = interface
#TARGET = /var/www/cgi-bin/liveCaster-4

#cgi include
#INCLUDEPATH += /home/MPS/libcgi-1.0/src
#INCLUDEPATH +=/home/xuyf/develop/MPS/sqlite-autoconf-3130000/install/include
#INCLUDEPATH +=/opt/sqlite/include
INCLUDEPATH +=/home/xuyf/develop-hi400/sqlite-autoconf-3380500/installdir/include
#cgi lib
#LIBS += /home/MPS/libcgi-1.0/src/libcgi.a

#log lib
INCLUDEPATH += \
    /home/xuyf/develop-hi400/libcommon_1.69.0/src      \
    /home/xuyf/develop-hi400/libcommon_1.69.0/src/LibXML  \
    /home/xuyf/develop-hi400/libcommon_1.69.0/src/LibTransmit \
    /home/xuyf/develop-hi400/libMLog \
    /home/xuyf/develop-hi400/log4cplus-1.2.1/include \
    /home/xuyf/develop-hi400/cJSONFiles/cJSON
#log lib
LIBS += \
    /home/xuyf/develop-hi400/libcommon_1.69.0/src/LibTransmit/qt600/tarnsmitv600/libtransmit.a  \
    /home/xuyf/develop-hi400/libMLog/libMLog.a \
    /home/xuyf/develop-hi400/log4cplus-1.2.1/installdir/lib/liblog4cplus.a \
    /home/xuyf/develop-hi400/cJSONFiles/cJSON/CJSON/libCJSON.a \

LIBS += /home/xuyf/develop-hi400/libcommon_1.69.0/src/LibXML/qtv600/xmlv600/libxml.a

#SQLite3 lib
#LIBS +=/home/xuyf/develop/MPS/sqlite-autoconf-3130000/install/lib/libsqlite3.a
LIBS +=/home/xuyf/develop-hi400/sqlite-autoconf-3380500/installdir/lib/libsqlite3.a
#boost include
INCLUDEPATH +=/home/xuyf/develop-hi400/boost_1_69_0

#boost lib
LIBS += /home/xuyf/develop-hi400/boost_1_69_0/installdir/lib/libboost_system.a
LIBS += /home/xuyf/develop-hi400/boost_1_69_0/installdir/lib/libboost_thread.a
LIBS += /home/xuyf/develop-hi400/boost_1_69_0/installdir/lib/libboost_filesystem.a
LIBS +=  \
    -lrt \
    -lpthread \
    -ldl
DEFINES -= UNICODE
