#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QTableWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    /**
     * @brief TableWidget конструктор по-умолчанию
     * @param parent родительский виджет
     */
    TableWidget(QWidget *parent = nullptr);

protected:
    /**
     * @brief mouseMoveEvent обработчик движения указателя
     * @param event событие от фабрики событий
     */
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // TABLEWIDGET_H
