#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class SearchWindow;
}

// SearchWindow Class
// This class is responsible for a dialog that pops up when you press the search button in the tool bar.
// It manages the UI for the dialog and the QObjects that are associated with it.
class SearchWindow : public QDialog
{
    Q_OBJECT

public:

    // Constructor
    explicit SearchWindow(QWidget *parent = nullptr);
    ~SearchWindow();


signals:

    // Query functions that connect to the ones in EventManager
    void queryAll();
    void queryDate(const QDate& date);
    void queryRange(const QDate& start, const QDate& end);
    void queryTitle(const QString& title);

private:
    Ui::SearchWindow *ui;

    // Functions to switch to different pages
    void goMenu();
    void goByDate();
    void goByTitle();

    // Connecting UI buttons and inputs
    void wireMenuPage();
    void wireByDatePage();
    void wireByTitlePage();

    // Enable/Disable range controls based on input
    void updateRangeControls();
};

#endif // SEARCHWINDOW_H
