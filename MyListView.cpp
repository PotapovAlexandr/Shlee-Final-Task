#include "MyListView.h"

namespace
{
    QRect GetRectForHeader(const QRect& in)
    {
        return QRect(in.x(), in.y() , in.width(), 20);
    }

    QRect GetRectForPict(const QRect& in)
    {
        return QRect(in.x() + 20, in.y() + 20 , 60, 40);
    }

    QRect GetRectForLinc(const QRect& in)
    {
        return QRect(in.x(), in.y() + 80 , in.width(), 20);
    }

    QRect GetRectForDate(const QRect& in)
    {
        return QRect(in.x(), in.y() + 100 , in.width(), 20);
    }

    void ShowContent(const QString& filePath)
    {
        Screen* screen = new Screen();
        screen->setPixmap(QPixmap(filePath));
        screen->QWidget::showFullScreen();
    }
}

QSize MyListItemDelegate::sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const
{
    return QSize(130, 130);
}

void MyListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
    {
        return;
    }

    QRect rectForHeader = GetRectForHeader(option.rect);
    QRect rectForPict = GetRectForPict(option.rect);
    QRect rectForLinc = GetRectForLinc(option.rect);
    QRect rectForDate = GetRectForDate(option.rect);

    QPixmap img = index.data(PreviewRole).value<QPixmap>();

    painter->drawText(rectForHeader, index.data(HeaderRole).toString());
    painter->drawPixmap(rectForPict, img);
    painter->drawText(rectForLinc, "Linc");
    painter->drawText(rectForDate, "Date:" + index.data(CreationDateRole).toString());
    painter->drawRoundedRect(option.rect, 5, 5);
}

bool MyListItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
    if (mouseEvent && mouseEvent->type() == QEvent::MouseButtonRelease && mouseEvent->button() & Qt::LeftButton)
    {
       QRect rectForPict = GetRectForPict(option.rect);
       bool pl = index.data(IsPlayableRole).toBool();
       if (rectForPict.contains(mouseEvent->pos()) && pl)//index.data(IsPlayableRole).toBool())
       {
            ShowContent(index.data(FilePathRole).toString());
       }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QWidget* MyListItemDelegate::createEditor(QWidget *parent,
                      const QStyleOptionViewItem &option,
                      const QModelIndex &index) const
{
    QLineEdit* editor = new QLineEdit(parent);
    editor->setAutoFillBackground(true);
    return editor;
}

void MyListItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);
    lineEditor->setText(index.data(HeaderRole).toString());
}

void MyListItemDelegate::updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    editor->setGeometry(QRect(option.rect.x(), option.rect.y() , option.rect.width(), 20));
}

MyListView::MyListView(QWidget* parent): QListView(parent)
{
    setResizeMode(QListView::Fixed);
    setGridSize(QSize(150, 150));
    setWrapping( true );
    setFlow(QListView::LeftToRight);

    MyListItemDelegate* delegate = new MyListItemDelegate(this);
    setItemDelegate(delegate);
}
