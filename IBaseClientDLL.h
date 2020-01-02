#pragma once
#include "UserCmd.h"
#include "EntityStruct.h"
class IPanel;
class CViewSetup
{
public:
	__int32   x;
	__int32   x_old;
	__int32   y;
	__int32   y_old;
	__int32   width;
	__int32   width_old;
	__int32   height;
	__int32   height_old;
	char      pad_0x0020[0x90];
	float     fov;
	float     viewmodel_fov;
	Vector    origin;
	Vector    angles;
	char      pad_0x00D0[0x7C];
};
class ClientClass
{
	typedef IClientNetworkable*   (*CreateClientClassFn)(int entnum, int serialNum);
	typedef IClientNetworkable*   (*CreateEventFn)();

public:
	CreateClientClassFn			m_pCreateFn;
	CreateEventFn  			m_pCreateEventFn;
	char			*m_pNetworkName;
	RecvTable		*m_pRecvTable;
	ClientClass		*m_pNext;
	int				m_ClassID;
};

class IBaseClientDLL
{
public:
	ClientClass * GetAllClasses()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return g_Utils->get_vfunc<GetAllClassesFn>(this, 8)(this);
	}
};

class IGlobalVars
{
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     absoluteframestarttimestddev;
	float     curtime;
	float     frametime;
	int       maxClients;
	int       tickcount;
	float     intervalPerTick;
	float     interpolationAmount;
	int       simTicksThisFrame;
	int       networkProtocol;
	void*     pSaveData;
	bool      bClient;
	bool      bRemoteClient;

private:
	int       nTimestampNetworkingBase;
	int       nTimestampRandomizeWindow;
};

class IClientMode
{
public:
	virtual             ~IClientMode() {}
	virtual int         ClientModeCSNormal(void *) = 0;
	virtual void        Init() = 0;
	virtual void        InitViewport() = 0;
	virtual void        Shutdown() = 0;
	virtual void        Enable() = 0;
	virtual void        Disable() = 0;
	virtual void        Layout() = 0;
	virtual IPanel*     GetViewport() = 0;
	virtual void*       GetViewportAnimationController() = 0;
	virtual void        ProcessInput(bool bActive) = 0;
	virtual bool        ShouldDrawDetailObjects() = 0;
	virtual bool        ShouldDrawEntity(C_BaseEntity *pEnt) = 0;
	virtual bool        ShouldDrawLocalPlayer(C_BaseEntity *pPlayer) = 0;
	virtual bool        ShouldDrawParticles() = 0;
	virtual bool        ShouldDrawFog(void) = 0;
	virtual void        OverrideView(CViewSetup *pSetup) = 0; // 19
	virtual int         KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0; // 20
	virtual void        StartMessageMode(int iMessageModeType) = 0; //21
	virtual IPanel*     GetMessagePanel() = 0; //22
	virtual void        OverrideMouseInput(float *x, float *y) = 0; //23
	virtual bool        CreateMove(float flSampleFrametime, void* pCmd) = 0; // 24
	virtual void        LevelInit(const char *newmap) = 0;
	virtual void        LevelShutdown(void) = 0;
};


class IMoveHelper
{
public:
	void SetHost(C_BaseEntity *pPlayer)
	{
		typedef void(__thiscall* OriginalFn)(void*, C_BaseEntity *pPlayer);
		g_Utils->get_vfunc<OriginalFn>(this, 1)(this, pPlayer);
	}

	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	int m_nPlayerHandle; // edict index on server, client entity handle on client=
	int m_nImpulseCommand; // Impulse command issued.
	QAngle m_vecViewAngles; // Command view angles (local space)
	QAngle m_vecAbsViewAngles; // Command view angles (world space)
	int m_nButtons; // Attack buttons.
	int m_nOldButtons; // From host_client->oldbuttons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	Vector m_vecVelocity; // edict::velocity // Current movement direction.
	QAngle m_vecAngles; // edict::angles
	QAngle m_vecOldAngles;
	float m_outStepHeight; // how much you climbed this move
	Vector m_outWishVel; // This is where you tried 
	Vector m_outJumpVel; // This is your jump velocity
	Vector m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	float m_flUnknown[5];
	Vector m_vecAbsOrigin;
};
class CPrediction
{
public:
	void SetupMove(C_BaseEntity* ent, CUserCmd* cmd, void* move, void* movedata)
	{
		typedef void(__thiscall* fn)(void*, C_BaseEntity*, CUserCmd*, void*, void*);
		g_Utils->get_vfunc<fn>(this, 20)(this, ent, cmd, move, movedata);
	}

