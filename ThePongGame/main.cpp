#include "raylib.h"
#include <bits/stdc++.h>



using namespace std;


int main(void)
{
    //screen settings
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int screenFps = 240;
    const Rectangle PaintArea = { 220, 10, screenWidth - 230.0f, screenHeight - 20.0f };
    InitWindow(screenWidth, screenHeight, "PONG GAME");
    SetTargetFPS(screenFps); 

    bool TwoPlayer;
    bool Started = false;

    Rectangle GameMode = {screenWidth/2-200/2 , screenHeight/2-75/2 , 200 , 75};
    Vector2 PlayerSize = {15,50};
    Vector2 Player1Pos = {50-PlayerSize.x/2,screenHeight/2-PlayerSize.y/2};
    Vector2 Player2Pos = {screenWidth-50-PlayerSize.x/2,screenHeight/2-PlayerSize.y/2};
    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    Vector2 ballSpeed = { 2.00f, 2.00f }; 
    int ballRadius = 5;
    
    int player1score=0;
    int player2score=0; 
    
    //main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
       if (Started==false){
            BeginDrawing();
            
            ClearBackground(RAYWHITE);
            DrawRectangleV({GameMode.x,GameMode.y},{GameMode.width,GameMode.height}, LIGHTGRAY);
            DrawRectangleV({GameMode.x,GameMode.y+100},{GameMode.width,GameMode.height}, LIGHTGRAY);
            DrawText("1 PLAYER",GameMode.x,GameMode.y + (GameMode.height/2/2), 40 ,BLACK);
            DrawText("2 PLAYER",GameMode.x,GameMode.y+100 + (GameMode.height/2/2), 40 ,BLACK);
            DrawText("The Classic Pong Game", GameMode.x-200,GameMode.y-125,50,BLACK);
            DrawText("Made By FakePlosive",10,GetScreenHeight()-25,16,GREEN);
            Vector2 MousePoint = GetMousePosition();
            if (CheckCollisionPointRec(MousePoint, {GameMode.x,GameMode.y,GameMode.width,GameMode.height}))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    Started = true;
                    TwoPlayer = false;
                }
            }    

            if (CheckCollisionPointRec(MousePoint, {GameMode.x,GameMode.y+100,GameMode.width,GameMode.height}))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    Started = true;
                    TwoPlayer = true;
                }
            }   
            EndDrawing();
       }else{
        //exit
        if (IsKeyDown(KEY_E)){
            ballSpeed = { 2.00f, 2.00f }; 
            ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
            Player1Pos = {50-PlayerSize.x/2,screenHeight/2-PlayerSize.y/2};
            Player2Pos = {screenWidth-50-PlayerSize.x/2,screenHeight/2-PlayerSize.y/2};
            player1score = 0;
            player2score = 0;
            Started = false;
        }
        //Player control
        if (IsKeyDown(KEY_W) && Player1Pos.y > 0) Player1Pos.y -= 1.5f;
        if (IsKeyDown(KEY_S) && Player1Pos.y + PlayerSize.y <= screenHeight) Player1Pos.y += 1.5f;
    
        if(TwoPlayer==true){
            if (IsKeyDown(KEY_UP) && Player2Pos.y > 0) Player2Pos.y -= 1.5f;
            if (IsKeyDown(KEY_DOWN) && Player2Pos.y + PlayerSize.y <= screenHeight) Player2Pos.y += 1.5f;
        }else{
        
            if(ballPosition.y>=Player2Pos.y) Player2Pos.y += 1.5f;
            if(ballPosition.y<=Player2Pos.y) Player2Pos.y -= 1.5f;
        }
        //ball move
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;


        BeginDrawing();
            ClearBackground(RAYWHITE);

            // FOR DEBUGGING
            DrawText("Press E to exit",10,GetScreenHeight()-25,16,GREEN);
            DrawText(to_string(player1score).c_str(),300,15,40,BLACK);
            DrawText(to_string(player2score).c_str(),500,15,40,BLACK);
            // SHOW X Y POSTION OF MOUSE

            
            //game win or lose
            if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
            if ((ballPosition.x >= (GetScreenWidth() - ballRadius))) {
                ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
                ballSpeed.x *= -1;
                ballSpeed.y *= -1;
                player1score++;
            }
            if ((ballPosition.x <= ballRadius)) {
                ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
                ballSpeed.x *= -1;
                ballSpeed.y *= -1;
                player2score++;
            }

            //Balls vs player
            if (CheckCollisionCircleRec(ballPosition, ballRadius, {Player1Pos.x , Player1Pos.y , PlayerSize.x , PlayerSize.y}))
            {
                ballSpeed.x *= -1.00f;
                ballSpeed.y *= -1.00f;
            }

            if (CheckCollisionCircleRec(ballPosition, ballRadius, {Player2Pos.x , Player2Pos.y , PlayerSize.x , PlayerSize.y}))
            {
                ballSpeed.x *= -1.00f;
                ballSpeed.y *= -1.00f;
            }
            

            DrawCircleV(ballPosition, ballRadius, BLACK); // BALLS
            //Players
            DrawRectangleV(Player1Pos,PlayerSize,BLACK);
            DrawRectangleV(Player2Pos,PlayerSize,BLACK);
        EndDrawing();

        

       }
    }
    CloseWindow();   






    return 0;
}