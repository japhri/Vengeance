#pragma once
#include "SDK.h"
class Quaternion
{
public:
	float x, y, z, w;
	float operator[](int i) const { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
	float& operator[](int i) { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
};

class RadianEuler
{
public:
	float x, y, z;
};
struct mstudiobbox_t
{
	int					bone;
	int					group;				// intersection group
	Vector				bbmin;				// bounding box
	Vector				bbmax;
	int					szhitboxnameindex;	// offset to the name of the hitbox.
	int					unused[3];
	float				radius;
	int					unused2[4];

	const char* pszHitboxName()
	{
		if (szhitboxnameindex == 0)
			return "";

		return ((char*)this) + szhitboxnameindex;
	}

	mstudiobbox_t() {}

private:
	mstudiobbox_t(const mstudiobbox_t& vOther);
};

struct mstudiobone_t
{
	int					sznameindex;
	inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
	int		 			parent;		// parent bone
	int					bonecontroller[6];	// bone controller index, -1 == none

											// default values
	Vector				pos;
	Quaternion			quat;
	Vector			rot;
	// compression scale
	Vector				posscale;
	Vector				rotscale;

	VMatrix			poseToBone;
	Quaternion			qAlignment;
	int					flags;
	int					proctype;
	int					procindex;		// procedural rule
	mutable int			physicsbone;	// index into physically simulated bone
	inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
	int					surfacepropidx;	// index into string tablefor property name
	inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
	int					contents;		// See BSPFlags.h for the contents flags

	int					unused[8];		// remove as appropriate

	mstudiobone_t() {}
private:
	// No copy constructors allowed
	mstudiobone_t(const mstudiobone_t& vOther);
};

struct mstudioseqdesc_t
{
	int	szlabelindex;
	inline char * const pszLabel(void) const { return ((char *)this) + szlabelindex; }

	int	szactivitynameindex;
	inline char * const pszActivityName(void) const { return ((char *)this) + szactivitynameindex; }

	int	flags;		// looping/non-looping flags

	int	activity;	// initialized at loadtime to game DLL values
	int	actweight;

	int	numevents;
	int	eventindex;
	inline void *pEvent(int i) const { return (((byte *)this) + eventindex) + i; };

	Vector	bbmin;		// per sequence bounding box
	Vector	bbmax;

	//-------------------------------------------------------------------------
	// Purpose: returns a model animation from the sequence group size and
	//          blend index
	// Note: this replaces GetAnimValue() that was previously in bone_setup
	// Note: this also acts as a SetAnimValue() as it returns a reference to
	//       the anim value in question
	//-------------------------------------------------------------------------
	inline unsigned short& pAnimValue(int nIndex0, int nIndex1) const
	{
		// Clamp indexes
		if (nIndex0 >= groupsize[0])
			nIndex0 = groupsize[0] - 1;

		if (nIndex1 >= groupsize[1])
			nIndex1 = groupsize[1] - 1;

		return *pBlend(nIndex1 * groupsize[0] + nIndex0);
	}

	int	numblends;

	int blendindex;
	inline unsigned short *pBlend(int i) const { return (unsigned short *)(((byte *)this) + blendindex) + i; };

	int seqgroup; // sequence group for demand loading

	int	groupsize[2];
	int	paramindex[2];	// X, Y, Z, XR, YR, ZR
	float	paramstart[2];	// local (0..1) starting value
	float	paramend[2];	// local (0..1) ending value
	int	paramparent;

	float	fadeintime;	// ideal cross fate in time (0.2 default)
	float	fadeouttime;	// ideal cross fade out time (0.2 default)

	int	entrynode;	// transition node at entry
	int	exitnode;	// transition node at exit
	int	nodeflags;	// transition rules

	float	entryphase;	// used to match entry gait
	float	exitphase;	// used to match exit gait

	float	lastframe;	// frame that should generation EndOfSequence

	int	nextseq;	// auto advancing sequences
	int	pose;		// index of delta animation between end and nextseq

	int	numikrules;

	int	numautolayers;
	int	autolayerindex;
	inline void *pAutolayer(int i) const { return (((byte *)this) + autolayerindex) + i; };

	int	weightlistindex;
	float	*pBoneweight(int i) const { return ((float *)(((byte *)this) + weightlistindex) + i); };
	float	weight(int i) const { return *(pBoneweight(i)); };

	int	posekeyindex;
	float				*pPoseKey(int iParam, int iAnim) const { return (float *)(((byte *)this) + posekeyindex) + iParam * groupsize[0] + iAnim; }
	float				poseKey(int iParam, int iAnim) const { return *(pPoseKey(iParam, iAnim)); }

	int	numiklocks;
	int	iklockindex;
	inline void *pIKLock(int i) const { return (((byte *)this) + iklockindex) + i; };

	// Key values
	int	keyvalueindex;
	int	keyvaluesize;
	inline const char * KeyValueText(void) const { return keyvaluesize != 0 ? ((char *)this) + keyvalueindex : NULL; }

	int	unused[3];		// remove/add as appropriate
};

struct mstudiohitboxset_t
{
	int					sznameindex;
	inline char * const	pszName(void) const { return ((char *)this) + sznameindex; }
	int					numhitboxes;
	int					hitboxindex;
	inline mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t *)(((byte *)this) + hitboxindex) + i; };
};