	void FinishMove(C_BaseEntity* ent, CUserCmd* cmd, void* movedata)
	{
		typedef void(__thiscall* fn)(void*, C_BaseEntity*, CUserCmd*, void*);
		g_Utils->get_vfunc<fn>(this, 21)(this, ent, cmd, movedata);
	}

	void RunCommand(C_BaseEntity* pEntity, CUserCmd* pCmd, void* moveHelper)
	{
		typedef void(__thiscall* fn)(void*, C_BaseEntity*, CUserCmd*, void*);
		g_Utils->get_vfunc<fn>(this, 19)(this, pEntity, pCmd, moveHelper);
	}
};

class CGameMovement
{
public:
	void ProcessMovement(C_BaseEntity* ent, void* movedata)
	{
		typedef void(__thiscall* fn)(void*, C_BaseEntity*, void*);
		g_Utils->get_vfunc<fn>(this, 1)(this, ent, movedata);
	}

	void StartTrackPredictionErrors(C_BaseEntity* ent)
	{
		typedef void(__thiscall* fn)(void*, C_BaseEntity*);
		g_Utils->get_vfunc<fn>(this, 3)(this, ent);
	}

	void FinishTrackPredictionErrors(C_BaseEntity* ent)
	{
		typedef void(__thiscall* fn)(void*, C_BaseEntity*);
		g_Utils->get_vfunc<fn>(this, 4)(this, ent);
	}

	void DecayPunchAngle()
	{
		typedef void(__thiscall* fn)(void*);
		g_Utils->get_vfunc<fn>(this, 19)(this);
	}
};




class IGameEvent
{
public:
	virtual ~IGameEvent() = 0;
	virtual const char *GetName() const = 0;

	virtual bool  IsReliable() const = 0;
	virtual bool  IsLocal() const = 0;
	virtual bool  IsEmpty(const char *keyName = NULL) = 0;

	virtual bool  GetBool(const char *keyName = NULL, bool defaultValue = false) = 0;
	virtual int   GetInt(const char *keyName = NULL, int defaultValue = 0) = 0;
	virtual unsigned long GetUint64(const char *keyName = NULL, unsigned long defaultValue = 0) = 0;
	virtual float GetFloat(const char *keyName = NULL, float defaultValue = 0.0f) = 0;
	virtual const char *GetString(const char *keyName = NULL, const char *defaultValue = "") = 0;
	virtual const wchar_t *GetWString(const char *keyName, const wchar_t *defaultValue = L"") = 0;

	virtual void SetBool(const char *keyName, bool value) = 0;
	virtual void SetInt(const char *keyName, int value) = 0;
	virtual void SetUint64(const char *keyName, unsigned long value) = 0;
	virtual void SetFloat(const char *keyName, float value) = 0;
	virtual void SetString(const char *keyName, const char *value) = 0;
	virtual void SetWString(const char *keyName, const wchar_t *value) = 0;
};
extern int GetServerSideID(int CBaseEntityIndex);
class IGameEventListener2
{
public:
	virtual	~IGameEventListener2(void) {};

	// FireEvent is called by EventManager if event just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void FireGameEvent(IGameEvent *event) = 0;
	virtual int  GetEventDebugID(void) = 0;
};

class IGameEventManager
{
public:
	bool AddListener(IGameEventListener2 *listener, const char *name, bool bServerSide)
	{
		if (!this)
			return false;

		typedef bool(__thiscall* OriginalFn)(PVOID, IGameEventListener2*, const char*, bool);
		return g_Utils->get_vfunc<OriginalFn>(this, 3)(this, listener, name, bServerSide);
	}

