//
// Created by bryan on 2025-11-07.
//
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QHeaderView>
#include <QDateTime>
#include <QItemSelectionModel>
#include <QCloseEvent>
#include <chrono>

#include "EventDialog.h"
#include "searchwindow.h"
#include "DateRange.h"

using namespace std;
using namespace std::chrono;

enum Columns : int { COL_TITLE = 0, COL_START = 1, COL_END = 2, COL_LOCATION = 3 };

// Helper function to convert from chrono::time_point to QString
QString MainWindow::tpToQString(Event::TimePoint tp, const char* fmt) {
    using namespace std::chrono;
    auto secs = time_point_cast<seconds>(tp).time_since_epoch().count();
    return QDateTime::fromSecsSinceEpoch(static_cast<qint64>(secs), Qt::LocalTime)
        .toString(fmt);
}

// Helper function to convert from QDateTime to TimePoint
Event::TimePoint MainWindow::qdtToTimePoint(const QDateTime& dt) {
    using namespace std::chrono;
    return system_clock::time_point{ seconds{ dt.toSecsSinceEpoch() } };
}

// Constructor
MainWindow::MainWindow(EventManager& manager, QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::MainWindow)
    , _manager(manager)
    , _model(new QStandardItemModel(this))
{
    _ui->setupUi(this);

    // Setting up the tray
    _tray = new QSystemTrayIcon(QIcon(":/icons/app.png"), this);
    _reminders.setTrayIcon(_tray);

    auto *menu = new QMenu(this);
    auto *showAction = new QAction("Show Timely");
    auto *quitAction = new QAction("Quit");

    menu->addAction(showAction);
    menu->addAction(quitAction);
    connect(showAction, &QAction::triggered, this, [this]() {
        this->show();
        this->raise();
        this->activateWindow();
    });

    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);

    // Quit Action Button
    connect(_ui->actionQuit, &QAction::triggered, this, [this]() {
        _tray->hide();   // clean tray removal
        qApp->quit();
    });

    _tray->setContextMenu(menu);
    _tray->show();

    // Opening the app again from the tray when you double click the icon
    connect(_tray, &QSystemTrayIcon::activated, this,
            [this](QSystemTrayIcon::ActivationReason reason) {
                if (reason == QSystemTrayIcon::DoubleClick) {
                    this->show();
                    this->raise();
                    this->activateWindow();
                }
            });

    // Configuring the event table
    _model->setHorizontalHeaderLabels({"Title", "Start", "End", "Location"});
    _ui->eventsView->setModel(_model);
    _ui->eventsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _ui->eventsView->setSelectionMode(QAbstractItemView::SingleSelection);
    _ui->eventsView->horizontalHeader()->setStretchLastSection(true);
    _ui->eventsView->verticalHeader()->setVisible(false);
    _ui->eventsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Signals for buttons
    connect(_ui->actionNew, &QAction::triggered, this, &MainWindow::onNew);
    connect(_ui->actionEdit, &QAction::triggered, this, &MainWindow::onEdit);
    connect(_ui->actionDelete, &QAction::triggered, this, &MainWindow::onDelete);
    connect(_ui->actionToday, &QAction::triggered, this, &MainWindow::onToday);
    connect(_ui->actionSearch, &QAction::triggered, this, &MainWindow::onSearch);

    connect(_ui->eventsView, &QTableView::doubleClicked,
            this, &MainWindow::onEventClicked);


    connect(_ui->calendar, &QCalendarWidget::selectionChanged,
            this, &MainWindow::onCalendarDateChanged);

    // Auto-refresh when data changes
    _manager.subscribe([this]{
        refreshForDate(_ui->calendar->selectedDate());
        _reminders.rescheduleAll(_manager.all());
    });

    _ui->calendar->setSelectedDate(QDate::currentDate());
    refreshForDate(_ui->calendar->selectedDate());
    _reminders.rescheduleAll(_manager.all());
}

