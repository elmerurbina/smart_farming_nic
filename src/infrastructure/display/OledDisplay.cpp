#include "OledDisplay.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

OledDisplay::OledDisplay()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

void OledDisplay::begin() {

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (true);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    for (int i = 0; i < 128; i++) {
        graph[i] = 0;
    }

    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("Iniciando");
    display.display();

    delay(2000);
}

void OledDisplay::render(MoistureData data) {

    // shift graph
    for (int i = 0; i < 127; i++) {
        graph[i] = graph[i + 1];
    }

    graph[127] = data.percent;

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Monitor Humedad");

    display.setTextSize(2);
    display.setCursor(0, 12);
    display.print(data.percent);
    display.println("%");

    display.setTextSize(1);
    display.setCursor(0, 34);
    display.print("ADC:");
    display.println(data.raw);

    for (int x = 0; x < 127; x++) {

        int y1 = map(graph[x], 0, 100, 63, 40);
        int y2 = map(graph[x + 1], 0, 100, 63, 40);

        display.drawLine(x, y1, x + 1, y2, SSD1306_WHITE);
    }

    display.display();
}