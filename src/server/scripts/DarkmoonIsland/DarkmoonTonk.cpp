/*
 * Copyright 2021 ShadowCore
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include "GameObject.h"
#include "Transport.h"
#include "DarkmoonIsland.h"
#include "AchievementMgr.h"
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "DarkmoonIsland.h"
#include "Player.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "InstanceScript.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "WorldSession.h"
#include "Item.h"
#include "SpellInfo.h"
#include "SpellMgr.h"
#include "GameEventMgr.h"
#include "AchievementPackets.h"
#include "DB2HotfixGenerator.h"
#include "DB2Stores.h"
#include "CellImpl.h"
#include "ChatTextBuilder.h"
#include "Containers.h"
#include "DatabaseEnv.h"
#include "GameTime.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Language.h"
#include "Mail.h"
#include "ObjectMgr.h"
#include "RBAC.h"
#include "StringConvert.h"
#include "World.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "CreatureAI.h"
#include "CreatureAIImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SharedDefines.h"
#include "ObjectAccessor.h"
#include "TemporarySummon.h"
#include <sstream>

#include "ScriptMgr.h"
#include "DarkmoonIsland.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "ScriptedGossip.h"
#include "MotionMaster.h"
#include <G3D/Quat.h>

enum eSpells
{
    SPELL_PROGRESS_BAR = 102178,
    SPELL_SUMMON_TONK = 100752,
};

class go_tonk_console : public GameObjectScript
{
public:
    go_tonk_console() : GameObjectScript("go_tonk_console") { }

    struct go_tonk_consoleAI : public GameObjectAI
    {
        go_tonk_consoleAI(GameObject* go) : GameObjectAI(go) { }

        bool OnGossipHello(Player* /*player*/) override
        {
            return false;
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_tonk_consoleAI(go);
    }
};

enum TonkCommander
{
    EVENT_TONKCOMMANDER_START_GAME_1 = 1,
    EVENT_TONKCOMMANDER_START_GAME_2 = 2,
    EVENT_TONKCOMMANDER_START_GAME_3 = 3,
    EVENT_TONKCOMMANDER_FINISH_GAME = 4,
};

class npc_finlay_coolshot : public CreatureScript
{
public:
    npc_finlay_coolshot() : CreatureScript("npc_finlay_coolshot") { }

    struct npc_finlay_coolshotAI : public ScriptedAI
    {
        npc_finlay_coolshotAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;

        bool Active;

        void Reset()
        {
            Active = false;
        }

        void StartGame()
        {
            if (!Active)
            {
                events.ScheduleEvent(EVENT_TONKCOMMANDER_START_GAME_1, 0ms);
                events.ScheduleEvent(EVENT_TONKCOMMANDER_START_GAME_2, 0ms);
                events.ScheduleEvent(EVENT_TONKCOMMANDER_START_GAME_3, 0ms);
                events.ScheduleEvent(EVENT_TONKCOMMANDER_FINISH_GAME, 60000ms);
            }
        }

