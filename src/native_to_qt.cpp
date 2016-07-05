#include <QVariant>
#include "native_to_qt.h"

controller::controller(QObject *obj) : root_{obj} {}

void controller::add_circle(const double x, const double y, const double r)
{
	if (circles_.size() > 1) circles_.pop_back();

	circles_.emplace(circles_.begin(), point{x, y}, r);

	QMetaObject::invokeMethod(root_, "clear_context");

	for (const auto &x : circles_) {
		QVariant centre_x = x.centre().x();
		QVariant centre_y = x.centre().y();
		QVariant radius = x.radius();
		QMetaObject::invokeMethod(
			root_, "draw_circle", Q_ARG(QVariant, centre_x),
			Q_ARG(QVariant, centre_y), Q_ARG(QVariant, radius));
	}

	if (circles_.size() == 2) {
		std::vector<line> tangents;
		tangent_lines(circles_.back(), circles_.front(),
					  std::back_inserter(tangents));
		for (const auto &tangent : tangents) {
			QVariant a_x = tangent.begin().x();
			QVariant a_y = tangent.begin().y();
			QVariant b_x = tangent.end().x();
			QVariant b_y = tangent.end().y();
			QMetaObject::invokeMethod(
				root_, "draw_line", Q_ARG(QVariant, a_x), Q_ARG(QVariant, a_y),
				Q_ARG(QVariant, b_x), Q_ARG(QVariant, b_y));
		}
	}
	QMetaObject::invokeMethod(root_, "draw");
}
