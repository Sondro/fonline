#ifndef __CRITTER_CL__
#define __CRITTER_CL__

#include "NetProtocol.h"
#include "Common.h"
#include "SpriteManager.h"
#include "BufferManager.h"
#include "Item.h"
#include "ItemManager.h"
#include "3dStuff.h"

class CritterCl
{
public:
    // Properties
    PROPERTIES_HEADER();
    CLASS_PROPERTY_DATA( Anim3dLayer );
    CLASS_PROPERTY( int, Strength );
    CLASS_PROPERTY( int, Perception );
    CLASS_PROPERTY( int, Agility );
    CLASS_PROPERTY( int, Charisma );
    CLASS_PROPERTY( int, Intellect );
    CLASS_PROPERTY( hash, BaseCrType );
    CLASS_PROPERTY( char, Gender );
    CLASS_PROPERTY( int, Level );
    CLASS_PROPERTY( int, Experience );
    CLASS_PROPERTY( int, BonusLook );
    CLASS_PROPERTY( hash, DialogId );
    CLASS_PROPERTY( int, BagId );
    CLASS_PROPERTY( int, NpcRole );
    CLASS_PROPERTY( int, TeamId );
    CLASS_PROPERTY( int, AiId );
    CLASS_PROPERTY( uint, FollowCrit );
    CLASS_PROPERTY( uint, FreeBarterPlayer );
    CLASS_PROPERTY( uint, LastWeaponId );
    CLASS_PROPERTY( hash, HandsItemProtoId );
    CLASS_PROPERTY( uchar, HandsItemMode );
    CLASS_PROPERTY( int, KarmaVoting );
    CLASS_PROPERTY( int, MaxTalkers );
    CLASS_PROPERTY( int, TalkDistance );
    CLASS_PROPERTY( int, CarryWeight );
    CLASS_PROPERTY( int, CurrentHp );
    CLASS_PROPERTY( int, ActionPoints );
    CLASS_PROPERTY( int, CurrentAp );
    CLASS_PROPERTY( int, MaxMoveAp );
    CLASS_PROPERTY( int, MoveAp );
    CLASS_PROPERTY( int, TurnBasedAc );
    CLASS_PROPERTY( int, ReplicationMoney );
    CLASS_PROPERTY( int, ReplicationCost );
    CLASS_PROPERTY( int, ReplicationCount );
    CLASS_PROPERTY( int, ReplicationTime );
    CLASS_PROPERTY( int, WalkTime );
    CLASS_PROPERTY( int, RunTime );
    CLASS_PROPERTY( int, ScaleFactor );
    CLASS_PROPERTY( int, SkillUnarmed );
    CLASS_PROPERTY( int, SkillSneak );
    CLASS_PROPERTY( int, SkillBarter );
    CLASS_PROPERTY( int, SkillLockpick );
    CLASS_PROPERTY( int, SkillSteal );
    CLASS_PROPERTY( int, SkillTraps );
    CLASS_PROPERTY( int, SkillFirstAid );
    CLASS_PROPERTY( int, SkillDoctor );
    CLASS_PROPERTY( int, SkillScience );
    CLASS_PROPERTY( int, SkillRepair );
    CLASS_PROPERTY( int, SkillSpeech );
    CLASS_PROPERTY( uint, TimeoutBattle );
    CLASS_PROPERTY( uint, TimeoutTransfer );
    CLASS_PROPERTY( uint, TimeoutRemoveFromGame );
    CLASS_PROPERTY( uint, TimeoutKarmaVoting );
    CLASS_PROPERTY( uint, TimeoutSkScience );
    CLASS_PROPERTY( uint, TimeoutSkRepair );
    CLASS_PROPERTY( char, DefaultCombat );
    CLASS_PROPERTY( bool, IsInvulnerable );
    CLASS_PROPERTY( bool, IsDlgScriptBarter );
    CLASS_PROPERTY( bool, IsUnlimitedAmmo );
    CLASS_PROPERTY( bool, IsNoUnarmed );
    CLASS_PROPERTY( bool, IsNoFavoriteItem );
    CLASS_PROPERTY( bool, IsNoPush );
    CLASS_PROPERTY( bool, IsNoItemGarbager );
    CLASS_PROPERTY( bool, IsNoEnemyStack );
    CLASS_PROPERTY( bool, IsGeck );
    CLASS_PROPERTY( bool, IsNoLoot );
    CLASS_PROPERTY( bool, IsNoSteal );
    CLASS_PROPERTY( bool, IsNoHome );
    CLASS_PROPERTY( bool, IsNoWalk );
    CLASS_PROPERTY( bool, IsNoRun );
    CLASS_PROPERTY( bool, IsNoTalk );
    CLASS_PROPERTY( bool, IsHide );
    CLASS_PROPERTY( bool, IsNoFlatten );
    CLASS_PROPERTY( bool, IsNoAim );
    CLASS_PROPERTY( bool, IsNoBarter );
    CLASS_PROPERTY( bool, IsEndCombat );
    CLASS_PROPERTY( bool, IsDamagedEye );
    CLASS_PROPERTY( bool, IsDamagedRightArm );
    CLASS_PROPERTY( bool, IsDamagedLeftArm );
    CLASS_PROPERTY( bool, IsDamagedRightLeg );
    CLASS_PROPERTY( bool, IsDamagedLeftLeg );
    CLASS_PROPERTY( uchar, PerkQuickPockets );
    CLASS_PROPERTY( uchar, PerkMasterTrader );
    CLASS_PROPERTY( uchar, PerkSilentRunning );

