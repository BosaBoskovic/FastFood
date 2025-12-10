#include "../Header/Game.h"
#include <cmath> // Za M_PI

//GLOBALNE PROMENLJIVE STANJA (INICIJALIZACIJA)
GameState current_state = ORDER_BUTTON;
IngredientState current_ingredient = BUN_BOTTOM;
float patty_current_X = 0.0f;
float patty_current_Y = STOVE_Y + STOVE_HEIGHT / 2.0f + PATTY_RADIUS + 0.01f;
float bun_current_X = PLATE_X;
float bun_current_Y = BUN_START_Y;
float stack_height = PLATE_Y;
float current_progress = 0.0f;
float patty_color_R = 1.0f; // Roze/crvena
float patty_color_G = 0.6f;
float patty_color_B = 0.6f;
double lastFrameTime = 0.0;
float ketchup_current_X = KETCHUP_START_X;
float ketchup_current_Y = KETCHUP_START_Y;
float mustard_current_X = MUSTARD_START_X;
float mustard_current_Y = MUSTARD_START_Y;
float ketchup_layer_Y_pos = 0.0f;
float mustard_layer_Y_pos = 0.0f;
float pickles_current_X = PLATE_X;       
float pickles_current_Y = 0.0f;
float onion_current_X = PLATE_X;
float onion_current_Y = 0.0f;
float onion_layer_Y_pos = 0.0f;
float lettuce_current_X = 0.0f;
float lettuce_current_Y = 0.0f;
float lettuce_layer_Y_pos = 0.0f;
float cheese_current_X = 0.0f;
float cheese_current_Y = 0.0f;
float cheese_layer_Y_pos = 0.0f;
float tomato_current_X = 0.0f;
float tomato_current_Y = 0.0f;
float tomato_layer_Y_pos = 0.0f;
float bun_top_current_X = PLATE_X;
float bun_top_current_Y = 0.0f;
std::vector<Spill> spills;

// GLOBALNI OPENGL OBJEKTI (INICIJALIZACIJA)
unsigned int VAO_Button, VBO_Button;
unsigned int VAO_Bell, VBO_Bell;
unsigned int VAO_Stove, VBO_Stove;
unsigned int VAO_Patty, VBO_Patty;
unsigned int VAO_BarBackground, VBO_BarBackground;
unsigned int VAO_BarFill, VBO_BarFill;
unsigned int VAO_Table, VBO_Table;
unsigned int VAO_Plate, VBO_Plate;
unsigned int VAO_BunBottom, VBO_BunBottom;
unsigned int VAO_KetchupBottle, VBO_KetchupBottle;
unsigned int VAO_Signature, VBO_Signature;

unsigned int bellTexture;
unsigned int tableTexture;
unsigned int bottomBunTexture;
unsigned int ketchupBottleTexture = 0; 
unsigned int ketchupLayerTexture = 0;
unsigned int ketchupSpillTexture = 0;
unsigned int mustardBottleTexture = 0; 
unsigned int mustardLayerTexture = 0;  
unsigned int mustardSpillTexture = 0;
unsigned int picklesTexture = 0;
unsigned int onionTexture = 0;
unsigned int lettuceTexture = 0;
unsigned int cheeseTexture = 0;
unsigned int tomatoTexture = 0;
unsigned int topBunTexture = 0;
unsigned int endTexture = 0;
unsigned int signatureTexture = 0;

unsigned int colorShader;
unsigned int textureShader;
unsigned int bunShader;

GLFWcursor* spatulaCursor = nullptr;
GLFWcursor* hamburgerCursor = nullptr;
GLFWcursor* handCursor = nullptr;
GLFWcursor* panCursor = nullptr;