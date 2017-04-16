#ifndef _COMMENINCLUDE_H_
#define _COMMENINCLUDE_H_

#include <iostream>
#include <QtCore\qbytearray.h>
#include <QtCore\qstring.h>
#include <QtCore\qqueue.h>

#include <QtCore\qjsondocument.h>
#include <QtCore\qjsonobject.h>
#include <QtCore\qjsonarray.h>

#include <QtCore\qthread.h>
#include <QtCore\qtimer.h>
#include <QtCore\qfile.h>
#include <QtCore\qtextstream.h>
#include <QtCore\qtextcodec.h>
#include <QtCore\qeventloop.h>

#include <QtCore\qcryptographichash.h>

#include <QtNetwork\qnetworkreply.h>
#include <QtNetwork\qnetworkrequest.h>
#include <QtNetwork\qnetworkcookie.h>
#include <QtNetwork\qnetworkcookiejar.h>
#include <QtNetwork\qnetworksession.h>
#include <QtNetwork\qnetworkconfigmanager.h>
#include <QtNetwork\qnetworkconfiguration.h>

#include <QtSql\qsqldatabase.h>
#include <QtSql\qsqlquery.h>
#include <QtSql\qsqlerror.h>

#include <zlib.h>

double getDoubleFromQJsonValueRef(QJsonValueRef data, int & flag);
double getDoubleFromQJsonObject(QJsonObject data, QString key, int & flag);
QString getStringFromQJsonValueRef(QJsonValueRef data, int & flag);
QString getStringFromQJsonObject(QJsonObject data, QString key, int & flag);
int decompress(QByteArray source, QByteArray * dest);

#endif