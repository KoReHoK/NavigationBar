#pragma once
#include <QWidget>
#include <QLayout>
#include <QToolButton>
#include <QPropertyAnimation>

class NavigationBar : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(bool m_isRightExpand READ isRightExpand WRITE setRightExpand)
	Q_PROPERTY(int duration READ getDuration WRITE setDuration NOTIFY durationChanged)
	Q_PROPERTY(int expandWidth READ getExpandWidth WRITE setExpandWidth NOTIFY expandWidthChanged)
	Q_PROPERTY(bool expand READ isExpanded WRITE setExpanded NOTIFY expanded)

	Q_DISABLE_COPY(NavigationBar)

public:
	explicit NavigationBar(QWidget *parent = 0);
	~NavigationBar();

signals:
	void durationChanged(int);
	void expandWidthChanged(int);
	void expanded(bool);

public:
	inline int getDuration() const { return duration; }
	void setDuration(const int dur);

	inline int getExpandWidth() const { return expandWidth; }
	void setExpandWidth(const int exWidth);

	inline bool isExpanded() const { return expand; }
	void setExpanded(const bool exp);

	inline bool isRightExpand() const { return m_isRightExpand; }
	void setRightExpand(const bool rExpand);

public:
	void addElement(QIcon& icon, QString& caption);

private:
	QVBoxLayout *scrollLayout;
	std::vector<QToolButton*> m_buttons;

	QPropertyAnimation *animation = nullptr;

	int duration = 100;
	int expandWidth = 0;
	const int ICON_W = 32;
	
	bool expand = false;
	bool m_isRightExpand = true;

private slots:
	void finish();

public slots:
	void expandPressed();
};