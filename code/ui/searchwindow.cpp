#include "searchwindow.h"
#include "ui_searchwindow.h"

#include <QDate>

// Constructor for Search Window
SearchWindow::SearchWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    // Configuring the QDateEdits
    const QDate now = QDate::currentDate();
    ui->startDate->setDate(now);
    ui->endDate->setDate(now);
    ui->startDate->setCalendarPopup(true);
    ui->endDate->setCalendarPopup(true);


    wireMenuPage();
    wireByDatePage();
    wireByTitlePage();

    updateRangeControls();

}

SearchWindow::~SearchWindow()
{
    delete ui;
}

// Function for going back to the menu page
void SearchWindow::goMenu() {

    ui->stackedWidget->setCurrentIndex(0);
}

// Function for going to the by date search page
void SearchWindow::goByDate() {

    ui->stackedWidget->setCurrentIndex(1);
}

// Function for going to the by title search page
void SearchWindow::goByTitle() {

    ui->stackedWidget->setCurrentIndex(2);
}


void SearchWindow::wireMenuPage() {

    // Wiring the Menu Buttons
    connect(ui->byAll, &QPushButton::clicked, this, [this] {
        emit queryAll();
        close();
    });

    connect(ui->byDate, &QPushButton::clicked, this, [this] {
        goByDate();
    });

    connect(ui->byTitle, &QPushButton::clicked, this, [this] {
        goByTitle();
    });

    // The cancel Button in the menu
    connect(ui->cancel, &QPushButton::clicked, this, &QDialog::close);
}

// Wiring the by date search page
void SearchWindow::wireByDatePage() {

    // Connecting all the buttons
    connect(ui->backButton, &QPushButton::clicked, this, [this] {goMenu();});
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::close);

    connect(ui->byRangeCheck, &QCheckBox::toggled, this, [this](bool) {updateRangeControls();});

    connect(ui->searchButton, &QPushButton::clicked, this, [this] {
        const QDate start = ui->startDate->date();

        // Emitting the date query functions
        if (!ui->byRangeCheck->isChecked()) emit queryDate(start);
        else {
            const QDate end = ui->endDate->date();
            emit queryRange(start, end);
        }

        close();
    });

}

// Wiring the by title search page
void SearchWindow::wireByTitlePage() {
    connect(ui->backButton_2, &QPushButton::clicked, this, [this] {goMenu();});
    connect(ui->cancelButton_2, &QPushButton::clicked, this, &QDialog::close);

    connect(ui->searchButton_2, &QPushButton::clicked, this, [this] {
        const QString str = ui->titleLineEdit->text();
        emit queryTitle(str);
        close();
    });
}

// Only enable end date if by range has been checked
void SearchWindow::updateRangeControls() {
    const bool checked = ui->byRangeCheck->isChecked();

    ui->endDate->setEnabled(checked);
    ui->endDate->setVisible(true);
}









