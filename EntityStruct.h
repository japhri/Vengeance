#pragma once
#include "offsets.h"

class C_BaseCombatWeapon;


enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4,
	MAX_MOVETYPE
};



enum class CSClasses // Must specify CSClasses::Whatever in order to use smth from here
					 // Last updated -- 29 November 2016 (Glove Update)
{
	CAI_BaseNPC = 0,
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseEntity = 11,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleCBaseEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempCBaseEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 29,
	CCascadeLight = 30,
	CChicken = 31,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 39,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconCBaseEntity = 44,
	CEconWearable = 45,
	CEmbers = 46,
	CCBaseEntityDissolve = 47,
	CCBaseEntityFlame = 48,
	CCBaseEntityFreezing = 49,
	CCBaseEntityParticleTrail = 50,
	CEnvAmbientLight = 51,
	CEnvDetailController = 52,
	CEnvDOFController = 53,
	CEnvParticleScript = 54,
	CEnvProjectedTexture = 55,
	CEnvQuadraticBeam = 56,
	CEnvScreenEffect = 57,
	CEnvScreenOverlay = 58,
	CEnvTonemapController = 59,
	CEnvWind = 60,
	CFEPlayerDecal = 61,
	CFireCrackerBlast = 62,
	CFireSmoke = 63,
	CFireTrail = 64,
	CFish = 65,
	CFlashbang = 66,
	CFogController = 67,
	CFootstepControl = 68,
	CFunc_Dust = 69,
	CFunc_LOD = 70,
	CFuncAreaPortalWindow = 71,
	CFuncBrush = 72,
	CFuncConveyor = 73,
	CFuncLadder = 74,
	CFuncMonitor = 75,
	CFuncMoveLinear = 76,
	CFuncOccluder = 77,
	CFuncReflectiveGlass = 78,
	CFuncRotating = 79,
	CFuncSmokeVolume = 80,
	CFuncTrackTrain = 81,
	CGameRulesProxy = 82,
	CHandleTest = 83,
	CHEGrenade = 84,
	CHostage = 85,
	CHostageCarriableProp = 86,
	CIncendiaryGrenade = 87,
	CInferno = 88,
	CInfoLadderDismount = 89,
	CInfoOverlayAccessor = 90,
	CItem_Healthshot = 91,
	CKnife = 92,
	CKnifeGG = 93,
	CLightGlow = 94,
	CMaterialModifyControl = 95,
	CMolotovGrenade = 96,
	CMolotovProjectile = 97,
	CMovieDisplay = 98,
	CParticleFire = 99,
	CParticlePerformanceMonitor = 100,
	CParticleSystem = 101,
	CPhysBox = 102,
	CPhysBoxMultiplayer = 103,
	CPhysicsProp = 104,
	CPhysicsPropMultiplayer = 105,
	CPhysMagnet = 106,
	CPlantedC4 = 107,
	CPlasma = 108,
	CPlayerResource = 109,
	CPointCamera = 110,
	CPointCommentaryNode = 111,
	CPoseController = 112,
	CPostProcessController = 113,
	CPrecipitation = 114,
	CPrecipitationBlocker = 115,
	CPredictedViewModel = 116,
	CProp_Hallucination = 117,
	CPropDoorRotating = 118,
	CPropJeep = 119,
	CPropVehicleDriveable = 120,
	CRagdollManager = 121,
	CRagdollProp = 122,
	CRagdollPropAttached = 123,
	CRopeKeyframe = 124,
	CSCAR17 = 125,
	CSceneCBaseEntity = 126,
	CSensorGrenade = 127,
	CSensorGrenadeProjectile = 128,
	CShadowControl = 129,
	CSlideshowDisplay = 130,
	CSmokeGrenade = 131,
	CSmokeGrenadeProjectile = 132,
	CSmokeStack = 133,
	CSpatialCBaseEntity = 134,
	CSpotlightEnd = 135,
	CSprite = 136,
	CSpriteOriented = 137,
	CSpriteTrail = 138,
	CStatueProp = 139,
	CSteamJet = 140,
	CSun = 141,
	CSunlightShadowControl = 142,
	CTeam = 143,
	CTeamplayRoundBasedRulesProxy = 144,
	CTEArmorRicochet = 145,
	CTEBaseBeam = 146,
	CTEBeamEntPoint = 147,
	CTEBeamEnts = 148,
	CTEBeamFollow = 149,
	CTEBeamLaser = 150,
	CTEBeamPoints = 151,
	CTEBeamRing = 152,
	CTEBeamRingPoint = 153,
	CTEBeamSpline = 154,
	CTEBloodSprite = 155,
	CTEBloodStream = 156,
	CTEBreakModel = 157,
	CTEBSPDecal = 158,
	CTEBubbles = 159,
	CTEBubbleTrail = 160,
	CTEClientProjectile = 161,
	CTEDecal = 162,
	CTEDust = 163,
	CTEDynamicLight = 164,
	CTEEffectDispatch = 165,
	CTEEnergySplash = 166,
	CTEExplosion = 167,
	CTEFireBullets = 168,
	CTEFizz = 169,
	CTEFootprintDecal = 170,
	CTEFoundryHelpers = 171,
	CTEGaussExplosion = 172,
	CTEGlowSprite = 173,
	CTEImpact = 174,
	CTEKillPlayerAttachments = 175,
	CTELargeFunnel = 176,
	CTEMetalSparks = 177,
	CTEMuzzleFlash = 178,
	CTEParticleSystem = 179,
	CTEPhysicsProp = 180,
	CTEPlantBomb = 181,
	CTEPlayerAnimEvent = 182,
	CTEPlayerDecal = 183,
	CTEProjectedDecal = 184,
	CTERadioIcon = 185,
	CTEShatterSurface = 186,
	CTEShowLine = 187,
	CTesla = 188,
	CTESmoke = 189,
	CTESparks = 190,
	CTESprite = 191,
	CTESpriteSpray = 192,
	CTest_ProxyToggle_Networkable = 193,
	CTestTraceline = 194,
	CTEWorldDecal = 195,
	CTriggerPlayerMovement = 196,
	CTriggerSoundOperator = 197,
	CVGuiScreen = 198,
	CVoteController = 199,
	CWaterBullet = 200,
	CWaterLODControl = 201,
	CWeaponAug = 202,
	CWeaponAWP = 203,
	CWeaponBaseItem = 204,
	CWeaponBizon = 205,
	CWeaponCSBase = 206,
	CWeaponCSBaseGun = 207,
	CWeaponCycler = 208,
	CWeaponElite = 209,
	CWeaponFamas = 210,
	CWeaponFiveSeven = 211,
	CWeaponG3SG1 = 212,
	CWeaponGalil = 213,
	CWeaponGalilAR = 214,
	CWeaponGlock = 215,
	CWeaponHKP2000 = 216,
	CWeaponM249 = 217,
	CWeaponM3 = 218,
	CWeaponM4A1 = 219,
	CWeaponMAC10 = 220,
	CWeaponMag7 = 221,
	CWeaponMP5Navy = 222,
	CWeaponMP7 = 223,
	CWeaponMP9 = 224,
	CWeaponNegev = 225,
	CWeaponNOVA = 226,
	CWeaponP228 = 227,
	CWeaponP250 = 228,
	CWeaponP90 = 229,
	CWeaponSawedoff = 230,
	CWeaponSCAR20 = 231,
	CWeaponScout = 232,
	CWeaponSG550 = 233,
	CWeaponSG552 = 234,
	CWeaponSG556 = 235,
	CWeaponSSG08 = 236,
	CWeaponTaser = 237,
	CWeaponTec9 = 238,
	CWeaponTMP = 239,
	CWeaponUMP45 = 240,
	CWeaponUSP = 241,
	CWeaponXM1014 = 242,
	CWorld = 243,
	DustTrail = 244,
	MovieExplosion = 245,
	ParticleSmokeGrenade = 246,
	RocketTrail = 247,
	SmokeTrail = 248,
	SporeExplosion = 249,
	SporeTrail = 250
};

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_LOOKSPIN		(1 << 25)

#define	FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define	FL_WATERJUMP			(1<<3)	// player jumping out of water
#define FL_ONTRAIN				(1<<4) // Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<5)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<6) // Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<7) // Player can't move, but keeps key inputs for controlling another entity
#define	FL_CLIENT				(1<<8)	// Is a player
#define FL_FAKECLIENT			(1<<9)	// Fake client, simulated server side; don't send network messages to them
#define	FL_INWATER				(1<<10)	// In water

// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS		11

// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_FLY					(1<<11)	// Changes the SV_Movestep() behavior to not need to be on ground
#define	FL_SWIM					(1<<12)	// Changes the SV_Movestep() behavior to not need to be on ground (but stay in water)
#define	FL_CONVEYOR				(1<<13)
#define	FL_NPC					(1<<14)
#define	FL_GODMODE				(1<<15)
#define	FL_NOTARGET				(1<<16)
#define	FL_AIMTARGET			(1<<17)	// set if the crosshair needs to aim onto the entity
#define	FL_PARTIALGROUND		(1<<18)	// not all corners are valid
#define FL_STATICPROP			(1<<19)	// Eetsa static prop!		
#define FL_GRAPHED				(1<<20) // worldgraph has this ent listed as something that blocks a connection
#define FL_GRENADE				(1<<21)
#define FL_STEPMOVEMENT			(1<<22)	// Changes the SV_Movestep() behavior to not do any processing
#define FL_DONTTOUCH			(1<<23)	// Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set
#define FL_BASEVELOCITY			(1<<24)	// Base velocity has been applied this frame (used to convert base velocity into momentum)
#define FL_WORLDBRUSH			(1<<25)	// Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something)
#define FL_OBJECT				(1<<26) // Terrible name. This is an object that NPCs should see. Missiles, for example.
#define FL_KILLME				(1<<27)	// This entity is marked for death -- will be freed by game DLL
#define FL_ONFIRE				(1<<28)	// You know...
#define FL_DISSOLVING			(1<<29) // We're dissolving!
#define FL_TRANSRAGDOLL			(1<<30) // In the process of turning into a client side ragdoll.
#define FL_UNBLOCKABLE_BY_PLAYER (1<<31) // pusher that can't be blocked by the player

#define SEQUENCE_DEFAULT_DRAW						0
#define SEQUENCE_DEFAULT_IDLE1						1
#define SEQUENCE_DEFAULT_IDLE2						2
#define SEQUENCE_DEFAULT_LIGHT_MISS1				3
#define SEQUENCE_DEFAULT_LIGHT_MISS2				4
#define SEQUENCE_DEFAULT_HEAVY_MISS1				9
#define SEQUENCE_DEFAULT_HEAVY_HIT1					10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB				11
#define SEQUENCE_DEFAULT_LOOKAT01					12

#define SEQUENCE_BUTTERFLY_DRAW						0
#define SEQUENCE_BUTTERFLY_DRAW2					1
#define SEQUENCE_BUTTERFLY_LOOKAT01					13
#define SEQUENCE_BUTTERFLY_LOOKAT03					15

#define SEQUENCE_FALCHION_IDLE1						1
#define SEQUENCE_FALCHION_HEAVY_MISS1				8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP		9
#define SEQUENCE_FALCHION_LOOKAT01					12
#define SEQUENCE_FALCHION_LOOKAT02					13

#define SEQUENCE_DAGGERS_IDLE1						1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 				2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 				6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 				11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 				12

#define SEQUENCE_BOWIE_IDLE1 						1

#define CONTENTS_EMPTY			0		// No contents

#define CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define CONTENTS_AUX			0x4
#define CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME			0x10
#define CONTENTS_WATER			0x20
#define CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL		0x8000

#define CONTENTS_PLAYERCLIP		0x10000
#define CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0		0x40000
#define CONTENTS_CURRENT_90		0x80000
#define CONTENTS_CURRENT_180	0x100000
#define CONTENTS_CURRENT_270	0x200000
#define CONTENTS_CURRENT_UP		0x400000
#define CONTENTS_CURRENT_DOWN	0x800000

#define CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define CONTENTS_DEBRIS			0x4000000
#define CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// These are given to FindMaterial to reference the texture groups that show up on the
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define MAXSTUDIOBONES 128
#define BONE_USED_BY_HITBOX 0x100

#define MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define SURF_LIGHT		0x0001		// value will hold the light strength
#define SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define SURF_SKY		0x0004		// don't draw, but add to skybox
#define SURF_WARP		0x0008		// turbulent water warp
#define SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define SURF_NODRAW		0x0080	// don't bother referencing the texture

#define SURF_HINT		0x0100	// make a primary bsp splitter

#define SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)


class IClientRenderable;
class IClientNetworkable;
class IClientUnknown;
class IClientThinkable;
struct model_t;
class CBaseCombatWeapon;
#define ACTIVITY_NOT_AVAILABLE		-1
//#define m_bClientSideAnimation 0x288C

class AnimationLayer;
struct CBasePlayerAnimState;
class CCSPlayerAnimState;
class CCSGOPlayerAnimState;

class AnimationLayer
{
public:
	char  pad_0000[20];
	uint32_t m_nOrder; //0x0014
	uint32_t m_nSequence; //0x0018
	float_t m_flPrevCycle; //0x001C
	float_t m_flWeight; //0x0020
	float_t m_flWeightDeltaRate; //0x0024
	float_t m_flPlaybackRate; //0x0028
	float_t m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038

class CCSGOPlayerAnimState
{
public:

	Vector GetVecVelocity()
	{
		// Only on ground velocity
		return *(Vector*)((uintptr_t)this + 0xC8);
	}

	float GetVelocity()
	{
		return *(float*)((uintptr_t)this + 0xEC);
	}

	char pad_0x0000[0x344]; //0x0000
}; //S

struct Weapon_Info
{
	char pad00[0xC8];
	int m_WeaponType; // 0xC8
	char padCC[0x20];
	int m_Damage; // 0xEC
	float m_ArmorRatio; // 0xF0
	char padF4[0x4];
	float m_Penetration; // 0xF8
	char padFC[0x8];
	float m_Range; // 0x104
	float m_RangeModifier; // 0x108
	char pad10C[0x10];
	bool m_HasSilencer; // 0x11C
};
enum WEAPONCLASS
{
	WEPCLASS_INVALID,
	WEPCLASS_RIFLE,
	WEPCLASS_PISTOL,
	WEPCLASS_SHOTGUN,
	WEPCLASS_SNIPER,
	WEPCLASS_SMG,
	WEPCLASS_MACHINEGUN,
	WEPCLASS_KNIFE,
};
enum ItemDefinitionIndex : int {
	DEAGLE = 1,
	ELITE = 2,
	FIVESEVEN = 3,
	GLOCK = 4,
	AK47 = 7,
	AUG = 8,
	AWP = 9,
	FAMAS = 10,
	G3SG1 = 11,
	GALILAR = 13,
	M249 = 14,
	M4A1 = 16,
	MAC10 = 17,
	P90 = 19,
	MP5 = 23,
	UMP45 = 24,
	XM1014 = 25,
	BIZON = 26,
	MAG7 = 27,
	NEGEV = 28,
	SAWEDOFF = 29,
	TEC9 = 30,
	TASER = 31,
	HKP2000 = 32,
	MP7 = 33,
	MP9 = 34,
	NOVA = 35,
	P250 = 36,
	SCAR20 = 38,
	SG556 = 39,
	SSG08 = 40,
	KNIFE = 42,
	FLASHBANG = 43,
	HEGRENADE = 44,
	SMOKEGRENADE = 45,
	MOLOTOV = 46,
	DECOY = 47,
	INCGRENADE = 48,
	C4 = 49,
	KNIFE_T = 59,
	M4A1_SILENCER = 60,
	USP_SILENCER = 61,
	CZ75A = 63,
	REVOLVER = 64,
	KNIFE_BAYONET = 500,
	KNIFE_FLIP = 505,
	KNIFE_GUT = 506,
	KNIFE_KARAMBIT = 507,
	KNIFE_M9_BAYONET = 508,
	KNIFE_TACTICAL = 509,
	KNIFE_FALCHION = 512,
	KNIFE_BUTTERFLY = 515,
	KNIFE_PUSH = 516,
	KNIFE_BOWIE = 514,
	KNIFE_NAVAJA = 520,
	KNIFE_STILETTO = 522,
	KNIFE_URSUS = 519,
	KNIFE_TALON = 523,
};
struct CHudTexture
{
	char	szShortName[64];	//0x0000
	char	szTextureFile[64];	//0x0040
	bool	bRenderUsingFont;	//0x0080
	bool	bPrecached;			//0x0081
	char	cCharacterInFont;	//0x0082
	BYTE	pad_0x0083;			//0x0083
	int		hFont;				//0x0084
	int		iTextureId;			//0x0088
	float	afTexCoords[4];		//0x008C
	int		iPosX[4];			//0x009C
}; //Size=0x00AC

class CSWeaponInfo
{
public:
	char _0x0000[20];
	__int32 max_clip;			//0x0014 
	char _0x0018[12];
	__int32 max_reserved_ammo;	//0x0024 
	char _0x0028[96];
	char* hud_name;				//0x0088 
	char* weapon_name;			//0x008C 
	char _0x0090[60];