struct studiohdr_t
{
	int	id;
	int	version;

	long checksum;	// this has to be the same in the phy and vtx files to load!

	char name[64];
	int	length;

	Vector	eyeposition;	// ideal eye position

	Vector	illumposition;	// illumination center

	Vector	hull_min;	// ideal movement hull size
	Vector	hull_max;

	Vector	view_bbmin;	// clipping bounding box
	Vector	view_bbmax;

	int	flags;

	int	numbones;	// bones
	int	boneindex;
	inline mstudiobone_t *pBone(int i) const { return (mstudiobone_t *)(((byte *)this) + boneindex) + i; };

	int	numbonecontrollers;	// bone controllers
	int	bonecontrollerindex;
	inline void *pBonecontroller(int i) const { return (((byte *)this) + bonecontrollerindex) + i; };

	int	numhitboxsets;
	int	hitboxsetindex;

	// Look up hitbox set by index

	mstudiohitboxset_t  *pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t *)(((byte *)this) + hitboxsetindex) + i;
	};

	// Calls through to hitbox to determine size of specified set
	inline mstudiobbox_t *pHitbox(int i, int set) const
	{
		mstudiohitboxset_t *s = pHitboxSet(set);

		if (!s)
			return NULL;

		return s->pHitbox(i);
	};

	// Calls through to set to get hitbox count for set
	inline int  iHitboxCount(int set) const
	{
		mstudiohitboxset_t const *s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};

	int	numanim;	// animations/poses
	int	animdescindex;	// animation descriptions
	inline void *pAnimdesc(int i) const { return (((byte *)this) + animdescindex) + i; };

	int 	numanimgroup;
	int 	animgroupindex;
	inline  void *pAnimGroup(int i) const { return (((byte *)this) + animgroupindex) + i; };

	int 	numbonedesc;
	int 	bonedescindex;
	inline  void *pBoneDesc(int i) const { return (((byte *)this) + bonedescindex) + i; };

	int	numseq;		// sequences
	int	seqindex;
	inline mstudioseqdesc_t *pSeqdesc(int i) const { if (i < 0 || i >= numseq) i = 0; return (mstudioseqdesc_t *)(((byte *)this) + seqindex) + i; };
	int	sequencesindexed;	// initialization flag - have the sequences been indexed?

	int	numseqgroups;		// demand loaded sequences
	int	seqgroupindex;
	inline  void *pSeqgroup(int i) const { return (((byte *)this) + seqgroupindex) + i; };

	int	numtextures;		// raw textures
	int	textureindex;
	inline void *pTexture(int i) const { return (((byte *)this) + textureindex) + i; };

	int	numcdtextures;		// raw textures search paths
	int	cdtextureindex;
	inline char			*pCdtexture(int i) const { return (((char *)this) + *((int *)(((byte *)this) + cdtextureindex) + i)); };

	int	numskinref;		// replaceable textures tables
	int	numskinfamilies;
	int	skinindex;
	inline short		*pSkinref(int i) const { return (short *)(((byte *)this) + skinindex) + i; };

	int	numbodyparts;
	int	bodypartindex;
	inline void	*pBodypart(int i) const { return (((byte *)this) + bodypartindex) + i; };

	int	numattachments;		// queryable attachable points
	int	attachmentindex;
	inline void	*pAttachment(int i) const { return (((byte *)this) + attachmentindex) + i; };

	int	numtransitions;		// animation node to animation node transition graph
	int	transitionindex;
	inline byte	*pTransition(int i) const { return (byte *)(((byte *)this) + transitionindex) + i; };

	int	numflexdesc;
	int	flexdescindex;
	inline void *pFlexdesc(int i) const { return (((byte *)this) + flexdescindex) + i; };

	int	numflexcontrollers;
	int	flexcontrollerindex;
	inline void *pFlexcontroller(int i) const { return (((byte *)this) + flexcontrollerindex) + i; };

	int	numflexrules;
	int	flexruleindex;
	inline void *pFlexRule(int i) const { return (((byte *)this) + flexruleindex) + i; };

	int	numikchains;
	int	ikchainindex;
	inline void *pIKChain(int i) const { return (((byte *)this) + ikchainindex) + i; };

	int	nummouths;
	int	mouthindex;
	inline void *pMouth(int i) const { return (((byte *)this) + mouthindex) + i; };

	int	numposeparameters;
	int	poseparamindex;
	inline void *pPoseParameter(int i) const { return (((byte *)this) + poseparamindex) + i; };

	int	surfacepropindex;
	inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropindex; }

	// Key values
	int	keyvalueindex;
	int	keyvaluesize;
	inline const char * KeyValueText(void) const { return keyvaluesize != 0 ? ((char *)this) + keyvalueindex : NULL; }

	int	numikautoplaylocks;
	int	ikautoplaylockindex;
	inline void *pIKAutoplayLock(int i) const { return (((byte *)this) + ikautoplaylockindex) + i; };

	float mass;		
	int	contents;
	int	unused[9];	
};

