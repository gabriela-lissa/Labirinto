#ifndef CONFIGS_H
#define CONFIGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ================= SISTEMA ================= */
#ifdef _WIN32
  #include <windows.h>
  #define LIMPAR_TELA system("cls")
  #define DORMIR(ms) Sleep(ms)
#else
  #include <unistd.h>
  static void dormir_ms(int ms) {
      struct timespec ts;
      ts.tv_sec  = ms / 1000;
      ts.tv_nsec = (ms % 1000) * 1000000L;
      nanosleep(&ts, NULL);
  }
  #define LIMPAR_TELA system("clear")
  #define DORMIR(ms) dormir_ms(ms)
#endif

/* ================= CONSTANTES ================= */
#define MAX_LINHAS  40
#define MAX_COLUNAS 40
#define DELAY_MS    400

#endif