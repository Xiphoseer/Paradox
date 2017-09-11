#include "cdclient.hpp"

void readDB(AICombatRoles& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_preferredRole);
    readField(file, entry.m_specifiedMinRangeNOUSE);
    readField(file, entry.m_specifiedMaxRangeNOUSE);
    readField(file, entry.m_specificMinRange);
    readField(file, entry.m_specificMaxRange);
}

void readDB(AccessoryDefaultLoc& entry, std::istream& file)
{
    readField(file, entry.m_GroupID);
    readField(file, entry.m_Description);
    readField(file, entry.m_Pos_X);
    readField(file, entry.m_Pos_Y);
    readField(file, entry.m_Pos_Z);
    readField(file, entry.m_Rot_X);
    readField(file, entry.m_Rot_Y);
    readField(file, entry.m_Rot_Z);
}

void readDB(Activities& entry, std::istream& file)
{
    readField(file, entry.m_ActivityID);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_instanceMapID);
    readField(file, entry.m_minTeams);
    readField(file, entry.m_maxTeams);
    readField(file, entry.m_minTeamSize);
    readField(file, entry.m_maxTeamSize);
    readField(file, entry.m_waitTime);
    readField(file, entry.m_startDelay);
    readField(file, entry.m_requiresUniqueData);
    readField(file, entry.m_leaderboardType);
    readField(file, entry.m_localize);
    readField(file, entry.m_optionalCostLOT);
    readField(file, entry.m_optionalCostCount);
    readField(file, entry.m_showUIRewards);
    readField(file, entry.m_CommunityActivityFlagID);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_noTeamLootOnDeath);
    readField(file, entry.m_optionalPercentage);
}

void readDB(ActivityRewards& entry, std::istream& file)
{
    readField(file, entry.m_objectTemplate);
    readField(file, entry.m_ActivityRewardIndex);
    readField(file, entry.m_activityRating);
    readField(file, entry.m_LootMatrixIndex);
    readField(file, entry.m_CurrencyIndex);
    readField(file, entry.m_ChallengeRating);
    readField(file, entry.m_description);
}

void readDB(ActivityText& entry, std::istream& file)
{
    readField(file, entry.m_activityID);
    readField(file, entry.m_type);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(AnimationIndex& entry, std::istream& file)
{
    readField(file, entry.m_animationGroupID);
    readField(file, entry.m_description);
    readField(file, entry.m_groupType);
}

void readDB(Animations& entry, std::istream& file)
{
    readField(file, entry.m_animationGroupID);
    readField(file, entry.m_animation_type);
    readField(file, entry.m_animation_name);
    readField(file, entry.m_chance_to_play);
    readField(file, entry.m_min_loops);
    readField(file, entry.m_max_loops);
    readField(file, entry.m_animation_length);
    readField(file, entry.m_hideEquip);
    readField(file, entry.m_ignoreUpperBody);
    readField(file, entry.m_restartable);
    readField(file, entry.m_face_animation_name);
    readField(file, entry.m_priority);
    readField(file, entry.m_blendTime);
}

void readDB(BaseCombatAIComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_behaviorType);
    readField(file, entry.m_combatRoundLength);
    readField(file, entry.m_combatRole);
    readField(file, entry.m_minRoundLength);
    readField(file, entry.m_maxRoundLength);
    readField(file, entry.m_tetherSpeed);
    readField(file, entry.m_pursuitSpeed);
    readField(file, entry.m_combatStartDelay);
    readField(file, entry.m_softTetherRadius);
    readField(file, entry.m_hardTetherRadius);
    readField(file, entry.m_spawnTimer);
    readField(file, entry.m_tetherEffectID);
    readField(file, entry.m_ignoreMediator);
    readField(file, entry.m_aggroRadius);
    readField(file, entry.m_ignoreStatReset);
    readField(file, entry.m_ignoreParent);
}

void readDB(BehaviorEffect& entry, std::istream& file)
{
    readField(file, entry.m_effectID);
    readField(file, entry.m_effectType);
    readField(file, entry.m_effectName);
    readField(file, entry.m_trailID);
    readField(file, entry.m_pcreateDuration);
    readField(file, entry.m_animationName);
    readField(file, entry.m_attachToObject);
    readField(file, entry.m_boneName);
    readField(file, entry.m_useSecondary);
    readField(file, entry.m_cameraEffectType);
    readField(file, entry.m_cameraDuration);
    readField(file, entry.m_cameraFrequency);
    readField(file, entry.m_cameraXAmp);
    readField(file, entry.m_cameraYAmp);
    readField(file, entry.m_cameraZAmp);
    readField(file, entry.m_cameraRotFrequency);
    readField(file, entry.m_cameraRoll);
    readField(file, entry.m_cameraPitch);
    readField(file, entry.m_cameraYaw);
    readField(file, entry.m_AudioEventGUID);
    readField(file, entry.m_renderEffectType);
    readField(file, entry.m_renderEffectTime);
    readField(file, entry.m_renderStartVal);
    readField(file, entry.m_renderEndVal);
    readField(file, entry.m_renderDelayVal);
    readField(file, entry.m_renderValue1);
    readField(file, entry.m_renderValue2);
    readField(file, entry.m_renderValue3);
    readField(file, entry.m_renderRGBA);
    readField(file, entry.m_renderShaderVal);
    readField(file, entry.m_motionID);
    readField(file, entry.m_meshID);
    readField(file, entry.m_meshDuration);
    readField(file, entry.m_meshLockedNode);
}

void readDB(BehaviorParameter& entry, std::istream& file)
{
    readField(file, entry.m_behaviorID);
    readField(file, entry.m_parameterID);
    readField(file, entry.m_value);
}

void readDB(BehaviorTemplate& entry, std::istream& file)
{
    readField(file, entry.m_behaviorID);
    readField(file, entry.m_templateID);
    readField(file, entry.m_effectID);
    readField(file, entry.m_effectHandle);
}

void readDB(BehaviorTemplateName& entry, std::istream& file)
{
    readField(file, entry.m_templateID);
    readField(file, entry.m_name);
}

void readDB(Blueprints& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_name);
    readField(file, entry.m_description);
    readField(file, entry.m_accountid);
    readField(file, entry.m_characterid);
    readField(file, entry.m_price);
    readField(file, entry.m_rating);
    readField(file, entry.m_categoryid);
    readField(file, entry.m_lxfpath);
    readField(file, entry.m_deleted);
    readField(file, entry.m_created);
    readField(file, entry.m_modified);
}

void readDB(BrickColors& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_red);
    readField(file, entry.m_green);
    readField(file, entry.m_blue);
    readField(file, entry.m_alpha);
    readField(file, entry.m_legopaletteid);
    readField(file, entry.m_description);
    readField(file, entry.m_validTypes);
    readField(file, entry.m_validCharacters);
    readField(file, entry.m_factoryValid);
}

void readDB(BrickIDTable& entry, std::istream& file)
{
    readField(file, entry.m_NDObjectID);
    readField(file, entry.m_LEGOBrickID);
}

void readDB(BuffDefinitions& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_Priority);
    readField(file, entry.m_UIIcon);
}

void readDB(BuffParameters& entry, std::istream& file)
{
    readField(file, entry.m_BuffID);
    readField(file, entry.m_ParameterName);
    readField(file, entry.m_NumberValue);
    readField(file, entry.m_StringValue);
    readField(file, entry.m_EffectID);
}

