#include "AudioHandler.hpp"
#include <iostream>
#include <raylib.h>

void AudioHandler::Init() {
  InitAudioDevice();
  m_CurrenntMusic = LoadMusicStream(m_BgMusicPath);
  PlayMusicStream(m_CurrenntMusic);
  std::cout << "Music is Loaded\n";
}

void AudioHandler::UnloadMusic() {
  UnloadMusicStream(m_CurrenntMusic);
  CloseAudioDevice();
}

void AudioHandler::PlayMusic() { UpdateMusicStream(m_CurrenntMusic); }

void AudioHandler::LoadNewSong(const char* a_MusicPath) {
  PauseMusicStream(m_CurrenntMusic);
  m_CurrenntMusic = LoadMusicStream(a_MusicPath);
  PlayMusicStream(m_CurrenntMusic);
}

void AudioHandler::UpdateSong() {
  m_isPlaying = !m_isPlaying;

  if (m_isPlaying) PauseMusicStream(m_CurrenntMusic);
  else PlayMusicStream(m_CurrenntMusic);
}
