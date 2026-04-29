/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionToday;
    QAction *actionQuit;
    QAction *actionSearch;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_central;
    QSplitter *splitter;
    QCalendarWidget *calendar;
    QWidget *rightPane;
    QVBoxLayout *verticalLayout_right;
    QLabel *label;
    QTableView *eventsView;
    QMenuBar *menubar;
    QToolBar *mainToolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(572, 308);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName("actionEdit");
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionToday = new QAction(MainWindow);
        actionToday->setObjectName("actionToday");
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        actionQuit->setCheckable(false);
        actionQuit->setMenuRole(QAction::MenuRole::NoRole);
        actionSearch = new QAction(MainWindow);
        actionSearch->setObjectName("actionSearch");
        actionSearch->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_central = new QVBoxLayout(centralwidget);
        verticalLayout_central->setObjectName("verticalLayout_central");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        calendar = new QCalendarWidget(splitter);
        calendar->setObjectName("calendar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(calendar->sizePolicy().hasHeightForWidth());
        calendar->setSizePolicy(sizePolicy);
        calendar->setGridVisible(false);
        calendar->setSelectionMode(QCalendarWidget::SelectionMode::SingleSelection);
        calendar->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat::ShortDayNames);
        calendar->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat::NoVerticalHeader);
        splitter->addWidget(calendar);
        rightPane = new QWidget(splitter);
        rightPane->setObjectName("rightPane");
        verticalLayout_right = new QVBoxLayout(rightPane);
        verticalLayout_right->setObjectName("verticalLayout_right");
        verticalLayout_right->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(rightPane);
        label->setObjectName("label");

        verticalLayout_right->addWidget(label);

        eventsView = new QTableView(rightPane);
        eventsView->setObjectName("eventsView");

        verticalLayout_right->addWidget(eventsView);

        splitter->addWidget(rightPane);

        verticalLayout_central->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 572, 25));
        MainWindow->setMenuBar(menubar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        mainToolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionEdit);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addAction(actionToday);
        mainToolBar->addAction(actionSearch);
        mainToolBar->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Timely", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        actionEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        actionToday->setText(QCoreApplication::translate("MainWindow", "Today", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Events", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