void readDB(Camera& entry, std::istream& file)
{
    readField(file, entry.m_camera_name);
    readField(file, entry.m_pitch_angle_tolerance);
    readField(file, entry.m_starting_zoom);
    readField(file, entry.m_zoom_return_modifier);
    readField(file, entry.m_pitch_return_modifier);
    readField(file, entry.m_tether_out_return_modifier);
    readField(file, entry.m_tether_in_return_multiplier);
    readField(file, entry.m_verticle_movement_dampening_modifier);
    readField(file, entry.m_return_from_incline_modifier);
    readField(file, entry.m_horizontal_return_modifier);
    readField(file, entry.m_yaw_behavior_speed_multiplier);
    readField(file, entry.m_camera_collision_padding);
    readField(file, entry.m_glide_speed);
    readField(file, entry.m_fade_player_min_range);
    readField(file, entry.m_min_movement_delta_tolerance);
    readField(file, entry.m_min_glide_distance_tolerance);
    readField(file, entry.m_look_forward_offset);
    readField(file, entry.m_look_up_offset);
    readField(file, entry.m_minimum_vertical_dampening_distance);
    readField(file, entry.m_maximum_vertical_dampening_distance);
    readField(file, entry.m_minimum_ignore_jump_distance);
    readField(file, entry.m_maximum_ignore_jump_distance);
    readField(file, entry.m_maximum_auto_glide_angle);
    readField(file, entry.m_minimum_tether_glide_distance);
    readField(file, entry.m_yaw_sign_correction);
    readField(file, entry.m_set_1_look_forward_offset);
    readField(file, entry.m_set_1_look_up_offset);
    readField(file, entry.m_set_2_look_forward_offset);
    readField(file, entry.m_set_2_look_up_offset);
    readField(file, entry.m_set_0_speed_influence_on_dir);
    readField(file, entry.m_set_1_speed_influence_on_dir);
    readField(file, entry.m_set_2_speed_influence_on_dir);
    readField(file, entry.m_set_0_angular_relaxation);
    readField(file, entry.m_set_1_angular_relaxation);
    readField(file, entry.m_set_2_angular_relaxation);
    readField(file, entry.m_set_0_position_up_offset);
    readField(file, entry.m_set_1_position_up_offset);
    readField(file, entry.m_set_2_position_up_offset);
    readField(file, entry.m_set_0_position_forward_offset);
    readField(file, entry.m_set_1_position_forward_offset);
    readField(file, entry.m_set_2_position_forward_offset);
    readField(file, entry.m_set_0_FOV);
    readField(file, entry.m_set_1_FOV);
    readField(file, entry.m_set_2_FOV);
    readField(file, entry.m_set_0_max_yaw_angle);
    readField(file, entry.m_set_1_max_yaw_angle);
    readField(file, entry.m_set_2_max_yaw_angle);
    readField(file, entry.m_set_1_fade_in_camera_set_change);
    readField(file, entry.m_set_1_fade_out_camera_set_change);
    readField(file, entry.m_set_2_fade_in_camera_set_change);
    readField(file, entry.m_set_2_fade_out_camera_set_change);
    readField(file, entry.m_input_movement_scalar);
    readField(file, entry.m_input_rotation_scalar);
    readField(file, entry.m_input_zoom_scalar);
    readField(file, entry.m_minimum_pitch_desired);
    readField(file, entry.m_maximum_pitch_desired);
    readField(file, entry.m_minimum_zoom);
    readField(file, entry.m_maximum_zoom);
    readField(file, entry.m_horizontal_rotate_tolerance);
    readField(file, entry.m_horizontal_rotate_modifier);
}

void readDB(CelebrationParameters& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_animation);
    readField(file, entry.m_backgroundObject);
    readField(file, entry.m_duration);
    readField(file, entry.m_subText);
    readField(file, entry.m_mainText);
    readField(file, entry.m_iconID);
    readField(file, entry.m_celeLeadIn);
    readField(file, entry.m_celeLeadOut);
    readField(file, entry.m_cameraPathLOT);
    readField(file, entry.m_pathNodeName);
    readField(file, entry.m_ambientR);
    readField(file, entry.m_ambientG);
    readField(file, entry.m_ambientB);
    readField(file, entry.m_directionalR);
    readField(file, entry.m_directionalG);
    readField(file, entry.m_directionalB);
    readField(file, entry.m_specularR);
    readField(file, entry.m_specularG);
    readField(file, entry.m_specularB);
    readField(file, entry.m_lightPositionX);
    readField(file, entry.m_lightPositionY);
    readField(file, entry.m_lightPositionZ);
    readField(file, entry.m_blendTime);
    readField(file, entry.m_fogColorR);
    readField(file, entry.m_fogColorG);
    readField(file, entry.m_fogColorB);
    readField(file, entry.m_musicCue);
    readField(file, entry.m_soundGUID);
    readField(file, entry.m_mixerProgram);
}

void readDB(ChoiceBuildComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_selections);
    readField(file, entry.m_imaginationOverride);
}

void readDB(CollectibleComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_requirement_mission);
}

void readDB(ComponentsRegistry& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_component_type);
    readField(file, entry.m_component_id);
}

void readDB(ControlSchemes& entry, std::istream& file)
{
    readField(file, entry.m_control_scheme);
    readField(file, entry.m_scheme_name);
    readField(file, entry.m_rotation_speed);
    readField(file, entry.m_walk_forward_speed);
    readField(file, entry.m_walk_backward_speed);
    readField(file, entry.m_walk_strafe_speed);
    readField(file, entry.m_walk_strafe_forward_speed);
    readField(file, entry.m_walk_strafe_backward_speed);
    readField(file, entry.m_run_backward_speed);
    readField(file, entry.m_run_strafe_speed);
    readField(file, entry.m_run_strafe_forward_speed);
    readField(file, entry.m_run_strafe_backward_speed);
    readField(file, entry.m_keyboard_zoom_sensitivity);
    readField(file, entry.m_keyboard_pitch_sensitivity);
    readField(file, entry.m_keyboard_yaw_sensitivity);
    readField(file, entry.m_mouse_zoom_wheel_sensitivity);
    readField(file, entry.m_x_mouse_move_sensitivity_modifier);
    readField(file, entry.m_y_mouse_move_sensitivity_modifier);
    readField(file, entry.m_freecam_speed_modifier);
    readField(file, entry.m_freecam_slow_speed_multiplier);
    readField(file, entry.m_freecam_fast_speed_multiplier);
    readField(file, entry.m_freecam_mouse_modifier);
    readField(file, entry.m_gamepad_pitch_rot_sensitivity);
    readField(file, entry.m_gamepad_yaw_rot_sensitivity);
    readField(file, entry.m_gamepad_trigger_sensitivity);
}

void readDB(CurrencyDenominations& entry, std::istream& file)
{
    readField(file, entry.m_value);
    readField(file, entry.m_objectid);
}

void readDB(CurrencyTable& entry, std::istream& file)
{
    readField(file, entry.m_currencyIndex);
    readField(file, entry.m_npcminlevel);
    readField(file, entry.m_minvalue);
    readField(file, entry.m_maxvalue);
    readField(file, entry.m_id);
}

void readDB(DBExclude& entry, std::istream& file)
{
    readField(file, entry.m_table);
    readField(file, entry.m_column);
}

void readDB(DeletionRestrictions& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_restricted);
    readField(file, entry.m_ids);
    readField(file, entry.m_checkType);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(DestructibleComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_faction);
    readField(file, entry.m_factionList);
    readField(file, entry.m_life);
    readField(file, entry.m_imagination);
    readField(file, entry.m_LootMatrixIndex);
    readField(file, entry.m_CurrencyIndex);
    readField(file, entry.m_level);
    readField(file, entry.m_armor);
    readField(file, entry.m_death_behavior);
    readField(file, entry.m_isnpc);
    readField(file, entry.m_attack_priority);
    readField(file, entry.m_isSmashable);
    readField(file, entry.m_difficultyLevel);
}

