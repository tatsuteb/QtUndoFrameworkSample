#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "VertexData.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_undoStack(new QUndoStack),
	m_undoView(new QUndoView(m_undoStack)),
	m_vertexData(QSharedPointer<VertexData>::create()),
	m_canvasWidget(new CanvasWidget(m_undoStack, m_vertexData))
{
	ui->setupUi(this);
	ui->canvasFrame->layout()->addWidget(m_canvasWidget);

	connect(ui->undoButton, &QPushButton::clicked, m_undoStack, &QUndoStack::undo);
	connect(ui->redoButton, &QPushButton::clicked, m_undoStack, &QUndoStack::redo);

	connect(ui->actionUndo, &QAction::triggered, m_undoStack, &QUndoStack::undo);
	connect(ui->actionRedo, &QAction::triggered, m_undoStack, &QUndoStack::redo);

	m_undoView->setWindowFlags(Qt::Dialog);
	m_undoView->show();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
	m_undoView->close();
}


