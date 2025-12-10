#include "../Header/Game.h"
#include "Header/Util.h"// Za createShader, loadImageToTexture
#define _USE_MATH_DEFINES
#include <cmath>

// Pomoćna funkcija za učitavanje i podešavanje teksture
void preprocessTexture(unsigned& texture, const char* filepath) {
    texture = loadImageToTexture(filepath);
    glBindTexture(GL_TEXTURE_2D, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

//  FUNKCIJE ZA CRTANJE 

void drawButton(unsigned int shader, unsigned int VAO) {
    glUseProgram(shader);
    glUniform1f(glGetUniformLocation(shader, "uX"), BUTTON_X);
    glUniform1f(glGetUniformLocation(shader, "uY"), BUTTON_Y);
    glUniform1f(glGetUniformLocation(shader, "uScaleX"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uScaleY"), 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void drawTexturedRect(unsigned int shader, unsigned int VAO, unsigned int texture, float x, float y, float scale = 1.0f) {
    glUseProgram(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1f(glGetUniformLocation(shader, "uX"), x);
    glUniform1f(glGetUniformLocation(shader, "uY"), y);
    glUniform1f(glGetUniformLocation(shader, "uS"), scale);
    glUniform1f(glGetUniformLocation(shader, "uA"), 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void drawTexturedQuad(unsigned int texture, float x, float y, float scale) {
    glUseProgram(textureShader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(textureShader, "uTex"), 0); // Postavi sampler na 0

    // Postavi transformacione uniforme
    glUniform1f(glGetUniformLocation(textureShader, "uX"), x);
    glUniform1f(glGetUniformLocation(textureShader, "uY"), y);
    glUniform1f(glGetUniformLocation(textureShader, "uS"), scale);
    glUniform1f(glGetUniformLocation(textureShader, "uA"), 1.0f);

    glBindVertexArray(VAO_KetchupBottle); // Koristimo VAO koji si napravila za kvad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void drawStove(unsigned int shader) {
    glUseProgram(shader);
    glUniform1f(glGetUniformLocation(shader, "uX"), STOVE_X);
    glUniform1f(glGetUniformLocation(shader, "uY"), STOVE_Y);
    glUniform1f(glGetUniformLocation(shader, "uScaleX"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uScaleY"), 1.0f);

    glBindVertexArray(VAO_Stove);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void drawPatty(unsigned int shader) {
    glUseProgram(shader);
    glUniform1f(glGetUniformLocation(shader, "uX"), patty_current_X);
    glUniform1f(glGetUniformLocation(shader, "uY"), patty_current_Y);
    glUniform1f(glGetUniformLocation(shader, "uScaleX"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uScaleY"), 0.5f);

    glBindVertexArray(VAO_Patty);
    glDrawArrays(GL_TRIANGLE_FAN, 0, PATTY_SLICES + 2);
    glBindVertexArray(0);
}

void drawLoadingBar(unsigned int shader) {
    glUseProgram(shader);

    // 1. Crtanje Pozadine (Sivi, puni bar)
    glUniform1f(glGetUniformLocation(shader, "uX"), BAR_X);
    glUniform1f(glGetUniformLocation(shader, "uY"), BAR_Y);
    glUniform1f(glGetUniformLocation(shader, "uScaleX"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uScaleY"), 1.0f);

    glBindVertexArray(VAO_BarBackground);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);

    // 2. Crtanje Ispunjenog Dela (Zeleni bar)
    float fill_percentage = current_progress / MAX_COOKING_TIME;
    if (fill_percentage > 1.0f) fill_percentage = 1.0f;
    if (fill_percentage < 0.0f) fill_percentage = 0.0f;

    float current_width = BAR_WIDTH * fill_percentage;
    float scale_x = fill_percentage;

    float offset_x = (BAR_WIDTH - current_width) / 2.0f;
    float new_x = BAR_X - offset_x; // Pomeranje centra ulevo

    glUniform1f(glGetUniformLocation(shader, "uX"), new_x);
    glUniform1f(glGetUniformLocation(shader, "uY"), BAR_Y);
    glUniform1f(glGetUniformLocation(shader, "uScaleX"), scale_x);
    glUniform1f(glGetUniformLocation(shader, "uScaleY"), 1.0f);

    glBindVertexArray(VAO_BarFill);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void drawPlate(unsigned int shader) {
    glUseProgram(shader);
    glUniform1f(glGetUniformLocation(shader, "uX"), PLATE_X);
    glUniform1f(glGetUniformLocation(shader, "uY"), PLATE_Y);
    glUniform1f(glGetUniformLocation(shader, "uScaleX"), 1.0f);
    glUniform1f(glGetUniformLocation(shader, "uScaleY"), 1.0f);

    glBindVertexArray(VAO_Plate);
    glDrawArrays(GL_TRIANGLE_FAN, 0, PATTY_SLICES + 2);
    glBindVertexArray(0);
}

void drawBottomBun()
{
    glUseProgram(textureShader);
    glUniform1f(glGetUniformLocation(textureShader, "uX"), bun_current_X);
    glUniform1f(glGetUniformLocation(textureShader, "uY"), bun_current_Y);
    glUniform1f(glGetUniformLocation(textureShader, "uS"), 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bottomBunTexture);
    glUniform1i(glGetUniformLocation(textureShader, "uTex"), 0);

    glBindVertexArray(VAO_BunBottom);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

void drawKetchupBottle() {
    drawTexturedQuad(ketchupBottleTexture, ketchup_current_X, ketchup_current_Y, BOTTLE_WIDTH);
}

void drawMustardBottle() {
    drawTexturedQuad(mustardBottleTexture, mustard_current_X, mustard_current_Y, BOTTLE_WIDTH);
}
void drawPickles() {
    drawTexturedQuad(picklesTexture, pickles_current_X, pickles_current_Y, PATTY_RADIUS*2.0f);
}
void drawOnion() {
    drawTexturedQuad(onionTexture, onion_current_X, onion_current_Y, PATTY_RADIUS*2.0f);
}
void drawLettuce() {
    drawTexturedQuad(lettuceTexture, lettuce_current_X, lettuce_current_Y, PATTY_RADIUS*2.0f);
}

void drawSignature() {
    glUseProgram(textureShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, signatureTexture);
    glUniform1i(glGetUniformLocation(textureShader, "uTex"), 0);

    glUniform1f(glGetUniformLocation(textureShader, "uX"), SIGNATURE_CENTER_X);
    glUniform1f(glGetUniformLocation(textureShader, "uY"), SIGNATURE_CENTER_Y);
    glUniform1f(glGetUniformLocation(textureShader, "uS"), SIGNATURE_SCALE);  // fiksna skala
    glUniform1f(glGetUniformLocation(textureShader, "uA"), SIGNATURE_ALPHA);

    glBindVertexArray(VAO_Signature);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}

// Glavna funkcija za crtanje scene (za main loop)
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (current_state == ORDER_BUTTON) {
        drawButton(colorShader, VAO_Button);
        drawTexturedRect(textureShader, VAO_Bell, bellTexture, BUTTON_X, BUTTON_Y, 1.0f);
    }
    else if (current_state == COOKING) {
        drawStove(colorShader);
        drawPatty(colorShader);
        drawLoadingBar(colorShader);
    }
    else if (current_state == ASSEMBLING) {
        // Sto
        drawTexturedRect(textureShader, VAO_Table, tableTexture, TABLE_X, TABLE_Y, 1.0f);
        // Tanjir
        drawPlate(colorShader);
        // Sastojci (koji su već postavljeni ili se postavljaju)
        if (current_ingredient >= PATTY_PLACING || current_ingredient == BUN_BOTTOM) {
            drawBottomBun();
        }
        if (current_ingredient >= PATTY_PLACING) {
            drawPatty(colorShader);
        }
        for (const auto& spill : spills) {
            if (spill.isKetchup) {
                drawTexturedQuad(ketchupSpillTexture, spill.x, spill.y, spill.scale);
            }
            else {
                drawTexturedQuad(mustardSpillTexture, spill.x, spill.y, spill.scale); 
            }
        }
        if (current_state == ASSEMBLING && current_ingredient == KETCHUP) {
            drawKetchupBottle();
        }
        if (current_state == ASSEMBLING && current_ingredient == MUSTARD) {
            drawMustardBottle();
        }
        if (current_ingredient > KETCHUP) {
            float ketchup_layer_Y = patty_current_Y - KETCHUP_VERTICAL_OFFSET;
            drawTexturedQuad(ketchupLayerTexture, PLATE_X, ketchup_layer_Y_pos, PATTY_RADIUS * 2.0f);
        }
        if (current_ingredient > MUSTARD) {
            float mustard_layer_Y = patty_current_Y - MUSTARD_VERTICAL_OFFSET;
            drawTexturedQuad(mustardLayerTexture, PLATE_X, mustard_layer_Y_pos, PATTY_RADIUS * 2.0f);
        }
        if (current_ingredient >= PICKLES) {
            drawPickles();
        }
        if (current_ingredient >= ONION) {
            drawOnion();
        }
        if (current_ingredient >= LETTUCE) {
            drawLettuce();
        }
        if (current_ingredient >= CHEESE) {
            drawTexturedQuad(cheeseTexture, cheese_current_X, cheese_current_Y, PATTY_RADIUS * 2.0f);
        }
        if (current_ingredient >= TOMATO) {
            drawTexturedQuad(tomatoTexture, tomato_current_X, tomato_current_Y, PATTY_RADIUS * 2.0f);
        }
        if (current_ingredient >= BUN_TOP) {
            drawTexturedQuad(topBunTexture, bun_top_current_X, bun_top_current_Y, 0.4f);
        }
    }
    else if (current_state == DONE) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawTexturedQuad(endTexture, 0.0f, -0.2f, 1.2f);
        return;
    }
    drawSignature();
}


// inicijalizacija shadera

void initShaders() {
    colorShader = createShader("basic_color.vert", "basic_color.frag");
    textureShader = createShader("texture.vert", "texture.frag");

    glUseProgram(textureShader);
    glUniform1i(glGetUniformLocation(textureShader, "uTex"), 0);

    // Učitavanje tekstura
    preprocessTexture(bellTexture, "res/porucivanje1.png");
    preprocessTexture(tableTexture, "res/sto11.png");
    preprocessTexture(bottomBunTexture, "res/zemickaD.png");
    preprocessTexture(ketchupBottleTexture, "res/kecap.png");
    preprocessTexture(ketchupLayerTexture, "res/kecapHamburger.png"); 
    preprocessTexture(ketchupSpillTexture, "res/kecapMrlja.png");
    preprocessTexture(mustardBottleTexture, "res/senf.png"); 
    preprocessTexture(mustardLayerTexture, "res/senfHamburger.png"); 
    preprocessTexture(mustardSpillTexture, "res/senfMrlja.png");
    preprocessTexture(picklesTexture, "res/krastavci.png");
    preprocessTexture(onionTexture, "res/luk.png");
    preprocessTexture(lettuceTexture, "res/salata.png");
    preprocessTexture(cheeseTexture, "res/sir.png");
    preprocessTexture(tomatoTexture, "res/paradajz.png");
    preprocessTexture(topBunTexture, "res/gornjaZemicka.png");
    preprocessTexture(endTexture, "res/prijatno.png");
    preprocessTexture(signatureTexture, "res/me.png");
}

// Funkcija koja inicijalizuje SVE VAO/VBO.
void initGeometry(int screenWidth, int screenHeight) {
    // za poziciju/boju
#define V_ATTRIB_POINTER_COLOR() \
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); \
        glEnableVertexAttribArray(0); \
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float))); \
        glEnableVertexAttribArray(1);

    // za poziciju/teksturu
#define V_ATTRIB_POINTER_TEX() \
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); \
        glEnableVertexAttribArray(0); \
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); \
        glEnableVertexAttribArray(1);

    // 1. DUGME
    float verticesButton[] = {
        -BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2, 0.88f, 0.82f, 0.70f,
        -BUTTON_WIDTH / 2, -BUTTON_HEIGHT / 2, 0.88f, 0.82f, 0.70f,
         BUTTON_WIDTH / 2, -BUTTON_HEIGHT / 2, 0.88f, 0.82f, 0.70f,
         BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2, 0.88f, 0.82f, 0.70f
    };
    glGenVertexArrays(1, &VAO_Button);
    glGenBuffers(1, &VBO_Button);
    glBindVertexArray(VAO_Button);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Button);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesButton), verticesButton, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_COLOR()
        glBindVertexArray(0);

    // 2. ZVONCE (Tekstura)
    float verticesBell[] = {
        -BELL_WIDTH / 2, BELL_HEIGHT / 2, 0.0f, 1.0f,
        -BELL_WIDTH / 2, -BELL_HEIGHT / 2, 0.0f, 0.0f,
         BELL_WIDTH / 2, -BELL_HEIGHT / 2, 1.0f, 0.0f,
         BELL_WIDTH / 2, BELL_HEIGHT / 2, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_Bell);
    glGenBuffers(1, &VBO_Bell);
    glBindVertexArray(VAO_Bell);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Bell);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBell), verticesBell, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_TEX()
        glBindVertexArray(0);

    // 3. ŠPORET
    float verticesStove[] = {
        -STOVE_WIDTH / 2, STOVE_HEIGHT / 2,0.25f, 0.25f, 0.25f,
        -STOVE_WIDTH / 2, -STOVE_HEIGHT / 2,0.25f, 0.25f, 0.25f,
         STOVE_WIDTH / 2, -STOVE_HEIGHT / 2,0.25f, 0.25f, 0.25f,
         STOVE_WIDTH / 2, STOVE_HEIGHT / 2,0.25f, 0.25f, 0.25f
    };
    glGenVertexArrays(1, &VAO_Stove);
    glGenBuffers(1, &VBO_Stove);
    glBindVertexArray(VAO_Stove);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Stove);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesStove), verticesStove, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_COLOR()
        glBindVertexArray(0);

    // 4. PLJESKAVICA (Krug)
    float verticesPatty[(PATTY_SLICES + 2) * 5];
    const float R = 1.0f, G = 0.6f, B = 0.6f;
    verticesPatty[0] = 0.0f; verticesPatty[1] = 0.0f;
    verticesPatty[2] = R; verticesPatty[3] = G; verticesPatty[4] = B;

    for (int i = 1; i < PATTY_SLICES + 2; ++i) {
        float angle = (float)(i - 1) * 2.0f * (float)3.14 / PATTY_SLICES;
        if (i == PATTY_SLICES + 1) angle = 0.0f;
        verticesPatty[i * 5] = cos(angle) * PATTY_RADIUS;
        verticesPatty[i * 5 + 1] = sin(angle) * PATTY_RADIUS;
        verticesPatty[i * 5 + 2] = R;
        verticesPatty[i * 5 + 3] = G;
        verticesPatty[i * 5 + 4] = B;
    }
    glGenVertexArrays(1, &VAO_Patty);
    glGenBuffers(1, &VBO_Patty);
    glBindVertexArray(VAO_Patty);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patty);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPatty), verticesPatty, GL_DYNAMIC_DRAW); // DYNAMIC_DRAW zbog promene boje
    V_ATTRIB_POINTER_COLOR()
        glBindVertexArray(0);

    // 5. STO (Tekstura)
    float verticesTable[] = {
        -TABLE_WIDTH / 2, TABLE_HEIGHT / 2, 0.0f, 1.0f,
        -TABLE_WIDTH / 2, -TABLE_HEIGHT / 2, 0.0f, 0.0f,
         TABLE_WIDTH / 2, -TABLE_HEIGHT / 2, 1.0f, 0.0f,
         TABLE_WIDTH / 2, TABLE_HEIGHT / 2, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_Table);
    glGenBuffers(1, &VBO_Table);
    glBindVertexArray(VAO_Table);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Table);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTable), verticesTable, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_TEX()
        glBindVertexArray(0);

    // 6. DONJA ZEMIČKA (Tekstura)
    float verticesBunBottom[] = {
        -BUN_WIDTH / 2, BUN_HEIGHT / 2, 0.0f, 1.0f,
        -BUN_WIDTH / 2, -BUN_HEIGHT / 2, 0.0f, 0.0f,
         BUN_WIDTH / 2, -BUN_HEIGHT / 2, 1.0f, 0.0f,
         BUN_WIDTH / 2, BUN_HEIGHT / 2, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_BunBottom);
    glGenBuffers(1, &VBO_BunBottom);
    glBindVertexArray(VAO_BunBottom);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_BunBottom);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBunBottom), verticesBunBottom, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_TEX()
        glBindVertexArray(0);

    // 7. TANJIR (Krug)
    float verticesPlate[(PATTY_SLICES + 2) * 5];
    const float R_P = 1.0f, G_P = 1.0f, B_P = 1.0f;
    verticesPlate[0] = 0.0f; verticesPlate[1] = 0.0f;
    verticesPlate[2] = R_P; verticesPlate[3] = G_P; verticesPlate[4] = B_P;

    for (int i = 1; i < PATTY_SLICES + 2; ++i) {
        float angle = (float)(i - 1) * 2.0f * (float)3.14 / PATTY_SLICES;
        if (i == PATTY_SLICES + 1) angle = 0.0f;
        verticesPlate[i * 5] = cos(angle) * PLATE_RADIUS;
        verticesPlate[i * 5 + 1] = sin(angle) * PLATE_RADIUS;
        verticesPlate[i * 5 + 2] = R_P;
        verticesPlate[i * 5 + 3] = G_P;
        verticesPlate[i * 5 + 4] = B_P;
    }
    glGenVertexArrays(1, &VAO_Plate);
    glGenBuffers(1, &VBO_Plate);
    glBindVertexArray(VAO_Plate);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Plate);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPlate), verticesPlate, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_COLOR()
        glBindVertexArray(0);

    // 8. LOADING BAR (Pozadina - Siva)
    float verticesBarBackground[] = {
        -BAR_WIDTH / 2, BAR_HEIGHT / 2, 0.7f, 0.7f, 0.7f,
        -BAR_WIDTH / 2, -BAR_HEIGHT / 2, 0.7f, 0.7f, 0.7f,
         BAR_WIDTH / 2, -BAR_HEIGHT / 2, 0.7f, 0.7f, 0.7f,
         BAR_WIDTH / 2, BAR_HEIGHT / 2, 0.7f, 0.7f, 0.7f
    };
    glGenVertexArrays(1, &VAO_BarBackground);
    glGenBuffers(1, &VBO_BarBackground);
    glBindVertexArray(VAO_BarBackground);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_BarBackground);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBarBackground), verticesBarBackground, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_COLOR()
        glBindVertexArray(0);

    // 9. LOADING BAR (Ispuna - Zelena)
    float verticesBarFill[] = {
        -BAR_WIDTH / 2, BAR_HEIGHT / 2, 0.1f, 0.6f, 0.1f,
        -BAR_WIDTH / 2, -BAR_HEIGHT / 2,0.1f, 0.6f, 0.1f,
         BAR_WIDTH / 2, -BAR_HEIGHT / 2, 0.1f, 0.6f, 0.1f,
         BAR_WIDTH / 2, BAR_HEIGHT / 2,0.1f, 0.6f, 0.1f
    };
    glGenVertexArrays(1, &VAO_BarFill);
    glGenBuffers(1, &VBO_BarFill);
    glBindVertexArray(VAO_BarFill);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_BarFill);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBarFill), verticesBarFill, GL_STATIC_DRAW);
    V_ATTRIB_POINTER_COLOR()
        glBindVertexArray(0);

    //KECAP
    float ketchupVertices[] = {
        // Pozicija | Tekstura
        -0.5f,  0.5f, 0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 1.0f, 1.0f, // Top-right
        -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
    };

    glGenVertexArrays(1, &VAO_KetchupBottle);
    glGenBuffers(1, &VBO_KetchupBottle);

    glBindVertexArray(VAO_KetchupBottle);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_KetchupBottle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ketchupVertices), ketchupVertices, GL_STATIC_DRAW);

    // Pozicija atribut (location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Tekstura atribut (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 10. POTPIS
    float verticesSignature[] = {
        -SIGNATURE_WIDTH / 2,  SIGNATURE_HEIGHT / 2, 0.0f, 1.0f,
        -SIGNATURE_WIDTH / 2, -SIGNATURE_HEIGHT / 2, 0.0f, 0.0f,
         SIGNATURE_WIDTH / 2, -SIGNATURE_HEIGHT / 2, 1.0f, 0.0f,
         SIGNATURE_WIDTH / 2,  SIGNATURE_HEIGHT / 2, 1.0f, 1.0f
    };
    glGenVertexArrays(1, &VAO_Signature);
    glGenBuffers(1, &VBO_Signature);
    glBindVertexArray(VAO_Signature);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Signature);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSignature), verticesSignature, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}