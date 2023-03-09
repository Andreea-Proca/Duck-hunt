#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include <components/text_renderer.h>

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    cx = (squareSide / 2) + corner.x;
    cy = (squareSide / 2) + corner.y;

    // Initialize tx and ty (the translation steps)
    translateX = 100;
    translateY = 0;

    angularStepHalo = 0;
    //tx and ty for Robo
    roboTranslateX = 0;
    roboTranslateY = 0;
    roboOnScreen = false;
 
    angularStep = 0;
    angularStepDuck = RADIANS(30);
    angle = 70;

    timerWings = 0;
    angularStepWings = 0;

    bulletsLeft = 3; // nr gloante ramase
    livesLeft = 3; // nr vieti ramase
    score = 0;

    cursorX = cursorY = 0; // coordonate target 
    dZborX = dZborY = 1; // directie rata
    dead = false; // daca rata este impuscata
    ttl = 0; // timpul cat sta rata pe ecran inainte sa scape
    click = false; // daca jucatorul a dat click
    outOfScreen = false; // daca rata nu este pe ecran
    ducksShot = 0;  // nr rate impuscate total
    speed = 100;
    timerLevelUp = 0; // timer pentru cronometrare cat timp este afisata fereastra de notif level up
    levelUp = false; // daca tocmai a trecut la lvl urm
    noBulletsLostLife = false; //  daca ramane fara gloante pierde o viata
    ttlLostLife = false; // daca timpul ratei pe ecran trece de limita, pierde o viata

    tr = new gfxc::TextRenderer(window->props.selfDir, resolution.x, resolution.y);
    tr->Load(window->props.selfDir + "\\assets\\fonts\\Hack-Bold.ttf", 128);

// BONUS ROBO ------------------------------------------------------------------------------------------------------->
    Mesh* square4 = object2D::CreateSquare("square4", corner, 50, glm::vec3(1, 0.3, 0.3), true); // head
    AddMeshToList(square4);
    Mesh* square5 = object2D::CreateSquare("square5", corner, 100, glm::vec3(0.7, 0.7, 0.7), true); // body
    AddMeshToList(square5);
    Mesh* square6 = object2D::CreateSquare("square6", corner, 30, glm::vec3(0.5, 0, 0.5), true); // big wheel
    AddMeshToList(square6);
    Mesh* square7 = object2D::CreateSquare("square7", corner, 30, glm::vec3(0.5, 0, 0.5), true); // big wheel
    AddMeshToList(square7);
    Mesh* square8 = object2D::CreateHalo("square8", corner, 30, glm::vec3(1, 1, 1)); //halo
    AddMeshToList(square8);
    Mesh* square9 = object2D::CreateSquare("square9", corner, 20, glm::vec3(0.4, 0.4, 0.4), true); //small wheel
    AddMeshToList(square9);
    Mesh* square10 = object2D::CreateSquare("square10", corner, 20, glm::vec3(0.4, 0.4, 0.4), true); //small wheel
    AddMeshToList(square10);
// <----------------------------------------------------------------------------------------------------------- BONUS
//BACKGROUND
    Mesh* backSquare = object2D::CreateSquare("backSquare", corner, resolution.y, glm::vec3(0.4f, 0.3f, 0.5f), true);
    AddMeshToList(backSquare);
// WEED
    Mesh* square0 = object2D::CreateSquare("square0", corner, squareSide, glm::vec3(0.3f, 0.6f, 0.1), true);
    AddMeshToList(square0);
//PURPLE SUN
    Mesh* circleSun = object2D::CreateCircle("circleSun", glm::vec3(700, 200, 0), 100, glm::vec3(0.7f, 0.20f, 0.40f));
    AddMeshToList(circleSun);
// HITBOX
    Mesh* square = object2D::CreateSquare("square", glm::vec3(0, 0, 0), 180, glm::vec3(0.4f, 0.3f, 0.5f));
    AddMeshToList(square);
