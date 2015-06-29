#include <pebble.h>

#define KEY_CONDITIONS 0
#define KEY_TEMPERATURE 1
#define KEY_FORECASTC 2
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_day_layer;
static TextLayer *s_connection_layer, *s_ampm_layer, *s_weather_layer, *s_temp_layer, *s_forecast_layer;
static GFont s_time_font;
static Layer *batt_layer;
static GBitmap        *bluetooth_image;
static BitmapLayer *s_bt_layer;



// Previous bluetooth connection status
static bool prev_bt_status = false;

/*static void handle_bluetooth(bool connected) {
  text_layer_set_text(s_bt_layer, connected ? "connected" : "disconnected");
}*/
/*
  Handle bluetooth events
*/
void handle_bluetooth( bool connected ) {
  
  if ( bluetooth_image != NULL ) {
    gbitmap_destroy( bluetooth_image );
  }
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  
  int hour = tick_time->tm_hour;
	
  if ( connected ) {
    bluetooth_image = gbitmap_create_with_resource( (hour >= 18 && hour <= 3) ? RESOURCE_ID_IMAGE_BLUETOOTH : RESOURCE_ID_IMAGE_BLUETOOTH_I);
  } else {
    bluetooth_image = gbitmap_create_with_resource( (hour >= 18 && hour <= 3) ? RESOURCE_ID_IMAGE_NO_BLUETOOTH : RESOURCE_ID_IMAGE_NO_BLUETOOTH_I);
 vibes_short_pulse();
  }

  prev_bt_status = connected;

  bitmap_layer_set_bitmap( s_bt_layer, bluetooth_image );
}

