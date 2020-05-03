#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewidget.h"
#include "statwidget.h"
#include "selectactorwidget.h"
#include "QPushButton"
#include "boardwidget.h"
#include "gamelogic.h"
#include "celltype.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Stacking the different windows
    GameWidget *gameWidget = new GameWidget();
    StatWidget *statWidget = new StatWidget(this);
    SelectActorWidget *selectActorWidget = new SelectActorWidget(this);
    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    ui->stackedWidget->removeWidget(ui->stackedWidget->currentWidget());
    ui->stackedWidget->addWidget(gameWidget);
    ui->stackedWidget->addWidget(statWidget);
    ui->stackedWidget->addWidget(selectActorWidget);
    ui->stackedWidget->setCurrentWidget(gameWidget);
    //Connecting widgets together with button
    QObject::connect(statWidget,
                     SIGNAL(toGameWidget()),
                     this, SLOT(toGameWidget()));
    QObject::connect(selectActorWidget,
                     SIGNAL(toGameWidget()),
                     this, SLOT(toGameWidget()));
    QObject::connect(gameWidget,
                     SIGNAL(toStatsWidget()),
                     this, SLOT(toStatsWidget()));
    QObject::connect(gameWidget,
                     SIGNAL(toSelectActorWidget()),
                     this, SLOT(toSelectActorWidget()));
    BoardWidget *board = gameWidget->findChild<BoardWidget*>("board");
    GameLogic *gameLogic = new GameLogic(board);
    QObject::connect(gameLogic,
                     SIGNAL(setBoardCell(int, int, CellType)),
                     board, SLOT(setBoardCell(int, int, CellType)));
    gameLogic->drawSnake();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Slots
// Control to move from one widget to another
void MainWindow::toGameWidget(){
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::toSelectActorWidget(){
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::toStatsWidget(){
    ui->stackedWidget->setCurrentIndex(1);
}