// BODY
    Mesh* triangle1 = object2D::CreateTriangle("triangle1", glm::mat3(30, 0, 0, 
                                                                       80, 0, 0, 
                                                                        55, 120, 0), glm::vec3(0.40f, 0.20f, 0.14f));
    AddMeshToList(triangle1);
// WINGS
    Mesh* triangle2 = object2D::CreateTriangle("triangle2", glm::mat3(0, 40, 0,
                                                                       45, 50, 0,
                                                                        50, 80, 0), glm::vec3(0.40f, 0.20f, 0.14f));
    AddMeshToList(triangle2);

    Mesh* triangle3 = object2D::CreateTriangle("triangle3", glm::mat3(120, 40, 0,
                                                                      65, 50, 0, 
                                                                        60, 80, 0), glm::vec3(0.40f, 0.20f, 0.14f));
    AddMeshToList(triangle3);
// CHOCK
    Mesh* triangle4 = object2D::CreateTriangle("triangle4", glm::mat3(45, 140, 0,
                                                                       55, 170, 0,
                                                                        65, 140, 0), glm::vec3(1.0f, 1.0f, 0.2f));
    AddMeshToList(triangle4);
// HEAD
    Mesh* circle= object2D::CreateCircle("circle", glm::vec3(55, 120, 0), 25, glm::vec3(0.40f, 0.60f, 0.20f));
    AddMeshToList(circle);
// LIVES
    Mesh* circle1 = object2D::CreateCircle("circle1", glm::vec3(resolution.x - 120, resolution.y - 50, 0), 15, glm::vec3(1.0f, 0.2f, 0.2f));
    AddMeshToList(circle1);
    Mesh* circle2 = object2D::CreateCircle("circle2", glm::vec3(resolution.x - 80, resolution.y - 50, 0), 15, glm::vec3(1.0f, 0.2f, 0.2f));
    AddMeshToList(circle2);
    Mesh* circle3 = object2D::CreateCircle("circle3", glm::vec3(resolution.x - 40, resolution.y - 50, 0), 15, glm::vec3(1.0f, 0.2f, 0.2f));
    AddMeshToList(circle3);
// BULLETS
    Mesh* square1 = object2D::CreateSquare("square1", glm::vec3(resolution.x - 120, resolution.y - 100, 0), 10, glm::vec3(0.4f, 0.8f, 0.2f), true);
    AddMeshToList(square1);
    Mesh* square2 = object2D::CreateSquare("square2", glm::vec3(resolution.x - 80, resolution.y - 100, 0), 10, glm::vec3(0.4f, 0.8f, 0.2f), true);
    AddMeshToList(square2);
    Mesh* square3 = object2D::CreateSquare("square3", glm::vec3(resolution.x - 40, resolution.y - 100, 0), 10, glm::vec3(0.4f, 0.8f, 0.2f), true);
    AddMeshToList(square3);
// SCORE
    Mesh* square11 = object2D::CreateSquare("square11", glm::vec3(resolution.x - 200, resolution.y - 150, 0), 20, glm::vec3(0.0f, 0.5f, 1.0f));
    AddMeshToList(square11);
    Mesh* square12 = object2D::CreateSquare("square12", glm::vec3(resolution.x - 200, resolution.y - 150, 0), 20, glm::vec3(0.0f, 0.3f, 1.0f), true);
    AddMeshToList(square12);
