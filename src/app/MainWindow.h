//
// Created by Pavel Slabunov on 31.03.26.
//

#pragma once

#include <QListWidget>
#include <QMainWindow>
#include <QTextEdit>

#include "domain/RelationshipGraph.h"

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(RelationshipGraph &graph, QWidget *parent = nullptr);

private slots:
    void onPersonSelected(const QListWidgetItem *item) const;

private: // NOLINT(*-redundant-access-specifiers)
    void buildUi();

    void refreshPeopleList() const;

    RelationshipGraph &graph_;
    QListWidget *      people_list_ = nullptr;
    QTextEdit *        detail_view_ = nullptr;
};
