#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QColorDialog>

#include <opencv2/opencv.hpp>
using namespace cv;

Mat img;
int radioPincel = 10;
Scalar colorPincel = CV_RGB(0, 255, 0); // Inicializado a verde por defecto

void mousecb(int event, int x, int y, int flags, void * param)
{
    // Si pulsa el ratón añade un círculo
    if (flags == EVENT_FLAG_LBUTTON) {
        circle(img, Point(x, y), radioPincel, colorPincel, -1);
        imshow("Imagen", img);
    } else {
        // Se previsualiza lo que se va a dibujar con un círculo blanco

        Mat copia = img.clone(); // Se crea una copia
        circle(copia, Point(x, y), radioPincel, colorPincel, 2);
        imshow("Imagen", copia);
}
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString nombre = QFileDialog::getOpenFileName();
    if (!nombre.isNull()) {
        img = imread(nombre.toLatin1().data());
        if (!img.empty()) {
            namedWindow("Imagen", 0);
            imshow("Imagen", img);
            setMouseCallback("Imagen", mousecb);
        }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    radioPincel = value;
}

void MainWindow::on_pushButton_2_clicked()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        // Convertimos el QColor a Scalar y se lo asignamos
        colorPincel = CV_RGB(color.red(), color.green(), color.blue());
    }
}
