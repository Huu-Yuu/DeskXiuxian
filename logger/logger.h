#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QThread>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = nullptr);
    ~Logger();
signals:

public slots:
    void log(QtMsgType type, const QMessageLogContext& context, const QString& message);

private:
    QFile logFile_;
    QTextStream logStream_;
    QThread thread_;

};

#endif // LOGGER_H