	bool FireEventClientSide(IGameEvent *event)
	{
		if (!this)
			return false;

		typedef bool(__thiscall* OriginalFn)(PVOID, IGameEvent*);
		return  g_Utils->get_vfunc<OriginalFn>(this, 9)(this, event);
	}
};

class cGameEvent : public IGameEventListener2
{


public:

	void FireGameEvent(IGameEvent *event);
	int GetEventDebugID();
	void RegisterSelf();
	void Register();


};


/*class CDebugOverlay
{
public:
int ScreenPosition(const Vector& point, Vector& screen)
{
typedef int(__thiscall* OriginalFn)(PVOID, const Vector&, Vector&);
return VMT.CallVFunction<OriginalFn>(this, 13)(this, point, screen);
}
void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration)
{
typedef void(__thiscall* Fn)(PVOID, const Vector&, const Vector&, const Vector&, QAngle const&, int, int, int, int, float);

}

}; */


class OverlayText_t;

class CDebugOverlay
{
public:
	virtual void            AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void            AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void            AddSphereOverlay(const Vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration) = 0;
	virtual void            AddTriangleOverlay(const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void            AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
	virtual void            AddTextOverlay(const Vector& origin, float duration, const char *format, ...) = 0;
	virtual void            AddTextOverlay(const Vector& origin, int line_offset, float duration, const char *format, ...) = 0;
	virtual void            AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
	virtual void            AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const QAngle & angles, int r, int g, int b, int a, float flDuration) = 0;
	virtual void            AddGridOverlay(const Vector& origin) = 0;
	virtual void            AddCoordFrameOverlay(const matrix3x4_t& frame, float flScale, int vColorTable[3][3] = NULL) = 0;
	virtual int             ScreenPosition(const Vector& point, Vector& screen) = 0;
	virtual int             ScreenPosition(float flXPos, float flYPos, Vector& screen) = 0;
	virtual OverlayText_t*  GetFirst(void) = 0;
	virtual OverlayText_t*  GetNext(OverlayText_t *current) = 0;
	virtual void            ClearDeadOverlays(void) = 0;
	virtual void            ClearAllOverlays(void) = 0;
	virtual void            AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ...) = 0;
	virtual void            AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void            AddLineOverlayAlpha(const Vector& origin, const Vector& dest, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void            AddBoxOverlay2(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, const uint8_t* faceColor, const uint8_t* edgeColor, float duration) = 0;
	virtual void			AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, int a, float, float) = 0;
	virtual void            PurgeTextOverlays() = 0;
	void AddCapsuleOverlay(Vector& mins, Vector& maxs, float pillradius, int r, int g, int b, int a, float duration)
	{
		g_Utils->get_vfunc<void(__thiscall*)(void*, Vector&, Vector&, float&, int, int, int, int, float)>(this, 23)(this, mins, maxs, pillradius, r, g, b, a, duration);
	}
};



#define PHYSICS_MULTIPLAYER_AUTODETECT	0	// use multiplayer physics mode as defined in model prop data

#define PHYSICS_MULTIPLAYER_SOLID		1	// soild, pushes player away 

#define PHYSICS_MULTIPLAYER_NON_SOLID	2	// nonsolid, but pushed by player

