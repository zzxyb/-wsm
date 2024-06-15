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

#ifndef WSM_SCENE_H
#define WSM_SCENE_H

#include "../config.h"

struct wlr_scene;
struct wlr_scene_tree;
struct wlr_scene_output_layout;

struct wsm_server;

/**
 * @brief scene render control.
 *
 * @details The order in which the scene-trees below are created determines the
 * z-order for nodes which cover the whole work-area.  For per-output scene-trees.
 *
 * | Type              | isWindow          | Scene Tree       | Per Output | Example
 * | ----------------- | ----------------- | ---------------- | ---------- | -------------------------------
 * | server-node       | No(display node)  | black-screen     | Yes        | black screen transition
 * | server-node       | No(display node)  | screen-water-mark| Yes        | show employee number information
 * | layer-shell       | No(display node)  | osd_overlay_layer| No         | screenshot preview window
 * | xdg-popups        | Yes               | xdg-popups(layer)| Yes        | server decides layer surface popup(wlr_xdg_popup)
 * | layer-shell       | Yes               | notify-osd       | Yes        | notify bubble or osd
 * | layer-shell       | Yes               | overlay-layer    | Yes        | lock-screen
 * | xdg-popups        | Yes               | xdg-popups       | No         | server decides(wlr_xdg_popup)
 * | xwayland-OR       | Yes               | unmanaged        | No         | like Qt::X11BypassWindowManagerHint,override_redirect appear above
 * | layer-shell       | Yes               | top-layer        | Yes        | launcher、dock、fullscreen window
 * | toplevels windows | Yes               | always-on-top    | No         | X or Wayland.like Qt::WindowStaysOnTopHint
 * | toplevels windows | Yes               | normal           | No         | X or Wayland.normal window
 * | toplevels windows | Yes               | always-on-bottom | No         | X or Waylandlike Qt::WindowStaysOnBottomHint
 * | layer-shell       | Yes               | bottom-layer     | Yes        | placeholder for custom desktop widget
 * | layer-shell       | Yes               | background-layer | Yes        | desktop
 *
 */
struct wsm_scene {
    struct wlr_scene *wlr_scene;
    struct wlr_scene_tree *view_tree_always_on_bottom;
    struct wlr_scene_tree *view_tree;
    struct wlr_scene_tree *view_tree_always_on_top;
    struct wlr_scene_tree *xdg_popup_tree;
#ifdef HAVE_XWAYLAND
    struct wlr_scene_tree *unmanaged_tree;
#endif
    struct wlr_scene_tree *osd_overlay_layers_tree;
    struct wlr_scene_output_layout *wlr_scene_output_layout;
};

struct wsm_scene *wsm_scene_create(const struct wsm_server* server);

#endif
