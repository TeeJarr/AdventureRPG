
/*******************************************************************************************
 *
 *   LayoutName v1.0.0 - Tool Description
 *
 *   LICENSE: Propietary License
 *
 *   Copyright (c) 2022 raylib technologies. All Rights Reserved.
 *
 *   Unauthorized copying of this file, via any medium is strictly prohibited
 *   This project is proprietary and confidential unless the owner allows
 *   usage in any other form by expresely written permission.
 *
 **********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void LabelButton009(); // LabelButton: LabelButton009 logic
static void LabelButton010(); // LabelButton: LabelButton010 logic
static void LabelButton013(); // LabelButton: LabelButton013 logic
static void LabelButton014(); // LabelButton: LabelButton014 logic
static void LabelButton015(); // LabelButton: LabelButton015 logic
static void LabelButton016(); // LabelButton: LabelButton016 logic
static void LabelButton017(); // LabelButton: LabelButton017 logic
static void LabelButton018(); // LabelButton: LabelButton018 logic
static void LabelButton019(); // LabelButton: LabelButton019 logic
static void LabelButton020(); // LabelButton: LabelButton020 logic
static void LabelButton021(); // LabelButton: LabelButton021 logic
static void LabelButton022(); // LabelButton: LabelButton022 logic
static void LabelButton023(); // LabelButton: LabelButton023 logic
static void LabelButton024(); // LabelButton: LabelButton024 logic
static void LabelButton029(); // LabelButton: LabelButton029 logic

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
  // Initialization
  //---------------------------------------------------------------------------------------
  int screenWidth  = 800;
  int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "layout_name");

  // layout_name: controls initialization
  //----------------------------------------------------------------------------------
  // Const text
  const char* BarText            = "";            // PROGRESSBAR: Exp Bar
  const char* LabelButton009Text = "Lv.";         // LABELBUTTON: LabelButton009
  const char* LabelButton010Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton010
  const char* GroupBox011Text    = "Inventory";   // GROUPBOX: GroupBox011
  const char* GroupBox012Text    = "Stats";       // GROUPBOX: GroupBox012
  const char* LabelButton013Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton013
  const char* LabelButton014Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton014
  const char* LabelButton015Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton015
  const char* LabelButton016Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton016
  const char* LabelButton017Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton017
  const char* LabelButton018Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton018
  const char* LabelButton019Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton019
  const char* LabelButton020Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton020
  const char* LabelButton021Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton021
  const char* LabelButton022Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton022
  const char* LabelButton023Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton023
  const char* LabelButton024Text = "SAMPLE TEXT"; // LABELBUTTON: LabelButton024
  const char* GroupBox026Text    = "Tools";       // GROUPBOX: GroupBox026
  const char* LabelButton029Text = "100/200";     // LABELBUTTON: LabelButton029

  // Define anchors
  Vector2 anchor01 = {408, 408}; // ANCHOR ID:1

  // Define controls variables
  float BarValue = 0.0f; // ProgressBar: Exp Bar

  // Define controls rectangles
  Rectangle layoutRecs[30] = {
      (Rectangle){anchor01.x + 24, anchor01.y + 24, 72, 72},    // Panel: Panel000
      (Rectangle){anchor01.x + 120, anchor01.y + 120, 72, 72},  // Panel: Panel001
      (Rectangle){anchor01.x + 120, anchor01.y + 216, 72, 72},  // Panel: Panel002
      (Rectangle){anchor01.x + 120, anchor01.y + 24, 72, 72},   // Panel: Panel003
      (Rectangle){anchor01.x + 24, anchor01.y + 120, 72, 72},   // Panel: Panel004
      (Rectangle){anchor01.x + 24, anchor01.y + 312, 72, 72},   // Panel: Panel005
      (Rectangle){anchor01.x + 24, anchor01.y + 216, 72, 72},   // Panel: Panel006
      (Rectangle){anchor01.x + 120, anchor01.y + 312, 72, 72},  // Panel: Panel007
      (Rectangle){anchor01.x + 216, anchor01.y + 368, 216, 16}, // ProgressBar: Exp Bar
      (Rectangle){anchor01.x + 216, anchor01.y + 344, 24, 24},  // LabelButton: LabelButton009
      (Rectangle){anchor01.x + 240, anchor01.y + 344, 216, 24}, // LabelButton: LabelButton010
      (Rectangle){anchor01.x + 0, anchor01.y + 0, 456, 408},    // GroupBox: GroupBox011
      (Rectangle){anchor01.x + 216, anchor01.y + 24, 216, 192}, // GroupBox: GroupBox012
      (Rectangle){anchor01.x + 240, anchor01.y + 48, 96, 24},   // LabelButton: LabelButton013
      (Rectangle){anchor01.x + 240, anchor01.y + 72, 120, 24},  // LabelButton: LabelButton014
      (Rectangle){anchor01.x + 240, anchor01.y + 96, 120, 24},  // LabelButton: LabelButton015
      (Rectangle){anchor01.x + 240, anchor01.y + 120, 120, 24}, // LabelButton: LabelButton016
      (Rectangle){anchor01.x + 336, anchor01.y + 48, 120, 24},  // LabelButton: LabelButton017
      (Rectangle){anchor01.x + 336, anchor01.y + 72, 120, 24},  // LabelButton: LabelButton018
      (Rectangle){anchor01.x + 336, anchor01.y + 96, 120, 24},  // LabelButton: LabelButton019
      (Rectangle){anchor01.x + 336, anchor01.y + 120, 120, 24}, // LabelButton: LabelButton020
      (Rectangle){anchor01.x + 240, anchor01.y + 144, 120, 24}, // LabelButton: LabelButton021
      (Rectangle){anchor01.x + 336, anchor01.y + 144, 120, 24}, // LabelButton: LabelButton022
      (Rectangle){anchor01.x + 240, anchor01.y + 168, 120, 24}, // LabelButton: LabelButton023
      (Rectangle){anchor01.x + 336, anchor01.y + 168, 120, 24}, // LabelButton: LabelButton024
      (Rectangle){anchor01.x + 216, anchor01.y + 232, 216, 16}, // Line: Line025
      (Rectangle){anchor01.x + 216, anchor01.y + 248, 216, 88}, // GroupBox: GroupBox026
      (Rectangle){anchor01.x + 240, anchor01.y + 256, 72, 72},  // Panel: Panel027
      (Rectangle){anchor01.x + 336, anchor01.y + 256, 72, 72},  // Panel: Panel028
      (Rectangle){anchor01.x + 216, anchor01.y + 368, 112, 16}, // LabelButton: LabelButton029
  };
  //----------------------------------------------------------------------------------

  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Implement required update logic
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    // raygui: controls drawing
    //----------------------------------------------------------------------------------
    // Draw controls
    GuiPanel(layoutRecs[0], " ");
    GuiPanel(layoutRecs[1], " ");
    GuiPanel(layoutRecs[2], " ");
    GuiPanel(layoutRecs[3], " ");
    GuiPanel(layoutRecs[4], " ");
    GuiPanel(layoutRecs[5], " ");
    GuiPanel(layoutRecs[6], " ");
    GuiPanel(layoutRecs[7], " ");
    // GuiProgressBar(layoutRecs[8], " ", NULL, " ", 0, 1);
    if (GuiLabelButton(layoutRecs[9], LabelButton009Text)) LabelButton009();
    if (GuiLabelButton(layoutRecs[10], LabelButton010Text)) LabelButton010();
    GuiGroupBox(layoutRecs[11], GroupBox011Text);
    GuiGroupBox(layoutRecs[12], GroupBox012Text);
    if (GuiLabelButton(layoutRecs[13], LabelButton013Text)) LabelButton013();
    if (GuiLabelButton(layoutRecs[14], LabelButton014Text)) LabelButton014();
    if (GuiLabelButton(layoutRecs[15], LabelButton015Text)) LabelButton015();
    if (GuiLabelButton(layoutRecs[16], LabelButton016Text)) LabelButton016();
    if (GuiLabelButton(layoutRecs[17], LabelButton017Text)) LabelButton017();
    if (GuiLabelButton(layoutRecs[18], LabelButton018Text)) LabelButton018();
    if (GuiLabelButton(layoutRecs[19], LabelButton019Text)) LabelButton019();
    if (GuiLabelButton(layoutRecs[20], LabelButton020Text)) LabelButton020();
    if (GuiLabelButton(layoutRecs[21], LabelButton021Text)) LabelButton021();
    if (GuiLabelButton(layoutRecs[22], LabelButton022Text)) LabelButton022();
    if (GuiLabelButton(layoutRecs[23], LabelButton023Text)) LabelButton023();
    if (GuiLabelButton(layoutRecs[24], LabelButton024Text)) LabelButton024();
    GuiLine(layoutRecs[25], " ");
    GuiGroupBox(layoutRecs[26], GroupBox026Text);
    GuiPanel(layoutRecs[27], " ");
    GuiPanel(layoutRecs[28], " ");
    if (GuiLabelButton(layoutRecs[29], LabelButton029Text)) LabelButton029();
    //----------------------------------------------------------------------------------

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
// LabelButton: LabelButton009 logic
static void LabelButton009() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton010 logic
static void LabelButton010() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton013 logic
static void LabelButton013() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton014 logic
static void LabelButton014() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton015 logic
static void LabelButton015() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton016 logic
static void LabelButton016() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton017 logic
static void LabelButton017() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton018 logic
static void LabelButton018() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton019 logic
static void LabelButton019() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton020 logic
static void LabelButton020() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton021 logic
static void LabelButton021() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton022 logic
static void LabelButton022() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton023 logic
static void LabelButton023() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton024 logic
static void LabelButton024() {
  // TODO: Implement control logic
}
// LabelButton: LabelButton029 logic
static void LabelButton029() {
  // TODO: Implement control logic
}
