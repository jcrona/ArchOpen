/*
*   MediOS project
*   Copyright (c) 2005 by Christophe THOMAS (oxygen77 at free.fr)
*
* All files in this archive are subject to the GNU General Public License.
* See the file COPYING in the source tree root for full license agreement.
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express of implied.
*/

#ifndef __TAG_H
#define __TAG_H

#include <snd_user/tag.h>

#include <snd/playlist.h>

void tag_parse(PLAYLIST_ITEM * item, char * format, char * output,int length);
void tag_clear(TAG * tag);
void tag_free(TAG * tag);

#endif
