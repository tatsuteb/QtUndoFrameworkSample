#include "VertexData.h"

const QPoint VertexData::INVALID_POINT = QPoint(-1, -1);

VertexData::VertexData()
{

}

int VertexData::addVertex(const QPoint &point)
{
	if (point.x() < 0 || point.y() <0) return INVALID_INDEX;


	m_points << point;

	return m_points.count() - 1;
}

QPoint VertexData::removeVertexAt(int index)
{
	if (index < 0) return INVALID_POINT;
	if (index >= m_points.count()) return INVALID_POINT;

	return m_points.takeAt(index);
}

void VertexData::moveVertex(int index, const QPoint &newPosition)
{
	Q_ASSERT(index >= 0 && index < m_points.count());

	m_points.replace(index, newPosition);
}

const QPoint &VertexData::getPointByIndex(int index)
{
	Q_ASSERT(index >= 0 && index < m_points.count());

	return m_points.at(index);
}

const QList<QPoint> &VertexData::getPoints() const
{
	return m_points;
}

int VertexData::getVertexCount() const
{
	return m_points.count();
}
