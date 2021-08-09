#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>

#include <QDebug>
#include <QObject>

class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = nullptr);

    void GETresponseClient(const QString url);
    void POSTresponseClient(const QString url, const QString data);

private slots:
    void onReadyRead();
    void onDisconnect();

    // QTcpServer interface
protected:
    void incomingConnection(qintptr handle) override;

private:
    QStringList data;

};

#endif // HTTPSERVER_H