void readDB(DevModelBehaviors& entry, std::istream& file)
{
    readField(file, entry.m_ModelID);
    readField(file, entry.m_BehaviorID);
}

void readDB(Emotes& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_animationName);
    readField(file, entry.m_iconFilename);
    readField(file, entry.m_channel);
    readField(file, entry.m_command);
    readField(file, entry.m_locked);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(EventGating& entry, std::istream& file)
{
    readField(file, entry.m_eventName);
    readField(file, entry.m_date_start);
    readField(file, entry.m_date_end);
}

void readDB(ExhibitComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_length);
    readField(file, entry.m_width);
    readField(file, entry.m_height);
    readField(file, entry.m_offsetX);
    readField(file, entry.m_offsetY);
    readField(file, entry.m_offsetZ);
    readField(file, entry.m_fReputationSizeMultiplier);
    readField(file, entry.m_fImaginationCost);
}

void readDB(Factions& entry, std::istream& file)
{
    readField(file, entry.m_faction);
    readField(file, entry.m_factionList);
    readField(file, entry.m_factionListFriendly);
    readField(file, entry.m_friendList);
    readField(file, entry.m_enemyList);
}

void readDB(FeatureGating& entry, std::istream& file)
{
    readField(file, entry.m_featureName);
    readField(file, entry.m_major);
    readField(file, entry.m_current);
    readField(file, entry.m_minor);
    readField(file, entry.m_description);
}

void readDB(FlairTable& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_asset);
}

void readDB(Icons& entry, std::istream& file)
{
    readField(file, entry.m_IconID);
    readField(file, entry.m_IconPath);
    readField(file, entry.m_IconName);
}

void readDB(InventoryComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_itemid);
    readField(file, entry.m_count);
    readField(file, entry.m_equip);
}

void readDB(ItemComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_equipLocation);
    readField(file, entry.m_baseValue);
    readField(file, entry.m_isKitPiece);
    readField(file, entry.m_rarity);
    readField(file, entry.m_itemType);
    readField(file, entry.m_itemInfo);
    readField(file, entry.m_inLootTable);
    readField(file, entry.m_inVendor);
    readField(file, entry.m_isUnique);
    readField(file, entry.m_isBOP);
    readField(file, entry.m_isBOE);
    readField(file, entry.m_reqFlagID);
    readField(file, entry.m_reqSpecialtyID);
    readField(file, entry.m_reqSpecRank);
    readField(file, entry.m_reqAchievementID);
    readField(file, entry.m_stackSize);
    readField(file, entry.m_color1);
    readField(file, entry.m_decal);
    readField(file, entry.m_offsetGroupID);
    readField(file, entry.m_buildTypes);
    readField(file, entry.m_reqPrecondition);
    readField(file, entry.m_animationFlag);
    readField(file, entry.m_equipEffects);
    readField(file, entry.m_readyForQA);
    readField(file, entry.m_itemRating);
    readField(file, entry.m_isTwoHanded);
    readField(file, entry.m_minNumRequired);
    readField(file, entry.m_delResIndex);
    readField(file, entry.m_currencyLOT);
    readField(file, entry.m_altCurrencyCost);
    readField(file, entry.m_subItems);
    readField(file, entry.m_audioEventUse);
    readField(file, entry.m_noEquipAnimation);
    readField(file, entry.m_commendationLOT);
    readField(file, entry.m_commendationCost);
    readField(file, entry.m_audioEquipMetaEventSet);
    readField(file, entry.m_currencyCosts);
    readField(file, entry.m_ingredientInfo);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_forgeType);
    readField(file, entry.m_SellMultiplier);
}

void readDB(ItemEggData& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_chassie_type_id);
}

void readDB(ItemFoodData& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_element_1);
    readField(file, entry.m_element_1_amount);
    readField(file, entry.m_element_2);
    readField(file, entry.m_element_2_amount);
    readField(file, entry.m_element_3);
    readField(file, entry.m_element_3_amount);
    readField(file, entry.m_element_4);
    readField(file, entry.m_element_4_amount);
}

void readDB(ItemSetSkills& entry, std::istream& file)
{
    readField(file, entry.m_SkillSetID);
    readField(file, entry.m_SkillID);
    readField(file, entry.m_SkillCastType);
}

void readDB(ItemSets& entry, std::istream& file)
{
    readField(file, entry.m_setID);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_itemIDs);
    readField(file, entry.m_kitType);
    readField(file, entry.m_kitRank);
    readField(file, entry.m_kitImage);
    readField(file, entry.m_skillSetWith2);
    readField(file, entry.m_skillSetWith3);
    readField(file, entry.m_skillSetWith4);
    readField(file, entry.m_skillSetWith5);
    readField(file, entry.m_skillSetWith6);
    readField(file, entry.m_localize);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_kitID);
    readField(file, entry.m_priority);
}

void readDB(JetPackPadComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_xDistance);
    readField(file, entry.m_yDistance);
    readField(file, entry.m_warnDistance);
    readField(file, entry.m_lotBlocker);
    readField(file, entry.m_lotWarningVolume);
}

void readDB(LUPExhibitComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_minXZ);
    readField(file, entry.m_maxXZ);
    readField(file, entry.m_maxY);
    readField(file, entry.m_offsetX);
    readField(file, entry.m_offsetY);
    readField(file, entry.m_offsetZ);
}

void readDB(LUPExhibitModelData& entry, std::istream& file)
{
    readField(file, entry.m_LOT);
    readField(file, entry.m_minXZ);
    readField(file, entry.m_maxXZ);
    readField(file, entry.m_maxY);
    readField(file, entry.m_description);
    readField(file, entry.m_owner);
}

void readDB(LUPZoneIDs& entry, std::istream& file)
{
    readField(file, entry.m_zoneID);
}

void readDB(LanguageType& entry, std::istream& file)
{
    readField(file, entry.m_LanguageID);
    readField(file, entry.m_LanguageDescription);
}

void readDB(LevelProgressionLookup& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_requiredUScore);
    readField(file, entry.m_BehaviorEffect);
}

void readDB(LootMatrix& entry, std::istream& file)
{
    readField(file, entry.m_LootMatrixIndex);
    readField(file, entry.m_LootTableIndex);
    readField(file, entry.m_RarityTableIndex);
    readField(file, entry.m_percent);
    readField(file, entry.m_minToDrop);
    readField(file, entry.m_maxToDrop);
    readField(file, entry.m_id);
    readField(file, entry.m_flagID);
    readField(file, entry.m_gate_version);
}

void readDB(LootMatrixIndex& entry, std::istream& file)
{
    readField(file, entry.m_LootMatrixIndex);
    readField(file, entry.m_inNpcEditor);
}

void readDB(LootTable& entry, std::istream& file)
{
    readField(file, entry.m_itemid);
    readField(file, entry.m_LootTableIndex);
    readField(file, entry.m_id);
    readField(file, entry.m_MissionDrop);
    readField(file, entry.m_sortPriority);
}

void readDB(LootTableIndex& entry, std::istream& file)
{
    readField(file, entry.m_LootTableIndex);
}

