
#pragma once

//
// OpenAL管理
//

#include <string>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include "wav.hpp"
#include "vector.hpp"


#if defined (_MSC_VER)
#pragma comment (lib, "openal32.lib")
#endif


namespace {

// OpenALの初期化と後始末を代行
class Audio {
  ALCdevice*  device_;
  ALCcontext* context_;

  
public:
  Audio() {
    DOUT << "Audio()" << std::endl;
    
    // OpenALの初期化
    device_  = alcOpenDevice(nullptr);
    context_ = alcCreateContext(device_, nullptr);
    alcMakeContextCurrent(context_);
  }

  ~Audio() {
    DOUT << "~Audio()" << std::endl;

    // OpenALの後始末
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context_);
    alcCloseDevice(device_);
  }

  // このクラスはコピー禁止
  Audio(const Audio&) = delete;
  Audio& operator=(const Audio&) = delete;

  
  // リスナーの位置を変更
  // x, y, z →位置
  static void lisnerPosition(const float x, const float y, const float z) {
    ALfloat listener_pos[] = { x, y, z };
    alListenerfv(AL_POSITION, listener_pos);
  }

  // pos →位置
  static void lisnerPosition(const Vec3f& pos) {
    lisnerPosition(pos.x(), pos.y(), pos.z());
  }

  // リスナーの向きを変更
  // at_x, at_y, at_z →向いている方向をあらわすベクトル
  // up_x, up_y, up_z →上方向をあらわすベクトル
  static void lisnerOrientation(const float at_x, const float at_y, const float at_z,
                                const float up_x, const float up_y, const float up_z) {
    ALfloat listener_orientation[] = { at_x, at_y, at_z,
                                       up_x, up_y, up_z };
    alListenerfv(AL_ORIENTATION, listener_orientation);
  }

  // at →向いている方向をあらわすベクトル
  // up →上方向をあらわすベクトル
  static void lisnerOrientation(const Vec3f& at, const Vec3f& up) {
    lisnerOrientation(at.x(), at.y(), at.z(),
                      up.x(), up.y(), up.z());
  }

  // リスナーの移動速度を変更
  // x, y, z →移動速度
  static void lisnerVerocity(const float x, const float y, const float z) {
    ALfloat listener_velocity[] = { x, y, z };
    alListenerfv(AL_VELOCITY, listener_velocity);
  }

  // vec →移動速度
  static void lisnerVerocity(const Vec3f& vec) {
    lisnerVerocity(vec.x(), vec.y(), vec.z());
  }
  
};


// バッファの管理を代行
class Buffer {
  ALuint id_;


public:
  explicit Buffer(const std::string& path) {
    DOUT << "Buffer()" << std::endl;

    // バッファを１つ確保
    alGenBuffers(1, &id_);

    // WAVファイルの読み込み
    Wav wav_data(path);

    // 波形データをバッファにコピー
    alBufferData(id_,
                 wav_data.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
                 wav_data.data(),
                 wav_data.size(),
                 wav_data.sampleRate());
  }

  ~Buffer() {
    DOUT << "~Buffer()" << std::endl;

    // バッファの後始末
    alDeleteBuffers(1, &id_);
  }

  // このクラスはコピー禁止
  Buffer(const Buffer&) = delete;
  Buffer& operator=(const Buffer&) = delete;

  
  // バッファの識別子
  ALuint id() const { return id_; }
  
};


// ソースの管理を代行
class Source {
  ALuint id_;


public:
  Source() {
    DOUT << "Source()" << std::endl;

    // ソースを１つ確保
    alGenSources(1, &id_);
  }

  ~Source() {
    DOUT << "~Source()" << std::endl;

    // ソースの後始末
    unbindBuffer();
    alDeleteSources(1, &id_);
  }