	__int32 type;				//0x00CC 
	__int32 price;				//0x00D0 
	__int32 reward;				//0x00D4 
	char _0x00D8[20];
	BYTE full_auto;				//0x00EC 
	char _0x00ED[3];
	__int32 damage;				//0x00F0 
	float armor_ratio;			//0x00F4 
	__int32 bullets;			//0x00F8 
	float penetration;			//0x00FC 
	char _0x0100[8];
	float range;				//0x0108 
	float range_modifier;		//0x010C 
	char _0x0110[16];
	BYTE silencer;				//0x0120 
	char _0x0121[15];
	float max_speed;			//0x0130 
	float max_speed_alt;		//0x0134 
	char _0x0138[76];
	__int32 recoil_seed;		//0x0184 
	char _0x0188[32];
};
enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	//WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};
class CCSWeaponInfo
{
public:
	void*           pVTable;
	char*	    	consoleName;			// 0x0004
	char	    	pad_0008[12];			// 0x0008
	int			    iMaxClip1;				// 0x0014
	int			    iMaxClip2;				// 0x0018
	int		    	iDefaultClip1;			// 0x001C
	int		    	iDefaultClip2;			// 0x0020
	char	    	pad_0024[8];			// 0x0024
	char*	    	szWorldModel;			// 0x002C
	char*	    	szViewModel;			// 0x0030
	char*	    	szDroppedModel;			// 0x0034
	char	    	pad_0038[4];			// 0x0038
	char*	    	N0000023E;				// 0x003C
	char	    	pad_0040[56];			// 0x0040
	char*	    	szEmptySound;			// 0x0078
	char	    	pad_007C[4];			// 0x007C
	char*	    	szBulletType;			// 0x0080
	char	    	pad_0084[4];			// 0x0084
	char*	    	szHudName;				// 0x0088
	char*	    	szWeaponName;			// 0x008C
	char		    pad_0090[60];			// 0x0090 - [54] -> [60] !!!
	CSWeaponType    iWeaponType;			// 0x00C8
	int		    	iWeaponPrice;			// 0x00CC
	int		    	iKillAward;				// 0x00D0
	char*	    	szAnimationPrefix;		// 0x00D4
	float	    	flCycleTime;			// 0x00D8
	float	    	flCycleTimeAlt;			// 0x00DC
	float	    	flTimeToIdle;			// 0x00E0
	float	    	flIdleInterval;			// 0x00E4
	bool	    	bFullAuto;				// 0x00E8
	char	    	pad_0x00E5[3];			// 0x00E9
	int		    	iDamage;				// 0x00EC
	float	    	flArmorRatio;			// 0x00F0
	int		    	iBullets;				// 0x00F4
	float	    	flPenetration;			// 0x00F8
	float	    	flFlinchVelocityModifierLarge;	// 0x00FC
	float	    	flFlinchVelocityModifierSmall;	// 0x0100
	float	    	flRange;				// 0x0104
	float	    	flRangeModifier;		// 0x0108
	float	    	flThrowVelocity;		// 0x010C
	char		    pad_0x010C[12];			// 0x0110
	bool	    	bHasSilencer;			// 0x011C
	char	    	pad_0x0119[3];			// 0x011D
	char*	    	pSilencerModel;			// 0x0120
	int		    	iCrosshairMinDistance;	// 0x0124
	int		    	iCrosshairDeltaDistance;// 0x0128 - iTeam?
	float	    	flMaxPlayerSpeed;		// 0x012C
	float	    	flMaxPlayerSpeedAlt;	// 0x0130
	float	    	flSpread;				// 0x0134
	float	    	flSpreadAlt;			// 0x0138
	float	    	flInaccuracyCrouch;		// 0x013C
	float	    	flInaccuracyCrouchAlt;	// 0x0140
	float	    	flInaccuracyStand;		// 0x0144
	float	    	flInaccuracyStandAlt;	// 0x0148
	float	    	flInaccuracyJumpInitial;// 0x014C
	float	    	flInaccuracyJump;		// 0x0150
	float	    	flInaccuracyJumpAlt;	// 0x0154
	float	    	flInaccuracyLand;		// 0x0158
	float	    	flInaccuracyLandAlt;	// 0x015C
	float	    	flInaccuracyLadder;		// 0x0160
	float	    	flInaccuracyLadderAlt;	// 0x0164
	float	    	flInaccuracyFire;		// 0x0168
	float	    	flInaccuracyFireAlt;	// 0x016C
	float	    	flInaccuracyMove;		// 0x0170
	float	    	flInaccuracyMoveAlt;	// 0x0174
	float	    	flInaccuracyReload;		// 0x0178
	int		    	iRecoilSeed;			// 0x017C
	float	    	flRecoilAngle;			// 0x0180
	float	    	flRecoilAngleAlt;		// 0x0184
	float	    	flRecoilAngleVariance;	// 0x0188
	float	    	flRecoilAngleVarianceAlt;	// 0x018C
	float	    	flRecoilMagnitude;		// 0x0190
	float	    	flRecoilMagnitudeAlt;	// 0x0194
	float		    flRecoilMagnitudeVariance;	// 0x0198
	float	    	flRecoilMagnitudeVarianceAlt;	// 0x019C
	float		    flRecoveryTimeCrouch;	// 0x01A0
	float	    	flRecoveryTimeStand;	// 0x01A4
	float	    	flRecoveryTimeCrouchFinal;	// 0x01A8
	float	    	flRecoveryTimeStandFinal;	// 0x01AC
	int		    	iRecoveryTransitionStartBullet;// 0x01B0 
	int		    	iRecoveryTransitionEndBullet;	// 0x01B4
	bool	    	bUnzoomAfterShot;		// 0x01B8
	bool	    	bHideViewModelZoomed;	// 0x01B9
	char	    	pad_0x01B5[2];			// 0x01BA
	char	    	iZoomLevels[3];			// 0x01BC
	int		    	iZoomFOV[2];			// 0x01C0
	float	    	fZoomTime[3];			// 0x01C4
	char*	    	szWeaponClass;			// 0x01D4
	float	    	flAddonScale;			// 0x01D8
	char	    	pad_0x01DC[12];			// 0x01DC - 4 -> 12
	char*	    	szEjectBrassEffect;		// 0x01E0 -> 0x01E8
	char*		    szTracerEffect;			// 0x01E4 -> 0x01EC
	int		       	iTracerFrequency;		// 0x01E8 -> 0x01F0
	int		    	iTracerFrequencyAlt;	// 0x01EC -> 0x01F4
	char*	    	szMuzzleFlashEffect_1stPerson; // 0x01F0 -> 0x01F8
	char	    	pad_0x01F4[4];			 // 0x01F4 -> 0x01FC
	char*	    	szMuzzleFlashEffect_3rdPerson; // 0x01F8 -> 0x0200
	char	    	pad_0x01FC[4];			// 0x01FC -> 0x0204
	char*	    	szMuzzleSmokeEffect;	// 0x0200 -> 0x0208
	float	    	flHeatPerShot;			// 0x0204 -> 0x020C
	char*	    	szZoomInSound;			// 0x0208 -> 0x0210
	char*	    	szZoomOutSound;			// 0x020C -> 0x0214
	float	    	flInaccuracyPitchShift;	// 0x0210 -> 0x0218
	float	    	flInaccuracySoundThreshold;	// 0x0214 -> 0x021C
	float	    	flBotAudibleRange;		// 0x0218 -> 0x220
	char	    	pad_0x0218[12];			// 0x0220??? -> 0x224 - 8 -> 12
											//char*	    	pWrongTeamMsg;			// 0x0224 -> 0x225
	bool	    	bHasBurstMode;			// 0x0228 -> 0x229 -> 0x230
											//char	    	pad_0x0225[3];			// 0x0229
	bool	    	bIsRevolver;			// 0x022C -> 0x22A -> 0x231
	bool	    	bCannotShootUnderwater;	// 0x0230 -> 0x22B -> 0x232
}; //Size: 0x0828
   /*float recovery_time_crouch; //0x01A0
   float recovery_time_stand; //0x01A4
   float recovery_time_crouch_final; //0x01A8
   float recovery_time_stand_final; //0x01AC
   int recovery_transition_start_bullet; //0x01B0
   int recovery_transition_end_bullet; //0x01B4
   bool unzoom_after_shot; //0x01B8
   bool hide_viewmodel_zoomed; //0x01B9
   char pad_0x01BA[0x2E]; //0x01BA
   char* eject_brass_effect; //0x01E8
   char* tracer_effect; //0x01EC
   int tracer_frequency; //0x01F0
   int tracer_frequency_alt; //0x01F4
   char* muzzle_flash_effect_1stPerson; //0x01F8
   char pad_0x01FC[0x4]; //0x01FC
   char* muzzle_flash_effect_3rdPerson; //0x0200
   char pad_0x0204[0x4]; //0x0204
   char* muzzle_smoke_effect; //0x0208
   float heat_per_shot; //0x020C
   char* zoom_in_sound; //0x0210
   char* zoom_out_sound; //0x0214
   float inaccuracy_pitch_shift; //0x0218
   float inaccuracy_sound_threshold; //0x021C
   float bot_audible_range; //0x0220
   char pad_0x0224[0xC]; //0x0224
   bool has_burst_mode; //0x0230
   bool is_revolver; //0x0231
   bool can_shoot_underwater; //0x0232
   };*/

enum ItemSchemaIndex
{
	ITEM_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALS = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_P2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SCOUT = 40,
	WEAPON_KNIFE_T = 42,
	WEAPON_FLASH = 43,
	WEAPON_HE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INC = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_CT = 59,
	WEAPON_M4A1S = 60,
	WEAPON_USPS = 61,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER = 64,
	WEAPON_MAX = 65,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9BAYONET = 508,
	WEAPON_KNIFE_HUNTSMAN = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_SHADOWDAGGERS = 516,
};

template <typename T>
__forceinline T Member(void *base, DWORD offset = 0)
{
	return (T)((DWORD)base + offset);
}
enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,	// indicates it was created +and+ entered the pvs
								//	DATA_UPDATE_ENTERED_PVS,
								DATA_UPDATE_DATATABLE_CHANGED,
								//	DATA_UPDATE_LEFT_PVS,
								//	DATA_UPDATE_DESTROYED,		// FIXME: Could enable this, but it's a little worrying
								// since it changes a bunch of existing code
};


class GlowObjectDefinition_t
{
public:
	GlowObjectDefinition_t() { memset(this, 0, sizeof(*this)); }

	class CBaseEntity* m_pEntity;    //0x0000
	Vector m_vGlowColor;           //0x0004
	float   m_flAlpha;                 //0x0010
	uint8_t pad_0014[4];               //0x0014
	float   m_flSomeFloat;             //0x0018
	uint8_t pad_001C[4];               //0x001C
	float   m_flAnotherFloat;          //0x0020
	bool    m_bRenderWhenOccluded;     //0x0024
	bool    m_bRenderWhenUnoccluded;   //0x0025
	bool    m_bFullBloomRender;        //0x0026
	uint8_t pad_0027[5];               //0x0027
	int32_t m_nGlowStyle;              //0x002C
	int32_t m_nSplitScreenSlot;        //0x0030
	int32_t m_nNextFreeSlot;           //0x0034

	bool IsUnused() const { return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE; }

	static const int END_OF_FREE_LIST = -1;
	static const int ENTRY_IN_USE = -2;
}; //Size: 0x0038 (56)

class CGlowObjectManager
{
public:

	class GlowObjectDefinition_t
	{
	public:

		class CBaseEntity *m_pEntity;
		union
		{
			Vector m_vGlowColor;           //0x0004
			struct
			{
				float   m_flRed;           //0x0004
				float   m_flGreen;         //0x0008
				float   m_flBlue;          //0x000C
			};
		};
		float m_flGlowAlpha;
		uint8_t pad_0014[4];
		float m_flSomeFloatThingy;
		uint8_t pad_001C[4];
		float m_flAnotherFloat;
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloomRender;
		uint8_t pad_0027[5];
		int32_t m_bPulsatingChams;
		int32_t m_nSplitScreenSlot;
		int32_t m_nNextFreeSlot;

		bool IsUnused() const { return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE; }

		static const int END_OF_FREE_LIST = -1;
		static const int ENTRY_IN_USE = -2;
	};

	GlowObjectDefinition_t *m_GlowObjectDefinitions;
	int max_size;
	int pad;
	int size;
	GlowObjectDefinition_t *m_Unknown;
	int	currentObjects;
};

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};
struct CBasePlayerAnimState
{
	char pad[3];
	char bUnknown; //0x4
	char pad2[91];
	CBaseEntity* pBaseEntity; //0x60
	CBaseCombatWeapon* pActiveWeapon; //0x64
	CBaseCombatWeapon* pLastActiveWeapon; //0x68
	float m_flLastClientSideAnimationUpdateTime; //0x6C
	int m_iLastClientSideAnimationUpdateFramecount; //0x70
	float m_flEyePitch; //0x74
	float m_flEyeYaw; //0x78
	float m_flPitch; //0x7C
	float m_flGoalFeetYaw; //0x80
	float m_flCurrentFeetYaw; //0x84
	float m_flCurrentTorsoYaw; //0x88
	float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
	float m_flLeanAmount; //0x90
	char pad4[4]; //NaN
	float m_flFeetCycle; //0x98 0 to 1
	float m_flFeetYawRate; //0x9C 0 to 1
	float m_fUnknown2;
	float m_fDuckAmount; //0xA4
	float m_fLandingDuckAdditiveSomething; //0xA8
	float m_fUnknown3; //0xAC
	Vector m_vOrigin; //0xB0, 0xB4, 0xB8
	Vector m_vLastOrigin; //0xBC, 0xC0, 0xC4
	float m_vVelocityX; //0xC8
	float m_vVelocityY; //0xCC
	char pad5[4];
	float m_flUnknownFloat1; //0xD4 Affected by movement and direction
	char pad6[8];
	float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
	float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
	float m_unknown; //0xE8
	float m_velocity; //0xEC
	float flUpVelocity; //0xF0
	float m_flSpeedNormalized; //0xF4 //from 0 to 1
	float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
	float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
	float m_flTimeSinceStartedMoving; //0x100
	float m_flTimeSinceStoppedMoving; //0x104
	unsigned char m_bOnGround; //0x108
	unsigned char m_bInHitGroundAnimation; //0x109
	char pad7[10];
	float m_flLastOriginZ; //0x114
	float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
	float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
	char pad8[4]; //NaN
	float m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
	char pad9[4]; //NaN
	float m_flUnknown3;
	char pad10[528];
};

