#pragma once

#include <QObject>

class BleDutControl : public QObject
{
    Q_OBJECT
public:
    explicit BleDutControl(QObject *parent = nullptr);

    ~BleDutControl();

public slots:

    int open(QString name);
    int close();

    int reset();
    int leTxTest(int freq, int payload, int len);
    int leTestEnd();

private:
    QString m_hciName;
    int m_sock = -1;

};
