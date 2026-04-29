/********************************************************************************
** Form generated from reading UI file 'searchwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWINDOW_H
#define UI_SEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWindow
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *cancel;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *byAll;
    QPushButton *byDate;
    QPushButton *byTitle;
    QWidget *byDatePage;
    QPushButton *searchButton;
    QPushButton *backButton;
    QPushButton *cancelButton;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QLabel *searchDateLabel;
    QCheckBox *byRangeCheck;
    QDateEdit *startDate;
    QDateEdit *endDate;
    QWidget *byTitlePage;
    QPushButton *cancelButton_2;
    QPushButton *backButton_2;
    QPushButton *searchButton_2;
    QWidget *layoutWidget2;
    QFormLayout *formLayout_2;
    QLabel *titleLabel;
    QLineEdit *titleLineEdit;

    void setupUi(QDialog *SearchWindow)
    {
        if (SearchWindow->objectName().isEmpty())
            SearchWindow->setObjectName("SearchWindow");
        SearchWindow->resize(348, 227);
        stackedWidget = new QStackedWidget(SearchWindow);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 331, 211));
        stackedWidget->setAutoFillBackground(false);
        page = new QWidget();
        page->setObjectName("page");
        cancel = new QPushButton(page);
        cancel->setObjectName("cancel");
        cancel->setGeometry(QRect(0, 160, 321, 41));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cancel->sizePolicy().hasHeightForWidth());
        cancel->setSizePolicy(sizePolicy);
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 20, 321, 111));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        byAll = new QPushButton(layoutWidget);
        byAll->setObjectName("byAll");
        sizePolicy.setHeightForWidth(byAll->sizePolicy().hasHeightForWidth());
        byAll->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(byAll);

        byDate = new QPushButton(layoutWidget);
        byDate->setObjectName("byDate");
        sizePolicy.setHeightForWidth(byDate->sizePolicy().hasHeightForWidth());
        byDate->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(byDate);

        byTitle = new QPushButton(layoutWidget);
        byTitle->setObjectName("byTitle");
        sizePolicy.setHeightForWidth(byTitle->sizePolicy().hasHeightForWidth());
        byTitle->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(byTitle);

        stackedWidget->addWidget(page);
        byDatePage = new QWidget();
        byDatePage->setObjectName("byDatePage");
        searchButton = new QPushButton(byDatePage);
        searchButton->setObjectName("searchButton");
        searchButton->setGeometry(QRect(210, 170, 121, 41));
        backButton = new QPushButton(byDatePage);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(0, 180, 90, 29));
        cancelButton = new QPushButton(byDatePage);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setGeometry(QRect(0, 150, 90, 29));
        layoutWidget1 = new QWidget(byDatePage);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 30, 331, 67));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        searchDateLabel = new QLabel(layoutWidget1);
        searchDateLabel->setObjectName("searchDateLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, searchDateLabel);

        byRangeCheck = new QCheckBox(layoutWidget1);
        byRangeCheck->setObjectName("byRangeCheck");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, byRangeCheck);

        startDate = new QDateEdit(layoutWidget1);
        startDate->setObjectName("startDate");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, startDate);

        endDate = new QDateEdit(layoutWidget1);
        endDate->setObjectName("endDate");
        endDate->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(10, 0, 0)));

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, endDate);

        stackedWidget->addWidget(byDatePage);
        byTitlePage = new QWidget();
        byTitlePage->setObjectName("byTitlePage");
        cancelButton_2 = new QPushButton(byTitlePage);
        cancelButton_2->setObjectName("cancelButton_2");
        cancelButton_2->setGeometry(QRect(0, 150, 90, 29));
        backButton_2 = new QPushButton(byTitlePage);
        backButton_2->setObjectName("backButton_2");
        backButton_2->setGeometry(QRect(0, 180, 90, 29));
        searchButton_2 = new QPushButton(byTitlePage);
        searchButton_2->setObjectName("searchButton_2");
        searchButton_2->setGeometry(QRect(210, 170, 121, 41));
        layoutWidget2 = new QWidget(byTitlePage);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(10, 30, 311, 30));
        formLayout_2 = new QFormLayout(layoutWidget2);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(layoutWidget2);
        titleLabel->setObjectName("titleLabel");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, titleLabel);

        titleLineEdit = new QLineEdit(layoutWidget2);
        titleLineEdit->setObjectName("titleLineEdit");

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, titleLineEdit);

        stackedWidget->addWidget(byTitlePage);

        retranslateUi(SearchWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SearchWindow);
    } // setupUi

    void retranslateUi(QDialog *SearchWindow)
    {
        SearchWindow->setWindowTitle(QCoreApplication::translate("SearchWindow", "Dialog", nullptr));
        cancel->setText(QCoreApplication::translate("SearchWindow", "Cancel", nullptr));
        byAll->setText(QCoreApplication::translate("SearchWindow", "Search All", nullptr));
        byDate->setText(QCoreApplication::translate("SearchWindow", "Search By Date", nullptr));
        byTitle->setText(QCoreApplication::translate("SearchWindow", "Search By Title", nullptr));
        searchButton->setText(QCoreApplication::translate("SearchWindow", "Search", nullptr));
        backButton->setText(QCoreApplication::translate("SearchWindow", "Back", nullptr));
        cancelButton->setText(QCoreApplication::translate("SearchWindow", "Cancel", nullptr));
        searchDateLabel->setText(QCoreApplication::translate("SearchWindow", "Search Date", nullptr));
        byRangeCheck->setText(QCoreApplication::translate("SearchWindow", "Search By Range", nullptr));
        cancelButton_2->setText(QCoreApplication::translate("SearchWindow", "Cancel", nullptr));
        backButton_2->setText(QCoreApplication::translate("SearchWindow", "Back", nullptr));
        searchButton_2->setText(QCoreApplication::translate("SearchWindow", "Search", nullptr));
        titleLabel->setText(QCoreApplication::translate("SearchWindow", "Title of Event", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchWindow: public Ui_SearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWINDOW_H
