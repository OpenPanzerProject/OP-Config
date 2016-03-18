#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    virtual ~Downloader();
    void startDownload(QString url);
    QByteArray downloadedData() const;

private slots:
    void downloadFinished(QNetworkReply* pReply);

private:
    QNetworkAccessManager manager;
    QByteArray qbaDownloadedData;

signals:
    void downloadSuccess();
    void downloadFailed();
};


#endif // DOWNLOADER_H
