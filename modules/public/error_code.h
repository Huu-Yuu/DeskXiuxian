#ifndef ERROR_CODE_H
#define ERROR_CODE_H


//错误码提取模板
#define ERROR_BASE_MASK                           int(0xFFFFF000)
//错误码模块提取模板
#define ERROR_CODE_MASK                           int(0x00000FFF)

//正常状态返回值
#define NO_ERROR                                  int(0)           //无错误

//AIUI官方错误码(取值重新映射)
#define ERROR_AIUI_MSP_INVALID_PARA               int(0xEE010101)  //参数名称错误(原值10106)
#define ERROR_AIUI_MSP_INVALID_PARA_VALUE         int(0xEE010102)  //参数取值错误(10107)
#define ERROR_AIUI_MSP_NOT_FOUND                  int(0xEE010103)  //云端无对应的scene场景参数(10116)
#define ERROR_AIUI_NO_RESPONSE_DATA               int(0xEE010104)  //结果等待超时(10120)
#define ERROR_AIUI_MSP_LMOD_RUNTIME_EXCEPTION     int(0xEE010105)  //MSC内部错误(16005)
#define ERROR_AIUI_NO_NETWORK                     int(0xEE010106)  //无有效的网络连接(20001)
#define ERROR_AIUI_NETWORK_TIMEOUT                int(0xEE010107)  //网络连接超时(20002)
#define ERROR_AIUI_NET_EXPECTION                  int(0xEE010108)  //网络连接发生异常(20003)
#define ERROR_AIUI_INVALID_RESULT                 int(0xEE010109)  //无有效的结果(20004)
#define ERROR_AIUI_NO_MATCH                       int(0xEE01010A)  //无匹配结果(20005)
#define ERROR_AIUI_AUDIO_RECORD                   int(0xEE01010B)  //录音失败(20006)
#define ERROR_AIUI_COMPONENT_NOT_INSTALLED        int(0xEE01010C)  //没有安装服务组件(21001)
#define ERROR_AIUI_SERVICE_BINDER_DIED            int(0xEE01010D)  //与服务的绑定已消亡(21020)
#define ERROR_AIUI_LOCAL_NO_INIT                  int(0xEE01010E)  //本地引擎未初始化(22001)
#define ERROR_AIUI_UNKNOWN                        int(0xEE01010F)  //未知错误(20999)

// 数据库操作错误宏定义
#define DB_ERROR_INVALID_QUERY          int(0xEE020101)  // 无效的查询语句
#define DB_ERROR_CONNECTION_FAILED      int(0xEE020102)  // 连接数据库失败
#define DB_ERROR_EXECUTION_FAILED       int(0xEE020103)  // 执行数据库操作失败
#define DB_ERROR_RECORD_NOT_FOUND       int(0xEE020104)  // 未找到记录
#define DB_ERROR_DUPLICATE_KEY          int(0xEE020105)  // 主键重复
#define DB_ERROR_ACCESS_DENIED          int(0xEE020106)  // 访问被拒绝
#define DB_ERROR_TIMEOUT                int(0xEE020107)  // 操作超时
#define DB_ERROR_CONNECTION_LOST        int(0xEE020108)  // 与数据库的连接丢失
#define DB_ERROR_INVALID_TABLE          int(0xEE020109)  // 无效的表名
#define DB_ERROR_INVALID_COLUMN         int(0xEE02010A)  // 无效的列名
#define DB_ERROR_TRANSACTION_FAILED     int(0xEE02010B)  // 事务执行失败
#define DB_ERROR_LOCK_TIMEOUT           int(0xEE02010C)  // 获取锁超时
#define DB_ERROR_CONSTRAINT_VIOLATION   int(0xEE02010D)  // 违反约束条件
#define DB_ERROR_INVALID_DATA           int(0xEE02010E)  // 无效的数据
#define DB_ERROR_DISK_FULL              int(0xEE02010F)  // 磁盘空间已满

//数据库函数错误码(模块代号037，名称QSQL)
#define ERROR_QSQL_BASE                           int(0xEE037000)  //SQL错误
#define ERROR_QSQL_UPDATE                         int(0xEE037001)  //SQL更新错误
#define ERROR_QSQL_DELETE                         int(0xEE037002)  //SQL删除错误
#define ERROR_QSQL_CREATE                         int(0xEE037003)  //SQL创建错误
#define ERROR_QSQL_SELECT                         int(0xEE037004)  //SQL选中错误
#define ERROR_QSQL_OPEN                           int(0xEE037005)  //SQL打开错误
#define ERROR_QSQL_INSERT                         int(0xEE037006)  //SQL插入错误
#define ERROR_QSQL_EMPTY                          int(0xEE037007)  //SQL为空

//配置文件错误码(模块代号038，名称SETTING_FILE)
#define ERROR_SETTING_FILE_BASE                   int(0xEE038000)  //配置文件错误
#define ERROR_SETTING_FILE_NOT_LOAD               int(0xEE038001)  //配置文件未加载

//网络通信错误码(模块代号022, 名称:NETWORK)
#define ERROR_NETWORK_BASE                        int(0xEE022000)  //网络通信错误
#define ERROR_NETWORK_DISCONNECTED                int(0xEE022001)  //网络连接断开
#define ERROR_NETWORK_HEAD_NOT_MATCH              int(0xEE022002)  //网络接收包头信息不匹配
#define ERROR_NETWORK_UUID_NOT_MATH               int(0xEE022003)  //网络UUID不匹配
#define ERROR_NETWORK_UNKNOW_CMAD                 int(0xEE022004)  //未知网络指令
#define ERROR_NETWORK_REQUEST_REJECT              int(0xEE022005)  //服务器拒绝请求
#define ERROR_NETWORK_RESEND_OVERTIMES            int(0xEE022006)  //网络重发超过限定次数
#define ERROR_NETWORK_COMMU_REFUSE                int(0xEE022007)  //服务器拒绝通信
#define ERROR_NETWORK_HEAD_NOT_VAILD              int(0xEE022008)  //接收到数据不合法

