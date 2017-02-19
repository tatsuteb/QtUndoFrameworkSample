#include "MoveVertexCommand.h"
#include "VertexData.h"
#include "CanvasWidget.h"

MoveVertexCommand::MoveVertexCommand(int index, const QPoint &newPosition, QSharedPointer<VertexData> vertexData, CanvasWidget *canvasWidget, QUndoCommand *parent) :
	QUndoCommand(parent),
	m_vertexData(vertexData),
	m_canvasWidget(canvasWidget),
	m_index(index),
	m_oldPos(m_vertexData->getPointByIndex(m_index)),
	m_newPos(newPosition)
{
	setText(QString("Move Vertex Command: From (%1, %2) To (%3, %4)")
			.arg(m_oldPos.x()).arg(m_oldPos.y())
			.arg(m_newPos.x()).arg(m_newPos.y())
			);
}

void MoveVertexCommand::undo()
{
	m_vertexData->moveVertex(m_index, m_oldPos);
	m_canvasWidget->update();
}

void MoveVertexCommand::redo()
{
	m_vertexData->moveVertex(m_index, m_newPos);
	m_canvasWidget->update();
}

int MoveVertexCommand::id() const
{
	return 1;
}

bool MoveVertexCommand::mergeWith(const QUndoCommand *other)
{
	const MoveVertexCommand *moveVertexCommand = static_cast<const MoveVertexCommand *>(other);

	// 同じ頂点を動かし続けているかどうか
	if (m_index != moveVertexCommand->getVertexIndex())	return false;

	m_newPos = moveVertexCommand->getNewPosition();

	return true;
}

int MoveVertexCommand::getVertexIndex() const
{
	return m_index;
}

const QPoint &MoveVertexCommand::getNewPosition() const
{
	return m_newPos;
}
