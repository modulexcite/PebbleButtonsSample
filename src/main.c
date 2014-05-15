#include <pebble.h>

Window *window;
GBitmap *nino_bitmap;
BitmapLayer *nino_layer;
int imageYLocation;
int difY;

void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    //Free the memoery used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
}
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay)
{
    //Declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);
 
    //Set characteristics
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
 
    //Set stopped handler to free memory
    AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
 
    //Start animation!
    animation_schedule((Animation*) anim);
}

/* Buttons Handlers */
void up_click_handler(ClickRecognizerRef recognizer, void *context)
{
  difY = imageYLocation - 10;
  if(difY >= 0)
  {
    GRect start = GRect(60, imageYLocation, 48, 48);
    GRect finish = GRect(60, difY, 48, 48);
    animate_layer(bitmap_layer_get_layer(nino_layer), &start, &finish, 300, 500);
    imageYLocation = difY;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Button Up ! Y: " + imageYLocation); 
  }
}
 
void down_click_handler(ClickRecognizerRef recognizer, void *context)
{
  int difY = imageYLocation + 10;
  if(difY <= 120)
  {
    GRect start = GRect(60, imageYLocation, 48, 48);
    GRect finish = GRect(60, difY, 48, 48);
    animate_layer(bitmap_layer_get_layer(nino_layer), &start, &finish, 300, 500);
    imageYLocation = difY;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Button Down ! Y: " + imageYLocation); 
  }
}
 
void select_click_handler(ClickRecognizerRef recognizer, void *context)
{
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Button Select !"); 
  vibes_double_pulse();
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
	
  //Load bitmaps into GBitmap structures
  //The ID you chose when uploading is prefixed with 'RESOURCE_ID_'
  nino_bitmap = gbitmap_create_with_resource(RESOURCE_ID_FOOTBALL);
   
  //Create BitmapLayers to show GBitmaps and add to Window
  nino_layer = bitmap_layer_create(GRect(60, 60, 48, 48));
  bitmap_layer_set_bitmap(nino_layer, nino_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(nino_layer));
  imageYLocation = 60;
  
  // buttons handlers
  window_set_click_config_provider(window, click_config_provider);
  
	// Push the window
	window_stack_push(window, true);
}

void handle_deinit(void) {
	
  //Destroy GBitmaps and BitmapLayers
  gbitmap_destroy(nino_bitmap);
  bitmap_layer_destroy(nino_layer);
    
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}