void readDB(MinifigComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_head);
    readField(file, entry.m_chest);
    readField(file, entry.m_legs);
    readField(file, entry.m_hairstyle);
    readField(file, entry.m_haircolor);
    readField(file, entry.m_chestdecal);
    readField(file, entry.m_headcolor);
    readField(file, entry.m_lefthand);
    readField(file, entry.m_righthand);
    readField(file, entry.m_eyebrowstyle);
    readField(file, entry.m_eyesstyle);
    readField(file, entry.m_mouthstyle);
}

void readDB(MinifigDecals_Eyebrows& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_High_path);
    readField(file, entry.m_Low_path);
    readField(file, entry.m_CharacterCreateValid);
    readField(file, entry.m_male);
    readField(file, entry.m_female);
}

void readDB(MinifigDecals_Eyes& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_High_path);
    readField(file, entry.m_Low_path);
    readField(file, entry.m_CharacterCreateValid);
    readField(file, entry.m_male);
    readField(file, entry.m_female);
}

void readDB(MinifigDecals_Legs& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_High_path);
}

void readDB(MinifigDecals_Mouths& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_High_path);
    readField(file, entry.m_Low_path);
    readField(file, entry.m_CharacterCreateValid);
    readField(file, entry.m_male);
    readField(file, entry.m_female);
}

void readDB(MinifigDecals_Torsos& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_High_path);
    readField(file, entry.m_CharacterCreateValid);
    readField(file, entry.m_male);
    readField(file, entry.m_female);
}

void readDB(MissionEmail& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_messageType);
    readField(file, entry.m_notificationGroup);
    readField(file, entry.m_missionID);
    readField(file, entry.m_attachmentLOT);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(MissionNPCComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_missionID);
    readField(file, entry.m_offersMission);
    readField(file, entry.m_acceptsMission);
    readField(file, entry.m_gate_version);
}

void readDB(MissionTasks& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_taskType);
    readField(file, entry.m_target);
    readField(file, entry.m_targetGroup);
    readField(file, entry.m_targetValue);
    readField(file, entry.m_taskParam1);
    readField(file, entry.m_largeTaskIcon);
    readField(file, entry.m_IconID);
    readField(file, entry.m_uid);
    readField(file, entry.m_largeTaskIconID);
    readField(file, entry.m_localize);
    readField(file, entry.m_gate_version);
}

void readDB(MissionText& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_story_icon);
    readField(file, entry.m_missionIcon);
    readField(file, entry.m_offerNPCIcon);
    readField(file, entry.m_IconID);
    readField(file, entry.m_state_1_anim);
    readField(file, entry.m_state_2_anim);
    readField(file, entry.m_state_3_anim);
    readField(file, entry.m_state_4_anim);
    readField(file, entry.m_state_3_turnin_anim);
    readField(file, entry.m_state_4_turnin_anim);
    readField(file, entry.m_onclick_anim);
    readField(file, entry.m_CinematicAccepted);
    readField(file, entry.m_CinematicAcceptedLeadin);
    readField(file, entry.m_CinematicCompleted);
    readField(file, entry.m_CinematicCompletedLeadin);
    readField(file, entry.m_CinematicRepeatable);
    readField(file, entry.m_CinematicRepeatableLeadin);
    readField(file, entry.m_CinematicRepeatableCompleted);
    readField(file, entry.m_CinematicRepeatableCompletedLeadin);
    readField(file, entry.m_AudioEventGUID_Interact);
    readField(file, entry.m_AudioEventGUID_OfferAccept);
    readField(file, entry.m_AudioEventGUID_OfferDeny);
    readField(file, entry.m_AudioEventGUID_Completed);
    readField(file, entry.m_AudioEventGUID_TurnIn);
    readField(file, entry.m_AudioEventGUID_Failed);
    readField(file, entry.m_AudioEventGUID_Progress);
    readField(file, entry.m_AudioMusicCue_OfferAccept);
    readField(file, entry.m_AudioMusicCue_TurnIn);
    readField(file, entry.m_turnInIconID);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(Missions& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_defined_type);
    readField(file, entry.m_defined_subtype);
    readField(file, entry.m_UISortOrder);
    readField(file, entry.m_offer_objectID);
    readField(file, entry.m_target_objectID);
    readField(file, entry.m_reward_currency);
    readField(file, entry.m_LegoScore);
    readField(file, entry.m_reward_reputation);
    readField(file, entry.m_isChoiceReward);
    readField(file, entry.m_reward_item1);
    readField(file, entry.m_reward_item1_count);
    readField(file, entry.m_reward_item2);
    readField(file, entry.m_reward_item2_count);
    readField(file, entry.m_reward_item3);
    readField(file, entry.m_reward_item3_count);
    readField(file, entry.m_reward_item4);
    readField(file, entry.m_reward_item4_count);
    readField(file, entry.m_reward_emote);
    readField(file, entry.m_reward_emote2);
    readField(file, entry.m_reward_emote3);
    readField(file, entry.m_reward_emote4);
    readField(file, entry.m_reward_maximagination);
    readField(file, entry.m_reward_maxhealth);
    readField(file, entry.m_reward_maxinventory);
    readField(file, entry.m_reward_maxmodel);
    readField(file, entry.m_reward_maxwidget);
    readField(file, entry.m_reward_maxwallet);
    readField(file, entry.m_repeatable);
    readField(file, entry.m_reward_currency_repeatable);
    readField(file, entry.m_reward_item1_repeatable);
    readField(file, entry.m_reward_item1_repeat_count);
    readField(file, entry.m_reward_item2_repeatable);
    readField(file, entry.m_reward_item2_repeat_count);
    readField(file, entry.m_reward_item3_repeatable);
    readField(file, entry.m_reward_item3_repeat_count);
    readField(file, entry.m_reward_item4_repeatable);
    readField(file, entry.m_reward_item4_repeat_count);
    readField(file, entry.m_time_limit);
    readField(file, entry.m_isMission);
    readField(file, entry.m_missionIconID);
    readField(file, entry.m_prereqMissionID);
    readField(file, entry.m_localize);
    readField(file, entry.m_inMOTD);
    readField(file, entry.m_cooldownTime);
    readField(file, entry.m_isRandom);
    readField(file, entry.m_randomPool);
    readField(file, entry.m_UIPrereqID);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_HUDStates);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_reward_bankinventory);
}

void readDB(ModelBehavior& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_definitionXMLfilename);
}

void readDB(ModularBuildComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_buildType);
    readField(file, entry.m_xml);
    readField(file, entry.m_createdLOT);
    readField(file, entry.m_createdPhysicsID);
    readField(file, entry.m_AudioEventGUID_Snap);
    readField(file, entry.m_AudioEventGUID_Complete);
    readField(file, entry.m_AudioEventGUID_Present);
}

void readDB(ModuleComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_partCode);
    readField(file, entry.m_buildType);
    readField(file, entry.m_xml);
    readField(file, entry.m_primarySoundGUID);
    readField(file, entry.m_assembledEffectID);
}

void readDB(MotionFX& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_typeID);
    readField(file, entry.m_slamVelocity);
    readField(file, entry.m_addVelocity);
    readField(file, entry.m_duration);
    readField(file, entry.m_destGroupName);
    readField(file, entry.m_startScale);
    readField(file, entry.m_endScale);
    readField(file, entry.m_velocity);
    readField(file, entry.m_distance);
}

void readDB(MovementAIComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_MovementType);
    readField(file, entry.m_WanderChance);
    readField(file, entry.m_WanderDelayMin);
    readField(file, entry.m_WanderDelayMax);
    readField(file, entry.m_WanderSpeed);
    readField(file, entry.m_WanderRadius);
    readField(file, entry.m_attachedPath);
}

