#include "mainui.h"
#include "ui_mainui.h"

MainUI::MainUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainUI)
{
    ui->setupUi(this);
    // 设置logo
    setWindowIcon(QIcon(":/res/logo.jpg"));

    // 设置窗口标题
    setWindowTitle("桌面修仙");

    // 固定窗口
    setFixedSize(width(),height());

    // 将窗口居中显示
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size(),
                    qApp->desktop()->availableGeometry()
                    )
                );

    //外层widget布局
    ui->centralwidget->setLayout(ui->outerLayout);

    //主角选项卡布局
    ui->role_page->setLayout(ui->role_Layout);
    ui->bisic_Att_Box->setLayout(ui->bisic_Layout);
    ui->equipment_Box->setLayout(ui->equipment_Layout);

    /////////////测试代码
    QTimer *timer = new QTimer;
    timer->setInterval(1000); // 设置定时器间隔为 1 秒
    timer->setSingleShot(false); // 设置定时器为非单次触发

    // 连接定时器的 timeout() 信号到槽函数
    QObject::connect(timer, &QTimer::timeout, this,&MainUI::SlotShowMsg);
    timer->start();

    // 创建日志记录器
    logger_ = Logger::GetInstance();

    // 将日志记录器的 log() 槽连接到 Qt 的日志处理器
    QObject::connect(this, SIGNAL(SignalLogOut(QtMsgType, const QMessageLogContext&, const QString&)),
                     logger_, SLOT(log(QtMsgType, const QMessageLogContext&, const QString&)));

}

MainUI::~MainUI()
{
    delete ui;
}

void MainUI::AddMessage(QString& msg)
{
    QString time_stamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm:ss");

    QString display_text = time_stamp + "：" + msg;

    ui->listWidget->addItem(display_text);
    // 滚动到底部
    // 延迟滚动到底部
    QTimer::singleShot(0, this, [this]() {
        QScrollBar* scrollbar = ui->listWidget->verticalScrollBar();
        scrollbar->setValue(scrollbar->maximum());
    });
    // 将消息记录到日志
    emit SignalLogOut(QtDebugMsg, QMessageLogContext(), msg);
}

Ui::MainUI* MainUI::GetUI()
{
    return ui;
}