// CURSOR
    Mesh* circle4 = object2D::CreateCircle("circle4", glm::vec3(cursorX, cursorY, 0), 3, glm::vec3(1.0f, 0.0f, 0.0f));
    AddMeshToList(circle4);
    Mesh* circle5 = object2D::CreateEmptyCircle("circle5", glm::vec3(cursorX, cursorY, 0), 13, glm::vec3(1.0f, 0.0f, 0.0f));
    AddMeshToList(circle5);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    angularStepHalo += deltaTimeSeconds * 10;

    if ((int)score == 20) {
        tr->RenderText("YOU WON!", 300, 300, 1, glm::vec3(1, 0.2, 1));
        tr->RenderText("SCORE: " + std::to_string((int)score) + " GG! ", 400, 200, 0.7, glm::vec3(0, 0, 0.8));
    }
    else {
        if (livesLeft == 0) {
            tr->RenderText("GAME OVER", 300, 300, 1, glm::vec3(1, 0, 0));
            tr->RenderText("SCORE: " + std::to_string((int)score) + " GG! ", 400, 200, 0.7, glm::vec3(0, 0, 0.8));
        }
        else {

            //Shot 5 ducks -> next lvl
            if (ducksShot % 5 == 0 && levelUp && outOfScreen &&  !roboOnScreen) {
                if (timerLevelUp < 5) {
                    tr->RenderText("YOU SHOT " + std::to_string(ducksShot) + " DUCKS!", 400, 200, 0.4, glm::vec3(0, 0.8, 0));
                    tr->RenderText("YOU LEVELED UP!", 400, 300, 0.4, glm::vec3(0, 0.6, 0.6));
                    tr->RenderText("DUCK SPEED INCREASED!", 400, 400, 0.4, glm::vec3(0.6, 0.6, 0));
                    timerLevelUp += deltaTimeSeconds;
                }
                else {
                    timerLevelUp = 0;
                    levelUp = false;
                }
            } else {
                // BONUS ----> CREATE ROBO
                if (dead && outOfScreen) { // rata e impuscata si a iesit de pe ecran
                    roboOnScreen = true;
                    angularStep += deltaTimeSeconds * 10;
                    roboTranslateX += deltaTimeSeconds * 500;
                    if (roboTranslateX >= resolution.x) {
                        roboOnScreen = false;
                        roboTranslateX = 0;
                        angularStep = 0;
                    }
                    if (roboOnScreen) {
                        if (roboTranslateX >= 50 + translateX) {
                            RenderDeadDuck();
                            CreateRobo();
                        }
                        else {
                            CreateRobo();
                        }
                    }
                }

                //Daca a murit sau a scapat si jucatorul mai are vieti ---> randomize duck
                if ((dead || ttl >= ttlMax) && outOfScreen && livesLeft > 0 && roboOnScreen == false) {
                    srand((unsigned)time(NULL));
                    int cadran = (rand() % 5);
                    if (cadran == 1) { // dreapta sus
                        angularStepDuck = 20 + (rand() % 51);
                        dZborX = 1;
                        dZborY = 1;
                        translateX = (rand() % resolution.x);
                        translateY = 0;
                        angle = 90 - angularStepDuck;
                        angularStepDuck = RADIANS(angularStepDuck);
                    }
                    if (cadran == 2) { // dreapta jos
                        angularStepDuck = 110 + (rand() % 51);
                        dZborX = 1;
                        dZborY = -1;
                        translateX = (rand() % resolution.x);
                        translateY = resolution.y;
                        angle = 90 - (180 - angularStepDuck);
                        angularStepDuck = RADIANS(angularStepDuck);
                    }
                    if (cadran == 3) { // stanga jos
                        angularStepDuck = 200 + (rand() % 51);
                        dZborX = -1;
                        dZborY = -1;
                        translateX = resolution.x;
                        translateY = (rand() % resolution.y);
                        angle = 90 - (angularStepDuck - 180);
                        angularStepDuck = RADIANS(-(360 - angularStepDuck));
                    }
                    if (cadran == 4) { // stanga sus
                        angularStepDuck = 290 + (rand() % 51);
                        dZborX = -1;
                        dZborY = 1;
                        translateX = (rand() % resolution.x);
                        translateY = 0;
                        angle = 90 - (360 - angularStepDuck);
                        angularStepDuck = RADIANS(-(360 - angularStepDuck));
                    }
                    dead = false;
                    outOfScreen = false;
                    ttl = 0;
                    bulletsLeft = 3;
                    noBulletsLostLife = false;
                    ttlLostLife = false;
                }

                ttl += deltaTimeSeconds;
                // DEAD DUCK
                if (dead) {
                    translateY -= deltaTimeSeconds * 100;
                    angularStepDuck = 180;
                    angularStepDuck *= 0.0174532925;
                    // HALO BOING DED
                    if (!outOfScreen) {
                        CreateHaloDead(glm::mat3(1), 100, 280, -0.5, -2);
                        CreateHaloDead(glm::mat3(1), 80, 290, 1, -2);
                        CreateHaloDead(glm::mat3(1), 90, 300, -1.5, 2);
                    }
                }
                else {  // NO MO BULLETS --> duck escaped
                    if (bulletsLeft == 0) {
                        if (!noBulletsLostLife && !ttlLostLife) {
                            livesLeft--;
                            noBulletsLostLife = true;

                        }
                        translateY += deltaTimeSeconds * 100; // rata scapa
                        angularStepDuck = 0;
                        angularStepDuck *= 0.0174532925;
                    }
                    else { // ALIVE & TTL REACHED --> duck escaped
                        if (ttl > ttlMax) {
                            if (!ttlLostLife && !noBulletsLostLife) {
                                livesLeft--;
                                ttlLostLife = true;
                            }
                            translateY += deltaTimeSeconds * 100; // rata scapa
                            angularStepDuck = 0;
                            angularStepDuck *= 0.0174532925;
                        }
                        else { // rata isi continua drumul
                            translateX += dZborX * deltaTimeSeconds * speed;
                            translateY += dZborY * deltaTimeSeconds * speed;
                        }
                    }
                }

                // WINGS MOVEMENT
                timerWings += deltaTimeSeconds;
                if (timerWings > 0.5) {
                    timerWings = 0;
                    angularStepWings = 0;
                }
                else {
                    angularStepWings += deltaTimeSeconds * 2;
                }

                //VERIFY COLLISION WITH WINDOW EDGES
               // SUS
                if (80 + translateY >= resolution.y) {
                    if (dead || ttl > ttlMax)
                        outOfScreen = true;
                    dZborY = -1;
                    if (dZborX == -1) { // zboara spre stanga
                        angularStepDuck = -180 + (90 - angle);
                    }
                    else { // zboara spre dreapta
                        angularStepDuck = 180 - (90 - angle);
                    }
                    angle = 90 - angle;
                    angularStepDuck *= 0.0174532925;
                }
                // JOS
                if (80 + translateY <= 0) {
                    if (dead || ttl > ttlMax)
                        outOfScreen = true;
                    dZborY = 1;
                    if (dZborX == -1) { // zboara spre stanga
                        angularStepDuck = -(90 - angle);
                    }
                    else { // zboara spre dreapta
                        angularStepDuck = 90 - angle;
                    }
                    angle = 90 - angle;
                    angularStepDuck *= 0.0174532925;
                }
                // DREAPTA
                if (50 + translateX >= resolution.x) {
                    if (dead || ttl > ttlMax)
                        outOfScreen = true;
                    dZborX = -1;
                    if (dZborY == -1) { //  zboara in jos
                        angularStepDuck = 180 + angle;
                    }
                    else { // zboara in sus
                        angularStepDuck = -angle;
                    }
                    angle = 90 - angle;
                    angularStepDuck *= 0.0174532925;
                }
                // STANGA
                if (50 + translateX <= 0) {
                    if (dead || ttl > ttlMax)
                        outOfScreen = true;
                    dZborX = 1;
                    if (dZborY == -1) { // zboara in jos
                        angularStepDuck = 180 - angle;
                    }
                    else { // zboara in sus
                        angularStepDuck = angle;
                    }
                    angle = 90 - angle; // unghiul cu care va lovi urmatorul perete 
                    angularStepDuck *= 0.0174532925;
                }

                //  BONUS ----> TARGET CURSOR
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(cursorX, resolution.y - cursorY);
                RenderMesh2D(meshes["circle4"], shaders["VertexColor"], modelMatrix);

                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(cursorX, resolution.y - cursorY);
                RenderMesh2D(meshes["circle5"], shaders["VertexColor"], modelMatrix);

                // WEED
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Scale(resolution.x - 150, 2);
                RenderMesh2D(meshes["square0"], shaders["VertexColor"], modelMatrix);

                if (outOfScreen == false) {
                    // HEAD
                    RenderMesh2D(meshes["circle"], shaders["VertexColor"], duckMovement(glm::mat3(1)));

                    // BODY
                    RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], duckMovement(glm::mat3(1)));

                    // LEFT WING 
                    modelMatrix = duckMovement(glm::mat3(1));
                    RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], wingsMovement(modelMatrix, -1));
                    // RIGHT  WING 
                    modelMatrix = duckMovement(glm::mat3(1));
                    RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], wingsMovement(modelMatrix, 1));

                    // CHOCK
                    RenderMesh2D(meshes["triangle4"], shaders["VertexColor"], duckMovement(glm::mat3(1)));
                }
                // LIVES
                for (int i = 0; i < livesLeft; i++) {
                    RenderMesh2D(meshes[lives[i]], shaders["VertexColor"], glm::mat3(1));
                }
                // BULLETS
                for (int i = 0; i < bulletsLeft; i++) {
                    RenderMesh2D(meshes[bullets[i]], shaders["VertexColor"], bulletsPos(glm::mat3(1), i));
                }
                // SCORE
                RenderMesh2D(meshes["square11"], shaders["VertexColor"], scoreInc(glm::mat3(1), 10));
                RenderMesh2D(meshes["square12"], shaders["VertexColor"], scoreInc(glm::mat3(1), score / 2));

                //PURPLE SUN
                RenderMesh2D(meshes["circleSun"], shaders["VertexColor"], glm::mat3(1));

                //BACKGROUND
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Scale(resolution.x - resolution.y, 1);
                RenderMesh2D(meshes["backSquare"], shaders["VertexColor"], modelMatrix);

                if (outOfScreen == false) {
                    // HITBOX
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(30 + translateX, 60 + translateY);
                    modelMatrix *= transform2D::Scale(0.8, 1.1);
                    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
                }
            }
        }
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    cursorX = mouseX;
    cursorY = mouseY;
    glm::ivec2 resolution = window->GetResolution();

    if (click == true) {
        click = false;
        if (bulletsLeft > 0) {
            bulletsLeft--;
            if (!dead && ttl < ttlMax) {
                if (mouseX > ((int)translateX + 30)
                    && mouseX < ((int)translateX + 30 + 144)
                    && ((int)resolution.y - mouseY) > ((int)translateY + 60)
                    && ((int)resolution.y - mouseY) < ((int)translateY + 60 + 198)) {
                    score++;
                    ducksShot++;
                    dead = true;
                    //Shot 5 ducks -> next lvl
                    if (ducksShot % 5 == 0) {
                        speed += (ducksShot / 5) * speed / 5;
                        levelUp = true;
                        timerLevelUp = 0;

                    }
                }
            }
        }
     }

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2)
        click = true;
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

