#ifndef MYUNITMODEL_H
#define MYUNITMODEL_H // this took me hours to debug, UNITMODEL is defined by kunitconversio

#include <QAbstractListModel>
#include <QObject>
#include <kunitconversion/unit.h>
#include <unordered_map>

class UnitModel : public QAbstractListModel
{
    Q_OBJECT
public:
    UnitModel();
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE double getRet(double val, int fromType, int toType); // use int index because text may be localized
public slots:
    void changeUnit(QString type);

private:
    QList<KUnitConversion::Unit> units_;
    static const std::unordered_map<QString, int> categoryToEnum;
};
#endif // UNITMODEL_H
