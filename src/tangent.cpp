#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QQuickItem>

#include "native_to_qt.h"

int main(int argc, char **argv)
{
	QGuiApplication app{argc, argv};
	QQuickView view;
	view.setSource(QUrl{"qrc:/gui.qml"});
	view.rootContext()->setContextProperty("controller",
										   new controller{view.rootObject()});
	view.show();
	return app.exec();
}
