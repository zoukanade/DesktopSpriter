//
// Created by kanade on 2023/5/28.
//
//4070
#include "Nahida.h"

Nahida::Nahida() : QWidget(nullptr) {
    //小图标菜单
    QMenu *menu = new QMenu(this);
    QIcon icon = QIcon(R"(.\sprite\nahida\hx_0.png)");
    auto *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("nahida"); //提示文字

    QAction *quit = new QAction("退出",this);
    connect(quit,&QAction::triggered, this, &Nahida::quit);

    menu->addAction(quit);
    trayIcon->setContextMenu(menu);
    trayIcon->show();
    //右键菜单
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &Nahida::customContextMenu);

    QDesktopWidget *pDesktopWidget = new QDesktopWidget();
    //获取可用桌面大小
    QRect deskRect = pDesktopWidget->availableGeometry();
    qInfo("desktop:W:%d\tH:%d", deskRect.width(), deskRect.height());
    this->resize(239,268);
    this->QWidget::move(200,200);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//透明
    this->setWindowFlag(Qt::FramelessWindowHint);//无边框
    this->show();

    this->spriteNahida = new Spriter(this);
    //this->spriteNahida->Spriter::move(-45, 30);
    this->spriteNahida->load(R"(.\sprite\nahida\hx_*.png)", "nahida", 16);
    this->spriteNahida->load(R"(.\sprite\nahida\t_*.png)", "nahida_t", 16);
    this->spriteNahida->load(R"(.\sprite\nahida\fing_*.png)", "nahida_fing", 16);
    this->spriteNahida->play("nahida_fing");
    ///Box2d
    this->timer_box2d_step = new QTimer(this);
    this->timer_box2d_step->setTimerType(Qt::PreciseTimer);//使用精确定时器
    connect(this->timer_box2d_step, &QTimer::timeout, this, &Nahida::box2d_step);
    this->timer_getWidgetSpeed = new QTimer(this);
    this->timer_getWidgetSpeed->setTimerType(Qt::PreciseTimer);//使用精确定时器
    connect(this->timer_getWidgetSpeed, &QTimer::timeout, this, &Nahida::getWidgetSpeed);
    //创建世界
    this->world = new b2World(b2Vec2(0.0f, 9.8f));//创建世界并设置重力
    this->world->SetAllowSleeping(true);//允许静止的物体休眠
    this->world->SetContinuousPhysics(true);//开启连续物理检测，使模拟更加的真实
    //创建刚体
    b2BodyDef body = b2BodyDef();//定义一个刚体信息对象
    body.type = b2_dynamicBody;
    body.position = b2Vec2(0.01f,0.01f);
    body.fixedRotation = true;//是否禁止刚体旋转
    //body.linearDamping = 2.75f;//线性阻尼
    body.gravityScale = 40.0f;//受到的重量影响倍数
    b2BodyDef boundary = b2BodyDef();//定义一个刚体信息对象 边界
    boundary.position = b2Vec2(0.0f,0.0f);
    boundary.type = b2_staticBody;
    auto *rect = new b2PolygonShape();
    rect->SetAsBox(this->width() / 2, this->height() / 2, b2Vec2(this->width() / 2, this->height() / 2), 0.0f);
    auto *fd = new b2FixtureDef();
    fd->shape = rect;
    fd->density = 0.01f;//密度
    //fd->friction = 1.0f;//摩擦系数
    fd->restitution = 0.25f;//弹性系数
    this->spriteNahidaBody = world->CreateBody(&body);//创建一个刚体


    auto *boundaryBody = world->CreateBody(&boundary);//创建一个刚体 边界
    this->spriteNahidaBody->CreateFixture(fd);
    //边框
    auto *shapeTop = new b2EdgeShape();
    shapeTop->SetTwoSided(b2Vec2(0, 0), b2Vec2(deskRect.width(), 0));
    auto *shapeLeft = new b2EdgeShape();
    shapeLeft->SetTwoSided(b2Vec2(0, 0), b2Vec2(0, deskRect.height()));
    auto *shapeRight = new b2EdgeShape();
    shapeRight->SetTwoSided(b2Vec2(deskRect.width(), 0), b2Vec2(deskRect.width() , deskRect.height()));
    auto *shapeBottom = new b2EdgeShape();
    shapeBottom->SetTwoSided(b2Vec2(0, deskRect.height()), b2Vec2(deskRect.width(), deskRect.height()));

    auto *fixtureTop = new b2FixtureDef();
    fixtureTop->shape = shapeTop;
    auto *fixtureLeft = new b2FixtureDef();
    fixtureLeft->shape = shapeLeft;
    auto *fixtureRight = new b2FixtureDef();
    fixtureRight->shape = shapeRight;
    auto *fixtureBottom = new b2FixtureDef();
    fixtureBottom->shape = shapeBottom;

    boundaryBody->CreateFixture(fixtureTop);
    boundaryBody->CreateFixture(fixtureLeft);
    boundaryBody->CreateFixture(fixtureRight);
    boundaryBody->CreateFixture(fixtureBottom);

    this->timer_box2d_step->start(2);

}
void Nahida::box2d_step() {
    this->world->Step(0.002, 10,10);
    if(this->spriteNahidaBody->IsAwake()){
        const b2Vec2 &position = this->spriteNahidaBody->GetPosition();
        this->QWidget::move(position.x, position.y);
        this->spriteNahida->play("nahida_fing");
        return;
    }

    if(this->spriteNahida->getNowSprite()->getName() == "nahida_fing")
        this->spriteNahida->play("nahida");
}

void Nahida::getWidgetSpeed() {
    widgetSpeed->x = (float)(this->QWidget::x() - startWidgetPoint.x()) * 7500.0f;
    widgetSpeed->y = (float)(this->QWidget::y() - startWidgetPoint.y()) * 7500.0f;
    startWidgetPoint = this->QWidget::pos();
}

void Nahida::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        m_bDrag = true;
        this->mouseStartPoint = event->globalPos();//获得鼠标起始位置
        this->windowTopLeftPoint = this->frameGeometry().topLeft();//获得窗口起始位置

        this->spriteNahida->play("nahida_t");
        this->spriteNahidaBody->SetAwake(false);
        timer_getWidgetSpeed->start(10);
    }
    QWidget::mousePressEvent(event);
}

void Nahida::mouseMoveEvent(QMouseEvent *event) {
    if(this->m_bDrag){
        QPoint distance = event->globalPos() - this->mouseStartPoint;//获得鼠标移动的距离
        this->move(this->windowTopLeftPoint + distance);//改变窗口的位置
    }
    QWidget::mouseMoveEvent(event);
}

void Nahida::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        this->m_bDrag = false;

        timer_getWidgetSpeed->stop();
        this->spriteNahidaBody->SetTransform(b2Vec2(this->QWidget::x(),this->QWidget::y()), 0);
        qInfo("%f\t%f", this->widgetSpeed->x, this->widgetSpeed->y);
        this->spriteNahidaBody->ApplyLinearImpulseToCenter(*this->widgetSpeed, true);
        //this->spriteNahidaBody->SetAwake(true);
    }
    QWidget::mouseReleaseEvent(event);
}

void Nahida::quit() {
    QApplication::quit();
}

void Nahida::customContextMenu(const QPoint &pos) {

    QMenu *menu = new QMenu(this);
    QAction *quit = new QAction("退出",this);
    connect(quit,&QAction::triggered, this, &Nahida::quit);

    menu->addAction(quit);
    menu->move(this->cursor().pos());
    menu->show();
}