enum
{
	TD_OFFSET_NORMAL = 0,
	TD_OFFSET_PACKED = 1,

	// Must be last
	TD_OFFSET_COUNT,
};
typedef enum
{

	ACT_INVALID = -1,			// So we have something more succint to check for than '-1'
	ACT_RESET = 0,				// Set m_Activity to this invalid value to force a reset to m_IdealActivity
	ACT_IDLE,
	ACT_TRANSITION,
	ACT_COVER,					// FIXME: obsolete? redundant with ACT_COVER_LOW?
	ACT_COVER_MED,				// FIXME: unsupported?
	ACT_COVER_LOW,				// FIXME: rename ACT_IDLE_CROUCH?
	ACT_WALK,
	ACT_WALK_AIM,
	ACT_WALK_CROUCH,
	ACT_WALK_CROUCH_AIM,
	ACT_RUN,
	ACT_RUN_AIM,
	ACT_RUN_CROUCH,
	ACT_RUN_CROUCH_AIM,
	ACT_RUN_PROTECTED,
	ACT_SCRIPT_CUSTOM_MOVE,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_RANGE_ATTACK1_LOW,		// FIXME: not used yet, crouched versions of the range attack
	ACT_RANGE_ATTACK2_LOW,		// FIXME: not used yet, crouched versions of the range attack
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_DIERAGDOLL,
	ACT_FLY,				// Fly (and flap if appropriate)
	ACT_HOVER,
	ACT_GLIDE,
	ACT_SWIM,
	ACT_JUMP,
	ACT_HOP,				// vertical jump
	ACT_LEAP,				// long forward jump
	ACT_LAND,
	ACT_CLIMB_UP,
	ACT_CLIMB_DOWN,
	ACT_CLIMB_DISMOUNT,
	ACT_SHIPLADDER_UP,
	ACT_SHIPLADDER_DOWN,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,			// tuck and roll, left
	ACT_ROLL_RIGHT,			// tuck and roll, right
	ACT_TURN_LEFT,			// turn quickly left (stationary)
	ACT_TURN_RIGHT,			// turn quickly right (stationary)
	ACT_CROUCH,				// FIXME: obsolete? only used be soldier (the act of crouching down from a standing position)
	ACT_CROUCHIDLE,			// FIXME: obsolete? only used be soldier (holding body in crouched position (loops))
	ACT_STAND,				// FIXME: obsolete? should be transition (the act of standing from a crouched position)
	ACT_USE,
	ACT_ALIEN_BURROW_IDLE,
	ACT_ALIEN_BURROW_OUT,

	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,

	ACT_SIGNAL_ADVANCE,		// Squad handsignals, specific.
	ACT_SIGNAL_FORWARD,
	ACT_SIGNAL_GROUP,
	ACT_SIGNAL_HALT,
	ACT_SIGNAL_LEFT,
	ACT_SIGNAL_RIGHT,
	ACT_SIGNAL_TAKECOVER,

	ACT_LOOKBACK_RIGHT,		// look back over shoulder without turning around.
	ACT_LOOKBACK_LEFT,
	ACT_COWER,				// FIXME: unused, should be more extreme version of crouching
	ACT_SMALL_FLINCH,		// FIXME: needed? shouldn't flinching be down with overlays?
	ACT_BIG_FLINCH,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_RELOAD_START,
	ACT_RELOAD_FINISH,
	ACT_RELOAD_LOW,
	ACT_ARM,				// pull out gun, for instance
	ACT_DISARM,				// reholster gun
	ACT_DROP_WEAPON,
	ACT_DROP_WEAPON_SHOTGUN,
	ACT_PICKUP_GROUND,		// pick up something in front of you on the ground
	ACT_PICKUP_RACK,		// pick up something from a rack or shelf in front of you.
	ACT_IDLE_ANGRY,			// FIXME: being used as an combat ready idle?  alternate idle animation in which the monster is clearly agitated. (loop)

	ACT_IDLE_RELAXED,
	ACT_IDLE_STIMULATED,
	ACT_IDLE_AGITATED,
	ACT_IDLE_STEALTH,
	ACT_IDLE_HURT,

	ACT_WALK_RELAXED,
	ACT_WALK_STIMULATED,
	ACT_WALK_AGITATED,
	ACT_WALK_STEALTH,

	ACT_RUN_RELAXED,
	ACT_RUN_STIMULATED,
	ACT_RUN_AGITATED,
	ACT_RUN_STEALTH,

	ACT_IDLE_AIM_RELAXED,
	ACT_IDLE_AIM_STIMULATED,
	ACT_IDLE_AIM_AGITATED,
	ACT_IDLE_AIM_STEALTH,

	ACT_WALK_AIM_RELAXED,
	ACT_WALK_AIM_STIMULATED,
	ACT_WALK_AIM_AGITATED,
	ACT_WALK_AIM_STEALTH,

	ACT_RUN_AIM_RELAXED,
	ACT_RUN_AIM_STIMULATED,
	ACT_RUN_AIM_AGITATED,
	ACT_RUN_AIM_STEALTH,

	ACT_CROUCHIDLE_STIMULATED,
	ACT_CROUCHIDLE_AIM_STIMULATED,
	ACT_CROUCHIDLE_AGITATED,

	ACT_WALK_HURT,			// limp  (loop)
	ACT_RUN_HURT,			// limp  (loop)
	ACT_SPECIAL_ATTACK1,	// very monster specific special attacks.
	ACT_SPECIAL_ATTACK2,
	ACT_COMBAT_IDLE,		// FIXME: unused?  agitated idle.
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,		// killed a player, do a victory dance.
	ACT_DIE_HEADSHOT,		// die, hit in head. 
	ACT_DIE_CHESTSHOT,		// die, hit in chest
	ACT_DIE_GUTSHOT,		// die, hit in gut
	ACT_DIE_BACKSHOT,		// die, hit in back
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
	ACT_FLINCH_PHYSICS,
	ACT_FLINCH_HEAD_BACK,
	ACT_FLINCH_CHEST_BACK,
	ACT_FLINCH_STOMACH_BACK,
	ACT_FLINCH_CROUCH_FRONT,
	ACT_FLINCH_CROUCH_BACK,
	ACT_FLINCH_CROUCH_LEFT,
	ACT_FLINCH_CROUCH_RIGHT,

	ACT_IDLE_ON_FIRE,		// ON FIRE animations
	ACT_WALK_ON_FIRE,
	ACT_RUN_ON_FIRE,

	ACT_RAPPEL_LOOP,		// Rappel down a rope!

	ACT_180_LEFT,			// 180 degree left turn
	ACT_180_RIGHT,

	ACT_90_LEFT,			// 90 degree turns
	ACT_90_RIGHT,

	ACT_STEP_LEFT,			// Single steps
	ACT_STEP_RIGHT,
	ACT_STEP_BACK,
	ACT_STEP_FORE,

	ACT_GESTURE_RANGE_ATTACK1,
	ACT_GESTURE_RANGE_ATTACK2,
	ACT_GESTURE_MELEE_ATTACK1,
	ACT_GESTURE_MELEE_ATTACK2,
	ACT_GESTURE_RANGE_ATTACK1_LOW,	// FIXME: not used yet, crouched versions of the range attack
	ACT_GESTURE_RANGE_ATTACK2_LOW,	// FIXME: not used yet, crouched versions of the range attack

	ACT_MELEE_ATTACK_SWING_GESTURE,

	ACT_GESTURE_SMALL_FLINCH,
	ACT_GESTURE_BIG_FLINCH,
	ACT_GESTURE_FLINCH_BLAST,			// Startled by an explosion
	ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
	ACT_GESTURE_FLINCH_BLAST_DAMAGED,	// Damaged by an explosion
	ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
	ACT_GESTURE_FLINCH_HEAD,
	ACT_GESTURE_FLINCH_CHEST,
	ACT_GESTURE_FLINCH_STOMACH,
	ACT_GESTURE_FLINCH_LEFTARM,
	ACT_GESTURE_FLINCH_RIGHTARM,
	ACT_GESTURE_FLINCH_LEFTLEG,
	ACT_GESTURE_FLINCH_RIGHTLEG,

	ACT_GESTURE_TURN_LEFT,
	ACT_GESTURE_TURN_RIGHT,
	ACT_GESTURE_TURN_LEFT45,
	ACT_GESTURE_TURN_RIGHT45,
	ACT_GESTURE_TURN_LEFT90,
	ACT_GESTURE_TURN_RIGHT90,
	ACT_GESTURE_TURN_LEFT45_FLAT,
	ACT_GESTURE_TURN_RIGHT45_FLAT,
	ACT_GESTURE_TURN_LEFT90_FLAT,
	ACT_GESTURE_TURN_RIGHT90_FLAT,

	// HALF-LIFE 1 compatability stuff goes here. Temporary!
	ACT_BARNACLE_HIT,		// barnacle tongue hits a monster
	ACT_BARNACLE_PULL,		// barnacle is lifting the monster ( loop )
	ACT_BARNACLE_CHOMP,		// barnacle latches on to the monster
	ACT_BARNACLE_CHEW,		// barnacle is holding the monster in its mouth ( loop )

							// Sometimes, you just want to set an NPC's sequence to a sequence that doesn't actually
							// have an activity. The AI will reset the NPC's sequence to whatever its IDEAL activity
							// is, though. So if you set ideal activity to DO_NOT_DISTURB, the AI will not interfere
							// with the NPC's current sequence. (SJB)
							ACT_DO_NOT_DISTURB,

							ACT_SPECIFIC_SEQUENCE,

							// viewmodel (weapon) activities
							// FIXME: move these to the specific viewmodels, no need to make global
							ACT_VM_DRAW,
							ACT_VM_HOLSTER,
							ACT_VM_IDLE,
							ACT_VM_FIDGET,
							ACT_VM_PULLBACK,
							ACT_VM_PULLBACK_HIGH,
							ACT_VM_PULLBACK_LOW,
							ACT_VM_THROW,
							ACT_VM_PULLPIN,
							ACT_VM_PRIMARYATTACK,		// fire
							ACT_VM_SECONDARYATTACK,		// alt. fire
							ACT_VM_RELOAD,
							ACT_VM_DRYFIRE,				// fire with no ammo loaded.
							ACT_VM_HITLEFT,				// bludgeon, swing to left - hit (primary attk)
							ACT_VM_HITLEFT2,			// bludgeon, swing to left - hit (secondary attk)
							ACT_VM_HITRIGHT,			// bludgeon, swing to right - hit (primary attk)
							ACT_VM_HITRIGHT2,			// bludgeon, swing to right - hit (secondary attk)
							ACT_VM_HITCENTER,			// bludgeon, swing center - hit (primary attk)
							ACT_VM_HITCENTER2,			// bludgeon, swing center - hit (secondary attk)
							ACT_VM_MISSLEFT,			// bludgeon, swing to left - miss (primary attk)
							ACT_VM_MISSLEFT2,			// bludgeon, swing to left - miss (secondary attk)
							ACT_VM_MISSRIGHT,			// bludgeon, swing to right - miss (primary attk)
							ACT_VM_MISSRIGHT2,			// bludgeon, swing to right - miss (secondary attk)
							ACT_VM_MISSCENTER,			// bludgeon, swing center - miss (primary attk)
							ACT_VM_MISSCENTER2,			// bludgeon, swing center - miss (secondary attk)
							ACT_VM_HAULBACK,			// bludgeon, haul the weapon back for a hard strike (secondary attk)
							ACT_VM_SWINGHARD,			// bludgeon, release the hard strike (secondary attk)
							ACT_VM_SWINGMISS,
							ACT_VM_SWINGHIT,
							ACT_VM_IDLE_TO_LOWERED,
							ACT_VM_IDLE_LOWERED,
							ACT_VM_LOWERED_TO_IDLE,
							ACT_VM_RECOIL1,
							ACT_VM_RECOIL2,
							ACT_VM_RECOIL3,
							ACT_VM_PICKUP,
							ACT_VM_RELEASE,

							ACT_VM_ATTACH_SILENCER,
							ACT_VM_DETACH_SILENCER,

							//===========================
							// HL2 Specific Activities
							//===========================
							// SLAM	Specialty Activities
							ACT_SLAM_STICKWALL_IDLE,
							ACT_SLAM_STICKWALL_ND_IDLE,
							ACT_SLAM_STICKWALL_ATTACH,
							ACT_SLAM_STICKWALL_ATTACH2,
							ACT_SLAM_STICKWALL_ND_ATTACH,
							ACT_SLAM_STICKWALL_ND_ATTACH2,
							ACT_SLAM_STICKWALL_DETONATE,
							ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
							ACT_SLAM_STICKWALL_DRAW,
							ACT_SLAM_STICKWALL_ND_DRAW,
							ACT_SLAM_STICKWALL_TO_THROW,
							ACT_SLAM_STICKWALL_TO_THROW_ND,
							ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
							ACT_SLAM_THROW_IDLE,
							ACT_SLAM_THROW_ND_IDLE,
							ACT_SLAM_THROW_THROW,
							ACT_SLAM_THROW_THROW2,
							ACT_SLAM_THROW_THROW_ND,
							ACT_SLAM_THROW_THROW_ND2,
							ACT_SLAM_THROW_DRAW,
							ACT_SLAM_THROW_ND_DRAW,
							ACT_SLAM_THROW_TO_STICKWALL,
							ACT_SLAM_THROW_TO_STICKWALL_ND,
							ACT_SLAM_THROW_DETONATE,
							ACT_SLAM_THROW_DETONATOR_HOLSTER,
							ACT_SLAM_THROW_TO_TRIPMINE_ND,
							ACT_SLAM_TRIPMINE_IDLE,
							ACT_SLAM_TRIPMINE_DRAW,
							ACT_SLAM_TRIPMINE_ATTACH,
							ACT_SLAM_TRIPMINE_ATTACH2,
							ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
							ACT_SLAM_TRIPMINE_TO_THROW_ND,
							ACT_SLAM_DETONATOR_IDLE,
							ACT_SLAM_DETONATOR_DRAW,
							ACT_SLAM_DETONATOR_DETONATE,
							ACT_SLAM_DETONATOR_HOLSTER,
							ACT_SLAM_DETONATOR_STICKWALL_DRAW,
							ACT_SLAM_DETONATOR_THROW_DRAW,

							// Shotgun Specialty Activities
							ACT_SHOTGUN_RELOAD_START,
							ACT_SHOTGUN_RELOAD_FINISH,
							ACT_SHOTGUN_PUMP,

							// SMG2 special activities
							ACT_SMG2_IDLE2,
							ACT_SMG2_FIRE2,
							ACT_SMG2_DRAW2,
							ACT_SMG2_RELOAD2,
							ACT_SMG2_DRYFIRE2,
							ACT_SMG2_TOAUTO,
							ACT_SMG2_TOBURST,

							// Physcannon special activities
							ACT_PHYSCANNON_UPGRADE,

							// weapon override activities
							ACT_RANGE_ATTACK_AR1,
							ACT_RANGE_ATTACK_AR2,
							ACT_RANGE_ATTACK_AR2_LOW,
							ACT_RANGE_ATTACK_AR2_GRENADE,
							ACT_RANGE_ATTACK_HMG1,
							ACT_RANGE_ATTACK_ML,
							ACT_RANGE_ATTACK_SMG1,
							ACT_RANGE_ATTACK_SMG1_LOW,
							ACT_RANGE_ATTACK_SMG2,
							ACT_RANGE_ATTACK_SHOTGUN,
							ACT_RANGE_ATTACK_SHOTGUN_LOW,
							ACT_RANGE_ATTACK_PISTOL,
							ACT_RANGE_ATTACK_PISTOL_LOW,
							ACT_RANGE_ATTACK_SLAM,
							ACT_RANGE_ATTACK_TRIPWIRE,
							ACT_RANGE_ATTACK_THROW,
							ACT_RANGE_ATTACK_SNIPER_RIFLE,
							ACT_RANGE_ATTACK_RPG,
							ACT_MELEE_ATTACK_SWING,

							ACT_RANGE_AIM_LOW,
							ACT_RANGE_AIM_SMG1_LOW,
							ACT_RANGE_AIM_PISTOL_LOW,
							ACT_RANGE_AIM_AR2_LOW,

							ACT_COVER_PISTOL_LOW,
							ACT_COVER_SMG1_LOW,

							// weapon override activities
							ACT_GESTURE_RANGE_ATTACK_AR1,
							ACT_GESTURE_RANGE_ATTACK_AR2,
							ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
							ACT_GESTURE_RANGE_ATTACK_HMG1,
							ACT_GESTURE_RANGE_ATTACK_ML,
							ACT_GESTURE_RANGE_ATTACK_SMG1,
							ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
							ACT_GESTURE_RANGE_ATTACK_SMG2,
							ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
							ACT_GESTURE_RANGE_ATTACK_PISTOL,
							ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
							ACT_GESTURE_RANGE_ATTACK_SLAM,
							ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
							ACT_GESTURE_RANGE_ATTACK_THROW,
							ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
							ACT_GESTURE_MELEE_ATTACK_SWING,

							ACT_IDLE_RIFLE,
							ACT_IDLE_SMG1,
							ACT_IDLE_ANGRY_SMG1,
							ACT_IDLE_PISTOL,
							ACT_IDLE_ANGRY_PISTOL,
							ACT_IDLE_ANGRY_SHOTGUN,
							ACT_IDLE_STEALTH_PISTOL,

							ACT_IDLE_PACKAGE,
							ACT_WALK_PACKAGE,
							ACT_IDLE_SUITCASE,
							ACT_WALK_SUITCASE,

							ACT_IDLE_SMG1_RELAXED,
							ACT_IDLE_SMG1_STIMULATED,
							ACT_WALK_RIFLE_RELAXED,
							ACT_RUN_RIFLE_RELAXED,
							ACT_WALK_RIFLE_STIMULATED,
							ACT_RUN_RIFLE_STIMULATED,

							ACT_IDLE_AIM_RIFLE_STIMULATED,
							ACT_WALK_AIM_RIFLE_STIMULATED,
							ACT_RUN_AIM_RIFLE_STIMULATED,

							ACT_IDLE_SHOTGUN_RELAXED,
							ACT_IDLE_SHOTGUN_STIMULATED,
							ACT_IDLE_SHOTGUN_AGITATED,

							// Policing activities
							ACT_WALK_ANGRY,
							ACT_POLICE_HARASS1,
							ACT_POLICE_HARASS2,

							// Manned guns
							ACT_IDLE_MANNEDGUN,

							// Melee weapon
							ACT_IDLE_MELEE,
							ACT_IDLE_ANGRY_MELEE,

							// RPG activities
							ACT_IDLE_RPG_RELAXED,
							ACT_IDLE_RPG,
							ACT_IDLE_ANGRY_RPG,
							ACT_COVER_LOW_RPG,
							ACT_WALK_RPG,
							ACT_RUN_RPG,
							ACT_WALK_CROUCH_RPG,
							ACT_RUN_CROUCH_RPG,
							ACT_WALK_RPG_RELAXED,
							ACT_RUN_RPG_RELAXED,

							ACT_WALK_RIFLE,
							ACT_WALK_AIM_RIFLE,
							ACT_WALK_CROUCH_RIFLE,
							ACT_WALK_CROUCH_AIM_RIFLE,
							ACT_RUN_RIFLE,
							ACT_RUN_AIM_RIFLE,
							ACT_RUN_CROUCH_RIFLE,
							ACT_RUN_CROUCH_AIM_RIFLE,
							ACT_RUN_STEALTH_PISTOL,

							ACT_WALK_AIM_SHOTGUN,
							ACT_RUN_AIM_SHOTGUN,

							ACT_WALK_PISTOL,
							ACT_RUN_PISTOL,
							ACT_WALK_AIM_PISTOL,
							ACT_RUN_AIM_PISTOL,
							ACT_WALK_STEALTH_PISTOL,
							ACT_WALK_AIM_STEALTH_PISTOL,
							ACT_RUN_AIM_STEALTH_PISTOL,

							// Reloads
							ACT_RELOAD_PISTOL,
							ACT_RELOAD_PISTOL_LOW,
							ACT_RELOAD_SMG1,
							ACT_RELOAD_SMG1_LOW,
							ACT_RELOAD_SHOTGUN,
							ACT_RELOAD_SHOTGUN_LOW,

							ACT_GESTURE_RELOAD,
							ACT_GESTURE_RELOAD_PISTOL,
							ACT_GESTURE_RELOAD_SMG1,
							ACT_GESTURE_RELOAD_SHOTGUN,

							// Busy animations
							ACT_BUSY_LEAN_LEFT,
							ACT_BUSY_LEAN_LEFT_ENTRY,
							ACT_BUSY_LEAN_LEFT_EXIT,
							ACT_BUSY_LEAN_BACK,
							ACT_BUSY_LEAN_BACK_ENTRY,
							ACT_BUSY_LEAN_BACK_EXIT,
							ACT_BUSY_SIT_GROUND,
							ACT_BUSY_SIT_GROUND_ENTRY,
							ACT_BUSY_SIT_GROUND_EXIT,
							ACT_BUSY_SIT_CHAIR,
							ACT_BUSY_SIT_CHAIR_ENTRY,
							ACT_BUSY_SIT_CHAIR_EXIT,
							ACT_BUSY_STAND,
							ACT_BUSY_QUEUE,

							// Dodge animations
							ACT_DUCK_DODGE,

							// For NPCs being lifted/eaten by barnacles:
							// being swallowed by a barnacle
							ACT_DIE_BARNACLE_SWALLOW,
							// being lifted by a barnacle
							ACT_GESTURE_BARNACLE_STRANGLE,

							ACT_PHYSCANNON_DETACH,	// An activity to be played if we're picking this up with the physcannon
							ACT_PHYSCANNON_ANIMATE, // An activity to be played by an object being picked up with the physcannon, but has different behavior to DETACH
							ACT_PHYSCANNON_ANIMATE_PRE,	// An activity to be played by an object being picked up with the physcannon, before playing the ACT_PHYSCANNON_ANIMATE
							ACT_PHYSCANNON_ANIMATE_POST,// An activity to be played by an object being picked up with the physcannon, after playing the ACT_PHYSCANNON_ANIMATE

							ACT_DIE_FRONTSIDE,
							ACT_DIE_RIGHTSIDE,
							ACT_DIE_BACKSIDE,
							ACT_DIE_LEFTSIDE,

							ACT_OPEN_DOOR,

							// Dynamic interactions
							ACT_DI_ALYX_ZOMBIE_MELEE,
							ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
							ACT_DI_ALYX_HEADCRAB_MELEE,
							ACT_DI_ALYX_ANTLION,

							ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
							ACT_DI_ALYX_ZOMBIE_SHOTGUN26,

							ACT_READINESS_RELAXED_TO_STIMULATED,
							ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
							ACT_READINESS_AGITATED_TO_STIMULATED,
							ACT_READINESS_STIMULATED_TO_RELAXED,

							ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
							ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
							ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
							ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,

							ACT_IDLE_CARRY,
							ACT_WALK_CARRY,

							//===========================
							// TF2 Specific Activities
							//===========================
							ACT_STARTDYING,
							ACT_DYINGLOOP,
							ACT_DYINGTODEAD,

							ACT_RIDE_MANNED_GUN,

							// All viewmodels
							ACT_VM_SPRINT_ENTER,
							ACT_VM_SPRINT_IDLE,
							ACT_VM_SPRINT_LEAVE,

							// Looping weapon firing
							ACT_FIRE_START,
							ACT_FIRE_LOOP,
							ACT_FIRE_END,

							ACT_CROUCHING_GRENADEIDLE,
							ACT_CROUCHING_GRENADEREADY,
							ACT_CROUCHING_PRIMARYATTACK,
							ACT_OVERLAY_GRENADEIDLE,
							ACT_OVERLAY_GRENADEREADY,
							ACT_OVERLAY_PRIMARYATTACK,
							ACT_OVERLAY_SHIELD_UP,
							ACT_OVERLAY_SHIELD_DOWN,
							ACT_OVERLAY_SHIELD_UP_IDLE,
							ACT_OVERLAY_SHIELD_ATTACK,
							ACT_OVERLAY_SHIELD_KNOCKBACK,
							ACT_SHIELD_UP,
							ACT_SHIELD_DOWN,
							ACT_SHIELD_UP_IDLE,
							ACT_SHIELD_ATTACK,
							ACT_SHIELD_KNOCKBACK,
							ACT_CROUCHING_SHIELD_UP,
							ACT_CROUCHING_SHIELD_DOWN,
							ACT_CROUCHING_SHIELD_UP_IDLE,
							ACT_CROUCHING_SHIELD_ATTACK,
							ACT_CROUCHING_SHIELD_KNOCKBACK,

							// turning in place
							ACT_TURNRIGHT45,
							ACT_TURNLEFT45,

							ACT_TURN,

							ACT_OBJ_ASSEMBLING,
							ACT_OBJ_DISMANTLING,
							ACT_OBJ_STARTUP,
							ACT_OBJ_RUNNING,
							ACT_OBJ_IDLE,
							ACT_OBJ_PLACING,
							ACT_OBJ_DETERIORATING,
							ACT_OBJ_UPGRADING,

							// Deploy
							ACT_DEPLOY,
							ACT_DEPLOY_IDLE,
							ACT_UNDEPLOY,

							// Crossbow
							ACT_CROSSBOW_DRAW_UNLOADED,

							// Gauss
							ACT_GAUSS_SPINUP,
							ACT_GAUSS_SPINCYCLE,

							//===========================
							// CSPort Specific Activities
							//===========================

							ACT_VM_PRIMARYATTACK_SILENCED,		// fire
							ACT_VM_RELOAD_SILENCED,
							ACT_VM_DRYFIRE_SILENCED,				// fire with no ammo loaded.
							ACT_VM_IDLE_SILENCED,
							ACT_VM_DRAW_SILENCED,
							ACT_VM_IDLE_EMPTY_LEFT,
							ACT_VM_DRYFIRE_LEFT,

							// new for CS2
							ACT_VM_IS_DRAW,
							ACT_VM_IS_HOLSTER,
							ACT_VM_IS_IDLE,
							ACT_VM_IS_PRIMARYATTACK,

							ACT_PLAYER_IDLE_FIRE,
							ACT_PLAYER_CROUCH_FIRE,
							ACT_PLAYER_CROUCH_WALK_FIRE,
							ACT_PLAYER_WALK_FIRE,
							ACT_PLAYER_RUN_FIRE,

							ACT_IDLETORUN,
							ACT_RUNTOIDLE,

							ACT_VM_DRAW_DEPLOYED,

							ACT_HL2MP_IDLE_MELEE,
							ACT_HL2MP_RUN_MELEE,
							ACT_HL2MP_IDLE_CROUCH_MELEE,
							ACT_HL2MP_WALK_CROUCH_MELEE,
							ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
							ACT_HL2MP_GESTURE_RELOAD_MELEE,
							ACT_HL2MP_JUMP_MELEE,

							// Portal!
							ACT_VM_FIZZLE,

							// Multiplayer
							ACT_MP_STAND_IDLE,
							ACT_MP_CROUCH_IDLE,
							ACT_MP_CROUCH_DEPLOYED_IDLE,
							ACT_MP_CROUCH_DEPLOYED,
							ACT_MP_DEPLOYED_IDLE,
							ACT_MP_RUN,
							ACT_MP_WALK,
							ACT_MP_AIRWALK,
							ACT_MP_CROUCHWALK,
							ACT_MP_SPRINT,
							ACT_MP_JUMP,
							ACT_MP_JUMP_START,
							ACT_MP_JUMP_FLOAT,
							ACT_MP_JUMP_LAND,
							ACT_MP_DOUBLEJUMP,
							ACT_MP_SWIM,
							ACT_MP_DEPLOYED,
							ACT_MP_SWIM_DEPLOYED,
							ACT_MP_VCD,

							ACT_MP_ATTACK_STAND_PRIMARYFIRE,
							ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
							ACT_MP_ATTACK_STAND_SECONDARYFIRE,
							ACT_MP_ATTACK_STAND_GRENADE,
							ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
							ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
							ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
							ACT_MP_ATTACK_CROUCH_GRENADE,
							ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
							ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
							ACT_MP_ATTACK_SWIM_GRENADE,
							ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
							ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
							ACT_MP_ATTACK_AIRWALK_GRENADE,
							ACT_MP_RELOAD_STAND,
							ACT_MP_RELOAD_STAND_LOOP,
							ACT_MP_RELOAD_STAND_END,
							ACT_MP_RELOAD_CROUCH,
							ACT_MP_RELOAD_CROUCH_LOOP,
							ACT_MP_RELOAD_CROUCH_END,
							ACT_MP_RELOAD_SWIM,
							ACT_MP_RELOAD_SWIM_LOOP,
							ACT_MP_RELOAD_SWIM_END,
							ACT_MP_RELOAD_AIRWALK,
							ACT_MP_RELOAD_AIRWALK_LOOP,
							ACT_MP_RELOAD_AIRWALK_END,
							ACT_MP_ATTACK_STAND_PREFIRE,
							ACT_MP_ATTACK_STAND_POSTFIRE,
							ACT_MP_ATTACK_STAND_STARTFIRE,
							ACT_MP_ATTACK_CROUCH_PREFIRE,
							ACT_MP_ATTACK_CROUCH_POSTFIRE,
							ACT_MP_ATTACK_SWIM_PREFIRE,
							ACT_MP_ATTACK_SWIM_POSTFIRE,

							// Multiplayer - Primary
							ACT_MP_STAND_PRIMARY,
							ACT_MP_CROUCH_PRIMARY,
							ACT_MP_RUN_PRIMARY,
							ACT_MP_WALK_PRIMARY,
							ACT_MP_AIRWALK_PRIMARY,
							ACT_MP_CROUCHWALK_PRIMARY,
							ACT_MP_JUMP_PRIMARY,
							ACT_MP_JUMP_START_PRIMARY,
							ACT_MP_JUMP_FLOAT_PRIMARY,
							ACT_MP_JUMP_LAND_PRIMARY,
							ACT_MP_SWIM_PRIMARY,
							ACT_MP_DEPLOYED_PRIMARY,
							ACT_MP_SWIM_DEPLOYED_PRIMARY,

							ACT_MP_ATTACK_STAND_PRIMARY,		// RUN, WALK
							ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
							ACT_MP_ATTACK_CROUCH_PRIMARY,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
							ACT_MP_ATTACK_SWIM_PRIMARY,
							ACT_MP_ATTACK_AIRWALK_PRIMARY,

							ACT_MP_RELOAD_STAND_PRIMARY,		// RUN, WALK
							ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
							ACT_MP_RELOAD_STAND_PRIMARY_END,
							ACT_MP_RELOAD_CROUCH_PRIMARY,		// CROUCHWALK
							ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
							ACT_MP_RELOAD_CROUCH_PRIMARY_END,
							ACT_MP_RELOAD_SWIM_PRIMARY,
							ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
							ACT_MP_RELOAD_SWIM_PRIMARY_END,
							ACT_MP_RELOAD_AIRWALK_PRIMARY,
							ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
							ACT_MP_RELOAD_AIRWALK_PRIMARY_END,

							ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
							ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,

							// Secondary
							ACT_MP_STAND_SECONDARY,
							ACT_MP_CROUCH_SECONDARY,
							ACT_MP_RUN_SECONDARY,
							ACT_MP_WALK_SECONDARY,
							ACT_MP_AIRWALK_SECONDARY,
							ACT_MP_CROUCHWALK_SECONDARY,
							ACT_MP_JUMP_SECONDARY,
							ACT_MP_JUMP_START_SECONDARY,
							ACT_MP_JUMP_FLOAT_SECONDARY,
							ACT_MP_JUMP_LAND_SECONDARY,
							ACT_MP_SWIM_SECONDARY,

							ACT_MP_ATTACK_STAND_SECONDARY,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_SECONDARY,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_SECONDARY,
							ACT_MP_ATTACK_AIRWALK_SECONDARY,

							ACT_MP_RELOAD_STAND_SECONDARY,		// RUN, WALK
							ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
							ACT_MP_RELOAD_STAND_SECONDARY_END,
							ACT_MP_RELOAD_CROUCH_SECONDARY,		// CROUCHWALK
							ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
							ACT_MP_RELOAD_CROUCH_SECONDARY_END,
							ACT_MP_RELOAD_SWIM_SECONDARY,
							ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
							ACT_MP_RELOAD_SWIM_SECONDARY_END,
							ACT_MP_RELOAD_AIRWALK_SECONDARY,
							ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
							ACT_MP_RELOAD_AIRWALK_SECONDARY_END,

							ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
							ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,

							// Melee
							ACT_MP_STAND_MELEE,
							ACT_MP_CROUCH_MELEE,
							ACT_MP_RUN_MELEE,
							ACT_MP_WALK_MELEE,
							ACT_MP_AIRWALK_MELEE,
							ACT_MP_CROUCHWALK_MELEE,
							ACT_MP_JUMP_MELEE,
							ACT_MP_JUMP_START_MELEE,
							ACT_MP_JUMP_FLOAT_MELEE,
							ACT_MP_JUMP_LAND_MELEE,
							ACT_MP_SWIM_MELEE,

							ACT_MP_ATTACK_STAND_MELEE,		// RUN, WALK
							ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
							ACT_MP_ATTACK_CROUCH_MELEE,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
							ACT_MP_ATTACK_SWIM_MELEE,
							ACT_MP_ATTACK_AIRWALK_MELEE,

							ACT_MP_ATTACK_STAND_GRENADE_MELEE,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
							ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,

							// Item1
							ACT_MP_STAND_ITEM1,
							ACT_MP_CROUCH_ITEM1,
							ACT_MP_RUN_ITEM1,
							ACT_MP_WALK_ITEM1,
							ACT_MP_AIRWALK_ITEM1,
							ACT_MP_CROUCHWALK_ITEM1,
							ACT_MP_JUMP_ITEM1,
							ACT_MP_JUMP_START_ITEM1,
							ACT_MP_JUMP_FLOAT_ITEM1,
							ACT_MP_JUMP_LAND_ITEM1,
							ACT_MP_SWIM_ITEM1,

							ACT_MP_ATTACK_STAND_ITEM1,		// RUN, WALK
							ACT_MP_ATTACK_STAND_ITEM1_SECONDARY,
							ACT_MP_ATTACK_CROUCH_ITEM1,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY,
							ACT_MP_ATTACK_SWIM_ITEM1,
							ACT_MP_ATTACK_AIRWALK_ITEM1,

							// Item2
							ACT_MP_STAND_ITEM2,
							ACT_MP_CROUCH_ITEM2,
							ACT_MP_RUN_ITEM2,
							ACT_MP_WALK_ITEM2,
							ACT_MP_AIRWALK_ITEM2,
							ACT_MP_CROUCHWALK_ITEM2,
							ACT_MP_JUMP_ITEM2,
							ACT_MP_JUMP_START_ITEM2,
							ACT_MP_JUMP_FLOAT_ITEM2,
							ACT_MP_JUMP_LAND_ITEM2,
							ACT_MP_SWIM_ITEM2,

							ACT_MP_ATTACK_STAND_ITEM2,		// RUN, WALK
							ACT_MP_ATTACK_STAND_ITEM2_SECONDARY,
							ACT_MP_ATTACK_CROUCH_ITEM2,		// CROUCHWALK
							ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY,
							ACT_MP_ATTACK_SWIM_ITEM2,
							ACT_MP_ATTACK_AIRWALK_ITEM2,

							// Flinches
							ACT_MP_GESTURE_FLINCH,
							ACT_MP_GESTURE_FLINCH_PRIMARY,
							ACT_MP_GESTURE_FLINCH_SECONDARY,
							ACT_MP_GESTURE_FLINCH_MELEE,
							ACT_MP_GESTURE_FLINCH_ITEM1,
							ACT_MP_GESTURE_FLINCH_ITEM2,

							ACT_MP_GESTURE_FLINCH_HEAD,
							ACT_MP_GESTURE_FLINCH_CHEST,
							ACT_MP_GESTURE_FLINCH_STOMACH,
							ACT_MP_GESTURE_FLINCH_LEFTARM,
							ACT_MP_GESTURE_FLINCH_RIGHTARM,
							ACT_MP_GESTURE_FLINCH_LEFTLEG,
							ACT_MP_GESTURE_FLINCH_RIGHTLEG,

							// Team Fortress specific - medic heal, medic infect, etc.....
							ACT_MP_GRENADE1_DRAW,
							ACT_MP_GRENADE1_IDLE,
							ACT_MP_GRENADE1_ATTACK,
							ACT_MP_GRENADE2_DRAW,
							ACT_MP_GRENADE2_IDLE,
							ACT_MP_GRENADE2_ATTACK,

							ACT_MP_PRIMARY_GRENADE1_DRAW,
							ACT_MP_PRIMARY_GRENADE1_IDLE,
							ACT_MP_PRIMARY_GRENADE1_ATTACK,
							ACT_MP_PRIMARY_GRENADE2_DRAW,
							ACT_MP_PRIMARY_GRENADE2_IDLE,
							ACT_MP_PRIMARY_GRENADE2_ATTACK,

							ACT_MP_SECONDARY_GRENADE1_DRAW,
							ACT_MP_SECONDARY_GRENADE1_IDLE,
							ACT_MP_SECONDARY_GRENADE1_ATTACK,
							ACT_MP_SECONDARY_GRENADE2_DRAW,
							ACT_MP_SECONDARY_GRENADE2_IDLE,
							ACT_MP_SECONDARY_GRENADE2_ATTACK,

							ACT_MP_MELEE_GRENADE1_DRAW,
							ACT_MP_MELEE_GRENADE1_IDLE,
							ACT_MP_MELEE_GRENADE1_ATTACK,
							ACT_MP_MELEE_GRENADE2_DRAW,
							ACT_MP_MELEE_GRENADE2_IDLE,
							ACT_MP_MELEE_GRENADE2_ATTACK,

							ACT_MP_ITEM1_GRENADE1_DRAW,
							ACT_MP_ITEM1_GRENADE1_IDLE,
							ACT_MP_ITEM1_GRENADE1_ATTACK,
							ACT_MP_ITEM1_GRENADE2_DRAW,
							ACT_MP_ITEM1_GRENADE2_IDLE,
							ACT_MP_ITEM1_GRENADE2_ATTACK,

							ACT_MP_ITEM2_GRENADE1_DRAW,
							ACT_MP_ITEM2_GRENADE1_IDLE,
							ACT_MP_ITEM2_GRENADE1_ATTACK,
							ACT_MP_ITEM2_GRENADE2_DRAW,
							ACT_MP_ITEM2_GRENADE2_IDLE,
							ACT_MP_ITEM2_GRENADE2_ATTACK,

							// Building
							ACT_MP_STAND_BUILDING,
							ACT_MP_CROUCH_BUILDING,
							ACT_MP_RUN_BUILDING,
							ACT_MP_WALK_BUILDING,
							ACT_MP_AIRWALK_BUILDING,
							ACT_MP_CROUCHWALK_BUILDING,
							ACT_MP_JUMP_BUILDING,
							ACT_MP_JUMP_START_BUILDING,
							ACT_MP_JUMP_FLOAT_BUILDING,
							ACT_MP_JUMP_LAND_BUILDING,
							ACT_MP_SWIM_BUILDING,

							ACT_MP_ATTACK_STAND_BUILDING,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_BUILDING,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_BUILDING,
							ACT_MP_ATTACK_AIRWALK_BUILDING,

							ACT_MP_ATTACK_STAND_GRENADE_BUILDING,		// RUN, WALK
							ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,		// CROUCHWALK
							ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
							ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,

							ACT_MP_STAND_PDA,
							ACT_MP_CROUCH_PDA,
							ACT_MP_RUN_PDA,
							ACT_MP_WALK_PDA,
							ACT_MP_AIRWALK_PDA,
							ACT_MP_CROUCHWALK_PDA,
							ACT_MP_JUMP_PDA,
							ACT_MP_JUMP_START_PDA,
							ACT_MP_JUMP_FLOAT_PDA,
							ACT_MP_JUMP_LAND_PDA,
							ACT_MP_SWIM_PDA,

							ACT_MP_ATTACK_STAND_PDA,
							ACT_MP_ATTACK_SWIM_PDA,

							ACT_MP_GESTURE_VC_HANDMOUTH,
							ACT_MP_GESTURE_VC_FINGERPOINT,
							ACT_MP_GESTURE_VC_FISTPUMP,
							ACT_MP_GESTURE_VC_THUMBSUP,
							ACT_MP_GESTURE_VC_NODYES,
							ACT_MP_GESTURE_VC_NODNO,

							ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
							ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
							ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
							ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
							ACT_MP_GESTURE_VC_NODYES_PRIMARY,
							ACT_MP_GESTURE_VC_NODNO_PRIMARY,

							ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
							ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
							ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
							ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
							ACT_MP_GESTURE_VC_NODYES_SECONDARY,
							ACT_MP_GESTURE_VC_NODNO_SECONDARY,

							ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
							ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
							ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
							ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
							ACT_MP_GESTURE_VC_NODYES_MELEE,
							ACT_MP_GESTURE_VC_NODNO_MELEE,

							ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1,
							ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1,
							ACT_MP_GESTURE_VC_FISTPUMP_ITEM1,
							ACT_MP_GESTURE_VC_THUMBSUP_ITEM1,
							ACT_MP_GESTURE_VC_NODYES_ITEM1,
							ACT_MP_GESTURE_VC_NODNO_ITEM1,

							ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2,
							ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2,
							ACT_MP_GESTURE_VC_FISTPUMP_ITEM2,
							ACT_MP_GESTURE_VC_THUMBSUP_ITEM2,
							ACT_MP_GESTURE_VC_NODYES_ITEM2,
							ACT_MP_GESTURE_VC_NODNO_ITEM2,

							ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
							ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
							ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
							ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
							ACT_MP_GESTURE_VC_NODYES_BUILDING,
							ACT_MP_GESTURE_VC_NODNO_BUILDING,

							ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
							ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
							ACT_MP_GESTURE_VC_FISTPUMP_PDA,
							ACT_MP_GESTURE_VC_THUMBSUP_PDA,
							ACT_MP_GESTURE_VC_NODYES_PDA,
							ACT_MP_GESTURE_VC_NODNO_PDA,


							ACT_VM_UNUSABLE,
							ACT_VM_UNUSABLE_TO_USABLE,
							ACT_VM_USABLE_TO_UNUSABLE,

							// Specific viewmodel activities for weapon roles
							ACT_PRIMARY_VM_DRAW,
							ACT_PRIMARY_VM_HOLSTER,
							ACT_PRIMARY_VM_IDLE,
							ACT_PRIMARY_VM_PULLBACK,
							ACT_PRIMARY_VM_PRIMARYATTACK,
							ACT_PRIMARY_VM_SECONDARYATTACK,
							ACT_PRIMARY_VM_RELOAD,
							ACT_PRIMARY_VM_DRYFIRE,
							ACT_PRIMARY_VM_IDLE_TO_LOWERED,
							ACT_PRIMARY_VM_IDLE_LOWERED,
							ACT_PRIMARY_VM_LOWERED_TO_IDLE,

							ACT_SECONDARY_VM_DRAW,
							ACT_SECONDARY_VM_HOLSTER,
							ACT_SECONDARY_VM_IDLE,
							ACT_SECONDARY_VM_PULLBACK,
							ACT_SECONDARY_VM_PRIMARYATTACK,
							ACT_SECONDARY_VM_SECONDARYATTACK,
							ACT_SECONDARY_VM_RELOAD,
							ACT_SECONDARY_VM_DRYFIRE,
							ACT_SECONDARY_VM_IDLE_TO_LOWERED,
							ACT_SECONDARY_VM_IDLE_LOWERED,
							ACT_SECONDARY_VM_LOWERED_TO_IDLE,

							ACT_MELEE_VM_DRAW,
							ACT_MELEE_VM_HOLSTER,
							ACT_MELEE_VM_IDLE,
							ACT_MELEE_VM_PULLBACK,
							ACT_MELEE_VM_PRIMARYATTACK,
							ACT_MELEE_VM_SECONDARYATTACK,
							ACT_MELEE_VM_RELOAD,
							ACT_MELEE_VM_DRYFIRE,
							ACT_MELEE_VM_IDLE_TO_LOWERED,
							ACT_MELEE_VM_IDLE_LOWERED,
							ACT_MELEE_VM_LOWERED_TO_IDLE,

							ACT_PDA_VM_DRAW,
							ACT_PDA_VM_HOLSTER,
							ACT_PDA_VM_IDLE,
							ACT_PDA_VM_PULLBACK,
							ACT_PDA_VM_PRIMARYATTACK,
							ACT_PDA_VM_SECONDARYATTACK,
							ACT_PDA_VM_RELOAD,
							ACT_PDA_VM_DRYFIRE,
							ACT_PDA_VM_IDLE_TO_LOWERED,
							ACT_PDA_VM_IDLE_LOWERED,
							ACT_PDA_VM_LOWERED_TO_IDLE,

							ACT_ITEM1_VM_DRAW,
							ACT_ITEM1_VM_HOLSTER,
							ACT_ITEM1_VM_IDLE,
							ACT_ITEM1_VM_PULLBACK,
							ACT_ITEM1_VM_PRIMARYATTACK,
							ACT_ITEM1_VM_SECONDARYATTACK,
							ACT_ITEM1_VM_RELOAD,
							ACT_ITEM1_VM_DRYFIRE,
							ACT_ITEM1_VM_IDLE_TO_LOWERED,
							ACT_ITEM1_VM_IDLE_LOWERED,
							ACT_ITEM1_VM_LOWERED_TO_IDLE,

							ACT_ITEM2_VM_DRAW,
							ACT_ITEM2_VM_HOLSTER,
							ACT_ITEM2_VM_IDLE,
							ACT_ITEM2_VM_PULLBACK,
							ACT_ITEM2_VM_PRIMARYATTACK,
							ACT_ITEM2_VM_SECONDARYATTACK,
							ACT_ITEM2_VM_RELOAD,
							ACT_ITEM2_VM_DRYFIRE,
							ACT_ITEM2_VM_IDLE_TO_LOWERED,
							ACT_ITEM2_VM_IDLE_LOWERED,
							ACT_ITEM2_VM_LOWERED_TO_IDLE,

							// Infested activities
							ACT_RELOAD_SUCCEED,
							ACT_RELOAD_FAIL,
							// Autogun
							ACT_WALK_AIM_AUTOGUN,
							ACT_RUN_AIM_AUTOGUN,
							ACT_IDLE_AUTOGUN,
							ACT_IDLE_AIM_AUTOGUN,
							ACT_RELOAD_AUTOGUN,
							ACT_CROUCH_IDLE_AUTOGUN,
							ACT_RANGE_ATTACK_AUTOGUN,
							ACT_JUMP_AUTOGUN,
							// Pistol
							ACT_IDLE_AIM_PISTOL,
							// PDW
							ACT_WALK_AIM_DUAL,
							ACT_RUN_AIM_DUAL,
							ACT_IDLE_DUAL,
							ACT_IDLE_AIM_DUAL,
							ACT_RELOAD_DUAL,
							ACT_CROUCH_IDLE_DUAL,
							ACT_RANGE_ATTACK_DUAL,
							ACT_JUMP_DUAL,
							// Shotgun
							ACT_IDLE_SHOTGUN,
							ACT_IDLE_AIM_SHOTGUN,
							ACT_CROUCH_IDLE_SHOTGUN,
							ACT_JUMP_SHOTGUN,
							// Rifle
							ACT_IDLE_AIM_RIFLE,
							ACT_RELOAD_RIFLE,
							ACT_CROUCH_IDLE_RIFLE,
							ACT_RANGE_ATTACK_RIFLE,
							ACT_JUMP_RIFLE,

							// Infested General AI
							ACT_SLEEP,
							ACT_WAKE,

							// Shield Bug
							ACT_FLICK_LEFT,
							ACT_FLICK_LEFT_MIDDLE,
							ACT_FLICK_RIGHT_MIDDLE,
							ACT_FLICK_RIGHT,
							ACT_SPINAROUND,

							// Mortar Bug
							ACT_PREP_TO_FIRE,
							ACT_FIRE,
							ACT_FIRE_RECOVER,

							// Shaman
							ACT_SPRAY,

							// Boomer
							ACT_PREP_EXPLODE,
							ACT_EXPLODE,

							// this is the end of the global activities, private per-monster activities start here.
							LAST_SHARED_ACTIVITY,
} Activity;


