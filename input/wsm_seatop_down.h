/*
MIT License

Copyright (c) 2024 YaoBing Xiao

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef WSM_SEATOP_DOWN_H
#define WSM_SEATOP_DOWN_H

struct wlr_surface;
struct wlr_touch_down_event;

struct wsm_seat;
struct wsm_container;

void seatop_begin_down(struct wsm_seat *seat, struct wsm_container *con,
					   double sx, double sy);

void seatop_begin_down_on_surface(struct wsm_seat *seat,
								  struct wlr_surface *surface, double sx, double sy);

void seatop_begin_touch_down(struct wsm_seat *seat, struct wlr_surface *surface,
							 struct wlr_touch_down_event *event, double sx, double sy, double lx, double ly);

#endif
