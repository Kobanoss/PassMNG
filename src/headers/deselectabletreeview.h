#ifndef DESELECTABLETREEVIEW_H
#define DESELECTABLETREEVIEW_H

#include <QCoreApplication>
#include <QMouseEvent>
#include <QTime>
#include <QTreeView>

// Class for custom TreeView which is deselectable (only per click)
class DeselectableTreeView : public QTreeView {
    Q_OBJECT

public:

    DeselectableTreeView(QWidget *parent) : QTreeView(parent) {}

    virtual ~DeselectableTreeView() {}

signals:

    void emptyClicked();

private:
    bool doubleClickHappened = false;
    bool clickSelected = false;

    // Custom mousePressEvent function
    virtual void mousePressEvent(QMouseEvent *event) {
        clickSelected = selectionModel()->isSelected(indexAt(event->pos()));
        QTreeView::mousePressEvent(event);
    }
    // Custom mouseReleaseEvent function
    void mouseReleaseEvent(QMouseEvent *event) {
        doubleClickHappened = false;
        QTime dieTime = QTime::currentTime().addMSecs(200);

        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        if (!doubleClickHappened && clickSelected) {
            QModelIndex item = indexAt(event->pos());
            bool selected = selectionModel()->isSelected(indexAt(event->pos()));

            if ((item.row() == -1 && item.column() == -1) || selected) {
                clearSelection();
                const QModelIndex index;
                selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);

                emit emptyClicked();
        }
            else {
                QTreeView::mouseReleaseEvent(event);
            }
        }
        else {
          QTreeView::mouseReleaseEvent(event);
        }
        clickSelected = false;
  }
    // Custom mouseDoubleClickEvent function
    void mouseDoubleClickEvent(QMouseEvent *event) {
        doubleClickHappened = true;
        QTreeView::mouseDoubleClickEvent(event);
    }
};

#endif // DESELECTABLETREEVIEW_H