    // Data
    uint          Id;
    hash          Pid;
    ushort        HexX, HexY;
    uchar         CrDir;
    uint          NameColor;
    uint          ContourColor;
    UShortVec     LastHexX, LastHexY;
    uchar         Cond;
    uint          Anim1Life;
    uint          Anim1Knockout;
    uint          Anim1Dead;
    uint          Anim2Life;
    uint          Anim2Knockout;
    uint          Anim2Dead;
    uint          Flags;
    uint          BaseType, BaseTypeAlias;
    uint          ApRegenerationTick;
    short         Multihex;
    Effect*       DrawEffect;

    ScriptString* Name;
    ScriptString* NameOnHead;
    ScriptString* Avatar;

    ItemVec       InvItems;
    Item*         DefItemSlotHand;
    Item*         DefItemSlotArmor;
    Item*         ItemSlotMain;
    Item*         ItemSlotExt;
    Item*         ItemSlotArmor;

    static bool   SlotEnabled[ 0x100 ];
    static IntSet RegProperties;

    CritterCl();
    ~CritterCl();
    void Init();
    void Finish();

    uint        GetId()   { return Id; }
    const char* GetInfo() { return Name->c_str(); }
    ushort      GetHexX() { return HexX; }
    ushort      GetHexY() { return HexY; }
    bool        IsLastHexes();
    void        FixLastHexes();
    ushort      PopLastHexX();
    ushort      PopLastHexY();
    void        SetBaseType( uint type );
    void        SetDir( uchar dir, bool animate = true );
    uchar       GetDir() { return CrDir; }
    uint        GetCrTypeAlias();

    void Animate( uint anim1, uint anim2, Item* item );
    void AnimateStay();
    void Action( int action, int action_ext, Item* item, bool local_call = true );
    void Process();
    void DrawStay( Rect r );

    const char* GetName()    { return Name->c_str(); }
    int         GetCond()    { return Cond; }
    bool        IsNpc()      { return FLAG( Flags, FCRIT_NPC ); }
    bool        IsPlayer()   { return FLAG( Flags, FCRIT_PLAYER ); }
    bool        IsChosen()   { return FLAG( Flags, FCRIT_CHOSEN ); }
    bool        IsGmapRule() { return FLAG( Flags, FCRIT_RULEGROUP ); }
    bool        IsOnline()   { return !FLAG( Flags, FCRIT_DISCONNECT ); }
    bool        IsOffline()  { return FLAG( Flags, FCRIT_DISCONNECT ); }
    bool        IsLife()     { return Cond == COND_LIFE; }
    bool        IsKnockout() { return Cond == COND_KNOCKOUT; }
    bool        IsDead()     { return Cond == COND_DEAD; }
    bool        IsCanTalk();
    bool        IsCombatMode();
    bool        IsTurnBased();
    bool        CheckFind( int find_type );

