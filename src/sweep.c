//   Copyright 2022 Will Thomas
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <gtk/gtk.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t** field;
uint8_t** flag;
uint8_t w;
uint8_t h;
int16_t m;
int16_t f;
int8_t run;
int8_t usr;
GtkWidget*** evnt;
GtkWidget* win;
GtkWidget* box;
GtkWidget* scr;
GtkWidget* grid;

void vict() {
	gtk_label_set_text((GtkLabel*) scr, "victory");
	run = 0;
}

void deft() {
	for (uint8_t i0 = 0; i0 < w; i0++) {
		for (uint8_t i1 = 0; i1 < h; i1++) {
			if (field[i0][i1] == 9 && flag[i0][i1] == 0) {
				GtkWidget* img = gtk_container_get_children((GtkContainer*) evnt[i0][i1])->data;
				if (usr) gtk_image_set_from_file((GtkImage*) img, "/usr/share/sweep/img/mine.bmp");
				else gtk_image_set_from_file((GtkImage*) img, "img/mine.bmp");
			}
			else if (field[i0][i1] != 9 && flag[i0][i1] == 2) {
				GtkWidget* img = gtk_container_get_children((GtkContainer*) evnt[i0][i1])->data;
				if (usr) gtk_image_set_from_file((GtkImage*) img, "/usr/share/sweep/img/flsflag.bmp");
				else gtk_image_set_from_file((GtkImage*) img, "img/flsflag.bmp");
			}
		}
	}
	gtk_label_set_text((GtkLabel*) scr, "defeat");
	run = 0;
}

void press(GtkWidget* wid, GdkEventButton* evt) {
	if (!run) return;
	uint8_t wi;
	uint8_t hi;
	for (uint8_t i0 = 0; i0 < w; i0++) {
		for (uint8_t i1 = 0; i1 < h; i1++) {
			if (evnt[i0][i1] == wid) {
				wi = i0;
				hi = i1;
				break;
			}
		}
	}
	if (evt->button == 1 && flag[wi][hi] == 0 && field[wi][hi] == 9) deft();
	else if (evt->button == 1 && flag[wi][hi] == 0 && field[wi][hi] != 9) {
		flag[wi][hi] = 1;
		if (field[wi][hi] == 0)  {
			GtkWidget* img = gtk_container_get_children((GtkContainer*) wid)->data;
			if (usr) gtk_image_set_from_file((GtkImage*) img, "/usr/share/sweep/img/empt.bmp");
			else gtk_image_set_from_file((GtkImage*) img, "img/empt.bmp");
			if (wi > 0 && flag[wi - 1][hi] != 2) press(evnt[wi - 1][hi], evt);
			if (hi > 0 && flag[wi][hi - 1] != 2) press(evnt[wi][hi - 1], evt);
			if (wi < (w - 1) && flag[wi + 1][hi] != 2) press(evnt[wi + 1][hi], evt);
			if (hi < (h - 1) && flag[wi][hi + 1] != 2) press(evnt[wi][hi + 1], evt);
			if (wi > 0 && hi > 0 && flag[wi - 1][hi - 1] != 2) press(evnt[wi - 1][hi - 1], evt);
			if (wi < (w - 1) && hi > 0 && flag[wi + 1][hi - 1] != 2) press(evnt[wi + 1][hi - 1], evt);
			if (wi > 0 && hi < (h - 1) && flag[wi - 1][hi + 1] != 2) press(evnt[wi - 1][hi + 1], evt);
			if (wi < (w - 1) && hi < (h - 1) && flag[wi + 1][hi + 1] != 2) press(evnt[wi + 1][hi + 1], evt);
		}
		else {
			int8_t s[27];
			if (usr) sprintf(s, "/usr/share/sweep/img/%hhu.bmp", field[wi][hi]);
			else sprintf(s, "img/%hhu.bmp", field[wi][hi]);
			GtkWidget* img = gtk_container_get_children((GtkContainer*) wid)->data;
			gtk_image_set_from_file((GtkImage*) img, s);
		}
	}
	else if (evt->button == 1 && flag[wi][hi] == 1 && field[wi][hi] != 0){
		uint8_t fcnt = 0;
		if (wi > 0 && flag[wi - 1][hi] == 2) fcnt++;
		if (hi > 0 && flag[wi][hi - 1] == 2) fcnt++;
		if (wi < (w - 1) && flag[wi + 1][hi] == 2) fcnt++;
		if (hi < (h - 1) && flag[wi][hi + 1] == 2) fcnt++;
		if (wi > 0 && hi > 0 && flag[wi - 1][hi - 1] == 2) fcnt++;
		if (wi < (w - 1) && hi > 0 && flag[wi + 1][hi - 1] == 2) fcnt++;
		if (wi > 0 && hi < (h - 1) && flag[wi - 1][hi + 1] == 2) fcnt++;
		if (wi < (w - 1) && hi < (h - 1) && flag[wi + 1][hi + 1] == 2) fcnt++;
		if (fcnt == field[wi][hi]) {
			if (wi > 0 && flag[wi - 1][hi] == 0) press(evnt[wi - 1][hi], evt);
			if (hi > 0 && flag[wi][hi - 1] == 0) press(evnt[wi][hi - 1], evt);
			if (wi < (w - 1) && flag[wi + 1][hi] == 0) press(evnt[wi + 1][hi], evt);
			if (hi < (h - 1) && flag[wi][hi + 1] == 0) press(evnt[wi][hi + 1], evt);
			if (wi > 0 && hi > 0 && flag[wi - 1][hi - 1] == 0) press(evnt[wi - 1][hi - 1], evt);
			if (wi < (w - 1) && hi > 0 && flag[wi + 1][hi - 1] == 0) press(evnt[wi + 1][hi - 1], evt);
			if (wi > 0 && hi < (h - 1) && flag[wi - 1][hi + 1] == 0) press(evnt[wi - 1][hi + 1], evt);
			if (wi < (w - 1) && hi < (h - 1) && flag[wi + 1][hi + 1] == 0) press(evnt[wi + 1][hi + 1], evt);
		}
	}
	else if (evt->button == 3 && flag[wi][hi] == 0) {
		GtkWidget* img = gtk_container_get_children((GtkContainer*) wid)->data;
		if (usr) gtk_image_set_from_file((GtkImage*) img, "/usr/share/sweep/img/flag.bmp");
		else gtk_image_set_from_file((GtkImage*) img, "img/flag.bmp");
		flag[wi][hi] = 2;
		f--;
		int8_t s[4];
		sprintf(s, "%i", f);
		gtk_label_set_text((GtkLabel*) scr, s);
		if (field[wi][hi] == 9) m--;
		if (f == 0 && m == 0) vict();
	}
	else if (evt->button == 3 && flag[wi][hi] == 2) {
		GtkWidget* img = gtk_container_get_children((GtkContainer*) wid)->data;
		if (usr) gtk_image_set_from_file((GtkImage*) img, "/usr/share/sweep/img/tile.bmp");
		else gtk_image_set_from_file((GtkImage*) img, "img/tile.bmp");
		flag[wi][hi] = 0;
		f++;
		int8_t s[4];
		sprintf(s, "%i", f);
		gtk_label_set_text((GtkLabel*) scr, s);
		if (field[wi][hi] == 9) m++;
		if (f == 0 && m == 0) vict();
	}
}

