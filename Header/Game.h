#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// ENUM-I STANJA IGRE
enum GameState {
    ORDER_BUTTON,
    COOKING,
    ASSEMBLING,
    DONE
};

enum IngredientState {
    BUN_BOTTOM,
    PATTY_PLACING,
    KETCHUP,
    MUSTARD,
    PICKLES,
    ONION,
    LETTUCE,
    CHEESE,
    TOMATO,
    BUN_TOP,
    FINALIZING
};

// GLOBALNE PROMENLJIVE STANJA (EXTERN)
extern GameState current_state;
extern IngredientState current_ingredient;
extern float patty_current_X;
extern float patty_current_Y;
extern float bun_current_X;
extern float bun_current_Y;
extern float stack_height;
extern float ketchup_current_X; 
extern float ketchup_current_Y;
extern float mustard_current_X; 
extern float mustard_current_Y;
extern float mustard_layer_Y_pos;
extern float ketchup_layer_Y_pos;
extern float pickles_current_X;
extern float pickles_current_Y;
extern float onion_current_X;
extern float onion_current_Y;
extern float onion_layer_Y_pos;
extern float lettuce_current_X;
extern float lettuce_current_Y;
extern float lettuce_layer_Y_pos;
extern float cheese_current_X;
extern float cheese_current_Y;
extern float cheese_layer_Y_pos;
extern float tomato_current_X;
extern float tomato_current_Y;
extern float tomato_layer_Y_pos;
extern float bun_top_current_X;
extern float bun_top_current_Y;

extern float current_progress;
extern float patty_color_R, patty_color_G, patty_color_B;
extern double lastFrameTime;

struct Spill {
    float x, y, scale;
    bool isKetchup; // true za kecap, false za senf
};

extern std::vector<Spill> spills; // Lista prosutih mrlja

// GLOBALNI OPENGL OBJEKTI (EXTERN)
extern unsigned int VAO_Button, VBO_Button;
extern unsigned int VAO_Bell, VBO_Bell;
extern unsigned int VAO_Stove, VBO_Stove;
extern unsigned int VAO_Patty, VBO_Patty;
extern unsigned int VAO_BarBackground, VBO_BarBackground;
extern unsigned int VAO_BarFill, VBO_BarFill;
extern unsigned int VAO_Table, VBO_Table;
extern unsigned int VAO_Plate, VBO_Plate;
extern unsigned int VAO_BunBottom, VBO_BunBottom;
extern unsigned int VAO_KetchupBottle, VBO_KetchupBottle;
extern unsigned int VAO_Signature, VBO_Signature;

extern unsigned int bellTexture;
extern unsigned int tableTexture;
extern unsigned int bottomBunTexture;
extern unsigned int ketchupBottleTexture; 
extern unsigned int ketchupLayerTexture; 
extern unsigned int ketchupSpillTexture; 
extern unsigned int mustardBottleTexture; 
extern unsigned int mustardLayerTexture;
extern unsigned int mustardSpillTexture;
extern unsigned int picklesTexture;
extern unsigned int onionTexture;
extern unsigned int lettuceTexture;
extern unsigned int cheeseTexture;
extern unsigned int tomatoTexture;
extern unsigned int topBunTexture;
extern unsigned int endTexture;
extern unsigned int signatureTexture;

extern unsigned int colorShader;
extern unsigned int textureShader;
extern unsigned int bunShader;

extern GLFWcursor* spatulaCursor;
extern GLFWcursor* hamburgerCursor;
extern GLFWcursor* handCursor;
extern GLFWcursor* panCursor;


// KONSTANTE
const int PATTY_SLICES = 40;
const float PATTY_RADIUS = 0.12f;
const float PATTY_THICKNESS = 0.05f;
const float MAX_COOKING_TIME = 10.0f;
const float STACKING_TOLERANCE = 0.08f;
const float BOTTLE_WIDTH = 0.45f;
const float BOTTLE_HEIGHT = 1.0f; 
const float KETCHUP_START_X = -0.5f; 
const float KETCHUP_START_Y = 0.5f;
const float LAYER_THICKNESS = 0.05f;
const float KETCHUP_VERTICAL_OFFSET = 0.0002f;
const float SPILLED_SCALE = 0.2f;
const float MUSTARD_START_X = -0.5f; 
const float MUSTARD_START_Y = 0.5f;
const float MUSTARD_VERTICAL_OFFSET = 0.0003f;
const float MOVE_SPEED = 0.01f;
const float BUN_MOVE_SPEED = 0.01f;
const float BUN_WIDTH = 0.5f;
const float BUN_HEIGHT = 0.4f;
const float PLATE_Y = -0.57f;
const float BUN_START_Y = PLATE_Y + 0.7f;
const float BUTTON_WIDTH = 0.25f;
const float BUTTON_HEIGHT = 0.25f;
const float BUTTON_X = 0.0f;
const float BUTTON_Y = 0.0f;
const float BELL_WIDTH = 0.3f;
const float BELL_HEIGHT = 0.3f;
const float STOVE_WIDTH = 1.8f;
const float STOVE_HEIGHT = 0.5f;
const float STOVE_X = 0.0f;
const float STOVE_Y = -1.0f + STOVE_HEIGHT / 2.0f;
const float TABLE_WIDTH = 2.2f;
const float TABLE_HEIGHT = 0.9f;
const float TABLE_X = 0.0f;
const float TABLE_Y = -1.0f + TABLE_HEIGHT / 2.0f;
const float PLATE_RADIUS = 0.18f;
const float PLATE_X = 0.0f;
const float BAR_WIDTH = 1.8f;
const float BAR_HEIGHT = 0.05f;
const float BAR_X = 0.0f;
const float BAR_Y = 1.0f - BAR_HEIGHT / 2.0f - 0.02f;
const float TARGET_R = 0.5f;
const float TARGET_G = 0.3f;
const float TARGET_B = 0.0f;
const float SIGNATURE_WIDTH = 0.3f;
const float SIGNATURE_HEIGHT = 0.40f;
const float SIGNATURE_CENTER_X = 1.0f - SIGNATURE_WIDTH / 2.0f - 0.02f; // Blizu desne ivice
const float SIGNATURE_CENTER_Y = 1.0f - SIGNATURE_HEIGHT / 2.0f - 0.1f; // Blizu gornje ivice
const float SIGNATURE_ALPHA = 0.9f;
const float SIGNATURE_SCALE = 1.2f;

// INTERFEJS FUNKCIJE
void initGeometry(int screenWidth, int screenHeight);
void initShaders();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void updatePattyAndBar(double deltaTime);
void updateCursor(GLFWwindow* window);
void clampPattyPosition();

void drawScene();
void drawBottomBun();
void drawButton(unsigned int shader, unsigned int VAO);
void drawLoadingBar(unsigned int shader);
void drawTexturedQuad(unsigned int texture, float x, float y, float scale);
bool isIngredientPlaced(float ingX, float ingY, float targetX, float targetY, float toleranceX = 0.05f, float toleranceY = 0.05f);