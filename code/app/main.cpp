#include <QApplication>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>

#include "mainwindow.h"
#include "JsonStorage.h"
#include "EventManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    EventManager manager;

    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    JsonStorage storage((dir + "/events.json").toStdString());

    try {
        for (const auto& e : storage.load()) {
            manager.create(e);
        }
    } catch (...) {

    }

    QObject::connect(&app, &QApplication::aboutToQuit, [&]() {
        try {
            storage.save(manager.all());
        } catch (...) {

        }
    });

    MainWindow w(manager);
    w.show();

    QApplication::setQuitOnLastWindowClosed(false);

    return app.exec();
}