    uint GetLook();
    uint GetTalkDist();
    uint GetAttackDist();
    uint GetUseDist();
    uint GetMultihex();

    uint GetMaxWeightKg();
    uint GetMaxVolume();
    uint GetCrType();
    bool IsDmgLeg();
    bool IsDmgTwoLeg();
    bool IsDmgArm();
    bool IsDmgTwoArm();
    int  GetRealAp();
    int  GetAllAp();
    void SubAp( int val );
    void SubMoveAp( int val );

    // Items
public:
    void       AddItem( Item* item );
    void       EraseItem( Item* item, bool animate );
    void       EraseAllItems();
    Item*      GetItem( uint item_id );
    Item*      GetItemByPid( hash item_pid );
    Item*      GetItemByPidInvPriority( hash item_pid );
    Item*      GetItemByPidSlot( hash item_pid, int slot );
    Item*      GetAmmo( uint caliber );
    Item*      GetItemSlot( int slot );
    void       GetItemsSlot( int slot, ItemVec& items );
    void       GetItemsType( int slot, ItemVec& items );
    uint       CountItemPid( hash item_pid );
    uint       CountItemType( uchar type );
    bool       IsCanSortItems();
    Item*      GetItemHighSortValue();
    Item*      GetItemLowSortValue();
    void       GetInvItems( ItemVec& items );
    uint       GetItemsCount();
    uint       GetItemsCountInv();
    uint       GetItemsWeight();
    uint       GetItemsWeightKg();
    uint       GetItemsVolume();
    int        GetFreeWeight();
    int        GetFreeVolume();
    bool       IsHaveLightSources();
    Item*      GetSlotUse( uchar num_slot, uchar& use );
    hash       GetUsePicName( uchar num_slot );
    bool       IsItemAim( uchar num_slot );
    uchar      GetUse()      { return ItemSlotMain->GetMode() & 0xF; }
    uchar      GetFullRate() { return ItemSlotMain->GetMode(); }
    bool       NextRateItem( bool prev );
    uchar      GetAim() { return ( ItemSlotMain->GetMode() >> 4 ) & 0xF; }
    bool       IsAim()  { return GetAim() > 0; }
    void       SetAim( uchar hit_location );
    uint       GetUseApCost( Item* item, uchar rate );
    ProtoItem* GetUnarmedItem( uchar tree, uchar priority );
    ProtoItem* GetProtoMain() { return ItemSlotMain->Proto; }
    ProtoItem* GetProtoExt()  { return ItemSlotExt->Proto; }
    ProtoItem* GetProtoArm()  { return ItemSlotArmor->Proto; }
    Item*      GetAmmoAvialble( Item* weap );
    bool       IsOverweight()       { return (int) GetItemsWeight() > GetCarryWeight(); }
    bool       IsDoubleOverweight() { return (int) GetItemsWeight() > GetCarryWeight() * 2; }

    // Moving
public:
    bool          IsRunning;
    UShortPairVec MoveSteps;
    int           CurMoveStep;
    bool IsNeedMove() { return MoveSteps.size() && !IsWalkAnim(); }
    void ZeroSteps()
    {
        MoveSteps.clear();
        CurMoveStep = 0;
    }
    void Move( int dir );

    // ReSet
private:
    bool needReSet;
    uint reSetTick;

public:
    bool IsNeedReSet() { return needReSet && Timer::GameTick() >= reSetTick; }
    void ReSetOk()     { needReSet = false; }

    // Time
public:
    uint TickCount;
    uint StartTick;

    void TickStart( uint ms )
    {
        TickCount = ms;
        StartTick = Timer::GameTick();
    }
    void TickNull() { TickCount = 0; }
    bool IsFree()   { return ( Timer::GameTick() - StartTick >= TickCount ); }