void readDB(MovingPlatforms& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_platformIsSimpleMover);
    readField(file, entry.m_platformMoveX);
    readField(file, entry.m_platformMoveY);
    readField(file, entry.m_platformMoveZ);
    readField(file, entry.m_platformMoveTime);
    readField(file, entry.m_platformStartAtEnd);
    readField(file, entry.m_description);
}

void readDB(NpcIcons& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_color);
    readField(file, entry.m_offset);
    readField(file, entry.m_LOT);
    readField(file, entry.m_Texture);
    readField(file, entry.m_isClickable);
    readField(file, entry.m_scale);
    readField(file, entry.m_rotateToFace);
    readField(file, entry.m_compositeHorizOffset);
    readField(file, entry.m_compositeVertOffset);
    readField(file, entry.m_compositeScale);
    readField(file, entry.m_compositeConnectionNode);
    readField(file, entry.m_compositeLOTMultiMission);
    readField(file, entry.m_compositeLOTMultiMissionVentor);
    readField(file, entry.m_compositeIconTexture);
}

void readDB(ObjectBehaviorXREF& entry, std::istream& file)
{
    readField(file, entry.m_LOT);
    readField(file, entry.m_behaviorID1);
    readField(file, entry.m_behaviorID2);
    readField(file, entry.m_behaviorID3);
    readField(file, entry.m_behaviorID4);
    readField(file, entry.m_behaviorID5);
    readField(file, entry.m_type);
}

void readDB(ObjectBehaviors& entry, std::istream& file)
{
    readField(file, entry.m_BehaviorID);
    readField(file, entry.m_xmldata);
}

void readDB(ObjectSkills& entry, std::istream& file)
{
    readField(file, entry.m_objectTemplate);
    readField(file, entry.m_skillID);
    readField(file, entry.m_castOnType);
    readField(file, entry.m_AICombatWeight);
}

void readDB(Objects& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_name);
    readField(file, entry.m_placeable);
    readField(file, entry.m_type);
    readField(file, entry.m_description);
    readField(file, entry.m_localize);
    readField(file, entry.m_npcTemplateID);
    readField(file, entry.m_displayName);
    readField(file, entry.m_interactionDistance);
    readField(file, entry.m_nametag);
    readField(file, entry.m__internalNotes);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_HQ_valid);
}

void readDB(PackageComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_LootMatrixIndex);
    readField(file, entry.m_packageType);
}

void readDB(PetAbilities& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_AbilityName);
    readField(file, entry.m_ImaginationCost);
    readField(file, entry.m_locStatus);
}

void readDB(PetComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_minTameUpdateTime);
    readField(file, entry.m_maxTameUpdateTime);
    readField(file, entry.m_percentTameChance);
    readField(file, entry.m_tamability);
    readField(file, entry.m_elementType);
    readField(file, entry.m_walkSpeed);
    readField(file, entry.m_runSpeed);
    readField(file, entry.m_sprintSpeed);
    readField(file, entry.m_idleTimeMin);
    readField(file, entry.m_idleTimeMax);
    readField(file, entry.m_petForm);
    readField(file, entry.m_imaginationDrainRate);
    readField(file, entry.m_AudioMetaEventSet);
    readField(file, entry.m_buffIDs);
}

void readDB(PetNestComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_ElementalType);
}

void readDB(PhysicsComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_static);
    readField(file, entry.m_physics_asset);
    readField(file, entry.m_jump);
    readField(file, entry.m_doublejump);
    readField(file, entry.m_speed);
    readField(file, entry.m_rotSpeed);
    readField(file, entry.m_playerHeight);
    readField(file, entry.m_playerRadius);
    readField(file, entry.m_pcShapeType);
    readField(file, entry.m_collisionGroup);
    readField(file, entry.m_airSpeed);
    readField(file, entry.m_boundaryAsset);
    readField(file, entry.m_jumpAirSpeed);
    readField(file, entry.m_friction);
    readField(file, entry.m_gravityVolumeAsset);
}

void readDB(PlayerFlags& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_SessionOnly);
    readField(file, entry.m_OnlySetByServer);
    readField(file, entry.m_SessionZoneOnly);
}

void readDB(PlayerStatistics& entry, std::istream& file)
{
    readField(file, entry.m_statID);
    readField(file, entry.m_sortOrder);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(PossessableComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_controlSchemeID);
    readField(file, entry.m_minifigAttachPoint);
    readField(file, entry.m_minifigAttachAnimation);
    readField(file, entry.m_minifigDetachAnimation);
    readField(file, entry.m_mountAttachAnimation);
    readField(file, entry.m_mountDetachAnimation);
    readField(file, entry.m_attachOffsetFwd);
    readField(file, entry.m_attachOffsetRight);
    readField(file, entry.m_possessionType);
    readField(file, entry.m_wantBillboard);
    readField(file, entry.m_billboardOffsetUp);
    readField(file, entry.m_depossessOnHit);
    readField(file, entry.m_hitStunTime);
    readField(file, entry.m_skillSet);
}

void readDB(Preconditions& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_type);
    readField(file, entry.m_targetLOT);
    readField(file, entry.m_targetGroup);
    readField(file, entry.m_targetCount);
    readField(file, entry.m_iconID);
    readField(file, entry.m_localize);
    readField(file, entry.m_validContexts);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(PropertyEntranceComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_mapID);
    readField(file, entry.m_propertyName);
    readField(file, entry.m_isOnProperty);
    readField(file, entry.m_groupType);
}

void readDB(PropertyTemplate& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_mapID);
    readField(file, entry.m_vendorMapID);
    readField(file, entry.m_spawnName);
    readField(file, entry.m_type);
    readField(file, entry.m_sizecode);
    readField(file, entry.m_minimumPrice);
    readField(file, entry.m_rentDuration);
    readField(file, entry.m_path);
    readField(file, entry.m_cloneLimit);
    readField(file, entry.m_durationType);
    readField(file, entry.m_achievementRequired);
    readField(file, entry.m_zoneX);
    readField(file, entry.m_zoneY);
    readField(file, entry.m_zoneZ);
    readField(file, entry.m_maxBuildHeight);
    readField(file, entry.m_localize);
    readField(file, entry.m_reputationPerMinute);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(ProximityMonitorComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_Proximities);
    readField(file, entry.m_LoadOnClient);
    readField(file, entry.m_LoadOnServer);
}

void readDB(ProximityTypes& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_Name);
    readField(file, entry.m_Radius);
    readField(file, entry.m_CollisionGroup);
    readField(file, entry.m_PassiveChecks);
    readField(file, entry.m_IconID);
    readField(file, entry.m_LoadOnClient);
    readField(file, entry.m_LoadOnServer);
}

void readDB(RacingModuleComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_topSpeed);
    readField(file, entry.m_acceleration);
    readField(file, entry.m_handling);
    readField(file, entry.m_stability);
    readField(file, entry.m_imagination);
}

void readDB(RailActivatorComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_startAnim);
    readField(file, entry.m_loopAnim);
    readField(file, entry.m_stopAnim);
    readField(file, entry.m_startSound);
    readField(file, entry.m_loopSound);
    readField(file, entry.m_stopSound);
    readField(file, entry.m_effectIDs);
    readField(file, entry.m_preconditions);
    readField(file, entry.m_playerCollision);
    readField(file, entry.m_cameraLocked);
    readField(file, entry.m_StartEffectID);
    readField(file, entry.m_StopEffectID);
    readField(file, entry.m_DamageImmune);
    readField(file, entry.m_NoAggro);
    readField(file, entry.m_ShowNameBillboard);
}

