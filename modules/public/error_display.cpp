/**
 *******************************************************************************
 * @file    error_display.cpp
 * @author  JunChao.Yuan
 * @version V1.1.2
 * @date    2019.09.24
 * @brief   错误码显示库文件
 *******************************************************************************
 * 可改进的地方：
 *  2.统一用QDebug进行错误输出
  * 3.启动程序调试信息输出程序版本和程序最后修改时间
 */

#include "error_display.h"

#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>


QMutex ErrorDisplay::std_log_mutex;
QMutex ErrorDisplay::custom_log_mutex;

ErrorDisplay::ErrorDisplay()
{}

int ErrorDisplay::GetErrorBaseType(int error_code)
{
    return (error_code & ERROR_BASE_MASK);
}

int ErrorDisplay::GetErrorBaseCode(int error_code)
{
    return (error_code & ERROR_CODE_MASK);
}

QString ErrorDisplay::GetErrorInfo(int error_code, int display_mode)
{
    QString text;
    QString error_desp = GetErrorDescription(error_code);
    QString error_type = GetErrorTypeName(error_code);
    QString error_code_str = GetErrorCodeString(error_code);
    switch (display_mode)
    {
        case 0:
        {
            //tr:%1：错误码：%2
            text = QString(tr("%1: error code: %2")).arg(error_type, error_code_str);
            break;
        }
        case 1:
        {
            //tr:%1：错误描述：%2
            text = QString(tr("%1: error description: %2"))
                   .arg(error_type, error_desp);
            break;
        }
        case 2:
        {
            //tr:%1：错误码：%2，错误描述：%3
            text = QString(tr("%1: error code: %2, error description: %3"))
                   .arg(error_type, error_code_str, error_desp);
            break;
        }
        case 3:
        {
            //tr:错误码：%1，错误描述：%2
            text = QString(tr("error code: %1, error description: %2"))
                   .arg(error_code_str, error_desp);
            break;
        }
        case 4:
        {
            //只返回错误描述信息
            text = error_desp;
            break;
        }
    }
    return text;
}

QString ErrorDisplay::GetErrorInfo(int error_code, bool with_prefix,
                                   bool with_descrip, bool with_type)
{
    QString text;
    if (with_type)
    {
        if (with_prefix)
        {
            //tr:错误类型：
            text += tr("error type: ");
        }
        text += GetErrorTypeName(error_code);
    }

    if (with_prefix)
    {
        //tr:错误码：
        text += tr("error code: ");
    }
    text += GetErrorCodeString(error_code);

    if (with_descrip)
    {
        if (with_prefix)
        {
            //tr:错误描述：
            text += tr("error description: ");
        }
        text += GetErrorDescription(error_code);
    }
    return text;
}

QString ErrorDisplay::GetErrorCodeString(int error_code)
{
    if (error_code == NO_ERROR)
    {
        return "0";
    }

    QString temp = QString("%1").arg(error_code, 0, 16, QChar('0')).toUpper();
    QString section = temp.section("EE", 1);
    if (section.isEmpty())
    {
        qDebug() << "未知错误码:" + temp;
        section = "???";
    }
    return "0xEE" + section;
}

int64_t ErrorDisplay::GetErrorCodeFromString(QString error_code)
{
    if (error_code.isEmpty())
    {
        qDebug() << "GetErrorCodeFromString: error_code is empty!";
        return -1;
    }

    bool ok_flag = false;
    int64_t value = error_code.toLongLong(&ok_flag, 16);
    if (!ok_flag)
    {
        qDebug() << QString("GetErrorCodeFromString: value(%1) toLongLong failed!")
                 .arg(error_code);
        return -1;
    }
    return value;
}