MainWindow::~MainWindow() { delete _ui; }

// Helper functions
void MainWindow::refreshForDate(const QDate& d) {
    _model->removeRows(0, _model->rowCount());

    const auto events = _manager.onDate(d.year(), d.month(), d.day());
    for (const auto& ev : events) {
        auto* title = new QStandardItem(QString::fromStdString(ev.getTitle()));
        title->setData(QString::fromStdString(ev.getId()), Qt::UserRole);

        auto* start = new QStandardItem(tpToQString(ev.getStart(), "HH:mm"));
        auto* end = new QStandardItem(ev.getEnd() ? tpToQString(*ev.getEnd(), "HH:mm")
                                                  : QString("All day"));
        auto* loc = new QStandardItem(ev.getLocation()
                                          ? QString::fromStdString(*ev.getLocation())
                                          : QString());

        _model->appendRow({title, start, end, loc});
    }

    _ui->eventsView->resizeColumnToContents(COL_START);
    _ui->eventsView->resizeColumnToContents(COL_END);

    statusBar()->showMessage(
        QString("%1 event(s) on %2")
            .arg(_model->rowCount())
            .arg(d.toString("yyyy-MM-dd"))
        );
}

// Function to populate the events table after a search query is requested.
void MainWindow::populateEventsTable(const std::vector<Event>& events, const QString& statusMsg) {
    _model->removeRows(0, _model->rowCount());

    // Getting all the information about the current event
    for (const auto& ev : events) {
        auto* title = new QStandardItem(QString::fromStdString(ev.getTitle()));
        title->setData(QString::fromStdString(ev.getId()), Qt::UserRole);

        auto* start = new QStandardItem(tpToQString(ev.getStart(), "yyyy-MM-dd HH:mm"));
        auto* end = new QStandardItem(ev.getEnd() ? tpToQString(*ev.getEnd(), "yyyy-MM-dd HH:mm") : QString("All day"));

        auto* loc = new QStandardItem(ev.getLocation() ? QString::fromStdString(*ev.getLocation()) : QString());

        _model->appendRow({title, start, end, loc});
    }

    _ui->eventsView->resizeColumnToContents(COL_START);
    _ui->eventsView->resizeColumnToContents(COL_END);

    if (!statusMsg.isEmpty()) {
        statusBar()->showMessage(statusMsg);
    }
}


std::optional<Event> MainWindow::findById(const std::string& id) const {
    // no core getById? do a simple scan
    auto all = _manager.all();
    for (const auto& e : all) {
        if (e.getId() == id) return e;
    }
    return std::nullopt;
}

// slot functions for toolbar buttons
void MainWindow::onToday() {
    _ui->calendar->setSelectedDate(QDate::currentDate());
}

void MainWindow::onCalendarDateChanged() {
    refreshForDate(_ui->calendar->selectedDate());
}

void MainWindow::onNew() {
    // prefill date from calendar
    QDate d = _ui->calendar->selectedDate();
    EventDialog dlg(this);
    dlg.prefillDate(d);
    if (dlg.exec() != QDialog::Accepted) return;

    // building Events (EventManager assigns id automatically)
    Event ev(
        "",                                       // id
        dlg.title(),                              // title
        qdtToTimePoint(dlg.startDateTime()),      // start
        dlg.hasEnd() ? std::optional<Event::TimePoint>{ qdtToTimePoint(dlg.endDateTime()) }
                     : std::nullopt,              // end (optional)
        dlg.category(),                           // optional<Category>
        dlg.location(),                           // optional<string>
        dlg.notes()                               // optional<string>
        );

    ev.setRemindersMinutesBefore(dlg.remindersMinutesBefore());
    _manager.create(ev);
}

