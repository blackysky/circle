#include <QApplication>

#include "domain/RelationshipGraph.h"
#include "app/MainWindow.h"
#include "domain/Person.h"

int main(int argc, char *argv[]) {
    QApplication const app(argc, argv);

    RelationshipGraph graph;

    Person alice;
    alice.first_name = "Alice";
    alice.surname = "Schmidt";
    alice.gender = Gender::Female;
    alice.birth_year = BirthYear{2000}; // NOLINT(*-magic-numbers)

    Person bob;
    bob.first_name = "Bob";
    bob.gender = Gender::Male;
    bob.birth_year = BirthYear{1990, true}; // NOLINT(*-magic-numbers)

    graph.addPerson(std::move(alice));
    graph.addPerson(std::move(bob));

    MainWindow window(graph);
    window.show();

    return QApplication::exec();
}
