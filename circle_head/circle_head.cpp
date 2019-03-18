#include "circle_head.h"
#include "QPainter"
#include "QMouseEvent"
#include "QtDebug"

circle_head::circle_head(QWidget *parent) : QWidget(parent)
{
    const QColor background(45,45,46);
    setPalette(QPalette(background));
    setAutoFillBackground(true);
    SourceFile.clear();
    isImgShow = false;
    cover_pen_width = 120;
    qDebug()<<"The pen width is:"<<cover_pen_width;
    is_show_border = false;
}



void circle_head::saveImg(void)
{

//    QPixmap Img = this->grab();
//    Img.save("Img.png");
    qDebug()<<"Last:"<<cover_x_s+cover_pen_width/2<<cover_y_s+cover_pen_width/2<<cover_x_e-cover_pen_width<<cover_y_e-cover_pen_width;
    //
    QPixmap Img = this->grab();
    int last_img_s_x = cover_x_s+cover_pen_width/2;
    int last_img_s_y = cover_y_s+cover_pen_width/2;
    int last_img_width = cover_x_e-cover_pen_width;
    QPixmap last_img = Img.copy(last_img_s_x,last_img_s_y,last_img_width,last_img_width);
    last_img.save("last.png");
    is_show_border = true;

    this->update();
}
// 鼠标移动事件       默认情况下，触发事件需要点击一下，才能触发。可设置为自动触发:setMouseTracking(true);
void circle_head::mouseMoveEvent(QMouseEvent *event)
{
    int x_step=0,y_step = 0;
    // 这里必须使用buttons()
    qDebug()<<"mouse move";
    if(event->buttons() & Qt::LeftButton){  //进行的按位与
            x_step = mouse_x_old - event->x();
            y_step = mouse_y_old - event->y();

            cover_x_s= cover_x_s - x_step;
            cover_y_s= cover_y_s - y_step;
            this->update();
            qDebug()<<"remove paint";
            mouse_x_old = event->x();
            mouse_y_old = event->y();
    }else if(event->buttons() & Qt::RightButton)
    {
        x_step = mouse_x_right_btn_old - event->x();
        y_step = mouse_y_right_btn_old - event->y();

        img_x_s = img_x_s - x_step;
        img_y_s -= y_step;
        this->update();
        qDebug()<<"mouse move & right button press";
        mouse_x_right_btn_old = event->x();
        mouse_y_right_btn_old = event->y();
    }
}




void circle_head::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(isImgShow == false)
    {
        if(SourceFile.isEmpty() == false)
        {
            const QColor background(255,255,255);
            setPalette(QPalette(background));
            isImgShow = true;
            img_x_s=0;
            img_y_s=0;
            drawpic(&p);
            drawCoverFirst(&p);
            cover_pen_width = 120;
        }
    }else{
        drawpic(&p);
        drawCover(&p);
        draw_external(&p);
    }

    if(is_show_border)
    {
        is_show_border = false;
        p.save();
    //    QPen pen(QColor(45,45,46));
        QPen pen(Qt::red);
//        pen.setWidth(cover_pen_width);
        p.setPen(pen);
        p.drawRect(cover_x_s+cover_pen_width/2,cover_y_s+cover_pen_width/2,cover_x_e-cover_pen_width,cover_y_e-cover_pen_width);
        p.restore();
    }
}

void circle_head::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键按下   改变指针形状，并且存储当前指针位置与窗口位置的差值。
    if(event->button() == Qt::LeftButton){
        qDebug()<<"left button Press";
//        isLeftButtonPress = true;
        mouse_x_old = event->x();
        mouse_y_old = event->y();
    }
    // 如果是鼠标右键按下
    else if(event->button() == Qt::RightButton){
        qDebug()<<"right button Press";
        mouse_x_right_btn_old = event->x();
        mouse_y_right_btn_old = event->y();
    }
}


void circle_head::wheelEvent(QWheelEvent *event)
{
    if(isImgShow)
    {
        if(event->delta() > 0){
            cover_pen_width --;
        }else{//当滚轮向使用者方向旋转时
            cover_pen_width ++;
        }
        if(cover_pen_width >0)
            this->update();
    }
}

void circle_head::drawCoverFirst(QPainter *p)
{
    p->save();
    cover_x_s=0;
    cover_y_s=0;
    cover_x_e = width();
    cover_y_e =  width();

    QPen pen(Qt::white);
    pen.setWidth(120);
    p->setPen(pen);
    p->drawArc(cover_x_s,cover_y_s,cover_x_e,cover_y_e,0*16,360*16);
    p->restore();
}


void circle_head::drawCover(QPainter *p)
{
    p->save();
//    QPen pen(QColor(45,45,46));
    QPen pen(Qt::white);
    pen.setWidth(cover_pen_width);
    p->setPen(pen);

    p->drawArc(cover_x_s,cover_y_s,cover_x_e,cover_y_e,0*16,360*16);
    p->restore();
    qDebug()<<"cover:"<<cover_pen_width<<cover_x_s<<cover_y_s<<cover_x_e;
}


void circle_head::drawpic(QPainter *p)
{
    p->save();
    QPixmap pix,pix_scaled;
    pix.load(SourceFile);

    if(pix.width() > pix.height())
    {
        pix_scaled = pix.scaledToWidth(this->width());
        qDebug()<<"scale to width";
    }else{
        pix_scaled = pix.scaledToHeight(this->height());
        qDebug()<<"scale to height";
    }
    p->drawPixmap(img_x_s,img_y_s, pix_scaled);
    p->restore();
}


void circle_head::draw_external(QPainter *p)
{
    p->save();
    QPen pen(Qt::white);
    p->setPen(pen);
    p->setBrush(QColor(255,255,255));
    int last_img_s_x = cover_x_s+cover_pen_width/2;
    int last_img_s_y = cover_y_s+cover_pen_width/2;
    int last_img_width = cover_x_e-cover_pen_width;

    int x,y,w,h;
    x=0;
    y=0;
    w = last_img_s_x;
    h = this->height();
    p->drawRect(x,y,w,h);

    w = this->width();
    h = last_img_s_y;
    p->drawRect(x,y,w,h);


    x = 0;
    y = last_img_s_y + last_img_width;

    w = this->width();
    if(this->height() >(last_img_s_y + last_img_width))
        h = this->height() - (last_img_s_y + last_img_width);
    p->drawRect(x,y,w,h);

    x = last_img_s_x + last_img_width;
    if(this->width() > x)
        w = this->width() - x;
    h = this->width();
    y=0;
    p->drawRect(x,y,w,h);
    p->restore();
}


void circle_head::setSourcefile(QString sourcefile)
{
    SourceFile = sourcefile;
    if (SourceFile.isEmpty() == false)
    {
        this->update();
    }
}


void circle_head::show_msg(void)
{

}