#define PHYSICS_MULTIPLAYER_CLIENTSIDE	3	// Clientside only, nonsolid 	
enum Collision_Group_t
{
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,				// Collides with nothing but world and static stuff
	COLLISION_GROUP_DEBRIS_TRIGGER,		// Same as debris, but hits triggers
	COLLISION_GROUP_INTERACTIVE_DEB,	// RIS, // Collides with everything except other interactive debris or debris
	COLLISION_GROUP_INTERACTIVE,		// Collides with everything except interactive debris or debris
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,	// For HL2, same as Collision_Group_Player
	COLLISION_GROUP_NPC,				// Generic NPC group
	COLLISION_GROUP_IN_VEHICLE,			// for any entity inside a vehicle
	COLLISION_GROUP_WEAPON,				// for any weapons that need collision detection
	COLLISION_GROUP_VEHICLE_CLIP,		// vehicle clip brush to restrict vehicle movement
	COLLISION_GROUP_PROJECTILE,			// Projectiles!
	COLLISION_GROUP_DOOR_BLOCKER,		// Blocks entities not permitted to get near moving doors
	COLLISION_GROUP_PASSABLE_DOOR,		// Doors that the player shouldn't collide with
	COLLISION_GROUP_DISSOLVING,			// Things that are dissolving are in this group
	COLLISION_GROUP_PUSHAWAY,			// Nonsolid on client and server, pushaway in player code
	COLLISION_GROUP_NPC_ACTOR,			// Used so NPCs in scripts ignore the player.
	LAST_SHARED_COLLISION_GROUP
};
struct surfacephysicsparams_t
{
	float    friction;
	float    elasticity; // collision elasticity - used to compute coefficient of restitution
	float    density;    // physical density (in kg / m^3)
	float    thickness;    // material thickness if not solid (sheet materials) in inches
	float    dampening;
};

struct surfaceaudioparams_t
{
	float    reflectivity;             // like elasticity, but how much sound should be reflected by this surface
	float    hardnessFactor;           // like elasticity, but only affects impact sound choices
	float    roughnessFactor;          // like friction, but only affects scrape sound choices   
	float    roughThreshold;           // surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
	float    hardThreshold;            // surface hardness > this causes "hard" impacts, < this causes "soft" impacts
	float    hardVelocityThreshold;    // collision velocity > this causes "hard" impacts, < this causes "soft" impacts   
	float    highPitchOcclusion;       //a value betweeen 0 and 100 where 0 is not occluded at all and 100 is silent (except for any additional reflected sound)
	float    midPitchOcclusion;
	float    lowPitchOcclusion;
};

struct surfacesoundnames_t
{
	unsigned short    stepleft;
	unsigned short    stepright;
	unsigned short    impactSoft;
	unsigned short    impactHard;
	unsigned short    scrapeSmooth;
	unsigned short    scrapeRough;
	unsigned short    bulletImpact;
	unsigned short    rolling;
	unsigned short    breakSound;
	unsigned short    strainSound;
};

struct surfacegameprops_t
{
public:
	float    maxSpeedFactor; //0x0000
	float    jumpFactor; //0x0004
	char    pad00[0x4]; //0x0008
	float    flPenetrationModifier; //0x000C
	float    flDamageModifier; //0x0010
	unsigned short    material; //0x0014
	char    pad01[0x3];

};//Size=0x0019

struct surfacedata_t
{
	surfacephysicsparams_t    physics;
	surfaceaudioparams_t    audio;
	surfacesoundnames_t        sounds;
	surfacegameprops_t        game;
};

class IPhysicsSurfaceProps
{
public:
	/*virtual ~IPhysicsSurfaceProps(void) {}
	virtual int				ParseSurfaceData(const char *pFilename, const char *pTextfile) = 0;
	virtual int				SurfacePropCount(void) const = 0;
	virtual int				GetSurfaceIndex(const char *pSurfacePropName) const = 0;
	virtual void			GetPhysicsProperties(int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity) const = 0;
	virtual surfacedata_t*	GetSurfaceData(int surfaceDataIndex) = 0;
	virtual const char*		GetString(unsigned short stringTableIndex) const = 0;
	virtual const char*		GetPropName(int surfaceDataIndex) const = 0;
	virtual void			SetWorldMaterialIndexTable(int *pMapArray, int mapSize) = 0;
	virtual void			GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;*/

	surfacedata_t	*GetSurfaceData(int surfaceDataIndex)
	{
		typedef surfacedata_t*(__thiscall* fnGetSurfaceData)(void*, int);
		return g_Utils->get_vfunc<fnGetSurfaceData>(this, 5)(this, surfaceDataIndex);
	}
};

