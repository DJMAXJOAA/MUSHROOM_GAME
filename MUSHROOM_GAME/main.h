#pragma once

void Init();
void Update();
void Render();
void WaitRender(clock_t OldTime);
void Release();
int GetKeyEvent();
void KeyProcess(int key);