void init_field(uint8_t x, uint8_t y, uint16_t n) {
	grid = gtk_grid_new();
	gtk_container_add((GtkContainer*) box, grid);
	w = x;
	h = y;
	m = n;
	f = m;
	field = malloc(sizeof(void*) * w);
	flag = malloc(sizeof(void*) * w);
	evnt = malloc(sizeof(void*) * w);
	for (uint8_t i0 = 0; i0 < w; i0++) {
		field[i0] = malloc(sizeof(uint8_t) * h);
		flag[i0] = malloc(sizeof(uint8_t) * h);
		evnt[i0] = malloc(sizeof(void*) * h);
		for (uint8_t i1 = 0; i1 < h; i1++) {
			field[i0][i1] = 0;
			flag[i0][i1] = 0;
			evnt[i0][i1] = gtk_event_box_new();
			GtkWidget* img;
			if (usr) img = gtk_image_new_from_file("/usr/share/sweep/img/tile.bmp");
			else img = gtk_image_new_from_file("img/tile.bmp");
			gtk_container_add((GtkContainer*) evnt[i0][i1], img);
			gtk_grid_attach((GtkGrid*) grid, evnt[i0][i1], i0, i1, 1, 1);
			g_signal_connect(evnt[i0][i1], "button-press-event", (GCallback) press, NULL);
		}
	}
	srand((uint64_t) malloc(1));
	for (uint16_t i = m; i > 0;) {
		uint8_t wi = rand();
		while (wi >= w) wi = rand();
		uint8_t hi = rand();
		while (hi >= h) hi = rand();
		if (field[wi][hi] != 9) {
			field[wi][hi] = 9;
			if (wi > 0 && field[wi - 1][hi] != 9) field[wi - 1][hi]++;
			if (hi > 0 && field[wi][hi - 1] != 9) field[wi][hi - 1]++;
			if (wi < (w - 1) && field[wi + 1][hi] != 9) field[wi + 1][hi]++;
			if (hi < (h - 1) && field[wi][hi + 1] != 9) field[wi][hi + 1]++;
			if (wi > 0 && hi > 0 && field[wi - 1][hi - 1] != 9) field[wi - 1][hi - 1]++;
			if (wi > 0 && hi < (h - 1) && field[wi - 1][hi + 1] != 9) field[wi - 1][hi + 1]++;
			if (wi < (w - 1) && hi > 0 && field[wi + 1][hi - 1] != 9) field[wi + 1][hi - 1]++;
			if (wi < (w - 1) && hi < (h - 1) && field[wi + 1][hi + 1] != 9) field[wi + 1][hi + 1]++;
			i--;
		}
	}
	run = 1;
	int8_t s[4];
	sprintf(s, "%u", m);
	gtk_label_set_text((GtkLabel*) scr, s);
	gtk_widget_show_all(win);
}