  // このクラスはコピー禁止
  Source(const Source&) = delete;
  Source& operator=(const Source&) = delete;

  
  ALuint name() const { return id_; }

  
  // ソースにバッファを割り当てる
  void bindBuffer(const Buffer& buffer) const {
    alSourcei(id_, AL_BUFFER, buffer.id());
  }

  // ソースに割り当てられたバッファを解除
  void unbindBuffer() const {
    alSourcei(id_, AL_BUFFER, 0);
  }


  // 再生開始
  void play() const {
    alSourcePlay(id_);
  }

  // 再生停止
  void stop() const {
    alSourceStop(id_);
  }

  // 一時停止(この後、再生すると続きからになる)
  void pause() const {
    alSourcePause(id_);
  }

  // 音量変更(value: 0.0f~)
  void gain(const float value) const {
    alSourcef(id_, AL_GAIN, value);
  }

  // 再生ピッチ変更(value: 0.0f~)
  void pitch(const float value) const {
    alSourcef(id_, AL_PITCH, value);
  }

  // ループのON/OFF
  // value: trueでループON、falseでループOFF
  void looping(const bool value) const {
    alSourcei(id_, AL_LOOPING, value ? AL_TRUE : AL_FALSE);
  }

  // ソース位置の変更
  // x, y, z →位置
  void position(const float x, const float y, const float z) const {
    ALfloat source_pos[] = { x, y, z };
    alSourcefv(id_, AL_POSITION, source_pos);
  }

  // pos →位置
  void position(const Vec3f& pos) const {
    position(pos.x(), pos.y(), pos.z());
  }

  // ソースの移動速度を変更
  // x, y, z →移動速度
  void verocity(const float x, const float y, const float z) const {
    ALfloat source_velocity[] = { x, y, z };
    alSourcefv(id_, AL_VELOCITY, source_velocity);
  }

  // pos →移動速度
  void verocity(const Vec3f& vec) const {
    verocity(vec.x(), vec.y(), vec.z());
  }

  // 再生中??
  bool isPlaying() const {
    ALint state;
    alGetSourcei(id_, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
  }

  // 再生位置(秒)
  float currentTime() const {
    ALfloat current_time_sec;
    alGetSourcef(id_, AL_SEC_OFFSET, &current_time_sec);
    return current_time_sec;
  }
};


class Media {
  Buffer buffer_;
  Source source_;
  

public:
  explicit Media(const std::string& path) :
    buffer_(path)
  {
    DOUT << "Media()" << std::endl;

    source_.bindBuffer(buffer_);
  }
  
  ~Media() {
    DOUT << "~Media()" << std::endl;
  }

  // このクラスはコピー禁止
  Media(const Media&) = delete;
  Media& operator=(const Media&) = delete;

  
  // 再生開始
  void play() const {
    source_.play();
  }

  // 再生停止
  void stop() const {
    source_.stop();
  }

  // 一時停止(この後、再生すると続きからになる)
  void pause() const {
    source_.pause();
  }

  // 音量変更(value: 0.0f~)
  void gain(const float value) const {
    source_.gain(value);
  }

  // 再生ピッチ変更(value: 0.0f~)
  void pitch(const float value) const {
    source_.pitch(value);
  }

  // ループのON/OFF
  // value: trueでループON、falseでループOFF
  void looping(const bool value) const {
    source_.looping(value);
  }

  // ソース位置の変更
  // x, y, z →位置
  void position(const float x, const float y, const float z) const {
    source_.position(x, y, z);
  }

  // pos →位置
  void position(const Vec3f& pos) const {
    source_.position(pos);
  }

  // ソースの移動速度を変更
  // x, y, z →移動速度
  void verocity(const float x, const float y, const float z) const {
    source_.verocity(x, y, z);
  }

  // pos →移動速度
  void verocity(const Vec3f& vec) const {
    source_.verocity(vec);
  }

  // 再生中??
  bool isPlaying() const {
    return source_.isPlaying();
  }

  // 再生位置(秒)
  float currentTime() const {
    return source_.currentTime();
  }
};


}
