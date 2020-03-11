#include "Frameless.h"
#include "qdebug.h"
#include "windows.h"
#include "windowsx.h"
#include "qevent.h"

Frameless::Frameless(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.newTitlebarLayout->setMenuBar(ui.menuBar);
}

bool Frameless::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	if (eventType != "windows_generic_MSG") {
		return QWidget::nativeEvent(eventType, message, result);
	}

	const MSG *msg = reinterpret_cast<MSG *>(message);

	// 마우스를 처리하고 싶다면?
	// long x = GET_X_LPARAM(msg->lParam);
	// long y = GET_Y_LPARAM(msg->lParam);

	switch (msg->message) {
		// make frameless window
		case WM_NCCALCSIZE: {
			//this kills the window frame and title bar we added with
			//WS_THICKFRAME and WS_CAPTION
			if (false)
				return QWidget::nativeEvent(eventType, message, result);
			*result = 0;
			return true;
		}
		default: {
			return QWidget::nativeEvent(eventType, message, result);
		}
	}
}

void Frameless::mousePressEvent(QMouseEvent *e)
{
	int x = e->pos().x();
	int y = e->pos().y();
	QSize size = this->size();

	qDebug() << "\n\n" << x << y << "\n\n";
	qDebug() << "\n\n" << size.width() << size.height() << "\n\n";

	if (e->button() == Qt::LeftButton) {
		ReleaseCapture();
		if (x < 50 && y > size.height() - 50) {
			this->setCursor(QCursor(Qt::SizeBDiagCursor));
			SendMessage(HWND(winId()), WM_NCLBUTTONDOWN, HTBOTTOMLEFT, 0);
		}
		else if (x > size.width() - 50 && y > size.height() - 50) {
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
			SendMessage(HWND(winId()), WM_NCLBUTTONDOWN, HTBOTTOMRIGHT, 0);
		}
		else if (x < 50) {
			this->setCursor(QCursor(Qt::SizeHorCursor));
			SendMessage(HWND(winId()), WM_NCLBUTTONDOWN, HTLEFT, 0);
		}
		else if (y > size.height() - 50) {
			this->setCursor(QCursor(Qt::SizeVerCursor));
			SendMessage(HWND(winId()), WM_NCLBUTTONDOWN, HTBOTTOM, 0);
		}
		else if (x > size.width() - 50) {
			this->setCursor(QCursor(Qt::SizeHorCursor));
			SendMessage(HWND(winId()), WM_NCLBUTTONDOWN, HTRIGHT, 0);
		}
		else if (y < 50) {		// 여기가 titlebar가 된다.
			SendMessage(HWND(winId()), WM_NCLBUTTONDOWN, HTCAPTION, 0);
		}
	}
}

bool Frameless::event(QEvent *event)
{

	QPoint widgetCursorPos = QWidget::mapFromGlobal(QCursor::pos());

	int x = widgetCursorPos.x();
	int y = widgetCursorPos.y();
	QSize size = this->size();

	switch (event->type())
	{
	case QEvent::MouseButtonPress:
		// 여기서 mousepress event 처리하면 안먹음.
	case QEvent::HoverEnter:
	case QEvent::HoverMove:
		qDebug() << "\n\n HoverEnter \n\n";
		qDebug() << "\n\n" << widgetCursorPos.x() << widgetCursorPos.y() << "\n\n";
		if (x < 50 && y > size.height() - 50) {
			this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x > size.width() - 50 && y > size.height() - 50) {
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		else if (x < 50) {
			this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (y > size.height() - 50) {
			this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else if (x > size.width() - 50) {
			this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else {
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
		return true;
		break;
	case QEvent::HoverLeave:
		qDebug() << "\n\n HoverLeave \n\n";
		this->setCursor(QCursor(Qt::ArrowCursor));
		return true;
		break;

	default:
		break;
	}

	return QWidget::event(event);
}