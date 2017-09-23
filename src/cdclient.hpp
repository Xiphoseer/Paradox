#pragma once

#include <string>
#include <iostream>

#include <assembly/database.hpp>


// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_preferredRole;
    float           m_specifiedMinRangeNOUSE;
    float           m_specifiedMaxRangeNOUSE;
    float           m_specificMinRange;
    float           m_specificMaxRange;
}
AICombatRoles;

void readDB(AICombatRoles& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_GroupID;
    std::string     m_Description;
    float           m_Pos_X;
    float           m_Pos_Y;
    float           m_Pos_Z;
    float           m_Rot_X;
    float           m_Rot_Y;
    float           m_Rot_Z;
}
AccessoryDefaultLoc;

void readDB(AccessoryDefaultLoc& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_ActivityID;
    int32_t         m_locStatus;
    int32_t         m_instanceMapID;
    int32_t         m_minTeams;
    int32_t         m_maxTeams;
    int32_t         m_minTeamSize;
    int32_t         m_maxTeamSize;
    int32_t         m_waitTime;
    int32_t         m_startDelay;
    bool            m_requiresUniqueData;
    int32_t         m_leaderboardType;
    bool            m_localize;
    int32_t         m_optionalCostLOT;
    int32_t         m_optionalCostCount;
    bool            m_showUIRewards;
    int32_t         m_CommunityActivityFlagID;
    std::string     m_gate_version;
    bool            m_noTeamLootOnDeath;
    float           m_optionalPercentage;
}
Activities;

void readDB(Activities& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_objectTemplate;
    int32_t         m_ActivityRewardIndex;
    int32_t         m_activityRating;
    int32_t         m_LootMatrixIndex;
    int32_t         m_CurrencyIndex;
    int32_t         m_ChallengeRating;
    std::string     m_description;
}
ActivityRewards;

