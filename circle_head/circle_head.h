#ifndef CIRCLE_HEAD_H
#define CIRCLE_HEAD_H

#include <QWidget>

class circle_head : public QWidget
{
    Q_OBJECT
public:
    explicit circle_head(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void drawCover(QPainter *p);
    void drawpic(QPainter *p);
    void setSourcefile(QString sourcefile);
    void drawCoverFirst(QPainter *p);
    void saveImg(void);
    void show_msg(void);
private:
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void draw_external(QPainter *p);
    QString SourceFile;
    bool isImgShow;
    int cover_pen_width;

    int mouse_x_old,mouse_y_old;
    int cover_x_s,cover_x_e,cover_y_s,cover_y_e;

    int mouse_x_right_btn_old,mouse_y_right_btn_old;
    int img_x_s,img_y_s;
    bool is_show_border;
};

#endif // CIRCLE_HEAD_H