static void update_time() {
  APP_LOG(APP_LOG_LEVEL_INFO, "Update time registered!");
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  
  int hour = tick_time->tm_hour;
  if(hour >= 21) {
    text_layer_set_text(s_ampm_layer," ");
	  text_layer_set_text(s_day_layer, "night");
	  window_set_background_color(s_main_window, GColorBlack);
	  text_layer_set_text_color(s_day_layer, GColorWhite);
    text_layer_set_text_color(s_ampm_layer, GColorWhite);
	  text_layer_set_text_color(s_time_layer, GColorWhite);
	  text_layer_set_text_color(s_connection_layer, GColorWhite);
		text_layer_set_text_color(s_temp_layer, GColorWhite);
		text_layer_set_text_color(s_weather_layer, GColorWhite);
//    text_layer_set_text_color(s_bt_layer, GColorWhite);
    text_layer_set_text_color(s_forecast_layer, GColorWhite);
  } else if(hour >= 18) {
    text_layer_set_text(s_ampm_layer," ");
	  text_layer_set_text(s_day_layer, "evening");
	  window_set_background_color(s_main_window, GColorBlack);
	  text_layer_set_text_color(s_day_layer, GColorWhite);
    text_layer_set_text_color(s_ampm_layer, GColorWhite);
	  text_layer_set_text_color(s_time_layer, GColorWhite);
	  text_layer_set_text_color(s_connection_layer, GColorWhite);
		text_layer_set_text_color(s_temp_layer, GColorWhite);
		text_layer_set_text_color(s_weather_layer, GColorWhite);
//    text_layer_set_text_color(s_bt_layer, GColorWhite);
    text_layer_set_text_color(s_forecast_layer, GColorWhite);
  } else if(hour >= 15) {
    text_layer_set_text(s_ampm_layer,"late");
	  text_layer_set_text(s_day_layer, "afternoon");
	  window_set_background_color(s_main_window, GColorWhite);
	  text_layer_set_text_color(s_day_layer, GColorBlack);
    text_layer_set_text_color(s_ampm_layer, GColorBlack);
	  text_layer_set_text_color(s_time_layer, GColorBlack);
	  text_layer_set_text_color(s_connection_layer, GColorBlack);
		text_layer_set_text_color(s_temp_layer, GColorBlack);
		text_layer_set_text_color(s_weather_layer, GColorBlack);
//    text_layer_set_text_color(s_bt_layer, GColorBlack);
    text_layer_set_text_color(s_forecast_layer, GColorBlack);
  } else if(hour >= 12) {
    text_layer_set_text(s_ampm_layer," ");
	  text_layer_set_text(s_day_layer, "afternoon");
	  window_set_background_color(s_main_window, GColorWhite);
	  text_layer_set_text_color(s_day_layer, GColorBlack);
    text_layer_set_text_color(s_ampm_layer, GColorBlack);
	  text_layer_set_text_color(s_time_layer, GColorBlack);
	  text_layer_set_text_color(s_connection_layer, GColorBlack);
		text_layer_set_text_color(s_temp_layer, GColorBlack);
		text_layer_set_text_color(s_weather_layer, GColorBlack);
//    text_layer_set_text_color(s_bt_layer, GColorBlack);
    text_layer_set_text_color(s_forecast_layer, GColorBlack);
  } else if(hour >= 9) {
    text_layer_set_text(s_ampm_layer,"late");
	  text_layer_set_text(s_day_layer, "morning");
	  window_set_background_color(s_main_window, GColorWhite);
	  text_layer_set_text_color(s_day_layer, GColorBlack);
    text_layer_set_text_color(s_ampm_layer, GColorBlack);
	  text_layer_set_text_color(s_time_layer, GColorBlack);
	  text_layer_set_text_color(s_connection_layer, GColorBlack);
		text_layer_set_text_color(s_temp_layer, GColorBlack);
		text_layer_set_text_color(s_weather_layer, GColorBlack);
//    text_layer_set_text_color(s_bt_layer, GColorBlack);
    text_layer_set_text_color(s_forecast_layer, GColorBlack);
  } else if(hour >= 6) {
    text_layer_set_text(s_ampm_layer," ");
	  text_layer_set_text(s_day_layer, "morning");
	  window_set_background_color(s_main_window, GColorWhite);
	  text_layer_set_text_color(s_day_layer, GColorBlack);
    text_layer_set_text_color(s_ampm_layer, GColorBlack);
	  text_layer_set_text_color(s_time_layer, GColorBlack);
	  text_layer_set_text_color(s_connection_layer, GColorBlack);
		text_layer_set_text_color(s_temp_layer, GColorBlack);
		text_layer_set_text_color(s_weather_layer, GColorBlack);
//    text_layer_set_text_color(s_bt_layer, GColorBlack);
    text_layer_set_text_color(s_forecast_layer, GColorBlack);
  } else if(hour >= 3) {
    text_layer_set_text(s_ampm_layer,"early");
	  text_layer_set_text(s_day_layer, "morning");
	  window_set_background_color(s_main_window, GColorBlack);
	  text_layer_set_text_color(s_day_layer, GColorWhite);
    text_layer_set_text_color(s_ampm_layer, GColorWhite);
	  text_layer_set_text_color(s_time_layer, GColorWhite);
	  text_layer_set_text_color(s_connection_layer, GColorWhite);
		text_layer_set_text_color(s_temp_layer, GColorWhite);
		text_layer_set_text_color(s_weather_layer, GColorWhite);
//    text_layer_set_text_color(s_bt_layer, GColorWhite);
    text_layer_set_text_color(s_forecast_layer, GColorWhite);
  } else if(hour >= 0) {
    text_layer_set_text(s_ampm_layer," ");
	  text_layer_set_text(s_day_layer, "midnight");
	  window_set_background_color(s_main_window, GColorBlack);
	  text_layer_set_text_color(s_day_layer, GColorWhite);
    text_layer_set_text_color(s_ampm_layer, GColorWhite);
	  text_layer_set_text_color(s_time_layer, GColorWhite);
	  text_layer_set_text_color(s_connection_layer, GColorWhite);
		text_layer_set_text_color(s_temp_layer, GColorWhite);
		text_layer_set_text_color(s_weather_layer, GColorWhite);
//    text_layer_set_text_color(s_bt_layer, GColorWhite);
    text_layer_set_text_color(s_forecast_layer, GColorWhite);
  } else {
    text_layer_set_text(s_ampm_layer,"error");
	  text_layer_set_text(s_day_layer, "error");
	  window_set_background_color(s_main_window, GColorWhite);
	  text_layer_set_text_color(s_day_layer, GColorBlack);
    text_layer_set_text_color(s_ampm_layer, GColorBlack);
	  text_layer_set_text_color(s_time_layer, GColorBlack);
	  text_layer_set_text_color(s_connection_layer, GColorBlack);
		text_layer_set_text_color(s_temp_layer, GColorBlack);
		text_layer_set_text_color(s_weather_layer, GColorBlack);
//    text_layer_set_text_color(s_bt_layer, GColorBlack);
    text_layer_set_text_color(s_forecast_layer, GColorBlack);
  }

  static char date_buffer[] = "WWWWWWWWW";

  strftime(date_buffer, sizeof("WWWWWWWWW"), "%A", tick_time);

if(strcmp(date_buffer, "Monday") == 0) {
	text_layer_set_text(s_connection_layer, "Monday");
} else if(strcmp(date_buffer, "Tuesday") == 0) {
	text_layer_set_text(s_connection_layer, "Tuesday");
} else if(strcmp(date_buffer, "Wednesday") == 0) {
	text_layer_set_text(s_connection_layer, "Wednesday");
} else if(strcmp(date_buffer, "Thursday") == 0) {
	text_layer_set_text(s_connection_layer, "Thursday");
} else if(strcmp(date_buffer, "Friday") == 0) {
	text_layer_set_text(s_connection_layer, "Friday");
} else if(strcmp(date_buffer, "Saturday") == 0) {
	text_layer_set_text(s_connection_layer, "Saturday");
} else if(strcmp(date_buffer, "Sunday") == 0) {
	text_layer_set_text(s_connection_layer, "Sunday");
} else {
	text_layer_set_text(s_connection_layer, date_buffer);
}
}

