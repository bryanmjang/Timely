//
// Created by bryan on 2025-11-11.
//
#include "eventdialog.h"
#include "ui_eventdialog.h"

#include <QMessageBox>
#include <QDateTime>

// Constructor
EventDialog::EventDialog(QWidget* parent) : QDialog(parent), _ui(new Ui::EventDialog) {
    _ui->setupUi(this);

    // Default times: start now, end an hour later
    _ui->startDateTime->setDateTime(QDateTime::currentDateTime());
    _ui->endDateTime->setDateTime(QDateTime::currentDateTime().addSecs(60 * 60)); // +1h
    populateCategoryCombo();
    populateReminderCombo();

    connect(_ui->hasEndCheck, &QCheckBox::toggled, this, &EventDialog::onHasEndToggled);
    connect(_ui->buttonBox, &QDialogButtonBox::accepted, this, &EventDialog::onAccept);
    connect(_ui->buttonBox, &QDialogButtonBox::rejected, this, &EventDialog::reject);
}

EventDialog::~EventDialog() { delete _ui; }

// Function to populate the dropdown with labels representing category enum values
void EventDialog::populateCategoryCombo() {

    _ui->categoryCombo->clear();
    _ui->categoryCombo->addItem("— None —");  // index 0 = no category
    _ui->categoryCombo->addItem("Work");      // 1
    _ui->categoryCombo->addItem("School");    // 2
    _ui->categoryCombo->addItem("Personal");  // 3
}

void EventDialog::populateReminderCombo() {

    _ui->reminderCombo->clear();
    _ui->reminderCombo->addItem("None", 0);
    _ui->reminderCombo->addItem("1 minute before", 1);
    _ui->reminderCombo->addItem("5 minutes before", 5);
    _ui->reminderCombo->addItem("15 minutes before", 15);
    _ui->reminderCombo->addItem("30 minutes before", 30);
    _ui->reminderCombo->addItem("1 hour before", 60);
    _ui->reminderCombo->addItem("2 hours before", 120);
    _ui->reminderCombo->addItem("1 day before", 1440);
    _ui->reminderCombo->addItem("2 days before", 2880);

}

// Converts a category to a combo index
int EventDialog::categoryToIndex(std::optional<Event::Category> cat) {
    if (!cat) return 0;
    switch (*cat) {
    case Event::Category::Work:     return 1;
    case Event::Category::School:   return 2;
    case Event::Category::Personal: return 3;
    default: return 0;
    }
}

// converts a combo index to a category
std::optional<Event::Category> EventDialog::indexToCategory(int i) {
    switch (i) {
    case 1: return Event::Category::Work;
    case 2: return Event::Category::School;
    case 3: return Event::Category::Personal;
    default: return std::nullopt;
    }
}

// Function to fill the default values for time (used when creating a new event)
void EventDialog::prefillDate(const QDate& d) {
    // Setting default time to 00:00
    QDateTime s(d, QTime(0, 0), Qt::LocalTime);
    _ui->startDateTime->setDateTime(s);
    _ui->endDateTime->setDateTime(s.addSecs(60 * 60)); // +1h
}

// Used when editing an existing event
void EventDialog::setEvent(const Event& e) {

    // title
    _ui->titleEdit->setText(QString::fromStdString(e.getTitle()));

    // start
    auto secsStart = std::chrono::time_point_cast<std::chrono::seconds>(e.getStart())
                         .time_since_epoch().count();
    _ui->startDateTime->setDateTime(QDateTime::fromSecsSinceEpoch(secsStart, Qt::LocalTime));

    // end
    if (e.getEnd()) {
        auto secsEnd = std::chrono::time_point_cast<std::chrono::seconds>(*e.getEnd())
        .time_since_epoch().count();
        _ui->endDateTime->setDateTime(QDateTime::fromSecsSinceEpoch(secsEnd, Qt::LocalTime));
        _ui->hasEndCheck->setChecked(true);
        _ui->endDateTime->setEnabled(true);
    } else {
        _ui->hasEndCheck->setChecked(false);
        _ui->endDateTime->setEnabled(false);
    }

    // category
    _ui->categoryCombo->setCurrentIndex(categoryToIndex(e.getCategory()));

    // location
    if (e.getLocation()) _ui->locationEdit->setText(QString::fromStdString(*e.getLocation()));
    else _ui->locationEdit->clear();

    // notes
    if (e.getNotes()) _ui->notesEdit->setPlainText(QString::fromStdString(*e.getNotes()));
    else _ui->notesEdit->clear();

    // reminder
    int mins = 0;
    const auto& r = e.getRemindersMinutesBefore();
    if (!r.empty()) mins = r.front();
    int idx = _ui->reminderCombo->findData(mins);
    if (idx < 0) idx = 0;
    _ui->reminderCombo->setCurrentIndex(idx);

}

std::string EventDialog::title() const {
    return _ui->titleEdit->text().toStdString();
}

QDateTime EventDialog::startDateTime() const {
    return _ui->startDateTime->dateTime();
}

bool EventDialog::hasEnd() const {
    return _ui->hasEndCheck->isChecked();
}

QDateTime EventDialog::endDateTime() const {
    return _ui->endDateTime->dateTime();
}

std::optional<Event::Category> EventDialog::category() const {
    return indexToCategory(_ui->categoryCombo->currentIndex());
}

std::optional<std::string> EventDialog::location() const {
    const QString t = _ui->locationEdit->text();
    if (t.isEmpty()) return std::nullopt;
    return t.toStdString();
}

std::optional<std::string> EventDialog::notes() const {
    const QString t = _ui->notesEdit->toPlainText();
    if (t.isEmpty()) return std::nullopt;
    return t.toStdString();
}

std::vector<int> EventDialog::remindersMinutesBefore() const {
    int mins = _ui->reminderCombo->currentData().toInt();
    if (mins <= 0) return {};
    return {mins};
    }

void EventDialog::onHasEndToggled(bool checked) {
    _ui->endDateTime->setEnabled(checked);
}

void EventDialog::onAccept() {
    if (_ui->titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Validation", "Title is required.");
        return;
    }
    if (hasEnd() && endDateTime() < startDateTime()) {
        QMessageBox::warning(this, "Validation", "End time must be after start time.");
        return;
    }
    accept();
}