QString ErrorDisplay::GetErrorTypeName(int error_code)
{
    int base_type = GetErrorBaseType(error_code);
    switch (base_type)
    {
        case NO_ERROR:
            return tr("NO_ERROR");
        case ERROR_NETWORK_BASE:
            return tr("ERROR_NETWORK_BASE");
        case ERROR_NETFILE_BASE:
            return tr("ERROR_NETFILE_BASE");
        case ERROR_QSOCKET_BASE:
            return tr("ERROR_QSOCKET_BASE");
        //tr:未知错误类型
        default:
            return tr("ERROR_UNKNOWN_ERROR_TYPE_BASE");
    }
}

QString ErrorDisplay::GetErrorDescription(int error_code)
{
    switch (error_code)
    {
        case NO_ERROR:
            return tr("NO_ERROR");
        case ERROR_AIUI_MSP_INVALID_PARA:
            return tr("ERROR_AIUI_MSP_INVALID_PARA");
        case ERROR_AIUI_MSP_INVALID_PARA_VALUE:
            return tr("ERROR_AIUI_MSP_INVALID_PARA_VALUE");
        case ERROR_AIUI_MSP_NOT_FOUND:
            return tr("ERROR_AIUI_MSP_NOT_FOUND");
        case ERROR_AIUI_NO_RESPONSE_DATA:
            return tr("ERROR_AIUI_NO_RESPONSE_DATA");
        case ERROR_AIUI_MSP_LMOD_RUNTIME_EXCEPTION:
            return tr("ERROR_AIUI_MSP_LMOD_RUNTIME_EXCEPTION");
        case ERROR_AIUI_NO_NETWORK:
            return tr("ERROR_AIUI_NO_NETWORK");
        case ERROR_AIUI_NETWORK_TIMEOUT:
            return tr("ERROR_AIUI_NETWORK_TIMEOUT");
        case ERROR_AIUI_NET_EXPECTION:
            return tr("ERROR_AIUI_NET_EXPECTION");
        case ERROR_AIUI_INVALID_RESULT:
            return tr("ERROR_AIUI_INVALID_RESULT");
        case ERROR_AIUI_NO_MATCH:
            return tr("ERROR_AIUI_NO_MATCH");
        case ERROR_AIUI_AUDIO_RECORD:
            return tr("ERROR_AIUI_AUDIO_RECORD");
        case ERROR_AIUI_COMPONENT_NOT_INSTALLED:
            return tr("ERROR_AIUI_COMPONENT_NOT_INSTALLED");
        case ERROR_AIUI_SERVICE_BINDER_DIED:
            return tr("ERROR_AIUI_SERVICE_BINDER_DIED");
        case ERROR_AIUI_LOCAL_NO_INIT:
            return tr("ERROR_AIUI_LOCAL_NO_INIT");
        case ERROR_AIUI_UNKNOWN:
            return tr("ERROR_AIUI_UNKNOWN");
        case ERROR_NETWORK_BASE:
            return tr("ERROR_NETWORK_BASE");
        case ERROR_NETWORK_DISCONNECTED:
            return tr("ERROR_NETWORK_DISCONNECTED");
        case ERROR_NETWORK_HEAD_NOT_MATCH:
            return tr("ERROR_NETWORK_HEAD_NOT_MATCH");
        case ERROR_NETWORK_UUID_NOT_MATH:
            return tr("ERROR_NETWORK_UUID_NOT_MATH");
        case ERROR_NETWORK_UNKNOW_CMAD:
            return tr("ERROR_NETWORK_UNKNOW_CMAD");
        case ERROR_NETWORK_REQUEST_REJECT:
            return tr("ERROR_NETWORK_REQUEST_REJECT");
        case ERROR_NETWORK_RESEND_OVERTIMES:
            return tr("ERROR_NETWORK_RESEND_OVERTIMES");
        case ERROR_NETWORK_COMMU_REFUSE:
            return tr("ERROR_NETWORK_COMMU_REFUSE");
        case ERROR_NETWORK_HEAD_NOT_VAILD:
            return tr("ERROR_NETWORK_HEAD_NOT_VAILD");

        case ERROR_NETFILE_BASE:
            return tr("ERROR_NETFILE_BASE");
        case ERROR_NETFILE_DISCONNECTED:
            return tr("ERROR_NETFILE_DISCONNECTED");
        case ERROR_NETFILE_DIR_CREATE:
            return tr("ERROR_NETFILE_DIR_CREATE");
        case ERROR_NETFILE_SEND_FILE_NOT_EXIST:
            return tr("ERROR_NETFILE_SEND_FILE_NOT_EXIST");
        case ERROR_NETFILE_SEND_FILE_OPEN:
            return tr("ERROR_NETFILE_SEND_FILE_OPEN");
        case ERROR_NETFILE_SEND_CONTENT:
            return tr("ERROR_NETFILE_SEND_CONTENT");
        case ERROR_NETFILE_SEND_NOT_MATCH:
            return tr("ERROR_NETFILE_SEND_NOT_MATCH");
        case ERROR_NETFILE_FILE_NOT_READABLE:
            return tr("ERROR_NETFILE_FILE_NOT_READABLE");
        case ERROR_NETFILE_RECV_FILE_NOT_EXIST:
            return tr("ERROR_NETFILE_RECV_FILE_NOT_EXIST");
        case ERROR_NETFILE_RECV_FILE_OPEN:
            return tr("ERROR_NETFILE_RECV_FILE_OPEN");
        case ERROR_NETFILE_RECV_CONTENT:
            return tr("ERROR_NETFILE_RECV_CONTENT");
        case ERROR_NETFILE_RECV_NOT_MATCH:
            return tr("ERROR_NETFILE_RECV_NOT_MATCH");
        case ERROR_NETFILE_FILE_NOT_WRITABLE:
            return tr("ERROR_NETFILE_FILE_NOT_WRITABLE");
        case ERROR_NETFILE_RECV_SIZE_NOT_MATCH:
            return tr("ERROR_NETFILE_RECV_SIZE_NOT_MATCH");
        case ERROR_NETFILE_RECV_UUID_NOT_MATCH:
            return tr("ERROR_NETFILE_RECV_UUID_NOT_MATCH");

        case ERROR_NETFILE_WRITE_SOCKET:
            return tr("ERROR_NETFILE_WRITE_SOCKET");


        case ERROR_QSOCKET_BASE:
            return tr("ERROR_QSOCKET_BASE");
        case ERROR_QSOCKET_FILE:
            return tr("ERROR_QSOCKET_FILE");
        case ERROR_QSOCKET_REMOTE_HOST_CLOSE:
            return tr("ERROR_QSOCKET_REMOTE_HOST_CLOSE");
        case ERROR_QSOCKET_HOST_NOT_FOUND:
            return tr("ERROR_QSOCKET_HOST_NOT_FOUND");
        case ERROR_QSOCKET_ACCESS:
            return tr("ERROR_QSOCKET_ACCESS");
        case ERROR_QSOCKET_SOURCE_RAN_OUT:
            return tr("ERROR_QSOCKET_SOURCE_RAN_OUT");
        case ERROR_QSOCKET_TIMEOUT:
            return tr("ERROR_QSOCKET_TIMEOUT");
        case ERROR_QSOCKET_DATAGRAM_TOO_LARGE:
            return tr("ERROR_QSOCKET_DATAGRAM_TOO_LARGE");
        case ERROR_QSOCKET_NETWORK:
            return tr("ERROR_QSOCKET_NETWORK");
        case ERROR_QSOCKET_ACCESS_IN_USE:
            return tr("ERROR_QSOCKET_ACCESS_IN_USE");
        case ERROR_QSOCKET_ADDR_NOT_AVAILABLE:
            return tr("ERROR_QSOCKET_ADDR_NOT_AVAILABLE");
        case ERROR_QSOCKET_UNSUPPORT_OPERATION:
            return tr("ERROR_QSOCKET_UNSUPPORT_OPERATION");
        case ERROR_QSOCKET_PROXY_AUT_REQ:
            return tr("ERROR_QSOCKET_PROXY_AUT_REQ");
        case ERROR_QSOCKET_SSL_HANDSHAKE:
            return tr("ERROR_QSOCKET_SSL_HANDSHAKE");
        case ERROR_QSOCKET_UNFINISHED_OPERATION:
            return tr("ERROR_QSOCKET_UNFINISHED_OPERATION");
        case ERROR_QSOCKET_PROXY_CONNECT_REFUSE:
            return tr("ERROR_QSOCKET_PROXY_CONNECT_REFUSE");
        case ERROR_QSOCKET_PROXY_CONNECT_CLOSE:
            return tr("ERROR_QSOCKET_PROXY_CONNECT_CLOSE");
        case ERROR_QSOCKET_PROXY_CONNECT_TIMEOUT:
            return tr("ERROR_QSOCKET_PROXY_CONNECT_TIMEOUT");
        case ERROR_QSOCKET_PROXY_NOT_FOUND:
            return tr("ERROR_QSOCKET_PROXY_NOT_FOUND");
        case ERROR_QSOCKET_PROXY_PROTOCOL:
            return tr("ERROR_QSOCKET_PROXY_PROTOCOL");
        case ERROR_QSOCKET_OPERATION:
            return tr("ERROR_QSOCKET_OPERATION");
        case ERROR_QSOCKET_SSL_INTERNAL:
            return tr("ERROR_QSOCKET_SSL_INTERNAL");
        case ERROR_QSOCKET_SSL_INVALID_USER_DATA:
            return tr("ERROR_QSOCKET_SSL_INVALID_USER_DATA");
        case ERROR_QSOCKET_TEMPORARY:
            return tr("ERROR_QSOCKET_TEMPORARY");
        case ERROR_QSOCKET_UNKNOW:
            return tr("ERROR_QSOCKET_UNKNOW");
        case ERROR_QSOCKET_WRITE:
            return tr("ERROR_QSOCKET_WRITE");


        case ERROR_QSQL_BASE:
            return tr("ERROR_QSQL_BASE");
        case ERROR_QSQL_UPDATE:
            return tr("ERROR_QSQL_UPDATE");
        case ERROR_QSQL_DELETE:
            return tr("ERROR_QSQL_DELETE");
        case ERROR_QSQL_CREATE:
            return tr("ERROR_QSQL_CREATE");
        case ERROR_QSQL_SELECT:
            return tr("ERROR_QSQL_SELECT");
        case ERROR_QSQL_OPEN:
            return tr("ERROR_QSQL_OPEN");
        case ERROR_QSQL_INSERT:
            return tr("ERROR_QSQL_INSERT");
        case ERROR_QSQL_EMPTY:
            return tr("ERROR_QSQL_EMPTY");


        case ERROR_SETTING_FILE_BASE:
            return tr("ERROR_SETTING_FILE_BASE");
        case ERROR_SETTING_FILE_NOT_LOAD:
            return tr("ERROR_SETTING_FILE_NOT_LOAD");

        //tr:未知错误描述
        default:
            return tr("ERROR_UNKNOWN_DESCRIPTION");
    }
}


void ErrorDisplay::OutputMessageToFile(const QString log_file_path,
                                       const QString& message)
{
    custom_log_mutex.lock();
    QString current_date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString current_time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString output_content = QString("\"%1 %2\" | %3")
                             .arg(current_date, current_time, message);
    QFile file(log_file_path);
    bool result = file.open(QIODevice::WriteOnly | QIODevice::Append |
                            QIODevice::Text);
    if (result == true)
    {
        QTextStream text_stream(&file);
        text_stream << output_content << endl;
        file.flush();
        file.close();
    }
    else
    {
        qDebug() << QString("Create Custom Output Mseeage File(%1) Failed！")
                 .arg(log_file_path);
    }
    custom_log_mutex.unlock();
}
