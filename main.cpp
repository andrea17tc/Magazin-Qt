#include "Main_Window.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepoProdus repo;
    RepoProdus cos;
    ValidatorProdus val;
    ServiceProdus srv{ repo,val };
    ServiceProdus srv_cos{ cos, val };
    Produs p{ "sare", "al", 5, "ion" };
    repo.adauga(p);
    Produs p1{ "piper", "al", 6, "ion" };
    repo.adauga(p1);
    Produs p2{"usturoi", "al", 3, "ion" };
    repo.adauga(p2);
    Main_Window w(srv, srv_cos);
    //QLabel* label = new QLabel("jecmanos");
     //label->show();

    w.setWindowTitle("Meniu");
    w.show();
    return a.exec();
}