glm::mat3 Tema1::duckMovement(glm::mat3 modelMatrix) {
    modelMatrix *= transform2D::Translate(50 + translateX, 80 + translateY);
    modelMatrix *= transform2D::Translate(50, 80);
    modelMatrix *= transform2D::Rotate(-angularStepDuck);
    modelMatrix *= transform2D::Translate(-50, -80);

    return modelMatrix;
}

glm::mat3 Tema1::wingsMovement(glm::mat3 modelMatrix, int wing) {
        modelMatrix *= transform2D::Translate(50, 80);
        modelMatrix *= transform2D::Rotate(wing * angularStepWings);
        modelMatrix *= transform2D::Translate(-50, -80);

    return modelMatrix;
}

glm::mat3 Tema1::roboMovement(glm::mat3 modelMatrix) {
    modelMatrix *= transform2D::Translate(10, 10);
    modelMatrix *= transform2D::Rotate(-2*angularStep);
    modelMatrix *= transform2D::Translate(-10, -10);

    return modelMatrix;
}

glm::mat3 Tema1::scoreInc(glm::mat3 modelMatrix, float scale) {
    glm::ivec2 resolution = window->GetResolution();
    modelMatrix *= transform2D::Translate(resolution.x - 200, resolution.y - 150);
    modelMatrix *= transform2D::Scale(scale, 1.5);
    modelMatrix *= transform2D::Translate(-(resolution.x - 200), -(resolution.y - 150));

    return modelMatrix;
}

