//
// Created by Pavel Slabunov on 31.03.26.
//

// ReSharper disable CppDFAMemoryLeak
// ^^^ due to GSL ownership semantics not understanding Qt's ownership model
#include "MainWindow.h"

#include <QSplitter>
#include <QToolBar>
#include <QVBoxLayout>

namespace {
    QString formatPersonDetail(const Person &person) {
        QString text;
        text += "First name: " + QString::fromStdString(person.first_name) + "\n";
        text += "Surname: " + QString::fromStdString(person.surname.value_or("-")) + "\n";

        text += "Gender: ";
        switch (person.gender) {
            case Gender::Male: text += "Male";
                break;
            case Gender::Female: text += "Female";
                break;
            case Gender::Unspecified: text += "Unspecified";
                break;
        }
        text += "\n";

        if (person.birth_year) {
            text += "Birth year: " + QString::number(person.birth_year->year());
            if (person.birth_year->is_approximate()) {
                text += " (approx.)";
            }
            text += "\n";
        }

        if (person.notes) {
            text += "\nNotes:\n" + QString::fromStdString(*person.notes) + "\n";
        }

        return text;
    }
} // namespace

MainWindow::MainWindow(RelationshipGraph &graph, QWidget *parent)
    : QMainWindow(parent), graph_(graph) {
    buildUi();
    refreshPeopleList();
}

void MainWindow::buildUi() {
    setWindowTitle("Circle");
    resize(1024, 768); // NOLINT(*-magic-numbers)

    auto *toolbar = addToolBar("Main");
    toolbar->addAction("+ Add");
    toolbar->addAction("- Remove");

    auto *splitter = new QSplitter(Qt::Horizontal, this);

    people_list_ = new QListWidget(splitter);
    detail_view_ = new QTextEdit(splitter);
    detail_view_->setReadOnly(true);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);

    setCentralWidget(splitter);

    connect(people_list_, &QListWidget::itemClicked,
            this, &MainWindow::onPersonSelected);
}

void MainWindow::refreshPeopleList() const {
    people_list_->clear();

    for (const auto &person: graph_.allPeople()) {
        const QString display_name = QString::fromStdString(
            person.first_name + (person.surname ? " " + *person.surname : "")
        );

        auto *item = new QListWidgetItem(display_name, people_list_);
        item->setData(Qt::UserRole, person.id);
    }
}

void MainWindow::onPersonSelected(const QListWidgetItem *item) const {
    const auto person_id = item->data(Qt::UserRole).toULongLong();

    const auto found = graph_.findPerson(person_id);
    if (!found) {
        return;
    }

    detail_view_->setPlainText(formatPersonDetail(**found));
}
