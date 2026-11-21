# BossHUD (archived)

> [!WARNING]
> **This plugin is no longer maintained.** BossHUD was merged into
> **[sm-plugin-BossHP](https://github.com/srcdslab/sm-plugin-BossHP)** 2.0.0
> (srcdslab/sm-plugin-BossHP#51). Everything BossHUD did (boss and entity health HUD, top hits table,
> rewards, death notice, admin health commands, natives, translations) now lives in a single plugin,
> `BossHP.smx`. Do not run `BossHUD.smx` next to BossHP 2.0.

The last BossHUD release is **3.8.17** (`latest` release of this repository). It is kept for reference
only and will not receive fixes.

## Migrating to BossHP 2.0

There is no compatibility layer: names changed, configs must be updated.

1. Remove `plugins/BossHUD.smx`, `translations/BossHUD.phrases.txt` and
   `cfg/sourcemod/plugin.BossHUD.cfg`.
2. Install the latest [BossHP release](https://github.com/srcdslab/sm-plugin-BossHP/releases) with its
   translations. Delete `cfg/sourcemod/plugin.BossHP.cfg` so it is regenerated with the new cvars.
3. Carry over the cvar values that differ from the new defaults (table below), then restart the server.

### Commands, cookie, files

| BossHUD | BossHP 2.0 |
| --- | --- |
| `BossHUD.smx` | `BossHP.smx` |
| `sm_bhud`, `sm_bosshud` | `sm_bhp` |
| `sm_currenthp`, `sm_subtracthp`, `sm_addhp` | unchanged |
| cookie `bhud_showhealth` | `bosshp_hud` (players' choices reset to enabled) |
| `BossHUD.phrases.txt` | `BossHP.phrases.txt` |
| `BossHUD` library, `BossHUD.inc` | `BossHP` library, `BossHP.inc` |

### Natives

| BossHUD | BossHP 2.0 |
| --- | --- |
| `BossHUD_GetBossHealth` | `BossHP_GetBossHealth` |
| `BossHUD_GetBossMaxHealth` | `BossHP_GetBossMaxHealth` |
| `BossHUD_GetBossName` | `BossHP_GetBossName` |
| `BossHUD_GetBossHits` | `BossHP_GetBossHits` |
| `BossHUD_GetBossHitsCount` | `BossHP_GetBossHitsCount` |
| `BossHUD_GetBossHitsByClient` | `BossHP_GetBossHitsByClient` |
| `BossHUD_GetBossHitsRank` | `BossHP_GetBossHitsRank` |
| `BossHUD_GetBossTopHits` | `BossHP_GetBossTopHits` |
| `BossHUD_IsBossActive` | dropped, use `BossHP_IsBossEnt` |

### Cvars

| BossHUD | BossHP 2.0 |
| --- | --- |
| `sm_bhud_displaytype` | `sm_bosshp_hud_type` |
| `sm_bhud_position` | `sm_bosshp_hud_position` |
| `sm_bhud_color` | `sm_bosshp_hud_color` |
| `sm_bhud_hud_channel` | `sm_bosshp_hud_channel` (health HUD only) |
| _(new)_ | `sm_bosshp_tophits_channel` (DynamicChannels group of the top hits table) |
| `sm_bhud_symbols` | `sm_bosshp_hud_symbols` |
| `sm_bhud_frame_to_skip` | `sm_bosshp_hud_frames` (default `7`, min `1`) |
| `sm_bhud_timeout` | `sm_bosshp_entity_timeout` |
| `sm_bhud_health_min` / `_max` | `sm_bosshp_entity_health_min` / `_max` |
| `sm_bhud_ignore_fakeclients` | `sm_bosshp_ignore_bots` |
| `sm_bhud_tophits_players` | `sm_bosshp_tophits_players` |
| `sm_bhud_tophits_uppertitle` | `sm_bosshp_tophits_uppercase` |
| `sm_bhud_tophits_position` / `_color` | `sm_bosshp_tophits_position` (default `"0.02 0.3"`) / `_color` |
| `sm_bhud_notify_console` | `sm_bosshp_tophits_console` |
| `sm_bhud_tophits_money` | `sm_bosshp_tophits_money` |
| `sm_bhud_tophits_reward` | `sm_bosshp_tophits_reward` |
| `sm_bhud_boss_death_notice` | `sm_bosshp_death_notice` |

Issues and pull requests go to [sm-plugin-BossHP](https://github.com/srcdslab/sm-plugin-BossHP).