static const char *Ranks[] =
{
	"Unranked",
	"Silver I",
	"Silver II",
	"Silver III",
	"Silver IV",
	"Silver Elite",
	"Silver Elite Master",

	"pWhite Nova I",
	"pWhite Nova II",
	"pWhite Nova III",
	"pWhite Nova Master",
	"Master Guardian I",
	"Master Guardian II",

	"Master Guardian Elite",
	"Distinguished Master Guardian",
	"Legendary Eagle",
	"Legendary Eagle Master",
	"Supreme Master First Class",
	"The Global Elite"
};
class CollisionProperty
{
public:
	Vector VecMins()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x8);
	}
	Vector VecMaxs()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x14);
	}
};


typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;
typedef unsigned char uint8;
class IClientRenderable
{
public:
	virtual IClientUnknown*            GetIClientUnknown() = 0;
	virtual Vector const&              GetRenderOrigin(void) = 0;
	virtual QAngle const&              GetRenderAngles(void) = 0;
	virtual bool                       ShouldDraw(void) = 0;
	virtual int                        GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void                       Unused(void) const {}
	virtual ClientShadowHandle_t       GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&      RenderHandle() = 0;
	virtual const model_t*             GetModel() const = 0;
	virtual int                        DrawModel(int flags, const int /*RenderableInstance_t*/ &instance) = 0;
	virtual int                        GetBody() = 0;
	virtual void                       GetColorModulation(float* color) = 0;
	virtual bool                       LODTest() = 0;
	virtual bool                       SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       SetupWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void                       DoAnimationEvents(void) = 0;
	virtual void* /*IPVSNotify*/       GetPVSNotifyInterface() = 0;
	virtual void                       GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetShadowRenderBounds(Vector &mins, Vector &maxs, int /*ShadowType_t*/ shadowType) = 0;
	virtual bool                       ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool                       GetShadowCastDistance(float *pDist, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       GetShadowCastDirection(Vector *pDirection, int /*ShadowType_t*/ shadowType) const = 0;
	virtual bool                       IsShadowDirty() = 0;
	virtual void                       MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*         GetShadowParent() = 0;
	virtual IClientRenderable*         FirstShadowChild() = 0;
	virtual IClientRenderable*         NextShadowPeer() = 0;
	virtual int /*ShadowType_t*/       ShadowCastType() = 0;
	virtual void                       CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t      GetModelInstance() = 0;
	virtual const matrix3x4_t&         RenderableToWorldTransform() = 0;
	virtual int                        LookupAttachment(const char *pAttachmentName) = 0;
	virtual   bool                     GetAttachment(int number, Vector &origin, QAngle &angles) = 0;
	virtual bool                       GetAttachment(int number, matrix3x4_t &matrix) = 0;
	virtual float*                     GetRenderClipPlane(void) = 0;
	virtual int                        GetSkin() = 0;
	virtual void                       OnThreadedDrawSetup() = 0;
	virtual bool                       UsesFlexDelayedWeights() = 0;
	virtual void                       RecordToolMessage() = 0;
	virtual bool                       ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual uint8                      OverrideAlphaModulation(uint8 nAlpha) = 0;
	virtual uint8                      OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
	bool SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		typedef bool(__thiscall* oSetupBones)(PVOID, VMatrix *, int, int, float);
		return g_Utils->get_vfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
	const model_t* GetModel() //void*
	{
		typedef const model_t*(__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(this, 8)(this);
	}
};


class IClientUnknown
{
public:
	virtual CollisionProperty*		GetCollideable() = 0;
	virtual IClientNetworkable*	GetClientNetworkable() = 0;
	virtual IClientRenderable*	GetClientRenderable() = 0;
	virtual void*		GetIClientCBaseEntity() = 0;
	virtual void*		GetBaseCBaseEntity() = 0;
	virtual IClientThinkable*	GetClientThinkable() = 0;
};
class IClientThinkable
{
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void*				GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
	virtual void				Release() = 0;
};


struct datamap_t;
class typedescription_t;

class VarMapEntry_t
{
public:
	unsigned short		type;
	unsigned short		m_bNeedsToInterpolate;	// Set to false when this var doesn't
												// need Interpolate() called on it anymore.
	void				*data;
	void	*watcher;
};

struct VarMapping_t
{
	VarMapping_t()
	{
		m_nInterpolatedEntries = 0;
	}

	VarMapEntry_t* m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationTime;
};


class CBaseAnimating
{
public:

	enum
	{
		NUM_POSEPAREMETERS = 24,
		NUM_BONECTRLS = 4
	};



};



class typedescription_t
{
public:
	int32_t fieldType; //0x0000
	char* fieldName; //0x0004
	int fieldOffset[TD_OFFSET_COUNT]; //0x0008
	int16_t fieldSize_UNKNWN; //0x0010
	int16_t flags_UNKWN; //0x0012
	char pad_0014[12]; //0x0014
	datamap_t* td; //0x0020
	char pad_0024[24]; //0x0024
}; //Size: 0x003C


   //-----------------------------------------------------------------------------
   // Purpose: stores the list of objects in the hierarchy
   //            used to iterate through an object's data descriptions
   //-----------------------------------------------------------------------------
struct datamap_t
{
	typedescription_t    *dataDesc;
	int                    dataNumFields;
	char const            *dataClassName;
	datamap_t            *baseMap;

	bool                chains_validated;
	// Have the "packed" offsets been computed
	bool                packed_offsets_computed;
	int                    packed_size;
};






class C_BaseEntity
{
public:

	matrix3x4_t GetBoneMatrix(int BoneID)
	{
		matrix3x4_t matrix;

		uintptr_t m_dwBoneMatrix = 0x2698;
		auto offset = *reinterpret_cast<uintptr_t*>(uintptr_t(this) + m_dwBoneMatrix);
		if (offset)
			matrix = *reinterpret_cast<matrix3x4_t*>(offset + 0x30 * BoneID);

		return matrix;
	}

	datamap_t * GetPredDescMap()
	{
		typedef datamap_t*(__thiscall *o_GetPredDescMap)(void*);
		return g_Utils->get_vfunc<o_GetPredDescMap>(this, 17)(this);
	}

	CBaseHandle* m_hMyWeapons()
	{
		return (CBaseHandle*)((uintptr_t)this + G_sets.m_hMyWeapons);
	}

	bool IsPlayer();
	float_t & m_flMaxspeed();
	float_t & m_surfaceFriction();
	UINT PhysicsSolidMaskForEntity()
	{
		typedef UINT(__thiscall* Fn)(void*);
		return g_Utils->get_vfunc<Fn>(this, 148)(this);
	}
	UINT* GetWearables()
	{
		return reinterpret_cast<UINT*>((DWORD)this + G_sets.m_hMyWearables);
	}
	int GetChockedPackets();
	float GetOldSimulationTime();


	static void UpdateAnimationState(CCSGOPlayerAnimState *state, QAngle angle);
	static void ResetAnimationState(CCSGOPlayerAnimState *state);
	void CreateAnimationState(CCSGOPlayerAnimState *state);


	Vector& m_vecNetworkOrigin();
	bool IsTargettingLocal();
	//virtual IClientUnknown*		GetIClientUnknown();
	//{
	//	return (IClientUnknown*)this; //index0
	//}


	void SetCurrentCommand(CUserCmd * cmd);
	void InvalidateBoneCache();


	std::array<float, 24>& m_flPoseParameter();


	bool IsValidRenderable();

	void UpdateClientSideAnimation();

	void SetAbsOrigin(const Vector & origin);

	int draw_model(int flags, uint8_t alpha) {
		using fn = int(__thiscall*)(void*, int, uint8_t);
		return g_Utils->get_vfunc< fn >(GetRenderable(), 9)(GetRenderable(), flags, alpha);
	}


	bool IsValidTarget();

	void SetAngle2(Vector wantedang);

	bool SetupBones2(matrix3x4_t * pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);

	bool canHit(Vector end, C_BaseEntity * ent);

	Vector GetHedPos();

	Vector GetBonePos(int i);



	Vector GetBonePos(int i, matrix3x4_t* matrix);


	CBaseAnimating*		GetBaseAnimating()
	{
		typedef CBaseAnimating*& (__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(this, 1)(this);
	} //vtable index 1
	float GetUpdateTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0xA9FC + 0x8); // was cast to int*
	}
	int GetSequence()
	{
		return *reinterpret_cast<int*>((DWORD)this + G_sets.m_nSequence);
	}
	int SetSequence(int seq)
	{
		return *reinterpret_cast<int*>((DWORD)this + G_sets.m_nSequence) = seq;
	}
	float GetCycle()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flCycle); // was cast to int*
	}

	float SetCycle(float cycle)
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flCycle) = cycle; // was cast to int*
	}

	float LowerBodyYaw()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flLowerBodyYawTarget);
	}
	BYTE GetLifeState()
	{
		return *(BYTE*)((DWORD)this + (DWORD)G_sets.m_lifeState);
	}
	bool IsValid()
	{
		bool bValid = (this != nullptr && GetLifeState() == 0 && GetHealth() > 0 && !IsDormant()) ? true : false;
		return bValid;
	}
	int GetCrossId()
	{
		return *reinterpret_cast<int*>((DWORD)this + (DWORD)0xB2A4);
	}
	AnimationLayer *GetAnimOverlays();
	AnimationLayer *GetAnimOverlay(int i);
	AnimationLayer & GetAnimOverlay2(int Index);
	int GetSequenceActivity(int sequence);
	CBasePlayerAnimState *GetBasePlayerAnimState();
	//CBasePlayerAnimState * GetAnimState();
	CCSPlayerAnimState *GetPlayerAnimState();

	float *FlashMaxAlpha()
	{
		return reinterpret_cast<float*>((DWORD)this + G_sets.m_flFlashMaxAlpha);
	}
	float GetMaxSpeed()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flMaxSpeed);
	}
	float GetAnimationTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + /*G_sets.m_flAnimTime*/0x3C);
	}
	float GetSimulationTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flSimulationTime);
	}
	int GetNumAnimOverlays()
	{
		return *(int*)((DWORD)this + 0x297C);
	}

	int &GetTickBase(void)
	{
		return *(int*)((DWORD)this + G_sets.m_nTickBase);
	}
	int GetHitboxSet()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x09FC);
	}
	Vector GetAngRotation()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x0128);
	}
	Vector GetPredictedEyePosition(float interval_per_tick)
	{
		return GetEyePosition() + (GetVelocity() * interval_per_tick);
	}
	float Friction()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x0140);
	}
	int GetTeamNum()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xF0);
	}

	int GetArmor()
	{
		return *reinterpret_cast<int*>((DWORD)this + G_sets.m_ArmorValue);
	}
	char* GetArmorName()
	{
		if (GetArmor() > 0)
		{
			if (HasHelmet())
				return "hk";
			else
				return "k";
		}
		else
			return " ";
	}
	bool m_bHasHeavyArmor()
	{
		return *(bool*)((DWORD)this + G_sets.m_bHasHeavyArmor);
	}
	bool HasHelmet()
	{
		return *reinterpret_cast<bool*>((DWORD)this + G_sets.m_bHasHelmet);
	}
	Vector Velocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x0110);
	}

	int GetHealth()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xFC);
	}

	int Index()
	{
		return GetNetworkable()->EntIndex();
	}
	std::array<float, 24>& get_ragdoll_pos()
	{
		return *reinterpret_cast<std::array<float, 24>*>(reinterpret_cast<uintptr_t>(this) + 0x00002970);
	}
	VarMapping_t* GetVarMap()
	{
		return reinterpret_cast<VarMapping_t*>((DWORD)this + 0x24);
	}
	int* GetFlags()
	{
		return (int*)((DWORD)this + G_sets.m_fFlags);
	}
	float GetFriction()
	{
		return *reinterpret_cast<float*>(uintptr_t(this + G_sets.m_flFriction));
	}
	float GetFallVelocity()
	{
		return *reinterpret_cast<float*>(uintptr_t(this + G_sets.m_flFallVelocity));
	}
	int GetShotsFired()
	{
		return *reinterpret_cast<int*>((DWORD)this + G_sets.m_iShotsFired);
	}
	Vector& GetAbsOrigin()
	{
		static Vector defaultVector = Vector(0, 0, 0);

		if (!this)
			return defaultVector;


		typedef Vector& (__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(this, 10)(this);
	}

	void SetFlags(int flags)
	{
		*reinterpret_cast<int*>(uintptr_t(this) + G_sets.m_fFlags) = flags;
	}

	void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		void* pRenderable = (void*)(this + 0x4);
		typedef void(__thiscall* Fn)(void*, Vector&, Vector&);
		g_Utils->get_vfunc<Fn>(pRenderable, 17)(pRenderable, mins, maxs);
	}

	bool IsMoving()
	{
		if (this->GetVelocity().Length() > 50)
			return true;
		return false;
	}
	Vector GetEyePosition(void)
	{
		Vector Vec{};

		g_Utils->get_vfunc<void(__thiscall*)(void*, Vector&)>(this, 277)(this, Vec);
		return Vec;
	}

	Vector GetEyePosition2(void)
	{
		return GetAbsOrigin() + *(Vector*)((DWORD)this + G_sets.m_vecViewOffset);
	}


	Vector GetOrigin()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + G_sets.m_vecOrigin);
	}

	Vector GetEyePosition3(void)
	{
		return GetOrigin() + *(Vector*)((DWORD)this + G_sets.m_vecViewOffset);
	}

	Vector& get_abs_eye_angles()
	{
		return g_Utils->get_vfunc<Vector&(__thiscall*)(void*)>(this, 11)(this);
	}
	float GetStepSize()
	{
		return *reinterpret_cast<float*>(uintptr_t(this + G_sets.m_flStepSize));
	}
	Vector SetOrigin(Vector Origin)
	{
		*(Vector*)((DWORD)this + G_sets.m_vecOrigin) = Origin;
	}
	Vector GetViewOffset()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x0104);;
	}
	Vector GetBaseVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + G_sets.m_vecBaseVelocity);
	}
	int GetActiveWeaponIndex()
	{
		return *reinterpret_cast<int*>(uintptr_t(this) + G_sets.m_hActiveWeapon) & 0xFFF;
	}
	void SetBaseVelocity(Vector Velocity)
	{
		*(Vector*)((DWORD)this + G_sets.m_vecBaseVelocity) = Velocity;
	}
	void SetVelocity(Vector Velocity)
	{
		*(Vector*)((DWORD)this + G_sets.m_vecVelocity) = Velocity;
	}
	void SetFallVelocity(float FallVelocity)
	{
		*(float*)((DWORD)this + G_sets.m_flFallVelocity) = FallVelocity;
	}

	Vector& GetAbsAngles()
	{
		typedef Vector& (__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(this, 11)(this);
		//return *reinterpret_cast<Vector*>((DWORD)this + 0x0128);
	}

	void* GetClientClass()
	{
		void* Networkable = (void*)(this + 0x8);
		typedef void* (__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(Networkable, 2)(Networkable);
	}
	bool UnkAwCeck()
	{
		typedef bool* (__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(this, 152)(this);
	}
	Vector GetVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + G_sets.m_vecVelocity);
	}
	bool IsDormant()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0xE9);
	}

	float MaxSpeed()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x3240);
	}

	DWORD C_BaseEntity::GetObserverTargetHandle()
	{
		return *(DWORD*)((DWORD)this + G_sets.m_hObserverTarget);
	}

	bool isAlive()
	{
		BYTE lifestate = *(BYTE*)((DWORD)this + 0x025B);
		return (lifestate == 0);
	}

	bool Sanity_Checks(C_BaseEntity* Entity);
	

	int GetIndex()
	{
		//	void* networkable = (void*)(this + 0x8);
		//typedef int(__thiscall* OriginalFn)(PVOID);
		//return g_Utils->get_vfunc<OriginalFn>(this, 76)(this);
		return GetNetworkable()->EntIndex();
	}
	IClientNetworkable* GetNetworkable()
	{
		return reinterpret_cast<IClientNetworkable*>((DWORD)this + 0x8);
	}

	bool SetupBones(VMatrix *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);

	const model_t* GetModel() //void*
	{
		void *pRenderable = (void*)(this + 0x4);
		typedef const model_t*(__thiscall* OriginalFn)(PVOID);
		return g_Utils->get_vfunc<OriginalFn>(pRenderable, 8)(pRenderable);
	}
	float GetPoseParameter()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x2764);

	}
	int GetCollisionGroup()
	{
		return *reinterpret_cast<int*>((DWORD)this + G_sets.m_CollisionGroup);
		//GetNetVar 
	}
	bool IsBroken()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x0A04);
	}
	CollisionProperty* GetCollision()
	{
		return reinterpret_cast<CollisionProperty*>((DWORD)this + 0x0318);
	}

	VMatrix& GetCollisionBoundTrans()
	{
		return *reinterpret_cast<VMatrix*>((DWORD)this + 0x0440);
	}
	IClientRenderable* GetRenderable()
	{
		return reinterpret_cast<IClientRenderable*>((DWORD)this + 0x4);
	}
	bool IsScoped()
	{
		return *reinterpret_cast<bool*>((DWORD)this + G_sets.m_bIsScoped);
	}
	bool& GetClientSideAnimation()
	{
		return *reinterpret_cast<bool*>((DWORD)this + G_sets.m_bClientSideAnimation);
	}
	bool IsProtected(void)
	{
		return *(bool*)((DWORD)this + G_sets.m_bGunGameImmunity);
	}
	bool m_bFreezePeriod()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x20);
	}

	QAngle GetPunchAngle()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + 0x0000301C);
	}
	QAngle GetPunchAngleVelocity()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + 0x3020);
	}
	QAngle* GetPunchAnglePtr()
	{
		return reinterpret_cast<QAngle*>((DWORD)this + 0x301C);
	}
	QAngle GetViewPunch()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + 0x3010);
	}
	QAngle* GetViewPunchPtr()
	{
		return reinterpret_cast<QAngle*>((DWORD)this + 0x3010);
	}
	Vector* GetEyeAnglesPtr()
	{
		return reinterpret_cast<Vector*>((DWORD)this + G_sets.m_angEyeAngles);
	}
	Vector GetEyeAngles()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + G_sets.m_angEyeAngles);
	}
	void SetEyeAngles(Vector Angles)
	{
		*(Vector*)((uintptr_t)this + 0xAA08) = Angles;
	}
	CBaseCombatWeapon* GetWeapon();
	bool IsEnemy();
	void CopyPoseParameters(float * dest);
	bool ComputeHitboxSurroundingBox(Vector * pVecWorldMins, Vector * pVecWorldMaxs);
	int GetGlowIndex()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x0000A320);
	}
	UINT* GetWeapons()
	{
		return (UINT*)((DWORD)this + 0x00002DE8);
	}
	std::vector< CBaseCombatWeapon* > C_BaseEntity::GetWeaponsData();
	int GetMoveType()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x258);
	}
	Vector GetNetworkOrigin()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + G_sets.m_flFriction - sizeof(Vector));
	}
	int GetRank()
	{

		return *(int*)((DWORD)G_sets.dw_CSPlayerResource + G_sets.m_iCompetetiveRanking + this->Index() * 4);
	}
	const char* szRank()
	{
		return Ranks[GetRank()];
	}
	int GetWins()
	{
		return *(int*)((DWORD)G_sets.dw_CSPlayerResource + G_sets.m_iCompetetiveWins + this->Index() * 4);
	}
	int GetPing()
	{
		int size = this->Index() * sizeof(int);
		return *(int*)(uintptr_t(G_sets.dw_CSPlayerResource + G_sets.m_iPing + size));
	}
	int GetMoney()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0xB228);
	}
	std::array<float, 24> GetPoseParameters()
	{
		std::array<float, 24> flParam;
		float * flPose = (float*)((DWORD)this + G_sets.m_flPoseParameter);
		for (int i = 0; i < 23; i++)
		{
			flParam[i] = flPose[i];
		}
		return flParam;
	}
};




