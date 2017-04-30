#include<QPushButton>
#include<QToolTip>

class QMPButton : public QPushButton
{
  Q_OBJECT

public:
  explicit QMPButton(const QString &description,QObject *parent = 0);

signals:
public slots:

public:
  QSize imagesize;
};
