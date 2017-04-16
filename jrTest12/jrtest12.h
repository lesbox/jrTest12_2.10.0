#ifndef JRTEST12_H
#define JRTEST12_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets\qplaintextedit.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qlayout.h>
#include <QtCore\qtimer.h>
#include <QtCore\qdatetime.h>
#include "BehaviourManager.h"
#include "ui_jrtest12.h"

class jrTest12 : public QMainWindow
{
	Q_OBJECT

public:
	BehaviourManager mainBehaviour;

public:
	jrTest12(QWidget *parent = 0);
	~jrTest12();

private:
	QVector<QLabel *> describe_pveExplore_logPrinter;
	QVector<QPlainTextEdit *> pveExplore_logPrinter;
	QVector<QLabel *> describe_pveExplore_timePrinter;
	QVector<QLabel *> pveExplore_timePrinter;
	QVector<QTime *> pveExplore_behaviourTime;

	QVector<QLabel *> describe_repairShip_logPrinter;
	QVector<QPlainTextEdit *> repairShip_logPrinter;
	QVector<QLabel *> describe_repairShip_timePrinter;
	QVector<QLabel *> repairShip_timePrinter;
	QVector<QTime *> repairShip_behaviourTime;

	QLabel * describe_updatePvpStatus_logPrinter;
	QPlainTextEdit * updatePvpStatus_logPrinter;
	QLabel * describe_updatePvpStatus_timePrinter;
	QLabel * updatePvpStatus_timePrinter;
	QTime * updatePvpStatus_behaviourTime;

	QLabel * describe_updateDrop500Status_logPrinter;
	QPlainTextEdit * updateDrop500Status_logPrinter;
	QLabel * describe_updateDrop500Status_timePrinter;
	QLabel * updateDrop500Status_timePrinter;
	QTime * updateDrop500Status_behaviourTime;

	QLabel * describe_logPrinter;
	QPlainTextEdit * logPrinter;
	QLabel * describe_timePrinter;
	QLabel * timePrinter;
	QTime * behaviourTime;

	QWidget * centralWidget;
	QGridLayout * mainLayout;
	QWidget * extraInformationWidget;
	QGridLayout * extraInformationLayout;

	QTimer * behaviourTimer;

	int collect505Count;
	QLabel * describe_collect505Num;
	QLabel * collect505Num;

	int stealOilCount;
	QLabel * describe_stealOilNum;
	QLabel * stealOilNum;

	int stealAmmoCount;
	QLabel * describe_stealAmmoNum;
	QLabel * stealAmmoNum;

	int stealAluminiumCount;
	QLabel * describe_stealAluminiumNum;
	QLabel * stealAluminiumNum;

	QLabel * describe_spoilNum;
	QLabel * spoilNum;

public slots:
	bool behaviourTimerTimeout();
	bool appendNextLog(int outputId, QString logInfo);
};

#endif // JRTEST12_H
