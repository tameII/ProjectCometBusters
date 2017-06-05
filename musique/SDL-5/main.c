 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include "SDL.h"

 /* Les donn�es du fichier son charg� */
 Uint8 * sounddata;
 /* La taille du fichier son charg�, en octets */
 Uint32 soundlength;
 /* Position courante de lecture dans le fichier son */
 Uint32 soundpos;

 /* Fonction de rappel qui copie les donn�es sonores dans le tampon audio */
 void mixaudio(void * userdata, Uint8 * stream, int len)
 {
   /* Attention � ne pas d�border lors de la copie */
   Uint32 tocopy = soundlength - soundpos > len ? len : soundlength - soundpos; 

   /* Copie des donn�es sonores dans le tampon audio... */
   memcpy(stream, sounddata + soundpos, tocopy); 

   /* Mise � jour de la position de lecture */
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

   /* Son 16 bits st�r�o � 44100 Hz */
   desired.freq = 44100;
   desired.format = AUDIO_U16SYS;
   desired.channels = 2;

   /* Le tampon audio contiendra 512 �chantillons */
   desired.samples = 512;

   /* Mise en place de la fonction de rappel et des donn�es utilisateur */
   desired.callback = &mixaudio;
   desired.userdata = NULL;

   if (SDL_OpenAudio(&desired, &obtained) != 0) {
     printf("Erreur lors de l'ouverture du p�riph�rique audio: %s\n", SDL_GetError());
     return 1;
   }

   printf("Param�tres audio obtenus: d canaux, fr�quence d �chantillons.\n", 
 	 obtained.format & 0xff, obtained.channels, obtained.freq, obtained.samples);

   /* Chargement du fichier .wav */
   if (SDL_LoadWAV("KDE_Startup_new.wav", &soundfile, &sounddata, &soundlength) == NULL) {
     printf("Erreur lors du chargement du fichier son: %s\n", SDL_GetError());
     return 1;
   }

   printf("Propri�t�s du fichier audio: d canaux, fr�quence d octets.\n", 
 	 soundfile.format & 0xff, soundfile.channels, soundfile.freq, soundlength);

   /* Conversion vers le format du tampon audio */
   if (SDL_BuildAudioCVT(&cvt, soundfile.format, soundfile.channels, soundfile.freq, 
	 		obtained.format, obtained.channels, obtained.freq) < 0) {
     printf("Impossible de construire le convertisseur audio!\n");
     return 1;
   }

   /* Cr�ation du tampon utilis� pour la conversion */
   cvt.buf = malloc(soundlength * cvt.len_mult);
   cvt.len = soundlength;
   memcpy(cvt.buf, sounddata, soundlength);

   /* Conversion... */
   if (SDL_ConvertAudio(&cvt) != 0) {
     printf("Erreur lors de la conversion du fichier audio: %s\n", SDL_GetError());
     return 1;
   }

   /* Lib�ration de l'ancien tampon, cr�ation du nouveau,
      copie des donn�es converties, effacement du tampon de conversion */
   SDL_FreeWAV(sounddata);
   sounddata = malloc(cvt.len_cvt);
   memcpy(sounddata, cvt.buf, cvt.len_cvt);
   free(cvt.buf);

   soundlength = cvt.len_cvt;
   printf("Taille du son converti: %d octets\n", soundlength);
   soundpos = 0;

   /* La fonction de rappel commence � �tre appel�e � partir de maintenant. */
   printf("D�marrage de la lecture...\n");
   SDL_PauseAudio(0);

   /* On attend que l'autre thread ait fini la lecture du son... */
   while (soundpos < soundlength);

   /* On cesse d'appeler la fonction de rappel */
   SDL_PauseAudio(1);

   /* Fermer le p�riph�rique audio */
   SDL_CloseAudio();

   SDL_Quit();
   return 0;
 }