static void batt_layer_draw(Layer *layer, GContext *ctx) {
	time_t temp = time(NULL);
 	struct tm *tick_time = localtime(&temp);
  
 	int hour = tick_time->tm_hour;

 	BatteryChargeState state = battery_state_service_peek();
 	int pct = state.charge_percent;
	int w = 4; // width of battery bar

	if(hour >= 21) { // black, black
		graphics_context_set_fill_color(ctx, GColorWhite); // foreground colour (remaining, lighter than bg)
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorBlack); // background colour (expended, darker than bg)
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 18) { // oxford blue, black
		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 15) { // sunset orange, white
		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 12) { // vivid cerulean, white
		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 9) { // vivid cerulean, white
		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 6) { // vivid cerulean, white
		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 3) { // very light blue, black
		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else if(hour >= 0) { // black, black
		graphics_context_set_fill_color(ctx, GColorWhite);
 		graphics_fill_rect(ctx, GRect(0,0,w,168), 0, GCornerNone);
 		graphics_context_set_fill_color(ctx, GColorBlack);
 		graphics_fill_rect(ctx, GRect(0,0,w,(16.8*(100-pct)/10)), 0, GCornerNone);
  } else {
	  
  }
}

void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    //Free the memory used by the Animation
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

static void handle_second_tick(struct tm* tick_time, TimeUnits units_changed) {
  // Needs to be static because it's used by the system later.
  static char s_time_text[] = "00:00";

  strftime(s_time_text, sizeof(s_time_text), "%T", tick_time);
  text_layer_set_text(s_time_layer, s_time_text);
  

}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) 
{
  update_time();
}