struct SpatializationInfo_t;
class IClientEntity : public IClientNetworkable
{
public:
	virtual void             Release(void) = 0;
	virtual const Vector     GetAbsOrigin(void) const = 0;
	virtual const QAngle     GetAbsAngles(void) const = 0;
	virtual void*            GetMouth(void) = 0;
	virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
	virtual bool             IsBlurred(void) = 0;
};

class IClientEntityList
{
public:
	virtual IClientNetworkable*   GetClientNetworkable(int entnum) = 0;
	virtual void*                 vtablepad0x1(void) = 0;
	virtual void*                 vtablepad0x2(void) = 0;
	virtual C_BaseEntity*         GetClientEntity(int entNum) = 0;
	virtual IClientEntity*        GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
	virtual void                  SetMaxEntities(int maxEnts) = 0;
	virtual int                   GetMaxEntities() = 0;

	C_BaseEntity* GetClientEntityFromHandle2(HANDLE Handle)
	{
		typedef C_BaseEntity*(__thiscall* Fn)(void*, HANDLE);
		return g_Utils->get_vfunc<Fn>(this, 7)(this, Handle);
	}
};




class CBomb
{
public:
	float GetC4BlowTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flC4Blow);
	}
	HANDLE GetOwnerEntity()
	{
		return *reinterpret_cast<HANDLE*>((DWORD)this + G_sets.m_hOwnerEntity);
	}
	bool IsDefused()
	{
		return *reinterpret_cast<bool*>((DWORD)this + G_sets.m_bBombDefused);
	}

	float DefuseTimer()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flDefuseCountDown);
	}
};
class CGrenade
{
public:
	bool IsPinPulled()
	{
		return *reinterpret_cast<bool*>((DWORD)this + G_sets.m_bPinPulled);
	}
	float GetThrowTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_fThrowTime);
	}
};
class CBaseCombatWeapon
{
	template<class T>
	T GetFieldValue(int offset) {
		return *(T*)((DWORD)this + offset);
	}
	template<class T>
	T* GetFieldPointer(int offset) {
		return (T*)((DWORD)this + offset);
	}
public:

