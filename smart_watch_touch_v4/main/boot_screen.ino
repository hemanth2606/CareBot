// splash screen 
void loadingScreen()
{
    static lv_style_t style_bg;
    static lv_style_t style_indic;
    lv_style_init(&style_bg);
    lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_border_width(&style_bg, 2);
    lv_style_set_pad_all(&style_bg, 6); /*To make the indicator smaller*/
    lv_style_set_radius(&style_bg, 6);
    lv_style_set_anim_time(&style_bg, 2000);

    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));    
    lv_style_set_radius(&style_indic, 3);

    static lv_style_t style_splash_text;
    lv_style_init(&style_splash_text);
    lv_style_set_text_font(&style_splash_text, &lv_font_montserrat_44); // Use a builtin font, Montserrat size 26
    lv_style_set_text_opa(&style_splash_text,LV_OPA_COVER); // Set opacity to 100%

    lv_obj_t * splash_text = lv_label_create(lv_scr_act());
    lv_obj_add_style(splash_text, &style_splash_text, 0);
    lv_label_set_text(splash_text, "CareBot");
    lv_obj_align(splash_text,LV_ALIGN_CENTER,0,0);

    lv_obj_t * boot_bar = lv_bar_create(lv_scr_act());
    lv_obj_remove_style_all(boot_bar);  /*To have a clean start*/
    lv_obj_add_style(boot_bar, &style_bg, 0);
    lv_obj_add_style(boot_bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(boot_bar, 200, 20);
    lv_obj_align(boot_bar,LV_ALIGN_CENTER,0,80);
    lv_bar_set_value(boot_bar, 100, LV_ANIM_ON);
}
void move_to_home_screen()
{
    tv = lv_tileview_create(NULL);
    lv_obj_remove_style(tv, NULL, LV_PART_SCROLLBAR | LV_STATE_ANY);

    home_screen = lv_tileview_add_tile(tv, 0, 0,LV_DIR_BOTTOM | LV_DIR_RIGHT);

    app_screen = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP);

    activity_screen = lv_tileview_add_tile(tv, 1, 0, LV_DIR_LEFT);
    
    lv_scr_load_anim(tv,LV_SCR_LOAD_ANIM_OUT_LEFT, 500, 2500, true);
    
    setStyle();
    makeKeyboard();
    buildStatusBar();
    buildPWMsgBox();
    buildBody();
    buildSettings();
    tryPreviousNetwork();
    app_icon_create();
}