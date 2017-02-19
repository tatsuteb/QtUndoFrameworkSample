#include "CanvasWidget.h"
#include "ui_CanvasWidget.h"

#include "AddVertexCommand.h"
#include "DeleteVertexCommand.h"
#include "MoveVertexCommand.h"
#include "VertexData.h"

#include <QMouseEvent>
#include <QPainter>

CanvasWidget::CanvasWidget(QUndoStack *undoStack, QSharedPointer<VertexData> vertexData, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CanvasWidget),
	m_undoStack(undoStack),
	m_vertexData(vertexData),
	m_activeVertexIndex(-1)
{
	ui->setupUi(this);

	this->setMouseTracking(true);
}

CanvasWidget::~CanvasWidget()
{
	delete ui;
}

void CanvasWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	// 点の描画
	painter.setPen(QPen(QBrush(Qt::red), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));

	auto points = m_vertexData->getPoints();
	for (auto point : points)
	{
		QRect rect = QRect(point - QPoint(3, 3), QSize(6, 6));
		painter.drawRect(rect);
	}

	// カーソルの近くの点を描画
	if (checkVertexIndex(m_activeVertexIndex))
	{
		painter.setPen(QPen(QBrush(Qt::red), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));

		auto point = m_vertexData->getPointByIndex(m_activeVertexIndex);
		QRect rect = QRect(point - QPoint(4, 4), QSize(8, 8));
		painter.drawRect(rect);
	}

}

void CanvasWidget::mouseMoveEvent(QMouseEvent *e)
{
	// ドラッグの時は、頂点を移動する
	if(e->buttons() & Qt::LeftButton)
	{
		if (!checkVertexIndex(m_activeVertexIndex)) return;

		MoveVertexCommand *moveVertexCommand = new MoveVertexCommand(m_activeVertexIndex, e->pos(), m_vertexData, this);
		m_undoStack->push(moveVertexCommand);

		m_draggingVertex = true;

		// 頂点を移動しているときは、アクティブな点を更新しない
		return;
	}


	// カーソルの近くの点のインデックスを更新
	m_activeVertexIndex = getVertexIndexByDistance(e->pos(), 6);
	this->update();
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *e)
{
	// 頂点を移動した後は、頂点を追加しない
	if (m_draggingVertex)
	{
		m_draggingVertex = false;
		return;
	}


	auto pos = e->pos();

	// Alt + Click で頂点の削除
	if (e->modifiers() == Qt::AltModifier)
	{
		deleteVertex(pos);

		return;
	}

	addVertex(pos);
}

void CanvasWidget::addVertex(const QPoint &pos)
{
	AddVertexCommand *addVertexCommand = new AddVertexCommand(pos, m_vertexData, this);
	addVertexCommand->setText(QString("Add Vertex Command:(%1, %2)").arg(pos.x()).arg(pos.y()));

	m_undoStack->push(addVertexCommand);

	m_activeVertexIndex = -1;
}

void CanvasWidget::deleteVertex(const QPoint &pos)
{
	// 最後に追加した点を削除候補にする
	int index = getVertexIndexByDistance(pos, 6);

	if (index < 0) return;

	DeleteVertexCommand *deleteVertexCommand = new DeleteVertexCommand(index, m_vertexData, this);
	deleteVertexCommand->setText(QString("Delete Vertex Command:(%1, %2)").arg(pos.x()).arg(pos.y()));

	m_undoStack->push(deleteVertexCommand);

	m_activeVertexIndex = -1;
}

int CanvasWidget::getVertexIndexByDistance(const QPoint &pos, float distance)
{
	int index = -1;

	// 最後に追加した点を削除候補にする
	auto points = m_vertexData->getPoints();
	for (int i = points.count() - 1; i >= 0; i--)
	{
		QVector2D v1(points.at(i));
		QVector2D v2(pos);

		if (v1.distanceToPoint(v2) <= distance)
		{
			index = i;
			break;
		}
	}

	return index;
}

bool CanvasWidget::checkVertexIndex(int index)
{
	if (index < 0) return false;
	if (index >= m_vertexData->getVertexCount()) return false;

	return true;
}
