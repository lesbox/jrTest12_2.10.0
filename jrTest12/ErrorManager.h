#ifndef _ERRORMANAGER_H_
#define _ERRORMANAGER_H_

#include "Commen.h"

class ErrorManager {
public:
	QString errorInfo;

public:
	ErrorManager();
	~ErrorManager();

	void clear();
	void pushErrorInfo(QString errorInfo);
	QString getErrorInfo();
};

#endif
