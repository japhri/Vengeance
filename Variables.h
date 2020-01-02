#pragma once
#include <Windows.h>

#define OPTION(type, var, value) type var = value // this is for keybinds mostly

struct ColorP
{
public:
	const char* Name;
	float* Ccolor;

	ColorP(const char* name, float* color)
	{
		this->Name = name;
		this->Ccolor = color;
	}
};

typedef struct
{
	int base;
	float add;
	int addon;
	int jitterMode;
	int jitterFlipTicks;
	float jitterRange;
	int spinbotMode;
	float spinbotSpeed;
	float spinbotRange;
} AntiAimSetting;

enum class VariableType
{
	BOOL,
	INT,
	FLOAT,
	STR,
	CLR
};

typedef struct
{
	char name[256];
	VariableType type;
	bool *boolVar;
	int *intVar;
	float *floatVar;
	char *strVar;
	float *clrVar;
} Variable;

class Options
{
public:
	bool allowUntrusted = false;

	/* ESP */
	OPTION(int, antiaim_pitch, 1);
	OPTION(int, antiaim_yaw_real, 1);
	OPTION(int, antiaim_yaw_fake, 5);
	OPTION(int, antiaim_yaw_lbybreakertype, 0);
	OPTION(float, antiaim_yaw_lbybreaker_offset, 110.f);
	OPTION(int, fakelag_ticks, 14);
	OPTION(int, fakelag_whileattack, false);
	OPTION(int, fakelag_lbylag, false);

	bool espEnable = false;
	bool espFriendlyBox = false;
	bool espEnemyBox = false;
	bool espFriendlyName = false;
	bool espEnemyName = false;
	bool espFriendlyHealth = false;
	bool espEnemyHealth = false;
	bool espFriendlyLines = false;
	bool espEnemyLines = false;
	bool espFriendlyWeapon = false;
	bool espEnemyWeapon = false;
	bool espFriendlyIndicators = false;
	bool espEnemyIndicators = false;
	bool espEnemyLagcomp = false;
	float espFriendlyColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float espEnemyColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool espFriendlyGlow = false;
	float glowFriendlyColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool espEnemyGlow = false;
	float glowEnemyColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool espLocalGlow = false;
	float glowLocalColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool espWeaponGlow = false;
	float glowWeaponColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int espFriendlyGlowStyle = 0;
	int espEnemyGlowStyle = 0;
	int espLocalGlowStyle = 0;
	int espWeaponGlowStyle = 0;
	bool espFriendlyShine = false;
	int espFriendlyShineMaterial = 0;
	float espFriendlyShineColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool espEnemyShine = false;
	int espEnemyShineMaterial = 0;
	float espEnemyShineColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool espLocalShine = false;
	int espLocalShineMaterial = 0;
	float espLocalShineColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	/* Chams */

	bool chamsFriendlyEnable = false;
	int chamsFriendlyMaterial = 0;
	float chamsFriendlyColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool chamsEnemyEnable = false;
	int chamsEnemyMaterial = 0;
	float chamsEnemyColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool chamsLocalEnable = false;
	int chamsLocalMaterial = 0;
	float chamsLocalColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool chamsFriendlyXQZEnable = false;
	int chamsFriendlyXQZMaterial = 0;
	float chamsFriendlyXQZColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool chamsEnemyXQZEnable = false;
	int chamsEnemyXQZMaterial = 0;
	float chamsEnemyXQZColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool chamsHandEnable = false;
	int chamsHandMaterial = 0;
	float chamsHandColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool chamsWeaponEnable = false;
	int chamsWeaponMaterial = 0;
	float chamsWeaponColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	int spreadCrosshair = 0;
	float spreadColor[4] = { 0.0f, 0.0f, 0.0f, 0.25f };
	bool thirdperson = false;
	int tpmode = 0;
	bool antiAimLines = false;
	bool antiAimLinesFirstPerson = false;
	bool antiAimInfo = false;
	bool smokeWireframe = false;
	bool bulletTracersEnable = false;
	int bulletTracersMaterial = 5;
	float bulletTracersLifetime = 2.5f;
	float bulletTracersWidth = 1.0f;
	float bulletTracersColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	bool autoWallEsp = false;
	bool peekEsp = false;
	bool multipointEsp = false;

	/* Style */

	bool espOutline = true;
	int espFont = 0;
	int espFontSize = 15;
	int espNameStyle = 0;
	int espHealthTextStyle = 0;
	int espIndicatorStyle = 0;
	bool espIndicatorHover = false;
	int espIndicatorHoverSizeStyle = 0;
	float espIndicatorEdgeDistance = 0.5f;
	float espIndicatorDrawDistance = 0.75f;
	bool espIndicatorFadeEnable = false;
	float espIndicatorFadeSpeed = 1.0f;
	float espIndicatorFadeMinimum = 0.0f;

	/* Misc */

