/**
 *******************************************************************************
 * @file    error_display.h
 * @author  JunChao.Yuan
 * @version V1.1.2
 * @date    2019.09.24
 * @brief   错误码显示头文件
 *******************************************************************************
 * 版本说明:
 *  V1.0.0 完成代码的整体框架，功能函数的封装
 *  V1.1.0 代码规范化;添加注释;
 */

#ifndef PUBLIC_ERROR_DISPLAY
#define PUBLIC_ERROR_DISPLAY

#include "error_code.h"

#include <QObject>
#include <QFile>
#include <QString>
#include <QMutex>


/**
 * @brief 错误显示类
 * @note 本类全部为全局函数
 */
class ErrorDisplay : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 获取错误码基类型
     * @param error_code：错误码
     * @return 错误码位与ERROR_BASE_MASK部分
     */
    static int GetErrorBaseType(int error_code);

    /**
     * @brief 获取错误码基编号
     * @param error_code：错误码
     * @return 错误码位与ERROR_CODE_MASK部分
     */
    static int GetErrorBaseCode(int error_code);

    /**
     * @brief 获取错误信息函数
     * @param error_code：错误码
     * @param display_mode：信息显示模式
     * @return 错误信息
     * @note display_mode不同取值对应输出如下：
     *       0：(错误类型)：错误码：xxx
     *       1：(错误类型)：错误描述：xxx
     *       2：(错误类型)：错误码：xxx，错误描述：xxx
     *       3：错误码：xxx，错误描述：xxx
     *       4：(错误描述)
     */
    static QString GetErrorInfo(int error_code, int display_mode = 4);

    /**
     * @brief 获取错误信息函数
     * @param error_code：错误码
     * @param with_descrip：是否显示错误描述
     * @param with_type：是否显示错误类型
     * @param with_prefix：是否带错误定义前缀(如：‘错误码：’) - ()控制项
     * @return 错误信息
     * @note 完整样式为: 错误类型：xxx，错误码：xxx，错误描述：xxx
     */
    static QString GetErrorInfo(int error_code,  bool with_prefix,
                                bool with_descrip = true, bool with_type = false);

    /**
     * @brief 错误码转为16进制的字符串格式函数
     * @param error_code：int型错误码
     * @return 字符串格式错误码
     * @note 例：错误码0xEE000001的字符串格式为”0xEE000001“
     */
    static QString GetErrorCodeString(int error_code);

    static int64_t GetErrorCodeFromString(QString error_code);

    /**
     * @brief 获取错误类型函数
     * @param error_code：错误码
     * @return 错误类型
     * @note 错误类型为error_code.h中各类第一个xxx_BASE注释信息，修改在翻译文件中修改。
     */
    static QString GetErrorTypeName(int error_type_base);

    /**
     * @brief 获取错误描述函数
     * @param error_code：错误码
     * @return 错误描述
     * @note 错误描述为error_code.h中错误码后方注释信息，修改在翻译文件中修改。
     */
    static QString GetErrorDescription(int error_code);

    static void OutputMessageToFile(const QString log_file_path,
                                    const QString& message);

protected:
    /**
     * @brief 类构造函数
     */
    ErrorDisplay();

private:
    //调试信息输出锁
    static QMutex std_log_mutex;
    static QMutex custom_log_mutex;
};

#endif // PUBLIC_ERROR_DISPLAY