void readDB(RarityTable& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_randmax);
    readField(file, entry.m_rarity);
    readField(file, entry.m_RarityTableIndex);
}

void readDB(RarityTableIndex& entry, std::istream& file)
{
    readField(file, entry.m_RarityTableIndex);
}

void readDB(RebuildComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_reset_time);
    readField(file, entry.m_complete_time);
    readField(file, entry.m_take_imagination);
    readField(file, entry.m_interruptible);
    readField(file, entry.m_self_activator);
    readField(file, entry.m_custom_modules);
    readField(file, entry.m_activityID);
    readField(file, entry.m_post_imagination_cost);
    readField(file, entry.m_time_before_smash);
}

void readDB(RebuildSections& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_rebuildID);
    readField(file, entry.m_objectID);
    readField(file, entry.m_offset_x);
    readField(file, entry.m_offset_y);
    readField(file, entry.m_offset_z);
    readField(file, entry.m_fall_angle_x);
    readField(file, entry.m_fall_angle_y);
    readField(file, entry.m_fall_angle_z);
    readField(file, entry.m_fall_height);
    readField(file, entry.m_requires_list);
    readField(file, entry.m_size);
    readField(file, entry.m_bPlaced);
}

void readDB(Release_Version& entry, std::istream& file)
{
    readField(file, entry.m_ReleaseVersion);
    readField(file, entry.m_ReleaseDate);
}

void readDB(RenderComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_render_asset);
    readField(file, entry.m_icon_asset);
    readField(file, entry.m_IconID);
    readField(file, entry.m_shader_id);
    readField(file, entry.m_effect1);
    readField(file, entry.m_effect2);
    readField(file, entry.m_effect3);
    readField(file, entry.m_effect4);
    readField(file, entry.m_effect5);
    readField(file, entry.m_effect6);
    readField(file, entry.m_animationGroupIDs);
    readField(file, entry.m_fade);
    readField(file, entry.m_usedropshadow);
    readField(file, entry.m_preloadAnimations);
    readField(file, entry.m_fadeInTime);
    readField(file, entry.m_maxShadowDistance);
    readField(file, entry.m_ignoreCameraCollision);
    readField(file, entry.m_renderComponentLOD1);
    readField(file, entry.m_renderComponentLOD2);
    readField(file, entry.m_gradualSnap);
    readField(file, entry.m_animationFlag);
    readField(file, entry.m_AudioMetaEventSet);
    readField(file, entry.m_billboardHeight);
    readField(file, entry.m_chatBubbleOffset);
    readField(file, entry.m_staticBillboard);
    readField(file, entry.m_LXFMLFolder);
    readField(file, entry.m_attachIndicatorsToNode);
}

void readDB(RenderComponentFlash& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_interactive);
    readField(file, entry.m_animated);
    readField(file, entry.m_nodeName);
    readField(file, entry.m_flashPath);
    readField(file, entry.m_elementName);
    readField(file, entry.m__uid);
}

void readDB(RenderComponentWrapper& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_defaultWrapperAsset);
}

void readDB(RenderIconAssets& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_icon_asset);
    readField(file, entry.m_blank_column);
}

void readDB(ReputationRewards& entry, std::istream& file)
{
    readField(file, entry.m_repLevel);
    readField(file, entry.m_sublevel);
    readField(file, entry.m_reputation);
}

void readDB(RewardCodes& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_code);
    readField(file, entry.m_attachmentLOT);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(Rewards& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_LevelID);
    readField(file, entry.m_MissionID);
    readField(file, entry.m_RewardType);
    readField(file, entry.m_value);
    readField(file, entry.m_count);
}

void readDB(RocketLaunchpadControlComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_targetZone);
    readField(file, entry.m_defaultZoneID);
    readField(file, entry.m_targetScene);
    readField(file, entry.m_gmLevel);
    readField(file, entry.m_playerAnimation);
    readField(file, entry.m_rocketAnimation);
    readField(file, entry.m_launchMusic);
    readField(file, entry.m_useLaunchPrecondition);
    readField(file, entry.m_useAltLandingPrecondition);
    readField(file, entry.m_launchPrecondition);
    readField(file, entry.m_altLandingPrecondition);
    readField(file, entry.m_altLandingSpawnPointName);
}

void readDB(SceneTable& entry, std::istream& file)
{
    readField(file, entry.m_sceneID);
    readField(file, entry.m_sceneName);
}

void readDB(ScriptComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_script_name);
    readField(file, entry.m_client_script_name);
}

void readDB(SkillBehavior& entry, std::istream& file)
{
    readField(file, entry.m_skillID);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_behaviorID);
    readField(file, entry.m_imaginationcost);
    readField(file, entry.m_cooldowngroup);
    readField(file, entry.m_cooldown);
    readField(file, entry.m_inNpcEditor);
    readField(file, entry.m_skillIcon);
    readField(file, entry.m_oomSkillID);
    readField(file, entry.m_oomBehaviorEffectID);
    readField(file, entry.m_castTypeDesc);
    readField(file, entry.m_imBonusUI);
    readField(file, entry.m_lifeBonusUI);
    readField(file, entry.m_armorBonusUI);
    readField(file, entry.m_damageUI);
    readField(file, entry.m_hideIcon);
    readField(file, entry.m_localize);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_cancelType);
}

void readDB(SmashableChain& entry, std::istream& file)
{
    readField(file, entry.m_chainIndex);
    readField(file, entry.m_chainLevel);
    readField(file, entry.m_lootMatrixID);
    readField(file, entry.m_rarityTableIndex);
    readField(file, entry.m_currencyIndex);
    readField(file, entry.m_currencyLevel);
    readField(file, entry.m_smashCount);
    readField(file, entry.m_timeLimit);
    readField(file, entry.m_chainStepID);
}

void readDB(SmashableChainIndex& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_targetGroup);
    readField(file, entry.m_description);
    readField(file, entry.m_continuous);
}

void readDB(SmashableComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_LootMatrixIndex);
}

void readDB(SmashableElements& entry, std::istream& file)
{
    readField(file, entry.m_elementID);
    readField(file, entry.m_dropWeight);
}

void readDB(SpeedchatMenu& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_parentId);
    readField(file, entry.m_emoteId);
    readField(file, entry.m_imageName);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(SubscriptionPricing& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_countryCode);
    readField(file, entry.m_monthlyFeeGold);
    readField(file, entry.m_monthlyFeeSilver);
    readField(file, entry.m_monthlyFeeBronze);
    readField(file, entry.m_monetarySymbol);
    readField(file, entry.m_symbolIsAppended);
}

void readDB(SurfaceType& entry, std::istream& file)
{
    readField(file, entry.m_SurfaceType);
    readField(file, entry.m_FootstepNDAudioMetaEventSetName);
}

void readDB(TamingBuildPuzzles& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_PuzzleModelLot);
    readField(file, entry.m_NPCLot);
    readField(file, entry.m_ValidPiecesLXF);
    readField(file, entry.m_InvalidPiecesLXF);
    readField(file, entry.m_Difficulty);
    readField(file, entry.m_Timelimit);
    readField(file, entry.m_NumValidPieces);
    readField(file, entry.m_TotalNumPieces);
    readField(file, entry.m_ModelName);
    readField(file, entry.m_FullModelLXF);
    readField(file, entry.m_Duration);
    readField(file, entry.m_imagCostPerBuild);
}

void readDB(TextDescription& entry, std::istream& file)
{
    readField(file, entry.m_TextID);
    readField(file, entry.m_TestDescription);
}

