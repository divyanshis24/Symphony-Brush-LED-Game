#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

const int slingshotX = 16; // X-coordinate of the slingshot
const int slingshotY = 56; // Y-coordinate of the slingshot
const int birdRadius = 3; // Radius of the bird
const int obstacleWidth = 10; // Width of obstacles
const int obstacleHeight = 20; // Height of obstacles

const int touchSensorPin1 = 7; // speed ++
const int touchSensorPin2 = 8; // speed --
int score = 0; // Initialize score counter

float launchSpeed = 3.0;

struct Bird {
  float x;
  float y;
  float vx;
  float vy;
  bool launched;
};

const int buildingWidth = 10; // Width of the building
const int buildingHeight = 20; // Height of the building

struct Building {
  float x;
  float y;
  bool active;
};

Building building = {OLED_WIDTH / 2, OLED_HEIGHT / 2, true}; // Initial position of the building

Bird bird = {slingshotX, slingshotY, 0, 0, false}; // Initial position of the bird

void setup() {
  Wire.begin(); // Initialize I2C communication
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize OLED display with I2C address 0x3C
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Press joystick to launch!");
  display.setCursor(OLED_WIDTH - 60, 0);
  display.print("Score: ");
  display.print(score);

  pinMode(2, INPUT_PULLUP); // Joystick button pin
  pinMode(touchSensorPin1, INPUT_PULLUP);
  pinMode(touchSensorPin2, INPUT_PULLUP);
}

void loop() {
  handleInput(); // Check for joystick input
  updateGame(); // Update game state
  renderGame(); // Render game on OLED display
  delay(50); // Adjust delay for frame rate
}

void handleInput() {
  int xInput = analogRead(A0); // X-axis input (for aiming)
  int yInput = analogRead(A1); // Y-axis input (for launching power)

  // Calculate aiming angle based on joystick position
  float angle = atan2(yInput - 512, xInput - 512) * 180 / PI;
  if (angle < 0) {
    angle += 360; // Normalize angle to range [0, 360)
  }

  // Launch bird when joystick button is pressed
  if (digitalRead(2) == LOW && !bird.launched) {
    if(digitalRead(touchSensorPin1) == HIGH && launchSpeed < 10)
    launchSpeed++;
    else if(digitalRead(touchSensorPin2) == HIGH && launchSpeed > 3)
    launchSpeed--;

    bird.vx = launchSpeed * cos(angle * PI / 180); // Calculate horizontal velocity
    bird.vy = launchSpeed * sin(angle * PI / 180); // Calculate vertical velocity
    bird.launched = true; // Mark bird as launched
  }
}

void updateGame() {
  if (bird.launched) {
    // Update bird position based on velocity
    bird.x += bird.vx;
    bird.y += bird.vy;

    // Simulate gravity (adjust acceleration as needed)
    bird.vy += 0.1; // Gravity effect

    // Check collision with obstacles (simple AABB collision detection)
    if (bird.x >= OLED_WIDTH || bird.x <= 0 || bird.y >= OLED_HEIGHT) {
      // Reset bird if it goes out of bounds
      bird = {slingshotX, slingshotY, 0, 0, false};
    }

    // Check collision with building
    if (building.active && bird.x >= building.x && bird.x <= building.x + buildingWidth &&
        bird.y >= building.y && bird.y <= building.y + buildingHeight) {
      // If bird hits the building, reset the building to a random position
      score++;
      building = {random(buildingWidth, OLED_WIDTH - buildingWidth), random(buildingHeight, OLED_HEIGHT - buildingHeight), true};
    }
  }
}

void renderGame() {
  display.clearDisplay();
  int xInput = analogRead(A0); // X-axis input (for aiming)
  int yInput = analogRead(A1); // Y-axis input (for launching power)

  // Render slingshot
  display.drawCircle(slingshotX, slingshotY, 3, SSD1306_WHITE);
  display.drawLine(slingshotX, slingshotY, slingshotX + xInput, slingshotY - yInput, SSD1306_WHITE);

  // Render bird
  display.fillCircle(bird.x, bird.y, birdRadius, SSD1306_WHITE);

  // Render building if active
  if (building.active) {
    display.fillRect(building.x, building.y, buildingWidth, buildingHeight, SSD1306_WHITE);
  }

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(OLED_WIDTH - 60, 0);
  display.print("Score: ");
  display.print(score);
  display.display();
}