#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include <QWidget>
#include <Qpainter>

class TEXTLabel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int  fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(bool haveBorder READ haveBorder WRITE setBorder NOTIFY haveBorderChanged)
    Q_PROPERTY(QString unitStr READ unitStr WRITE setUnitStr NOTIFY unitStrChanged)

public:
    explicit TEXTLabel(QWidget *parent = 0);
    QString text() const { return this->m_text; }
    int fontSize() const { return this->m_size; }
    QColor textColor() const { return this->m_color; }
    bool haveBorder() const { return this->m_border; }
    QString unitStr() const { return this->m_unit; }

signals:
    void textChanged();
    void fontSizeChanged();
    void textColorChanged();
    void haveBorderChanged();
    void unitStrChanged();

public slots:
   void setText(QString text);
   void setFontSize(int size);
   void setTextColor(QColor color);
   void setBorder(bool border);
   void setUnitStr(QString unit);

private:
//   QPainter *painter;
   QString m_text;
   int m_size;
   QColor m_color;
   bool m_border;
   QString m_unit;

protected:
    void paintEvent(QPaintEvent *e);

};

#endif // TEXTLABEL_H