void clr_field() {
	for (uint8_t i = 0; i < w; i++) {
		free(field[i]);
		free(flag[i]);
		free(evnt[i]);
	}
	free(field);
	free(flag);
	free(evnt);
}

void new_field(GtkDialog* dia, int32_t resp, void* data) {
	if (resp == GTK_RESPONSE_DELETE_EVENT) return;
	GtkWidget* area = gtk_dialog_get_content_area((GtkDialog*) dia);
	GtkWidget* went = gtk_container_get_children((GtkContainer*) area)->data;
	GtkWidget* hent = gtk_container_get_children((GtkContainer*) area)->next->data;
	GtkWidget* ment = gtk_container_get_children((GtkContainer*) area)->next->next->data;
	GtkWidget* stat = gtk_container_get_children((GtkContainer*) area)->next->next->next->data;
	const int8_t* wstr = gtk_entry_get_text((GtkEntry*) went);
	const int8_t* hstr = gtk_entry_get_text((GtkEntry*) hent);
	const int8_t* mstr = gtk_entry_get_text((GtkEntry*) ment);
	int32_t wint = atoi(wstr);
	int32_t hint = atoi(hstr);
	int32_t mint = atoi(mstr);
	if (wint > 32 || wint < 1) {
		gtk_statusbar_push((GtkStatusbar*) stat, gtk_statusbar_get_context_id((GtkStatusbar*) stat, "width"), "width must be between 1 and 32");
		return;
	}
	if (hint > 32 || hint < 1) {
		gtk_statusbar_push((GtkStatusbar*) stat, gtk_statusbar_get_context_id((GtkStatusbar*) stat, "height"), "height must be between 1 and 32");
		return;
	}
	if (mint > wint * hint || mint < 1) {
		gtk_statusbar_push((GtkStatusbar*) stat, gtk_statusbar_get_context_id((GtkStatusbar*) stat, "height"), "mines must be between 1 and maximum area");
		return;
	}
	clr_field();
	gtk_container_remove((GtkContainer*) box, grid);
	init_field(wint, hint, mint);
	gtk_window_close((GtkWindow*) dia);
}

void new_game() {
	GtkWidget* dia = gtk_dialog_new();
	gtk_dialog_add_button((GtkDialog*) dia, "create", GTK_RESPONSE_ACCEPT);
	gtk_window_set_title((GtkWindow*) dia, "new field");
	GtkWidget* went = gtk_entry_new();
	GtkWidget* hent = gtk_entry_new();
	GtkWidget* ment = gtk_entry_new();
	GtkWidget* stat = gtk_statusbar_new();
	GtkWidget* area = gtk_dialog_get_content_area((GtkDialog*) dia);
	gtk_container_add((GtkContainer*) area, went);
	gtk_container_add((GtkContainer*) area, hent);
	gtk_container_add((GtkContainer*) area, ment);
	gtk_container_add((GtkContainer*) area, stat);
	gtk_entry_set_placeholder_text((GtkEntry*) went, "width");
	gtk_entry_set_placeholder_text((GtkEntry*) hent, "height");
	gtk_entry_set_placeholder_text((GtkEntry*) ment, "mines");
	g_signal_connect(dia, "response", (GCallback) new_field, NULL);
	gtk_widget_show_all(dia);
}

void keycb(GtkWidget* wid, GdkEventKey* key) {
	if (key->keyval == GDK_KEY_Escape) new_game();
}

int16_t main() {
	gtk_init(0, NULL);
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	if (fopen("/usr/share/sweep/", "r") != NULL) usr = 1;
	else gtk_window_set_default_icon_from_file("img/mine.bmp", NULL);
	gtk_window_set_title((GtkWindow*) win, "sweep");
	gtk_window_set_resizable((GtkWindow*) win, 0);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add((GtkContainer*) win, box);
	scr = gtk_label_new(NULL);
	gtk_container_add((GtkContainer*) box, scr);
	init_field(12, 16, 50);
	g_signal_connect(win, "key-press-event", (GCallback) keycb, NULL);
	g_signal_connect(win, "destroy", gtk_main_quit, NULL);
	gtk_main();
	clr_field();
	return 0;
}
