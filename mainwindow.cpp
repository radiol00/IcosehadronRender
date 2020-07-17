#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->transXSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(transXChanged(int)));
    connect(ui->transYSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(transYChanged(int)));
    connect(ui->transZSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(transZChanged(int)));

    connect(ui->scaleXSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(scaleXChanged(int)));
    connect(ui->scaleYSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(scaleYChanged(int)));
    connect(ui->scaleZSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(scaleZChanged(int)));

    connect(ui->rotateXSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(rotateXChanged(int)));
    connect(ui->rotateYSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(rotateYChanged(int)));
    connect(ui->rotateZSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(rotateZChanged(int)));

    connect(ui->tiltXSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(tiltXChanged(int)));
    connect(ui->tiltYSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(tiltYChanged(int)));
    connect(ui->tiltZSlider,SIGNAL(valueChanged(int)),ui->widget,SLOT(tiltZChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