struct model_t
{
	char name[255];
};

class CModelInfo
{
public:
	studiohdr_t * GetStudioModel(const model_t* Model)
	{
		if (!this)
			return nullptr;

		typedef studiohdr_t*(__thiscall* Fn)(void*, const model_t*);
		return g_Utils->get_vfunc<Fn>(this, 32)(this, Model);

	}
	void GetModelRenderBounds(const model_t *model, Vector& mins, Vector& maxs)
	{
		typedef void(__thiscall* Fn)(void*, const model_t*, Vector&, Vector&);
		return g_Utils->get_vfunc<Fn>(this, 6)(this, model, mins, maxs);
	}
	int GetModelIndex(const char* ModelName)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, const char*);
		return g_Utils->get_vfunc<OriginalFn>(this, 2)(this, ModelName);
	}
	const char* GetModelName(const model_t *model)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, const model_t*);
		return g_Utils->get_vfunc<OriginalFn>(this, 3)(this, model);
	}

	
	std::string GetModelNameString(const model_t* pModel)
	{
		typedef const char*(__thiscall* OriginalFn)(PVOID, const model_t*);
		return std::string(g_Utils->get_vfunc< OriginalFn >(this, 3)(this, pModel));
	}
	void GetModelMaterials(const model_t *model, int count, IMaterial** ppMaterial)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const model_t*, int, IMaterial**);
		g_Utils->get_vfunc<OriginalFn>(this, 17)(this, model, count, ppMaterial);
	}

};









enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};


struct ModelRenderInfo_t
{
	Vector origin;
	Vector angles;
	char pad[0x4];
	void *pRenderable;
	const model_t*          pModel;

	const matrix3x4_t *pModelToWorld;
	const matrix3x4_t *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	unsigned short instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	//	MATERIAL_VAR_UNUSED					  = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
										   //	MATERIAL_VAR_UNUSED					  = (1 << 18),
										   MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
										   MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
										   MATERIAL_VAR_TRANSLUCENT = (1 << 21),
										   MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
										   MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
										   MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
										   MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
										   MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
										   MATERIAL_VAR_HALFLAMBERT = (1 << 27),
										   MATERIAL_VAR_WIREFRAME = (1 << 28),
										   MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
										   MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
										   MATERIAL_VAR_VERTEXFOG = (1 << 31),

										   // NOTE: Only add flags here that either should be read from
										   // .vmts or can be set directly from client code. Other, internal
										   // flags should to into the flag enum in IMaterialInternal.h
};
typedef int ImageFormat;
typedef int MaterialPropertyTypes_t;
//-----------------------------------------------------------------------------
// Internal flags not accessible from outside the material system. Stored in Flags2
//-----------------------------------------------------------------------------
enum MaterialVarFlags2_t
{
	// NOTE: These are for $flags2!!!!!
	//	UNUSED											= (1 << 0),

	MATERIAL_VAR2_LIGHTING_UNLIT = 0,
	MATERIAL_VAR2_LIGHTING_VERTEX_LIT = (1 << 1),
	MATERIAL_VAR2_LIGHTING_LIGHTMAP = (1 << 2),
	MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP = (1 << 3),
	MATERIAL_VAR2_LIGHTING_MASK =
	(MATERIAL_VAR2_LIGHTING_VERTEX_LIT |
		MATERIAL_VAR2_LIGHTING_LIGHTMAP |
		MATERIAL_VAR2_LIGHTING_BUMPED_LIGHTMAP),

