#include "httpserver.h"

HttpServer::HttpServer(QObject *parent)
    : QTcpServer(parent)
{
    if (listen(QHostAddress::LocalHost, 80)) {
        qDebug() << "Start http server...";
    } else {
        qDebug() << "Error: " << errorString();
    }
}

void HttpServer::POSTresponseClient(const QString url, const QString data)
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    if (socket->isOpen()) {
        QString response = "HTTP/1.1 200 OK\r\n\r\n";

        if (url == "/data") {
            this->data.append(data);
        }

        socket->write(response.toUtf8());
    }
}

void HttpServer::GETresponseClient(const QString url)
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    if (socket->isOpen()) {
        QString response = "HTTP/1.1 200 OK\r\n";
        response.append("Content-Type: text/html; charset=UTF-8\r\n\r\n");

        QString body = "";

        if (url == "/") {
            body = QTime::currentTime().toString();
        } else if (url == "/test") {
            body = "<!DOCTYPE html> <html lang=\"en\"> <head> <title>Test page</title> <meta charset=\"utf8\"> </head> <body> <h1 style=\"text-align: center;\">Hello World</h1> </body> </html>";
        } else if (url == "/data") {
            QString dataPageHtml = "<!DOCTYPE html> <html lang=\"en\"> <head> <title>Test page</title> <meta charset=\"utf8\"> </head> <body> <ul>:d</ul> </body> </html>";
            QString list;

            for (const auto &str : this->data) {
                list.append("<li>" + str + "</li>");
            }

            dataPageHtml.replace(":d", list);
            body = dataPageHtml;
        }

        response.append(body);

        socket->write(response.toUtf8());
    }
}

void HttpServer::onReadyRead()
{
    qDebug() << "Connect client...";
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    QString headersString = socket->readAll().toStdString().c_str();
    QStringList headers = headersString.split("\r\n");

    QString method = headers.first().split(" ")[0];
    QString url = headers.first().split(" ")[1];
    QString data = headers.last();

    for (const auto &header : headers) {
        qDebug() << header;
    }

    if (method == "GET") {
        GETresponseClient(url);
    } else if ("POST") {
        POSTresponseClient(url, data);
    }

    socket->disconnectFromHost();
}

void HttpServer::onDisconnect()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    socket->close();
    socket->deleteLater();

    qDebug() << "Disconnect client...";
}

void HttpServer::incomingConnection(qintptr handle)
{
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(handle);

    connect(socket, &QTcpSocket::readyRead, this, &HttpServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &HttpServer::onDisconnect);
}
