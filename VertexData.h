#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QObject>
#include <QList>
#include <QPoint>

class VertexData : public QObject
{
		Q_OBJECT

	public:
		VertexData();

		// 追加した頂点のインデックスを返す
		int addVertex(const QPoint &point);

		// 指定されたインデックスの頂点を削除する
		QPoint removeVertexAt(int index);

		void moveVertex(int index, const QPoint &newPosition);

		const QPoint &getPointByIndex(int index);
		const QList<QPoint> &getPoints() const;
		int getVertexCount() const;

	private:
		static const QPoint INVALID_POINT;
		static const int INVALID_INDEX = -1;

		QList<QPoint> m_points;
};

#endif // VERTEXDATA_H
