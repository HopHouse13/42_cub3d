#include "mlx_int.h"
#include <X11/extensions/Xfixes.h>
#define LEAK_FIX 1

int		mlx_mouse_move(t_xvar *xvar, t_win_list *win, int x, int y)
{
	XWarpPointer(xvar->display, None, win->window, 0, 0, 0, 0, x, y);

	// rajout fix leaks en dessous
	XFlush(xvar->display);
	return (0);
}

int		mlx_mouse_hide(t_xvar *xvar, t_win_list *win, int x)
{
	#if LEAK_FIX
	XFixesHideCursor(xvar->display, win->window);
	XFlush(xvar->display);

	#else
	static char data[1] = {0};
	Cursor cursor;
	Pixmap blank;
	XColor dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);

	#endif
	return (0);
}

int		mlx_mouse_show(t_xvar *xvar, t_win_list *win)
{
	#if LEAK_FIX
	XFixesShowCursor(xvar->display, win->window);
	XFlush(xvar->display);

	#else
	XUndefineCursor(xvar->display, win->window);

	#endif
	return (0);
}

/*
** Queries the position of the mouse pointer relative to the origin of the
** specified window and saves it to the provided location.
**
** If the pointer is not on the same screen as the specified window, both
** win_x_return and win_y_return are set to zero and the function returns 0.
*/

int		mlx_mouse_get_pos(t_xvar *xvar, t_win_list *win, \
			int *win_x_return, int *win_y_return)
{
	Window		root_return;
	Window		child_return;
	int			root_x_return;
	int			root_y_return;
	unsigned	mask_return;

	return (XQueryPointer(xvar->display, win->window, \
		&root_return, &child_return, &root_x_return, &root_y_return, \
		win_x_return, win_y_return, &mask_return));
}