	// FIXME: Should this be a part of the above lighting enums?
	MATERIAL_VAR2_DIFFUSE_BUMPMAPPED_MODEL = (1 << 4),
	MATERIAL_VAR2_USES_ENV_CUBEMAP = (1 << 5),
	MATERIAL_VAR2_NEEDS_TANGENT_SPACES = (1 << 6),
	MATERIAL_VAR2_NEEDS_SOFTWARE_LIGHTING = (1 << 7),
	// GR - HDR path puts lightmap alpha in separate texture...
	MATERIAL_VAR2_BLEND_WITH_LIGHTMAP_ALPHA = (1 << 8),
	MATERIAL_VAR2_NEEDS_BAKED_LIGHTING_SNAPSHOTS = (1 << 9),
	MATERIAL_VAR2_USE_FLASHLIGHT = (1 << 10),
	MATERIAL_VAR2_USE_FIXED_FUNCTION_BAKED_LIGHTING = (1 << 11),
	MATERIAL_VAR2_NEEDS_FIXED_FUNCTION_FLASHLIGHT = (1 << 12),
	MATERIAL_VAR2_USE_EDITOR = (1 << 13),
	MATERIAL_VAR2_NEEDS_POWER_OF_TWO_FRAME_BUFFER_TEXTURE = (1 << 14),
	MATERIAL_VAR2_NEEDS_FULL_FRAME_BUFFER_TEXTURE = (1 << 15),
	MATERIAL_VAR2_IS_SPRITECARD = (1 << 16),
	MATERIAL_VAR2_USES_VERTEXID = (1 << 17),
	MATERIAL_VAR2_SUPPORTS_HW_SKINNING = (1 << 18),
	MATERIAL_VAR2_SUPPORTS_FLASHLIGHT = (1 << 19),
	MATERIAL_VAR2_USE_GBUFFER0 = (1 << 20),
	MATERIAL_VAR2_USE_GBUFFER1 = (1 << 21),
	MATERIAL_VAR2_SELFILLUMMASK = (1 << 22),
	MATERIAL_VAR2_SUPPORTS_TESSELLATION = (1 << 23)
};
typedef int VertexFormat_t;
enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};
class IMaterialVar;
class KeyValues
{
public:
	char _pad[0x20];//csgo, for css its a diff size
};
class IMaterial
{
public:
	virtual const char*             GetName() const = 0;
	virtual const char*             GetTextureGroupName() const = 0;
	virtual PreviewImageRetVal_t    GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool* isTranslucent) const = 0;
	virtual PreviewImageRetVal_t    GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int                     GetMappingWidth() = 0;
	virtual int                     GetMappingHeight() = 0;
	virtual int                     GetNumAnimationFrames() = 0;
	virtual bool                    InMaterialPage(void) = 0;
	virtual    void                 GetMaterialOffset(float *pOffset) = 0;
	virtual void                    GetMaterialScale(float *pScale) = 0;
	virtual IMaterial*              GetMaterialPage(void) = 0;
	virtual IMaterialVar*           FindVar(const char *varName, bool *found, bool complain = true) = 0;
	virtual void                    IncrementReferenceCount(void) = 0;
	virtual void                    DecrementReferenceCount(void) = 0;
	inline void                     AddRef() { IncrementReferenceCount(); }
	inline void                     Release() { DecrementReferenceCount(); }
	virtual int                     GetEnumerationID(void) const = 0;
	virtual void                    GetLowResColorSample(float s, float t, float *color) const = 0;
	virtual void                    RecomputeStateSnapshots() = 0;
	virtual bool                    IsTranslucent() = 0;
	virtual bool                    IsAlphaTested() = 0;
	virtual bool                    IsVertexLit() = 0;
	virtual VertexFormat_t          GetVertexFormat() const = 0;
	virtual bool                    HasProxy(void) const = 0;
	virtual bool                    UsesEnvCubemap(void) = 0;
	virtual bool                    NeedsTangentSpace(void) = 0;
	virtual bool                    NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool                    NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool                    NeedsSoftwareSkinning(void) = 0;
	virtual void                    AlphaModulate(float alpha) = 0;
	virtual void                    ColorModulate(float r, float g, float b) = 0;
	virtual void                    SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool                    GetMaterialVarFlag(MaterialVarFlags_t flag) const = 0;
	virtual void                    GetReflectivity(Vector& reflect) = 0;
	virtual bool                    GetPropertyFlag(MaterialPropertyTypes_t type) = 0;
	virtual bool                    IsTwoSided() = 0;
	virtual void                    SetShader(const char *pShaderName) = 0;
	virtual int                     GetNumPasses(void) = 0;
	virtual int                     GetTextureMemoryBytes(void) = 0;
	virtual void                    Refresh() = 0;
	virtual bool                    NeedsLightmapBlendAlpha(void) = 0;
	virtual bool                    NeedsSoftwareLighting(void) = 0;
	virtual int                     ShaderParamCount() const = 0;
	virtual IMaterialVar**          GetShaderParams(void) = 0;
	virtual bool                    IsErrorMaterial() const = 0;
	virtual void                    Unused() = 0;
	virtual float                   GetAlphaModulation() = 0;
	virtual void                    GetColorModulation(float *r, float *g, float *b) = 0;
	virtual bool                    IsTranslucentUnderModulation(float fAlphaModulation = 1.0f) const = 0;
	virtual IMaterialVar*           FindVarFast(char const *pVarName, unsigned int *pToken) = 0;
	virtual void                    SetShaderAndParams(KeyValues *pKeyValues) = 0;
	virtual const char*             GetShaderName() const = 0;
	virtual void                    DeleteIfUnreferenced() = 0;
	virtual bool                    IsSpriteCard() = 0;
	virtual void                    CallBindProxy(void *proxyData) = 0;
	virtual void                    RefreshPreservingMaterialVars() = 0;
	virtual bool                    WasReloadedFromWhitelist() = 0;
	virtual bool                    SetTempExcluded(bool bSet, int nExcludedDimensionLimit) = 0;
	virtual int                     GetReferenceCount() const = 0;
};

