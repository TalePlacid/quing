#ifndef TASKNAVIGATORVIEWMODEL_H
#define TASKNAVIGATORVIEWMODEL_H

#include <QObject>
#include <QStringList>
#include <QtTypes>

class TaskNavigatorActionHandler;

class TaskNavigatorViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList titles READ GetTitles NOTIFY TitlesChanged)
    Q_PROPERTY(qint64 length READ GetLength NOTIFY LengthChanged)

public:
    explicit TaskNavigatorViewModel(TaskNavigatorActionHandler* actionHandler, QObject* parent = 0);

    QStringList GetTitles() const;
    qint64 GetLength() const;

    Q_INVOKABLE void LoadCurrentPathTitles();

signals:
    void TitlesChanged();
    void LengthChanged();

private:
    TaskNavigatorActionHandler* actionHandler;
    QStringList titles;
    qint64 length;
};

#endif // TASKNAVIGATORVIEWMODEL_H
