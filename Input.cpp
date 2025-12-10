#include "../Header/Game.h"
#include <cmath>

// Funkcija za proveru da li je sastojak postavljen (Tolerancija)
bool isIngredientPlaced(float ingX, float ingY,
    float targetX, float targetY,
    float toleranceX, float toleranceY)
{
    // Apsolutna razlika u X i Y koordinati mora biti manja od tolerancije.
    bool x_ok = std::abs(ingX - targetX) < toleranceX;
    bool y_ok = std::abs(ingY - targetY) < toleranceY;

    return x_ok && y_ok;
}


// Funkcija za prelazak na sledeći sastojak
void placeNextIngredient() {
    switch (current_ingredient) {
    case BUN_BOTTOM:
        // Ažuriraj stack_height na vrh postavljenog sastojka
        stack_height = PLATE_Y + BUN_HEIGHT / 2.0f;
        current_ingredient = PATTY_PLACING;
        std::cout << "Pljeskavica!" << std::endl;
        patty_current_X = PLATE_X;
        patty_current_Y = stack_height + 0.5f;
        break;
    case PATTY_PLACING:
        stack_height = (PLATE_Y + BUN_HEIGHT) + PATTY_THICKNESS / 2.0f;
        current_ingredient = KETCHUP;
        std::cout << "Kečap!" << std::endl;
        ketchup_current_X = KETCHUP_START_X;
        ketchup_current_Y = KETCHUP_START_Y;
        break;
    case KETCHUP: 
        ketchup_layer_Y_pos = stack_height - (PATTY_THICKNESS / 2.0f) + (LAYER_THICKNESS / 2.0f)-0.3f;
        stack_height += LAYER_THICKNESS;
        current_ingredient = MUSTARD;
        std::cout << "Senf!" << std::endl;
        mustard_current_X = MUSTARD_START_X;
        mustard_current_Y = MUSTARD_START_Y;
        break;
    case MUSTARD: 
        mustard_layer_Y_pos = stack_height + LAYER_THICKNESS / 2.0f -0.3f;
        stack_height += LAYER_THICKNESS;
        current_ingredient = PICKLES;
        pickles_current_X = PLATE_X;
        pickles_current_Y = stack_height + 0.5f;
        std::cout << "Kiseli krastavci!" << std::endl;
        break;
    case PICKLES:
        stack_height += 0.05f; 
        current_ingredient = ONION;
        onion_current_X = PLATE_X;
        onion_current_Y = stack_height + 0.5f;
        std::cout << "Krastavci postavljeni!" << std::endl;
        break;
    case ONION:
        stack_height += LAYER_THICKNESS;
        current_ingredient = LETTUCE;
        lettuce_current_X = PLATE_X;
        lettuce_current_Y = stack_height + 0.5f;
        std::cout << "Luk postavljen! Sada ide salata!" << std::endl;
        break;
    case LETTUCE:
        stack_height += LAYER_THICKNESS;
        current_ingredient = CHEESE;
        cheese_current_X = PLATE_X;
        cheese_current_Y = stack_height + 0.5f;
        std::cout << "Salata postavljena! Sada ide sir!" << std::endl;
        break;
    case CHEESE:
        stack_height += LAYER_THICKNESS;
        current_ingredient = TOMATO;
        tomato_current_X = PLATE_X;
        tomato_current_Y = stack_height + 0.5f;
        std::cout << "Sir postavljen! Sada ide paradajz!" << std::endl;
        break;
    case TOMATO:
        stack_height += 0.05f;
        current_ingredient = BUN_TOP;
        bun_top_current_X = PLATE_X;
        bun_top_current_Y = stack_height + BUN_HEIGHT / 2.0f;
        std::cout << "Paradajz postavljen! Sada ide gornja zemicka!" << std::endl;
        break;
    case BUN_TOP:
        stack_height += BUN_HEIGHT;
        current_ingredient = FINALIZING;
        current_state = DONE;
        std::cout << "Burger zavrsen!" << std::endl;
        break;
    default:
        break;
    }
}