typedef unsigned short MaterialHandle_t;
class CMaterialSystem
{
public:
	IMaterial * FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL)
	{
		typedef IMaterial*(__thiscall* oFindMaterial)(PVOID, char const*, char const*, bool, char const*);
		return g_Utils->get_vfunc< oFindMaterial >(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}

	IMaterial*	CreateMaterial(const char *pMaterialName, KeyValues *pVMTKeyValues)
	{
		typedef IMaterial* (__thiscall* oCreateMaterial)(PVOID, const char *, KeyValues*);
		return g_Utils->get_vfunc<oCreateMaterial>(this, 83)(this, pMaterialName, pVMTKeyValues);
	}
	MaterialHandle_t FirstMaterial()
	{
		typedef MaterialHandle_t(__thiscall* FirstMaterialFn)(void*);
		return  g_Utils->get_vfunc<FirstMaterialFn>(this, 86)(this);
	}

	MaterialHandle_t NextMaterial(MaterialHandle_t h)
	{
		typedef MaterialHandle_t(__thiscall* NextMaterialFn)(void*, MaterialHandle_t);
		return  g_Utils->get_vfunc<NextMaterialFn>(this, 87)(this, h);
	}

	MaterialHandle_t InvalidMaterial()
	{
		typedef MaterialHandle_t(__thiscall* InvalidMaterialFn)(void*);
		return  g_Utils->get_vfunc<InvalidMaterialFn>(this, 88)(this);
	}

	IMaterial* GetMaterial(MaterialHandle_t h)
	{
		typedef IMaterial*(__thiscall* GetMaterialFn)(void*, MaterialHandle_t);
		return g_Utils->get_vfunc<GetMaterialFn>(this, 89)(this, h);
	}
};
class CModelRender
{
public:
	void ForcedMaterialOverride(IMaterial *material, OverrideType_t type = OVERRIDE_NORMAL, int idk = NULL)
	{
		typedef void(__thiscall* Fn)(void*, IMaterial*, OverrideType_t, int);
		return g_Utils->get_vfunc<Fn>(this, 1)(this, material, type, idk);
	}

};
class CRenderView
{
public:
	void SetBlend(float alpha)
	{
		typedef void(__thiscall* oDrawModelExecute)(PVOID, float);
		return g_Utils->get_vfunc< oDrawModelExecute >(this, 4)(this, alpha);
	}

	void SetColorModulation(float const* colors)
	{
		typedef void(__thiscall* oDrawModelExecute)(PVOID, float const*);
		return g_Utils->get_vfunc< oDrawModelExecute >(this, 6)(this, colors);
	}
};


class CUtlVectorSimple
{
public:
	unsigned memory;
	char pad[8];
	unsigned int count;
	inline void* Retrieve(int index, unsigned sizeofdata)
	{
		return (void*)((*(unsigned*)this) + (sizeofdata * index));
	}
};
