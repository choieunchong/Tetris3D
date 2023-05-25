pragma once

#include <QWidget>
#include "ui_QtInputClass.h"

class QtInputClass : public QWidget
{
	Q_OBJECT

public:
	QtInputClass(QWidget *parent = nullptr);
	~QtInputClass();

private:
	Ui::QtInputClassClass ui;
};
