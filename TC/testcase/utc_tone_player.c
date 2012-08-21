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



#include <tet_api.h>
#include <tone_player.h>

#define MY_ASSERT( fun , test , msg ) \
{\
	if( !test ) \
		dts_fail(fun , msg ); \
}		

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_tone_player_start_p(void);
static void utc_tone_player_start_n(void);
static void utc_tone_player_stop_p(void);
static void utc_tone_player_stop_n(void);

struct tet_testlist tet_testlist[] = {
	{ utc_tone_player_start_p , 1 },
	{ utc_tone_player_start_n , 2 },
	{ utc_tone_player_stop_p, 3 },
	{ utc_tone_player_stop_n, 4 },
	{ NULL, 0 },
};

static void startup(void)
{
	/* start of TC */
}

static void cleanup(void)
{
	/* end of TC */
}

static void utc_tone_player_start_p(void){
	int ret;
	ret = tone_player_start(TONE_TYPE_DEFAULT, SOUND_TYPE_MEDIA,1000, NULL);
	MY_ASSERT(__func__, ret== TONE_PLAYER_ERROR_NONE , "tone_player_start fail");
	dts_pass(__func__, "PASS");		
}
static void utc_tone_player_start_n(void){
	int ret;
	ret = tone_player_start(-1, SOUND_TYPE_MEDIA ,1000, NULL);
	MY_ASSERT(__func__, ret != TONE_PLAYER_ERROR_NONE , " not allow null");
	dts_pass(__func__, "PASS");			
}
static void utc_tone_player_stop_p(void){
	int ret;
	int id;
	ret = tone_player_start(TONE_TYPE_DEFAULT, SOUND_TYPE_MEDIA,1000, &id);
	ret = tone_player_stop(id);
	MY_ASSERT(__func__, ret== TONE_PLAYER_ERROR_NONE , "tone_player_stop fail");
	dts_pass(__func__, "PASS");			
}
static void utc_tone_player_stop_n(void){
	int ret;
	ret = tone_player_stop(-1);
	MY_ASSERT(__func__, ret != TONE_PLAYER_ERROR_NONE , " not allow -1");
	dts_pass(__func__, "PASS");			

}