	void SetPattern(int skin, int quality, int seed, int stattrak, const char* name)
	{

		*(int*)((DWORD)this + G_sets.m_nFallbackPaintKit) = skin;
		*(int*)((DWORD)this + G_sets.m_iEntityQuality) = quality;
		*(int*)((DWORD)this + G_sets.m_nFallbackSeed) = seed;
		*(int*)((DWORD)this + G_sets.m_nFallbackStatTrak) = stattrak;
		*(float*)((DWORD)this + G_sets.m_flFallbackWear) = 0.0001f;

		if (name != "") {
			char* a = (char*)((DWORD)this + G_sets.m_szCustomName);
			sprintf_s(a, 32, "%s", name);
		}

		*(int*)((DWORD)this + G_sets.m_iItemIDHigh) = -1;
	}

	//CBaseViewModel* GetViewModel()
	//{
	//	if (!this)
	//		return nullptr;
	//static std::uintptr_t offset = GET_NETVAR(XorStr("DT_BasePlayer"), XorStr("m_hViewModel[0]"));
	//return (CBaseViewModel*)I::ClientCBaseEntityList->GetClientEntityFromHandle(GetFieldValue<CHandle<CBaseViewModel>>(offset));
	//}

	HANDLE m_hWeaponWorldModel()
	{
		return *(HANDLE*)((uintptr_t)this + G_sets.m_hWeaponWorldModel);
	}

