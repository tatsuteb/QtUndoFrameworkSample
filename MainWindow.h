#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <CanvasWidget.h>
#include <QUndoStack>
#include <QUndoView>

class VertexData;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		// QWidget interface
	protected:
		void closeEvent(QCloseEvent *) Q_DECL_OVERRIDE;

	private:
		Ui::MainWindow *ui;

		QUndoStack *m_undoStack;
		QUndoView *m_undoView;

		QSharedPointer<VertexData> m_vertexData;
		CanvasWidget *m_canvasWidget;

};

#endif // MAINWINDOW_H