// Rukovanje tastaturom
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    // Proveri pritisak ili držanje tastera
    if (action != GLFW_PRESS && action != GLFW_REPEAT) return;

    float current_move_speed = MOVE_SPEED;

    // Pomeranje u stanju COOKING (Pljeskavica)
    if (current_state == COOKING) {
        if (key == GLFW_KEY_W) patty_current_Y += current_move_speed;
        if (key == GLFW_KEY_S) patty_current_Y -= current_move_speed;
        if (key == GLFW_KEY_A) patty_current_X -= current_move_speed;
        if (key == GLFW_KEY_D) patty_current_X += current_move_speed;
    }
    // --- Pomeranje u stanju ASSEMBLING (Sastojci) ---
    else if (current_state == ASSEMBLING) {
        // Kontrolišeš komponentu koja se TRENUTNO postavlja
        float* current_X = nullptr;
        float* current_Y = nullptr;

        if (current_ingredient == BUN_BOTTOM) {
            current_X = &bun_current_X;
            current_Y = &bun_current_Y;
        }
        else if (current_ingredient == PATTY_PLACING) {
            current_X = &patty_current_X;
            current_Y = &patty_current_Y;
        }
        else if (current_ingredient == KETCHUP) {
            current_X = &ketchup_current_X;
            current_Y = &ketchup_current_Y;
        }
        else if (current_ingredient == MUSTARD) {
            current_X = &mustard_current_X;
            current_Y = &mustard_current_Y;
        }
        else if (current_ingredient == PICKLES) {
            current_X = &pickles_current_X;
            current_Y = &pickles_current_Y;
        }
        else if (current_ingredient == ONION) {
            current_X = &onion_current_X;
            current_Y = &onion_current_Y;
        }
        else if (current_ingredient == LETTUCE) {
            current_X = &lettuce_current_X;
            current_Y = &lettuce_current_Y;
        }
        else if (current_ingredient == CHEESE) {
            current_X = &cheese_current_X;
            current_Y = &cheese_current_Y;
        }
        else if (current_ingredient == TOMATO) {
            current_X = &tomato_current_X;
            current_Y = &tomato_current_Y;
        }
        else if (current_ingredient == BUN_TOP) {
            current_X = &bun_top_current_X;
            current_Y = &bun_top_current_Y;
        }
        
        if (current_X != nullptr) {
            if (key == GLFW_KEY_W) *current_Y += current_move_speed;
            if (key == GLFW_KEY_S) *current_Y -= current_move_speed;
            if (key == GLFW_KEY_A) *current_X -= current_move_speed;
            if (key == GLFW_KEY_D) *current_X += current_move_speed;
        }

        if (key == GLFW_KEY_SPACE) {

            if (current_ingredient == KETCHUP) {
                // Provjeravam da li je flaiscca iznad tanjira
                bool above_plate = std::abs(ketchup_current_X - PLATE_X) < PLATE_RADIUS;

                if (above_plate) {
                    // Postavljen na burger: Prelazim na senf.
                    std::cout << "Kečap postavljen na burger!" << std::endl;
                    // automatski dodaje sloj i povecava stack_height (u placeNextIngredient)
                    placeNextIngredient();
                }
                else {
                    // Pprosuto na sto: Dodajemo mrlju, ali ostajemo u fazi KETCHUP.
                    const float SPILL_Y = -0.7f;
                    Spill new_spill = { ketchup_current_X, SPILL_Y, SPILLED_SCALE, true };
                    spills.push_back(new_spill);
                    std::cout << "Kečap proliven na (" << new_spill.x << ", " << new_spill.y << ")! Pokusajte ponovo." << std::endl;
                }
            }
            else if (current_ingredient == MUSTARD) {
                // Provjeravam da li je flasica iznad tanjira
                bool above_plate = std::abs(mustard_current_X - PLATE_X) < PLATE_RADIUS;

                if (above_plate) {
                    // Postavljeno na burger: Prelazimo na krastavce.
                    std::cout << "Senf postavljen na burger!" << std::endl;
                    placeNextIngredient();
                }
                else {
                    // Prosuto na sto: Dodajemo mrlju, ali ostajemo u fazi MUSTARD.
                    const float SPILL_Y = -0.7f;
                    Spill new_spill = { mustard_current_X, SPILL_Y, SPILLED_SCALE, false };
                    spills.push_back(new_spill);
                    std::cout << "Senf proliven na (" << new_spill.x << ", " << new_spill.y << ")! Pokusajte ponovo." << std::endl;
                }
            }
        }
    }
}

