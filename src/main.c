#include <pebble.h>

Window *window;
TextLayer *text_layer;


/* Buttons Handlers */
void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Button Up !"); 
}
 
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Button Down !"); 
}
 
void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Button Select !"); 
}
void click_config_provider(void *context)
{
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}
void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "El Bruno, buttons sample!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

  // buttons handlers
  window_set_click_config_provider(window, click_config_provider);
  
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