	int* OwnerXuidLow()
	{
		return (int*)((uintptr_t)this + G_sets.m_OriginalOwnerXuidLow);
	}
	int* OwnerXuidHigh()
	{
		return (int*)((uintptr_t)this + G_sets.m_OriginalOwnerXuidHigh);
	}

	bool IsValid()
	{
		WeaponType t = get_wpn_type();

		if (t != WeaponType::Knife && t != WeaponType::Grenade && t != WeaponType::Bomb)
		{
			if (Clip1() > 0)
				return true;
		}
		return false;
	}
	enum WeaponType : byte
	{
		Shotgun,
		Pistol,
		Automatic,
		Sniper,
		Grenade,
		Knife,
		Bomb
	};

	WeaponType get_wpn_type()
	{
		auto WeaponID = this->GetItemDefinitionIndex();

		if (WeaponID == WEAPON_XM1014 || WeaponID == WEAPON_NOVA || WeaponID == WEAPON_SAWEDOFF || WeaponID == WEAPON_MAG7)
			return WeaponType::Shotgun;

		if (WeaponID == WEAPON_P2000
			|| WeaponID == WEAPON_USPS
			|| WeaponID == WEAPON_GLOCK
			|| WeaponID == WEAPON_DUALS
			|| WeaponID == WEAPON_P250
			|| WeaponID == WEAPON_CZ75
			|| WeaponID == WEAPON_P2000
			|| WeaponID == WEAPON_FIVE7
			|| WeaponID == WEAPON_TEC9
			|| WeaponID == WEAPON_DEAGLE
			|| WeaponID == WEAPON_REVOLVER)
			return WeaponType::Pistol;

		if (WeaponID == WEAPON_M249
			|| WeaponID == WEAPON_NEGEV
			|| WeaponID == WEAPON_MAC10
			|| WeaponID == WEAPON_MP9
			|| WeaponID == WEAPON_MP7
			|| WeaponID == WEAPON_UMP45
			|| WeaponID == WEAPON_P90
			|| WeaponID == WEAPON_BIZON
			|| WeaponID == WEAPON_FAMAS
			|| WeaponID == WEAPON_GALIL
			|| WeaponID == WEAPON_M4A1
			|| WeaponID == WEAPON_M4A1S
			|| WeaponID == WEAPON_AUG
			|| WeaponID == WEAPON_SG553
			|| WeaponID == WEAPON_AK47)
			return WeaponType::Automatic;

		if (WeaponID == WEAPON_AWP
			|| WeaponID == WEAPON_SCAR20
			|| WeaponID == WEAPON_G3SG1)
			return WeaponType::Sniper;

		if (WeaponID == WEAPON_FLASH
			|| WeaponID == WEAPON_HE
			|| WeaponID == WEAPON_DECOY
			|| WeaponID == WEAPON_SMOKE
			|| WeaponID == WEAPON_MOLOTOV
			|| WeaponID == WEAPON_INC)
			return WeaponType::Grenade;

		if (WeaponID == WEAPON_KNIFE_SHADOWDAGGERS
			|| WeaponID == WEAPON_KNIFE_T
			|| WeaponID == WEAPON_KNIFE_CT
			|| WeaponID == WEAPON_KNIFE_BAYONET
			|| WeaponID == WEAPON_KNIFE_FLIP
			|| WeaponID == WEAPON_KNIFE_GUT
			|| WeaponID == WEAPON_KNIFE_KARAMBIT
			|| WeaponID == WEAPON_KNIFE_M9BAYONET
			|| WeaponID == WEAPON_KNIFE_HUNTSMAN
			|| WeaponID == WEAPON_KNIFE_FALCHION
			|| WeaponID == WEAPON_KNIFE_BUTTERFLY ||
			WeaponID == KNIFE_NAVAJA ||
			WeaponID == KNIFE_STILETTO ||
			WeaponID == KNIFE_URSUS ||
			WeaponID == KNIFE_TALON)
			return WeaponType::Knife;

		if (WeaponID == WEAPON_C4)
			return WeaponType::Bomb;
	}

	int* GetEntityQuality() {
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		return (int*)((DWORD)this + 0x2D70 + 0x40 + 0x1DC);
	}

	float* FallbackWear()
	{
		return (float*)((uintptr_t)this + G_sets.m_flFallbackWear);
	}



	inline int* GetFallbackPaintKit() {
		// DT_BaseAttributableItem -> m_nFallbackPaintKit: 0x3140
		return (int*)((DWORD)this + G_sets.m_nFallbackPaintKit);
	}

	int* ItemIDHigh()
	{
		return (int*)((uintptr_t)this + 0x1F0);
	}

	int* ViewModelIndex()
	{
		return (int*)((uintptr_t)this + G_sets.m_iViewModelIndex);
	}

	int* WorldModelIndex()
	{
		return (int*)((uintptr_t)this + G_sets.m_iWorldModelIndex);
	}

	int* ModelIndex()
	{
		return (int*)((uintptr_t)this + G_sets.m_nModeIndex);
	}

	short* ItemDefinitionIndex()
	{
		return (short*)((uintptr_t)this + 0x1D8);
	}