static void tap_handler(AccelAxisType axis, int32_t direction) {
	APP_LOG(APP_LOG_LEVEL_INFO, "Tap/flick registered!");
	
 time_t now = time(NULL);
 struct tm *current_time = localtime(&now);
 handle_second_tick(current_time, MINUTE_UNIT);

  //tick_timer_service_subscribe(MINUTE_UNIT, handle_second_tick);
	// Battery bar moves in from the left
	GRect startbatt = GRect(-5,0,144,168);
	GRect finishbatt = GRect(0,0,144,168);
	animate_layer(batt_layer, &startbatt, &finishbatt, 1000, 0);
	
	GRect startbatt2 = GRect(0,0,144,168);
	GRect finishbatt2 = GRect(-5,0,144,168);
	animate_layer(batt_layer, &startbatt2, &finishbatt2, 1000, 7000);
  // Current temp moves in from the right
	GRect start = GRect(288,0,141,168);
	GRect finish = GRect(0,0,141,168);
	animate_layer(text_layer_get_layer(s_temp_layer), &start, &finish, 1000, 0);
	
	GRect start3 = GRect(0,0,141,168);
	GRect finish3 = GRect(288,0,141,168);
	animate_layer(text_layer_get_layer(s_temp_layer), &start3, &finish3, 1000, 7000);
	// Current time moves in from the right
  GRect start8 = GRect(288, 60, 141, 34);
  GRect finish8 = GRect(0, 60, 141, 34);
  animate_layer(text_layer_get_layer(s_time_layer), &start8, &finish8,1000,0);
  
  GRect start9 = GRect(0, 60, 141, 34);
  GRect finish9 = GRect(288, 60, 141, 34);
  animate_layer(text_layer_get_layer(s_time_layer), &start9, &finish9,1000,7000); 
  
	// Current weather moves in from right
	GRect start2 = GRect(288,15,141,168);
	GRect finish2 = GRect(0,15,141,168);
	animate_layer(text_layer_get_layer(s_weather_layer), &start2, &finish2, 1000, 0);
	
	GRect start1 = GRect(0,15,141,168);
	GRect finish1 = GRect(288,15,141,168);
	animate_layer(text_layer_get_layer(s_weather_layer), &start1, &finish1, 1000, 7000);
  
  //Forecast move in from right
  GRect start6 = GRect(288,30,141,168);
  GRect finish6 = GRect(0,30,141,168);
  animate_layer(text_layer_get_layer(s_forecast_layer), &start6, &finish6, 1000, 0);
  
  GRect start7 = GRect(0,30,141,168);
  GRect finish7 = GRect(288,30,141,168);
  animate_layer(text_layer_get_layer(s_forecast_layer), &start7, &finish7, 1000, 7000);
}



static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
	static char temperature_buffer[25];
	static char conditions_buffer[100];
  static char forecast_buffer[100];
	
	// Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
		// Which key was received?
    switch(t->key) {
		case KEY_TEMPERATURE: 
    
      if ((int)t->value->int32 > 20 && (int)t->value->int32 < 27) {
        snprintf(temperature_buffer, sizeof(temperature_buffer), "It's pretty warm");
      } else if ((int)t->value->int32 >= 27 && (int)t->value->int32 < 30) {
        snprintf(temperature_buffer, sizeof(temperature_buffer), "It's HOT!");
      } else if ((int)t->value->int32 >= 30) {
        snprintf(temperature_buffer, sizeof(temperature_buffer), "It's really HOT !");
      } else if ((int)t->value->int32 <= 20 && (int)t->value->int32 > 14) {
        snprintf(temperature_buffer, sizeof(temperature_buffer), "Feels mildly warm...");
      } else if ((int)t->value->int32 <= 14 && (int)t->value->int32 > 4) {
        snprintf(temperature_buffer, sizeof(temperature_buffer), "It's cold.");
      } else if ((int)t->value->int32 <= 4 && (int)t->value->int32 > 0) {
        snprintf(temperature_buffer, sizeof(temperature_buffer), "It's really cold !");
      } else if ((int)t->value->int32 <= 0) {  
        snprintf(temperature_buffer, sizeof(temperature_buffer), "It's freezing!");
      } else {
			snprintf(temperature_buffer, sizeof(temperature_buffer), "Feels like %d.", (int)t->value->int32);
      }  
      break;
		case KEY_CONDITIONS:
 		 	snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
 		break;
    case KEY_FORECASTC:
      snprintf(forecast_buffer, sizeof(forecast_buffer), "Next: %s", t->value->cstring);
    break;
		default:
 		 APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
 		 break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
	// Set text for conditions
	text_layer_set_text(s_weather_layer, conditions_buffer);
  // Set text for forecast
  text_layer_set_text(s_forecast_layer, forecast_buffer);
	// Set text for temperature
		text_layer_set_text(s_temp_layer, temperature_buffer);
} 

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
	text_layer_set_text(s_weather_layer, "Update Failed");
  text_layer_set_text(s_forecast_layer, "Update Failed");
	text_layer_set_text(s_temp_layer, "Update Failed");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
	text_layer_set_text(s_weather_layer, "Update Failed"); // No BT, Internet
  text_layer_set_text(s_forecast_layer, "Update Failed");
	text_layer_set_text(s_temp_layer, "Update Failed");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) { // updates weather
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_32));
  bluetooth_connection_service_subscribe(handle_bluetooth);

  
  batt_layer = layer_create(GRect(-5, 0, 144, 168));
	layer_add_child(window_get_root_layer(window), batt_layer);
	layer_set_update_proc(batt_layer, batt_layer_draw);
  
  s_time_layer = text_layer_create(GRect(0, 60, bounds.size.w, 34));
  text_layer_set_text_color(s_time_layer, GColorWhite);
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentRight);

  s_ampm_layer = text_layer_create(GRect(0, 100, bounds.size.w, 168));
	text_layer_set_background_color(s_ampm_layer, GColorClear);
	text_layer_set_font(s_ampm_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_25)));
	text_layer_set_text_alignment(s_ampm_layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_ampm_layer));
  
  s_connection_layer = text_layer_create(GRect(0, 116, bounds.size.w, 34));
  text_layer_set_text_color(s_connection_layer, GColorWhite);
  text_layer_set_background_color(s_connection_layer, GColorClear);
  text_layer_set_font(s_connection_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_22)));
  text_layer_set_text_alignment(s_connection_layer, GTextAlignmentRight);
  
  //s_bt_layer = text_layer_create(GRect(0, 85, bounds.size.w, 34));
  GRect BT_RECT        = GRect( 124,  93,  17,  20 );
  s_bt_layer = bitmap_layer_create(BT_RECT);