glm::mat3 Tema1::bulletsPos(glm::mat3 modelMatrix, int i) {
    glm::ivec2 resolution = window->GetResolution();
    modelMatrix *= transform2D::Translate(resolution.x - 120 - (i * 40), resolution.y - 100);
    modelMatrix *= transform2D::Scale(1, 2);
    modelMatrix *= transform2D::Translate(-(resolution.x - 120 - (i * 40)), -(resolution.y - 100));

    return modelMatrix;
}

void Tema1::CreateRobo() {
    // HALO
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(60 + roboTranslateX, 320);
    modelMatrix *= transform2D::Translate(10, 10);
    modelMatrix *= transform2D::Rotate(-100 * angularStep);
    modelMatrix *= transform2D::Translate(-10, -10);
    RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);
    // HEAD
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(40 + roboTranslateX, 230); //40
    RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
    // BODY
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20 + roboTranslateX, 130);  //20
    RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);
    // WHEELS
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(30 + roboTranslateX, 100); //30
    RenderMesh2D(meshes["square6"], shaders["VertexColor"], roboMovement(modelMatrix));

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(80 + roboTranslateX, 100); //80
    RenderMesh2D(meshes["square7"], shaders["VertexColor"], roboMovement(modelMatrix));
    // ARMS
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(120 + roboTranslateX, 100); //120
    RenderMesh2D(meshes["square9"], shaders["VertexColor"], roboMovement(modelMatrix));

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0 + roboTranslateX, 100); // 0
    RenderMesh2D(meshes["square10"], shaders["VertexColor"], roboMovement(modelMatrix));
}

