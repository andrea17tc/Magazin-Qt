#include "Main_Window.h"
#include <random>

Main_Window::Main_Window(ServiceProdus& srv, ServiceProdus& cos) : service{srv}, cos{cos}
{
    layout = new QVBoxLayout(this);
    service.add_observer(this);
    cos.add_observer(this);
    add_button = new QPushButton("Adauga");
    adauga = new Adaugare(service);
    layout->addWidget(add_button);
    //this->setLayout(layout);
    adauga->setWindowTitle("Adaugare");
    this->connect(add_button, SIGNAL(clicked()), adauga, SLOT(show()));
    add_button->show();

    /////////////////////////

    del_button = new QPushButton("Sterge");
    sterge = new Stergere(service);
    layout->addWidget(del_button);
    //this->setLayout(layout);
    sterge->setWindowTitle("Stergere");
    this->connect(del_button, SIGNAL(clicked()), sterge, SLOT(show()));
    del_button->show();
    /*
    afisare = new QPushButton("Afisare");
    layout->addWidget(afisare);
    this->connect(afisare, SIGNAL(clicked()), this, SLOT(afisare_button_clicked()));*/

    ///////////////////////////////////
        
    functii_cos = new QPushButton("Functii cos");
    layout->addWidget(functii_cos);
    this->connect(functii_cos, SIGNAL(clicked()), this, SLOT(spre_cos()));

    ///////////////////////////////////

    lista = new QListWidget();
    vector<Produs> toate = service.get_all();
    QString item, item1;
    item1.append("Nume      Tip      Pret       Producator");
    lista->addItem(item1);
    lista->setWindowTitle("Produse\n");
    for (auto prod : toate) {

        item.clear();
        item.append(QString::fromStdString(prod.get_nume()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_tip()));
        item.append("            ");
        item.append(QString::number(prod.get_pret()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_producator()));
        //item.append("\n");
        lista->addItem(item);
    }
    layout->addWidget(lista);

}

void Main_Window::update() {
    reload();
}

void Main_Window::reload() {

    lista->clear();
    vector<Produs> toate = service.get_all();
    QString item, item1;
    item1.append("Nume      Tip      Pret       Producator");
    lista->addItem(item1);
    lista->setWindowTitle("Produse\n");
    for (auto prod : toate) {

        item.clear();
        item.append(QString::fromStdString(prod.get_nume()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_tip()));
        item.append("            ");
        item.append(QString::number(prod.get_pret()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_producator()));
        //item.append("\n");
        lista->addItem(item);
    }
}

/*
void Main_Window::afisare_button_clicked() {

    lista = new QListWidget();
    vector<Produs> toate = service.get_all();
    QString item, item1;
    item1.append("Nume      Tip      Pret       Producator");
    lista->addItem(item1);
    lista->setWindowTitle("Produse\n");
    for (auto prod : toate) {
        
        item.append(QString::fromStdString(prod.get_nume()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_tip()));
        item.append("            ");
        item.append(QString::number(prod.get_pret()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_producator()));
        //item.append("\n");
        lista->addItem(item);
    }
    lista->show();
}
*/

void Main_Window::spre_cos() {
    Cos_Window* fereastra_cos;
    fereastra_cos = new Cos_Window( service, cos );
    cos.add_observer(fereastra_cos);
    fereastra_cos->show();

}

Cos_Window::Cos_Window(ServiceProdus& srv, ServiceProdus& cos) : srv{ srv }, cos{ cos } {
    layout = new QHBoxLayout(this);
    srv.add_observer(this);
    //incarca tabelu
    lista_cos = new QListWidget(this);
    layout->addWidget(lista_cos);
    //reload_cos();

    layout_secundar = new QVBoxLayout(this);
    //buton generare
    generare_button = new QPushButton("Generare cos");
    layout_secundar->addWidget(generare_button);
    this->connect(generare_button, SIGNAL(clicked()), this, SLOT(generare_cos()));

    //buton golire
    golire_button = new QPushButton("Golire cos");
    layout_secundar->addWidget(golire_button);
    this->connect(golire_button, SIGNAL(clicked()), this, SLOT(golire_cos()));

    //buton adaugare
    adauga_button = new QPushButton("Adauga la cos");
    layout_secundar->addWidget(adauga_button);
   // this->connect(adauga_button, SIGNAL(clicked()), this, SLOT(adauga_la_cos()));
    adauga = new Adaugare(cos);
    //this->setLayout(layout);
    adauga->setWindowTitle("Adaugare");
    this->connect(adauga_button, SIGNAL(clicked()), adauga, SLOT(show()));

    //buton stergere
    sterge_button = new QPushButton("Sterge din cos");
    layout_secundar->addWidget(sterge_button);
    //this->connect(sterge_button, SIGNAL(clicked()), this, SLOT(sterge_din_cos()));
    sterge = new Stergere(cos);
    //this->setLayout(layout);
    sterge->setWindowTitle("Stergere");
    this->connect(sterge_button, SIGNAL(clicked()), sterge, SLOT(show()));

    cos_read_only = new QPushButton("Continut cos");
    layout_secundar->addWidget(cos_read_only);
    this->connect(cos_read_only, SIGNAL(clicked()), this, SLOT(desen_cos()));

    layout->addLayout(layout_secundar);
}