// Rukovanje klikom miša
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS) return;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int screenWidth, screenHeight;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);

    float x_norm = (float)(xpos / screenWidth) * 2.0f - 1.0f;
    float y_norm = -((float)(ypos / screenHeight) * 2.0f - 1.0f);

    if (current_state == ORDER_BUTTON) {
        if (x_norm >= BUTTON_X - BUTTON_WIDTH / 2 && x_norm <= BUTTON_X + BUTTON_WIDTH / 2 &&
            y_norm >= BUTTON_Y - BUTTON_HEIGHT / 2 && y_norm <= BUTTON_Y + BUTTON_HEIGHT / 2)
        {
            std::cout << "Dugme 'Poruci' je kliknuto! Prelazimo na prvu scenu." << std::endl;
            current_state = COOKING;
        }
    }
    else if (current_state == ASSEMBLING) {
        bool placed = false;
        float targetY;

        switch (current_ingredient) {
        case BUN_BOTTOM:
            targetY = PLATE_Y + BUN_HEIGHT / 2.0f;
            placed = isIngredientPlaced(bun_current_X, bun_current_Y, PLATE_X, targetY, 0.15f, 0.15f);
            break;
        case PATTY_PLACING: {
            float targetX = PLATE_X;
            float targetY = PLATE_Y + BUN_HEIGHT / 2.0f;   // CENTAR DONJE ZEMIČKE
            placed = isIngredientPlaced(patty_current_X, patty_current_Y,targetX, targetY, 0.15f, 0.15f);
            break;
        }
        case PICKLES: {
            float targetX = PLATE_X;
            float targetY = mustard_layer_Y_pos + 0.1f; // centar senfa + malo iznad
            placed = isIngredientPlaced(pickles_current_X, pickles_current_Y, targetX, targetY, 0.15f, 0.15f);
            break;
        }

        case ONION: {
            float targetX = PLATE_X;
            float targetY = pickles_current_Y + 0.1f;
            placed = isIngredientPlaced(onion_current_X, onion_current_Y, targetX, targetY, 0.15f, 0.15f);
            break;
        }
        case LETTUCE: {
            float targetX = PLATE_X;
            float targetY = onion_current_Y + 0.1f; 
            placed = isIngredientPlaced(lettuce_current_X, lettuce_current_Y, targetX, targetY, 0.15f, 0.15f);
            break;
        }
        case CHEESE: {
            float targetX = PLATE_X;
            float targetY = lettuce_current_Y + 0.1f; // Sir ide na salatu
            bool placed = isIngredientPlaced(cheese_current_X, cheese_current_Y, targetX, targetY, 0.15f, 0.15f);
            if (placed) {
                placeNextIngredient();
            }
            break;
        }
        case TOMATO: {
            float targetX = PLATE_X;
            float targetY = cheese_current_Y + 0.1f; 
            bool placed = isIngredientPlaced(tomato_current_X, tomato_current_Y, targetX, targetY, 0.15f, 0.15f);
            if (placed) {
                placeNextIngredient();
            }
            break;
        }
        case BUN_TOP: {
            float targetX = PLATE_X;
            float targetY = stack_height - (BUN_HEIGHT * (1.0f - 0.4f) / 2.0f);
            bool placed = isIngredientPlaced(bun_top_current_X, bun_top_current_Y, targetX, targetY, 0.15f, 0.15f);
            if (placed) {
                placeNextIngredient(); 
            }
            break;
        }
        default:
            break;
        }

        if (placed) {
            placeNextIngredient();
        }
        else {
            std::cout << "Sastojak nije pravilno postavljen, pomeri ga!" << std::endl;
        }

    }
}