# SourcePawn Plugin Development Guidelines for BossHUD

## Repository Overview
This repository contains the **BossHUD** plugin for SourceMod, a scripting platform for Source engine games. The plugin displays boss health information and damage statistics to players in real-time through various HUD displays.

## Technical Environment
- **Language**: SourcePawn (`.sp` files compile to `.smx` bytecode)
- **Platform**: SourceMod 1.12+ (minimum compatible version)
- **Compiler**: SourcePawn compiler (spcomp) via SourceKnight build system
- **Build Tools**: SourceKnight (Python-based build system with dependency management)
- **Target Games**: Source engine games

## Project Structure
```
addons/sourcemod/
├── scripting/
│   ├── BossHUD.sp              # Main plugin file (1625 lines)
│   └── include/
│       ├── BossHUD.inc         # Native function definitions for other plugins
│       └── CEntity.inc         # Entity class methodmap
└── translations/
    └── BossHUD.phrases.txt     # Multi-language support (EN/FR/ZH)

.github/workflows/ci.yml        # GitHub Actions CI/CD
sourceknight.yaml              # Build configuration and dependencies
```

## Key Files and Their Purpose

### Main Plugin (`addons/sourcemod/scripting/BossHUD.sp`)
- **Purpose**: Core plugin functionality for boss health display
- **Key Features**:
  - Boss health tracking and HUD display
  - Damage statistics and top hits leaderboard
  - Client preferences and admin commands
  - Multi-display type support (center, game, hint)
  - Integration with external plugins

### Include Files
- **`BossHUD.inc`**: Native function declarations for other plugins to interact with BossHUD
- **`CEntity.inc`**: Methodmap class for entity management using the Basic library

### Dependencies (defined in `sourceknight.yaml`)
- **sourcemod**: Core SourceMod framework
- **multicolors**: Colored chat message support
- **bosshp**: Boss health tracking functionality  
- **loghelper**: Logging utilities
- **basic**: Basic data structure library
- **dynamicchannels**: Dynamic channel management (optional)

## Code Style & Standards

### SourcePawn Specific Rules
```sourcepawn
#pragma semicolon 1           // Always required
#pragma newdecls required     // Use new declaration syntax

// Naming conventions
ConVar g_cVHudPosition;       // Global variables prefixed with g_
bool g_bShowHealth[MAXPLAYERS + 1];  // Boolean globals with g_b prefix
int g_iEntityId[MAXPLAYERS+1];       // Integer globals with g_i prefix

// Function naming
public void OnPluginStart()    // Public functions in PascalCase
native int BossHUD_GetBossHealth(int bossEnt);  // Natives with plugin prefix
```

### Memory Management Rules
- **CRITICAL**: Use `delete` instead of `.Clear()` for StringMap/ArrayList (prevents memory leaks)
- **CRITICAL**: All SQL queries must be asynchronous using methodmaps
- **GOOD**: No need to check for null when using `delete`
- **GOOD**: Use `delete` for CloseHandle and set to null
- **GOOD**: Use `delete` directly without checking if it's null before delete

### Performance Best Practices
- Minimize timer usage where possible
- Cache expensive operation results
- Use frame skipping for frequent updates (`g_iFramesToSkip`)
- Avoid loops in frequently called functions (like `OnGameFrame`)
- Always aim for O(1) complexity over O(n) when possible

### CI/CD Pipeline
The GitHub Actions workflow (`.github/workflows/ci.yml`):
1. Uses `maxime1907/action-sourceknight@v1` for building
2. Creates distribution packages
3. Automatically tags and releases on main/master branch
4. Uploads build artifacts

### Local Development
- Edit `.sp` files in `addons/sourcemod/scripting/`
- Test on a development server before committing
- Use SourceMod's built-in profiler to check for memory leaks
- Validate that all SQL queries are async and properly escaped

## Common Development Tasks

### Adding New ConVars
```sourcepawn
// In OnPluginStart()
g_cVNewSetting = CreateConVar("sm_bhud_newsetting", "1", "Description", _, true, 0.0, true, 1.0);
g_cVNewSetting.AddChangeHook(OnConVarChange);

// In GetConVars()
g_bNewSetting = g_cVNewSetting.BoolValue;
```

