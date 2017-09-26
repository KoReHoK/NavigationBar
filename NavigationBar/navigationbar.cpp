#include "navigationbar.h"
#include <QScrollArea>

NavigationBar::NavigationBar(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setMargin(0);

	QWidget		*scrollWidget = new QWidget(this);
	scrollLayout = new QVBoxLayout(scrollWidget);
	scrollLayout->setMargin(0);
	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(scrollWidget);
	mainLayout->addWidget(scrollArea);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

	animation = new QPropertyAnimation(this, "geometry", this);
	connect(animation, &QPropertyAnimation::finished, this, &NavigationBar::finish);

	QToolButton *expandButton = new QToolButton(this);
	expandButton->setText("");
	expandButton->setIcon(QIcon(":/icons/Resources/expand.png"));
	expandButton->setIconSize(QSize(ICON_W, ICON_W));
	//expandButton->setAttribute(Qt::WA_Hover);
	expandButton->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	expandButton->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
	m_buttons.push_back(expandButton);

	mainLayout->setMenuBar(expandButton);
	connect(expandButton, &QToolButton::clicked, this, &NavigationBar::expandPressed);
}

NavigationBar::~NavigationBar()
{
	animation->deleteLater();
	scrollLayout->deleteLater();

	for (auto &b : m_buttons)
		b->deleteLater();
}

void NavigationBar::expandPressed()
{
	expand = !expand;

	if (expand) {	// for false has function void AbstractNavBar::finish()
		for (const auto &b : m_buttons)
			b->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);
	}

	QRect geom = geometry();
	animation->setDuration(duration);
	animation->setStartValue(geom);

	if (m_isRightExpand && expand) {
		animation->setEndValue(QRect(geom.x(), geom.y(), ICON_W + 8 + expandWidth, geom.height()));
	}
	else if (m_isRightExpand && !expand) {
		animation->setEndValue(QRect(geom.x(), geom.y(), ICON_W + 8, geom.height()));
	}
	else if (!m_isRightExpand && expand) {
		animation->setEndValue(QRect(geom.x() - expandWidth, geom.y(), ICON_W + 8 + expandWidth, geom.height()));
	}
	else if (!m_isRightExpand && !expand) {
		animation->setEndValue(QRect(geom.x() + geom.width() - (ICON_W + 8), geom.y(), ICON_W + 8, geom.height()));
	}

	animation->start();
	emit expanded(expand);
}

void NavigationBar::finish()	// дл€ более красивой отрисовки
{
	if (!expand && (animation->state() == QAbstractAnimation::State::Stopped)) {
		for (const auto &b : m_buttons) {
			b->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
		}
	}
}

void NavigationBar::addElement(QIcon& icon, QString& caption)
{
	m_buttons.push_back(new QToolButton(this));
	m_buttons.back()->setIcon(icon);
	m_buttons.back()->setText(caption);
	m_buttons.back()->setToolTip(caption);
	m_buttons.back()->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
	m_buttons.back()->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
	m_buttons.back()->setIconSize(QSize(ICON_W, ICON_W));
	//m_buttons.back()->setAttribute(Qt::WA_Hover);	// необходимо дл€ обработки событий QEvent::HoverEnter и QEvent::HoverLeave
	//m_buttons.back()->setCursor(*myCursor);

//	ќпредел€ем самую длинную строчку, чтобы знать насколько экспандить меню
	QFont font = m_buttons.back()->font();
	QFontMetrics fm(font);
	if (fm.width(caption) > expandWidth) {
		setExpandWidth(fm.width(caption) + 10);
	}	

	if (m_isRightExpand) {
		m_buttons.back()->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
	}
	else {
		m_buttons.back()->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
	}
		
	scrollLayout->addWidget(m_buttons.back());

	QRect pos = geometry();
	pos.setWidth(ICON_W + 8);
	pos.setHeight(height() + ICON_W);
	setGeometry(pos);
}

void NavigationBar::setDuration(const int dur) {
	if (duration != dur) {
		duration = dur;
		emit durationChanged(dur);
	}
}

void NavigationBar::setExpandWidth(const int exWidth) {
	if (expandWidth != exWidth) {
		expandWidth = exWidth;
		emit expandWidthChanged(exWidth);
	}
}

void NavigationBar::setExpanded(const bool exp) {
	// TODO: add implementation from expandPressed
	if (expand != exp) {
		expand = exp;
		emit expanded(expand);
	}
}

void NavigationBar::setRightExpand(const bool rExpand) { 
	if (m_isRightExpand != rExpand) {
		m_isRightExpand = rExpand;
	}
}