	bool noScopeEnable = false;
	float noScopeColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool bhopEnable = false;
	bool bhopUseSpace = false;
	bool autostrafe = false;
	bool autostrafeWaitForMovement = false;
	bool circlestrafer = false;
	bool fakelag = false;
	bool FakelagEnable = false;
	bool FakelagOnground = true;
	int FakelagMode =2;
	int FakelagAmount = 15;
	bool FakelagShoot = false;
	OPTION(bool, aimbot_enabled, true);
	OPTION(int, aimbot_hitchance, 0);
	OPTION(int, aimbot_mindamage, 1);
	OPTION(int, aimbot_maxplayers, 5);
	OPTION(int, aimbot_mp_slicing, 0);
	OPTION(int, aimbot_delayshot_level, 0);
	OPTION(int, lagcomp_level, 0);
	bool EventLogs = false;
	bool DrawDamage = false;
	bool atlasTag = false;
	bool fovEnable = false;
	float fov = 0.0f;
	float SCAN = 0.0f;
	bool fovRestore = false;
	bool fovRelative = true;

	/* Rage */

	bool ragebotEnable = false;
	bool ragebotAutoFire = false;
	bool ragebotRecoil = false;
	bool ragebotBacktrack = false;
	bool ragebotHitchanceEnable = false;
	float ragebotHitchanceAmount = 0.0f;
	float ragebotPointscale = 0.9f;
	bool ragebotCorrections = false;

	bool ragebotHitboxes[8] = {
		true, true, true, true,
		true, true, true, true
	};

	bool rage_multipoint = true;
	float rage_pointscale = 1.020f;
	float lbydelta = 0.f;
	int lagcomp = 2;
	int backtrack_recordss;
	bool zeusbots;


	/* Anti aim */

	bool antiAimEnable = false;
	int antiAimPitch = 0;
	int antiAimYaw = 0;
	int antiAimFakes = 0;
	bool antiAimFake = true;
	AntiAimSetting antiAimStillReal = { 0, 0.0f, 0, 0, 2, 0.0f, 0, 1.0f, 360.0f };
	AntiAimSetting antiAimStillFake = { 0, 0.0f, 0, 0, 2, 0.0f, 0, 1.0f, 360.0f };
	AntiAimSetting antiAimMovingReal = { 0, 0.0f, 0, 0, 2, 0.0f, 0, 1.0f, 360.0f };
	AntiAimSetting antiAimMovingFake = { 0, 0.0f, 0, 0, 2, 0.0f, 0, 1.0f, 360.0f };
	AntiAimSetting antiAimJumpingReal = { 0, 0.0f, 0, 0, 2, 0.0f, 0, 1.0f, 360.0f };
	AntiAimSetting antiAimJumpingFake = { 0, 0.0f, 0, 0, 2, 0.0f, 0, 1.0f, 360.0f };
	float antiAimPitchCustom = 0.0;
	bool antiAimBreakLBY = false;
	bool antiAimFlipEnable = false;
	bool antiAimFlip = false;
	int antiAimFlipMethod = 0;
	int antiAimFreestandingMethod = 0;
	int antiAimFreestandingQuality = 2;
	int antiAimFreestandingScanQuality = 1;
	float antiAimFreestandingSmoothing = 0.0f;
	bool antiAimFreestandingStutteredUpdates = false;

	float rage_mindmg = 0.f;
	int ragehitbox = 0;
	int bones = 0;
	bool silentaim;

	bool hitSoundEnable = false;

	float test1 = 0.0f;
	float test2 = 0.0f;
	bool test3 = false;
	bool test4 = false;
	bool test5;
	float leftTurnTimer = 0.0f;
	float rightTurnTimer = 0.0f;
	float resetTurnTimer = 0.0f;

	OPTION(ButtonCode_t, tpkey, BUTTON_CODE_NONE);
	OPTION(ButtonCode_t, antiAimFlipKey, BUTTON_CODE_NONE);
	OPTION(ButtonCode_t, cstrafeKey, BUTTON_CODE_NONE);

	std::vector<Variable> variables;

	void RegisterVariable(const char *name, VariableType type, void *addr)
	{
		Variable variable;
		strcpy_s(variable.name, 256, name);
		variable.type = type;
		switch (type)
		{
		case VariableType::BOOL:
			variable.boolVar = (bool*)addr;
			break;
		case VariableType::INT:
			variable.intVar = (int*)addr;
			break;
		case VariableType::FLOAT:
			variable.floatVar = (float*)addr;
			break;
		case VariableType::STR:
			variable.strVar = (char*)addr;
			break;
		case VariableType::CLR:
			variable.clrVar = (float*)addr;
			break;
		}
		variables.push_back(variable);
	}

	void RegisterAntiAimSetting(char *name, AntiAimSetting *addr);

	Variable *FindVariable(char *name)
	{
		std::vector<Variable>::iterator iter;

		for (iter = variables.begin(); iter != variables.end(); iter++) {
			if (!strcmp(iter->name, name)) {
				return &*iter;
			}
		}

		return NULL;
	}

	char *configsFolderPath = "csgo\\atlasconfigs";

	std::vector<std::string> configs;

	void FindConfigs();
	void LoadConfig(const char *name);
	void SaveConfig(const char *name);
	void DeleteConfig(const char *name);
};