### Adding Translation Support
1. Add phrases to `addons/sourcemod/translations/BossHUD.phrases.txt`
2. Use in code: `CPrintToChat(client, "%T", "phrase_key", client);`

### Creating Native Functions
```sourcepawn
// In AskPluginLoad2()
CreateNative("BossHUD_NewFunction", Native_NewFunction);

// Implementation
public int Native_NewFunction(Handle plugin, int numParams)
{
    int param1 = GetNativeCell(1);
    // Implementation
    return result;
}
```

### Entity Management
```sourcepawn
// Use CEntity methodmap for entity data
CEntity entity = new CEntity();
entity.iIndex = entIndex;
entity.iHealth = health;
entity.SetName("BossName");
```

## Testing and Validation

### Required Checks Before Committing
1. **Compilation**: Plugin compiles without errors/warnings
2. **Memory Leaks**: Use SourceMod profiler to check for leaks
3. **SQL Validation**: All queries are async and injection-safe
4. **Compatibility**: Test with minimum SourceMod version (1.12+)
5. **Performance**: Check server tick rate impact

### Testing Environment Setup
- Install SourceMod 1.12+ on a development server
- Load all required dependencies
- Test with multiple players and various boss entities
- Verify HUD displays work correctly across different display types

## Plugin Integration Points

### Native Functions (for other plugins)
```sourcepawn
BossHUD_GetBossHealth(int bossEnt)        // Get current boss health
BossHUD_GetBossMaxHealth(int bossEnt)     // Get maximum boss health  
BossHUD_GetBossHits(int bossEnt)          // Get total hits on boss
BossHUD_GetBossTopHits(int bossEnt, int maxPlayers, int[] topHits)
BossHUD_IsBossActive(int bossEnt)         // Check if boss is active
BossHUD_GetBossName(int bossEnt, char[] buffer, int maxlen)
```

### Event Hooks
- `OnHealthChanged`: Tracks entity health changes
- `round_end`: Cleanup and statistics display
- `player_connect_client`/`player_disconnect`: Player management

### Command Interface
- `sm_bhud`/`sm_bosshud`: Toggle HUD display for players
- `sm_currenthp`: Admin command to check current HP
- `sm_subtracthp`/`sm_addhp`: Admin commands for health manipulation

## Configuration Management

### Key ConVars
```
sm_bhud_position "x y"              // HUD position coordinates
sm_bhud_color "r g b"               // RGB color values
sm_bhud_displaytype "0-2"           // Display type (center/game/hint)
sm_bhud_health_min/max "value"      // Health detection range
sm_bhud_timeout "seconds"           // HUD fade timeout
sm_bhud_frame_to_skip "frames"      // Performance optimization
```

### Client Preferences
- Uses SourceMod cookies for persistent client settings
- `bhud_showhealth`: Toggle HUD display per client

## Troubleshooting Common Issues

### Build Failures
- Check `sourceknight.yaml` for correct dependency versions
- Ensure all include files are available
- Verify SourceMod version compatibility

### Runtime Issues
- Check server logs for SourceMod errors
- Verify all dependencies are loaded
- Test with `sm plugins list` command
- Use `sm_currenthp` to debug entity detection

### Performance Problems
- Increase `sm_bhud_frame_to_skip` value
- Check for memory leaks with SourceMod profiler
- Monitor server tick rate during boss fights

## Version Control Best Practices
- Use semantic versioning (MAJOR.MINOR.PATCH)
- Update plugin version in `myinfo` structure
- Keep commit messages descriptive
- Tag releases to match plugin versions
- Test thoroughly before merging to main branch

## Dependencies and External Libraries
All dependencies are automatically managed by SourceKnight. Key external dependencies:
- **MultiColors**: For colored chat messages
- **BossHP**: Core boss health tracking
- **Basic**: Data structure utilities
- **DynamicChannels**: Advanced HUD channel management (optional)

When modifying dependencies, update `sourceknight.yaml` and test compatibility thoroughly.
