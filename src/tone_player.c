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




#define LOG_TAG "TIZEN_N_TONE_PLAYER"

#include <sound_manager.h>
#include <tone_player.h>
#include <mm_sound.h>
#include <mm_sound_private.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <dlog.h>


int _convert_tone_player_error_code(const char *func, int code){
	int ret = TONE_PLAYER_ERROR_NONE;
	char *errorstr = NULL;
	switch(code)
	{
		case MM_ERROR_NONE:
			ret = TONE_PLAYER_ERROR_NONE;
			errorstr = "ERROR_NONE";
			break;
		case TONE_PLAYER_ERROR_INVALID_PARAMETER:
		case MM_ERROR_INVALID_ARGUMENT: 
		case MM_ERROR_SOUND_INVALID_POINTER:
			ret = TONE_PLAYER_ERROR_INVALID_PARAMETER;
			errorstr = "INVALID_PARAMETER";
			break;
		case MM_ERROR_SOUND_INTERNAL:
			ret = TONE_PLAYER_ERROR_INVALID_OPERATION;
			errorstr = "INVALID_OPERATION";
			break;
	}	
	LOGE( "[%s] %s(0x%08x) : core frameworks error code(0x%08x)",func, errorstr, ret, code);
	return ret;
}


int tone_player_start(tone_type_e tone, sound_type_e type, int duration, int *id){
	int ret;
	int player;
	if( tone < TONE_TYPE_DEFAULT || tone > TONE_TYPE_CDMA_SIGNAL_OFF )
		return _convert_tone_player_error_code(__func__, TONE_PLAYER_ERROR_INVALID_PARAMETER);
	
	ret = mm_sound_play_tone(tone, type , 1, duration, &player);

	if( ret == 0 && id != NULL)
		*id = player;		
	return _convert_tone_player_error_code(__func__, ret);
}

int tone_player_stop(int id){
	return _convert_tone_player_error_code(__func__, mm_sound_stop_sound(id));
}