//网络文件传输错误码(模块代号0223, 名称:NETFILE)
#define ERROR_NETFILE_BASE                        int(0xEE022300)  //网络文件传输错误
#define ERROR_NETFILE_DISCONNECTED                int(0xEE022301)  //网络文件传输连接断开
#define ERROR_NETFILE_DIR_CREATE                  int(0xEE022302)  //创建文件夹失败
#define ERROR_NETFILE_SEND_FILE_NOT_EXIST         int(0xEE022303)  //发送文件不存在
#define ERROR_NETFILE_SEND_FILE_OPEN              int(0xEE022304)  //发送文件打开失败
#define ERROR_NETFILE_SEND_CONTENT                int(0xEE022305)  //发送写网络端口失败
#define ERROR_NETFILE_SEND_NOT_MATCH              int(0xEE022306)  //发送文件参数与之前不匹配
#define ERROR_NETFILE_FILE_NOT_READABLE           int(0xEE022307)  //发送文件不可读
#define ERROR_NETFILE_RECV_FILE_NOT_EXIST         int(0xEE022308)  //接收文件不存在
#define ERROR_NETFILE_RECV_FILE_OPEN              int(0xEE022309)  //接收文件打开失败
#define ERROR_NETFILE_RECV_CONTENT                int(0xEE02230A)  //接收文件写失败
#define ERROR_NETFILE_RECV_NOT_MATCH              int(0xEE02230B)  //传输文件参数与之前不匹配
#define ERROR_NETFILE_FILE_NOT_WRITABLE           int(0xEE02230C)  //传输文件不可写
#define ERROR_NETFILE_RECV_SIZE_NOT_MATCH         int(0xEE02230D)  //接收文件片段大小不匹配
#define ERROR_NETFILE_RECV_UUID_NOT_MATCH         int(0xEE02230E)  //接收文件片段UUID不匹配

#define ERROR_NETFILE_WRITE_SOCKET                int(0xEE022310)  //网络文件写入数据错误

//QSocket错误(模块代号023, 名称:QSOCKET)
//错误码采用位或形式生成，更多解释请查看Qt文档QAbstractSocket::SocketError条目)
#define ERROR_QSOCKET_BASE                        int(0xEE023000)  //网络套接字错误
#define ERROR_QSOCKET_REMOTE_HOST_CLOSE           int(0xEE023001)  //远程主机关闭
#define ERROR_QSOCKET_HOST_NOT_FOUND              int(0xEE023002)  //找不到主机地址
#define ERROR_QSOCKET_ACCESS                      int(0xEE023003)  //无法访问
#define ERROR_QSOCKET_SOURCE_RAN_OUT              int(0xEE023004)  //连接数已达上限
#define ERROR_QSOCKET_TIMEOUT                     int(0xEE023005)  //超时错误
#define ERROR_QSOCKET_DATAGRAM_TOO_LARGE          int(0xEE023006)  //数据报过长（超过8K）
#define ERROR_QSOCKET_NETWORK                     int(0xEE023007)  //网络连接错误（网线可能被拔出）
#define ERROR_QSOCKET_ACCESS_IN_USE               int(0xEE023008)  //网络地址被占用
#define ERROR_QSOCKET_ADDR_NOT_AVAILABLE          int(0xEE023009)  //访问地址不存在
#define ERROR_QSOCKET_UNSUPPORT_OPERATION         int(0xEE02300A)  //系统不支持该操作（如缺少IPv6协议支持）
#define ERROR_QSOCKET_PROXY_AUT_REQ               int(0xEE02300B)  //需要代理授权支持
#define ERROR_QSOCKET_SSL_HANDSHAKE               int(0xEE02300C)  //SSL握手失败
#define ERROR_QSOCKET_UNFINISHED_OPERATION        int(0xEE02300D)  //操作未完成
#define ERROR_QSOCKET_PROXY_CONNECT_REFUSE        int(0xEE02300E)  //代理服务器拒绝连接
#define ERROR_QSOCKET_PROXY_CONNECT_CLOSE         int(0xEE02300F)  //代理服务器意外关闭
#define ERROR_QSOCKET_PROXY_CONNECT_TIMEOUT       int(0xEE023010)  //代理连接超时
#define ERROR_QSOCKET_PROXY_NOT_FOUND             int(0xEE023011)  //没有找到代理服务器
#define ERROR_QSOCKET_PROXY_PROTOCOL              int(0xEE023012)  //代理服务器返回信息错误
#define ERROR_QSOCKET_OPERATION                   int(0xEE023013)  //操作错误
#define ERROR_QSOCKET_SSL_INTERNAL                int(0xEE023014)  //SSL内部错误
#define ERROR_QSOCKET_SSL_INVALID_USER_DATA       int(0xEE023015)  //SSL非法用户数据
#define ERROR_QSOCKET_TEMPORARY                   int(0xEE023016)  //临时错误
#define ERROR_QSOCKET_FILE                        int(0xEE023017)  //对方拒绝连接或超时
#define ERROR_QSOCKET_UNKNOW                      int(0xEE023099)  //未知错误
//追加自定义错误（开始地址0xEE023400）
#define ERROR_QSOCKET_WRITE                       int(0xEE023401)  //发送数据错误

#endif // ERROR_CODE_H
