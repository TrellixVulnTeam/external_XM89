// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.chromium.content;

/**
 * Provide Android internal resources to Chrome's content layer.  This allows
 * classes that access resources via org.chromium.content.R to function properly
 * in webview.  In a normal Chrome build, content resources live in a res folder
 * in the content layer and the org.chromium.content.R class is generated at
 * build time based on these resources.  In webview, resources live in the
 * Android framework and can't be accessed directly from the content layer.
 * Instead, we copy resources needed by content into the Android framework and
 * use this R class to map resources IDs from org.chromium.content.R to
 * com.android.internal.R.
 */
public final class R {
    public static final class attr {
        public static int select_dialog_multichoice;
        public static int select_dialog_singlechoice;
    }
    public static final class dimen {
        public static int link_preview_overlay_radius;
    }
    public static final class drawable {
        public static int ondemand_overlay;
    }
    public static final class id {
        public static int date_picker;
        public static int position_in_year;
        public static int pickers;
        public static int select_action_menu_select_all;
        public static int select_action_menu_cut;
        public static int select_action_menu_copy;
        public static int select_action_menu_paste;
        public static int select_action_menu_share;
        public static int select_action_menu_web_search;
        public static int time_picker;
        public static int year;
    }
    public static final class layout {
        public static int date_time_picker_dialog;
        public static int two_field_date_picker;
    }
    public static final class menu {
        public static int select_action_menu;
    }
    public static final class string {
        public static int accessibility_content_view;
        public static int accessibility_date_picker_month;
        public static int accessibility_date_picker_week;
        public static int accessibility_date_picker_year;
        public static int accessibility_datetime_picker_date;
        public static int accessibility_datetime_picker_time;
        public static int actionbar_share;
        public static int actionbar_web_search;
        public static int date_picker_dialog_clear;
        public static int date_picker_dialog_set;
        public static int date_picker_dialog_title;
        public static int date_time_picker_dialog_title;
        public static int media_player_error_button;
        public static int media_player_error_text_invalid_progressive_playback;
        public static int media_player_error_text_unknown;
        public static int media_player_error_title;
        public static int media_player_loading_video;
        public static int month_picker_dialog_title;
        public static int week_picker_dialog_title;
        public static int media_info_audio_not_supported;
        public static int media_info_video_not_supported;
        public static int save_password_label;
        public static int save_password_message;
        public static int save_password_notnow;
        public static int save_password_remember;
        public static int save_password_never;
    }
    public static final class style {
        public static int ContentActionBar;
        public static int SelectPopupDialog;
    }
}