void readDB(ActivityRewards& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_activityID;
    std::string     m_type;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
ActivityText;

void readDB(ActivityText& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_animationGroupID;
    std::string     m_description;
    std::string     m_groupType;
}
AnimationIndex;

void readDB(AnimationIndex& entry, std::istream& file);

// SlotCount: 8192
typedef struct
{
    int32_t         m_animationGroupID;
    std::string     m_animation_type;
    std::string     m_animation_name;
    float           m_chance_to_play;
    int32_t         m_min_loops;
    int32_t         m_max_loops;
    float           m_animation_length;
    bool            m_hideEquip;
    bool            m_ignoreUpperBody;
    bool            m_restartable;
    std::string     m_face_animation_name;
    float           m_priority;
    float           m_blendTime;
}
Animations;

void readDB(Animations& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_id;
    int32_t         m_behaviorType;
    float           m_combatRoundLength;
    int32_t         m_combatRole;
    float           m_minRoundLength;
    float           m_maxRoundLength;
    float           m_tetherSpeed;
    float           m_pursuitSpeed;
    float           m_combatStartDelay;
    float           m_softTetherRadius;
    float           m_hardTetherRadius;
    float           m_spawnTimer;
    int32_t         m_tetherEffectID;
    bool            m_ignoreMediator;
    float           m_aggroRadius;
    bool            m_ignoreStatReset;
    bool            m_ignoreParent;
}
BaseCombatAIComponent;

void readDB(BaseCombatAIComponent& entry, std::istream& file);

// SlotCount: 16384
typedef struct
{
    int32_t         m_effectID;
    std::string     m_effectType;
    std::string     m_effectName;
    int32_t         m_trailID;
    float           m_pcreateDuration;
    std::string     m_animationName;
    bool            m_attachToObject;
    std::string     m_boneName;
    bool            m_useSecondary;
    int32_t         m_cameraEffectType;
    float           m_cameraDuration;
    float           m_cameraFrequency;
    float           m_cameraXAmp;
    float           m_cameraYAmp;
    float           m_cameraZAmp;
    float           m_cameraRotFrequency;
    float           m_cameraRoll;
    float           m_cameraPitch;
    float           m_cameraYaw;
    std::string     m_AudioEventGUID;
    int32_t         m_renderEffectType;
    float           m_renderEffectTime;
    float           m_renderStartVal;
    float           m_renderEndVal;
    float           m_renderDelayVal;
    float           m_renderValue1;
    float           m_renderValue2;
    float           m_renderValue3;
    std::string     m_renderRGBA;
    int32_t         m_renderShaderVal;
    int32_t         m_motionID;
    int32_t         m_meshID;
    float           m_meshDuration;
    std::string     m_meshLockedNode;
}
BehaviorEffect;

void readDB(BehaviorEffect& entry, std::istream& file);

// SlotCount: 65536
typedef struct
{
    int32_t         m_behaviorID;
    std::string     m_parameterID;
    float           m_value;
}
BehaviorParameter;

void readDB(BehaviorParameter& entry, std::istream& file);

// SlotCount: 65536
typedef struct
{
    int32_t         m_behaviorID;
    int32_t         m_templateID;
    int32_t         m_effectID;
    std::string     m_effectHandle;
}
BehaviorTemplate;

void readDB(BehaviorTemplate& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_templateID;
    std::string     m_name;
}
BehaviorTemplateName;

void readDB(BehaviorTemplateName& entry, std::istream& file);

// SlotCount: 2
typedef struct
{
    int64_t         m_id;
    std::string     m_name;
    std::string     m_description;
    int64_t         m_accountid;
    int64_t         m_characterid;
    int32_t         m_price;
    int32_t         m_rating;
    int32_t         m_categoryid;
    std::string     m_lxfpath;
    bool            m_deleted;
    int64_t         m_created;
    int64_t         m_modified;
}
Blueprints;

void readDB(Blueprints& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    float           m_red;
    float           m_green;
    float           m_blue;
    float           m_alpha;
    int32_t         m_legopaletteid;
    std::string     m_description;
    int32_t         m_validTypes;
    int32_t         m_validCharacters;
    bool            m_factoryValid;
}
BrickColors;

void readDB(BrickColors& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_NDObjectID;
    int32_t         m_LEGOBrickID;
}
BrickIDTable;

void readDB(BrickIDTable& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_ID;
    float           m_Priority;
    std::string     m_UIIcon;
}
BuffDefinitions;

void readDB(BuffDefinitions& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_BuffID;
    std::string     m_ParameterName;
    float           m_NumberValue;
    std::string     m_StringValue;
    int32_t         m_EffectID;
}
BuffParameters;

void readDB(BuffParameters& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    std::string     m_camera_name;
    float           m_pitch_angle_tolerance;
    float           m_starting_zoom;
    float           m_zoom_return_modifier;
    float           m_pitch_return_modifier;
    float           m_tether_out_return_modifier;
    float           m_tether_in_return_multiplier;
    float           m_verticle_movement_dampening_modifier;
    float           m_return_from_incline_modifier;
    float           m_horizontal_return_modifier;
    float           m_yaw_behavior_speed_multiplier;
    float           m_camera_collision_padding;
    float           m_glide_speed;
    float           m_fade_player_min_range;
    float           m_min_movement_delta_tolerance;
    float           m_min_glide_distance_tolerance;
    float           m_look_forward_offset;
    float           m_look_up_offset;
    float           m_minimum_vertical_dampening_distance;
    float           m_maximum_vertical_dampening_distance;
    float           m_minimum_ignore_jump_distance;
    float           m_maximum_ignore_jump_distance;
    float           m_maximum_auto_glide_angle;
    float           m_minimum_tether_glide_distance;
    float           m_yaw_sign_correction;
    float           m_set_1_look_forward_offset;
    float           m_set_1_look_up_offset;
    float           m_set_2_look_forward_offset;
    float           m_set_2_look_up_offset;
    float           m_set_0_speed_influence_on_dir;
    float           m_set_1_speed_influence_on_dir;
    float           m_set_2_speed_influence_on_dir;
    float           m_set_0_angular_relaxation;
    float           m_set_1_angular_relaxation;
    float           m_set_2_angular_relaxation;
    float           m_set_0_position_up_offset;
    float           m_set_1_position_up_offset;
    float           m_set_2_position_up_offset;
    float           m_set_0_position_forward_offset;
    float           m_set_1_position_forward_offset;
    float           m_set_2_position_forward_offset;
    float           m_set_0_FOV;
    float           m_set_1_FOV;
    float           m_set_2_FOV;
    float           m_set_0_max_yaw_angle;
    float           m_set_1_max_yaw_angle;
    float           m_set_2_max_yaw_angle;
    int32_t         m_set_1_fade_in_camera_set_change;
    int32_t         m_set_1_fade_out_camera_set_change;
    int32_t         m_set_2_fade_in_camera_set_change;
    int32_t         m_set_2_fade_out_camera_set_change;
    float           m_input_movement_scalar;
    float           m_input_rotation_scalar;
    float           m_input_zoom_scalar;
    float           m_minimum_pitch_desired;
    float           m_maximum_pitch_desired;
    float           m_minimum_zoom;
    float           m_maximum_zoom;
    float           m_horizontal_rotate_tolerance;
    float           m_horizontal_rotate_modifier;
}
Camera;

void readDB(Camera& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    std::string     m_animation;
    int32_t         m_backgroundObject;
    float           m_duration;
    std::string     m_subText;
    std::string     m_mainText;
    int32_t         m_iconID;
    float           m_celeLeadIn;
    float           m_celeLeadOut;
    int32_t         m_cameraPathLOT;
    std::string     m_pathNodeName;
    float           m_ambientR;
    float           m_ambientG;
    float           m_ambientB;
    float           m_directionalR;
    float           m_directionalG;
    float           m_directionalB;
    float           m_specularR;
    float           m_specularG;
    float           m_specularB;
    float           m_lightPositionX;
    float           m_lightPositionY;
    float           m_lightPositionZ;
    float           m_blendTime;
    float           m_fogColorR;
    float           m_fogColorG;
    float           m_fogColorB;
    std::string     m_musicCue;
    std::string     m_soundGUID;
    std::string     m_mixerProgram;
}
CelebrationParameters;

void readDB(CelebrationParameters& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_id;
    std::string     m_selections;
    int32_t         m_imaginationOverride;
}
ChoiceBuildComponent;

void readDB(ChoiceBuildComponent& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_requirement_mission;
}
CollectibleComponent;

void readDB(CollectibleComponent& entry, std::istream& file);

// SlotCount: 32768
typedef struct
{
    int32_t         m_id;
    int32_t         m_component_type;
    int32_t         m_component_id;
}
ComponentsRegistry;

void readDB(ComponentsRegistry& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_control_scheme;
    std::string     m_scheme_name;
    float           m_rotation_speed;
    float           m_walk_forward_speed;
    float           m_walk_backward_speed;
    float           m_walk_strafe_speed;
    float           m_walk_strafe_forward_speed;
    float           m_walk_strafe_backward_speed;
    float           m_run_backward_speed;
    float           m_run_strafe_speed;
    float           m_run_strafe_forward_speed;
    float           m_run_strafe_backward_speed;
    float           m_keyboard_zoom_sensitivity;
    float           m_keyboard_pitch_sensitivity;
    float           m_keyboard_yaw_sensitivity;
    float           m_mouse_zoom_wheel_sensitivity;
    float           m_x_mouse_move_sensitivity_modifier;
    float           m_y_mouse_move_sensitivity_modifier;
    float           m_freecam_speed_modifier;
    float           m_freecam_slow_speed_multiplier;
    float           m_freecam_fast_speed_multiplier;
    float           m_freecam_mouse_modifier;
    float           m_gamepad_pitch_rot_sensitivity;
    float           m_gamepad_yaw_rot_sensitivity;
    float           m_gamepad_trigger_sensitivity;
}
ControlSchemes;

void readDB(ControlSchemes& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_value;
    int32_t         m_objectid;
}
CurrencyDenominations;

void readDB(CurrencyDenominations& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_currencyIndex;
    int32_t         m_npcminlevel;
    int32_t         m_minvalue;
    int32_t         m_maxvalue;
    int32_t         m_id;
}
CurrencyTable;

void readDB(CurrencyTable& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    std::string     m_table;
    std::string     m_column;
}
DBExclude;

void readDB(DBExclude& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    bool            m_restricted;
    std::string     m_ids;
    int32_t         m_checkType;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
DeletionRestrictions;

void readDB(DeletionRestrictions& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_id;
    int32_t         m_faction;
    std::string     m_factionList;
    int32_t         m_life;
    int32_t         m_imagination;
    int32_t         m_LootMatrixIndex;
    int32_t         m_CurrencyIndex;
    int32_t         m_level;
    float           m_armor;
    int32_t         m_death_behavior;
    bool            m_isnpc;
    int32_t         m_attack_priority;
    bool            m_isSmashable;
    int32_t         m_difficultyLevel;
}
DestructibleComponent;

void readDB(DestructibleComponent& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_ModelID;
    int32_t         m_BehaviorID;
}
DevModelBehaviors;

void readDB(DevModelBehaviors& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_id;
    std::string     m_animationName;
    std::string     m_iconFilename;
    std::string     m_channel;
    std::string     m_command;
    bool            m_locked;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
Emotes;

void readDB(Emotes& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    std::string     m_eventName;
    int64_t         m_date_start;
    int64_t         m_date_end;
}
EventGating;

void readDB(EventGating& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    float           m_length;
    float           m_width;
    float           m_height;
    float           m_offsetX;
    float           m_offsetY;
    float           m_offsetZ;
    float           m_fReputationSizeMultiplier;
    float           m_fImaginationCost;
}
ExhibitComponent;

void readDB(ExhibitComponent& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_faction;
    std::string     m_factionList;
    bool            m_factionListFriendly;
    std::string     m_friendList;
    std::string     m_enemyList;
}
Factions;

void readDB(Factions& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    std::string     m_featureName;
    int32_t         m_major;
    int32_t         m_current;
    int32_t         m_minor;
    std::string     m_description;
}
FeatureGating;

void readDB(FeatureGating& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    std::string     m_asset;
}
FlairTable;

void readDB(FlairTable& entry, std::istream& file);

// SlotCount: 4096
typedef struct
{
    int32_t         m_IconID;
    std::string     m_IconPath;
    std::string     m_IconName;
}
Icons;

void readDB(Icons& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_id;
    int32_t         m_itemid;
    int32_t         m_count;
    bool            m_equip;
}
InventoryComponent;

void readDB(InventoryComponent& entry, std::istream& file);

// SlotCount: 8192
typedef struct
{
    int32_t         m_id;
    std::string     m_equipLocation;
    int32_t         m_baseValue;
    bool            m_isKitPiece;
    int32_t         m_rarity;
    int32_t         m_itemType;
    int64_t         m_itemInfo;
    bool            m_inLootTable;
    bool            m_inVendor;
    bool            m_isUnique;
    bool            m_isBOP;
    bool            m_isBOE;
    int32_t         m_reqFlagID;
    int32_t         m_reqSpecialtyID;
    int32_t         m_reqSpecRank;
    int32_t         m_reqAchievementID;
    int32_t         m_stackSize;
    int32_t         m_color1;
    int32_t         m_decal;
    int32_t         m_offsetGroupID;
    int32_t         m_buildTypes;
    std::string     m_reqPrecondition;
    int32_t         m_animationFlag;
    int32_t         m_equipEffects;
    bool            m_readyForQA;
    int32_t         m_itemRating;
    bool            m_isTwoHanded;
    int32_t         m_minNumRequired;
    int32_t         m_delResIndex;
    int32_t         m_currencyLOT;
    int32_t         m_altCurrencyCost;
    std::string     m_subItems;
    std::string     m_audioEventUse;
    bool            m_noEquipAnimation;
    int32_t         m_commendationLOT;
    int32_t         m_commendationCost;
    std::string     m_audioEquipMetaEventSet;
    std::string     m_currencyCosts;
    std::string     m_ingredientInfo;
    int32_t         m_locStatus;
    int32_t         m_forgeType;
    float           m_SellMultiplier;
}
ItemComponent;

void readDB(ItemComponent& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_id;
    int32_t         m_chassie_type_id;
}
ItemEggData;

void readDB(ItemEggData& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_id;
    int32_t         m_element_1;
    int32_t         m_element_1_amount;
    int32_t         m_element_2;
    int32_t         m_element_2_amount;
    int32_t         m_element_3;
    int32_t         m_element_3_amount;
    int32_t         m_element_4;
    int32_t         m_element_4_amount;
}
ItemFoodData;

void readDB(ItemFoodData& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_SkillSetID;
    int32_t         m_SkillID;
    int32_t         m_SkillCastType;
}
ItemSetSkills;

void readDB(ItemSetSkills& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_setID;
    int32_t         m_locStatus;
    std::string     m_itemIDs;
    int32_t         m_kitType;
    int32_t         m_kitRank;
    int32_t         m_kitImage;
    int32_t         m_skillSetWith2;
    int32_t         m_skillSetWith3;
    int32_t         m_skillSetWith4;
    int32_t         m_skillSetWith5;
    int32_t         m_skillSetWith6;
    bool            m_localize;
    std::string     m_gate_version;
    int32_t         m_kitID;
    float           m_priority;
}
ItemSets;

void readDB(ItemSets& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_id;
    float           m_xDistance;
    float           m_yDistance;
    float           m_warnDistance;
    int32_t         m_lotBlocker;
    int32_t         m_lotWarningVolume;
}
JetPackPadComponent;

void readDB(JetPackPadComponent& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    int32_t         m_id;
    float           m_minXZ;
    float           m_maxXZ;
    float           m_maxY;
    float           m_offsetX;
    float           m_offsetY;
    float           m_offsetZ;
}
LUPExhibitComponent;

void readDB(LUPExhibitComponent& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_LOT;
    float           m_minXZ;
    float           m_maxXZ;
    float           m_maxY;
    std::string     m_description;
    std::string     m_owner;
}
LUPExhibitModelData;

void readDB(LUPExhibitModelData& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_zoneID;
}
LUPZoneIDs;

void readDB(LUPZoneIDs& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    int32_t         m_LanguageID;
    std::string     m_LanguageDescription;
}
LanguageType;

void readDB(LanguageType& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_requiredUScore;
    std::string     m_BehaviorEffect;
}
LevelProgressionLookup;

void readDB(LevelProgressionLookup& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_LootMatrixIndex;
    int32_t         m_LootTableIndex;
    int32_t         m_RarityTableIndex;
    float           m_percent;
    int32_t         m_minToDrop;
    int32_t         m_maxToDrop;
    int32_t         m_id;
    int32_t         m_flagID;
    std::string     m_gate_version;
}
LootMatrix;

void readDB(LootMatrix& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_LootMatrixIndex;
    bool            m_inNpcEditor;
}
LootMatrixIndex;

void readDB(LootMatrixIndex& entry, std::istream& file);

// SlotCount: 8192
typedef struct
{
    int32_t         m_itemid;
    int32_t         m_LootTableIndex;
    int32_t         m_id;
    bool            m_MissionDrop;
    int32_t         m_sortPriority;
}
LootTable;

void readDB(LootTable& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_LootTableIndex;
}
LootTableIndex;

void readDB(LootTableIndex& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_id;
    int32_t         m_head;
    int32_t         m_chest;
    int32_t         m_legs;
    int32_t         m_hairstyle;
    int32_t         m_haircolor;
    int32_t         m_chestdecal;
    int32_t         m_headcolor;
    int32_t         m_lefthand;
    int32_t         m_righthand;
    int32_t         m_eyebrowstyle;
    int32_t         m_eyesstyle;
    int32_t         m_mouthstyle;
}
MinifigComponent;

void readDB(MinifigComponent& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_ID;
    std::string     m_High_path;
    std::string     m_Low_path;
    bool            m_CharacterCreateValid;
    bool            m_male;
    bool            m_female;
}
MinifigDecals_Eyebrows;

void readDB(MinifigDecals_Eyebrows& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_ID;
    std::string     m_High_path;
    std::string     m_Low_path;
    bool            m_CharacterCreateValid;
    bool            m_male;
    bool            m_female;
}
MinifigDecals_Eyes;

void readDB(MinifigDecals_Eyes& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_ID;
    std::string     m_High_path;
}
MinifigDecals_Legs;

void readDB(MinifigDecals_Legs& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_ID;
    std::string     m_High_path;
    std::string     m_Low_path;
    bool            m_CharacterCreateValid;
    bool            m_male;
    bool            m_female;
}
MinifigDecals_Mouths;

void readDB(MinifigDecals_Mouths& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_ID;
    std::string     m_High_path;
    bool            m_CharacterCreateValid;
    bool            m_male;
    bool            m_female;
}
MinifigDecals_Torsos;

void readDB(MinifigDecals_Torsos& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_ID;
    int32_t         m_messageType;
    int32_t         m_notificationGroup;
    int32_t         m_missionID;
    int32_t         m_attachmentLOT;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
MissionEmail;

void readDB(MissionEmail& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_id;
    int32_t         m_missionID;
    bool            m_offersMission;
    bool            m_acceptsMission;
    std::string     m_gate_version;
}
MissionNPCComponent;

void readDB(MissionNPCComponent& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_id;
    int32_t         m_locStatus;
    int32_t         m_taskType;
    int32_t         m_target;
    std::string     m_targetGroup;
    int32_t         m_targetValue;
    std::string     m_taskParam1;
    std::string     m_largeTaskIcon;
    int32_t         m_IconID;
    int32_t         m_uid;
    int32_t         m_largeTaskIconID;
    bool            m_localize;
    std::string     m_gate_version;
}
MissionTasks;

void readDB(MissionTasks& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_id;
    std::string     m_story_icon;
    std::string     m_missionIcon;
    std::string     m_offerNPCIcon;
    int32_t         m_IconID;
    std::string     m_state_1_anim;
    std::string     m_state_2_anim;
    std::string     m_state_3_anim;
    std::string     m_state_4_anim;
    std::string     m_state_3_turnin_anim;
    std::string     m_state_4_turnin_anim;
    std::string     m_onclick_anim;
    std::string     m_CinematicAccepted;
    float           m_CinematicAcceptedLeadin;
    std::string     m_CinematicCompleted;
    float           m_CinematicCompletedLeadin;
    std::string     m_CinematicRepeatable;
    float           m_CinematicRepeatableLeadin;
    std::string     m_CinematicRepeatableCompleted;
    float           m_CinematicRepeatableCompletedLeadin;
    std::string     m_AudioEventGUID_Interact;
    std::string     m_AudioEventGUID_OfferAccept;
    std::string     m_AudioEventGUID_OfferDeny;
    std::string     m_AudioEventGUID_Completed;
    std::string     m_AudioEventGUID_TurnIn;
    std::string     m_AudioEventGUID_Failed;
    std::string     m_AudioEventGUID_Progress;
    std::string     m_AudioMusicCue_OfferAccept;
    std::string     m_AudioMusicCue_TurnIn;
    int32_t         m_turnInIconID;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
MissionText;

void readDB(MissionText& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_id;
    std::string     m_defined_type;
    std::string     m_defined_subtype;
    int32_t         m_UISortOrder;
    int32_t         m_offer_objectID;
    int32_t         m_target_objectID;
    int64_t         m_reward_currency;
    int32_t         m_LegoScore;
    int64_t         m_reward_reputation;
    bool            m_isChoiceReward;
    int32_t         m_reward_item1;
    int32_t         m_reward_item1_count;
    int32_t         m_reward_item2;
    int32_t         m_reward_item2_count;
    int32_t         m_reward_item3;
    int32_t         m_reward_item3_count;
    int32_t         m_reward_item4;
    int32_t         m_reward_item4_count;
    int32_t         m_reward_emote;
    int32_t         m_reward_emote2;
    int32_t         m_reward_emote3;
    int32_t         m_reward_emote4;
    int32_t         m_reward_maximagination;
    int32_t         m_reward_maxhealth;
    int32_t         m_reward_maxinventory;
    int32_t         m_reward_maxmodel;
    int32_t         m_reward_maxwidget;
    int64_t         m_reward_maxwallet;
    bool            m_repeatable;
    int64_t         m_reward_currency_repeatable;
    int32_t         m_reward_item1_repeatable;
    int32_t         m_reward_item1_repeat_count;
    int32_t         m_reward_item2_repeatable;
    int32_t         m_reward_item2_repeat_count;
    int32_t         m_reward_item3_repeatable;
    int32_t         m_reward_item3_repeat_count;
    int32_t         m_reward_item4_repeatable;
    int32_t         m_reward_item4_repeat_count;
    int32_t         m_time_limit;
    bool            m_isMission;
    int32_t         m_missionIconID;
    std::string     m_prereqMissionID;
    bool            m_localize;
    bool            m_inMOTD;
    int64_t         m_cooldownTime;
    bool            m_isRandom;
    std::string     m_randomPool;
    int32_t         m_UIPrereqID;
    std::string     m_gate_version;
    std::string     m_HUDStates;
    int32_t         m_locStatus;
    int32_t         m_reward_bankinventory;
}
Missions;

void readDB(Missions& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_id;
    std::string     m_definitionXMLfilename;
}
ModelBehavior;

void readDB(ModelBehavior& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_id;
    int32_t         m_buildType;
    std::string     m_xml;
    int32_t         m_createdLOT;
    int32_t         m_createdPhysicsID;
    std::string     m_AudioEventGUID_Snap;
    std::string     m_AudioEventGUID_Complete;
    std::string     m_AudioEventGUID_Present;
}
ModularBuildComponent;

void readDB(ModularBuildComponent& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_id;
    int32_t         m_partCode;
    int32_t         m_buildType;
    std::string     m_xml;
    std::string     m_primarySoundGUID;
    int32_t         m_assembledEffectID;
}
ModuleComponent;

void readDB(ModuleComponent& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_id;
    int32_t         m_typeID;
    float           m_slamVelocity;
    float           m_addVelocity;
    float           m_duration;
    std::string     m_destGroupName;
    float           m_startScale;
    float           m_endScale;
    float           m_velocity;
    float           m_distance;
}
MotionFX;

void readDB(MotionFX& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    std::string     m_MovementType;
    float           m_WanderChance;
    float           m_WanderDelayMin;
    float           m_WanderDelayMax;
    float           m_WanderSpeed;
    float           m_WanderRadius;
    std::string     m_attachedPath;
}
MovementAIComponent;

void readDB(MovementAIComponent& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    bool            m_platformIsSimpleMover;
    float           m_platformMoveX;
    float           m_platformMoveY;
    float           m_platformMoveZ;
    float           m_platformMoveTime;
    bool            m_platformStartAtEnd;
    std::string     m_description;
}
MovingPlatforms;

void readDB(MovingPlatforms& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_id;
    int32_t         m_color;
    float           m_offset;
    int32_t         m_LOT;
    std::string     m_Texture;
    bool            m_isClickable;
    float           m_scale;
    bool            m_rotateToFace;
    float           m_compositeHorizOffset;
    float           m_compositeVertOffset;
    float           m_compositeScale;
    std::string     m_compositeConnectionNode;
    int32_t         m_compositeLOTMultiMission;
    int32_t         m_compositeLOTMultiMissionVentor;
    std::string     m_compositeIconTexture;
}
NpcIcons;

void readDB(NpcIcons& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_LOT;
    int64_t         m_behaviorID1;
    int64_t         m_behaviorID2;
    int64_t         m_behaviorID3;
    int64_t         m_behaviorID4;
    int64_t         m_behaviorID5;
    int32_t         m_type;
}
ObjectBehaviorXREF;

void readDB(ObjectBehaviorXREF& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int64_t         m_BehaviorID;
    std::string     m_xmldata;
}
ObjectBehaviors;

void readDB(ObjectBehaviors& entry, std::istream& file);

// SlotCount: 4096
typedef struct
{
    int32_t         m_objectTemplate;
    int32_t         m_skillID;
    int32_t         m_castOnType;
    int32_t         m_AICombatWeight;
}
ObjectSkills;

void readDB(ObjectSkills& entry, std::istream& file);

// SlotCount: 16384
typedef struct
{
    int32_t         m_id;
    std::string     m_name;
    bool            m_placeable;
    std::string     m_type;
    std::string     m_description;
    bool            m_localize;
    int32_t         m_npcTemplateID;
    std::string     m_displayName;
    float           m_interactionDistance;
    bool            m_nametag;
    std::string     m__internalNotes;
    int32_t         m_locStatus;
    std::string     m_gate_version;
    bool            m_HQ_valid;
}
Objects;

void readDB(Objects& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_id;
    int32_t         m_LootMatrixIndex;
    int32_t         m_packageType;
}
PackageComponent;

void readDB(PackageComponent& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_id;
    std::string     m_AbilityName;
    int32_t         m_ImaginationCost;
    int32_t         m_locStatus;
}
PetAbilities;

void readDB(PetAbilities& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    float           m_minTameUpdateTime;
    float           m_maxTameUpdateTime;
    float           m_percentTameChance;
    float           m_tamability;
    int32_t         m_elementType;
    float           m_walkSpeed;
    float           m_runSpeed;
    float           m_sprintSpeed;
    float           m_idleTimeMin;
    float           m_idleTimeMax;
    int32_t         m_petForm;
    float           m_imaginationDrainRate;
    std::string     m_AudioMetaEventSet;
    std::string     m_buffIDs;
}
PetComponent;

void readDB(PetComponent& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    int32_t         m_id;
    int32_t         m_ElementalType;
}
PetNestComponent;

void readDB(PetNestComponent& entry, std::istream& file);

// SlotCount: 8192
typedef struct
{
    int32_t         m_id;
    float           m_static;
    std::string     m_physics_asset;
    float           m_jump;
    float           m_doublejump;
    float           m_speed;
    float           m_rotSpeed;
    float           m_playerHeight;
    float           m_playerRadius;
    int32_t         m_pcShapeType;
    int32_t         m_collisionGroup;
    float           m_airSpeed;
    std::string     m_boundaryAsset;
    float           m_jumpAirSpeed;
    float           m_friction;
    std::string     m_gravityVolumeAsset;
}
PhysicsComponent;

void readDB(PhysicsComponent& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_id;
    bool            m_SessionOnly;
    bool            m_OnlySetByServer;
    bool            m_SessionZoneOnly;
}
PlayerFlags;

void readDB(PlayerFlags& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_statID;
    int32_t         m_sortOrder;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
PlayerStatistics;

void readDB(PlayerStatistics& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    int32_t         m_controlSchemeID;
    std::string     m_minifigAttachPoint;
    std::string     m_minifigAttachAnimation;
    std::string     m_minifigDetachAnimation;
    std::string     m_mountAttachAnimation;
    std::string     m_mountDetachAnimation;
    float           m_attachOffsetFwd;
    float           m_attachOffsetRight;
    int32_t         m_possessionType;
    bool            m_wantBillboard;
    float           m_billboardOffsetUp;
    bool            m_depossessOnHit;
    float           m_hitStunTime;
    int32_t         m_skillSet;
}
PossessableComponent;

void readDB(PossessableComponent& entry, std::istream& file);

// SlotCount: 512
typedef struct
{
    int32_t         m_id;
    int32_t         m_type;
    std::string     m_targetLOT;
    std::string     m_targetGroup;
    int32_t         m_targetCount;
    int32_t         m_iconID;
    bool            m_localize;
    int64_t         m_validContexts;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
Preconditions;

void readDB(Preconditions& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    int32_t         m_mapID;
    std::string     m_propertyName;
    bool            m_isOnProperty;
    std::string     m_groupType;
}
PropertyEntranceComponent;

void readDB(PropertyEntranceComponent& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_mapID;
    int32_t         m_vendorMapID;
    std::string     m_spawnName;
    int32_t         m_type;
    int32_t         m_sizecode;
    int32_t         m_minimumPrice;
    int32_t         m_rentDuration;
    std::string     m_path;
    int32_t         m_cloneLimit;
    int32_t         m_durationType;
    int32_t         m_achievementRequired;
    float           m_zoneX;
    float           m_zoneY;
    float           m_zoneZ;
    float           m_maxBuildHeight;
    bool            m_localize;
    int32_t         m_reputationPerMinute;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
PropertyTemplate;

void readDB(PropertyTemplate& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    std::string     m_Proximities;
    bool            m_LoadOnClient;
    bool            m_LoadOnServer;
}
ProximityMonitorComponent;

void readDB(ProximityMonitorComponent& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_id;
    std::string     m_Name;
    int32_t         m_Radius;
    int32_t         m_CollisionGroup;
    bool            m_PassiveChecks;
    int32_t         m_IconID;
    bool            m_LoadOnClient;
    bool            m_LoadOnServer;
}
ProximityTypes;

void readDB(ProximityTypes& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    float           m_topSpeed;
    float           m_acceleration;
    float           m_handling;
    float           m_stability;
    float           m_imagination;
}
RacingModuleComponent;

void readDB(RacingModuleComponent& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    std::string     m_startAnim;
    std::string     m_loopAnim;
    std::string     m_stopAnim;
    std::string     m_startSound;
    std::string     m_loopSound;
    std::string     m_stopSound;
    std::string     m_effectIDs;
    std::string     m_preconditions;
    bool            m_playerCollision;
    bool            m_cameraLocked;
    std::string     m_StartEffectID;
    std::string     m_StopEffectID;
    bool            m_DamageImmune;
    bool            m_NoAggro;
    bool            m_ShowNameBillboard;
}
RailActivatorComponent;

void readDB(RailActivatorComponent& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    float           m_randmax;
    int32_t         m_rarity;
    int32_t         m_RarityTableIndex;
}
RarityTable;

void readDB(RarityTable& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_RarityTableIndex;
}
RarityTableIndex;

void readDB(RarityTableIndex& entry, std::istream& file);

// SlotCount: 256
typedef struct
{
    int32_t         m_id;
    float           m_reset_time;
    float           m_complete_time;
    int32_t         m_take_imagination;
    bool            m_interruptible;
    bool            m_self_activator;
    std::string     m_custom_modules;
    int32_t         m_activityID;
    int32_t         m_post_imagination_cost;
    float           m_time_before_smash;
}
RebuildComponent;

void readDB(RebuildComponent& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_rebuildID;
    int32_t         m_objectID;
    float           m_offset_x;
    float           m_offset_y;
    float           m_offset_z;
    float           m_fall_angle_x;
    float           m_fall_angle_y;
    float           m_fall_angle_z;
    float           m_fall_height;
    std::string     m_requires_list;
    int32_t         m_size;
    bool            m_bPlaced;
}
RebuildSections;

void readDB(RebuildSections& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    std::string     m_ReleaseVersion;
    int64_t         m_ReleaseDate;
}
Release_Version;

void readDB(Release_Version& entry, std::istream& file);

// SlotCount: 16384
typedef struct
{
    int32_t         m_id;
    std::string     m_render_asset;
    std::string     m_icon_asset;
    int32_t         m_IconID;
    int32_t         m_shader_id;
    int32_t         m_effect1;
    int32_t         m_effect2;
    int32_t         m_effect3;
    int32_t         m_effect4;
    int32_t         m_effect5;
    int32_t         m_effect6;
    std::string     m_animationGroupIDs;
    bool            m_fade;
    bool            m_usedropshadow;
    bool            m_preloadAnimations;
    float           m_fadeInTime;
    float           m_maxShadowDistance;
    bool            m_ignoreCameraCollision;
    int32_t         m_renderComponentLOD1;
    int32_t         m_renderComponentLOD2;
    bool            m_gradualSnap;
    int32_t         m_animationFlag;
    std::string     m_AudioMetaEventSet;
    float           m_billboardHeight;
    float           m_chatBubbleOffset;
    bool            m_staticBillboard;
    std::string     m_LXFMLFolder;
    bool            m_attachIndicatorsToNode;
}
RenderComponent;

void readDB(RenderComponent& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    bool            m_interactive;
    bool            m_animated;
    std::string     m_nodeName;
    std::string     m_flashPath;
    std::string     m_elementName;
    int32_t         m__uid;
}
RenderComponentFlash;

void readDB(RenderComponentFlash& entry, std::istream& file);

// SlotCount: 2
typedef struct
{
    int32_t         m_id;
    std::string     m_defaultWrapperAsset;
}
RenderComponentWrapper;

void readDB(RenderComponentWrapper& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_id;
    std::string     m_icon_asset;
    std::string     m_blank_column;
}
RenderIconAssets;

void readDB(RenderIconAssets& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_repLevel;
    int32_t         m_sublevel;
    float           m_reputation;
}
ReputationRewards;

void readDB(ReputationRewards& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    std::string     m_code;
    int32_t         m_attachmentLOT;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
RewardCodes;

void readDB(RewardCodes& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    int32_t         m_LevelID;
    int32_t         m_MissionID;
    int32_t         m_RewardType;
    int32_t         m_value;
    int32_t         m_count;
}
Rewards;

void readDB(Rewards& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    int32_t         m_targetZone;
    int32_t         m_defaultZoneID;
    std::string     m_targetScene;
    int32_t         m_gmLevel;
    std::string     m_playerAnimation;
    std::string     m_rocketAnimation;
    std::string     m_launchMusic;
    bool            m_useLaunchPrecondition;
    bool            m_useAltLandingPrecondition;
    std::string     m_launchPrecondition;
    std::string     m_altLandingPrecondition;
    std::string     m_altLandingSpawnPointName;
}
RocketLaunchpadControlComponent;

void readDB(RocketLaunchpadControlComponent& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_sceneID;
    std::string     m_sceneName;
}
SceneTable;

void readDB(SceneTable& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_id;
    std::string     m_script_name;
    std::string     m_client_script_name;
}
ScriptComponent;

void readDB(ScriptComponent& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_skillID;
    int32_t         m_locStatus;
    int32_t         m_behaviorID;
    int32_t         m_imaginationcost;
    int32_t         m_cooldowngroup;
    float           m_cooldown;
    bool            m_inNpcEditor;
    int32_t         m_skillIcon;
    std::string     m_oomSkillID;
    int32_t         m_oomBehaviorEffectID;
    int32_t         m_castTypeDesc;
    int32_t         m_imBonusUI;
    int32_t         m_lifeBonusUI;
    int32_t         m_armorBonusUI;
    int32_t         m_damageUI;
    bool            m_hideIcon;
    bool            m_localize;
    std::string     m_gate_version;
    int32_t         m_cancelType;
}
SkillBehavior;

void readDB(SkillBehavior& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_chainIndex;
    int32_t         m_chainLevel;
    int32_t         m_lootMatrixID;
    int32_t         m_rarityTableIndex;
    int32_t         m_currencyIndex;
    int32_t         m_currencyLevel;
    int32_t         m_smashCount;
    int32_t         m_timeLimit;
    int32_t         m_chainStepID;
}
SmashableChain;

void readDB(SmashableChain& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    int32_t         m_id;
    std::string     m_targetGroup;
    std::string     m_description;
    int32_t         m_continuous;
}
SmashableChainIndex;

void readDB(SmashableChainIndex& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_id;
    int32_t         m_LootMatrixIndex;
}
SmashableComponent;

void readDB(SmashableComponent& entry, std::istream& file);

// SlotCount: 1024
typedef struct
{
    int32_t         m_elementID;
    int32_t         m_dropWeight;
}
SmashableElements;

void readDB(SmashableElements& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    int32_t         m_parentId;
    int32_t         m_emoteId;
    std::string     m_imageName;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
SpeedchatMenu;

void readDB(SpeedchatMenu& entry, std::istream& file);

// SlotCount: 4
typedef struct
{
    int32_t         m_id;
    std::string     m_countryCode;
    std::string     m_monthlyFeeGold;
    std::string     m_monthlyFeeSilver;
    std::string     m_monthlyFeeBronze;
    int32_t         m_monetarySymbol;
    bool            m_symbolIsAppended;
}
SubscriptionPricing;

void readDB(SubscriptionPricing& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_SurfaceType;
    std::string     m_FootstepNDAudioMetaEventSetName;
}
SurfaceType;

void readDB(SurfaceType& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_id;
    int32_t         m_PuzzleModelLot;
    int32_t         m_NPCLot;
    std::string     m_ValidPiecesLXF;
    std::string     m_InvalidPiecesLXF;
    int32_t         m_Difficulty;
    int32_t         m_Timelimit;
    int32_t         m_NumValidPieces;
    int32_t         m_TotalNumPieces;
    std::string     m_ModelName;
    std::string     m_FullModelLXF;
    float           m_Duration;
    int32_t         m_imagCostPerBuild;
}
TamingBuildPuzzles;

void readDB(TamingBuildPuzzles& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_TextID;
    std::string     m_TestDescription;
}
TextDescription;

void readDB(TextDescription& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_TextID;
    int32_t         m_LanguageID;
    std::string     m_Text;
}
TextLanguage;

void readDB(TextLanguage& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_trailID;
    std::string     m_textureName;
    int32_t         m_blendmode;
    float           m_cardlifetime;
    float           m_colorlifetime;
    float           m_minTailFade;
    float           m_tailFade;
    int32_t         m_max_particles;
    float           m_birthDelay;
    float           m_deathDelay;
    std::string     m_bone1;
    std::string     m_bone2;
    float           m_texLength;
    float           m_texWidth;
    float           m_startColorR;
    float           m_startColorG;
    float           m_startColorB;
    float           m_startColorA;
    float           m_middleColorR;
    float           m_middleColorG;
    float           m_middleColorB;
    float           m_middleColorA;
    float           m_endColorR;
    float           m_endColorG;
    float           m_endColorB;
    float           m_endColorA;
}
TrailEffects;

void readDB(TrailEffects& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_id;
    std::string     m_guid;
    bool            m_localize;
    int32_t         m_locStatus;
    std::string     m_gate_version;
}
UGBehaviorSounds;

void readDB(UGBehaviorSounds& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_id;
    std::string     m_hkxFilename;
    float           m_fGravityScale;
    float           m_fMass;
    float           m_fChassisFriction;
    float           m_fMaxSpeed;
    float           m_fEngineTorque;
    float           m_fBrakeFrontTorque;
    float           m_fBrakeRearTorque;
    float           m_fBrakeMinInputToBlock;
    float           m_fBrakeMinTimeToBlock;
    float           m_fSteeringMaxAngle;
    float           m_fSteeringSpeedLimitForMaxAngle;
    float           m_fSteeringMinAngle;
    float           m_fFwdBias;
    float           m_fFrontTireFriction;
    float           m_fRearTireFriction;
    float           m_fFrontTireFrictionSlide;
    float           m_fRearTireFrictionSlide;
    float           m_fFrontTireSlipAngle;
    float           m_fRearTireSlipAngle;
    float           m_fWheelWidth;
    float           m_fWheelRadius;
    float           m_fWheelMass;
    float           m_fReorientPitchStrength;
    float           m_fReorientRollStrength;
    float           m_fSuspensionLength;
    float           m_fSuspensionStrength;
    float           m_fSuspensionDampingCompression;
    float           m_fSuspensionDampingRelaxation;
    int32_t         m_iChassisCollisionGroup;
    float           m_fNormalSpinDamping;
    float           m_fCollisionSpinDamping;
    float           m_fCollisionThreshold;
    float           m_fTorqueRollFactor;
    float           m_fTorquePitchFactor;
    float           m_fTorqueYawFactor;
    float           m_fInertiaRoll;
    float           m_fInertiaPitch;
    float           m_fInertiaYaw;
    float           m_fExtraTorqueFactor;
    float           m_fCenterOfMassFwd;
    float           m_fCenterOfMassUp;
    float           m_fCenterOfMassRight;
    float           m_fWheelHardpointFrontFwd;
    float           m_fWheelHardpointFrontUp;
    float           m_fWheelHardpointFrontRight;
    float           m_fWheelHardpointRearFwd;
    float           m_fWheelHardpointRearUp;
    float           m_fWheelHardpointRearRight;
    float           m_fInputTurnSpeed;
    float           m_fInputDeadTurnBackSpeed;
    float           m_fInputAccelSpeed;
    float           m_fInputDeadAccelDownSpeed;
    float           m_fInputDecelSpeed;
    float           m_fInputDeadDecelDownSpeed;
    float           m_fInputSlopeChangePointX;
    float           m_fInputInitialSlope;
    float           m_fInputDeadZone;
    float           m_fAeroAirDensity;
    float           m_fAeroFrontalArea;
    float           m_fAeroDragCoefficient;
    float           m_fAeroLiftCoefficient;
    float           m_fAeroExtraGravity;
    float           m_fBoostTopSpeed;
    float           m_fBoostCostPerSecond;
    float           m_fBoostAccelerateChange;
    float           m_fBoostDampingChange;
    float           m_fPowerslideNeutralAngle;
    float           m_fPowerslideTorqueStrength;
    int32_t         m_iPowerslideNumTorqueApplications;
    float           m_fImaginationTankSize;
    float           m_fSkillCost;
    float           m_fWreckSpeedBase;
    float           m_fWreckSpeedPercent;
    float           m_fWreckMinAngle;
    std::string     m_AudioEventEngine;
    std::string     m_AudioEventSkid;
    std::string     m_AudioEventLightHit;
    float           m_AudioSpeedThresholdLightHit;
    float           m_AudioTimeoutLightHit;
    std::string     m_AudioEventHeavyHit;
    float           m_AudioSpeedThresholdHeavyHit;
    float           m_AudioTimeoutHeavyHit;
    std::string     m_AudioEventStart;
    std::string     m_AudioEventTreadConcrete;
    std::string     m_AudioEventTreadSand;
    std::string     m_AudioEventTreadWood;
    std::string     m_AudioEventTreadDirt;
    std::string     m_AudioEventTreadPlastic;
    std::string     m_AudioEventTreadGrass;
    std::string     m_AudioEventTreadGravel;
    std::string     m_AudioEventTreadMud;
    std::string     m_AudioEventTreadWater;
    std::string     m_AudioEventTreadSnow;
    std::string     m_AudioEventTreadIce;
    std::string     m_AudioEventTreadMetal;
    std::string     m_AudioEventTreadLeaves;
    std::string     m_AudioEventLightLand;
    float           m_AudioAirtimeForLightLand;
    std::string     m_AudioEventHeavyLand;
    float           m_AudioAirtimeForHeavyLand;
    bool            m_bWheelsVisible;
}
VehiclePhysics;

void readDB(VehiclePhysics& entry, std::istream& file);

// SlotCount: 8
typedef struct
{
    int32_t         m_id;
    std::string     m_ModuleStat;
    std::string     m_HavokStat;
    float           m_HavokChangePerModuleStat;
}
VehicleStatMap;

void readDB(VehicleStatMap& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    float           m_buyScalar;
    float           m_sellScalar;
    float           m_refreshTimeSeconds;
    int32_t         m_LootMatrixIndex;
}
VendorComponent;

void readDB(VendorComponent& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_itemID;
    bool            m_localize;
    std::string     m_gate_version;
    int32_t         m_locStatus;
}
WhatsCoolItemSpotlight;

void readDB(WhatsCoolItemSpotlight& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    int32_t         m_iconID;
    int32_t         m_type;
    bool            m_localize;
    std::string     m_gate_version;
    int32_t         m_locStatus;
}
WhatsCoolNewsAndTips;

void readDB(WhatsCoolNewsAndTips& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    int32_t         m_WorldConfigID;
    float           m_pegravityvalue;
    float           m_pebroadphaseworldsize;
    float           m_pegameobjscalefactor;
    float           m_character_rotation_speed;
    float           m_character_walk_forward_speed;
    float           m_character_walk_backward_speed;
    float           m_character_walk_strafe_speed;
    float           m_character_walk_strafe_forward_speed;
    float           m_character_walk_strafe_backward_speed;
    float           m_character_run_backward_speed;
    float           m_character_run_strafe_speed;
    float           m_character_run_strafe_forward_speed;
    float           m_character_run_strafe_backward_speed;
    float           m_global_cooldown;
    float           m_characterGroundedTime;
    float           m_characterGroundedSpeed;
    float           m_globalImmunityTime;
    float           m_character_max_slope;
    float           m_defaultrespawntime;
    float           m_mission_tooltip_timeout;
    float           m_vendor_buy_multiplier;
    float           m_pet_follow_radius;
    float           m_character_eye_height;
    float           m_flight_vertical_velocity;
    float           m_flight_airspeed;
    float           m_flight_fuel_ratio;
    float           m_flight_max_airspeed;
    float           m_fReputationPerVote;
    int32_t         m_nPropertyCloneLimit;
    int32_t         m_defaultHomespaceTemplate;
    float           m_coins_lost_on_death_percent;
    int32_t         m_coins_lost_on_death_min;
    int32_t         m_coins_lost_on_death_max;
    int32_t         m_character_votes_per_day;
    int32_t         m_property_moderation_request_approval_cost;
    int32_t         m_property_moderation_request_review_cost;
    int32_t         m_propertyModRequestsAllowedSpike;
    int32_t         m_propertyModRequestsAllowedInterval;
    int32_t         m_propertyModRequestsAllowedTotal;
    int32_t         m_propertyModRequestsSpikeDuration;
    int32_t         m_propertyModRequestsIntervalDuration;
    bool            m_modelModerateOnCreate;
    float           m_defaultPropertyMaxHeight;
    float           m_reputationPerVoteCast;
    float           m_reputationPerVoteReceived;
    int32_t         m_showcaseTopModelConsiderationBattles;
    float           m_reputationPerBattlePromotion;
    float           m_coins_lost_on_death_min_timeout;
    float           m_coins_lost_on_death_max_timeout;
    int32_t         m_mail_base_fee;
    float           m_mail_percent_attachment_fee;
    int32_t         m_propertyReputationDelay;
    int32_t         m_LevelCap;
    std::string     m_LevelUpBehaviorEffect;
    int32_t         m_CharacterVersion;
    int32_t         m_LevelCapCurrencyConversion;
}
WorldConfig;

void readDB(WorldConfig& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_id;
    int32_t         m_zoneid;
    std::string     m_imagelocation;
    bool            m_localize;
    std::string     m_gate_version;
    int32_t         m_locStatus;
    int32_t         m_weight;
    std::string     m_targetVersion;
}
ZoneLoadingTips;

void readDB(ZoneLoadingTips& entry, std::istream& file);

// SlotCount: 64
typedef struct
{
    int32_t         m_zoneID;
    int32_t         m_type;
    int32_t         m_value;
    int32_t         m__uniqueID;
}
ZoneSummary;

void readDB(ZoneSummary& entry, std::istream& file);

// SlotCount: 2048
typedef struct
{
    int32_t         m_zoneID;
    int32_t         m_locStatus;
    std::string     m_zoneName;
    int32_t         m_scriptID;
    float           m_ghostdistance_min;
    float           m_ghostdistance;
    int32_t         m_population_soft_cap;
    int32_t         m_population_hard_cap;
    std::string     m_DisplayDescription;
    std::string     m_mapFolder;
    float           m_smashableMinDistance;
    float           m_smashableMaxDistance;
    std::string     m_mixerProgram;
    std::string     m_clientPhysicsFramerate;
    std::string     m_serverPhysicsFramerate;
    int32_t         m_zoneControlTemplate;
    int32_t         m_widthInChunks;
    int32_t         m_heightInChunks;
    bool            m_petsAllowed;
    bool            m_localize;
    float           m_fZoneWeight;
    std::string     m_thumbnail;
    bool            m_PlayerLoseCoinsOnDeath;
    bool            m_disableSaveLoc;
    float           m_teamRadius;
    std::string     m_gate_version;
    bool            m_mountsAllowed;
}
ZoneTable;

void readDB(ZoneTable& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_ID;
    std::string     m_icon_asset;
    int32_t         m_display_order;
    int32_t         m_locStatus;
}
brickAttributes;

void readDB(brickAttributes& entry, std::istream& file);

// SlotCount: 0
typedef struct
{
    int32_t         m_id;
    int32_t         m_objectid;
    std::string     m_property;
    std::string     m_value;
    std::string     m_uvalue;
    void*           m_lvalue;
    int32_t         m_version;
}
dtproperties;

void readDB(dtproperties& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    std::string     m_name;
    float           m_priority;
}
mapAnimationPriorities;

void readDB(mapAnimationPriorities& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    std::string     m_label;
    std::string     m_pathdir;
    std::string     m_typelabel;
}
mapAssetType;

void readDB(mapAssetType& entry, std::istream& file);

// SlotCount: 4096
typedef struct
{
    int32_t         m_LOT;
    int32_t         m_iconID;
    int32_t         m_iconState;
}
mapIcon;

void readDB(mapIcon& entry, std::istream& file);

// SlotCount: 32
typedef struct
{
    int32_t         m_id;
    std::string     m_description;
    std::string     m_equipLocation;
}
mapItemTypes;

void readDB(mapItemTypes& entry, std::istream& file);

// SlotCount: 16
typedef struct
{
    int32_t         m_id;
    int32_t         m_gameID;
    std::string     m_description;
}
mapRenderEffects;

void readDB(mapRenderEffects& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    std::string     m_label;
    int32_t         m_gameValue;
    int32_t         m_priority;
}
mapShaders;

void readDB(mapShaders& entry, std::istream& file);

// SlotCount: 128
typedef struct
{
    int32_t         m_id;
    std::string     m_texturepath;
    int32_t         m_SurfaceType;
}
mapTextureResource;

void readDB(mapTextureResource& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    int32_t         m_id;
    std::string     m_description;
    bool            m_enabled;
}
map_BlueprintCategory;

void readDB(map_BlueprintCategory& entry, std::istream& file);

// SlotCount: 1
typedef struct
{
    std::string     m_name;
    int32_t         m_principal_id;
    int32_t         m_diagram_id;
    int32_t         m_version;
    std::string     m_definition;
}
sysdiagrams;

void readDB(sysdiagrams& entry, std::istream& file);

