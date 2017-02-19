#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QUndoStack>

class VertexData;

namespace Ui {
	class CanvasWidget;
}

class CanvasWidget : public QWidget
{
		Q_OBJECT

	public:
		explicit CanvasWidget(QUndoStack *undoStack, QSharedPointer<VertexData> vertexData, QWidget *parent = 0);
		~CanvasWidget();

		// QWidget interface
	protected:
		void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
		void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
		void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

	private:
		void addVertex(const QPoint &pos);
		void deleteVertex(const QPoint &pos);
		int getVertexIndexByDistance(const QPoint &pos, float distance);
		bool checkVertexIndex(int index);

	private:
		Ui::CanvasWidget *ui;

		QUndoStack *m_undoStack;
		QSharedPointer<VertexData> m_vertexData;
		int m_activeVertexIndex;
		bool m_draggingVertex;

};

#endif // CANVASWIDGET_H