        void UpdateAI(uint32 diff)
        {
            events.Update(diff);

            Map::PlayerList const& PlayerList = me->GetMap()->GetPlayers();

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_TONKCOMMANDER_START_GAME_1:
                    switch (urand(0, 16))
                    {
                    case 0:
                        me->SummonCreature(33081, -4141.6f, 6315.88f, 13.11f, 4.91587f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 1:
                        me->SummonCreature(33081, -4146.43f, 6309.72f, 13.11f, 5.9655f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 2:
                        me->SummonCreature(33081, -4143.39f, 6314.97f, 13.11f, 5.87662f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 3:
                        me->SummonCreature(33081, -4128.46f, 6312.61f, 13.11f, 0.0794366f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 4:
                        me->SummonCreature(33081, -4123.75f, 6305.47f, 13.11f, 3.03825f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 5:
                        me->SummonCreature(33081, -4136.6f, 6301.53f, 13.1176f, 1.45875f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 6:
                        me->SummonCreature(33081, -4139.58f, 6308.16f, 13.1176f, 1.04362f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 7:
                        me->SummonCreature(33081, -4142.23f, 6291.32f, 13.1167f, 0.986097f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 8:
                        me->SummonCreature(33081, -4136.95f, 6289.13f, 13.1167f, 1.68022f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 9:
                        me->SummonCreature(33081, -4126.09f, 6292.85f, 13.1167f, 2.36872f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 10:
                        me->SummonCreature(33081, -4139.19f, 6287.29f, 13.1167f, 1.47097f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 11:
                        me->SummonCreature(33081, -4148.21f, 6301.88f, 13.1165f, 0.0309724f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 12:
                        me->SummonCreature(33081, -4142.29f, 6299.38f, 13.1165f, 0.0309724f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 13:
                        me->SummonCreature(33081, -4124.66f, 6299.65f, 13.1165f, 2.8671f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 14:
                        me->SummonCreature(33081, -4133.37f, 6308.8f, 13.1165f, 1.07716f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 15:
                        me->SummonCreature(33081, -4132.44f, 6291.18f, 13.1165f, 2.16906f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 16:
                        me->SummonCreature(33081, -4137.18f, 6295.24f, 13.1165f, 4.25818f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    }
                    events.ScheduleEvent(EVENT_TONKCOMMANDER_START_GAME_1, 5000ms);
                    break;
                case EVENT_TONKCOMMANDER_START_GAME_2:
                    switch (urand(0, 16))
                    {
                    case 0:
                        me->SummonCreature(33081, -4141.6f, 6315.88f, 13.11f, 4.91587f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 1:
                        me->SummonCreature(33081, -4146.43f, 6309.72f, 13.11f, 5.9655f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 2:
                        me->SummonCreature(33081, -4143.39f, 6314.97f, 13.11f, 5.87662f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 3:
                        me->SummonCreature(33081, -4128.46f, 6312.61f, 13.11f, 0.0794366f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 4:
                        me->SummonCreature(33081, -4123.75f, 6305.47f, 13.11f, 3.03825f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 5:
                        me->SummonCreature(33081, -4136.6f, 6301.53f, 13.1176f, 1.45875f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 6:
                        me->SummonCreature(33081, -4139.58f, 6308.16f, 13.1176f, 1.04362f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 7:
                        me->SummonCreature(33081, -4142.23f, 6291.32f, 13.1167f, 0.986097f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 8:
                        me->SummonCreature(33081, -4136.95f, 6289.13f, 13.1167f, 1.68022f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 9:
                        me->SummonCreature(33081, -4126.09f, 6292.85f, 13.1167f, 2.36872f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 10:
                        me->SummonCreature(33081, -4139.19f, 6287.29f, 13.1167f, 1.47097f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 11:
                        me->SummonCreature(33081, -4148.21f, 6301.88f, 13.1165f, 0.0309724f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 12:
                        me->SummonCreature(33081, -4142.29f, 6299.38f, 13.1165f, 0.0309724f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 13:
                        me->SummonCreature(33081, -4124.66f, 6299.65f, 13.1165f, 2.8671f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 14:
                        me->SummonCreature(33081, -4133.37f, 6308.8f, 13.1165f, 1.07716f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 15:
                        me->SummonCreature(33081, -4132.44f, 6291.18f, 13.1165f, 2.16906f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 16:
                        me->SummonCreature(33081, -4137.18f, 6295.24f, 13.1165f, 4.25818f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    }
                    events.ScheduleEvent(EVENT_TONKCOMMANDER_START_GAME_2, 5000ms);
                    break;
                case EVENT_TONKCOMMANDER_START_GAME_3:
                    switch (urand(0, 16))
                    {
                    case 0:
                        me->SummonCreature(33081, -4141.6f, 6315.88f, 13.11f, 4.91587f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 1:
                        me->SummonCreature(33081, -4146.43f, 6309.72f, 13.11f, 5.9655f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 2:
                        me->SummonCreature(33081, -4143.39f, 6314.97f, 13.11f, 5.87662f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 3:
                        me->SummonCreature(33081, -4128.46f, 6312.61f, 13.11f, 0.0794366f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 4:
                        me->SummonCreature(33081, -4123.75f, 6305.47f, 13.11f, 3.03825f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 5:
                        me->SummonCreature(33081, -4136.6f, 6301.53f, 13.1176f, 1.45875f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 6:
                        me->SummonCreature(33081, -4139.58f, 6308.16f, 13.1176f, 1.04362f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 7:
                        me->SummonCreature(33081, -4142.23f, 6291.32f, 13.1167f, 0.986097f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 8:
                        me->SummonCreature(33081, -4136.95f, 6289.13f, 13.1167f, 1.68022f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 9:
                        me->SummonCreature(33081, -4126.09f, 6292.85f, 13.1167f, 2.36872f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 10:
                        me->SummonCreature(33081, -4139.19f, 6287.29f, 13.1167f, 1.47097f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 11:
                        me->SummonCreature(33081, -4148.21f, 6301.88f, 13.1165f, 0.0309724f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 12:
                        me->SummonCreature(33081, -4142.29f, 6299.38f, 13.1165f, 0.0309724f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 13:
                        me->SummonCreature(33081, -4124.66f, 6299.65f, 13.1165f, 2.8671f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 14:
                        me->SummonCreature(33081, -4133.37f, 6308.8f, 13.1165f, 1.07716f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 15:
                        me->SummonCreature(33081, -4132.44f, 6291.18f, 13.1165f, 2.16906f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    case 16:
                        me->SummonCreature(33081, -4137.18f, 6295.24f, 13.1165f, 4.25818f, TEMPSUMMON_TIMED_DESPAWN, 10000ms);
                        break;
                    }
                    events.ScheduleEvent(EVENT_TONKCOMMANDER_START_GAME_3, 5000ms);
                    break;
                case EVENT_TONKCOMMANDER_FINISH_GAME:
                    Active = false;
                    events.CancelEvent(EVENT_TONKCOMMANDER_START_GAME_1);
                    events.CancelEvent(EVENT_TONKCOMMANDER_START_GAME_2);
                    events.CancelEvent(EVENT_TONKCOMMANDER_START_GAME_3);
                    break;
                }
            }
        }

        bool OnGossipHello(Player* player) override
        {
            if (me->IsQuestGiver())
                player->PrepareQuestMenu(me->GetGUID());

            char const* GOSSIP_BUTTON_1;
            char const* GOSSIP_BUTTON_2;

            switch (LocaleConstant currentlocale = player->GetSession()->GetSessionDbcLocale())
            {
            case 20:    // locales end on 11, case 20 is impossible case, this is just to fix compile warnings.
                break;
            default:
                GOSSIP_BUTTON_1 = "How do I play the Tonk Challenge?";
                GOSSIP_BUTTON_2 = "Ready to play! |cFF0000FF(Darkmoon Game Token)|r";
                break;
            };

            AddGossipItemFor(player, GossipOptionNpc::None, GOSSIP_BUTTON_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            if (!player->HasAura(101612) && !player->HasAura(110230) && !player->HasAura(102121) && !player->HasAura(102178) && !player->HasAura(102058) && !player->HasAura(101871))
                AddGossipItemFor(player, GossipOptionNpc::None, GOSSIP_BUTTON_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

            SendGossipMenuFor(player, 54605, me->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, uint32 uiSender, uint32 action) override
        {
            char const* GOSSIP_BUTTON_1;
            char const* GOSSIP_BUTTON_2;
            char const* GOSSIP_BUTTON_3;

            switch (LocaleConstant currentlocale = player->GetSession()->GetSessionDbcLocale())
            {
            case 20:    // locales end on 11, case 20 is impossible case, this is just to fix compile warnings.
                break;
            default:
                GOSSIP_BUTTON_1 = "How do I play the Tonk Challenge?";
                GOSSIP_BUTTON_2 = "Ready to play! |cFF0000FF(Darkmoon Game Token)|r";
                GOSSIP_BUTTON_3 = "Alright.";
                break;
            };

            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                AddGossipItemFor(player, GossipOptionNpc::None, GOSSIP_BUTTON_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                SendGossipMenuFor(player, 54606, me->GetGUID());
            }

            if (action == GOSSIP_ACTION_INFO_DEF + 2)
            {
                if (player->HasItemCount(71083))
                {
                    CloseGossipMenuFor(player);

                    player->DestroyItemCount(71083, 1, true);
                    player->RemoveAurasByType(SPELL_AURA_MOUNTED);
                    player->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

                    player->AddAura(102178, player);

                    if (Creature* summon = me->SummonCreature(54588, -4131.37f, 6317.32f, 13.11f, 4.31f, TEMPSUMMON_TIMED_DESPAWN, 60000ms))
                        player->CastSpell(summon, 46598, false);

                    CAST_AI(npc_finlay_coolshot::npc_finlay_coolshotAI, me->AI())->StartGame();
                    CAST_AI(npc_finlay_coolshot::npc_finlay_coolshotAI, me->AI())->Active = true;

                    return true;
                }
                else
                    SendGossipMenuFor(player, 54603, me->GetGUID());
            }

            if (action == GOSSIP_ACTION_INFO_DEF + 3)
            {
                if (me->IsQuestGiver())
                    player->PrepareQuestMenu(me->GetGUID());

                AddGossipItemFor(player, GossipOptionNpc::None, GOSSIP_BUTTON_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

                if (!player->HasAura(101612) && !player->HasAura(110230) && !player->HasAura(102121) && !player->HasAura(102178) && !player->HasAura(102058) && !player->HasAura(101871))
                    AddGossipItemFor(player, GossipOptionNpc::None, GOSSIP_BUTTON_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

                SendGossipMenuFor(player, 54605, me->GetGUID());
            }

            return true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_finlay_coolshotAI(creature);
    }
};

void AddSC_darkmoon_tonk()
{
    //npc
    new npc_finlay_coolshot();
    //go
    new go_tonk_console();
};