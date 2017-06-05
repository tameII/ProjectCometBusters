 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include "SDL.h"

 /* Les données du fichier son chargé */
 Uint8 * sounddata;
 /* La taille du fichier son chargé, en octets */
 Uint32 soundlength;
 /* Position courante de lecture dans le fichier son */
 Uint32 soundpos;

 /* Fonction de rappel qui copie les données sonores dans le tampon audio */
 void mixaudio(void * userdata, Uint8 * stream, int len)
 {
   /* Attention à ne pas déborder lors de la copie */
   Uint32 tocopy = soundlength - soundpos > len ? len : soundlength - soundpos; 

   /* Copie des données sonores dans le tampon audio... */
   memcpy(stream, sounddata + soundpos, tocopy); 

   /* Mise à jour de la position de lecture */
   soundpos += tocopy;
 }

 int main(int argc, char * argv[])
 {
   SDL_AudioSpec desired, obtained, soundfile;
   SDL_AudioCVT cvt; 

   if (SDL_Init(SDL_INIT_AUDIO) == -1) {
     printf("Erreur lors de l'initialisation de SDL!\n");
     return 1;
   }

   /* Son 16 bits stéréo à 44100 Hz */
   desired.freq = 44100;
   desired.format = AUDIO_U16SYS;
   desired.channels = 2;

   /* Le tampon audio contiendra 512 échantillons */
   desired.samples = 512;

   /* Mise en place de la fonction de rappel et des données utilisateur */
   desired.callback = &mixaudio;
   desired.userdata = NULL;

   if (SDL_OpenAudio(&desired, &obtained) != 0) {
     printf("Erreur lors de l'ouverture du périphérique audio: %s\n", SDL_GetError());
     return 1;
   }

   printf("Paramètres audio obtenus: d canaux, fréquence d échantillons.\n", 
 	 obtained.format & 0xff, obtained.channels, obtained.freq, obtained.samples);

   /* Chargement du fichier .wav */
   if (SDL_LoadWAV("KDE_Startup_new.wav", &soundfile, &sounddata, &soundlength) == NULL) {
     printf("Erreur lors du chargement du fichier son: %s\n", SDL_GetError());
     return 1;
   }

   printf("Propriétés du fichier audio: d canaux, fréquence d octets.\n", 
 	 soundfile.format & 0xff, soundfile.channels, soundfile.freq, soundlength);

   /* Conversion vers le format du tampon audio */
   if (SDL_BuildAudioCVT(&cvt, soundfile.format, soundfile.channels, soundfile.freq, 
	 		obtained.format, obtained.channels, obtained.freq) < 0) {
     printf("Impossible de construire le convertisseur audio!\n");
     return 1;
   }

   /* Création du tampon utilisé pour la conversion */
   cvt.buf = malloc(soundlength * cvt.len_mult);
   cvt.len = soundlength;
   memcpy(cvt.buf, sounddata, soundlength);

   /* Conversion... */
   if (SDL_ConvertAudio(&cvt) != 0) {
     printf("Erreur lors de la conversion du fichier audio: %s\n", SDL_GetError());
     return 1;
   }

   /* Libération de l'ancien tampon, création du nouveau,
      copie des données converties, effacement du tampon de conversion */
   SDL_FreeWAV(sounddata);
   sounddata = malloc(cvt.len_cvt);
   memcpy(sounddata, cvt.buf, cvt.len_cvt);
   free(cvt.buf);

   soundlength = cvt.len_cvt;
   printf("Taille du son converti: %d octets\n", soundlength);
   soundpos = 0;

   /* La fonction de rappel commence à être appelée à partir de maintenant. */
   printf("Démarrage de la lecture...\n");
   SDL_PauseAudio(0);

   /* On attend que l'autre thread ait fini la lecture du son... */
   while (soundpos < soundlength);

   /* On cesse d'appeler la fonction de rappel */
   SDL_PauseAudio(1);

   /* Fermer le périphérique audio */
   SDL_CloseAudio();

   SDL_Quit();
   return 0;
 }
