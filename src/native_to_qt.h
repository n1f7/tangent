#ifndef native_to_qt_
#define native_to_qt_

#include <iostream>
#include <vector>
#include <cmath>

#include <QObject>

#include "point.h"
#include "line.h"
#include "circle.h"

class controller : public QObject
{
	Q_OBJECT

	QObject *root_;
	std::vector<circle> circles_;

public:
	explicit controller(QObject *);

public slots:
	void add_circle(const double, const double, const double);
};

#endif
