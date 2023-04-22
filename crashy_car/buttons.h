/* this code was adapted from https://stackoverflow.com/a/53135675 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>
#include <QObject>

class OrientablePushButton : public QPushButton
{
    Q_OBJECT
public:
    enum Orientation {
        Horizontal,
        VerticalTopToBottom,
        VerticalBottomToTop
    };

    OrientablePushButton(QWidget * parent = nullptr);
    OrientablePushButton(const QString & text, QWidget *parent = nullptr);
    OrientablePushButton(const QIcon & icon, const QString & text, QWidget *parent = nullptr);

    QSize sizeHint() const;

    OrientablePushButton::Orientation orientation() const;
    void setOrientation(const OrientablePushButton::Orientation &orientation);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Orientation mOrientation = Horizontal;
};

#endif // BUTTONS_H
