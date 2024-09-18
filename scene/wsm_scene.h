#ifndef WSM_SCENE_H
#define WSM_SCENE_H

#include "../config.h"
#include "node/wsm_node.h"

#include <stdbool.h>

struct wlr_scene;
struct wlr_scene_tree;
struct wlr_scene_output;
struct wlr_output_state;
struct wlr_output_layout;
struct wlr_scene_output_layout;
struct wlr_scene_output_state_options;

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
 * | server-node       | No(display node)  | drag display node| No         | show drag icon
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
	struct {
		struct wlr_scene_tree *shell_background;
		struct wlr_scene_tree *shell_bottom;
		struct wlr_scene_tree *tiling;
		struct wlr_scene_tree *floating;
		struct wlr_scene_tree *shell_top;
		struct wlr_scene_tree *fullscreen;
		struct wlr_scene_tree *fullscreen_global;
#ifdef HAVE_XWAYLAND
		struct wlr_scene_tree *unmanaged;
#endif
		struct wlr_scene_tree *shell_overlay;
		struct wlr_scene_tree *popup;
		struct wlr_scene_tree *seat;
		struct wlr_scene_tree *session_lock;
	} layers;

	struct wsm_node node;

	struct {
		struct wl_signal new_node;
	} events;

	struct wl_list all_outputs;

	struct wlr_output_layout *output_layout;

	struct wlr_scene *root_scene;
	struct wlr_scene_tree *staging;

	struct wlr_scene_tree *layer_tree;

	struct wsm_list *outputs;
	struct wsm_list *non_desktop_outputs;
	struct wsm_list *scratchpad;

	struct wsm_output *fallback_output;
	struct wsm_container *fullscreen_global;

	double x, y;
	double width, height;
};

struct wsm_scene *wsm_scene_create(const struct wsm_server* server);
bool wsm_scene_output_commit(struct wlr_scene_output *scene_output,
	const struct wlr_scene_output_state_options *options);
bool wsm_scene_output_build_state(struct wlr_scene_output *scene_output,
	struct wlr_output_state *state, const struct wlr_scene_output_state_options *options);
void root_get_box(struct wsm_scene *root, struct wlr_box *box);
void root_scratchpad_show(struct wsm_container *con);

#endif
