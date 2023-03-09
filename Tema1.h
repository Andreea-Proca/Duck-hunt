#pragma once

#include "components/simple_scene.h"
#include <components/text_renderer.h>


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        glm::mat3 duckMovement(glm::mat3 modelMatrix);
        glm::mat3 wingsMovement(glm::mat3 modelMatrix, int wing);
        glm::mat3 roboMovement(glm::mat3 modelMatrix);
        glm::mat3 scoreInc(glm::mat3 modelMatrix, float scale);
        glm::mat3 bulletsPos(glm::mat3 modelMatrix, int i);
        void CreateRobo();
        void CreateHaloDead(glm::mat3 modelMatrix, float X, float Y, float scale, int dir);
        void Tema1::RenderDeadDuck();
        glm::mat3 DeadDuckMovement(glm::mat3 modelMatrix);

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        float angularStepHalo;
        float angularStepDuck;
        float timerWings;
        float angularStepWings;
        float headX, headY;
        int bulletsLeft;
        int livesLeft;
        std::string bullets[3] = { "square1", "square2", "square3" };
        std::string lives[3] = { "circle1", "circle2", "circle3" };
        float score;
        int cursorX, cursorY;
        int dZborX, dZborY;
        bool dead;
        float ttl;
        bool click;
        int angle;
        bool outOfScreen;
        int ducksShot;
        float speed;
        float roboTranslateX, roboTranslateY;
        bool roboOnScreen;
        gfxc::TextRenderer* tr;
        float timerLevelUp;
        bool levelUp;
        bool noBulletsLostLife;
        bool ttlLostLife;
        float ttlMax = 15;

    };
}   // namespace m1