void Tema1::CreateHaloDead(glm::mat3 modelMatrix, float X, float Y, float scale, int dir) {
    modelMatrix *= transform2D::Translate(X + translateX, Y + translateY);
    modelMatrix *= transform2D::Translate(10, 10);
    modelMatrix *= transform2D::Scale(scale, scale);
    modelMatrix *= transform2D::Rotate(dir * angularStepHalo);
    modelMatrix *= transform2D::Translate(-10, -10);

    RenderMesh2D(meshes["square8"], shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderDeadDuck() {
    // HEAD
    RenderMesh2D(meshes["circle"], shaders["VertexColor"], DeadDuckMovement(glm::mat3(1)));

    // BODY
    RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], DeadDuckMovement(glm::mat3(1)));

    // LEFT WING 
    RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], DeadDuckMovement(glm::mat3(1)));

    // RIGHT  WING 
    RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], DeadDuckMovement(glm::mat3(1)));

    // CHOCK
    RenderMesh2D(meshes["triangle4"], shaders["VertexColor"], DeadDuckMovement(glm::mat3(1)));
}

glm::mat3 Tema1::DeadDuckMovement(glm::mat3 modelMatrix) {
    modelMatrix *= transform2D::Translate(20 + roboTranslateX, 100 + roboTranslateY);
    modelMatrix *= transform2D::Translate(50, 80);
    modelMatrix *= transform2D::Scale(0.7, 0.6);
    modelMatrix *= transform2D::Rotate(RADIANS(-45));
    modelMatrix *= transform2D::Translate(-50, -80);

    return modelMatrix;
}