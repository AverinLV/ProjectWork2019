#ifndef GAME_API_H
#define GAME_API_H

#ifdef GAME_API_EXPORTS
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif


extern "C" GAME_API void Connect(const char *ip, unsigned short port);
extern "C" GAME_API void Disconnect();
extern "C" GAME_API bool Start();
extern "C" GAME_API bool Stop();
extern "C" GAME_API int Request(unsigned int action_id);
extern "C" GAME_API bool Stat(unsigned int action_id, unsigned int n_got, unsigned int n_tries, unsigned int n_right);


#endif //GAME_API_H
