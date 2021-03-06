/*
 * lcd_SPFD5414D.h
 *
 *  Created on: 30.01.2011
 *      Author: Miroslav Kostadinov
 */

#ifndef LCD_SPFD5414D_H_
#define LCD_SPFD5414D_H_

#include <lcd.h>

struct SPFD5414D: public LCD_MODULE
{
	unsigned int reset_timeout;
	unsigned int* disp_buf;
    unsigned int video_buf[256];

	SPFD5414D(	unsigned int x, unsigned int y,
				unsigned int dx, unsigned int dy,
				HANDLE hnd, const PIN_DESC* p) :
		LCD_MODULE(x, y, dx, dy, hnd, p), reset_timeout(0)
	{
	}
	;

	//virtual functions
	virtual void lcd_reset();
	void draw_bitmap( int x0,  int y0,
			const  char* src,  int width,  int rows);
	void draw_point( int x,  int y);
	void draw_hline( int x0,  int x1,  int y);
	void draw_bline( int x0,  int x1,  int y);
	void draw_vline( int y0,  int y1,  int x);
	void invert_vline( int y0,  int y1,  int x);
	void invert_hline( int x0,  int x1,  int y);
	void update_screen();
	void clear_screen();
	void redraw_rect (GObject* object, RECT_T area);
	void direct_write (GSplash draw_cb);
	void adjust_for_screen (GObject** object, RECT_T &area);

};

#ifndef CSX_PIN_INDX
#define CSX_PIN_INDX	2
#endif
#ifndef SCL_PIN_INDX
#define SCL_PIN_INDX	3
#endif
#ifndef SDA_PIN_INDX
#define SDA_PIN_INDX	4
#endif


/**
 * TFT_CHECK class can be used to detect the LCD MODULE installed.
 * It is using GPIOs only so it can be called from AppInit()
 *
 */
struct TFT_CHECK
{
	const PIN_DESC* pins;

	TFT_CHECK(const PIN_DESC* p) : pins(p)
	{
	}
	;

	void delay(unsigned int time = 0);
	void tft_write(unsigned int value);
	unsigned int tft_read();

	unsigned int read_id();
	unsigned int id();
};

#endif /* LCD_SPFD5414D_H_ */
