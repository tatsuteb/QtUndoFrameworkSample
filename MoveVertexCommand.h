#ifndef MOVEVERTEXCOMMAND_H
#define MOVEVERTEXCOMMAND_H

#include <QSharedPointer>
#include <QUndoCommand>
#include <QPoint>

class VertexData;
class CanvasWidget;

class MoveVertexCommand : public QUndoCommand
{
	public:
		MoveVertexCommand(int index, const QPoint &dp, QSharedPointer<VertexData> vertexData, CanvasWidget *canvasWidget, QUndoCommand *parent = 0);

		// QUndoCommand interface
	public:
		void undo() Q_DECL_OVERRIDE;
		void redo() Q_DECL_OVERRIDE;
		int id() const Q_DECL_OVERRIDE;
		bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;

		int getVertexIndex() const;
		const QPoint &getNewPosition() const;

	private:
		QSharedPointer<VertexData> m_vertexData;
		CanvasWidget *m_canvasWidget;
		int m_index;
		QPoint m_oldPos;
		QPoint m_newPos;

};

#endif // MOVEVERTEXCOMMAND_H
