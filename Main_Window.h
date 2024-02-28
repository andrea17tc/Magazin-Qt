#pragma once

#include "Service.h"
#include <QtWidgets/QMainWindow>
#include "ui_Main_Window.h"
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qmessagebox>
#include <QListWidget>
#include <QRandomGenerator>
#include <QPainter>
#include <vector>

using namespace std;

class Adaugare : public QWidget
{
    Q_OBJECT
public:
    Adaugare(ServiceProdus& service);

private:
    ServiceProdus& srv;
    QFormLayout* layout;
    QLabel* label_nume;
    QLabel* label_tip;
    QLabel* label_pret;
    QLabel* label_prod;
    QLineEdit* text_nume;
    QLineEdit* text_tip;
    QLineEdit* text_pret;
    QLineEdit* text_prod;
    QPushButton* submit_button;

signals:

private slots:
    void submit_button_clicked();
};

class Stergere : public QWidget {
    Q_OBJECT

public:
    Stergere(ServiceProdus& service);
private:
    ServiceProdus& srv;
    QFormLayout* layout;
    QLabel* label_nume;
    QLabel* label_tip;
    QLabel* label_pret;
    QLabel* label_prod;
    QLineEdit* text_nume;
    QLineEdit* text_tip;
    QLineEdit* text_pret;
    QLineEdit* text_prod;
    QPushButton* submit_button;
signals:

private slots:
    void submit_button_clicked();
};

class Cos_Window : public QWidget, public Observer {
    
    Q_OBJECT

public:
    Cos_Window(ServiceProdus& srv, ServiceProdus& cos);
    void update() override
    {
        reload_cos();
    }
private:
    ServiceProdus& srv;
    ServiceProdus& cos;
    QHBoxLayout* layout;
    QVBoxLayout* layout_secundar;
    QListWidget* lista_cos;
    QPushButton* generare_button;
    QPushButton* golire_button;
    QPushButton* adauga_button;
    QPushButton* sterge_button;
    QPushButton* cos_read_only;
    Adaugare* adauga;
    Stergere* sterge;

public slots:
    void reload_cos();
    void generare_cos();
    void golire_cos();
    void desen_cos();
};


class Cos_Window2 : public QWidget{

    Q_OBJECT

public:
    Cos_Window2(int size);
    //int len;
    void paintEvent(QPaintEvent* ev) override {

        QPainter p{ this };
        /*if (len == 0) {
            QColor color(255, 187, 153);
            p.setPen(color);
            p.setBrush(color);

            p.drawEllipse(100, 200, 200, 200);
            p.drawEllipse(300, 200, 200, 200);
            p.drawEllipse(220, 0, 150, 350);

        }*/


        for (int i = 1; i <= len; i++) {

            int red = QRandomGenerator::global()->bounded(256);
            int green = QRandomGenerator::global()->bounded(256);
            int blue = QRandomGenerator::global()->bounded(256);

            // Set the random color for drawing the circle
            QColor color(red, green, blue);
            p.setPen(color);
            p.setBrush(color);

            int w = QRandomGenerator::global()->bounded(100, width());
            int h = QRandomGenerator::global()->bounded(100, height());
            if (i % 3 == 1)
            {
                int x1 = w / 2;
                int y1 = h / 4;
                int x2 = w / 4;
                int y2 = h * 3 / 4;
                int x3 = w * 3 / 4;
                int y3 = h * 3 / 4;

                // Create a polygon and add the triangle vertices
                QPolygon triangle;
                triangle << QPoint(x1, y1);
                triangle << QPoint(x2, y2);
                triangle << QPoint(x3, y3);

                // Draw the triangle
                p.drawPolygon(triangle);
            }
            else if (i % 3 == 0) {

                // Calculate the size and position of the square
                int size = qMin(w, h) * 0.8; // Adjust the scale of the square
                int x = (w - size) / 2;
                int y = (h - size) / 2;

                // Draw the square
                p.drawRect(x, y, size, size);
            }
            else {

                // Calculate the center and radius of the circle
                int centerX = w;
                int centerY = h;
                int radius = qMin(w, h) / 2;

                // Draw the circle using the calculated values
                p.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            }

        }
    }

private:
    int len;

};


class Main_Window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Main_Window(ServiceProdus& srv, ServiceProdus& cos);
    void update() override;


private:
    QVBoxLayout* layout;
    ServiceProdus& service;
    ServiceProdus& cos;
    QPushButton* add_button;
    QPushButton* del_button;
    //QPushButton* get_button;
    //QPushButton* afisare;
    QPushButton* functii_cos;
    Adaugare* adauga;
    Stergere* sterge;
    QListWidget* lista;

private slots:
    //void afisare_button_clicked();
    void reload();
    void spre_cos();
};
