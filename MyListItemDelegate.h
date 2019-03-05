#include <QtWidgets>
#include <QObject>

class MyListItemDelegate: public QStyledItemDelegate
{
public:
    MyListItemDelegate(QWidget* parent = nullptr);

    virtual QSize sizeHint(const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const override;
    virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual bool editorEvent(QEvent* event,
                             QAbstractItemModel* model,
                             const QStyleOptionViewItem& option,
                             const QModelIndex& index) override;
    virtual QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    virtual void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

