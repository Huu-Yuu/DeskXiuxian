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

#include "public/error_display.h"

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
        case ERROR_COMMON_BASE:
            return tr("ERROR_COMMON_BASE");
        case ERROR_CAMERA_BASE:
            return tr("ERROR_CAMERA_BASE");
        case ERROR_RECORD_BASE:
            return tr("ERROR_RECORD_BASE");
        case ERROR_ICCARD_BASE:
            return tr("ERROR_ICCARD_BASE");
        case ERROR_SERIAL_BASE:
            return tr("ERROR_SERIAL_BASE");
        case ERROR_GPIO_BASE:
            return tr("ERROR_GPIO_BASE");
        case ERROR_MOVEMENT_BASE:
            return tr("ERROR_MOVEMENT_BASE");
        case ERROR_PRINTER_BASE:
            return tr("ERROR_PRINTER_BASE");
        case ERROR_IDCARD_BASE:
            return tr("ERROR_IDCARD_BASE");
        case ERROR_KINECT_BASE:
            return tr("ERROR_KINECT_BASE");
        case ERROR_RING_BASE:
            return tr("ERROR_RING_BASE");
        case ERROR_TTS_BASE:
            return tr("ERROR_TTS_BASE");
        case ERROR_FINGER_BASE:
            return tr("ERROR_FINGER_BASE");
        case ERROR_SCANNER_BASE:
            return tr("ERROR_SCANNER_BASE");
        case ERROR_FACE_BASE:
            return tr("ERROR_FACE_BASE");
        case ERROR_LOCK_BASE:
            return tr("ERROR_LOCK_BASE");
        case ERROR_AIUI_BASE:
            return tr("ERROR_AIUI_BASE");
        case ERROR_BLE_BASE:
            return tr("ERROR_BLE_BASE");
        case ERROR_WIRELESS_AUDIO_BASE:
            return tr("ERROR_WIRELESS_AUDIO_BASE");
        case ERROR_VERIFY_BASE:
            return tr("ERROR_VERIFY_BASE");
        case ERROR_DOOR_CTRL_BASE:
            return tr("ERROR_DOOR_CTRL_BASE");
        case ERROR_MEDIA_BASE:
            return tr("ERROR_MEDIA_BASE");
        case ERROR_VIDEO_BASE:
            return tr("ERROR_VIDEO_BASE");
        case ERROR_REALSENSE_BASE:
            return tr("ERROR_REALSENSE_BASE");
        case ERROR_UV_LIGHT_BASE:
            return tr("ERROR_UV_LIGHT_BASE");
        case ERROR_CABINET_BASE:
            return tr("ERROR_CABINET_BASE");
        case ERROR_MAIN_BASE:
            return tr("ERROR_MAIN_BASE");
        case ERROR_NETWORK_BASE:
            return tr("ERROR_NETWORK_BASE");
        case ERROR_NETFILE_BASE:
            return tr("ERROR_NETFILE_BASE");
        case ERROR_QSOCKET_BASE:
            return tr("ERROR_QSOCKET_BASE");
        case ERROR_BASE64_BASE:
            return tr("ERROR_BASE64_BASE");
        case ERROR_PUBLIC_THREAD_BASE:
            return tr("ERROR_PUBLIC_THREAD_BASE");
        case ERROR_GZIP_BASE:
            return tr("ERROR_GZIP_BASE");
        case ERROR_HTTP_BASE:
            return tr("ERROR_HTTP_BASE");
        case ERROR_VIEW_BASE:
            return tr("ERROR_VIEW_BASE");
        case ERROR_XUNFEI_BASE:
            return tr("ERROR_XUNFEI_BASE");
        case ERROR_NMCLI_BASE:
            return tr("ERROR_NMCLI_BASE");
        case ERROR_SYSTEM_BASE:
            return tr("ERROR_SYSTEM_BASE");
        case ERROR_FILE_BASE:
            return tr("ERROR_FILE_BASE");
        case ERROR_DIR_BASE:
            return tr("ERROR_DIR_BASE");
        case ERROR_ICONV_BASE:
            return tr("ERROR_ICONV_BASE");
        case ERROR_IOCTL_BASE:
            return tr("ERROR_IOCTL_BASE");
        case ERROR_FFMPEG_BASE:
            return tr("ERROR_FFMPEG_BASE");
        case ERROR_QSQL_BASE:
            return tr("ERROR_QSQL_BASE");
        case ERROR_SETTING_FILE_BASE:
            return tr("ERROR_SETTING_FILE_BASE");
        case ERROR_LIFT_CTRL_BASE:
            return tr("ERROR_LIFT_CTRL_BASE");
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


        case ERROR_COMMON_BASE:
            return tr("ERROR_COMMON_BASE");
        case ERROR_COMMON_PARAM_EMPTY:
            return tr("ERROR_COMMON_PARAM_EMPTY");
        case ERROR_COMMON_PARAM_NOT_SUPPORT:
            return tr("ERROR_COMMON_PARAM_NOT_SUPPORT");
        case ERROR_COMMON_PARAM_INVAILD:
            return tr("ERROR_COMMON_PARAM_INVAILD");
        case ERROR_COMMON_OPEN:
            return tr("ERROR_COMMON_OPEN");
        case ERROR_COMMON_LOGIC:
            return tr("ERROR_COMMON_LOGIC");
        case ERROR_COMMON_PARAM_EXCEED:
            return tr("ERROR_COMMON_PARAM_EXCEED");


        case ERROR_CAMERA_BASE:
            return tr("ERROR_CAMERA_BASE");
        case ERROR_CAMERA_OPEN:
            return tr("ERROR_CAMERA_OPEN");
        case ERROR_CAMERA_CLOSE:
            return tr("ERROR_CAMERA_CLOSE");
        case ERROR_CAMERA_GET_DEV_INFO:
            return tr("ERROR_CAMERA_GET_DEV_INFO");
        case ERROR_CAMERA_TYPE:
            return tr("ERROR_CAMERA_TYPE");
        case ERROR_CAMERA_NOT_CAPTURE_DEV:
            return tr("ERROR_CAMERA_NOT_CAPTURE_DEV");
        case ERROR_CAMERA_NOT_STREAM_DEV:
            return tr("ERROR_CAMERA_NOT_STREAM_DEV");
        case ERROR_CAMERA_GET_INPUT_INDEX:
            return tr("ERROR_CAMERA_GET_INPUT_INDEX");
        case ERROR_CAMERA_INPUT_SELECT:
            return tr("ERROR_CAMERA_INPUT_SELECT");
        case ERROR_CAMERA_CHECK_FORMAT:
            return tr("ERROR_CAMERA_CHECK_FORMAT");
        case ERROR_CAMERA_GET_FORMAT:
            return tr("ERROR_CAMERA_GET_FORMAT");
        case ERROR_CAMERA_SET_FORMAT:
            return tr("ERROR_CAMERA_SET_FORMAT");
        case ERROR_CAMERA_MMAP_NOT_SUPPORT:
            return tr("ERROR_CAMERA_MMAP_NOT_SUPPORT");
        case ERROR_CAMERA_REQ_BUFF:
            return tr("ERROR_CAMERA_REQ_BUFF");
        case ERROR_CAMERA_INSUFFICIENT_MEM:
            return tr("ERROR_CAMERA_INSUFFICIENT_MEM");
        case ERROR_CAMERA_MEM_MAP:
            return tr("ERROR_CAMERA_MEM_MAP");
        case ERROR_CAMERA_ENQUEUE:
            return tr("ERROR_CAMERA_ENQUEUE");
        case ERROR_CAMERA_DEQUEUE:
            return tr("ERROR_CAMERA_DEQUEUE");
        case ERROR_CAMERA_STREAM_START:
            return tr("ERROR_CAMERA_STREAM_START");
        case ERROR_CAMERA_STREAM_END:
            return tr("ERROR_CAMERA_STREAM_END");
        case ERROR_CAMERA_MEM_UNMAP:
            return tr("ERROR_CAMERA_MEM_UNMAP");
        case ERROR_CAMERA_THREAD_CREATE:
            return tr("ERROR_CAMERA_THREAD_CREATE");
        case ERROR_CAMERA_PARAM_NULL:
            return tr("ERROR_CAMERA_PARAM_NULL");
        case ERROR_CAMERA_GET_FRAME_TIMEOUT:
            return tr("ERROR_CAMERA_GET_FRAME_TIMEOUT");
        case ERROR_CAMERA_GET_FRAME:
            return tr("ERROR_CAMERA_GET_FRAME");
        case ERROR_CAMERA_GENERATE_PIC:
            return tr("ERROR_CAMERA_GENERATE_PIC");
        case ERROR_CAMERA_NOT_OPEN:
            return tr("ERROR_CAMERA_NOT_OPEN");
        case ERROR_CAMERA_STORE_PATH_EMPTY:
            return tr("ERROR_CAMERA_STORE_PATH_EMPTY");
        case ERROR_CAMERA_OPEN_TYPE_CABINET:
            return tr("ERROR_CAMERA_OPEN_TYPE_CABINET");
        case ERROR_CAMERA_OPEN_TYPE_FRONT:
            return tr("ERROR_CAMERA_OPEN_TYPE_FRONT");
        case ERROR_CAMERA_OPEN_TYPE_BACK:
            return tr("ERROR_CAMERA_OPEN_TYPE_BACK");
        case ERROR_CAMERA_SET_FORMAT_TYPE_CABINET:
            return tr("ERROR_CAMERA_SET_FORMAT_TYPE_CABINET");
        case ERROR_CAMERA_SET_FORMAT_TYPE_FRONT:
            return tr("ERROR_CAMERA_SET_FORMAT_TYPE_FRONT");
        case ERROR_CAMERA_SET_FORMAT_TYPE_BACK:
            return tr("ERROR_CAMERA_SET_FORMAT_TYPE_BACK");


        case ERROR_RECORD_BASE:
            return tr("ERROR_RECORD_BASE");
        case ERROR_RECORD_INVALID_FORMAT:
            return tr("ERROR_RECORD_INVALID_FORMAT");
        case ERROR_RECORD_OPERATION:
            return tr("ERROR_RECORD_OPERATION");
        case ERROR_RECORD_OPEN_FILE:
            return tr("ERROR_RECORD_OPEN_FILE");
        case ERROR_RECORD_OPEN_PCM_DEV:
            return tr("ERROR_RECORD_OPEN_PCM_DEV");
        case ERROR_RECORD_NOT_STD_WAV:
            return tr("ERROR_RECORD_NOT_STD_WAV");
        case ERROR_RECORD_GET_WAV_HEADER:
            return tr("ERROR_RECORD_GET_WAV_HEADER");
        case ERROR_RECORD_PLAY_WAV:
            return tr("ERROR_RECORD_PLAY_WAV");
        case ERROR_RECORD_DEV_BUSY:
            return tr("ERROR_RECORD_DEV_BUSY");
        case ERROR_RECORD_WRITE_WAV:
            return tr("ERROR_RECORD_WRITE_WAV");
        case ERROR_RECORD_READ_PCM_DATA:
            return tr("ERROR_RECORD_READ_PCM_DATA");
        case ERROR_RECORD_THREAD_CREATE:
            return tr("ERROR_RECORD_THREAD_CREATE");
        case ERROR_RECORD_CALLOC:
            return tr("ERROR_RECORD_CALLOC");
        case ERROR_RECORD_PARAM_NULL:
            return tr("ERROR_RECORD_PARAM_NULL");
        case ERROR_RECORD_LARGE_BUFF_FULL:
            return tr("ERROR_RECORD_LARGE_BUFF_FULL");
        case ERROR_RECORD_THREAD_BUSY:
            return tr("ERROR_RECORD_THREAD_BUSY");
        case ERROR_RECORD_MIXER_OPEN:
            return tr("ERROR_RECORD_MIXER_OPEN");
        case ERROR_RECORD_SMALL_BUFF_OVERFLOW:
            return tr("ERROR_RECORD_SMALL_BUFF_OVERFLOW");
        case ERROR_RECORD_JUDGE_COUNT_INVALID:
            return tr("ERROR_RECORD_JUDGE_COUNT_INVALID");
        case ERROR_RECORD_DEV_NOT_INIT:
            return tr("ERROR_RECORD_DEV_NOT_INIT");
        case ERROR_RECORD_LEVEL_NOT_OBVIOUS:
            return tr("ERROR_RECORD_LEVEL_NOT_OBVIOUS");
        case ERROR_RECORD_WRITE_SETTING_FILE:
            return tr("ERROR_RECORD_WRITE_SETTING_FILE");
        case ERROR_RECORD_READ_SETTING_FILE:
            return tr("ERROR_RECORD_READ_SETTING_FILE");
        case ERROR_RECORD_SETTING_FILE_NOT_EXIST:
            return tr("ERROR_RECORD_SETTING_FILE_NOT_EXIST");
        case ERROR_RECORD_SETTING_FILE_NOT_MATCH:
            return tr("ERROR_RECORD_SETTING_FILE_NOT_MATCH");
        case ERROR_RECORD_DEV_OPEN:
            return tr("ERROR_RECORD_DEV_OPEN");
        case ERROR_RECORD_DEV_NOT_OPEN:
            return tr("ERROR_RECORD_DEV_NOT_OPEN");
        case ERROR_RECORD_DEV_RESPON:
            return tr("ERROR_RECORD_DEV_RESPON");
        case ERROR_RECORD_DEV_INVAILD_PARAM:
            return tr("ERROR_RECORD_DEV_INVAILD_PARAM");
        case ERROR_RECORD_THREAD_LOCK_INIT:
            return tr("ERROR_RECORD_THREAD_LOCK_INIT");


        case ERROR_ICCARD_BASE:
            return tr("ERROR_ICCARD_BASE");
        case ERROR_ICCARD_OPT_SUCC:
            return tr("ERROR_ICCARD_OPT_SUCC");
        case ERROR_ICCARD_OPT:
            return tr("ERROR_ICCARD_OPT");
        case ERROR_ICCARD_LOW_POWSUPP:
            return tr("ERROR_ICCARD_LOW_POWSUPP");
        case ERROR_ICCARD_UNDEFINE_CMAD:
            return tr("ERROR_ICCARD_UNDEFINE_CMAD");
        case ERROR_ICCARD_INVALD_PARM:
            return tr("ERROR_ICCARD_INVALD_PARM");
        case ERROR_ICCARD_CAN_NOT_EXEC:
            return tr("ERROR_ICCARD_CAN_NOT_EXEC");
        case ERROR_ICCARD_DATA:
            return tr("ERROR_ICCARD_DATA");
        case ERROR_ICCARD_ENTER_TIMEOUT:
            return tr("ERROR_ICCARD_ENTER_TIMEOUT");
        case ERROR_ICCARD_WRONG_CARD:
            return tr("ERROR_ICCARD_WRONG_CARD");
        case ERROR_ICCARD_NO_CARD_ABOVE:
            return tr("ERROR_ICCARD_NO_CARD_ABOVE");
        case ERROR_ICCARD_NO_CARD_IN:
            return tr("ERROR_ICCARD_NO_CARD_IN");
        case ERROR_ICCARD_NO_RESET_RESPON:
            return tr("ERROR_ICCARD_NO_RESET_RESPON");
        case ERROR_ICCARD_CHECK_KEY:
            return tr("ERROR_ICCARD_CHECK_KEY");
        case ERROR_ICCARD_WRITE_CARD:
            return tr("ERROR_ICCARD_WRITE_CARD");
        case ERROR_ICCARD_CPU_EX_DATA:
            return tr("ERROR_ICCARD_CPU_EX_DATA");
        case ERROR_ICCARD_SAM_COMMU:
            return tr("ERROR_ICCARD_SAM_COMMU");
        case ERROR_ICCARD_DEV_OPEN:
            return tr("ERROR_ICCARD_DEV_OPEN");
        case ERROR_ICCARD_DEV_NOT_OPEN:
            return tr("ERROR_ICCARD_DEV_NOT_OPEN");
        case ERROR_ICCARD_DEV_CLOSE:
            return tr("ERROR_ICCARD_DEV_CLOSE");
        case ERROR_ICCARD_READ_CAED_TIMEOUT:
            return tr("ERROR_ICCARD_READ_CAED_TIMEOUT");
        case ERROR_ICCARD_INVALID_CARD_MODE:
            return tr("ERROR_ICCARD_INVALID_CARD_MODE");
        case ERROR_ICCARD_RECV_DATA_INVALID:
            return tr("ERROR_ICCARD_RECV_DATA_INVALID");
        case ERROR_ICCARD_CRC:
            return tr("ERROR_ICCARD_CRC");
        case ERROR_ICCARD_DATA_OVERFLOW:
            return tr("ERROR_ICCARD_DATA_OVERFLOW");
        case ERROR_ICCARD_AUTHENTICATE:
            return tr("ERROR_ICCARD_AUTHENTICATE");
        case ERROR_ICCARD_PARITY:
            return tr("ERROR_ICCARD_PARITY");
        case ERROR_ICCARD_CODE:
            return tr("ERROR_ICCARD_CODE");
        case ERROR_ICCARD_SERIAL_NUMBER:
            return tr("ERROR_ICCARD_SERIAL_NUMBER");
        case ERROR_ICCARD_NOT_AUTHENTICATE:
            return tr("ERROR_ICCARD_NOT_AUTHENTICATE");
        case ERROR_ICCARD_BIT_COUNT:
            return tr("ERROR_ICCARD_BIT_COUNT");
        case ERROR_ICCARD_BYTE_COUNT:
            return tr("ERROR_ICCARD_BYTE_COUNT");
        case ERROR_ICCARD_TRANSFER:
            return tr("ERROR_ICCARD_TRANSFER");
        case ERROR_ICCARD_INCREMENT:
            return tr("ERROR_ICCARD_INCREMENT");
        case ERROR_ICCARD_DECREMENT:
            return tr("ERROR_ICCARD_DECREMENT");
        case ERROR_ICCARD_READ:
            return tr("ERROR_ICCARD_READ");
        case ERROR_ICCARD_HIGH_LEVEL_COMPARE:
            return tr("ERROR_ICCARD_HIGH_LEVEL_COMPARE");
        case ERROR_ICCARD_HIGH_LEVEL_STRUCT:
            return tr("ERROR_ICCARD_HIGH_LEVEL_STRUCT");
        case ERROR_ICCARD_CMAD:
            return tr("ERROR_ICCARD_CMAD");
        case ERROR_ICCARD_NO_MATCH:
            return tr("ERROR_ICCARD_NO_MATCH");
        case ERROR_ICCARD_SUM:
            return tr("ERROR_ICCARD_SUM");
        case ERROR_ICCARD_CPU_OR_SAM_POEWER_DOWN:
            return tr("ERROR_ICCARD_CPU_OR_SAM_POEWER_DOWN");
        case ERROR_ICCARD_VERIFY_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_VERIFY_SPECIFIED_BLOCK");
        case ERROR_ICCARD_READ_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_READ_SPECIFIED_BLOCK");
        case ERROR_ICCARD_WRITE_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_WRITE_SPECIFIED_BLOCK");
        case ERROR_ICCARD_DECREASE_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_DECREASE_SPECIFIED_BLOCK");
        case ERROR_ICCARD_INCREASE_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_INCREASE_SPECIFIED_BLOCK");
        case ERROR_ICCARD_RESET_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_RESET_SPECIFIED_BLOCK");
        case ERROR_ICCARD_BACKUP_SPECIFIED_BLOCK:
            return tr("ERROR_ICCARD_BACKUP_SPECIFIED_BLOCK");
        case ERROR_ICCARD_WRITE_KEY_TO_CHIP:
            return tr("ERROR_ICCARD_WRITE_KEY_TO_CHIP");
        case ERROR_ICCARD_VERIFY_SPECIFIED_BLOCK_TEMP:
            return tr("ERROR_ICCARD_VERIFY_SPECIFIED_BLOCK_TEMP");
        case ERROR_ICCARD_SET_PASSWORD_AND_PROP:
            return tr("ERROR_ICCARD_SET_PASSWORD_AND_PROP");
        case ERROR_ICCARD_VALUE_BLOCK_FROMAT:
            return tr("ERROR_ICCARD_VALUE_BLOCK_FROMAT");
        case ERROR_ICCARD_OPERATE_VALUE_INVALID:
            return tr("ERROR_ICCARD_OPERATE_VALUE_INVALID");
        case ERROR_ICCARD_INCREASE_OVERFLOW:
            return tr("ERROR_ICCARD_INCREASE_OVERFLOW");
        case ERROR_ICCARD_CARD_RESPON_TIMEOUT:
            return tr("ERROR_ICCARD_CARD_RESPON_TIMEOUT");
        case ERROR_ICCARD_BROKEN_OR_NONE_IC:
            return tr("ERROR_ICCARD_BROKEN_OR_NONE_IC");
        case ERROR_ICCARD_EXCHANGE_APDU:
            return tr("ERROR_ICCARD_EXCHANGE_APDU");


        case ERROR_SERIAL_BASE:
            return tr("ERROR_SERIAL_BASE");
        case ERROR_SERIAL_OPEN:
            return tr("ERROR_SERIAL_OPEN");
        case ERROR_SERIAL_SET_SPEED:
            return tr("ERROR_SERIAL_SET_SPEED");
        case ERROR_SERIAL_SETOWN:
            return tr("ERROR_SERIAL_SETOWN");
        case ERROR_SERIAL_SETFL:
            return tr("ERROR_SERIAL_SETFL");
        case ERROR_SERIAL_GET_ATTR:
            return tr("ERROR_SERIAL_GET_ATTR");
        case ERROR_SERIAL_SET_ATTR:
            return tr("ERROR_SERIAL_SET_ATTR");
        case ERROR_SERIAL_UNSUPPORT_DATA_SIZE:
            return tr("ERROR_SERIAL_UNSUPPORT_DATA_SIZE");
        case ERROR_SERIAL_UNSUPPORT_PARITY:
            return tr("ERROR_SERIAL_UNSUPPORT_PARITY");
        case ERROR_SERIAL_UNSUPPORT_STOPBITS:
            return tr("ERROR_SERIAL_UNSUPPORT_STOPBITS");
        case ERROR_SERIAL_READ:
            return tr("ERROR_SERIAL_READ");
        case ERROR_SERIAL_READ_OVERFLOW:
            return tr("ERROR_SERIAL_READ_OVERFLOW");
        case ERROR_SERIAL_READ_TIMEOUT:
            return tr("ERROR_SERIAL_READ_TIMEOUT");
        case ERROR_SERIAL_WRITE_OVERFLOW:
            return tr("ERROR_SERIAL_WRITE_OVERFLOW");
        case ERROR_SERIAL_WRITE:
            return tr("ERROR_SERIAL_WRITE");
        case ERROR_SERIAL_CLOSE:
            return tr("ERROR_SERIAL_CLOSE");
        case ERROR_SERIAL_NOT_OPEN:
            return tr("ERROR_SERIAL_NOT_OPEN");
        case ERROR_SERIAL_BAUDRATE_NOT_SUPPORT:
            return tr("ERROR_SERIAL_BAUDRATE_NOT_SUPPORT");
        case ERROR_SERIAL_SEND_DATA:
            return tr("ERROR_SERIAL_SEND_DATA");
        case ERROR_SERIAL_PARAM_INVALID:
            return tr("ERROR_SERIAL_PARAM_INVALID");
        case ERROR_SERIAL_RECEIVE_DATA_TIMEOUT:
            return tr("ERROR_SERIAL_RECEIVE_DATA_TIMEOUT");


        case ERROR_GPIO_BASE:
            return tr("ERROR_GPIO_BASE");
        case ERROR_GPIO_OPEN:
            return tr("ERROR_GPIO_OPEN");
        case ERROR_GPIO_CLOSE:
            return tr("ERROR_GPIO_CLOSE");
        case ERROR_GPIO_NOT_OPEN:
            return tr("ERROR_GPIO_NOT_OPEN");
        case ERROR_GPIO_IOCTL_LEDS:
            return tr("ERROR_GPIO_IOCTL_LEDS");
        case ERROR_GPIO_READ_LEDS:
            return tr("ERROR_GPIO_READ_LEDS");
        case ERROR_GPIO_READ_HM_SENSOR:
            return tr("ERROR_GPIO_READ_HM_SENSOR");
        case ERROR_GPIO_SET_LOW_LEVEL:
            return tr("ERROR_GPIO_SET_LOW_LEVEL");
        case ERROR_GPIO_SET_HIGH_LEVEL:
            return tr("ERROR_GPIO_SET_HIGH_LEVEL");
        case ERROR_GPIO_CAN_NOT_SET_VAL:
            return tr("ERROR_GPIO_CAN_NOT_SET_VAL");
        case ERROR_GPIO_GET_LEVEL:
            return tr("ERROR_GPIO_GET_LEVEL");
        case ERROR_GPIO_FLASH_THREAD_CREATE:
            return tr("ERROR_GPIO_FLASH_THREAD_CREATE");
        case ERROR_GPIO_THREAD_BUSY:
            return tr("ERROR_GPIO_THREAD_BUSY");
        case ERROR_GPIO_READ_KEY_STATUS:
            return tr("ERROR_GPIO_READ_KEY_STATUS");
        case ERROR_GPIO_IOCTL_DOOR:
            return tr("ERROR_GPIO_IOCTL_DOOR");
        case ERROR_GPIO_READ_DOOR_OVERTIMES:
            return tr("ERROR_GPIO_READ_DOOR_OVERTIMES");
        case ERROR_GPIO_DOOR_CTRL_OVERTIMES:
            return tr("ERROR_GPIO_DOOR_CTRL_OVERTIMES");
        case ERROR_GPIO_READ_STATUS:
            return tr("ERROR_GPIO_READ_STATUS");
        case ERROR_GPIO_NOT_EXIST:
            return tr("ERROR_GPIO_NOT_EXIST");
        case ERROR_GPIO_OPEN_DRAWER:
            return tr("ERROR_GPIO_OPEN_DRAWER");


        case ERROR_MOVEMENT_BASE:
            return tr("ERROR_MOVEMENT_BASE");
        case ERROR_MOVEMENT_DATA_NOT_MATCH:
            return tr("ERROR_MOVEMENT_DATA_NOT_MATCH");
        case ERROR_MOVEMENT_CHECK_NOT_MARCH:
            return tr("ERROR_MOVEMENT_CHECK_NOT_MARCH");
        case ERROR_MOVEMENT_WRONG_RESPON:
            return tr("ERROR_MOVEMENT_WRONG_RESPON");
        case ERROR_MOVEMENT_RESULT_NOT_FIND:
            return tr("ERROR_MOVEMENT_RESULT_NOT_FIND");
        case ERROR_MOVEMENT_GET_STATUS_TIMEOUT:
            return tr("ERROR_MOVEMENT_GET_STATUS_TIMEOUT");
        case ERROR_MOVEMENT_OPEN_PATH_FILE:
            return tr("ERROR_MOVEMENT_OPEN_PATH_FILE");
        case ERROR_MOVEMENT_START_CHARGE:
            return tr("ERROR_MOVEMENT_START_CHARGE");
        case ERROR_MOVEMENT_STOP_CHARGE:
            return tr("ERROR_MOVEMENT_STOP_CHARGE");
        case ERROR_MOVEMENT_PATH_NOT_EXIT:
            return tr("ERROR_MOVEMENT_PATH_NOT_EXIT");
        case ERROR_MOVEMENT_BACKWARD_NOT_SUPPORT:
            return tr("ERROR_MOVEMENT_BACKWARD_NOT_SUPPORT");
        case ERROR_MOVEMENT_MOVE_TIMEOUT:
            return tr("ERROR_MOVEMENT_MOVE_TIMEOUT");
        case ERROR_MOVEMENT_OUT_OF_XY_LIMIT:
            return tr("ERROR_MOVEMENT_OUT_OF_XY_LIMIT");
        case ERROR_MOVEMENT_PATH_UNREACHABLE:
            return tr("ERROR_MOVEMENT_PATH_UNREACHABLE");
        case ERROR_MOVEMENT_NOT_VAILD_PATH:
            return tr("ERROR_MOVEMENT_NOT_VAILD_PATH");
        case ERROR_MOVEMENT_START_MOVE:
            return tr("ERROR_MOVEMENT_START_MOVE");
        case ERROR_MOVEMENT_INVALID_CHARGE:
            return tr("ERROR_MOVEMENT_INVALID_CHARGE");
        case ERROR_MOVEMENT_INVALID_PARM:
            return tr("ERROR_MOVEMENT_INVALID_PARM");
        case ERROR_MOVEMENT_ID_NOT_MATCH:
            return tr("ERROR_MOVEMENT_ID_NOT_MATCH");
        case ERROR_MOVEMENT_MAP_NOT_MATCH:
            return tr("ERROR_MOVEMENT_MAP_NOT_MATCH");
        case ERROR_MOVEMENT_PATH_FILE_CHECK:
            return tr("ERROR_MOVEMENT_PATH_FILE_CHECK");
        case ERROR_MOVEMENT_MAP_UNKNOWN:
            return tr("ERROR_MOVEMENT_MAP_UNKNOWN");
        case ERROR_MOVEMENT_MISSION_STILL_RUNNING:
            return tr("ERROR_MOVEMENT_MISSION_STILL_RUNNING");
        case ERROR_MOVEMENT_NOT_SUCH_CMAD:
            return tr("ERROR_MOVEMENT_NOT_SUCH_CMAD");
        case ERROR_MOVEMENT_ROUTE_DATA_EXCEED:
            return tr("ERROR_MOVEMENT_ROUTE_DATA_EXCEED");
        case ERROR_MOVEMENT_SETTING_FILE_NOT_OPEN:
            return tr("ERROR_MOVEMENT_SETTING_FILE_NOT_OPEN");
        case ERROR_MOVEMENT_SETTING_FILE_NOT_EXIST:
            return tr("ERROR_MOVEMENT_SETTING_FILE_NOT_EXIST");
        case ERROR_MOVEMENT_CABINET_RAISE:
            return tr("ERROR_MOVEMENT_CABINET_RAISE");
        case ERROR_MOVEMENT_CABINET_DROP:
            return tr("ERROR_MOVEMENT_CABINET_DROP");
        case ERROR_MOVEMENT_SET_MAP:
            return tr("ERROR_MOVEMENT_SET_MAP");
        case ERROR_MOVEMENT_ENTER_LIFT:
            return tr("ERROR_MOVEMENT_ENTER_LIFT");
        case ERROR_MOVEMENT_EXIT_LIFT:
            return tr("ERROR_MOVEMENT_EXIT_LIFT");
        case ERROR_MOVEMENT_OVER_ULTRA_LIMIT:
            return tr("ERROR_MOVEMENT_OVER_ULTRA_LIMIT");
        case ERROR_MOVEMENT_FORCED_STOP:
            return tr("ERROR_MOVEMENT_FORCED_STOP");
        case ERROR_MOVEMENT_DATA_SET_OVERFLOW:
            return tr("ERROR_MOVEMENT_DATA_SET_OVERFLOW");
        case ERROR_MOVEMENT_NOT_VAILD_TIME:
            return tr("ERROR_MOVEMENT_NOT_VAILD_TIME");
        case ERROR_MOVEMENT_UNKNOWN:
            return tr("ERROR_MOVEMENT_UNKNOWN");
        case ERROR_MOVEMENT_RUNNING_NOTICE:
            return tr("ERROR_MOVEMENT_RUNNING_NOTICE");
        case ERROR_MOVEMENT_ESTOP_PRESS:
            return tr("ERROR_MOVEMENT_ESTOP_PRESS");
        case ERROR_MOVEMENT_ESTOP_RELEASE:
            return tr("ERROR_MOVEMENT_ESTOP_RELEASE");
        case ERROR_MOVEMENT_LEFT_DRIVER:
            return tr("ERROR_MOVEMENT_LEFT_DRIVER");
        case ERROR_MOVEMENT_RIGHT_DRIVER:
            return tr("ERROR_MOVEMENT_RIGHT_DRIVER");
        case ERROR_MOVEMENT_ULTRA_SOUND:
            return tr("ERROR_MOVEMENT_ULTRA_SOUND");
        case ERROR_MOVEMENT_BATTERY_HIGH_TEMPERATURE:
            return tr("ERROR_MOVEMENT_BATTERY_HIGH_TEMPERATURE");
        case ERROR_MOVEMENT_BATTERY_SHORT_CIRCUIT:
            return tr("ERROR_MOVEMENT_BATTERY_SHORT_CIRCUIT");
        case ERROR_MOVEMENT_BATTERY_OVERCURRENT:
            return tr("ERROR_MOVEMENT_BATTERY_OVERCURRENT");
        case ERROR_MOVEMENT_START_CHARGE_TIMEOUT:
            return tr("ERROR_MOVEMENT_START_CHARGE_TIMEOUT");
        case ERROR_MOVEMENT_CHARGE_UNKNOWN:
            return tr("ERROR_MOVEMENT_CHARGE_UNKNOWN");
        case ERROR_MOVEMENT_CALIBRATE_MAP:
            return tr("ERROR_MOVEMENT_CALIBRATE_MAP");
        case ERROR_MOVEMENT_MAP_LIMITED:
            return tr("ERROR_MOVEMENT_MAP_LIMITED");
        case ERROR_MOVEMENT_ROUTE_SET_EMPTY:
            return tr("ERROR_MOVEMENT_ROUTE_SET_EMPTY");
        case ERROR_MOVEMENT_ROUTE_PLAN:
            return tr("ERROR_MOVEMENT_ROUTE_PLAN");
        case ERROR_MOVEMENT_AUTO_SHUTDOWN:
            return tr("ERROR_MOVEMENT_AUTO_SHUTDOWN");
        case ERROR_MOVEMENT_CABINET_OPEN:
            return tr("ERROR_MOVEMENT_CABINET_OPEN");
        case ERROR_MOVEMENT_CABINET_RESUME:
            return tr("ERROR_MOVEMENT_CABINET_RESUME");
        case ERROR_MOVEMENT_LEFT_DRIVER_BREAKDOWN:
            return tr("ERROR_MOVEMENT_LEFT_DRIVER_BREAKDOWN");
        case ERROR_MOVEMENT_RIGHT_DRIVER_BREAKDOWN:
            return tr("ERROR_MOVEMENT_RIGHT_DRIVER_BREAKDOWN");
        case ERROR_MOVEMENT_GET_STATUS_OVER_LIMIT:
            return tr("ERROR_MOVEMENT_GET_STATUS_OVER_LIMIT");
        case ERROR_MOVEMENT_GET_SOFTWARE_VERSION:
            return tr("ERROR_MOVEMENT_GET_SOFTWARE_VERSION");
        case ERROR_MOVEMENT_ENTER_LIFT_FAIL_WAIT:
            return tr("ERROR_MOVEMENT_ENTER_LIFT_FAIL_WAIT");
        case ERROR_MOVEMENT_CMAD_EXEC:
            return tr("ERROR_MOVEMENT_CMAD_EXEC");
        case ERROR_MOVEMENT_QRCODE_DETECT:
            return tr("ERROR_MOVEMENT_QRCODE_DETECT");
        case ERROR_MOVEMENT_STATION_OCC:
            return tr("ERROR_MOVEMENT_STATION_OCC");
        case ERROR_MOVEMENT_NET_CONTORL_STOP:
            return tr("ERROR_MOVEMENT_NET_CONTORL_STOP");
        case ERROR_MOVEMENT_SHELF_DECOUPLING:
            return tr("ERROR_MOVEMENT_SHELF_DECOUPLING");
        case ERROR_MOVEMENT_SHELF_RESUME:
            return tr("ERROR_MOVEMENT_SHELF_RESUME");
        case ERROR_MOVEMENT_POSITION_CORRECT:
            return tr("ERROR_MOVEMENT_POSITION_CORRECT");
        case ERROR_MOVEMENT_CONNECT_NETWORK_TIMEOUT:
            return tr("ERROR_MOVEMENT_CONNECT_NETWORK_TIMEOUT");
        case ERROR_MOVEMENT_SET_MAP_TIMEOUT:
            return tr("ERROR_MOVEMENT_SET_MAP_TIMEOUT");
        case ERROR_MOVEMENT_CHARGE_TIMEOUT:
            return tr("ERROR_MOVEMENT_CHARGE_TIMEOUT");
        case ERROR_MOVEMENT_SHIFT_MOVE_TIMEOUT:
            return tr("ERROR_MOVEMENT_SHIFT_MOVE_TIMEOUT");


        case ERROR_PRINTER_BASE:
            return tr("ERROR_PRINTER_BASE");
        case ERROR_PRINTER_NO_PAPER:
            return tr("ERROR_PRINTER_NO_PAPER");
        case ERROR_PRINTER_PAPER_BLOCK:
            return tr("ERROR_PRINTER_PAPER_BLOCK");
        case ERROR_PRINTER_ABNORMAL:
            return tr("ERROR_PRINTER_ABNORMAL");
        case ERROR_PRINTER_OFFLINE:
            return tr("ERROR_PRINTER_OFFLINE");
        case ERROR_PRINTER_CUT_PAPER:
            return tr("ERROR_PRINTER_CUT_PAPER");
        case ERROR_PRINTER_BLACK_MARK:
            return tr("ERROR_PRINTER_BLACK_MARK");
        case ERROR_PRINTER_COVER_OPEN:
            return tr("ERROR_PRINTER_COVER_OPEN");
        case ERROR_PRINTER_PAPER_RUNOUT:
            return tr("ERROR_PRINTER_PAPER_RUNOUT");
        case ERROR_PRINTER_RESPON_NOT_MATCH:
            return tr("ERROR_PRINTER_RESPON_NOT_MATCH");
        case ERROR_PRINTER_INVALID_PARAM:
            return tr("ERROR_PRINTER_INVALID_PARAM");
        case ERROR_PRINTER_DEV_OPEN:
            return tr("ERROR_PRINTER_DEV_OPEN");
        case ERROR_PRINTER_DEV_NOT_OPEN:
            return tr("ERROR_PRINTER_DEV_NOT_OPEN");
        case ERROR_PRINTER_DEV_CLOSE:
            return tr("ERROR_PRINTER_DEV_CLOSE");
        case ERROR_PRINTER_LINE_OVERFLOW:
            return tr("ERROR_PRINTER_LINE_OVERFLOW");
        case ERROR_PRINTER_NULL_PARAM:
            return tr("ERROR_PRINTER_NULL_PARAM");
        case ERROR_PRINTER_UNKONWN:
            return tr("ERROR_PRINTER_UNKONWN");


        case ERROR_IDCARD_BASE:
            return tr("ERROR_IDCARD_BASE");
        case ERROR_IDCARD_RECV_CRC:
            return tr("ERROR_IDCARD_RECV_CRC");
        case ERROR_IDCARD_RECV_LEN:
            return tr("ERROR_IDCARD_RECV_LEN");
        case ERROR_IDCARD_RECV_CMAD:
            return tr("ERROR_IDCARD_RECV_CMAD");
        case ERROR_IDCARD_OPT_EXCEED:
            return tr("ERROR_IDCARD_OPT_EXCEED");
        case ERROR_IDCARD_UNKNOWN:
            return tr("ERROR_IDCARD_UNKNOWN");
        case ERROR_IDCARD_SAM_TO_CARD:
            return tr("ERROR_IDCARD_SAM_TO_CARD");
        case ERROR_IDCARD_CARD_TO_SAM:
            return tr("ERROR_IDCARD_CARD_TO_SAM");
        case ERROR_IDCARD_INFO_CHECK:
            return tr("ERROR_IDCARD_INFO_CHECK");
        case ERROR_IDCARD_UNKNOWN_CARD:
            return tr("ERROR_IDCARD_UNKNOWN_CARD");
        case ERROR_IDCARD_READ_CARD:
            return tr("ERROR_IDCARD_READ_CARD");
        case ERROR_IDCARD_GET_RANDOM_NUM:
            return tr("ERROR_IDCARD_GET_RANDOM_NUM");
        case ERROR_IDCARD_SELF_CHECK:
            return tr("ERROR_IDCARD_SELF_CHECK");
        case ERROR_IDCARD_UNAUTHORIZED:
            return tr("ERROR_IDCARD_UNAUTHORIZED");
        case ERROR_IDCARD_FIND_CARD:
            return tr("ERROR_IDCARD_FIND_CARD");
        case ERROR_IDCARD_SELECT_CARD:
            return tr("ERROR_IDCARD_SELECT_CARD");
        case ERROR_IDCARD_NO_CONTENT:
            return tr("ERROR_IDCARD_NO_CONTENT");


        case ERROR_KINECT_BASE:
            return tr("ERROR_KINECT_BASE");
        case ERROR_KINECT_DEV_NOT_FOUND:
            return tr("ERROR_KINECT_DEV_NOT_FOUND");
        case ERROR_KINECT_OPEN_DEV:
            return tr("ERROR_KINECT_OPEN_DEV");
        case ERROR_KINECT_START_DEV:
            return tr("ERROR_KINECT_START_DEV");
        case ERROR_KINECT_STOP_DEV:
            return tr("ERROR_KINECT_STOP_DEV");
        case ERROR_KINECT_GET_FRAME_TIMEOUT:
            return tr("ERROR_KINECT_GET_FRAME_TIMEOUT");
        case ERROR_KINECT_NULL_PARAM:
            return tr("ERROR_KINECT_NULL_PARAM");
        case ERROR_KINECT_BUFF_NOT_ENOUGH:
            return tr("ERROR_KINECT_BUFF_NOT_ENOUGH");
        case ERROR_KINECT_INVALID_FRAME_TYPE:
            return tr("ERROR_KINECT_INVALID_FRAME_TYPE");
        case ERROR_KINECT_OPEN_VIDEO_ENCODER:
            return tr("ERROR_KINECT_OPEN_VIDEO_ENCODER");


        case ERROR_RING_BASE:
            return tr("ERROR_RING_BASE");
        case ERROR_RING_RECV_DATA:
            return tr("ERROR_RING_RECV_DATA");
        case ERROR_RING_COMMU:
            return tr("ERROR_RING_COMMU");


        case ERROR_TTS_BASE:
            return tr("ERROR_TTS_BASE");
        case ERROR_TTS_RECV_DATA:
            return tr("ERROR_TTS_RECV_DATA");
        case ERROR_TTS_INVAILD_PARAM:
            return tr("ERROR_TTS_INVAILD_PARAM");
        case ERROR_TTS_DEV_OPEN:
            return tr("ERROR_TTS_DEV_OPEN");
        case ERROR_TTS_DEV_CLOSE:
            return tr("ERROR_TTS_DEV_CLOSE");
        case ERROR_TTS_RECV_DATA_OVER_LEN:
            return tr("ERROR_TTS_RECV_DATA_OVER_LEN");
        case ERROR_TTS_MUTE:
            return tr("ERROR_TTS_MUTE");
        case ERROR_TTS_UNKONWN_CMAD:
            return tr("ERROR_TTS_UNKONWN_CMAD");
        case ERROR_TTS_DEV_NAME:
            return tr("ERROR_TTS_DEV_NAME");


        case ERROR_FINGER_BASE:
            return tr("ERROR_FINGER_BASE");
        case ERROR_FINGER_OPERATION:
            return tr("ERROR_FINGER_OPERATION");
        case ERROR_FINGER_EIGENVALUE_NOT_ENOUGH:
            return tr("ERROR_FINGER_EIGENVALUE_NOT_ENOUGH");
        case ERROR_FINGER_CUPTURE_TIMEOUT:
            return tr("ERROR_FINGER_CUPTURE_TIMEOUT");
        case ERROR_FINGER_USER_ID_EXIST:
            return tr("ERROR_FINGER_USER_ID_EXIST");
        case ERROR_FINGER_DATABASE_FULL:
            return tr("ERROR_FINGER_DATABASE_FULL");
        case ERROR_FINGER_USER_NOT_EXIST:
            return tr("ERROR_FINGER_USER_NOT_EXIST");
        case ERROR_FINGER_CHECK_SUM:
            return tr("ERROR_FINGER_CHECK_SUM");
        case ERROR_FINGER_RECV_DATA_FORMAT:
            return tr("ERROR_FINGER_RECV_DATA_FORMAT");
        case ERROR_FINGER_CMAD_NOT_MATCH:
            return tr("ERROR_FINGER_CMAD_NOT_MATCH");
        case ERROR_FINGER_USER_FINGER_EXIT:
            return tr("ERROR_FINGER_USER_FINGER_EXIT");
        case ERROR_FINGER_TIMEOUT:
            return tr("ERROR_FINGER_TIMEOUT");
        case ERROR_FINGER_UNKONW:
            return tr("ERROR_FINGER_UNKONW");
        case ERROR_FINGER_RECV_DATA_OVER_LEN:
            return tr("ERROR_FINGER_RECV_DATA_OVER_LEN");
        case ERROR_FINGER_RESPON:
            return tr("ERROR_FINGER_RESPON");
        case ERROR_FINGER_VERIFY_TIMEOUT:
            return tr("ERROR_FINGER_VERIFY_TIMEOUT");
        case ERROR_FINGER_NO_TARGET_ABOVE:
            return tr("ERROR_FINGER_NO_TARGET_ABOVE");
        case ERROR_FINGER_RECORD:
            return tr("ERROR_FINGER_RECORD");
        case ERROR_FINGER_IMAGE_NOT_CLRAE:
            return tr("ERROR_FINGER_IMAGE_NOT_CLRAE");
        case ERROR_FINGER_REMAIN:
            return tr("ERROR_FINGER_REMAIN");
        case ERROR_FINGER_WRITE_FLASH:
            return tr("ERROR_FINGER_WRITE_FLASH");
        case ERROR_FINGER_NO_VALID_IMAGE_IN_BUFF:
            return tr("ERROR_FINGER_NO_VALID_IMAGE_IN_BUFF");
        case ERROR_FINGER_MERGE_MODULE:
            return tr("ERROR_FINGER_MERGE_MODULE");
        case ERROR_FINGER_EXE_COMMAND:
            return tr("ERROR_FINGER_EXE_COMMAND");
        case ERROR_FINGER_CANNOT_RECEIVE_LEFT:
            return tr("ERROR_FINGER_CANNOT_RECEIVE_LEFT");
        case ERROR_FINGER_OPERATION_CANCLE:
            return tr("ERROR_FINGER_OPERATION_CANCLE");
        case ERROR_FINGER_PACKET_RECV:
            return tr("ERROR_FINGER_PACKET_RECV");
        case ERROR_FINGER_TOO_DRY_OR_LIGHT:
            return tr("ERROR_FINGER_TOO_DRY_OR_LIGHT");
        case ERROR_FINGER_TOO_WET_OR_BLURRY:
            return tr("ERROR_FINGER_TOO_WET_OR_BLURRY");
        case ERROR_FINGER_NOT_MATCH:
            return tr("ERROR_FINGER_NOT_MATCH");
        case ERROR_FINGER_NUMBER_OUT_OF_RANGE:
            return tr("ERROR_FINGER_NUMBER_OUT_OF_RANGE");
        case ERROR_FINGER_READ_TEMPLATE:
            return tr("ERROR_FINGER_READ_TEMPLATE");
        case ERROR_FINGER_FEATURE_UPLOAD:
            return tr("ERROR_FINGER_FEATURE_UPLOAD");
        case ERROR_FINGER_UPLOAD_IMAGE:
            return tr("ERROR_FINGER_UPLOAD_IMAGE");
        case ERROR_FINGER_DELETE_TEMPLATE:
            return tr("ERROR_FINGER_DELETE_TEMPLATE");
        case ERROR_FINGER_CLEAR_FINGERPRINT_LIBRARY:
            return tr("ERROR_FINGER_CLEAR_FINGERPRINT_LIBRARY");
        case ERROR_FINGER_ENTER_LOW_POWER_STATE:
            return tr("ERROR_FINGER_ENTER_LOW_POWER_STATE");
        case ERROR_FINGER_INCORRECT_PASSWORD:
            return tr("ERROR_FINGER_INCORRECT_PASSWORD");
        case ERROR_FINGER_ONLINE_UPGRADE:
            return tr("ERROR_FINGER_ONLINE_UPGRADE");
        case ERROR_FINGER_RANDOM_NUMBER_GENERATION:
            return tr("ERROR_FINGER_RANDOM_NUMBER_GENERATION");
        case ERROR_FINGER_INVALID_REGISTER_NUMBER:
            return tr("ERROR_FINGER_INVALID_REGISTER_NUMBER");
        case ERROR_FINGER_REGISTER_SETTING_CONTENT:
            return tr("ERROR_FINGER_REGISTER_SETTING_CONTENT");
        case ERROR_FINGER_NOTEPAD_PAGE_CODE:
            return tr("ERROR_FINGER_NOTEPAD_PAGE_CODE");
        case ERROR_FINGER_PORT_OPERATION:
            return tr("ERROR_FINGER_PORT_OPERATION");
        case ERROR_FINGER_AUTOMATIC_ENROLL:
            return tr("ERROR_FINGER_AUTOMATIC_ENROLL");
        case ERROR_FINGER_LIBRARY_FULL:
            return tr("ERROR_FINGER_LIBRARY_FULL");
        case ERROR_FINGER_DEVICE_ADDRESS:
            return tr("ERROR_FINGER_DEVICE_ADDRESS");
        case ERROR_FINGER_WRONG_PASSWORD:
            return tr("ERROR_FINGER_WRONG_PASSWORD");
        case ERROR_FINGER_TEMPLATE_IS_NOT_EMPTY:
            return tr("ERROR_FINGER_TEMPLATE_IS_NOT_EMPTY");
        case ERROR_FINGER_TEMPLATE_IS_EMPTY:
            return tr("ERROR_FINGER_TEMPLATE_IS_EMPTY");
        case ERROR_FINGER_LIBRARY_IS_EMPTY:
            return tr("ERROR_FINGER_LIBRARY_IS_EMPTY");
        case ERROR_FINGER_SET_NUMBER_OF_ENTRIES:
            return tr("ERROR_FINGER_SET_NUMBER_OF_ENTRIES");
        case ERROR_FINGER_FEATURES_ARE_RELATED:
            return tr("ERROR_FINGER_FEATURES_ARE_RELATED");
        case ERROR_FINGER_SENSOR_OPERATION:
            return tr("ERROR_FINGER_SENSOR_OPERATION");
        case ERROR_FINGER_MODULE_INFO_IS_NOT_EMPTY:
            return tr("ERROR_FINGER_MODULE_INFO_IS_NOT_EMPTY");
        case ERROR_FINGER_MODULE_INFO_IS_EMPTY:
            return tr("ERROR_FINGER_MODULE_INFO_IS_EMPTY");
        case ERROR_FINGER_OTP_OPERATION:
            return tr("ERROR_FINGER_OTP_OPERATION");
        case ERROR_FINGER_KEY_GENERATION:
            return tr("ERROR_FINGER_KEY_GENERATION");
        case ERROR_FINGER_KEY_NOT_EXIST:
            return tr("ERROR_FINGER_KEY_NOT_EXIST");
        case ERROR_FINGER_SECURITY_ALGORITHM_EXEC:
            return tr("ERROR_FINGER_SECURITY_ALGORITHM_EXEC");
        case ERROR_FINGER_SECURITY_ALGORITHM_RESULT:
            return tr("ERROR_FINGER_SECURITY_ALGORITHM_RESULT");
        case ERROR_FINGER_ENCRYPTION_LEVEL_NOT_MATCH:
            return tr("ERROR_FINGER_ENCRYPTION_LEVEL_NOT_MATCH");
        case ERROR_FINGER_KEY_IS_LOCK:
            return tr("ERROR_FINGER_KEY_IS_LOCK");
        case ERROR_FINGER_SMALL_IMAGE_AREA:
            return tr("ERROR_FINGER_SMALL_IMAGE_AREA");
        case ERROR_FINGER_IMAGE_IS_NOT_AVAILABLE:
            return tr("ERROR_FINGER_IMAGE_IS_NOT_AVAILABLE");
        case ERROR_FINGER_ILLEGAL_DATA:
            return tr("ERROR_FINGER_ILLEGAL_DATA");
        case ERROR_FINGER_SYSTEM_RESET_FAILED:
            return tr("ERROR_FINGER_SYSTEM_RESET_FAILED");
        case ERROR_FINGER_OPEN:
            return tr("ERROR_FINGER_OPEN");


        case ERROR_SCANNER_BASE:
            return tr("ERROR_SCANNER_BASE");
        case ERROR_SCANNER_NAK_DENIED:
            return tr("ERROR_SCANNER_NAK_DENIED");
        case ERROR_SCANNER_RECOGNIZE_CHECK_SUM:
            return tr("ERROR_SCANNER_RECOGNIZE_CHECK_SUM");
        case ERROR_SCANNER_NAK_BAD_CONTEXT:
            return tr("ERROR_SCANNER_NAK_BAD_CONTEXT");
        case ERROR_SCANNER_UNKONWN:
            return tr("ERROR_SCANNER_UNKONWN");
        case ERROR_SCANNER_READ_TIMEOUT:
            return tr("ERROR_SCANNER_READ_TIMEOUT");
        case ERROR_SCANNER_CMAD_CHECK_SUM:
            return tr("ERROR_SCANNER_CMAD_CHECK_SUM");
        case ERROR_SCANNER_CHECKSUM:
            return tr("ERROR_SCANNER_CHECKSUM");
        case ERROR_SCANNER_HEAD:
            return tr("ERROR_SCANNER_HEAD");
        case ERROR_SCANNER_MODULE_CHECK_SUM:
            return tr("ERROR_SCANNER_MODULE_CHECK_SUM");
        case ERROR_SCANNER_OPERATION:
            return tr("ERROR_SCANNER_OPERATION");
        case ERROR_SCANNER_UNKONWN_RESPONSE:
            return tr("ERROR_SCANNER_UNKONWN_RESPONSE");
        case ERROR_SCANNER_OPEN:
            return tr("ERROR_SCANNER_OPEN");
        case ERROR_SCANNER_NOT_OPEN:
            return tr("ERROR_SCANNER_NOT_OPEN");
        case ERROR_SCANNER_CLOSE:
            return tr("ERROR_SCANNER_CLOSE");
        case ERROR_SCANNER_RECV_INVALID_LEN:
            return tr("ERROR_SCANNER_RECV_INVALID_LEN");
        case ERROR_SCANNER_SET_INTERVAL_TIME:
            return tr("ERROR_SCANNER_SET_INTERVAL_TIME");


        case ERROR_FACE_BASE:
            return tr("ERROR_FACE_BASE");
        case ERROR_FACE_CAMERA_NOT_OPEN:
            return tr("ERROR_FACE_CAMERA_NOT_OPEN");
        case ERROR_FACE_LOAD_XML:
            return tr("ERROR_FACE_LOAD_XML");
        case ERROR_FACE_CAPTURE:
            return tr("ERROR_FACE_CAPTURE");
        case ERROR_FACE_OPEN_CSV_FILE:
            return tr("ERROR_FACE_OPEN_CSV_FILE");
        case ERROR_FACE_IMAGE_NOT_ENOUGH:
            return tr("ERROR_FACE_IMAGE_NOT_ENOUGH");
        case ERROR_FACE_IMAGE_WRITE:
            return tr("ERROR_FACE_IMAGE_WRITE");
        case ERROR_FACE_FILE_DIR_EXIST:
            return tr("ERROR_FACE_FILE_DIR_EXIST");
        case ERROR_FACE_IDENTIFY_DEGREE_LOW:
            return tr("ERROR_FACE_IDENTIFY_DEGREE_LOW");
        case ERROR_FACE_USER_NOT_EXIST:
            return tr("ERROR_FACE_USER_NOT_EXIST");
        case ERROR_FACE_FEATURE_FILE_NOT_EXIST:
            return tr("ERROR_FACE_FEATURE_FILE_NOT_EXIST");
        case ERROR_FACE_DATA_LEN:
            return tr("ERROR_FACE_DATA_LEN");
        case ERROR_FACE_RECORD:
            return tr("ERROR_FACE_RECORD");
        case ERROR_FACE_FUNC_OPT:
            return tr("ERROR_FACE_FUNC_OPT");
        case ERROR_FACE_SERIAL_RECORD:
            return tr("ERROR_FACE_SERIAL_RECORD");
        case ERROR_FACE_SERIAL_FEATURE_SYNC:
            return tr("ERROR_FACE_SERIAL_FEATURE_SYNC");
        case ERROR_FACE_VERIFY_TIMEOUT:
            return tr("ERROR_FACE_VERIFY_TIMEOUT");
        case ERROR_FACE_CAMERA_OPEN:
            return tr("ERROR_FACE_CAMERA_OPEN");
        case ERROR_FACE_TARGET_NOT_FOUND:
            return tr("ERROR_FACE_TARGET_NOT_FOUND");
        case ERROR_FACE_REGISTER_TIMEOUT:
            return tr("ERROR_FACE_REGISTER_TIMEOUT");
        case ERROR_FACE_CAMERA_SET_FORMAT:
            return tr("ERROR_FACE_CAMERA_SET_FORMAT");


        case ERROR_LOCK_BASE:
            return tr("ERROR_LOCK_BASE");
        case ERROR_LOCK_NUMBER:
            return tr("ERROR_LOCK_NUMBER");
        case ERROR_LOCK_OPEN:
            return tr("ERROR_LOCK_OPEN");
        case ERROR_LOCK_BUSY:
            return tr("ERROR_LOCK_BUSY");


        case ERROR_AIUI_BASE:
            return tr("ERROR_AIUI_BASE");
        case ERROR_AIUI_WIFI_CONFIG:
            return tr("ERROR_AIUI_WIFI_CONFIG");
        case ERROR_AIUI_SLEEP:
            return tr("ERROR_AIUI_SLEEP");
        case ERROR_AIUI_WAKEUP:
            return tr("ERROR_AIUI_WAKEUP");
        case ERROR_AIUI_WIFI_NOT_RETURN:
            return tr("ERROR_AIUI_WIFI_NOT_RETURN");
        case ERROR_AIUI_STATUS_NOT_RETURN:
            return tr("ERROR_AIUI_STATUS_NOT_RETURN");
        case ERROR_AIUI_WIFI_PACKAGE_OVERLEN:
            return tr("ERROR_AIUI_WIFI_PACKAGE_OVERLEN");
        case ERROR_AIUI_HANDSHAKE:
            return tr("ERROR_AIUI_HANDSHAKE");
        case ERROR_AIUI_RESEND:
            return tr("ERROR_AIUI_RESEND");

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


        case ERROR_BLE_BASE:
            return tr("ERROR_BLE_BASE");
        case ERROR_BLE_GET_DEVICE:
            return tr("ERROR_BLE_GET_DEVICE");
        case ERROR_BLE_CREATE_SERVICE_UUID:
            return tr("ERROR_BLE_CREATE_SERVICE_UUID");
        case ERROR_BLE_CONNECT_SERVICE:
            return tr("ERROR_BLE_CONNECT_SERVICE");
        case ERROR_BLE_DEVICE_DISCONNECT:
            return tr("ERROR_BLE_DEVICE_DISCONNECT");
        case ERROR_BLE_POWER_OFF:
            return tr("ERROR_BLE_POWER_OFF");
        case ERROR_BLE_INPUT_OUTPUT:
            return tr("ERROR_BLE_INPUT_OUTPUT");
        case ERROR_BLE_DOOR_NAK:
            return tr("ERROR_BLE_DOOR_NAK");
        case ERROR_BLE_DOOR_GET_STATUS:
            return tr("ERROR_BLE_DOOR_GET_STATUS");
        case ERROR_BLE_AT_DATA_CHECK_SUM:
            return tr("ERROR_BLE_AT_DATA_CHECK_SUM");
        case ERROR_BLE_OPEN_DOOR:
            return tr("ERROR_BLE_OPEN_DOOR");
        case ERROR_BLE_CLOSE_DOOR:
            return tr("ERROR_BLE_CLOSE_DOOR");
        case ERROR_BLE_NO_MATCHING_DEVICE:
            return tr("ERROR_BLE_NO_MATCHING_DEVICE");
        case ERROR_BLE_UNKNOWN:
            return tr("ERROR_BLE_UNKNOWN");
        case ERROR_BLE_START_DISCOVERY:
            return tr("ERROR_BLE_START_DISCOVERY");
        case ERROR_BLE_CREATE_SERVICE:
            return tr("ERROR_BLE_CREATE_SERVICE");
        case ERROR_BLE_SERVEIC_EMPTY:
            return tr("ERROR_BLE_SERVEIC_EMPTY");
        case ERROR_BLE_WRITE_CHARACTERISTIC:
            return tr("ERROR_BLE_WRITE_CHARACTERISTIC");
        case ERROR_BLE_STOP_DISCOVERY:
            return tr("ERROR_BLE_STOP_DISCOVERY");
        case ERROR_BLE_DOOR_NAME_EMPTY:
            return tr("ERROR_BLE_DOOR_NAME_EMPTY");
        case ERROR_BLE_SERIAL_OPEN:
            return tr("ERROR_BLE_SERIAL_OPEN");
        case ERROR_BLE_SERIAL_CLOSE:
            return tr("ERROR_BLE_SERIAL_CLOSE");
        case ERROR_BLE_RECV_NOT_MATCH:
            return tr("ERROR_BLE_RECV_NOT_MATCH");
        case ERROR_BLE_CONTROLLER_BASE:
            return tr("ERROR_BLE_CONTROLLER_BASE");
        case ERROR_BLE_CONTROLLER_UNKNOWN:
            return tr("ERROR_BLE_CONTROLLER_UNKNOWN");
        case ERROR_BLE_CONTROLLER_REMOTE_DEVICE:
            return tr("ERROR_BLE_CONTROLLER_REMOTE_DEVICE");
        case ERROR_BLE_CONTROLLER_NETWORK:
            return tr("ERROR_BLE_CONTROLLER_NETWORK");
        case ERROR_BLE_CONTROLLER_INVALID_ADAPTER:
            return tr("ERROR_BLE_CONTROLLER_INVALID_ADAPTER");
        case ERROR_BLE_CONTROLLER_CONNECTION:
            return tr("ERROR_BLE_CONTROLLER_CONNECTION");
        case ERROR_BLE_AGENT_BASE:
            return tr("ERROR_BLE_AGENT_BASE");
        case ERROR_BLE_AGENT_INPUT_OUTPUT:
            return tr("ERROR_BLE_AGENT_INPUT_OUTPUT");
        case ERROR_BLE_AGENT_POWER_OFF:
            return tr("ERROR_BLE_AGENT_POWER_OFF");
        case ERROR_BLE_AGENT_INVALID_ADAPTER:
            return tr("ERROR_BLE_AGENT_INVALID_ADAPTER");
        case ERROR_BLE_AGENT_UNSUPPORT_PLATFORM:
            return tr("ERROR_BLE_AGENT_UNSUPPORT_PLATFORM");
        case ERROR_BLE_AGENT_UNKNOWN:
            return tr("ERROR_BLE_AGENT_UNKNOWN");


        case ERROR_WIRELESS_AUDIO_BASE:
            return tr("ERROR_WIRELESS_AUDIO_BASE");
        case ERROR_WIRELESS_AUDIO_RECV_DATA:
            return tr("ERROR_WIRELESS_AUDIO_RECV_DATA");


        case ERROR_VERIFY_BASE:
            return tr("ERROR_VERIFY_BASE");
        case ERROR_VERIFY_DUPLICATE_INFO:
            return tr("ERROR_VERIFY_DUPLICATE_INFO");
        case ERROR_VERIFY_USER_ALREADY_EXIST:
            return tr("ERROR_VERIFY_USER_ALREADY_EXIST");
        case ERROR_VERIFY_TARGET_NOT_FOUND:
            return tr("ERROR_VERIFY_TARGET_NOT_FOUND");
        case ERROR_VERIFY_NO_AUTHORIZED:
            return tr("ERROR_VERIFY_NO_AUTHORIZED");
        case ERROR_VERIFY_NO_NETWORK:
            return tr("ERROR_VERIFY_NO_NETWORK");
        case ERROR_VERIFY_MULT_FINGER_USER:
            return tr("ERROR_VERIFY_MULT_FINGER_USER");
        case ERROR_VERIFY_MULT_FACE_USER:
            return tr("ERROR_VERIFY_MULT_FACE_USER");
        case ERROR_VERIFY_DATA_NUM_NOT_MATCH:
            return tr("ERROR_VERIFY_DATA_NUM_NOT_MATCH");
        case ERROR_VERIFY_DEVICE_NOT_OPEN:
            return tr("ERROR_VERIFY_DEVICE_NOT_OPEN");
        case ERROR_VERIFY_STRANGER:
            return tr("ERROR_VERIFY_STRANGER");
        case ERROR_VERIFY_DOWNLOAD_FILE_NOT_EXIST:
            return tr("ERROR_VERIFY_DOWNLOAD_FILE_NOT_EXIST");
        case ERROR_VERIFY_DOWNLOAD_FILE_NOT_NEW:
            return tr("ERROR_VERIFY_DOWNLOAD_FILE_NOT_NEW");
        case ERROR_VERIFY_REMOVE_FILE:
            return tr("ERROR_VERIFY_REMOVE_FILE");
        case ERROR_VERIFY_RENAME_FILE:
            return tr("ERROR_VERIFY_RENAME_FILE");
        case ERROR_VERIFY_DOWNLOAD_FILE_SAME:
            return tr("ERROR_VERIFY_DOWNLOAD_FILE_SAME");
        case ERROR_VERIFY_NULL_PARAM:
            return tr("ERROR_VERIFY_NULL_PARAM");
        case ERROR_VERIFY_INFO_NOT_ENOUGH:
            return tr("ERROR_VERIFY_INFO_NOT_ENOUGH");
        case ERROR_VERIFY_PRIORITY_INVALID:
            return tr("ERROR_VERIFY_PRIORITY_INVALID");
        case ERROR_VERIFY_CHAR_OVER_LEN:
            return tr("ERROR_VERIFY_CHAR_OVER_LEN(60)");
        case ERROR_VERIFY_CARD_ID_OVER_LEN:
            return tr("ERROR_VERIFY_CARD_ID_OVER_LEN(20)");
        case ERROR_VERIFY_LOCAL:
            return tr("ERROR_VERIFY_LOCAL");
        case ERROR_VERIFY_NEED_NETWORK:
            return tr("ERROR_VERIFY_NEED_NETWORK");
        case ERROR_VERIFY_NETWORK_NOT_SUPPORT:
            return tr("ERROR_VERIFY_NETWORK_NOT_SUPPORT");
        case ERROR_VERIFY_MIX_NOT_SUPPORT:
            return tr("ERROR_VERIFY_MIX_NOT_SUPPORT");
        case ERROR_VERIFY_PASSWORD_OVER_LEN:
            return tr("ERROR_VERIFY_PASSWORD_OVER_LEN");
        case ERROR_VERIFY_STATION_ACCESS:
            return tr("ERROR_VERIFY_STATION_ACCESS");
        case ERROR_VERIFY_DATA_NUM_EXCEED:
            return tr("ERROR_VERIFY_DATA_NUM_EXCEED");
        case ERROR_VERIFY_CONFLICT_INFO:
            return tr("ERROR_VERIFY_CONFLICT_INFO");
        case ERROR_VERIFY_USER_FILE_NOT_EXIST:
            return tr("ERROR_VERIFY_USER_FILE_NOT_EXIST");

        case ERROR_DOOR_CTRL_BASE:
            return tr("ERROR_DOOR_CTRL_BASE");
        case ERROR_DOOR_CTRL_RECV_NOT_MATCH:
            return tr("ERROR_DOOR_CTRL_RECV_NOT_MATCH");
        case ERROR_DOOR_CTRL_OPEN_DOOR:
            return tr("ERROR_DOOR_CTRL_OPEN_DOOR");
        case ERROR_DOOR_CTRL_CLOSE_DOOR:
            return tr("ERROR_DOOR_CTRL_CLOSE_DOOR");
        case ERROR_DOOR_CTRL_INPUT_OUTPUT:
            return tr("ERROR_DOOR_CTRL_INPUT_OUTPUT");

        case ERROR_MEDIA_BASE:
            return tr("ERROR_MEDIA_BASE");
        case ERROR_MEDIA_VOLUME_CTRL_FAIL:
            return tr("ERROR_MEDIA_VOLUME_CTRL_FAIL");
        case ERROR_MEDIA_IOCTL_FAIL:
            return tr("ERROR_MEDIA_IOCTL_FAIL");
        case ERROR_MEDIA_TARGET_DEV_NOT_FOUND:
            return tr("ERROR_MEDIA_TARGET_DEV_NOT_FOUND");
        case ERROR_MEDIA_VOLUME_DEV_OPEN_FAIL:
            return tr("ERROR_MEDIA_VOLUME_DEV_OPEN_FAIL");
        case ERROR_MEDIA_VOLUME_DEV_CLOSE_FAIL:
            return tr("ERROR_MEDIA_VOLUME_DEV_CLOSE_FAIL");


        case ERROR_VIDEO_BASE:
            return tr("ERROR_VIDEO_BASE");
        case ERROR_VIDEO_ENCODER_OPEN:
            return tr("ERROR_VIDEO_ENCODER_OPEN");
        case ERROR_VIDEO_AV_WRITE_TRAILER:
            return tr("ERROR_VIDEO_AV_WRITE_TRAILER");
        case ERROR_VIDEO_AVCODEC_CLOSE:
            return tr("ERROR_VIDEO_AVCODEC_CLOSE");
        case ERROR_VIDEO_AVIO_CLOSE:
            return tr("RROR_VIDEO_AVIO_CLOSE");
        case ERROR_VIDEO_ENCODE:
            return tr("ERROR_VIDEO_ENCODE");
        case ERROR_VIDEO_INTERLEAVE_WEITE_FRAME:
            return tr("ERROR_VIDEO_INTERLEAVE_WEITE_FRAME");
        case ERROR_VIDEO_ALLOC_OUTPUT_CONTEXT:
            return tr("ERROR_VIDEO_ALLOC_OUTPUT_CONTEXT");
        case ERROR_VIDEO_CODEC_ID_NONE:
            return tr("ERROR_VIDEO_CODEC_ID_NONE");
        case ERROR_VIDEO_AVIO_OPEN:
            return tr("ERROR_VIDEO_AVIO_OPEN");
        case ERROR_VIDEO_CREATE_NEW_STREAM:
            return tr("ERROR_VIDEO_CREATE_NEW_STREAM");
        case ERROR_VIDEO_OPT_SET:
            return tr("ERROR_VIDEO_OPT_SET");
        case ERROR_VIDEO_ENCODER_NOT_FOUND:
            return tr("ERROR_VIDEO_ENCODER_NOT_FOUND");
        case ERROR_VIDEO_FRAME_ALLOC:
            return tr("ERROR_VIDEO_FRAME_ALLOC");
        case ERROR_VIDEO_PICTURE_GET_SIZE:
            return tr("ERROR_VIDEO_PICTURE_GET_SIZE");
        case ERROR_VIDEO_PICTURE_FILL:
            return tr("ERROR_VIDEO_PICTURE_FILL");
        case ERROR_VIDEO_WRITE_HEADER:
            return tr("ERROR_VIDEO_WRITE_HEADER");
        case ERROR_VIDEO_NEW_PACKET:
            return tr("ERROR_VIDEO_NEW_PACKET");
        case ERROR_VIDEO_CODEC_CAP_DELAY:
            return tr("ERROR_VIDEO_CODEC_CAP_DELAY");
        case ERROR_VIDEO_WRITE_FRAME:
            return tr("ERROR_VIDEO_WRITE_FRAME");


        case ERROR_REALSENSE_BASE:
            return tr("ERROR_REALSENSE_BASE");
        case ERROR_REALSENSE_OPEN_DEV:
            return tr("ERROR_REALSENSE_OPEN_DEV");
        case ERROR_REALSENSE_START_DEV:
            return tr("ERROR_REALSENSE_START_DEV");
        case ERROR_REALSENSE_STOP_DEV:
            return tr("ERROR_REALSENSE_STOP_DEV");
        case ERROR_REALSENSE_NULL_PARAM:
            return tr("ERROR_REALSENSE_NULL_PARAM");
        case ERROR_REALSENSE_UDER_POWER:
            return tr("ERROR_REALSENSE_UDER_POWER");
        case ERROR_REALSENSE_THROW_EXCEPTION:
            return tr("ERROR_REALSENSE_THROW_EXCEPTION");


        case ERROR_UV_LIGHT_BASE:
            return tr("ERROR_UV_LIGHT_BASE");
        case ERROR_UV_LIGHT_OPEN_FAIL:
            return tr("ERROR_UV_LIGHT_OPEN_FAIL");
        case ERROR_UV_LIGHT_CLOSE_FAIL:
            return tr("ERROR_UV_LIGHT_CLOSE_FAIL");


        case ERROR_CABINET_BASE:
            return tr("ERROR_CABINET_BASE");
        case ERROR_CABINET_OPEN_FAIL:
            return tr("ERROR_CABINET_OPEN_FAIL");


        case ERROR_DISINFECTION_HOUSE_BASE:
            return tr("ERROR_DISINFECTION_HOUSE_BASE");
        case ERROR_DISINFECTION_HOUSE_RECV_NOT_MATCH:
            return tr("ERROR_DISINFECTION_HOUSE_RECV_NOT_MATCH");
        case ERROR_DISINFECTION_HOUSE_OPEN_DOOR:
            return tr("ERROR_DISINFECTION_HOUSE_OPEN_DOOR");
        case ERROR_DISINFECTION_HOUSE_CLOSE_DOOR:
            return tr("ERROR_DISINFECTION_HOUSE_CLOSE_DOOR");
        case ERROR_DISINFECTION_HOUSE_INPUT_OUTPUT:
            return tr("ERROR_DISINFECTION_HOUSE_INPUT_OUTPUT");
        case ERROR_DISINFECTION_HOUSE_HUMANITY:
            return tr("ERROR_DISINFECTION_HOUSE_HUMANITY");
        case ERROR_DISINFECTION_HOUSE_DOOR_DEV:
            return tr("ERROR_DISINFECTION_HOUSE_DOOR_DEV");
        case ERROR_DISINFECTION_HOUSE_MANMAL:
            return tr("ERROR_DISINFECTION_HOUSE_MANMAL");
        case ERROR_DISINFECTION_HOUSE_EMPTY:
            return tr("ERROR_DISINFECTION_HOUSE_EMPTY");
        case ERROR_DISINFECTION_HOUSE_FULL:
            return tr("ERROR_DISINFECTION_HOUSE_FULL");
        case ERROR_DISINFECTION_HOUSE_BUSY:
            return tr("ERROR_DISINFECTION_HOUSE_BUSY");
        case ERROR_DISINFECTION_HOUSE_OPERATING:
            return tr("ERROR_DISINFECTION_HOUSE_OPERATING");
        case ERROR_DISINFECTION_HOUSE_NO_RESPONSE:
            return tr("ERROR_DISINFECTION_HOUSE_NO_RESPONSE");
        case ERROR_DISINFECTION_HOUSE_ENTER_TIMEOUT:
            return tr("ERROR_DISINFECTION_HOUSE_ENTER_TIMEOUT");
        case ERROR_DISINFECTION_HOUSE_KEEP:
            return tr("ERROR_DISINFECTION_HOUSE_KEEP");

        case ERROR_DCU_BASE:
            return tr("ERROR_DCU_BASE");
        case ERROR_DCU_PARAM_INVAILD:
            return tr("ERROR_DCU_PARAM_INVAILD");
        case ERROR_DCU_BUSY:
            return tr("ERROR_DCU_BUSY");
        case ERROR_DCU_RESPON_TIMEOUT:
            return tr("ERROR_DCU_RESPON_TIMEOUT");
        case ERROR_DCU_HARDWARE_EXCEPTION:
            return tr("ERROR_DCU_HARDWARE_EXCEPTION");
        case ERROR_DCU_OPEN:
            return tr("ERROR_DCU_OPEN");
        case ERROR_DCU_HIGH_TEMPERATURE:
            return tr("ERROR_DCU_HIGH_TEMPERATURE");

        case ERROR_DCU_TC_DOCKING_IC:
            return tr("ERROR_DCU_TC_DOCKING_IC");
        case ERROR_DCU_TC_DETACH_IC:
            return tr("ERROR_DCU_TC_DETACH_IC");
        case ERROR_DCU_TC_DOCKING_ATD:
            return tr("ERROR_DCU_TC_DOCKING_ATD");
        case ERROR_DCU_TC_DETACH_ATD:
            return tr("ERROR_DCU_TC_DETACH_ATD");
        case ERROR_DCU_TC_DOCKING_SHELF:
            return tr("ERROR_DCU_TC_DOCKING_SHELF");
        case ERROR_DCU_TC_DETACH_SHELF:
            return tr("ERROR_DCU_TC_DETACH_SHELF");

        case ERROR_DCU_ATD_DOCKING_IC:
            return tr("ERROR_DCU_ATD_DOCKING_IC");
        case ERROR_DCU_ATD_DETACH_IC:
            return tr("ERROR_DCU_ATD_DETACH_IC");
        case ERROR_DCU_ATD_MOVE_UP_AND_DOWN:
            return tr("ERROR_DCU_ATD_MOVE_UP_AND_DOWN");
        case ERROR_DCU_ATD_TAKE_OUT_FROM_IC:
            return tr("ERROR_DCU_ATD_TAKE_OUT_FROM_IC");
        case ERROR_DCU_ATD_DEPOSIT_FROM_TRAY:
            return tr("ERROR_DCU_ATD_DEPOSIT_FROM_TRAY");
        case ERROR_DCU_ATD_TAKE_OUT_TO_TRAY:
            return tr("ERROR_DCU_ATD_TAKE_OUT_TO_TRAY");
        case ERROR_DCU_ATD_DEPOSIT_TO_IC:
            return tr("ERROR_DCU_ATD_DEPOSIT_TO_IC");
        case ERROR_DCU_IC_DOCKING_ATD:
            return tr("ERROR_DCU_IC_DOCKING_ATD");
        case ERROR_DCU_IC_DETACH_ATD:
            return tr("ERROR_DCU_IC_DETACH_ATD");
        case ERROR_DCU_IC_DEPOSIT:
            return tr("ERROR_DCU_IC_DEPOSIT");
        case ERROR_DCU_IC_TAKE_OUT:
            return tr("ERROR_DCU_IC_TAKE_OUT");

        case ERROR_MAIN_BASE:
            return tr("ERROR_MAIN_BASE");
        case ERROR_MAIN_MISSION_STEP:
            return tr("ERROR_MAIN_MISSION_STEP");
        case ERROR_MAIN_STATION_STOP_TIMEOUT:
            return tr("ERROR_MAIN_STATION_STOP_TIMEOUT");
        case ERROR_MAIN_ITEM_COUNT_USE_UP:
            return tr("ERROR_MAIN_ITEM_COUNT_USE_UP");
        case ERROR_MAIN_MISSION_MODE:
            return tr("ERROR_MAIN_MISSION_MODE");
        case ERROR_MAIN_DISPLAY_PAGE:
            return tr("ERROR_MAIN_DISPLAY_PAGE");
        case ERROR_MAIN_PATH_TYPE_NOT_SUPPORT:
            return tr("ERROR_MAIN_PATH_TYPE_NOT_SUPPORT");

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
        case ERROR_NETWORK_PATH_NOT_FOUND:
            return tr("ERROR_NETWORK_PATH_NOT_FOUND");
        case ERROR_NETWORK_ALREADY_IN_PATH:
            return tr("ERROR_NETWORK_ALREADY_IN_PATH");
        case ERROR_NETWORK_RECONNECT_OVERTIMES:
            return tr("ERROR_NETWORK_RECONNECT_OVERTIMES");
        case ERROR_NETWORK_SET_TIME:
            return tr("ERROR_NETWORK_SET_TIME");
        case ERROR_NETWORK_ID_VARIFY:
            return tr("ERROR_NETWORK_ID_VARIFY");
        case ERROR_NETWORK_BARCODE_VARIFY:
            return tr("ERROR_NETWORK_BARCODE_VARIFY");
        case ERROR_NETWORK_CHARGE_REFUSE:
            return tr("ERROR_NETWORK_CHARGE_REFUSE");
        case ERROR_NETWORK_DELAY_RECAL:
            return tr("ERROR_NETWORK_DELAY_RECAL");
        case ERROR_NETWORK_ACTION_UNCANCELABLE:
            return tr("ERROR_NETWORK_ACTION_UNCANCELABLE");
        case ERROR_NETWORK_ORDER_LIMITED:
            return tr("ERROR_NETWORK_ORDER_LIMITED");
        case ERROR_NETWORK_CALL_WAIT_TIMEOUT:
            return tr("ERROR_NETWORK_CALL_WAIT_TIMEOUT");
        case ERROR_NETWORK_CONNECT_UNKNOWN:
            return tr("ERROR_NETWORK_CONNECT_UNKNOWN");
        case ERROR_NETWORK_ROBOT_BUSY:
            return tr("ERROR_NETWORK_ROBOT_BUSY");
        case ERROR_NETWORK_MISSION_ID_REPEAT:
            return tr("ERROR_NETWORK_MISSION_ID_REPEAT");
        case ERROR_NETWORK_MISSION_ID_EMPTY:
            return tr("ERROR_NETWORK_MISSION_ID_EMPTY");
        case ERROR_NETWORK_MISSION_NAME_EMPTY:
            return tr("ERROR_NETWORK_MISSION_NAME_EMPTY");
        case ERROR_NETWORK_MISSION_ROUTE_EMPTY:
            return tr("ERROR_NETWORK_MISSION_ROUTE_EMPTY");
        case ERROR_NETWORK_ID_REPEAT:
            return tr("ERROR_NETWORK_ID_REPEAT");
        case ERROR_NETWORK_FILE_NOT_FOUND:
            return tr("ERROR_NETWORK_FILE_NOT_FOUND");
        case ERROR_NETWORK_LIFT_CALL_TIMEOUT:
            return tr("ERROR_NETWORK_LIFT_CALL_TIMEOUT");
        case ERROR_NETWORK_LIFT_EXIT_TIMEOUT:
            return tr("ERROR_NETWORK_LIFT_EXIT_TIMEOUT");
        case ERROR_NETWORK_STATION_WAIT_TIMEOUT:
            return tr("ERROR_NETWORK_STATION_WAIT_TIMEOUT");
        case ERROR_NETWORK_IC_TARGET_NOT_EXIST:
            return tr("ERROR_NETWORK_IC_TARGET_NOT_EXIST");
        case ERROR_NETWORK_IC_DESTIN_NOT_AVAILABLE:
            return tr("ERROR_NETWORK_IC_DESTIN_NOT_AVAILABLE");
        case ERROR_NETWORK_ID_NOT_MATCH:
            return tr("ERROR_NETWORK_ID_NOT_MATCH");


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

        case ERROR_BASE64_BASE:
            return tr("ERROR_BASE64_BASE");
        case ERROR_BASE64_OVERFLOW:
            return tr("ERROR_BASE64_OVERFLOW");
        case ERROR_BASE64_FILE_OPEN:
            return tr("ERROR_BASE64_FILE_OPEN");
        case ERROR_BASE64_FSEEK:
            return tr("ERROR_BASE64_FSEEK");
        case ERROR_BASE64_FILE_READ:
            return tr("ERROR_BASE64_FILE_READ");
        case ERROR_BASE64_FILE_WRITE:
            return tr("ERROR_BASE64_FILE_WRITE");
        case ERROR_BASE64_FILE_ECODE:
            return tr("ERROR_BASE64_FILE_ECODE");
        case ERROR_BASE64_FILE_DCODE:
            return tr("ERROR_BASE64_FILE_DCODE");


        case ERROR_PUBLIC_THREAD_BASE:
            return tr("ERROR_PUBLIC_THREAD_BASE");
        case ERROR_PUBLIC_THREAD_CANCELED:
            return tr("ERROR_PUBLIC_THREAD_CANCELED");
        case ERROR_PUBLIC_THREAD_REG_WITH_LEN_0:
            return tr("ERROR_PUBLIC_THREAD_REG_WITH_LEN_0");
        case ERROR_PUBLIC_THREAD_STILL_RUNNING:
            return tr("ERROR_PUBLIC_THREAD_STILL_RUNNING");
        case ERROR_PUBLIC_THREAD_CREATE_WHILE_RUN:
            return tr("ERROR_PUBLIC_THREAD_CREATE_WHILE_RUN");


        case ERROR_GZIP_BASE:
            return tr("ERROR_GZIP_BASE");
        case ERROR_GZIP_STREAM_END:
            return tr("ERROR_GZIP_STREAM_END");
        case ERROR_GZIP_NEED_DICT:
            return tr("ERROR_GZIP_NEED_DICT");
        case ERROR_GZIP_ERRNO:
            return tr("ERROR_GZIP_ERRNO");
        case ERROR_GZIP_STREAM:
            return tr("ERROR_GZIP_STREAM");
        case ERROR_GZIP_DATA:
            return tr("ERROR_GZIP_DATA");
        case ERROR_GZIP_MEM:
            return tr("ERROR_GZIP_MEM");
        case ERROR_GZIP_BUFF:
            return tr("ERROR_GZIP_BUFF");
        case ERROR_GZIP_VERSION:
            return tr("ERROR_GZIP_VERSION");


        case ERROR_HTTP_BASE:
            return tr("ERROR_HTTP_BASE");
        case ERROR_HTTP_CONNECT_TIMEOUT:
            return tr("ERROR_HTTP_CONNECT_TIMEOUT");
        case ERROR_HTTP_JSON_ANSWER:
            return tr("ERROR_HTTP_JSON_ANSWER");
        case ERROR_HTTP_NO_RESPONSE:
            return tr("ERROR_HTTP_NO_RESPONSE");
        case ERROR_HTTP_RESULTS:
            return tr("ERROR_HTTP_RESULTS");
        case ERROR_HTTP_NOT_JSON_PACK:
            return tr("ERROR_HTTP_NOT_JSON_PACK");


        case ERROR_VIEW_BASE:
            return tr("ERROR_VIEW_BASE");
        case ERROR_VIEW_ASSERTURE:
            return tr("ERROR_VIEW_ASSERTURE");
        case ERROR_VIEW_INPUTBOX_OVERFLOW:
            return tr("ERROR_VIEW_INPUTBOX_OVERFLOW");
        case ERROR_VIEW_SHOW_POINT_NUMBER:
            return tr("ERROR_VIEW_SHOW_POINT_NUMBER");
        case ERROR_VIEW_PIC_IS_EMPTY:
            return tr("ERROR_VIEW_PIC_IS_EMPTY");


        case ERROR_XUNFEI_BASE:
            return tr("ERROR_XUNFEI_BASE");

        case ERROR_NMCLI_BASE:
            return tr("ERROR_NMCLI_BASE");
        case ERROR_NMCLI_UNKNOWN:
            return tr("ERROR_NMCLI_UNKNOWN");
        case ERROR_NMCLI_INVALID_USER_INPUT:
            return tr("ERROR_NMCLI_INVALID_USER_INPUT");
        case ERROR_NMCLI_TIMEOUT_EXPIRED:
            return tr("ERROR_NMCLI_TIMEOUT_EXPIRED");
        case ERROR_NMCLI_CONNECTION_ACTIVATION:
            return tr("ERROR_NMCLI_CONNECTION_ACTIVATION");
        case ERROR_NMCLI_CONNECTION_DEACTIVATION:
            return tr("ERROR_NMCLI_CONNECTION_DEACTIVATION");
        case ERROR_NMCLI_DISCONNECTING_DEVICE:
            return tr("ERROR_NMCLI_DISCONNECTING_DEVICE");
        case ERROR_NMCLI_CONNECTING_DELETION:
            return tr("ERROR_NMCLI_CONNECTING_DELETION");
        case ERROR_NMCLI_MANAGER_NOT_RUNNING:
            return tr("ERROR_NMCLI_MANAGER_NOT_RUNNING");
        case ERROR_NMCLI_TARGET_NOT_EXIST:
            return tr("ERROR_NMCLI_TARGET_NOT_EXIST");
        case ERROR_NMCLI_NETWORK_MANAGE_NOT_RUNNING:
            return tr("ERROR_NMCLI_NETWORK_MANAGE_NOT_RUNNING");


        case ERROR_SYSTEM_BASE:
            return tr("ERROR_SYSTEM_BASE");
        case ERROR_SYSTEM_SHELL_CMAD:
            return tr("ERROR_SYSTEM_SHELL_CMAD");
        case ERROR_SYSTEM_CMAD_INVALID_CMAD:
            return tr("ERROR_SYSTEM_CMAD_INVALID_CMAD");
        case ERROR_SYSTEM_CMAD_CHILD_PROCESS:
            return tr("ERROR_SYSTEM_CMAD_CHILD_PROCESS");
        case ERROR_SYSTEM_CMAD_ABEND:
            return tr("ERROR_SYSTEM_CMAD_ABEND");
        case ERROR_SYSTEM_CMAD_NO_RESULT:
            return tr("ERROR_SYSTEM_CMAD_NO_RESULT");
        case ERROR_SYSTEM_CMAD_POPEN:
            return tr("ERROR_SYSTEM_CMAD_POPEN");
        case ERROR_SYSTEM_CMAD_OPERATION:
            return tr("ERROR_SYSTEM_CMAD_OPERATION");


        case ERROR_FILE_BASE:
            return tr("ERROR_FILE_BASE");
        case ERROR_FILE_FPRINTF:
            return tr("ERROR_FILE_FPRINTF");
        case ERROR_FILE_FCLOSE:
            return tr("ERROR_FILE_FCLOSE");
        case ERROR_FILE_FSEEK:
            return tr("ERROR_FILE_FSEEK");
        case ERROR_FILE_FSCANF:
            return tr("ERROR_FILE_FSCANF");
        case ERROR_FILE_FOPEN:
            return tr("ERROR_FILE_FOPEN");
        case ERROR_FILE_FWRITE:
            return tr("ERROR_FILE_FWRITE");
        case ERROR_FILE_FREAD:
            return tr("ERROR_FILE_FREAD");
        case ERROR_FILE_BAD:
            return tr("ERROR_FILE_BAD");
        case ERROR_FILE_EXCEED:
            return tr("ERROR_FILE_EXCEED");
        case ERROR_FILE_REMOVE:
            return tr("ERROR_FILE_REMOVE");
        case ERROR_FILE_RENAME:
            return tr("ERROR_FILE_RENAME");
        case ERROR_FILE_OPEN:
            return tr("ERROR_FILE_OPEN");
        case ERROR_FILE_NOT_EXIST:
            return tr("ERROR_FILE_NOT_EXIST");
        case ERROR_FILE_EMPTY:
            return tr("ERROR_FILE_EMPTY");
        case ERROR_FILE_KEY_NOT_EXIST:
            return tr("ERROR_FILE_KEY_NOT_EXIST");


        case ERROR_DIR_BASE:
            return tr("ERROR_DIR_BASE");
        case ERROR_DIR_STATFS:
            return tr("ERROR_DIR_STATFS");
        case ERROR_DIR_CREATE:
            return tr("ERROR_DIR_CREATE");
        case ERROR_DIR_SPACE_NOT_ENOUGH:
            return tr("ERROR_DIR_SPACE_NOT_ENOUGH");
        case ERROR_DIR_NOT_EXIST:
            return tr("ERROR_DIR_NOT_EXIST");


        case ERROR_ICONV_BASE:
            return tr("ERROR_ICONV_BASE");
        case ERROR_ICONV_OPEN:
            return tr("ERROR_ICONV_OPEN");
        case ERROR_ICONV_OPERATION:
            return tr("ERROR_ICONV_OPERATION");
        case ERROR_ICONV_CLOSE:
            return tr("ERROR_ICONV_CLOSE");


        case ERROR_IOCTL_BASE:
            return tr("ERROR_IOCTL_BASE");
        case ERROR_IOCTL_USBDEVFS_RESET:
            return tr("ERROR_IOCTL_USBDEVFS_RESET");


        case ERROR_FFMPEG_BASE:
            return tr("ERROR_FFMPEG_BASE");
        case ERROR_FFMPEG_FORMAT_NEW_STREAM:
            return tr("ERROR_FFMPEG_FORMAT_NEW_STREAM");
        case ERROR_FFMPEG_INVALID_ARGUMENT:
            return tr("ERROR_FFMPEG_INVALID_ARGUMENT");
        case ERROR_FFMPEG_RETURN_NULLPTR:
            return tr("ERROR_FFMPEG_RETURN_NULLPTR");
        case ERROR_FFMPEG_TARGET_STREAM_NOT_FOUND:
            return tr("ERROR_FFMPEG_TARGET_STREAM_NOT_FOUND");
        case ERROR_FFMPEG_PUSH_VIDEO_TIMEOUT:
            return tr("ERROR_FFMPEG_PUSH_VIDEO_TIMEOUT");
        case ERROR_FFMPEG_PUSH_VIDEO_START:
            return tr("ERROR_FFMPEG_PUSH_VIDEO_START");
        case ERROR_FFMPEG_PUSH_VIDEO_DEV_BUSY:
            return tr("ERROR_FFMPEG_PUSH_VIDEO_DEV_BUSY");
        case ERROR_FFMPEG_PUSH_VIDEO_HANDSHAKE:
            return tr("ERROR_FFMPEG_PUSH_VIDEO_HANDSHAKE");
        case ERROR_FFMPEG_PUSH_KILL_PROCESS:
            return tr("ERROR_FFMPEG_PUSH_KILL_PROCESS");


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


        case ERROR_LIFT_CTRL_BASE:
            return tr("ERROR_LIFT_CTRL_BASE");
        case ERROR_LIFT_CTRL_INPUT_OUTPUT:
            return tr("ERROR_LIFT_CTRL_INPUT_OUTPUT");
        case ERROR_LIFT_CTRL_NO_RESPONSE:
            return tr("ERROR_LIFT_CTRL_NO_RESPONSE");
        case ERROR_LIFT_CTRL_BUSY:
            return tr("ERROR_LIFT_CTRL_BUSY");
        case ERROR_LIFT_CTRL_ABNORMAL:
            return tr("ERROR_LIFT_CTRL_ABNORMAL");
        case ERROR_LIFT_CTRL_RECV_NOT_MATCH:
            return tr("ERROR_LIFT_CTRL_RECV_NOT_MATCH");
        case ERROR_LIFT_CTRL_OPERATING:
            return tr("ERROR_LIFT_CTRL_OPERATING");
        case ERROR_LIFT_CTRL_KEEP:
            return tr("ERROR_LIFT_CTRL_KEEP");
        case ERROR_LIFT_RESEND_TIMEOUT:
            return tr("ERROR_LIFT_RESEND_TIMEOUT");

        case ERROR_MECHANICAL_ARM_COLLISION:
            return tr("机械臂碰撞");
        case ERROR_MECHANICAL_ARM_CONTINUE_FAILD:
            return tr("机械臂急停恢复失败");
        case ERROR_MECHANICAL_ARM_GRAB_OBJECT_FAILD:
            return tr("机械臂抓取失败");
        case ERROR_MECHANICAL_ARM_INIT_FAILD:
            return tr("机械臂初始化失败");
        case ERROR_MECHANICAL_ARM_PAUSE_FAILD:
            return tr("机械臂暂停失败");
        case ERROR_MECHANICAL_ARM_PUT_OBJECT_FAILD:
            return tr("机械臂放置失败");
        case ERROR_MECHANICAL_ARM_REG_NO_OBJECT:
            return tr("视觉识别无餐盒");
        case ERROR_MECHANICAL_ARM_RELEASE_FAILD:
            return tr("机械臂释放夹爪失败");
        case ERROR_MECHANICAL_ARM_RESET_FAILD:
            return tr("机械臂重置失败");
        case ERROR_MECHANICAL_ARM_SPREAD_FAILD:
            return tr("机械臂预动作失败");


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
