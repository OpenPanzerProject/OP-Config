#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    // Trying to measure progress using a QNetworkReply object ended up being too much
    // work, and according to some, not very useful when the file size isn't returned.
    // http://www.bogotobogo.com/Qt/Qt5_QNetworkRequest_Http_File_Download.php

    // Connect progress and finished to our slot
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

Downloader::~Downloader() { }

void Downloader::startDownload(QString url)
{
    // Start the download
    manager.get(QNetworkRequest(QUrl(url)));
}

void Downloader::downloadFinished(QNetworkReply* reply)
{
    // Save the file as a QByteArray
    qbaDownloadedData = reply->readAll();

    if(reply->error())
    {
        //qDebug() << "File download error: " << reply->errorString();

        // emit a signal
        emit downloadFailed();
    }
    else
    {
        //qDebug() << "Content type: " << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        //qDebug() << "Last modified: " << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        //qDebug() << "File size: " << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        //qDebug() << "HTTP Status Code Attribute: " << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        //qDebug() << "HTTP Reason Phrase: " << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        //emit a signal
        emit downloadSuccess();
    }
    reply->deleteLater();
}


QByteArray Downloader::downloadedData() const
{
    return qbaDownloadedData;
}