void MainWindow::onEdit() {
    auto sel = _ui->eventsView->selectionModel()->selectedRows();
    if (sel.isEmpty()) {
        QMessageBox::information(this, "Edit", "Select an event to edit.");
        return;
    }
    int row = sel.first().row();
    auto* titleItem = _model->item(row, COL_TITLE);
    const QString qid = titleItem->data(Qt::UserRole).toString();
    if (qid.isEmpty()) {
        QMessageBox::warning(this, "Edit", "Missing event id.");
        return;
    }
    auto existing = findById(qid.toStdString());
    if (!existing) {
        QMessageBox::warning(this, "Edit", "Event not found.");
        return;
    }

    EventDialog dlg(this);
    dlg.setEvent(*existing);
    if (dlg.exec() != QDialog::Accepted) return;

    // Keep same id; replace other fields
    Event updated(
        existing->getId(),
        dlg.title(),
        qdtToTimePoint(dlg.startDateTime()),
        dlg.hasEnd() ? std::optional<Event::TimePoint>{ qdtToTimePoint(dlg.endDateTime()) }
                     : std::nullopt,
        dlg.category(),
        dlg.location(),
        dlg.notes()
        );

    updated.setRemindersMinutesBefore(dlg.remindersMinutesBefore());
    _manager.update(updated);
}

void MainWindow::onDelete() {
    auto sel = _ui->eventsView->selectionModel()->selectedRows();
    if (sel.isEmpty()) return;
    int row = sel.first().row();
    auto* titleItem = _model->item(row, COL_TITLE);
    const QString qid = titleItem->data(Qt::UserRole).toString();
    if (qid.isEmpty()) return;

    if (QMessageBox::question(this, "Delete", "Delete selected event?") == QMessageBox::Yes) {
        _manager.remove(qid.toStdString());
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    this->hide();
    event->ignore();

    if (_tray) {
        _tray->showMessage("Timely", "Timely is still running in the background. Use the icon to reopen", QSystemTrayIcon::Information, 5000);
    }
}

void MainWindow::onEventClicked(const QModelIndex& index) {
    if (!index.isValid()) return;

    int row = index.row();

    auto* titleItem = _model->item(row, COL_TITLE);
    if (!titleItem) return;

    QString qid = titleItem->data(Qt::UserRole).toString();
    if (qid.isEmpty()) return;

    auto ev = findById(qid.toStdString());
    if (!ev) return;

    // Only show something if notes exist
    if (!ev->getNotes() || ev->getNotes()->empty()) return;

    QMessageBox::information(
        this,
        QString::fromStdString("Notes"),
        QString::fromStdString(*ev->getNotes())
        );
}

void MainWindow::onSearch() {
    auto* w = new SearchWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);

    // Search All query
    connect(w, &SearchWindow::queryAll, this, [this]() {
        populateEventsTable(_manager.all(), "Showing all events");
    });

    // Search by Date query
    connect(w, &SearchWindow::queryDate, this, [this](const QDate& d) {
        _ui->calendar->setSelectedDate(d);
        refreshForDate(d);
    });

    // Search by Range query
    connect(w, &SearchWindow::queryRange, this, [this](const QDate& start, const QDate& end) {
        QDate endExclusive = end.addDays(1);

        Event::TimePoint from = qdtToTimePoint(QDateTime(start, QTime(0, 0)));
        Event::TimePoint to = qdtToTimePoint(QDateTime(endExclusive, QTime(0,0)));

        DateRange r(from, to);
        auto events = _manager.inRange(r);

        populateEventsTable(events, QString("Showing Events From %1 to %2").arg(start.toString("yyyy-MM-dd")).arg(end.toString("yyyy-MM-dd")));
    });

    // Search by title query
    connect(w, &SearchWindow::queryTitle, this, [this](const QString& title) {
        TextQuery q;
        q.text = title.toStdString();
        auto events = _manager.searchByTitle(q);
        populateEventsTable(events, QString("Showing %1 matches for title: \"%2\"").arg(events.size()).arg(title));
    });

    w->show();
    w->raise();
    w->activateWindow();
}

