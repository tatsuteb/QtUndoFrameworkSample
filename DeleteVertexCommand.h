#ifndef DELETEVERTEXCOMMAND_H
#define DELETEVERTEXCOMMAND_H

#include <QSharedPointer>
#include <QUndoCommand>
#include <QPoint>
#include <QRect>

class VertexData;
class CanvasWidget;

class DeleteVertexCommand : public QUndoCommand
{
	public:
		DeleteVertexCommand(int index, QSharedPointer<VertexData> vertexData, CanvasWidget *canvasWidget, QUndoCommand *parent = 0);

		// QUndoCommand interface
	public:
		void undo() Q_DECL_OVERRIDE;
		void redo() Q_DECL_OVERRIDE;

	private:
		QPoint m_point;
		QSharedPointer<VertexData> m_vertexData;
		CanvasWidget *m_canvasWidget;
		int m_index;
		QRect m_effectiveArea;
};

#endif // DELETEVERTEXCOMMAND_H
