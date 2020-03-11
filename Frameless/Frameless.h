#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Frameless.h"

class Frameless : public QMainWindow
{
	Q_OBJECT

public:
	Frameless(QWidget *parent = Q_NULLPTR);

private:
	Ui::FramelessClass ui;

public:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	bool event(QEvent *event);
	void mousePressEvent(QMouseEvent *e);
};
