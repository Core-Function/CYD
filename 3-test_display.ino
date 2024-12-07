#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// แสดงบันทึกการทำงานของไลบรารี
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

void lv_create_main_gui(void) {
  // สร้างป้ายกำกับข้อความเพื่อจัดตำแหน่งให้อยู่กึ่งกลาง
  lv_obj_t * text_label = lv_label_create(lv_screen_active());
  lv_label_set_text(text_label, "Hello, world!");
  lv_obj_align(text_label, LV_ALIGN_CENTER, 0, 0);

  // กำหนดชนิดและขนาดของฟอนต์
  static lv_style_t style_text_label;
  lv_style_init(&style_text_label);
  lv_style_set_text_font(&style_text_label, &lv_font_montserrat_18);
  lv_obj_add_style(text_label, &style_text_label, 0);
}

void setup() {
  Serial.begin(9600);
  Serial.printf("Start...");

  // LVGL เริ่มทำงาน
  lv_init();

  // เปิดฟังก์ชันการแสดงข้อมูลสำหรับหาข้อผิดพลาดของโปรแกรม
  //lv_log_register_print_cb(log_print);
  
  // สร้างการแสดงผล
  lv_display_t * disp;
  
  // เริ่มต้นการแสดงผลบนจอ TFT โดยใช้ไลบรารี TFT_eSPI
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
  
  // สร้างองค์ประกอบ GUI บนจอภาพ
  lv_create_main_gui();
}

void loop() {
  lv_task_handler(); // ให้ GUI ทำงาน
  lv_tick_inc(5);    // กำหนดคาบเวลาทำงานให้กับ LVGL
  delay(5);
}
