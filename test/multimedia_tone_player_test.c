/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/



#include <stdio.h>
#include <tone_player.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static GMainLoop *g_mainloop = NULL;
static GThread *event_thread;

gpointer GmainThread(gpointer data){
	g_mainloop = g_main_loop_new (NULL, 0);
	g_main_loop_run (g_mainloop);

	return NULL;
}

void tone_play_test(){
	int i ;

	for( i =0 ; i <= 106 ; i++){
		printf("play %d sound\n", i);
		tone_player_start(i, SOUND_TYPE_MEDIA ,500,NULL);
		usleep(1000);

	}

//	tone_player_start(SOUND_TONE_DTMF_C, SOUND_TYPE_MEDIA ,100000,NULL);
	sleep(1000);
}

int main(int argc, char**argv)
{
	if( !g_thread_supported() )
	{
		g_thread_init(NULL);
	}

	GError *gerr = NULL;
	event_thread = g_thread_create(GmainThread, NULL, 1, &gerr);

	tone_play_test();
	return 0;
}