    // Animation
public:
    uint GetAnim1( Item* anim_item = NULL );
    uint GetAnim2();
    void ProcessAnim( bool animate_stay, bool is2d, uint anim1, uint anim2, Item* item );
    int* GetLayers3dData();
    bool IsAnimAviable( uint anim1, uint anim2 );

private:
    uint curSpr, lastEndSpr;
    uint animStartTick;

    struct CritterAnim
    {
        AnyFrames* Anim;
        uint       AnimTick;
        int        BeginFrm;
        int        EndFrm;
        bool       MoveText;
        int        DirOffs;
        uint       IndCrType, IndAnim1, IndAnim2;
        Item*      ActiveItem;
        CritterAnim() {}
        CritterAnim( AnyFrames* anim, uint tick, int beg_frm, int end_frm, bool move_text, int dir_offs, uint ind_crtype, uint ind_anim1, uint ind_anim2, Item* item ): Anim( anim ), AnimTick( tick ), BeginFrm( beg_frm ), EndFrm( end_frm ), MoveText( move_text ), DirOffs( dir_offs ),
                                                                                                                                                                        IndCrType( ind_crtype ), IndAnim1( ind_anim1 ), IndAnim2( ind_anim2 ), ActiveItem( item ) {}
    };
    typedef vector< CritterAnim > CritterAnimVec;

    CritterAnimVec animSequence;
    CritterAnim    stayAnim;

    CritterAnim* GetCurAnim() { return IsAnim() ? &animSequence[ 0 ] : NULL; }
    void         NextAnim( bool erase_front );

public:
    Animation3d* Anim3d;
    Animation3d* Anim3dStay;
    bool         Visible;
    uchar        Alpha;
    Rect         DRect;
    bool         SprDrawValid;
    Sprite*      SprDraw;
    uint         SprId;
    short        SprOx, SprOy;
    // Extra offsets
    short        OxExtI, OyExtI;
    float        OxExtF, OyExtF;
    float        OxExtSpeed, OyExtSpeed;
    uint         OffsExtNextTick;

    void         SetSprRect();
    bool         Is3dAnim()  { return Anim3d != NULL; }
    Animation3d* GetAnim3d() { return Anim3d; }
    bool         IsAnim()    { return animSequence.size() > 0; }
    bool         IsWalkAnim();
    void         ClearAnim();

    void SetOffs( short set_ox, short set_oy, bool move_text );
    void ChangeOffs( short change_ox, short change_oy, bool move_text );
    void AddOffsExt( short ox, short oy );
    void GetWalkHexOffsets( int dir, int& ox, int& oy );

    // Stay sprite
private:
    int  staySprDir;
    uint staySprTick;

    // Finish
private:
    uint finishingTime;

public:
    bool IsFinishing() { return finishingTime != 0; }
    bool IsFinish()    { return ( finishingTime && Timer::GameTick() > finishingTime ); }

    // Fade
private:
    bool fadingEnable;
    bool fadeUp;

    void  SetFade( bool fade_up );
    uchar GetFadeAlpha();

public:
    uint FadingTick;

    // Text
public:
    Rect GetTextRect();
    void SetText( const char* str, uint color, uint text_delay );
    void DrawTextOnHead();
    void GetNameTextInfo( bool& nameVisible, int& x, int& y, int& w, int& h, int& lines );

private:
    Rect   textRect;
    uint   tickFidget;
    string strTextOnHead;
    uint   tickStartText;
    uint   tickTextDelay;
    uint   textOnHeadColor;

    // Ap cost
public:
    int GetApCostCritterMove( bool is_run );
    int GetApCostMoveItemContainer();
    int GetApCostMoveItemInventory();
    int GetApCostPickItem();
    int GetApCostDropItem();
    int GetApCostPickCritter();
    int GetApCostUseSkill();

    // Ref counter
public:
    short RefCounter;
    bool  IsNotValid;
    void AddRef()  { RefCounter++; }
    void Release() { if( --RefCounter <= 0 ) delete this; }
};

typedef map< uint, CritterCl* > CritMap;
typedef vector< CritterCl* >    CritVec;
typedef CritterCl*              CritterClPtr;

#endif // __CRITTER_CL__