void readDB(TextLanguage& entry, std::istream& file)
{
    readField(file, entry.m_TextID);
    readField(file, entry.m_LanguageID);
    readField(file, entry.m_Text);
}

void readDB(TrailEffects& entry, std::istream& file)
{
    readField(file, entry.m_trailID);
    readField(file, entry.m_textureName);
    readField(file, entry.m_blendmode);
    readField(file, entry.m_cardlifetime);
    readField(file, entry.m_colorlifetime);
    readField(file, entry.m_minTailFade);
    readField(file, entry.m_tailFade);
    readField(file, entry.m_max_particles);
    readField(file, entry.m_birthDelay);
    readField(file, entry.m_deathDelay);
    readField(file, entry.m_bone1);
    readField(file, entry.m_bone2);
    readField(file, entry.m_texLength);
    readField(file, entry.m_texWidth);
    readField(file, entry.m_startColorR);
    readField(file, entry.m_startColorG);
    readField(file, entry.m_startColorB);
    readField(file, entry.m_startColorA);
    readField(file, entry.m_middleColorR);
    readField(file, entry.m_middleColorG);
    readField(file, entry.m_middleColorB);
    readField(file, entry.m_middleColorA);
    readField(file, entry.m_endColorR);
    readField(file, entry.m_endColorG);
    readField(file, entry.m_endColorB);
    readField(file, entry.m_endColorA);
}

void readDB(UGBehaviorSounds& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_guid);
    readField(file, entry.m_localize);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_gate_version);
}

void readDB(VehiclePhysics& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_hkxFilename);
    readField(file, entry.m_fGravityScale);
    readField(file, entry.m_fMass);
    readField(file, entry.m_fChassisFriction);
    readField(file, entry.m_fMaxSpeed);
    readField(file, entry.m_fEngineTorque);
    readField(file, entry.m_fBrakeFrontTorque);
    readField(file, entry.m_fBrakeRearTorque);
    readField(file, entry.m_fBrakeMinInputToBlock);
    readField(file, entry.m_fBrakeMinTimeToBlock);
    readField(file, entry.m_fSteeringMaxAngle);
    readField(file, entry.m_fSteeringSpeedLimitForMaxAngle);
    readField(file, entry.m_fSteeringMinAngle);
    readField(file, entry.m_fFwdBias);
    readField(file, entry.m_fFrontTireFriction);
    readField(file, entry.m_fRearTireFriction);
    readField(file, entry.m_fFrontTireFrictionSlide);
    readField(file, entry.m_fRearTireFrictionSlide);
    readField(file, entry.m_fFrontTireSlipAngle);
    readField(file, entry.m_fRearTireSlipAngle);
    readField(file, entry.m_fWheelWidth);
    readField(file, entry.m_fWheelRadius);
    readField(file, entry.m_fWheelMass);
    readField(file, entry.m_fReorientPitchStrength);
    readField(file, entry.m_fReorientRollStrength);
    readField(file, entry.m_fSuspensionLength);
    readField(file, entry.m_fSuspensionStrength);
    readField(file, entry.m_fSuspensionDampingCompression);
    readField(file, entry.m_fSuspensionDampingRelaxation);
    readField(file, entry.m_iChassisCollisionGroup);
    readField(file, entry.m_fNormalSpinDamping);
    readField(file, entry.m_fCollisionSpinDamping);
    readField(file, entry.m_fCollisionThreshold);
    readField(file, entry.m_fTorqueRollFactor);
    readField(file, entry.m_fTorquePitchFactor);
    readField(file, entry.m_fTorqueYawFactor);
    readField(file, entry.m_fInertiaRoll);
    readField(file, entry.m_fInertiaPitch);
    readField(file, entry.m_fInertiaYaw);
    readField(file, entry.m_fExtraTorqueFactor);
    readField(file, entry.m_fCenterOfMassFwd);
    readField(file, entry.m_fCenterOfMassUp);
    readField(file, entry.m_fCenterOfMassRight);
    readField(file, entry.m_fWheelHardpointFrontFwd);
    readField(file, entry.m_fWheelHardpointFrontUp);
    readField(file, entry.m_fWheelHardpointFrontRight);
    readField(file, entry.m_fWheelHardpointRearFwd);
    readField(file, entry.m_fWheelHardpointRearUp);
    readField(file, entry.m_fWheelHardpointRearRight);
    readField(file, entry.m_fInputTurnSpeed);
    readField(file, entry.m_fInputDeadTurnBackSpeed);
    readField(file, entry.m_fInputAccelSpeed);
    readField(file, entry.m_fInputDeadAccelDownSpeed);
    readField(file, entry.m_fInputDecelSpeed);
    readField(file, entry.m_fInputDeadDecelDownSpeed);
    readField(file, entry.m_fInputSlopeChangePointX);
    readField(file, entry.m_fInputInitialSlope);
    readField(file, entry.m_fInputDeadZone);
    readField(file, entry.m_fAeroAirDensity);
    readField(file, entry.m_fAeroFrontalArea);
    readField(file, entry.m_fAeroDragCoefficient);
    readField(file, entry.m_fAeroLiftCoefficient);
    readField(file, entry.m_fAeroExtraGravity);
    readField(file, entry.m_fBoostTopSpeed);
    readField(file, entry.m_fBoostCostPerSecond);
    readField(file, entry.m_fBoostAccelerateChange);
    readField(file, entry.m_fBoostDampingChange);
    readField(file, entry.m_fPowerslideNeutralAngle);
    readField(file, entry.m_fPowerslideTorqueStrength);
    readField(file, entry.m_iPowerslideNumTorqueApplications);
    readField(file, entry.m_fImaginationTankSize);
    readField(file, entry.m_fSkillCost);
    readField(file, entry.m_fWreckSpeedBase);
    readField(file, entry.m_fWreckSpeedPercent);
    readField(file, entry.m_fWreckMinAngle);
    readField(file, entry.m_AudioEventEngine);
    readField(file, entry.m_AudioEventSkid);
    readField(file, entry.m_AudioEventLightHit);
    readField(file, entry.m_AudioSpeedThresholdLightHit);
    readField(file, entry.m_AudioTimeoutLightHit);
    readField(file, entry.m_AudioEventHeavyHit);
    readField(file, entry.m_AudioSpeedThresholdHeavyHit);
    readField(file, entry.m_AudioTimeoutHeavyHit);
    readField(file, entry.m_AudioEventStart);
    readField(file, entry.m_AudioEventTreadConcrete);
    readField(file, entry.m_AudioEventTreadSand);
    readField(file, entry.m_AudioEventTreadWood);
    readField(file, entry.m_AudioEventTreadDirt);
    readField(file, entry.m_AudioEventTreadPlastic);
    readField(file, entry.m_AudioEventTreadGrass);
    readField(file, entry.m_AudioEventTreadGravel);
    readField(file, entry.m_AudioEventTreadMud);
    readField(file, entry.m_AudioEventTreadWater);
    readField(file, entry.m_AudioEventTreadSnow);
    readField(file, entry.m_AudioEventTreadIce);
    readField(file, entry.m_AudioEventTreadMetal);
    readField(file, entry.m_AudioEventTreadLeaves);
    readField(file, entry.m_AudioEventLightLand);
    readField(file, entry.m_AudioAirtimeForLightLand);
    readField(file, entry.m_AudioEventHeavyLand);
    readField(file, entry.m_AudioAirtimeForHeavyLand);
    readField(file, entry.m_bWheelsVisible);
}

void readDB(VehicleStatMap& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_ModuleStat);
    readField(file, entry.m_HavokStat);
    readField(file, entry.m_HavokChangePerModuleStat);
}

