#pragma once
#include <raylib.h>

class AudioHandler {
  public:
  void Init();
  void UpdateSong();
  void LoadNewSong(const char* a_MusicPath);
  void UnloadMusic();
  void PlayMusic();

  // music flags
  bool m_isPlaying = true;

  // Music Paths
  const char* m_BgMusicPath = "../../sound/music/music.mp3";

  Music m_CurrenntMusic;
};
