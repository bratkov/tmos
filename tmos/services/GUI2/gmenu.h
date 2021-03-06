/*
 * gmenu.h
 *
 *  Created on: 03.10.2013
 *      Author: stanly
 */

#ifndef GMENU_H_
#define GMENU_H_

#include <gobject.h>
#include <gscroll.h>

#define GMENU_FLG_CHECK_ITEM		0x0100

struct MENUTEMPLATE
{
	int 		parent;
	short unsigned int	item;
	short unsigned int	flags;
	const char*	item_name;
};

struct menu_template_t
{
	int 		parent;
	short unsigned int 	item;
	short unsigned int	flags;
	CSTRING		item_name;
};


struct GEdit;
struct GListBox;

struct GMenu: GObject
{
	friend GEdit;
	friend GListBox;

	menu_template_t*	base;
	menu_template_t*	menu;
	menu_template_t*	item;
	const char*		title;
	int 			size;
	GScroll* 		scroll;
	const RENDER_MODE*	text_font;

	GMenu (GId id_t, RECT_T rect_t, const char* title_t, GFlags flags_t = GO_FLG_DEFAULT)
		:GObject (id_t, rect_t, flags_t),
		 base(NULL), menu(NULL), item(NULL), title(title_t),
		 size(0), scroll(NULL), text_font(&FNT5x7)
	{}

	GMenu(): base(NULL), menu(NULL), item(NULL), title(NULL), size(0),
			scroll(NULL), text_font(&FNT5x7)
	{}

	~GMenu()
	{
		if(scroll)
		{
			delete scroll;
			scroll = NULL;
		}
		if(base)
		{
			size =0;
			while( !IsEmpty(base + size) )
			{
				base[size++].item_name.free();
			}
			delete base;
			base = NULL;
		}
	}

	void free()
	{
		if(scroll)
		{
			delete scroll;
			scroll = NULL;
		}
		if(base)
		{
			size =0;
			while(	!IsEmpty(base + size) )
			{
				base[size++].item_name.free();
			}
			delete base;
			base = NULL;
		}
		item = menu = NULL;
		size=0;
	}

	virtual bool AppendMenu(int parent_id, int menu_id, const CSTRING& menu_name, short unsigned int flg =0);
	bool LoadMenu(const MENUTEMPLATE* pat);

	menu_template_t* GetItem(int parent_id, int menu_id);
	menu_template_t* FindItem(int item_id);
	menu_template_t* GetMenu(int parent_id, menu_template_t* start = NULL);
	int GetMenuSize(int menu_id);
	bool SetReplaceItem(int item_id, const CSTRING& item_name, short unsigned int flg =0);
	bool Select(int item_id);
	virtual bool RemoveItem(int item_id);
	bool InsertItem(int item_id, int new_item_id, const CSTRING& new_item_name, short unsigned int new_flg =0);

protected:
	virtual void draw_this (LCD_MODULE* lcd);
	virtual unsigned int process_key (GMessage& msg);
	virtual unsigned int initialize (GMessage& msg);

	bool IsEmpty(menu_template_t* ptr)
	{
		return (!ptr->item && !ptr->parent && ptr->item_name.empty());
	}
	bool process_selected();
	int get_item_pos(menu_template_t* ptr);
//private:
	virtual bool set_scroll(void);
	bool add_item(int parent_id, int item_id, const CSTRING& name, short unsigned int flg =0);
	void adjust_item_names();
};

unsigned int remove_amp(CSTRING& str);
#endif /* GMENU_H_ */