//  text_layer_set_text_color(s_bt_layer, GColorWhite);
//  text_layer_set_background_color(s_bt_layer, GColorClear);
//  text_layer_set_font(s_bt_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_22)));
//  text_layer_set_text_alignment(s_bt_layer, GTextAlignmentRight);
  handle_bluetooth(bluetooth_connection_service_peek());
  
  s_day_layer = text_layer_create(GRect(0, 132, bounds.size.w, 34));
  text_layer_set_text_color(s_day_layer, GColorWhite);
  text_layer_set_background_color(s_day_layer, GColorClear);
  text_layer_set_font(s_day_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_25)));
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentRight);
  text_layer_set_text(s_day_layer, "100% charged");
  
  s_temp_layer = text_layer_create(GRect(288, 0, 141, 168));
	text_layer_set_background_color(s_temp_layer, GColorClear);
	text_layer_set_font(s_temp_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_14)));
	text_layer_set_text_alignment(s_temp_layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_temp_layer));
	text_layer_set_text(s_temp_layer, "Updating");
	
	s_weather_layer = text_layer_create(GRect(288, 15, 141, 168));
	text_layer_set_background_color(s_weather_layer, GColorClear);
	text_layer_set_font(s_weather_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_14)));
	text_layer_set_text_alignment(s_weather_layer, GTextAlignmentRight);
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_layer));
	text_layer_set_text(s_weather_layer, "Weather");
  
  //Forecast layer
  s_forecast_layer = text_layer_create(GRect(288,30,141,168));
  text_layer_set_background_color(s_forecast_layer, GColorClear);
  text_layer_set_font(s_forecast_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CYNTHE_14)));
  text_layer_set_text_alignment(s_forecast_layer, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_forecast_layer));
  text_layer_set_text(s_forecast_layer, "Updating Forecast");

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  //time_t now = time(NULL);
  //struct tm *current_time = localtime(&now);
  //handle_second_tick(current_time, MINUTE_UNIT);

  //tick_timer_service_subscribe(MINUTE_UNIT, handle_second_tick);

  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_connection_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_day_layer));
  layer_add_child(window_layer, bitmap_layer_get_layer(s_bt_layer));
  //update_time();
}

static void main_window_unload(Window *window) {
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_connection_layer);
  text_layer_destroy(s_day_layer);
  text_layer_destroy(s_forecast_layer);
  text_layer_destroy(s_temp_layer);
  text_layer_destroy(s_weather_layer);
  bitmap_layer_destroy(s_bt_layer);
}

static void init() {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, true);
  accel_tap_service_subscribe(tap_handler);
  	// Register callbacks
	app_message_register_inbox_received(inbox_received_callback);
	// Open AppMessage
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
  update_time();
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}

