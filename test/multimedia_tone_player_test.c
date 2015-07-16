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
#include <getopt.h>

#define TONE_FIRST          TONE_TYPE_DTMF_0
#define TONE_LAST           TONE_TYPE_USER_DEFINED_HIGH_FRE

static GMainLoop *g_mainloop = NULL;
static GThread *event_thread;

gpointer GmainThread(gpointer data) {
	g_mainloop = g_main_loop_new (NULL, 0);
	g_main_loop_run (g_mainloop);

	return NULL;
}

void help()
{
	printf("Usage : ");
	printf("multimedia_tone_player_test [OPTION]\n\n"
		   "  -f, --from                from which tone type\n"
		   "  -t, --to                  to which tone type\n"
		   "  -d, --duration            duration(ms)\n"
		   "  -s, --sleep               sleep time after play start(ms)\n"
		   "  -h, --help                help\n");
}

void tone_play_test(int from, int to, int duration, int sleep_time)
{
	int i ;

	printf("From : %2d,   To : %2d,    Duration : %4d,  sleep_time : %4d\n", from, to, duration, sleep_time);

	if (from < TONE_FIRST || to < TONE_FIRST || duration < 0 || from > to || from > TONE_LAST || to > TONE_LAST || sleep_time < 0) {
		printf("Wrong Parameter\n");
		return;
	}

	for(i = from ;i <= to ;i++) {
		printf("Play Tone : %d\n", i);
		tone_player_start(i, SOUND_TYPE_MEDIA , duration, NULL);
		usleep(sleep_time * 1000);
	}
}

int main(int argc, char** argv)
{
	GError *gerr = NULL;
	int from = TONE_TYPE_DTMF_0, to = TONE_TYPE_DTMF_S;
	int duration = 500, sleep_time = -1;

	while (1) {
		int opt;
		int opt_idx = 0;

		static struct option long_options[] =
		{
			{"from"    , required_argument, 0, 'f'},
			{"to"      , required_argument, 0, 't'},
			{"duration", required_argument, 0, 'd'},
			{"sleep"   , required_argument, 0, 's'},
			{"help"    , no_argument      , 0, 'h'},
			{ 0, 0, 0, 0 }
		};

		if ((opt = getopt_long(argc, argv, "f:t:d:s:h", long_options, &opt_idx)) == -1)
			break;

		switch (opt) {
			case 'f':
				from = atoi(optarg);
				break;
			case 't':
				to = atoi(optarg);
				break;
			case 'd':
				duration = atoi(optarg);
				break;
			case 's':
				sleep_time = atoi(optarg);
				break;
			case 'h':
			default:
				help();
				return 0;
		}
	}

	if (sleep_time == -1)
		sleep_time = duration;

	if (!g_thread_supported())
		g_thread_init(NULL);

	event_thread = g_thread_create(GmainThread, NULL, 1, &gerr);

	tone_play_test(from, to, duration, sleep_time);

	return 0;
}
