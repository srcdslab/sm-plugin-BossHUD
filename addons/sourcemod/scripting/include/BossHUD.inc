/**
 * This is the include file for BossHP
 * To check that BossHP is installed and running, verify that the "BossHP" library exists
 */

#if defined _BossHUD_included
	#endinput
#endif
#define _BossHUD_included

#include "CEntity.inc"

enum DisplayType {
	DISPLAY_CENTER = 0,
	DISPLAY_GAME = 1,
	DISPLAY_HINT = 2
}