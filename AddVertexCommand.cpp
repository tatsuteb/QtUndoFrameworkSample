#include "AddVertexCommand.h"

#include "VertexData.h"
#include "CanvasWidget.h"

AddVertexCommand::AddVertexCommand(const QPoint &pos, QSharedPointer<VertexData> vertexData, CanvasWidget *canvasWidget, QUndoCommand *parent):
	QUndoCommand(parent),
	m_point(pos),
	m_vertexData(vertexData),
	m_canvasWidget(canvasWidget),
	m_index(-1)
{

}

void AddVertexCommand::undo()
{
	m_vertexData->removeVertexAt(m_index);
	m_canvasWidget->update();
}

void AddVertexCommand::redo()
{
	m_index = m_vertexData->addVertex(m_point);
	m_canvasWidget->update();
}

