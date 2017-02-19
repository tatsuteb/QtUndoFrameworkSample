#ifndef ADDVERTEXCOMMAND_H
#define ADDVERTEXCOMMAND_H

#include <QSharedPointer>
#include <QUndoCommand>
#include <QPoint>

class VertexData;
class CanvasWidget;

class AddVertexCommand : public QUndoCommand
{
	public:
		AddVertexCommand(const QPoint &pos, QSharedPointer<VertexData> vertexData, CanvasWidget *canvasWidget, QUndoCommand *parent = 0);

		// QUndoCommand interface
	public:
		void undo() Q_DECL_OVERRIDE;
		void redo() Q_DECL_OVERRIDE;

	private:
		QPoint m_point;
		QSharedPointer<VertexData> m_vertexData;
		CanvasWidget *m_canvasWidget;
		int m_index;
};

#endif // ADDVERTEXCOMMAND_H