void readDB(VendorComponent& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_buyScalar);
    readField(file, entry.m_sellScalar);
    readField(file, entry.m_refreshTimeSeconds);
    readField(file, entry.m_LootMatrixIndex);
}

void readDB(WhatsCoolItemSpotlight& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_itemID);
    readField(file, entry.m_localize);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_locStatus);
}

void readDB(WhatsCoolNewsAndTips& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_iconID);
    readField(file, entry.m_type);
    readField(file, entry.m_localize);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_locStatus);
}

void readDB(WorldConfig& entry, std::istream& file)
{
    readField(file, entry.m_WorldConfigID);
    readField(file, entry.m_pegravityvalue);
    readField(file, entry.m_pebroadphaseworldsize);
    readField(file, entry.m_pegameobjscalefactor);
    readField(file, entry.m_character_rotation_speed);
    readField(file, entry.m_character_walk_forward_speed);
    readField(file, entry.m_character_walk_backward_speed);
    readField(file, entry.m_character_walk_strafe_speed);
    readField(file, entry.m_character_walk_strafe_forward_speed);
    readField(file, entry.m_character_walk_strafe_backward_speed);
    readField(file, entry.m_character_run_backward_speed);
    readField(file, entry.m_character_run_strafe_speed);
    readField(file, entry.m_character_run_strafe_forward_speed);
    readField(file, entry.m_character_run_strafe_backward_speed);
    readField(file, entry.m_global_cooldown);
    readField(file, entry.m_characterGroundedTime);
    readField(file, entry.m_characterGroundedSpeed);
    readField(file, entry.m_globalImmunityTime);
    readField(file, entry.m_character_max_slope);
    readField(file, entry.m_defaultrespawntime);
    readField(file, entry.m_mission_tooltip_timeout);
    readField(file, entry.m_vendor_buy_multiplier);
    readField(file, entry.m_pet_follow_radius);
    readField(file, entry.m_character_eye_height);
    readField(file, entry.m_flight_vertical_velocity);
    readField(file, entry.m_flight_airspeed);
    readField(file, entry.m_flight_fuel_ratio);
    readField(file, entry.m_flight_max_airspeed);
    readField(file, entry.m_fReputationPerVote);
    readField(file, entry.m_nPropertyCloneLimit);
    readField(file, entry.m_defaultHomespaceTemplate);
    readField(file, entry.m_coins_lost_on_death_percent);
    readField(file, entry.m_coins_lost_on_death_min);
    readField(file, entry.m_coins_lost_on_death_max);
    readField(file, entry.m_character_votes_per_day);
    readField(file, entry.m_property_moderation_request_approval_cost);
    readField(file, entry.m_property_moderation_request_review_cost);
    readField(file, entry.m_propertyModRequestsAllowedSpike);
    readField(file, entry.m_propertyModRequestsAllowedInterval);
    readField(file, entry.m_propertyModRequestsAllowedTotal);
    readField(file, entry.m_propertyModRequestsSpikeDuration);
    readField(file, entry.m_propertyModRequestsIntervalDuration);
    readField(file, entry.m_modelModerateOnCreate);
    readField(file, entry.m_defaultPropertyMaxHeight);
    readField(file, entry.m_reputationPerVoteCast);
    readField(file, entry.m_reputationPerVoteReceived);
    readField(file, entry.m_showcaseTopModelConsiderationBattles);
    readField(file, entry.m_reputationPerBattlePromotion);
    readField(file, entry.m_coins_lost_on_death_min_timeout);
    readField(file, entry.m_coins_lost_on_death_max_timeout);
    readField(file, entry.m_mail_base_fee);
    readField(file, entry.m_mail_percent_attachment_fee);
    readField(file, entry.m_propertyReputationDelay);
    readField(file, entry.m_LevelCap);
    readField(file, entry.m_LevelUpBehaviorEffect);
    readField(file, entry.m_CharacterVersion);
    readField(file, entry.m_LevelCapCurrencyConversion);
}

void readDB(ZoneLoadingTips& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_zoneid);
    readField(file, entry.m_imagelocation);
    readField(file, entry.m_localize);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_weight);
    readField(file, entry.m_targetVersion);
}

void readDB(ZoneSummary& entry, std::istream& file)
{
    readField(file, entry.m_zoneID);
    readField(file, entry.m_type);
    readField(file, entry.m_value);
    readField(file, entry.m__uniqueID);
}

void readDB(ZoneTable& entry, std::istream& file)
{
    readField(file, entry.m_zoneID);
    readField(file, entry.m_locStatus);
    readField(file, entry.m_zoneName);
    readField(file, entry.m_scriptID);
    readField(file, entry.m_ghostdistance_min);
    readField(file, entry.m_ghostdistance);
    readField(file, entry.m_population_soft_cap);
    readField(file, entry.m_population_hard_cap);
    readField(file, entry.m_DisplayDescription);
    readField(file, entry.m_mapFolder);
    readField(file, entry.m_smashableMinDistance);
    readField(file, entry.m_smashableMaxDistance);
    readField(file, entry.m_mixerProgram);
    readField(file, entry.m_clientPhysicsFramerate);
    readField(file, entry.m_serverPhysicsFramerate);
    readField(file, entry.m_zoneControlTemplate);
    readField(file, entry.m_widthInChunks);
    readField(file, entry.m_heightInChunks);
    readField(file, entry.m_petsAllowed);
    readField(file, entry.m_localize);
    readField(file, entry.m_fZoneWeight);
    readField(file, entry.m_thumbnail);
    readField(file, entry.m_PlayerLoseCoinsOnDeath);
    readField(file, entry.m_disableSaveLoc);
    readField(file, entry.m_teamRadius);
    readField(file, entry.m_gate_version);
    readField(file, entry.m_mountsAllowed);
}

void readDB(brickAttributes& entry, std::istream& file)
{
    readField(file, entry.m_ID);
    readField(file, entry.m_icon_asset);
    readField(file, entry.m_display_order);
    readField(file, entry.m_locStatus);
}

void readDB(dtproperties& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_objectid);
    readField(file, entry.m_property);
    readField(file, entry.m_value);
    readField(file, entry.m_uvalue);
    readField(file, entry.m_lvalue);
    readField(file, entry.m_version);
}

void readDB(mapAnimationPriorities& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_name);
    readField(file, entry.m_priority);
}

void readDB(mapAssetType& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_label);
    readField(file, entry.m_pathdir);
    readField(file, entry.m_typelabel);
}

void readDB(mapIcon& entry, std::istream& file)
{
    readField(file, entry.m_LOT);
    readField(file, entry.m_iconID);
    readField(file, entry.m_iconState);
}

void readDB(mapItemTypes& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_description);
    readField(file, entry.m_equipLocation);
}

void readDB(mapRenderEffects& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_gameID);
    readField(file, entry.m_description);
}

void readDB(mapShaders& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_label);
    readField(file, entry.m_gameValue);
    readField(file, entry.m_priority);
}

void readDB(mapTextureResource& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_texturepath);
    readField(file, entry.m_SurfaceType);
}

void readDB(map_BlueprintCategory& entry, std::istream& file)
{
    readField(file, entry.m_id);
    readField(file, entry.m_description);
    readField(file, entry.m_enabled);
}

void readDB(sysdiagrams& entry, std::istream& file)
{
    readField(file, entry.m_name);
    readField(file, entry.m_principal_id);
    readField(file, entry.m_diagram_id);
    readField(file, entry.m_version);
    readField(file, entry.m_definition);
}