class IMultiplayerPhysics
{
public:
	virtual int		GetMultiplayerPhysicsMode(void) = 0;
	virtual float	GetMass(void) = 0;
	virtual bool	IsAsleep(void) = 0;
};
enum mp_break_t
{
	MULTIPLAYER_BREAK_DEFAULT,
	MULTIPLAYER_BREAK_SERVERSIDE,
	MULTIPLAYER_BREAK_CLIENTSIDE,
	MULTIPLAYER_BREAK_BOTH
};
enum propdata_interactions_t
{
	PROPINTER_PHYSGUN_WORLD_STICK,		// "onworldimpact"	"stick"
	PROPINTER_PHYSGUN_FIRST_BREAK,		// "onfirstimpact"	"break"
	PROPINTER_PHYSGUN_FIRST_PAINT,		// "onfirstimpact"	"paintsplat"
	PROPINTER_PHYSGUN_FIRST_IMPALE,		// "onfirstimpact"	"impale"
	PROPINTER_PHYSGUN_LAUNCH_SPIN_NONE,	// "onlaunch"		"spin_none"
	PROPINTER_PHYSGUN_LAUNCH_SPIN_Z,	// "onlaunch"		"spin_zaxis"
	PROPINTER_PHYSGUN_BREAK_EXPLODE,	// "onbreak"		"explode_fire"
	PROPINTER_PHYSGUN_DAMAGE_NONE,		// "damage"			"none"
	PROPINTER_FIRE_FLAMMABLE,			// "flammable"			"yes"
	PROPINTER_FIRE_EXPLOSIVE_RESIST,	// "explosive_resist"	"yes"
	PROPINTER_FIRE_IGNITE_HALFHEALTH,	// "ignite"				"halfhealth"
	PROPINTER_PHYSGUN_CREATE_FLARE,		// "onpickup"		"create_flare"
	PROPINTER_PHYSGUN_ALLOW_OVERHEAD,	// "allow_overhead"	"yes"
	PROPINTER_WORLD_BLOODSPLAT,			// "onworldimpact", "bloodsplat"
	PROPINTER_PHYSGUN_NOTIFY_CHILDREN,	// "onfirstimpact" cause attached flechettes to explode
	PROPINTER_NUM_INTERACTIONS,			// If we get more than 32 of these, we'll need a different system
};
class IBreakableWithPropData
{
public:
	// Damage modifiers
	virtual void            SetDmgModBullet(float flDmgMod) = 0;
	virtual void            SetDmgModClub(float flDmgMod) = 0;
	virtual void            SetDmgModExplosive(float flDmgMod) = 0;
	virtual float           GetDmgModBullet(void) = 0;
	virtual float           GetDmgModClub(void) = 0;
	virtual float           GetDmgModExplosive(void) = 0;
	// Explosive
	virtual void            SetExplosiveRadius(float flRadius) = 0;
	virtual void            SetExplosiveDamage(float flDamage) = 0;
	virtual float           GetExplosiveRadius(void) = 0;
	virtual float           GetExplosiveDamage(void) = 0;
	// Physics damage tables
	virtual void            SetPhysicsDamageTable(char* iszTableName) = 0;
	virtual char*           GetPhysicsDamageTable(void) = 0;
	// Breakable chunks
	virtual void            SetBreakableModel(char* iszModel) = 0;
	virtual char*           GetBreakableModel(void) = 0;
	virtual void            SetBreakableSkin(int iSkin) = 0;
	virtual int                     GetBreakableSkin(void) = 0;
	virtual void            SetBreakableCount(int iCount) = 0;
	virtual int                     GetBreakableCount(void) = 0;
	virtual void            SetMaxBreakableSize(int iSize) = 0;
	virtual int                     GetMaxBreakableSize(void) = 0;
	// LOS blocking
	virtual void            SetPropDataBlocksLOS(bool bBlocksLOS) = 0;
	virtual void            SetPropDataIsAIWalkable(bool bBlocksLOS) = 0;
	// Interactions
	virtual void            SetInteraction(propdata_interactions_t Interaction) = 0;
	virtual bool            HasInteraction(propdata_interactions_t Interaction) = 0;
	// Multi player physics mode
	virtual void            SetPhysicsMode(int iMode) = 0;
	virtual int                     GetPhysicsMode() = 0;
	// Multi player breakable spawn behavior
	virtual void            SetMultiplayerBreakMode(mp_break_t mode) = 0;
	virtual mp_break_t      GetMultiplayerBreakMode(void) const = 0;
	// Used for debugging
	virtual void            SetBasePropData(char* iszBase) = 0;
	virtual char*           GetBasePropData(void) = 0;
};


