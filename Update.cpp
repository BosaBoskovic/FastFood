#include "../Header/Game.h"
#include <cmath>
#include <iostream>

// Proverava da li pljeskavica dodiruje šporet
bool isPattyCooking() {
    bool x_overlap = (patty_current_X + PATTY_RADIUS >= STOVE_X - STOVE_WIDTH / 2) &&
        (patty_current_X - PATTY_RADIUS <= STOVE_X + STOVE_WIDTH / 2);

    float stove_top = STOVE_Y + STOVE_HEIGHT / 2.0f;
    float patty_scaled_radius_y = PATTY_RADIUS * 0.5f; // vertikalno spljoštena

    bool y_overlap = (patty_current_Y - patty_scaled_radius_y <= stove_top) &&
        (patty_current_Y + patty_scaled_radius_y >= STOVE_Y - STOVE_HEIGHT / 2);

    return x_overlap && y_overlap;
}


// Ograničava pljeskavicu da ostane na ekranu
void clampPattyPosition() {
    const float minX = -1.0f + PATTY_RADIUS;
    const float maxX = 1.0f - PATTY_RADIUS;
    const float minY = -1.0f + PATTY_RADIUS;
    const float maxY = 1.0f - PATTY_RADIUS;

    if (patty_current_X < minX) patty_current_X = minX;
    if (patty_current_X > maxX) patty_current_X = maxX;
    if (patty_current_Y < minY) patty_current_Y = minY;
    if (patty_current_Y > maxY) patty_current_Y = maxY;
}

// Ažurira loading bar i boju pljeskavice
void updatePattyAndBar(double deltaTime) {
    if (current_state != COOKING) return;

    clampPattyPosition();

    if (isPattyCooking()) {
        if (current_progress < MAX_COOKING_TIME) {
            current_progress += (float)deltaTime;
        }

        if (current_progress >= MAX_COOKING_TIME) {
            current_progress = MAX_COOKING_TIME;
            current_state = ASSEMBLING;
            std::cout << "Pljeskavica gotova! Prelazak na sastavljanje." << std::endl;
            // Postavlja pljeskavicu na početnu visoku poziciju za ASSEMBLING
            patty_current_X = PLATE_X;
            patty_current_Y = stack_height  + 0.5f; 
        }

        // Dinamička promena boje (LERP)
        float cook_ratio = current_progress / MAX_COOKING_TIME;
        patty_color_R = 1.0f + cook_ratio * (TARGET_R - 1.0f);
        patty_color_G = 0.6f + cook_ratio * (TARGET_G - 0.6f);
        patty_color_B = 0.6f + cook_ratio * (TARGET_B - 0.6f);

        //AŽURIRANJE VBO SA NOVOM BOJOM
        float verticesPatty[(PATTY_SLICES + 2) * 5];
        verticesPatty[0] = 0.0f;
        verticesPatty[1] = 0.0f;
        verticesPatty[2] = patty_color_R;
        verticesPatty[3] = patty_color_G;
        verticesPatty[4] = patty_color_B;

        //pravi krug - pljeskavicu
        for (int i = 1; i < PATTY_SLICES + 2; ++i) {
            float angle = (float)(i - 1) * 2.0f * (float)3.14 / PATTY_SLICES;
            if (i == PATTY_SLICES + 1) angle = 0.0f;
            verticesPatty[i * 5] = cos(angle) * PATTY_RADIUS;
            verticesPatty[i * 5 + 1] = sin(angle) * PATTY_RADIUS;
            verticesPatty[i * 5 + 2] = patty_color_R;
            verticesPatty[i * 5 + 3] = patty_color_G;
            verticesPatty[i * 5 + 4] = patty_color_B;
        }
        //saljem novu boju ljeskavice GPU
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Patty);
        // Koristim glBufferSubData jer je VBO već alociran kao GL_DYNAMIC_DRAW
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesPatty), verticesPatty);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void updateCursor(GLFWwindow* window) {
    switch (current_state) {
    case ORDER_BUTTON:
        glfwSetCursor(window, handCursor);
        break;
    case COOKING:
        glfwSetCursor(window, panCursor);
        break;
    case ASSEMBLING:
        glfwSetCursor(window, spatulaCursor);
        break;
    case DONE:
        glfwSetCursor(window, hamburgerCursor);
        break;
    }
}
