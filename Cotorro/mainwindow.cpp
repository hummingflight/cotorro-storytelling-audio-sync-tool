#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cotorro.h"

using ct::Cotorro;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setCentralWidget(ui->mainSplitter);

  // Create Cotorro's module.
  Cotorro::Start(this);

  // Initialize
  init();
}

MainWindow::~MainWindow()
{
  delete ui;
}

QPlainTextEdit*
MainWindow::getLoggerTextWidget()
{
  return ui->pText_logger;
}

void
MainWindow::init()
{
  // Initialize Cotorro's module.
  Cotorro::Instance()->init(this);

  // Init Logger Widget
  QPalette p = ui->pText_logger->palette();
  p.setColor(QPalette::Base, Qt::black);
  p.setColor(QPalette::Text, Qt::white);
  ui->pText_logger->setPalette(p);

  Cotorro::Log(eLOGTYPE::kMessage, "Application initialized.");
  return;
}