typedef void* FileNameHandle_t;

struct SndInfo_t
{
	int m_nGuid;
	FileNameHandle_t m_filenameHandle;
	int m_nSoundSource;
	int m_nChannel;
	int m_nSpeakerEntity;
	float m_flVolume;
	float m_flLastSpatializedVolume;
	float m_flRadius;
	int m_nPitch;
	Vector *m_pOrigin;
	Vector *m_pDirection;
	bool m_bUpdatePositions;
	bool m_bIsSentence;
	bool m_bDryMix;
	bool m_bSpeaker;
	bool m_bSpecialDSP;
	bool m_bFromServer;
};

#define VOL_NORM		1.0f


//-----------------------------------------------------------------------------
// common attenuation values
//-----------------------------------------------------------------------------
#define ATTN_NONE		0.0f
#define ATTN_NORM		0.8f
#define ATTN_IDLE		2.0f
#define ATTN_STATIC		1.25f 
#define ATTN_RICOCHET	1.5f

// HL2 world is 8x bigger now! We want to hear gunfire from farther.
// Don't change this without consulting Kelly or Wedge (sjb).
#define ATTN_GUNFIRE	0.27f

enum soundlevel_t
{
	SNDLVL_NONE = 0,

	SNDLVL_20dB = 20,			// rustling leaves
	SNDLVL_25dB = 25,			// whispering
	SNDLVL_30dB = 30,			// library
	SNDLVL_35dB = 35,
	SNDLVL_40dB = 40,
	SNDLVL_45dB = 45,			// refrigerator

	SNDLVL_50dB = 50,	// 3.9	// average home
	SNDLVL_55dB = 55,	// 3.0

	SNDLVL_IDLE = 60,	// 2.0	
	SNDLVL_60dB = 60,	// 2.0	// normal conversation, clothes dryer

	SNDLVL_65dB = 65,	// 1.5	// washing machine, dishwasher
	SNDLVL_STATIC = 66,	// 1.25

	SNDLVL_70dB = 70,	// 1.0	// car, vacuum cleaner, mixer, electric sewing machine

	SNDLVL_NORM = 75,
	SNDLVL_75dB = 75,	// 0.8	// busy traffic

	SNDLVL_80dB = 80,	// 0.7	// mini-bike, alarm clock, noisy restaurant, office tabulator, outboard motor, passing snowmobile
	SNDLVL_TALKING = 80,	// 0.7
	SNDLVL_85dB = 85,	// 0.6	// average factory, electric shaver
	SNDLVL_90dB = 90,	// 0.5	// screaming child, passing motorcycle, convertible ride on frw
	SNDLVL_95dB = 95,
	SNDLVL_100dB = 100,	// 0.4	// subway train, diesel truck, woodworking shop, pneumatic drill, boiler shop, jackhammer
	SNDLVL_105dB = 105,			// helicopter, power mower
	SNDLVL_110dB = 110,			// snowmobile drvrs seat, inboard motorboat, sandblasting
	SNDLVL_120dB = 120,			// auto horn, propeller aircraft
	SNDLVL_130dB = 130,			// air raid siren

	SNDLVL_GUNFIRE = 140,	// 0.27	// THRESHOLD OF PAIN, gunshot, jet engine
	SNDLVL_140dB = 140,	// 0.2

	SNDLVL_150dB = 150,	// 0.2

	SNDLVL_180dB = 180,			// rocket launching