void Cos_Window::generare_cos() {
    //srv.generare(5, cos);
    vector<Produs>& rez = srv.get_all();

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, rez.size() - 1); // define the range

    for (int n = 0; n < 5; ++n)
    {
        int poz = distr(gen);
        Produs p = rez[poz];
        cos.adauga_cos(p.get_nume(), p.get_tip(), p.get_pret(), p.get_producator());
    }
    
}

void Cos_Window::golire_cos() {
    cos.golire();
}

void Cos_Window::reload_cos() {
    lista_cos->clear();
    vector<Produs> l{ cos.get_all() };
    QString item;
    for (auto prod:l){
        item.clear();
        item.append(QString::fromStdString(prod.get_nume()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_tip()));
        item.append("            ");
        item.append(QString::number(prod.get_pret()));
        item.append("            ");
        item.append(QString::fromStdString(prod.get_producator()));
        //item.append("\n");
        lista_cos->addItem(item);
    }

}

void Cos_Window::desen_cos() {

    Cos_Window2* fereastra_cos_desen;

    vector<Produs> rez = cos.get_all();

    fereastra_cos_desen = new Cos_Window2(rez.size());
    fereastra_cos_desen->show();
}

Cos_Window2::Cos_Window2(int size) : len{ size }
{
    this->setWindowTitle("Desen Cos");
    this->resize(600, 400);

}

Adaugare::Adaugare(ServiceProdus& service) : srv{ service }
{
    layout = new QFormLayout(this);
    //service.add_observer(this);
    label_nume = new QLabel("Nume");
    label_tip = new QLabel("Tip");
    label_pret = new QLabel("Pret");
    label_prod = new QLabel("Producator");
    text_nume = new QLineEdit;
    text_tip = new QLineEdit;
    text_pret = new QLineEdit;
    text_prod = new QLineEdit;
    submit_button = new QPushButton("Submit");
    layout->addRow(label_nume, text_nume);
    layout->addRow(label_tip, text_tip);
    layout->addRow(label_pret, text_pret);
    layout->addRow(label_prod, text_prod);
    layout->addRow(submit_button);
    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(close()));
}

Stergere::Stergere(ServiceProdus& service) : srv{ service } {
    layout = new QFormLayout(this);
    label_nume = new QLabel("Nume");
    label_tip = new QLabel("Tip");
    label_pret = new QLabel("Pret");
    label_prod = new QLabel("Producator");
    text_nume = new QLineEdit;
    text_tip = new QLineEdit;
    text_pret = new QLineEdit;
    text_prod = new QLineEdit;
    submit_button = new QPushButton("Submit");
    layout->addRow(label_nume, text_nume);
    layout->addRow(label_tip, text_tip);
    layout->addRow(label_pret, text_pret);
    layout->addRow(label_prod, text_prod);
    layout->addRow(submit_button);
    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(close()));
}

void Adaugare::submit_button_clicked()
{
    std::string nume = text_nume->text().toStdString();
    //QString proba = QString::fromStdString(nume);
    std::string tip = text_tip->text().toStdString();
    bool convert = true;
    int pret = text_pret->text().toInt(&convert);
    if (convert == false)
    {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Nu");
        mesaj->show();
        return;
    }
    std::string prod = text_prod->text().toStdString();
    srv.adauga(nume, tip, pret, prod);
}

void Stergere::submit_button_clicked() {
    std::string nume = text_nume->text().toStdString();
    //QString proba = QString::fromStdString(nume);
    std::string tip = text_tip->text().toStdString();
    bool convert = true;
    int pret = text_pret->text().toInt(&convert);
    if (convert == false)
    {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Nu");
        mesaj->show();
        return;
    }
    std::string prod = text_prod->text().toStdString();
    Produs p{ nume,tip,pret,prod };
    try {
        srv.sterge(p);
    }
    catch (RepoProdusExceptie&) {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Nu exista produsul");
        mesaj->show();
        return;
    }
    
}