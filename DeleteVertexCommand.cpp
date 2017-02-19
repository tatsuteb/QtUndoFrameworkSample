#include "DeleteVertexCommand.h"

#include "CanvasWidget.h"
#include "VertexData.h"

DeleteVertexCommand::DeleteVertexCommand(int index, QSharedPointer<VertexData> vertexData, CanvasWidget *canvasWidget, QUndoCommand *parent):
	QUndoCommand(parent),
	m_vertexData(vertexData),
	m_canvasWidget(canvasWidget),
	m_index(index)
{

}

void DeleteVertexCommand::undo()
{
	m_vertexData->addVertex(m_point);
	m_canvasWidget->update();
}

void DeleteVertexCommand::redo()
{
	m_point = m_vertexData->removeVertexAt(m_index);
	m_canvasWidget->update();
}