								// NOTE: Valid soundlevel_t values are 0-255.
								//       256-511 are reserved for sounds using goldsrc compatibility attenuation.
};

#define MAX_SNDLVL_BITS		9	// Used to encode 0-255 for regular soundlevel_t's and 256-511 for goldsrc-compatible ones.
#define MIN_SNDLVL_VALUE	0
#define MAX_SNDLVL_VALUE	((1<<MAX_SNDLVL_BITS)-1)


#define ATTN_TO_SNDLVL( a ) (soundlevel_t)(int)((a) ? (50 + 20 / ((float)a)) : 0 )
#define SNDLVL_TO_ATTN( a ) ((a > 50) ? (20.0f / (float)(a - 50)) : 4.0 )

// This is a limit due to network encoding.
// It encodes attenuation * 64 in 8 bits, so the maximum is (255 / 64)
#define MAX_ATTENUATION		3.98f

//-----------------------------------------------------------------------------
// Flags to be or-ed together for the iFlags field
//-----------------------------------------------------------------------------
enum SoundFlags_t
{
	SND_NOFLAGS = 0,			// to keep the compiler happy
	SND_CHANGE_VOL = (1 << 0),		// change sound vol
	SND_CHANGE_PITCH = (1 << 1),		// change sound pitch
	SND_STOP = (1 << 2),		// stop the sound
	SND_SPAWNING = (1 << 3),		// we're spawning, used in some cases for ambients
									// not sent over net, only a param between dll and server.
									SND_DELAY = (1 << 4),		// sound has an initial delay
									SND_STOP_LOOPING = (1 << 5),		// stop all looping sounds on the entity.
									SND_SPEAKER = (1 << 6),		// being played again by a microphone through a speaker

									SND_SHOULDPAUSE = (1 << 7),		// this sound should be paused if the game is paused
									SND_IGNORE_PHONEMES = (1 << 8),
									SND_IGNORE_NAME = (1 << 9),		// used to change all sounds emitted by an entity, regardless of scriptname

									SND_DO_NOT_OVERWRITE_EXISTING_ON_CHANNEL = (1 << 10),
};

#define SND_FLAG_BITS_ENCODE 11

#define MAX_SOUND_INDEX_BITS	14
#define	MAX_SOUNDS				(1<<MAX_SOUND_INDEX_BITS)

#if !defined( IN_XBOX_CODELINE )
// +/-4096 msec
#define MAX_SOUND_DELAY_MSEC_ENCODE_BITS	(13)
#else
// +/-65536 msec, 64 seconds
#define MAX_SOUND_DELAY_MSEC_ENCODE_BITS	(17)
#endif

// Subtract one to leave room for the sign bit
#define MAX_SOUND_DELAY_MSEC				(1<<(MAX_SOUND_DELAY_MSEC_ENCODE_BITS-1))    // 4096 msec or about 4 seconds

//-----------------------------------------------------------------------------
// common pitch values
//-----------------------------------------------------------------------------
#define	PITCH_NORM		100			// non-pitch shifted
#define PITCH_LOW		95			// other values are possible - 0-255, where 255 is very high
#define PITCH_HIGH		120

#define DEFAULT_SOUND_PACKET_VOLUME 1.0f
#define DEFAULT_SOUND_PACKET_PITCH	100
#define DEFAULT_SOUND_PACKET_DELAY	0.0f

class IRecipientFilter
{
public:
	virtual			~IRecipientFilter() {}

	virtual bool	IsReliable(void) const = 0;
	virtual bool	IsInitMessage(void) const = 0;

	virtual int		GetRecipientCount(void) const = 0;
	virtual int		GetRecipientIndex(int slot) const = 0;
};

class IEngineSound
{
public:
	void GetActiveSounds(CUtlVector<SndInfo_t> & sndlist)
	{
		typedef void(__thiscall* FnGetName)(PVOID, CUtlVector<SndInfo_t> &);
		return g_Utils->get_vfunc< FnGetName >(this, 18)(this, sndlist);
	}
};