	model_t* CBaseCombatWeapon::GetModel()
	{
		return *(model_t**)((DWORD)this + 0x6C);
	}
	Vector GetOrigin()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x0134);
	}
	HANDLE GetOwnerCBaseEntity()
	{
		return *reinterpret_cast<HANDLE*>((DWORD)this + 0x0148);
	}

	float NextPrimaryAttack()
	{
		return *(float*)((DWORD)this + 0x3208);
	}

	float NextSecondaryAttack()
	{
		return *reinterpret_cast<float*>((DWORD)this + 0x31CC);
	}
	float GetAccuracyPenalty()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_fAccuracyPenalty);
	}
	int Clip1()
	{
		return *reinterpret_cast<int*>((DWORD)this + G_sets.m_iClip1);
	}

	char* GetGunText()
	{
		int WeaponId = this->WeaponID();
		switch (WeaponId)
		{
		case KNIFE:
		case 500:
		case 505:
		case 506:
		case 507:
		case 508:
		case 509:
		case 512:
		case 514:
		case 515:
		case 516:
		case 520:
		case 522:
		case 519:
		case 523:
			return "KNIFE";
		case DEAGLE:
			return "DEAGLE";
		case ELITE:
			return "BERRETS";
		case FIVESEVEN:
			return "FIVESEVEN";
		case GLOCK:
			return "GLOCK";
		case HKP2000:
			return "P2000";
		case P250:
			return "P250";
		case USP_SILENCER:
			return "USP";
		case TEC9:
			return "TEC9";
		case CZ75A:
			return "CZ75A";
		case REVOLVER:
			return "REVOLVER";
		case MAC10:
			return "MAC10";
		case UMP45:
			return "UMP45";
		case BIZON:
			return "BIZON";
		case MP7:
			return "MP7";
		case MP9:
			return "MP9";
		case P90:
			return "P90";
		case GALILAR:
			return "GALILAR";
		case FAMAS:
			return "FAMAS";
		case M4A1_SILENCER:
			return "M4A1-S";
		case M4A1:
			return "M4A1";
		case AUG:
			return "AUG";
		case SG556:
			return "SSG553";
		case AK47:
			return "AK47";
		case G3SG1:
			return "G3SG1";
		case SCAR20:
			return "SCAR20";
		case AWP:
			return "AWP";
		case SSG08:
			return "SSG08";
		case XM1014:
			return "XM1014";
		case SAWEDOFF:
			return "SAWED";
		case MAG7:
			return "MAG7";
		case NOVA:
			return "NOVA";
		case NEGEV:
			return "NEGEV";
		case M249:
			return "M249";
		case TASER:
			return "TASER";
		case FLASHBANG:
			return "FLASHBANG";
		case HEGRENADE:
			return "GRENADE";
		case SMOKEGRENADE:
			return "SMOKE";
		case MOLOTOV:
			return "MOLOTOV";
		case DECOY:
			return "DECOY";
		case INCGRENADE:
			return "MOLOTOV";
		case C4:
			return "C4";
		default:
			return " ";
		}
	}

	int GetMaxAmmoReserve(void)
	{
		return *(int*)((DWORD)this + G_sets.m_iPrimaryReserveAmmoCount);
	}
	int GetLoadedAmmo()
	{
		return *(int*)((DWORD)this + G_sets.m_iClip1);
	}
	int WeaponID()
	{
		return GetItemDefinitionIndex();
	}
	short GetItemDefinitionIndex(void)
	{
		if (!this) return 0;
		return *(short*)((DWORD)this + G_sets.m_iItemDefinitionIndex);
	}
	float GetPostponeFireReadyTime()
	{
		return *reinterpret_cast<float*>((DWORD)this + G_sets.m_flPostponeFireReadyTime);
	}
	int GetZoomLevel()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x3330);
	}
	const char* GetWeaponName()
	{
		typedef const char*(__thiscall* GetWeaponNameFn)(void*);
		GetWeaponNameFn Name = (GetWeaponNameFn)((*(PDWORD_PTR*)this)[378]);
		return Name(this);
	}
	std::string GetName(bool Ammo)
	{
		const char* name = GetWeaponName();
		std::string Name = name;
		std::string NName;
		NName = Name.substr(7, Name.length() - 7);


		if (Ammo && !this->IsMiscWeapon())
		{
			char buffer[32]; sprintf_s(buffer, " [%i]", Clip1());
			NName.append(buffer);
			return NName;
		}
		return NName;
	}
	char* GetGunIcon()
	{
		int WeaponId = this->WeaponID();
		switch (WeaponId)
		{
		case KNIFE:
		case 500:
		case 505:
		case 506:
		case 507:
		case 508:
		case 509:
		case 512:
		case 514:
		case 515:
		case 516:
		case 520:
		case 522:
		case 519:
		case 523:
			return "]";
		case DEAGLE:
			return "A";
		case ELITE:
			return "B";
		case FIVESEVEN:
			return "C";
		case GLOCK:
			return "D";
		case HKP2000:
			return "E";
		case P250:
			return "F";
		case USP_SILENCER:
			return "G";
		case TEC9:
			return "H";
		case CZ75A:
			return "I";
		case REVOLVER:
			return "J";
		case MAC10:
			return "K";
		case UMP45:
			return "L";
		case BIZON:
			return "M";
		case MP7:
			return "N";
		case MP9:
			return "O";
		case P90:
			return "P";
		case GALILAR:
			return "Q";
		case FAMAS:
			return "R";
		case M4A1_SILENCER:
			return "S";
		case M4A1:
			return "T";
		case AUG:
			return "U";
		case SG556:
			return "V";
		case AK47:
			return "W";
		case G3SG1:
			return "X";
		case SCAR20:
			return "Y";
		case AWP:
			return "Z";
		case SSG08:
			return "a";
		case XM1014:
			return "b";
		case SAWEDOFF:
			return "c";
		case MAG7:
			return "d";
		case NOVA:
			return "e";
		case NEGEV:
			return "f";
		case M249:
			return "g";
		case TASER:
			return "h";
		case FLASHBANG:
			return "i";
		case HEGRENADE:
			return "j";
		case SMOKEGRENADE:
			return "k";
		case MOLOTOV:
			return "l";
		case DECOY:
			return "m";
		case INCGRENADE:
			return "n";
		case C4:
			return "o";
		default:
			return " ";
		}
	}
	int GetWeaponType()
	{
		if (!this) return WEPCLASS_INVALID;
		auto id = this->WeaponID();
		switch (id)
		{
		case DEAGLE:
		case ELITE:
		case FIVESEVEN:
		case HKP2000:
		case USP_SILENCER:
		case CZ75A:
		case TEC9:
		case REVOLVER:
		case GLOCK:
		case P250:
			return WEPCLASS_PISTOL;
			break;
		case AK47:
		case M4A1:
		case M4A1_SILENCER:
		case GALILAR:
		case AUG:
		case FAMAS:
		case SG556:
		case MP5:
			return WEPCLASS_RIFLE;
			break;
		case P90:
		case BIZON:
		case MP7:
		case MP9:
		case MAC10:
		case UMP45:
			return WEPCLASS_SMG;
			break;
		case AWP:
		case G3SG1:
		case SCAR20:
		case SSG08:
			return WEPCLASS_SNIPER;
			break;
		case NEGEV:
		case M249:
			return WEPCLASS_MACHINEGUN;
			break;
		case MAG7:
		case SAWEDOFF:
		case NOVA:
		case XM1014:
			return WEPCLASS_SHOTGUN;
			break;
		case KNIFE:
		case KNIFE_BAYONET:
		case KNIFE_BUTTERFLY:
		case KNIFE_FALCHION:
		case KNIFE_FLIP:
		case KNIFE_GUT:
		case KNIFE_KARAMBIT:
		case KNIFE_TACTICAL:
		case KNIFE_M9_BAYONET:
		case KNIFE_PUSH:
		case KNIFE_BOWIE:
		case KNIFE_NAVAJA:
		case KNIFE_STILETTO:
		case KNIFE_URSUS:
		case KNIFE_TALON:
		case KNIFE_T:
			return WEPCLASS_KNIFE;
			break;

		default:
			return WEPCLASS_INVALID;
		}
	}
	//float GetInaccuracy()
	//{
	//	if (!this)
	//		return 0;

	//	typedef float(__thiscall* GetInaccuracyFn)(void*);
	//	GetInaccuracyFn Inaccuracy = (GetInaccuracyFn)((*(PDWORD_PTR*)this)[468]); //459
	//	return Inaccuracy(this);
	//}
	float GetFloatRecoilIndex()
	{
		if (!this)
			return -1.f;
		return *reinterpret_cast<float*>((DWORD)this + 0x32D0);
	}


	float GetSpread()
	{
		typedef float(__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(this, 436)(this);
	}
	float GetCone()
	{
		if (!this)
			return -1.f;
		typedef float(__thiscall* OriginalFn)(void*);
		return g_Utils->get_vfunc<OriginalFn>(this, 468)(this);

	}

	//float GetInaccuracy()
	//{
	//	if (this != nullptr)
	//	{
	//		typedef float(__thiscall* GetInaccuracyFn)(void*);
	//		GetInaccuracyFn Inaccuracy = (GetInaccuracyFn)((*(PDWORD_PTR*)this)[468]); //459
	//		return Inaccuracy(this);
	//	}
	//}

	float GetInaccuracy()
	{
		typedef float(__thiscall* GetInaccuracyFn)(void*);
		return g_Utils->get_vfunc<GetInaccuracyFn>(this, 467)(this);

	}

	void UpdateAccuracyPenalty()
	{
		typedef void(__thiscall* UpdateAccuracyPenaltyFn)(void*);
		g_Utils->get_vfunc<UpdateAccuracyPenaltyFn>(this, 468)(this);
	}

	int GetWeaponNum()
	{
		int defindex = WeaponID();
		switch (defindex)
		{
		case WEAPON_GLOCK:
			return 0;
		case WEAPON_CZ75:
			return 1;
		case WEAPON_P250:
			return 2;
		case WEAPON_FIVE7:
			return 3;
		case WEAPON_DEAGLE:
			return 4;
		case WEAPON_DUALS:
			return 5;
		case WEAPON_TEC9:
			return 6;
		case WEAPON_P2000:
			return 7;
		case WEAPON_USPS:
			return 8;
		case WEAPON_REVOLVER:
			return 9;
		case WEAPON_MAC10:
			return 10;
		case WEAPON_MP9:
			return 11;
		case WEAPON_MP7:
			return 12;
		case WEAPON_UMP45:
			return 13;
		case WEAPON_BIZON:
			return 14;
		case WEAPON_P90:
			return 15;
		case WEAPON_GALIL:
			return 16;
		case WEAPON_FAMAS:
			return 17;
		case WEAPON_AK47:
			return 18;
		case WEAPON_M4A1:
			return 19;
		case WEAPON_M4A1S:
			return 20;
		case WEAPON_SG553:
			return 21;
		case WEAPON_AUG:
			return 22;
		case WEAPON_SCOUT:
			return 23;
		case WEAPON_AWP:
			return 24;
		case WEAPON_G3SG1:
			return 25;
		case WEAPON_SCAR20:
			return 26;
		case WEAPON_NOVA:
			return 27;
		case WEAPON_XM1014:
			return 28;
		case WEAPON_SAWEDOFF:
			return 29;
		case WEAPON_MAG7:
			return 30;
		case WEAPON_M249:
			return 31;
		case WEAPON_NEGEV:
			return 32;
		default:
			return -1;
		}
		return -1;
	}

	bool IsRifle()
	{
		int iWeaponID = WeaponID();
	}
	bool IsScopeable()
	{
		int iWeaponID = WeaponID();
		return (iWeaponID == 38 || iWeaponID == 11 || iWeaponID == 9 || iWeaponID == 40 || iWeaponID == 8 || iWeaponID == SG556);
	}
	bool IsSniper()
	{
		int iWeaponID = WeaponID();
		return (iWeaponID == SSG08 || iWeaponID == AWP || iWeaponID == SCAR20 || iWeaponID == G3SG1);
	}
	bool IsPistol()
	{
		int iWeaponID = WeaponID();
		return (iWeaponID == GLOCK || iWeaponID == HKP2000
			|| iWeaponID == P250 || iWeaponID == DEAGLE
			|| iWeaponID == ELITE || iWeaponID == TEC9 || iWeaponID == USP_SILENCER
			|| iWeaponID == FIVESEVEN);
	}
	bool IsMiscWeapon()
	{
		int iWeaponID = WeaponID();
		return (iWeaponID == KNIFE
			|| iWeaponID == C4
			|| iWeaponID == HEGRENADE || iWeaponID == DECOY
			|| iWeaponID == FLASHBANG || iWeaponID == MOLOTOV
			|| iWeaponID == SMOKEGRENADE || iWeaponID == INCGRENADE || iWeaponID == KNIFE_T
			|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
			|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
			|| iWeaponID == 515 || iWeaponID == KNIFE_NAVAJA ||
			iWeaponID == KNIFE_STILETTO ||
			iWeaponID == KNIFE_URSUS ||
			iWeaponID == KNIFE_TALON);
	}
	bool IsGun()
	{
		int id = this->GetItemDefinitionIndex();

		if (id == KNIFE || id == HEGRENADE || id == WEAPON_DECOY || id == WEAPON_INC || id == WEAPON_MOLOTOV || id == WEAPON_C4 || id == TASER || id == FLASHBANG || id == SMOKEGRENADE || id == KNIFE)
			return false;
		else
			return true;
	}
	bool IsGrenade()
	{

		int iWeaponID = WeaponID();
		return (iWeaponID == HEGRENADE || iWeaponID == DECOY
			|| iWeaponID == FLASHBANG || iWeaponID == MOLOTOV
			|| iWeaponID == SMOKEGRENADE || iWeaponID == INCGRENADE);
	}
	bool IsKnife()
	{
		int iWeaponID = WeaponID();
		return (iWeaponID == 42 || iWeaponID == 59 || iWeaponID == 41
			|| iWeaponID == 500 || iWeaponID == 505 || iWeaponID == 506
			|| iWeaponID == 507 || iWeaponID == 508 || iWeaponID == 509
			|| iWeaponID == 515 || iWeaponID == KNIFE_NAVAJA ||
			iWeaponID == KNIFE_STILETTO ||
			iWeaponID == KNIFE_URSUS ||
			iWeaponID == KNIFE_TALON);
	}
	float GetPenetration()
	{
		if (!this)
			return -1.f;
		return *reinterpret_cast<float*>((DWORD)this + 0x7C4);
	}
	float GetDamage()
	{
		if (!this)
			return -1.f;
		return *reinterpret_cast<float*>((DWORD)this + 0x7C8);
	}
	float GetRange()
	{
		if (!this)
			return -1.f;
		return *reinterpret_cast<float*>((DWORD)this + 0x7CC);
	}
	float GetRangeModifier()
	{
		if (!this)
			return -1.f;
		return *reinterpret_cast<float*>((DWORD)this + 0x7D0);
	}
	float GetArmorRatio()
	{
		if (!this)
			return -1.f;
		return *reinterpret_cast<float*>((DWORD)this + 0x7AC);
	}
	CSWeaponInfo* GetCSWeaponData();
	bool IsReloadingVisually();
};

class CBaseViewModel
{
public:
	CBaseViewModel(void);
	~CBaseViewModel(void);


	bool IsViewable(void) { return false; }

	virtual void					UpdateOnRemove(void);

	// Weapon client handling
	virtual void			SendViewModelMatchingSequence(int sequence);
	virtual void			SetWeaponModel(const char *pszModelname, CBaseCombatWeapon *weapon);

	void SendViewModelMatchingSequenceManual(int sequence)
	{
		typedef void(__thiscall* OriginalFn)(void*, int);
		return g_Utils->get_vfunc<OriginalFn>(this, 241)(this, sequence);
	}

};