static const char *fonts[4] = { "Arial", "Mont", "Comfortaa", "Quicksand" };
static const int fontsCount = 4;

static const char *nameStyles[2] = { "Top", "Bottom" };
static const int nameStylesCount = 2;

static const char *healthTextStyles[3] = { "Off", "Bottom", "Side" };
static const int healthTextStylesCount = 3;

static const char *indicatorStyles[2] = { "Top-down radar", "Point at target" };
static const int indicatorStylesCount = 2;

static const char *indicatorHoverSizeStyles[2] = { "Static", "Dynamic" };
static const int indicatorHoverSizeStylesCount = 2;

static const char *chamsMaterialList[15] = { "Default", "Flat", "Cartoon", "Clown", "Ferrofluid", "Plastic", "Aluminum", "Gold", "Ghost", "Tin Foil", "Slime", "Lava", "Ice", "Dark", "Custom" };
static const int chamsMaterialListCount = 15;

/*

HITBOX_HEAD,
HITBOX_NECK,
HITBOX_PELVIS,
HITBOX_BELLY,
HITBOX_THORAX,
HITBOX_LOWER_CHEST,
HITBOX_UPPER_CHEST,
HITBOX_RIGHT_THIGH,
HITBOX_LEFT_THIGH,
HITBOX_RIGHT_CALF,
HITBOX_LEFT_CALF,
HITBOX_RIGHT_FOOT,
HITBOX_LEFT_FOOT,
HITBOX_RIGHT_HAND,
HITBOX_LEFT_HAND,
HITBOX_RIGHT_UPPER_ARM,
HITBOX_RIGHT_FOREARM,
HITBOX_LEFT_UPPER_ARM,
HITBOX_LEFT_FOREARM,

*/

static const char *shineMaterialList[3] = { "Highlight", "Rimlight", "Cartoon" };
static const int shineMaterialListCount = 3;
// DONT FORGET TO REMOVE NECK HITBOX STUFF LOL
static const char *spreadCrosshairList[3] = { "Off", "Circle", "Fade" };
static const int spreadCrosshairListCount = 3;
static const char *bulletTracersMaterialList[8] = { "Blue Glow", "Bubble", "Glow", "Phys Beam", "Purple Glow", "Purple Laser", "Radio", "White" };
static const int bulletTracersMaterialListCount = 8;
static const char *opt_AimHitboxSpot[] = { "Head", "Neck", "Body", "Pelvis" };
static const char *boners[] = { "Head", "Neck", "Body", "Pelvis" };
static const char* hitboxList[8] = { "Head", "Neck", "Body", "Pelvis", "Arms", "Hands", "Legs", "Feet" };
static const int hitboxListCount = 8;
static const char *opt_MultiHitboxes[14] = { "Head", "Pelvis", "Upper Chest", "Chest", "Neck", "Left Forearm", "Right Forearm", "Hands", "Left Thigh", "Right Thigh", "Left Calf", "Right Calf", "Left Foot", "Right Foot" };
static const char *glowStyleList[4] = { "Default", "Shimmer", "Outline", "Outline Pulse" };
static const int glowStyleListCount = 4;
static int realHitboxSpot[] = { 0, 1, 2, 3 };
static const char *bonevalues[20] = { "1", "2", "3", "4", "5", "6", "7", "8","9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19" ," 20" };
static const int bonecount = 20;
static const char *pitch[5] = { "Off", "Custom", "Down", "Zero", "Up" };
static const int pitchCount = 5;
static const char *utPitch[10] = { "Off", "Custom", "Down", "Zero", "Up", "Fake Down", "Fake Zero", "Fake Up", "True Down", "True Up" };
static const int utPitchCount = 10;
static const char *baseYaws[4] = { "Camera Yaw", "Zero", "At Targets", "Freestanding" };
static const int baseYawsCount = 4;
static const char *tpmodee[2] = { "Real", "Fake" };
static const int tpcount = 2;
static const char *addons[3] = { "Static", "Jitter", "Spinbot" };
static const int addonsCount = 3;
static const char *jitterModes[2] = { "Random", "Flip" };
static const int jitterModesCount = 2;
static const char *spinbotModes[2] = { "Loop", "Ping-Pong" };
static const int spinbotModesCount = 2;
static const char *flipMethods[2] = { "Mirror", "Add 180" };
static const int flipMethodsCount = 2;
static const char *yaws[2] = { "off", "freestanding" };
static const int yawcount = 2;
static const char *fakeyaw[2] = { "off", "backwards" };
static const int fakecount = 2;
extern bool input_shouldListen;


static const char *lcompmode[2] = { "lc breakers", "always backtrack" };
static const int lcount = 2;

static const char* freestandingMethods[2] = { "Safe", "Stylish" };
static const int freestandingMethodsCount = 2;
static const char* freestandingQualities[3] = { "Low", "Medium", "High" };
static const int freestandingQualitiesCount = 3;
static const char* freestandingScanQualities[2] = { "Low", "High" };
static const int freestandingScanQualitiesCount = 2;


extern Options g_Options;

