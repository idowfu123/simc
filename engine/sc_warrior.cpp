// ==========================================================================
// Dedmonwakeen's DPS-DPM Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================

#include "simulationcraft.h"

// ==========================================================================
// Warrior
// ==========================================================================

enum warrior_stance { STANCE_BATTLE=1, STANCE_BERSERKER, STANCE_DEFENSE=4 };

struct warrior_t : public player_t
{
  // Active
  action_t* active_deep_wounds;
  int       active_stance;

  // Active Spells
   struct active_spells_t
  {
    active_spell_t* battle_shout;
    active_spell_t* berserker_rage;
    active_spell_t* bladestorm;
    active_spell_t* bloodthirst;
    active_spell_t* cleave;
    active_spell_t* colossus_smash;
    active_spell_t* concussion_blow;
    active_spell_t* deadly_calm;
    active_spell_t* death_wish;
    active_spell_t* devastate;
    active_spell_t* execute;
    active_spell_t* heroic_strike;
    active_spell_t* inner_rage;
    active_spell_t* mortal_strike;
    active_spell_t* overpower;
    active_spell_t* pummel;
    active_spell_t* raging_blow;
    active_spell_t* recklessness;
    active_spell_t* rend;
    active_spell_t* revenge;
    active_spell_t* shield_bash;
    active_spell_t* shield_block;
    active_spell_t* shield_slam;
    active_spell_t* shockwave;
    active_spell_t* slam;
    active_spell_t* sweeping_strikes;
    active_spell_t* thunder_clap;
    active_spell_t* victory_rush;
    active_spell_t* whirlwind;
  };
  active_spells_t   active_spells;

  // Buffs
  buff_t* buffs_bastion_of_defense;
  buff_t* buffs_battle_stance;
  buff_t* buffs_battle_trance;
  buff_t* buffs_berserker_rage;
  buff_t* buffs_berserker_stance;
  buff_t* buffs_bloodsurge;
  buff_t* buffs_colossus_smash;
  buff_t* buffs_deadly_calm;
  buff_t* buffs_death_wish;
  buff_t* buffs_defensive_stance;
  buff_t* buffs_enrage;
  buff_t* buffs_executioner_talent;
  buff_t* buffs_flurry;
  buff_t* buffs_hold_the_line;
  buff_t* buffs_incite;
  buff_t* buffs_inner_rage;
  buff_t* buffs_lambs_to_the_slaughter;
  buff_t* buffs_meat_cleaver;
  buff_t* buffs_overpower;
  buff_t* buffs_recklessness;
  buff_t* buffs_revenge;
  buff_t* buffs_rude_interruption;
  buff_t* buffs_shield_block;
  buff_t* buffs_sweeping_strikes;
  buff_t* buffs_sword_and_board;
  buff_t* buffs_taste_for_blood;
  buff_t* buffs_thunderstruck;
  buff_t* buffs_victory_rush;
  buff_t* buffs_wrecking_crew;
  buff_t* buffs_tier10_2pc_melee;
  buff_t* buffs_tier10_4pc_melee;

  // Cooldowns
  cooldown_t* cooldowns_colossus_smash;
  cooldown_t* cooldowns_shield_slam;

  // Dots
  dot_t* dots_deep_wounds;
  dot_t* dots_rend;

  // Events
  event_t* deep_wounds_delay_event;

  // Gains
  gain_t* gains_anger_management;
  gain_t* gains_avoided_attacks;
  gain_t* gains_battle_shout;
  gain_t* gains_berserker_rage;
  gain_t* gains_blood_frenzy;
  gain_t* gains_incoming_damage;
  gain_t* gains_mh_attack;
  gain_t* gains_oh_attack;
  gain_t* gains_shield_specialization;
  gain_t* gains_sudden_death;

  // Glyphs
  struct glyphs_t
  {
    int battle;
    int berserker_rage;
    int bladestorm;
    int bloodthirst;
    int cleaving;
    int devastate;
    int enduring_victory;
    int mortal_strike;
    int overpower;
    int raging_blow;
    int resonating_power;
    int revenge;
    int shield_slam;
    int shockwave;
    int slam;
    int sweeping_strikes;

    glyphs_t() { memset( ( void* ) this, 0x0, sizeof( glyphs_t ) ); }
  };
  glyphs_t glyphs;

  // Mastery
  struct mastery_t
  {
    passive_spell_t* critical_block;
    passive_spell_t* strikes_of_opportunity;
    passive_spell_t* unshackled_fury;

    mastery_t() { memset( ( void* ) this, 0x0, sizeof( mastery_t ) ); }
  };
  mastery_t mastery;

  // Procs
  proc_t* procs_deferred_deep_wounds;
  proc_t* procs_munched_deep_wounds;
  proc_t* procs_rolled_deep_wounds;
  proc_t* procs_parry_haste;
  proc_t* procs_strikes_of_opportunity;
  proc_t* procs_sudden_death;

  // Random Number Generation
  rng_t* rng_blood_frenzy;
  rng_t* rng_executioner_talent;
  rng_t* rng_impending_victory;
  rng_t* rng_strikes_of_opportunity;
  rng_t* rng_sudden_death;
  rng_t* rng_wrecking_crew;
  rng_t* rng_tier10_4pc_melee;  

  // Spec Passives
  struct spec_t
  {
    passive_spell_t* anger_management;    
    passive_spell_t* dual_wield_specialization;
    passive_spell_t* precision;
    passive_spell_t* sentinel;
    passive_spell_t* two_handed_weapon_specialization;

    spec_t() { memset( ( void* ) this, 0x0, sizeof( spec_t ) ); }
  };
  spec_t spec;

  // Talents
  struct talents_t
  {
    // Arms
    talent_t* bladestorm;
    talent_t* blood_frenzy;
    talent_t* deadly_calm;
    talent_t* deep_wounds;
    talent_t* drums_of_war;
    talent_t* impale;
    talent_t* improved_slam;
    talent_t* lambs_to_the_slaughter;
    talent_t* sudden_death;
    talent_t* sweeping_strikes;
    talent_t* tactical_mastery;
    talent_t* taste_for_blood;
    talent_t* war_academy;
    talent_t* wrecking_crew;

    // Fury
    talent_t* battle_trance;
    talent_t* bloodsurge;
    talent_t* booming_voice;
    talent_t* cruelty;
    talent_t* death_wish;
    talent_t* enrage;
    talent_t* executioner;
    talent_t* flurry;
    talent_t* gag_order;
    talent_t* intensify_rage;
    talent_t* meat_cleaver;
    talent_t* raging_blow;
    talent_t* rampage;
    talent_t* rude_interruption;
    talent_t* single_minded_fury;
    talent_t* titans_grip;

    // Prot
    talent_t* bastion_of_defense;
    talent_t* concussion_blow;
    talent_t* devastate;
    talent_t* heavy_repercussions;
    talent_t* hold_the_line;
    talent_t* impending_victory;
    talent_t* improved_revenge;
    talent_t* incite;
    talent_t* shockwave;
    talent_t* shield_mastery;
    talent_t* shield_specialization;
    talent_t* sword_and_board;
    talent_t* toughness;
    talent_t* thunderstruck;

    talents_t() { memset( ( void* ) this, 0x0, sizeof( talents_t ) ); }
  };
  talents_t talents;

  // Up-Times
  uptime_t* uptimes_deep_wounds;
  uptime_t* uptimes_rage_cap;
  uptime_t* uptimes_rend;

  bool plate_specialization;

  warrior_t( sim_t* sim, const std::string& name, race_type r = RACE_NONE ) : player_t( sim, WARRIOR, name, r )
  {
    tree_type[ WARRIOR_ARMS       ] = TREE_ARMS;
    tree_type[ WARRIOR_FURY       ] = TREE_FURY;
    tree_type[ WARRIOR_PROTECTION ] = TREE_PROTECTION;

    // Active
    active_deep_wounds = 0;
    active_stance      = STANCE_BATTLE;

    // Cooldowns
    cooldowns_colossus_smash = get_cooldown( "colossus_smash" );
    cooldowns_shield_slam    = get_cooldown( "shield_slam"    );

    // Dots
    dots_deep_wounds = get_dot( "deep_wounds" );
    dots_rend        = get_dot( "rend"        );

    // Plate Specialization enabled by default
    plate_specialization = true;
  }

  // Character Definition
  virtual void      init_talents();
  virtual void      init_spells();
  virtual void      init_glyphs();
  virtual void      init_race();
  virtual void      init_base();
  virtual void      init_scaling();
  virtual void      init_buffs();
  virtual void      init_gains();
  virtual void      init_procs();
  virtual void      init_uptimes();
  virtual void      init_rng();
  virtual void      init_actions();
  virtual void      combat_begin();
  virtual double    composite_attack_penetration() SC_CONST;
  virtual double    composite_attack_power_multiplier() SC_CONST;
  virtual double    composite_attack_hit() SC_CONST;
  virtual double    composite_attribute_multiplier( int attr ) SC_CONST;
  virtual double    composite_tank_block() SC_CONST;
  virtual void      reset();
  virtual void      interrupt();
  virtual void      regen( double periodicity );
  virtual double    resource_loss( int resurce, double amount, action_t* );
  virtual std::vector<talent_translation_t>& get_talent_list();
  virtual std::vector<option_t>& get_options();
  virtual action_t* create_action( const std::string& name, const std::string& options );
  virtual int       decode_set( item_t& item );
  virtual int       primary_resource() SC_CONST { return RESOURCE_RAGE; }
  virtual int       primary_role() SC_CONST     { return ROLE_ATTACK; }
  virtual int       target_swing();
};

namespace   // ANONYMOUS NAMESPACE ==========================================
{

// ==========================================================================
// Warrior Attack
// ==========================================================================

struct warrior_attack_t : public attack_t
{
  double min_rage, max_rage;
  int stancemask;

  warrior_attack_t( const char* n, player_t* player, const school_type s=SCHOOL_PHYSICAL, int t=TREE_NONE, bool special=true  ) :
      attack_t( n, player, RESOURCE_RAGE, s, t, special ),
      min_rage( 0 ), max_rage( 0 ),
      stancemask( STANCE_BATTLE|STANCE_BERSERKER|STANCE_DEFENSE )
  {
    may_glance   = false;
    normalize_weapon_speed = true;
  }

  virtual void   parse_options( option_t*, const std::string& options_str );
  virtual void   consume_resource();
  virtual double cost() SC_CONST;
  virtual void   execute();
  virtual void   player_buff();
  virtual bool   ready();
  virtual void   assess_damage( double amount, int dmg_type );
};


// ==========================================================================
// Static Functions
// ==========================================================================

// trigger_blood_frenzy =====================================================

static void trigger_blood_frenzy( action_t* a )
{
  warrior_t* p = a -> player -> cast_warrior();
  if ( p -> talents.blood_frenzy -> rank() == 0 )
    return;

  target_t* t = a -> sim -> target;

  // Don't alter the duration if it is set to 0 (override/optimal_raid)
  if ( t -> debuffs.blood_frenzy_bleed -> buff_duration > 0 )
  {
    t -> debuffs.blood_frenzy_bleed -> buff_duration = a -> num_ticks * a -> base_tick_time;
  }
  if ( t -> debuffs.blood_frenzy_physical -> buff_duration > 0 )
  {
    t -> debuffs.blood_frenzy_physical -> buff_duration = a -> num_ticks * a -> base_tick_time;
  }

  double rank = p -> talents.blood_frenzy -> rank();

  if ( rank * 2 >= t -> debuffs.blood_frenzy_bleed -> current_value )
  {
    t -> debuffs.blood_frenzy_bleed -> trigger( 1, rank * 2 );
  }
  if ( rank * 15 >= t -> debuffs.blood_frenzy_physical -> current_value )
  {
    t -> debuffs.blood_frenzy_physical -> trigger( 1, rank * 15 );
  }
}

// trigger_bloodsurge =======================================================

static void trigger_bloodsurge( action_t* a )
{
  warrior_t* p = a -> player -> cast_warrior();

  if ( ! p -> talents.bloodsurge -> rank() )
    return;

  if ( p -> set_bonus.tier10_4pc_melee() && p -> rng_tier10_4pc_melee -> roll( 0.30 ) )
  {
    p -> buffs_bloodsurge -> max_stack = 2;
    p -> buffs_bloodsurge -> buff_duration = 10;

    p -> buffs_tier10_4pc_melee -> buff_duration = 20;
  }
  else
  {
    p -> buffs_bloodsurge -> max_stack = 1;
    p -> buffs_bloodsurge -> buff_duration = 10;
  }

  if ( p -> buffs_bloodsurge -> trigger( p -> buffs_bloodsurge -> max_stack ) )
  {
    p -> buffs_tier10_4pc_melee -> trigger();
  }
}

// trigger_deep_wounds ======================================================

static void trigger_deep_wounds( action_t* a )
{
  warrior_t* p = a -> player -> cast_warrior();
  sim_t*   sim = a -> sim;

  if ( ! p -> talents.deep_wounds -> rank() )
    return;

  // Every action HAS to have an weapon associated.
  assert( a -> weapon != 0 );

  struct deep_wounds_t : public warrior_attack_t
  {
    deep_wounds_t( warrior_t* p ) :
      warrior_attack_t( "deep_wounds", p, SCHOOL_BLEED, TREE_ARMS )
    {
      background = true;
      trigger_gcd = 0;
      weapon_multiplier = p -> talents.deep_wounds -> rank() * 0.16;
      base_tick_time = 1.0;
      num_ticks = 6;
      number_ticks = num_ticks;
      reset(); // required since construction occurs after player_t::init()

      id = 12834;
    }

    virtual void target_debuff( int dmg_type )
    {
      target_t* t = sim -> target;
      warrior_attack_t::target_debuff( dmg_type );

      // Deep Wounds doesn't benefit from Blood Frenzy or Savage Combat despite being a Bleed so disable it.
      if ( t -> debuffs.blood_frenzy_bleed  -> up() ||
           t -> debuffs.savage_combat       -> up() )
      {
        target_multiplier /= 1.04;
      }
    }

    virtual double total_td_multiplier() SC_CONST
    {
      return target_multiplier;
    }

    virtual void tick()
    {
      warrior_attack_t::tick();
      warrior_t* p = player -> cast_warrior();
      p -> buffs_tier10_2pc_melee -> trigger();
    }
  };

  if ( ! p -> active_deep_wounds ) p -> active_deep_wounds = new deep_wounds_t( p );

  p -> active_deep_wounds -> weapon = a -> weapon;
  p -> active_deep_wounds -> player_buff();

  double deep_wounds_dmg = ( p -> active_deep_wounds -> calculate_weapon_damage() *
                             p -> active_deep_wounds -> weapon_multiplier *
	                           p -> active_deep_wounds -> player_multiplier );

  if ( a -> weapon -> slot == SLOT_OFF_HAND )
    deep_wounds_dmg *= 0.5;

  if ( p -> active_deep_wounds -> ticking )
  {
    int num_ticks = p -> active_deep_wounds -> num_ticks;
    int remaining_ticks = num_ticks - p -> active_deep_wounds -> current_tick;

    deep_wounds_dmg += p -> active_deep_wounds -> base_td * remaining_ticks;
  }

  // The Deep Wounds SPELL_AURA_APPLIED does not actually occur immediately.
  // There is a short delay which can result in "munched" or "rolled" ticks.

  if ( sim -> aura_delay == 0 )
  {
    // Do not model the delay, so no munch/roll, just defer.

    if ( p -> active_deep_wounds -> ticking )
    {
      if ( sim -> log ) log_t::output( sim, "Player %s defers Deep Wounds.", p -> name() );
      p -> procs_deferred_deep_wounds -> occur();
      p -> active_deep_wounds -> cancel();
    }

    p -> active_deep_wounds -> base_td = deep_wounds_dmg / 6.0;
    p -> active_deep_wounds -> schedule_tick();
    trigger_blood_frenzy( p -> active_deep_wounds );

    return;
  }

  struct deep_wounds_delay_t : public event_t
  {
    double deep_wounds_dmg;

    deep_wounds_delay_t( sim_t* sim, player_t* p, double dmg ) : event_t( sim, p ), deep_wounds_dmg( dmg )
    {
      name = "Deep Wounds Delay";
      sim -> add_event( this, sim -> gauss( sim -> aura_delay, sim -> aura_delay * 0.25 ) );
    }
    virtual void execute()
    {
      warrior_t* p = player -> cast_warrior();

      if ( p -> active_deep_wounds -> ticking )
      {
	      if ( sim -> log ) log_t::output( sim, "Player %s defers Deep Wounds.", p -> name() );
	      p -> procs_deferred_deep_wounds -> occur();
	      p -> active_deep_wounds -> cancel();
      }

      p -> active_deep_wounds -> base_td = deep_wounds_dmg / 6.0;
      p -> active_deep_wounds -> schedule_tick();
      trigger_blood_frenzy( p -> active_deep_wounds );

      if ( p -> deep_wounds_delay_event == this ) p -> deep_wounds_delay_event = 0;
    }
  };

  if ( p -> deep_wounds_delay_event )
  {
    // There is an SPELL_AURA_APPLIED already in the queue.
    if ( sim -> log ) log_t::output( sim, "Player %s munches Deep Wounds.", p -> name() );
    p -> procs_munched_deep_wounds -> occur();
  }

  p -> deep_wounds_delay_event = new ( sim ) deep_wounds_delay_t( sim, p, deep_wounds_dmg );

  if ( p -> active_deep_wounds -> ticking )
  {
    if ( p -> active_deep_wounds -> tick_event -> occurs() <
	 p -> deep_wounds_delay_event -> occurs() )
    {
      // Deep Wounds will tick before SPELL_AURA_APPLIED occurs, which means that the current Deep Wounds will
      // both tick -and- get rolled into the next Deep Wounds.
      if ( sim -> log ) log_t::output( sim, "Player %s rolls Deep Wounds.", p -> name() );
      p -> procs_rolled_deep_wounds -> occur();
    }
  }
}

// trigger_rage_gain ========================================================

static void trigger_rage_gain( attack_t* a, double rage_conversion_value )
{
  // Basic Formula:      http://forums.worldofwarcraft.com/thread.html?topicId=17367760070&sid=1&pageNo=1
  // Blue Clarification: http://forums.worldofwarcraft.com/thread.html?topicId=17367760070&sid=1&pageNo=13#250

  if ( a -> proc )
    return;

  warrior_t* p = a -> player -> cast_warrior();
  weapon_t*  w = a -> weapon;

  double rage_factor = 6.5;
  if ( a -> result == RESULT_CRIT ) rage_factor *= 2.0;
  if ( w -> slot == SLOT_OFF_HAND ) rage_factor /= 2.0;
  
  double rage_gain = rage_factor * w -> swing_time;

  if ( p -> spec.anger_management -> ok() )
  {
    rage_gain *= 1.0 + p -> spec.anger_management -> effect_base_value( 2 ) / 100.0;
  }

  p -> resource_gain( RESOURCE_RAGE, rage_gain, w -> slot == SLOT_OFF_HAND ? p -> gains_oh_attack : p -> gains_mh_attack );
}

// trigger_strikes_of_opportunity ===========================================

static void trigger_strikes_of_opportunity( attack_t* a )
{
  if ( a -> proc )
    return;

  if ( a -> result_is_miss() )
    return;

  weapon_t* w = a -> weapon;

  if ( ! w )
    return;

  warrior_t* p = a -> player -> cast_warrior();

  if ( ! p -> mastery.strikes_of_opportunity -> ok() )
    return;
  
  if ( p -> rng_strikes_of_opportunity -> roll( p -> composite_mastery() * p -> mastery.strikes_of_opportunity -> effect_base_value( 2 ) / 10000.0 ) )
  {
    if ( a -> sim -> log )
      log_t::output( a -> sim, "%s gains one extra attack through %s",
                     p -> name(), p -> procs_strikes_of_opportunity -> name() );

    p -> procs_strikes_of_opportunity -> occur();
    
    double proc_value = ( a -> sim -> P403 ) ? 0.75 : 1.15; // HOTFIX 115% weapon damage
    p -> main_hand_attack -> proc = true;
    p -> main_hand_attack -> player_multiplier *= proc_value;
    p -> main_hand_attack -> execute();
    p -> main_hand_attack -> proc = false;
    p -> main_hand_attack -> player_multiplier /= proc_value;
  }
}

// trigger_sudden_death =====================================================

static void trigger_sudden_death( action_t* a )
{
  warrior_t* p = a -> player -> cast_warrior();

  if ( a -> proc )
    return;

  if ( p -> rng_sudden_death -> roll ( p -> talents.sudden_death -> proc_chance() ) )
  {
    p -> cooldowns_colossus_smash -> reset();
    p -> procs_sudden_death       -> occur();
  }
}

// trigger_sword_and_board ==================================================

static void trigger_sword_and_board( attack_t* a )
{
  warrior_t* p = a -> player -> cast_warrior();

  if ( p -> buffs_sword_and_board -> trigger() )
  {
    p -> cooldowns_shield_slam -> reset();
  }
}

// ==========================================================================
// Warrior Attacks
// ==========================================================================

// warrior_attack_t::assess_damage ==========================================

void warrior_attack_t::assess_damage( double amount,
                                    int    dmg_type )
{
  attack_t::assess_damage( amount, dmg_type );

  warrior_t* p = player -> cast_warrior();

  if ( p -> buffs_sweeping_strikes -> up() && sim -> target -> adds_nearby )
  {
    attack_t::additional_damage( amount, dmg_type );
  }
}

// warrior_attack_t::cost ===================================================

double warrior_attack_t::cost() SC_CONST
{
  warrior_t* p = player -> cast_warrior();
  double c = attack_t::cost() / 10; // Rage Costs are stored as * 10
  if ( p -> buffs_deadly_calm   -> check() )          c  = 0;
  if ( p -> buffs_inner_rage    -> check() )          c *= 1.50;
  if ( p -> buffs_battle_trance -> check() && c > 5 ) c  = 0;
  return c;
}

// warrior_attack_t::consume_resource =======================================

void warrior_attack_t::consume_resource()
{
  warrior_t* p = player -> cast_warrior();

  attack_t::consume_resource();

  if ( special && p -> buffs_recklessness -> check() )
  {
    p -> buffs_recklessness -> decrement();
  }

  // Warrior attacks (non-AoE) which are are avoided by the target consume only 20%

  if ( resource_consumed > 0 && ! aoe && result_is_miss() )
  {
    double rage_restored = resource_consumed * 0.80;
    p -> resource_gain( RESOURCE_RAGE, rage_restored, p -> gains_avoided_attacks );
  }
}

// warrior_attack_t::execute ================================================

void warrior_attack_t::execute()
{
  attack_t::execute();

  warrior_t* p = player -> cast_warrior();
  p -> buffs_battle_trance   -> expire();

  if ( result_is_hit() )
  {
    trigger_sudden_death( this );

    if( result == RESULT_CRIT )
    {
      trigger_deep_wounds( this );
      p -> buffs_flurry -> trigger( 3 );
    }
  }
  else if ( result == RESULT_DODGE  )
  {
    p -> buffs_overpower -> trigger();
  }
}

// warrior_attack_t::parse_options ==========================================

void warrior_attack_t::parse_options( option_t*          options,
                                      const std::string& options_str )
{
  option_t base_options[] =
  {
    { "min_rage", OPT_FLT, &min_rage },
    { "max_rage", OPT_FLT, &max_rage },
    { "rage>",    OPT_FLT, &min_rage },
    { "rage<",    OPT_FLT, &max_rage },
    { NULL, OPT_UNKNOWN, NULL }
  };
  std::vector<option_t> merged_options;
  attack_t::parse_options( merge_options( merged_options, options, base_options ), options_str );
}

// warrior_attack_t::player_buff ============================================

void warrior_attack_t::player_buff()
{
  attack_t::player_buff();

  warrior_t* p = player -> cast_warrior();

  if ( weapon )
  {
    if ( p -> spec.dual_wield_specialization -> ok() && weapon -> slot == SLOT_OFF_HAND )
    {
      player_multiplier *= 1.0 + p -> spec.dual_wield_specialization -> effect_base_value( 2 ) / 100.0;
    }
    if ( p -> spec.two_handed_weapon_specialization -> ok() && weapon -> group() == WEAPON_2H)
    {
      player_multiplier *= 1.0 + p -> spec.two_handed_weapon_specialization -> effect_base_value( 1 ) / 100.0;
    }
  }

  if ( p -> active_stance == STANCE_BATTLE && p -> buffs_battle_stance -> up() )
  {
    player_multiplier *= 1.05;
  }
  else if ( p -> active_stance == STANCE_BERSERKER && p -> buffs_berserker_stance -> up() )
  {
    player_multiplier *= 1.10;
  }
  else if ( p -> active_stance == STANCE_DEFENSE && p -> buffs_defensive_stance -> up() )
  {
    player_multiplier *= 0.95;
  }
  
  player_multiplier *= 1.0 + p -> buffs_death_wish    -> value();
  player_multiplier *= 1.0 + p -> buffs_enrage        -> value();
  player_multiplier *= 1.0 + p -> buffs_wrecking_crew -> value();
  
  if ( p -> talents.single_minded_fury -> rank() && p -> dual_wield() )
  {
    if ( p -> main_hand_attack -> weapon -> group() == WEAPON_1H ||
	       p ->  off_hand_attack -> weapon -> group() == WEAPON_1H )
    {
      player_multiplier *= 1 + p -> talents.single_minded_fury -> effect_base_value( 1 ) / 100.0;
    }
  }

  if ( p -> spec.dual_wield_specialization -> ok() && p -> dual_wield() && school == SCHOOL_PHYSICAL )
  {
    player_multiplier *= 1.0 + p -> spec.dual_wield_specialization -> effect_base_value( 3 ) / 100.0;
  }

  if ( special && p -> buffs_recklessness -> up() )
    player_crit += 1.0;

  if ( p -> buffs_inner_rage -> check() )
    player_multiplier *= 1.15;

  if ( p -> buffs_rude_interruption -> check() )
    player_multiplier *= 1.05;

  if ( p -> talents.rampage -> rank() )
    player_crit += p -> talents.rampage -> effect_base_value( 2 ) / 100.0;

  if ( p -> buffs_hold_the_line -> check() )
    player_crit += 0.10;

  if ( p -> buffs_bastion_of_defense -> check() )
    player_multiplier *= 1.0 + p -> talents.bastion_of_defense -> rank() * 0.05;

  if ( sim -> debug )
    log_t::output( sim, "warrior_attack_t::player_buff: %s hit=%.2f expertise=%.2f crit=%.2f crit_multiplier=%.2f",
                   name(), player_hit, player_expertise, player_crit, player_crit_multiplier );
  
}

// warrior_attack_t::ready() ================================================

bool warrior_attack_t::ready()
{
  if ( ! attack_t::ready() )
    return false;

  warrior_t* p = player -> cast_warrior();

  if ( min_rage > 0 )
    if ( p -> resource_current[ RESOURCE_RAGE ] < min_rage )
      return false;

  if ( max_rage > 0 )
    if ( p -> resource_current[ RESOURCE_RAGE ] > max_rage )
      return false;

  // Attack vailable in current stance?
  if ( ( stancemask & p -> active_stance ) == 0 )
    return false;

  return true;
}

// Melee Attack =============================================================

struct melee_t : public warrior_attack_t
{
  int sync_weapons;
  double rage_conversion_value;

  melee_t( const char* name, player_t* player, int sw ) :
    warrior_attack_t( name, player, SCHOOL_PHYSICAL, TREE_NONE, false ), sync_weapons( sw ), rage_conversion_value( 0 )
  {
    warrior_t* p = player -> cast_warrior();

    base_dd_min = base_dd_max = 1;

    may_glance      = true;
    may_crit        = true;
    background      = true;
    repeating       = true;
    trigger_gcd     = 0;
    base_cost       = 0;

    normalize_weapon_speed = false;

    if ( p -> dual_wield() ) base_hit -= 0.19;

    // Rage Conversion Value, needed for: damage done => rage gained
    if ( p -> level == 80 )
      rage_conversion_value = 453.3;
    else
      rage_conversion_value = 0.0091107836 * p -> level * p -> level + 3.225598133 * p -> level + 4.2652911;
  }

  virtual double haste() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    double h = warrior_attack_t::haste();
    if ( p -> buffs_flurry -> up() )
    {
      h *= 1.0 / ( 1.0 + util_t::talent_rank( p -> talents.flurry -> rank(), 3, 0.08, 0.16, 0.25 ) );
    }
    if ( p -> buffs_executioner_talent -> up() )
    {
      h *= 1.0 / ( 1.0 + p -> buffs_executioner_talent -> stack() * 0.05 );
    }
    return h;
  }

  virtual double execute_time() SC_CONST
  {
    double t = warrior_attack_t::execute_time();
    if ( ! player -> in_combat )
    {
      return ( weapon -> slot == SLOT_OFF_HAND ) ? ( sync_weapons ? std::min( t/2, 0.2 ) : t/2 ) : 0.01;
    }
    return t;
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();

    p -> buffs_flurry -> decrement();

    warrior_attack_t::execute();
    if ( result_is_hit() )
    {
	    trigger_rage_gain( this, rage_conversion_value );
      trigger_strikes_of_opportunity( this );

      if ( ! proc &&  p -> rng_blood_frenzy -> roll( p -> talents.blood_frenzy -> proc_chance() ) )
      {
        p -> resource_gain( RESOURCE_RAGE, p -> talents.blood_frenzy -> effect_base_value( 3 ), p -> gains_blood_frenzy );
      }

      double enrage_value = util_t::talent_rank( p -> talents.enrage -> rank(), 3, 3, 7, 10 ) * 0.01;
      if ( p -> mastery.unshackled_fury -> ok() )
      {
        enrage_value *= p -> composite_mastery() * p -> mastery.unshackled_fury -> effect_base_value( 3 ) / 10000.0;
      }
      p -> buffs_enrage -> trigger( 1, enrage_value);
    }
  }
};

// Auto Attack ==============================================================

struct auto_attack_t : public warrior_attack_t
{
  int sync_weapons;

  auto_attack_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "auto_attack", player ), sync_weapons( 0 )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { "sync_weapons", OPT_BOOL, &sync_weapons }
    };
    parse_options( options, options_str );

    assert( p -> main_hand_weapon.type != WEAPON_NONE );

    p -> main_hand_attack = new melee_t( "melee_main_hand", player, sync_weapons );
    p -> main_hand_attack -> weapon = &( p -> main_hand_weapon );
    p -> main_hand_attack -> base_execute_time = p -> main_hand_weapon.swing_time;

    if ( p -> off_hand_weapon.type != WEAPON_NONE )
    {
      p -> off_hand_attack = new melee_t( "melee_off_hand", player, sync_weapons );
      p -> off_hand_attack -> weapon = &( p -> off_hand_weapon );
      p -> off_hand_attack -> base_execute_time = p -> off_hand_weapon.swing_time;
    }

    trigger_gcd = 0;
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    p -> main_hand_attack -> schedule_execute();
    if ( p -> off_hand_attack )
    {
      p -> off_hand_attack -> schedule_execute();
    }
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs.moving -> check() ) return false;
    return( p -> main_hand_attack -> execute_event == 0 ); // not swinging
  }
};

// Bladestorm ===============================================================

struct bladestorm_tick_t : public warrior_attack_t
{
  bladestorm_tick_t( player_t* player ) :
      warrior_attack_t( "bladestorm", player, SCHOOL_PHYSICAL, TREE_ARMS, false )
  {
    warrior_t* p = player -> cast_warrior();

    id = 50622;
    parse_data( p -> player_data );
    
    if ( ! sim -> P403 )
      weapon_multiplier = 1.5; // HOTFIX: 150% weapon damage

    dual        = true;
    background  = true;
    may_crit    = true;
    aoe         = true;
    direct_tick = true;
  }

  virtual void assess_damage( double amount, int dmg_type )
  {
    warrior_attack_t::assess_damage( amount, dmg_type );

    // Assume it hits all nearby targets
    for ( int i=0; i < sim -> target -> adds_nearby && i < 4; i ++ )
    {
      warrior_attack_t::additional_damage( amount, dmg_type );
    }
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    tick_dmg = direct_dmg;
    update_stats( DMG_OVER_TIME );
  }
};

struct bladestorm_t : public warrior_attack_t
{
  attack_t* bladestorm_tick;

  bladestorm_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "bladestorm", player, SCHOOL_PHYSICAL, TREE_ARMS )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.bladestorm -> rank() );
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 46924;
    parse_data( p -> player_data );

    aoe       = true;
    harmful   = false;
    channeled = true;
    tick_zero = true;

    if ( p -> glyphs.bladestorm ) cooldown -> duration -= 15;

    bladestorm_tick = new bladestorm_tick_t( p );
  }
  
  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();
    if ( p -> main_hand_attack ) p -> main_hand_attack -> cancel();
    if ( p ->  off_hand_attack ) p -> off_hand_attack -> cancel();
  }

  virtual void tick()
  {
    if ( sim -> debug ) log_t::output( sim, "%s ticks (%d of %d)", name(), current_tick, num_ticks );

    bladestorm_tick -> weapon = &( player -> main_hand_weapon );
    bladestorm_tick -> execute();

    if ( bladestorm_tick -> result_is_hit() )
    {
      if ( player -> off_hand_weapon.type != WEAPON_NONE )
      {
        bladestorm_tick -> weapon = &( player -> off_hand_weapon );
        bladestorm_tick -> execute();
      }
    }

    update_time( DMG_OVER_TIME );
  }

  // Bladestorm not modified by haste effects
  virtual double haste() SC_CONST { return 1.0; }
};

// Bloodthirst ==============================================================

struct bloodthirst_t : public warrior_attack_t
{
  bloodthirst_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "bloodthirst",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();
    check_spec( TREE_FURY );

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 23881;
    parse_data( p -> player_data );

    weapon             = &( p -> main_hand_weapon );
    weapon_multiplier  = 0;
    player_multiplier *= 1.0 + p -> glyphs.bloodthirst * 0.10;
    direct_power_mod   = ( sim -> P403 ) ? 0.50 : 0.75; // HOTFIX 
    may_crit           = true;
    base_crit         += p -> talents.cruelty -> effect_base_value ( 1 ) / 100.0;
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    if( result_is_hit() )
    {
      warrior_t* p = player -> cast_warrior();
      p -> buffs_battle_trance -> trigger();
      trigger_bloodsurge( this );
    }
  }
};

// Cleave ===================================================================

struct cleave_t : public warrior_attack_t
{
  cleave_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "cleave",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    weapon = &( p -> main_hand_weapon );

    id = 845;
    parse_data( p -> player_data );

    aoe              = true;
    may_crit         = true;
    base_multiplier *= 1.0 + p -> talents.war_academy   -> effect_base_value( 1 ) / 100.0;
    base_multiplier *= 1.0 + p -> talents.thunderstruck -> effect_base_value( 1 ) / 100.0;
    direct_power_mod = 0.45;
    base_dd_min      = 6;
    base_dd_max      = 6;
  }

  virtual void assess_damage( double amount, int dmg_type )
  {
    warrior_attack_t::assess_damage( amount, dmg_type );
    warrior_t* p = player -> cast_warrior();

    for ( int i=0; i < sim -> target -> adds_nearby && i < ( 1 + p -> glyphs.cleaving ); i ++ )
    {
      warrior_attack_t::additional_damage( amount, dmg_type );
    }
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();    
    p -> buffs_meat_cleaver -> trigger();
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_meat_cleaver -> check() )
    {
      player_multiplier *= 1.0 + p -> talents.meat_cleaver -> rank() * 0.05 * p -> buffs_meat_cleaver -> stack();
    }
  }
};

// Colossus Smash ===========================================================

struct colossus_smash_t : public warrior_attack_t
{
  colossus_smash_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "colossus_smash",  player, SCHOOL_PHYSICAL, TREE_ARMS )
  {
    warrior_t* p = player -> cast_warrior();
    check_min_level( 81 );
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 86346;
    parse_data( p -> player_data );

    may_crit    = true;
    base_dd_min = 120;
    base_dd_max = 120;
    stancemask  = STANCE_BERSERKER | STANCE_BATTLE;
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();
    if( result_is_hit() )
      p -> buffs_colossus_smash -> trigger();
  }
};

// Concussion Blow ==========================================================

struct concussion_blow_t : public warrior_attack_t
{
  concussion_blow_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "concussion_blow",  player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.concussion_blow -> rank() );
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 12809;
    parse_data( p -> player_data );

    weapon            = &( p -> main_hand_weapon );
    weapon_multiplier = 0;
    direct_power_mod  = effect_base_value( 3 ) / 100.0;
    may_crit          = true;
  }
};

// Devastate ================================================================

struct devastate_t : public warrior_attack_t
{
  devastate_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "devastate",  player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.devastate -> rank() );
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 20243;
    parse_data( p -> player_data );

    may_crit   = true;
    base_crit += p -> talents.sword_and_board -> effect_base_value( 2 ) / 100.0
               + p -> glyphs.devastate * 0.05;
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();

    if ( result_is_hit() ) trigger_sword_and_board( this );

    if ( sim -> target -> health_percentage() <= 20 )
    {
      if ( p -> rng_impending_victory -> roll( p -> talents.impending_victory -> proc_chance() ) )
        p -> buffs_victory_rush -> trigger();
    }      
  }
};

// Execute ==================================================================

struct execute_t : public warrior_attack_t
{
  execute_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "execute",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 5308;
    parse_data( p -> player_data );

    weapon            = &( p -> main_hand_weapon );
    weapon_multiplier = 0;
    may_crit          = true;
    base_dd_min       = 10;
    base_dd_max       = 10;
    
    // Handling of additional scaling for additional consumed rage is handled in player_buff()
    direct_power_mod  = 0.25;

    // Execute consumes rage no matter if it missed or not
    aoe = true;

    stancemask = STANCE_BATTLE | STANCE_BERSERKER;
  }

  virtual double gcd() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_tier10_4pc_melee -> up() )
      return trigger_gcd - 0.5;

    return trigger_gcd;
  }

  virtual void consume_resource()
  {
    warrior_t* p = player -> cast_warrior();

    // Consumes base_cost + 20
    resource_consumed = std::min( p -> resource_current[ RESOURCE_RAGE ], 20.0 + cost() );
    
    if ( sim -> debug )
      log_t::output( sim, "%s consumes %.1f %s for %s", player -> name(),
                     resource_consumed, util_t::resource_type_string( resource ), name() );

    player -> resource_loss( resource, resource_consumed );

    stats -> consume_resource( resource_consumed );

    if ( p -> talents.sudden_death -> rank() )
    {
      double current_rage = p -> resource_current[ RESOURCE_RAGE ];
      double sudden_death_rage = p -> talents.sudden_death -> effect_base_value( 1 );

      if ( current_rage < sudden_death_rage )
      {
        p -> resource_gain( RESOURCE_RAGE, sudden_death_rage - current_rage, p -> gains_sudden_death ); // FIXME: Do we keep up to 10 or always at least 10?
      }
    }
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_lambs_to_the_slaughter -> expire();
    p -> buffs_tier10_4pc_melee -> decrement();
    if ( result_is_hit() && p -> rng_executioner_talent -> roll( p -> talents.executioner -> proc_chance() ) )
    {
      p -> buffs_executioner_talent -> trigger();
    }
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();

    // player_buff happens before consume_resource
    // so be we can savely check here how much excess rage we will spend
    double base_consumed = cost();
    double max_consumed = std::min( p -> resource_current[ RESOURCE_RAGE ], 20.0 + base_consumed );
    
    // Rage cost is done, convert the excessrage to damage
    // up to 50% AP for up to 20
    // 2.5%*AP ~ 1 excess_rage
    player_dd_adder = 0.025 * ( max_consumed - base_consumed ) * p -> composite_attack_power() -1;

    if ( p -> buffs_lambs_to_the_slaughter -> check() )
    {
      player_multiplier *= 1.0 + p -> talents.lambs_to_the_slaughter -> rank() * 0.10;
    }
  }

  virtual bool ready()
  {
    if ( ! warrior_attack_t::ready() )
      return false;

    if ( sim -> target -> health_percentage() > 20 )
      return false;

    return true;
  }
};

// Heroic Strike ============================================================

struct heroic_strike_t : public warrior_attack_t
{
  heroic_strike_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "heroic_strike",  player, SCHOOL_PHYSICAL, TREE_ARMS )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 78;
    parse_data( p -> player_data );

    may_crit          = true;
    base_crit        += p -> talents.incite -> effect_base_value( 1 ) / 100.0;
    base_multiplier  *= 1.0 + p -> talents.war_academy -> effect_base_value( 1 ) / 100.0;
    base_dd_min       = 8;
    base_dd_max       = 8;
    direct_power_mod  = 0.6;
    weapon            = &( p -> main_hand_weapon );
    weapon_multiplier = 0;
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    warrior_attack_t::execute();    
    if ( result == RESULT_CRIT )
    {
      if ( ! p -> buffs_incite -> check() )
        p -> buffs_incite -> trigger();
    }

    p -> buffs_incite -> expire();
  }
  
  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_incite -> check() ) player_crit += 1.0;
  }
};

// Mortal Strike ============================================================

struct mortal_strike_t : public warrior_attack_t
{
  mortal_strike_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "mortal_strike",  player, SCHOOL_PHYSICAL, TREE_ARMS )
  {
    warrior_t* p = player -> cast_warrior();
    check_spec( TREE_ARMS );
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 12294;
    parse_data( p -> player_data );
    
    may_crit                    = true;
    base_multiplier            *= 1.0 + p -> glyphs.mortal_strike * 0.10;
    base_crit_bonus_multiplier *= 1.0 + p -> talents.impale -> effect_base_value( 1 ) / 100.0;
    base_crit                  += p -> talents.cruelty -> effect_base_value ( 1 ) / 100.0;
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_lambs_to_the_slaughter -> expire();
    p -> buffs_lambs_to_the_slaughter -> trigger();
    p -> buffs_battle_trance -> trigger();
    if ( result == RESULT_CRIT && p -> rng_wrecking_crew -> roll( p -> talents.wrecking_crew -> proc_chance() ) )
    {
      double value = p -> talents.wrecking_crew -> rank() * 0.05;
      p -> buffs_wrecking_crew -> trigger( 1, value );
    }
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_lambs_to_the_slaughter -> check() )
    {
      player_multiplier *= 1.0 + p -> talents.lambs_to_the_slaughter -> rank() * 0.10;
    }
  }
};

// Overpower ================================================================

struct overpower_t : public warrior_attack_t
{
  overpower_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "overpower",  player, SCHOOL_PHYSICAL, TREE_ARMS )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 7384;
    parse_data( p -> player_data );

    may_crit   = true;
    may_dodge  = false;
    may_parry  = false;
    may_block  = false; // The Overpower cannot be blocked, dodged or parried.
    base_crit += p -> talents.taste_for_blood -> effect_base_value( 2 ) / 100.0;
    base_crit_bonus_multiplier *= 1.0 + p -> talents.impale -> effect_base_value( 1 ) / 100.0;
    player_multiplier          *= 1.0 + p -> glyphs.overpower * 0.10;

    stancemask = STANCE_BATTLE;    
  }
  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    // Track some information on what got us the overpower
    // Talents or lack of expertise
    p -> buffs_overpower -> up();
    p -> buffs_taste_for_blood -> up();
    warrior_attack_t::execute();
    p -> buffs_overpower -> expire();
    p -> buffs_lambs_to_the_slaughter -> expire();
    p -> buffs_taste_for_blood -> expire();
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_lambs_to_the_slaughter -> check() )
    {
      player_multiplier *= 1.0 + p -> talents.lambs_to_the_slaughter -> rank() * 0.10;
    }
  }

  virtual bool ready()
  {
    if ( ! warrior_attack_t::ready() )
      return false;

    warrior_t* p = player -> cast_warrior();

    if ( p -> buffs_overpower -> check() || p -> buffs_taste_for_blood -> check() )
      return true;

    return false;
  }
};

// Pummel ===================================================================

struct pummel_t : public warrior_attack_t
{
  pummel_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "pummel",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 6552;
    parse_data( p -> player_data );

    base_cost *= 1.0 + p -> talents.drums_of_war -> effect_base_value( 1 ) / 100.0;

    may_miss = may_resist = may_glance = may_block = may_dodge = may_crit = false;
  }

  virtual bool ready()
  {
    if ( ! sim -> target -> debuffs.casting -> check() ) return false;
    return warrior_attack_t::ready();
  }
};

// Raging Blow ==============================================================

struct raging_blow_t : public warrior_attack_t
{
  raging_blow_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "raging_blow",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.raging_blow -> rank() );

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 85288;
    parse_data( p -> player_data );

    may_crit   = true;
    base_crit += p -> glyphs.raging_blow * 0.05;
    stancemask = STANCE_BERSERKER;

    if ( ! sim -> P403 )
      weapon_multiplier *= 1.50; // HOTFIX  - 150% weapon damage
  }

  virtual void execute()
  {
    attack_t::consume_resource();
    warrior_t* p = player -> cast_warrior();

    weapon = &( player -> main_hand_weapon );
    warrior_attack_t::execute();

    if ( p -> off_hand_weapon.type != WEAPON_NONE )
    {
      weapon = &( player -> off_hand_weapon );
      warrior_attack_t::execute();
    }
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();
    if ( p -> mastery.unshackled_fury -> ok() )
    {
      player_multiplier *= 1.0 + p -> composite_mastery() * p -> mastery.unshackled_fury -> effect_base_value( 3 ) / 10000.0;
    }
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();
    if ( ! ( p -> buffs_death_wish -> check() || p -> buffs_enrage -> check() || p -> buffs_berserker_rage -> check() ) )
      return false;

    return warrior_attack_t::ready();
  }
};

// Rend =====================================================================

struct rend_t : public warrior_attack_t
{
  rend_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "rend",  player, SCHOOL_BLEED, TREE_ARMS )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 94009; // The action is 772, but the damage is stored in 94009
    parse_data( p -> player_data );

    base_cost              = 100.0; // Cost is stored in 772
    weapon                 = &( p -> main_hand_weapon );
    may_crit               = true;
    tick_may_crit          = true;
    tick_zero              = true;
    normalize_weapon_speed = false;
    scale_with_haste       = false;
    base_multiplier       *= 1.0 + p -> talents.thunderstruck -> effect_base_value( 1 ) / 100.0;
    if ( ! sim -> P403 )
      base_multiplier *= 1.5; // HOTFIX: Base damage increased by 50%
    stancemask             = STANCE_BATTLE | STANCE_DEFENSE;
  }

  virtual double calculate_direct_damage()
  {
    // Rend doesn't actually hit with the weapon, but ticks on application
    return 0.0;
  }

  virtual void execute()
  {
    base_td = base_td_init + calculate_weapon_damage() / 5.0;
    warrior_attack_t::execute();
    if ( result_is_hit() )
      trigger_blood_frenzy( this );
  }

  virtual void tick()
  {
    warrior_attack_t::tick();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_tier10_2pc_melee -> trigger();
    p -> buffs_taste_for_blood -> trigger();
  }
};

// Revenge ==================================================================

struct revenge_t : public warrior_attack_t
{
  revenge_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "revenge",  player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 6572;
    parse_data( p -> player_data );

    weapon            = &( p -> main_hand_weapon );
    weapon_multiplier = 0;
    direct_power_mod  = 0.31; // Assumption from 3.3.5
    may_crit          = true;
    base_multiplier  *= 1 + p -> talents.improved_revenge -> effect_base_value( 2 ) / 100.0
                          + p -> glyphs.revenge * 0.1;
    stancemask = STANCE_DEFENSE;
  }

  virtual void assess_damage( double amount, int dmg_type )
  {
    warrior_attack_t::assess_damage( amount, dmg_type );
    warrior_t* p = player -> cast_warrior();

    if ( p -> talents.improved_revenge -> rank() )
    {
      amount *= p -> talents.improved_revenge -> rank() * 0.50;
      warrior_attack_t::additional_damage( amount, dmg_type );
    }
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    warrior_attack_t::execute();
    p -> buffs_revenge -> expire();
    if ( result_is_hit() ) trigger_sword_and_board( this );
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();
    if ( ! p -> buffs_revenge -> check() ) return false;
    return warrior_attack_t::ready();
  }
};

// Shield Bash ==============================================================

struct shield_bash_t : public warrior_attack_t
{
  shield_bash_t( player_t* player, const std::string& options_str ) :
    warrior_attack_t( "shield_bash", player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 72;
    parse_data( p -> player_data );

    base_cost *= 1.0 + p -> talents.drums_of_war -> effect_base_value( 1 ) / 100.0;

    stancemask = STANCE_DEFENSE | STANCE_BATTLE;
  }

  virtual bool ready()
  {
    if ( ! sim -> target -> debuffs.casting -> check() ) return false;
    return warrior_attack_t::ready();
  }
};

// Shield Slam ==============================================================

struct shield_slam_t : public warrior_attack_t
{
  int sword_and_board;
  shield_slam_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "shield_slam",  player, SCHOOL_PHYSICAL, TREE_PROTECTION ),
      sword_and_board( 0 )
  {
    warrior_t* p = player -> cast_warrior();
    check_spec( TREE_PROTECTION );

    option_t options[] =
    {
      { "sword_and_board", OPT_BOOL, &sword_and_board },
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 23922;
    parse_data( p -> player_data );

    weapon            = &( p -> main_hand_weapon );
    weapon_multiplier = 0;
    direct_power_mod  = 0; // FIXME: What is this?
    may_crit          = true;
    base_crit        += p -> talents.cruelty -> effect_base_value ( 1 ) / 100.0;
    base_multiplier  *= 1.0  + ( 0.10 * p -> glyphs.shield_slam );
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();

    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_shield_block -> check() )
    {
      player_multiplier *= 1.0 + p -> talents.heavy_repercussions -> effect_base_value( 1 ) / 100.0;
    }
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    warrior_attack_t::execute();
    p -> buffs_sword_and_board -> expire();
    p -> buffs_battle_trance -> trigger();
  }

  virtual double cost() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_sword_and_board -> check() ) return 0;
    double c = warrior_attack_t::cost();
    return c;
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();

    if ( sword_and_board )
      if ( ! p -> buffs_sword_and_board -> check() )
        return false;

    return warrior_attack_t::ready();
  }
};

// Shockwave ================================================================

struct shockwave_t : public warrior_attack_t
{
  shockwave_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "shockwave",  player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.shockwave -> rank() );
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 46968;
    parse_data( p -> player_data );

    weapon            = &( p -> main_hand_weapon );
    weapon_multiplier = 0;
    direct_power_mod  = 0.75;
    may_crit          = true;
    may_dodge         = false;
    may_parry         = false;
    may_block         = false;
    if ( p -> glyphs.shockwave ) cooldown -> duration -= 3;
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_thunderstruck -> expire();
  }

  virtual void player_buff()
  {
    warrior_t* p = player -> cast_warrior();
    warrior_attack_t::player_buff();    
    player_multiplier *= 1.0 + p -> buffs_thunderstruck -> stack() * p -> talents.thunderstruck -> effect_base_value( 2 ) / 100.0;
  }
};

// Slam =====================================================================

struct slam_t : public warrior_attack_t
{
  int bloodsurge;
  slam_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "slam",  player, SCHOOL_PHYSICAL, TREE_FURY ),
      bloodsurge( 0 )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { "bloodsurge", OPT_BOOL, &bloodsurge },
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    static rank_t ranks[] =
    {
      { 85, 85, 277, 277, 0, 200 },
      { 84, 84, 272, 272, 0, 200 },
      { 83, 83, 266, 266, 0, 200 },
      { 82, 82, 261, 261, 0, 200 },
      { 81, 81, 255, 255, 0, 200 },
      { 80, 80, 250, 250, 0, 200 },
      { 0, 0, 0, 0, 0, 0 },
    };
    init_rank( ranks );
    // FIXME: Scaling data is stored in effect 462, but not parsed automatically

    id = 1464;
    parse_data( p -> player_data );

    weapon                      = &( p -> main_hand_weapon );
    normalize_weapon_speed      = false;
    may_crit                    = true;
    base_crit                  += p -> glyphs.slam * 0.05;
    base_crit_bonus_multiplier *= 1.0 + p -> talents.impale      -> effect_base_value( 1 ) / 100.0;
    base_execute_time          += p -> talents.improved_slam     -> effect_base_value( 1 ) / 1000.0;
    base_multiplier            *= 1 + p -> talents.improved_slam -> effect_base_value( 2 ) / 100.0
                                    + p -> talents.war_academy   -> effect_base_value( 1 ) / 100.0;
    if ( ! sim -> P403 )
      weapon_multiplier *= 1.50; // HOTFIX  - 150% weapon damage
  }

  virtual double gcd() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_tier10_4pc_melee -> up() )
      return trigger_gcd - 0.5;

    return trigger_gcd;
  }

  virtual double haste() SC_CONST
  {
    // No haste for slam cast?
    return 1.0;
  }

  virtual double cost() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    if ( ! sim -> P403 ) // HOTFIX - Bloodsurge is now instant and free
    {
      if ( p -> buffs_bloodsurge -> check() )
        return 0;
    }
    return warrior_attack_t::cost();
  }

  virtual double execute_time() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_bloodsurge -> check() )
      return 0.0;
    else
      return warrior_attack_t::execute_time();
  }

  virtual void consume_resource() { }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    
    p -> buffs_bloodsurge -> decrement();
    p -> buffs_tier10_4pc_melee -> decrement();

    // MH hit
    weapon = &( player -> main_hand_weapon );
    warrior_attack_t::execute();

    if ( p -> talents.single_minded_fury -> rank() && p -> off_hand_weapon.type != WEAPON_NONE )
    {
      weapon = &( player -> off_hand_weapon );
      warrior_attack_t::execute();
    }

    warrior_attack_t::consume_resource();
  }

  virtual bool ready()
  {
    if ( ! warrior_attack_t::ready() )
      return false;

    warrior_t* p = player -> cast_warrior();

    if ( bloodsurge )
    {
      // Player does not instantaneous become aware of the proc
      if ( ! p -> buffs_bloodsurge -> may_react() )
        return false;
    }

    return true;
  }
};

// Thunder Clap =============================================================

struct thunder_clap_t : public warrior_attack_t
{
  thunder_clap_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "thunder_clap",  player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 6343;
    parse_data( p -> player_data );

    weapon = &( p -> main_hand_weapon );
    weapon_multiplier = 0;

    aoe               = true;
    may_crit          = true;
    may_dodge         = false;
    may_parry         = false;
    may_block         = false;
    direct_power_mod  = 0.12; // FIXME: Is this correct?
    base_multiplier  *= 1.0 + p -> talents.thunderstruck -> effect_base_value( 1 ) / 100.0;
    base_crit        += p -> talents.incite -> effect_base_value( 1 ) / 100.0;
    base_cost        -= p -> glyphs.resonating_power  * 5.0;
  }

  virtual void execute()
  {
    warrior_attack_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_thunderstruck -> trigger();
  }
};

// Whirlwind ================================================================

struct whirlwind_t : public warrior_attack_t
{
  whirlwind_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "whirlwind",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 1680;
    parse_data( p -> player_data );

    aoe               = true;
    may_crit          = true;
    stancemask        = STANCE_BERSERKER;
  }

  virtual void consume_resource() { }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();

    // MH hit
    weapon = &( player -> main_hand_weapon );
    warrior_attack_t::execute();

    if ( p -> off_hand_weapon.type != WEAPON_NONE )
    {
      weapon = &( player -> off_hand_weapon );
      warrior_attack_t::execute();
    }

    p -> buffs_meat_cleaver -> trigger();

    warrior_attack_t::consume_resource();
  }

  virtual void player_buff()
  {
    warrior_attack_t::player_buff();
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_meat_cleaver -> check() )
    {
      player_multiplier *= 1.0 + p -> talents.meat_cleaver -> rank() * 0.05 * p -> buffs_meat_cleaver -> stack();
    }
  }
};

// Victory Rush =============================================================

struct victory_rush_t : public warrior_attack_t
{
  victory_rush_t( player_t* player, const std::string& options_str ) :
      warrior_attack_t( "victory_rush",  player, SCHOOL_PHYSICAL, TREE_FURY )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 34428;
    parse_data( p -> player_data );

    weapon           = &( p -> main_hand_weapon );
    direct_power_mod = 0.45;
    may_crit         = true;
    base_multiplier *= 1.0 + p -> talents.war_academy -> effect_base_value( 1 ) / 100.0;
  }

  virtual bool ready()
  {
     warrior_t* p = player -> cast_warrior();
    if ( ! p -> buffs_victory_rush -> check() )
      return false;

    return warrior_attack_t::ready();
  }
};

// ==========================================================================
// Warrior Spells
// ==========================================================================

struct warrior_spell_t : public spell_t
{
  double min_rage, max_rage;
  int stancemask;
  warrior_spell_t( const char* n, player_t* player, const school_type s=SCHOOL_PHYSICAL, int t=TREE_NONE ) :
      spell_t( n, player, RESOURCE_RAGE, s, t ),
      min_rage( 0 ), max_rage( 0 ),
      stancemask( STANCE_BATTLE|STANCE_BERSERKER|STANCE_DEFENSE )
  {}

  virtual double cost() SC_CONST;
  virtual double gcd() SC_CONST;
  virtual void   parse_options( option_t*, const std::string& options_str );
  virtual bool   ready();
};

// warrior_spell_t::cost ====================================================

double warrior_spell_t::cost() SC_CONST
{
  double c = spell_t::cost() / 10; // Rage Costs are stored as * 10;
  return c;
}

// warrior_spell_t::gcd =====================================================

double warrior_spell_t::gcd() SC_CONST
{
  // Unaffected by haste
  return trigger_gcd;
}

// warrior_spell_t::ready() =================================================

bool warrior_spell_t::ready()
{
  if ( ! spell_t::ready() )
    return false;

  warrior_t* p = player -> cast_warrior();

  if ( min_rage > 0 )
    if ( p -> resource_current[ RESOURCE_RAGE ] < min_rage )
      return false;

  if ( max_rage > 0 )
    if ( p -> resource_current[ RESOURCE_RAGE ] > max_rage )
      return false;

  // Attack vailable in current stance?
  if ( ( stancemask & p -> active_stance ) == 0 )
    return false;

  return true;
}

// warrior_spell_t::parse_options ===========================================

void warrior_spell_t::parse_options( option_t*          options,
                                     const std::string& options_str )
{
  option_t base_options[] =
  {
    { "min_rage",       OPT_FLT, &min_rage       },
    { "max_rage",       OPT_FLT, &max_rage       },
    { "rage>",          OPT_FLT, &min_rage       },
    { "rage<",          OPT_FLT, &max_rage       },
    { NULL, OPT_UNKNOWN, NULL }
  };
  std::vector<option_t> merged_options;
  spell_t::parse_options( merge_options( merged_options, options, base_options ), options_str );
}

// Battle Shout =============================================================

struct battle_shout_t : public warrior_spell_t
{
  double rage_gain;

  float refresh_early;
  int   shout_base_bonus;
  battle_shout_t( player_t* player, const std::string& options_str ) :
      warrior_spell_t( "battle_shout", player ),
      refresh_early( 0.0 ),
      shout_base_bonus( 0 )
  {
    warrior_t* p = player -> cast_warrior();

    id = 6673;
    parse_data( p -> player_data );

    harmful   = false;
    rage_gain = 20 + p -> talents.booming_voice -> effect_base_value( 2 ) / 10.0;
    cooldown -> duration += p -> talents.booming_voice -> effect_base_value( 1 ) / 1000.0;
  }
  
  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    
    if ( ! sim -> overrides.battle_shout )
      sim -> auras.battle_shout -> buff_duration = 120 + p -> glyphs.battle * 120;
    sim -> auras.battle_shout -> trigger( 1, 1395 );

    p -> resource_gain( RESOURCE_RAGE, rage_gain , p -> gains_battle_shout );
  }
};

// Berserker Rage ===========================================================

struct berserker_rage_t : public warrior_spell_t
{
  berserker_rage_t( player_t* player, const std::string& options_str ) :
      warrior_spell_t( "berserker_rage", player )
  {
    warrior_t* p = player -> cast_warrior();

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 18499;
    parse_data( p -> player_data );

    harmful = false;
    if ( p -> talents.intensify_rage -> rank() )
      cooldown -> duration *= ( 1.0 + p -> talents.intensify_rage -> effect_base_value( 1 ) / 100.0 );
  }

  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    if ( sim -> log ) log_t::output( sim, "%s performs %s", p -> name(), name() );  
    if ( p -> glyphs.berserker_rage )
      p -> resource_gain( RESOURCE_RAGE, 5.0, p -> gains_berserker_rage );
    p -> buffs_berserker_rage -> trigger();
  }
};

// Deadly Calm ==============================================================

struct deadly_calm_t : public warrior_spell_t
{
  deadly_calm_t( player_t* player, const std::string& options_str ) :
    warrior_spell_t( "deadly_calm", player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.deadly_calm -> rank() );

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 85730;
    parse_data( p -> player_data );

    harmful = false;
  }

  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    if ( sim -> log ) log_t::output( sim, "%s performs %s", p -> name(), name() );    
    p -> buffs_deadly_calm -> trigger();  
    update_ready();
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> buffs_inner_rage -> check() )
      return false;

    return warrior_spell_t::ready();
  }
};

// Death Wish ===============================================================

struct death_wish_t : public warrior_spell_t
{
  double enrage_bonus;

  death_wish_t( player_t* player, const std::string& options_str ) :
      warrior_spell_t( "death_wish", player )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.death_wish -> rank() );

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 12292;
    parse_data( p -> player_data );

    harmful = false;
    if ( p -> talents.intensify_rage -> rank() )
      cooldown -> duration *= ( 1.0 + p -> talents.intensify_rage -> effect_base_value( 1 ) / 100.0 );

    enrage_bonus = 0.20;
    if ( p -> mastery.unshackled_fury -> ok() )
      enrage_bonus *= p -> composite_mastery() * p -> mastery.unshackled_fury -> effect_base_value( 3 ) / 10000.0; 
  }

  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_death_wish -> trigger( 1, enrage_bonus );
  }
};

// Inner Rage ===============================================================

struct inner_rage_t : public warrior_spell_t
{
  inner_rage_t( player_t* player, const std::string& options_str ) :
    warrior_spell_t( "inner_rage", player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    check_min_level( 83 );

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 1134;
    parse_data( p -> player_data );
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();
    if ( sim -> log ) log_t::output( sim, "%s performs %s", p -> name(), name() );    
    p -> buffs_inner_rage -> trigger();  
    update_ready();
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();
    if ( p -> resource_current[ RESOURCE_RAGE ] < 75.0 )
      return false;

    return warrior_spell_t::ready();
  }
};

// Recklessness =============================================================

struct recklessness_t : public warrior_spell_t
{
  recklessness_t( player_t* player, const std::string& options_str ) :
      warrior_spell_t( "recklessness", player )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 1719;
    parse_data( p -> player_data );

    harmful = false;
    if ( p -> talents.intensify_rage -> rank() )
      cooldown -> duration *= ( 1.0 + p -> talents.intensify_rage -> effect_base_value( 1 ) / 100.0 );

    stancemask  = STANCE_BERSERKER;
  }

  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_recklessness -> trigger( 3 );
  }
};

// Shield Block =============================================================

struct shield_block_t : public warrior_spell_t
{
  shield_block_t( player_t* player, const std::string& options_str ) :
      warrior_spell_t( "shield_block", player )
  {
    warrior_t* p = player -> cast_warrior();
    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 2565;
    parse_data( p -> player_data );

    harmful = false;
    if ( p -> talents.shield_mastery -> rank() )
      cooldown -> duration += p -> talents.shield_mastery -> effect_base_value( 1 ) / 1000.0;
  }

  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    p -> buffs_shield_block -> trigger();
  }
};

// Stance ===================================================================

struct stance_t : public warrior_spell_t
{
  int switch_to_stance;
  stance_t( player_t* player, const std::string& options_str ) :
      warrior_spell_t( "stance", player ), switch_to_stance( 0 )
  {
    //warrior_t* p = player -> cast_warrior();

    std::string stance_str;
    option_t options[] =
    {
      { "choose",  OPT_STRING, &stance_str     },
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    if ( ! stance_str.empty() )
    {
      if ( stance_str == "battle" )
        switch_to_stance = STANCE_BATTLE;
      else if ( stance_str == "berserker" || stance_str == "zerker" )
        switch_to_stance = STANCE_BERSERKER;
      else if ( stance_str == "def" || stance_str == "defensive" )
        switch_to_stance = STANCE_DEFENSE;
    }
    else
    {
      // Default to Battle Stance
      switch_to_stance = STANCE_BATTLE;
    }

    harmful = false;
    base_cost   = 0;
    trigger_gcd = 0;
    cooldown -> duration = 1.0;
  }

  virtual void execute()
  {
    warrior_t* p = player -> cast_warrior();

    switch ( p -> active_stance )
    {
      case STANCE_BATTLE:     p -> buffs_battle_stance    -> expire(); break;
      case STANCE_BERSERKER:  p -> buffs_berserker_stance -> expire(); break;
      case STANCE_DEFENSE:    p -> buffs_defensive_stance -> expire(); break;
    }
    p -> active_stance = switch_to_stance;

    switch ( p -> active_stance )
    {
      case STANCE_BATTLE:     p -> buffs_battle_stance    -> trigger(); break;
      case STANCE_BERSERKER:  p -> buffs_berserker_stance -> trigger(); break;
      case STANCE_DEFENSE:    p -> buffs_defensive_stance -> trigger(); break;
    }
    consume_resource();

    update_ready();
  }

  virtual double cost() SC_CONST
  {
    warrior_t* p = player -> cast_warrior();
    double c = p -> resource_current [ RESOURCE_RAGE ];
    c -= 25.0; // Stance Mastery
    if ( p -> talents.tactical_mastery -> rank() )
      c -= p -> talents.tactical_mastery -> effect_base_value( 1 );
    if ( c < 0 ) c = 0;
    return c;
  }

  virtual bool ready()
  {
    warrior_t* p = player -> cast_warrior();

    if ( ! warrior_spell_t::ready() )
      return false;

    return p -> active_stance != switch_to_stance;
  }
};

// Sweeping Strikes =========================================================

struct sweeping_strikes_t : public warrior_spell_t
{
  sweeping_strikes_t( player_t* player, const std::string& options_str ) :
    warrior_spell_t( "sweeping_strikes", player, SCHOOL_PHYSICAL, TREE_PROTECTION )
  {
    warrior_t* p = player -> cast_warrior();
    check_talent( p -> talents.sweeping_strikes -> rank() );

    option_t options[] =
    {
      { NULL, OPT_UNKNOWN, NULL }
    };
    parse_options( options, options_str );

    id = 12328;
    parse_data( p -> player_data );

    base_cost *= 1.0 - p -> glyphs.sweeping_strikes * 1.0;

    stancemask = STANCE_BERSERKER | STANCE_BATTLE;
  }

  virtual void execute()
  {
    warrior_spell_t::execute();
    warrior_t* p = player -> cast_warrior();
    if ( sim -> log ) log_t::output( sim, "%s performs %s", p -> name(), name() );    
    p -> buffs_sweeping_strikes -> trigger();  
    update_ready();
  }
};

} // ANONYMOUS NAMESPACE ====================================================

// ==========================================================================
// Warrior Character Definition
// ==========================================================================

// warrior_t::create_action  ================================================

action_t* warrior_t::create_action( const std::string& name,
                                    const std::string& options_str )
{
  if ( name == "auto_attack"      ) return new auto_attack_t     ( this, options_str );
  if ( name == "battle_shout"     ) return new battle_shout_t    ( this, options_str );
  if ( name == "berserker_rage"   ) return new berserker_rage_t  ( this, options_str );
  if ( name == "bladestorm"       ) return new bladestorm_t      ( this, options_str );
  if ( name == "bloodthirst"      ) return new bloodthirst_t     ( this, options_str );
  if ( name == "cleave"           ) return new cleave_t          ( this, options_str );
  if ( name == "colossus_smash"   ) return new colossus_smash_t  ( this, options_str );
  if ( name == "concussion_blow"  ) return new concussion_blow_t ( this, options_str );
  if ( name == "deadly_calm"      ) return new deadly_calm_t     ( this, options_str );
  if ( name == "death_wish"       ) return new death_wish_t      ( this, options_str );
  if ( name == "devastate"        ) return new devastate_t       ( this, options_str );
  if ( name == "execute"          ) return new execute_t         ( this, options_str );
  if ( name == "heroic_strike"    ) return new heroic_strike_t   ( this, options_str );
  if ( name == "inner_rage"       ) return new inner_rage_t      ( this, options_str );
  if ( name == "mortal_strike"    ) return new mortal_strike_t   ( this, options_str );
  if ( name == "overpower"        ) return new overpower_t       ( this, options_str );
  if ( name == "pummel"           ) return new pummel_t          ( this, options_str );
  if ( name == "raging_blow"      ) return new raging_blow_t     ( this, options_str );
  if ( name == "recklessness"     ) return new recklessness_t    ( this, options_str );
  if ( name == "rend"             ) return new rend_t            ( this, options_str );
  if ( name == "revenge"          ) return new revenge_t         ( this, options_str );
  if ( name == "shield_bash"      ) return new shield_bash_t     ( this, options_str );
  if ( name == "shield_block"     ) return new shield_block_t    ( this, options_str );
  if ( name == "shield_slam"      ) return new shield_slam_t     ( this, options_str );
  if ( name == "shockwave"        ) return new shockwave_t       ( this, options_str );
  if ( name == "slam"             ) return new slam_t            ( this, options_str );
  if ( name == "stance"           ) return new stance_t          ( this, options_str );
  if ( name == "sweeping_strikes" ) return new sweeping_strikes_t( this, options_str);
  if ( name == "thunder_clap"     ) return new thunder_clap_t    ( this, options_str );
  if ( name == "victory_rush"     ) return new victory_rush_t    ( this, options_str );
  if ( name == "whirlwind"        ) return new whirlwind_t       ( this, options_str );

  return player_t::create_action( name, options_str );
}

// warrior_t::init_talents ==================================================

void warrior_t::init_talents()
{
  // Talents

  // Arms
  talents.bladestorm              = new talent_t( this, "bladestorm", "Bladestorm" );
  talents.blood_frenzy            = new talent_t( this, "blood_frenzy", "Blood Frenzy" );
  talents.deadly_calm             = new talent_t( this, "deadly_calm", "Deadly Calm" );
  talents.deep_wounds             = new talent_t( this, "deep_wounds", "Deep Wounds" );
  talents.drums_of_war            = new talent_t( this, "drums_of_war", "Drums of War" );
  talents.impale                  = new talent_t( this, "impale", "Impale" );
  talents.improved_slam           = new talent_t( this, "improved_slam", "Improved Slam" );
  talents.lambs_to_the_slaughter  = new talent_t( this, "lambs_to_the_slaughter", "Lambs to the Slaughter" );
  talents.sudden_death            = new talent_t( this, "sudden_death", "Sudden Death" );
  talents.sweeping_strikes        = new talent_t( this, "sweeping_strikes", "Sweeping Strikes" );
  talents.tactical_mastery        = new talent_t( this, "tactical_mastery", "Tactical Mastery" );
  talents.taste_for_blood         = new talent_t( this, "taste_for_blood", "Taste for Blood" );
  talents.war_academy             = new talent_t( this, "war_academy", "War Academy" );
  talents.wrecking_crew           = new talent_t( this, "wrecking_crew", "Wrecking Crew" );

  // Fury
  talents.battle_trance           = new talent_t( this, "battle_trance", "Battle Trance" );
  talents.bloodsurge              = new talent_t( this, "bloodsurge", "Bloodsurge" );
  talents.booming_voice           = new talent_t( this, "booming_voice", "Booming Voice" );
  talents.cruelty                 = new talent_t( this, "cruelty", "Cruelty" );
  talents.death_wish              = new talent_t( this, "death_wish", "Death Wish" );
  talents.enrage                  = new talent_t( this, "enrage", "Enrage" );
  talents.executioner             = new talent_t( this, "executioner", "Executioner" );
  talents.flurry                  = new talent_t( this, "flurry", "Flurry" );
  talents.gag_order               = new talent_t( this, "gag_order", "Gag Order" );
  talents.intensify_rage          = new talent_t( this, "intensify_rage", "Intensify Rage" );
  talents.meat_cleaver            = new talent_t( this, "meat_cleaver", "Meat Cleaver" );
  talents.raging_blow             = new talent_t( this, "raging_blow", "Raging Blow" );
  talents.rampage                 = new talent_t( this, "rampage", "Rampage" );
  talents.rude_interruption       = new talent_t( this, "rude_interruption", "Rude Interruption" );
  talents.single_minded_fury      = new talent_t( this, "single_minded_fury", "Single-Minded Fury" );
  talents.titans_grip             = new talent_t( this, "titans_grip", "Titan's Grip" );

  // Prot
  talents.bastion_of_defense      = new talent_t( this, "bastion_of_defense", "Bastion of Defense" );
  talents.concussion_blow         = new talent_t( this, "concussion_blow", "Concussion Blow" );
  talents.devastate               = new talent_t( this, "devastate", "Devastate" );
  talents.heavy_repercussions     = new talent_t( this, "heavy_repercussions", "Heavy Repercussions" );
  talents.hold_the_line           = new talent_t( this, "hold_the_line", "Hold the Line" );
  talents.impending_victory       = new talent_t( this, "impending_victory", "Impending Victory" );
  talents.improved_revenge        = new talent_t( this, "improved_revenge", "Improved Revenge" );
  talents.incite                  = new talent_t( this, "incite", "Incite" );
  talents.shockwave               = new talent_t( this, "shockwave", "Shockwave" );
  talents.shield_mastery          = new talent_t( this, "shield_mastery", "Shield Mastery" );
  talents.shield_specialization   = new talent_t( this, "shield_specialization", "Shield Specialization" );
  talents.sword_and_board         = new talent_t( this, "sword_and_board", "Sword and Board" );
  talents.toughness               = new talent_t( this, "toughness", "Toughness" );
  talents.thunderstruck           = new talent_t( this, "thunderstruck", "Thunderstruck" );

  player_t::init_talents();
}

// warrior_t::init_spells ==================================================

void warrior_t::init_spells()
{
  player_t::init_spells();

  // Active Spells
  active_spells.battle_shout      = new active_spell_t( this, "battle_shout", "Battle Shout", WARRIOR_FURY );
  active_spells.berserker_rage    = new active_spell_t( this, "berserker_rage", "Berserker Rage", WARRIOR_FURY );
  active_spells.bladestorm        = new active_spell_t( this, "bladestorm", "Bladestorm", WARRIOR_ARMS );
  active_spells.bloodthirst       = new active_spell_t( this, "bloodthirst", "Bloodthirst", WARRIOR_FURY );
  active_spells.cleave            = new active_spell_t( this, "cleave", "Cleave", WARRIOR_FURY );
  active_spells.colossus_smash    = new active_spell_t( this, "colossus_smash", "Colossus Smash", WARRIOR_ARMS );
  active_spells.concussion_blow   = new active_spell_t( this, "concussion_blow", "Concussion Blow", WARRIOR_PROTECTION );
  active_spells.deadly_calm       = new active_spell_t( this, "deadly_calm", "Deadly Calm", WARRIOR_ARMS );
  active_spells.death_wish        = new active_spell_t( this, "death_wish", "Death Wish", WARRIOR_FURY );
  active_spells.devastate         = new active_spell_t( this, "devastate", "Devastate", WARRIOR_PROTECTION );
  active_spells.execute           = new active_spell_t( this, "execute", "Execute", WARRIOR_FURY );
  active_spells.heroic_strike     = new active_spell_t( this, "heroic_strike", "Heroic Strike", WARRIOR_ARMS );
  active_spells.inner_rage        = new active_spell_t( this, "inner_rage", "Inner Rage", WARRIOR_FURY );
  active_spells.mortal_strike     = new active_spell_t( this, "mortal_strike", "Mortal Strike", WARRIOR_ARMS );
  active_spells.overpower         = new active_spell_t( this, "overpower", "Overpower", WARRIOR_ARMS );
  active_spells.pummel            = new active_spell_t( this, "pummel", "Pummel", WARRIOR_FURY );
  active_spells.raging_blow       = new active_spell_t( this, "raging_blow", "Raging Blow", WARRIOR_FURY );
  active_spells.recklessness      = new active_spell_t( this, "recklessness", "Recklessness", WARRIOR_FURY );
  active_spells.rend              = new active_spell_t( this, "rend", "Rend", WARRIOR_ARMS );
  active_spells.revenge           = new active_spell_t( this, "revenge", "Revenge", WARRIOR_PROTECTION );
  active_spells.shield_bash       = new active_spell_t( this, "shield_bash", "Shield Bash", WARRIOR_PROTECTION );
  active_spells.shield_block      = new active_spell_t( this, "shield_block", "Shield Block", WARRIOR_PROTECTION );
  active_spells.shield_slam       = new active_spell_t( this, "shield_slam", "Shield Slam", WARRIOR_PROTECTION );
  active_spells.shockwave         = new active_spell_t( this, "shockwave", "Shockwave", WARRIOR_PROTECTION );
  active_spells.slam              = new active_spell_t( this, "slam", "Slam", WARRIOR_FURY );
  active_spells.sweeping_strikes  = new active_spell_t( this, "sweeping_strikes", "Sweeping Strikes", WARRIOR_ARMS );
  active_spells.thunder_clap      = new active_spell_t( this, "thunder_clap", "Thunder Clap", WARRIOR_ARMS );
  active_spells.victory_rush      = new active_spell_t( this, "victory_rush", "Victory Rush", WARRIOR_FURY );
  active_spells.whirlwind         = new active_spell_t( this, "whirlwind", "Whirlwind", WARRIOR_FURY );

  // Mastery
  mastery.critical_block         = new passive_spell_t( this, "critical_block",         76857, WARRIOR_PROTECTION );
  mastery.strikes_of_opportunity = new passive_spell_t( this, "strikes_of_opportunity", 76838, WARRIOR_ARMS );
  mastery.unshackled_fury        = new passive_spell_t( this, "unshackled_fury",        76856, WARRIOR_FURY );

  // Spec Passives
  spec.anger_management                 = new passive_spell_t( this, "anger_management",                 12296, WARRIOR_ARMS );
  spec.dual_wield_specialization        = new passive_spell_t( this, "dual_wield_specialization",        23588, WARRIOR_FURY );
  spec.precision                        = new passive_spell_t( this, "precision",                        29592, WARRIOR_FURY );
  spec.sentinel                         = new passive_spell_t( this, "sentinel",                         29144, WARRIOR_PROTECTION );
  spec.two_handed_weapon_specialization = new passive_spell_t( this, "two_handed_weapon_specialization", 12712, WARRIOR_ARMS );
}

// warrior_t::init_glyphs ===================================================

void warrior_t::init_glyphs()
{
  memset( ( void* ) &glyphs, 0x0, sizeof( glyphs_t ) );

  std::vector<std::string> glyph_names;
  int num_glyphs = util_t::string_split( glyph_names, glyphs_str, ",/" );

  for ( int i=0; i < num_glyphs; i++ )
  {
    std::string& n = glyph_names[ i ];

    if      ( n == "battle"           ) glyphs.battle = 1;
    else if ( n == "berserker_rage"   ) glyphs.berserker_rage = 1;
    else if ( n == "bladestorm"       ) glyphs.bladestorm = 1;
    else if ( n == "bloodthirst"      ) glyphs.bloodthirst = 1;
    else if ( n == "cleaving"         ) glyphs.cleaving = 1;
    else if ( n == "devastate"        ) glyphs.devastate = 1;
    else if ( n == "enduring_victory" ) glyphs.enduring_victory = 1;
    else if ( n == "mortal_strike"    ) glyphs.mortal_strike = 1;
    else if ( n == "overpower"        ) glyphs.overpower = 1;
    else if ( n == "raging_blow"      ) glyphs.raging_blow = 1;
    else if ( n == "resonating_power" ) glyphs.resonating_power = 1;
    else if ( n == "revenge"          ) glyphs.revenge = 1;
    else if ( n == "shield_slam"      ) glyphs.shield_slam = 1;
    else if ( n == "shockwave"        ) glyphs.shockwave = 1;
    else if ( n == "slam"             ) glyphs.slam = 1;
    else if ( n == "sweeping_strikes" ) glyphs.sweeping_strikes = 1;
    // To prevent warnings....
    else if ( n == "bloody_healing"     ) ;
    else if ( n == "command"            ) ;
    else if ( n == "demoralizing_shout" ) ;
    else if ( n == "furious_sundering"  ) ;
    else if ( n == "hamstring"          ) ;
    else if ( n == "heroic_throw"       ) ;
    else if ( n == "intervene"          ) ;
    else if ( n == "intimidating_shout" ) ;
    else if ( n == "long_charge"        ) ;
    else if ( n == "rapid_charge"       ) ;
    else if ( n == "spell_reflection"   ) ;
    else if ( n == "sunder_armor"       ) ;
    else if ( n == "thunder_clap"       ) ;
    else if ( ! sim -> parent ) 
    {
      sim -> errorf( "Player %s has unrecognized glyph %s\n", name(), n.c_str() );
    }
  }
}

// warrior_t::init_race =====================================================

void warrior_t::init_race()
{
  race = util_t::parse_race_type( race_str );
  switch ( race )
  {
    case RACE_DRAENEI:
    case RACE_DWARF:
    case RACE_HUMAN:
    case RACE_NIGHT_ELF:
    case RACE_GNOME:
    case RACE_GOBLIN:
    case RACE_ORC:
    case RACE_TAUREN:
    case RACE_TROLL:
    case RACE_WORGEN:
    case RACE_UNDEAD:
      break;
    default:
      race = RACE_NIGHT_ELF;
      race_str = util_t::race_type_string( race );
  }

  player_t::init_race();
}

// warrior_t::init_base =====================================================

void warrior_t::init_base()
{
  player_t::init_base();

  resource_base[  RESOURCE_RAGE  ] = 100;

  initial_attack_power_per_strength = 2.0;
  initial_attack_power_per_agility  = 0.0;

  base_attack_power = level * 2 + 60;

  // FIXME! Level-specific!
  base_defense = level * 5;
  base_miss    = 0.05;
  base_dodge   = 0.03664;
  base_parry   = 0.05;
  base_block   = 0.05;

  if ( mastery.critical_block -> ok() )
  {
    base_block += composite_mastery() * mastery.critical_block -> effect_base_value( 3 ) / 10000.0;
  }

  if ( talents.toughness -> rank() )
    initial_armor_multiplier *= 1.0 + talents.toughness -> effect_base_value( 1 ) / 100.0;
  initial_dodge_per_agility = 0.0001180;
  initial_armor_per_agility = 2.0;

  diminished_kfactor    = 0.9560;
  diminished_miss_capi  = 1.0 / 0.16;
  diminished_dodge_capi = 1.0 / 0.88129021;
  diminished_parry_capi = 1.0 / 0.47003525;

  if ( spec.sentinel -> ok() )
  {
    attribute_multiplier_initial[ ATTR_STAMINA ] *= 1.0  + spec.sentinel -> effect_base_value( 1 ) / 100.0;
    base_block += spec.sentinel -> effect_base_value( 3 ) / 100.0;
  }

  health_per_stamina = 10;

  base_gcd = 1.5;

  if ( tank == -1 && primary_tree() == TREE_PROTECTION ) tank = 1;
}

// warrior_t::init_scaling ==================================================

void warrior_t::init_scaling()
{
  player_t::init_scaling();

  if ( talents.single_minded_fury -> rank() || talents.titans_grip -> rank() )
  {
    scales_with[ STAT_WEAPON_OFFHAND_DPS    ] = 1;
    scales_with[ STAT_WEAPON_OFFHAND_SPEED  ] = 1;
  }
}

// warrior_t::init_buffs ====================================================

void warrior_t::init_buffs()
{
  player_t::init_buffs();

  // buff_t( sim, name, max_stack, duration, cooldown, proc_chance, quiet )
  buffs_bastion_of_defense        = new buff_t( this, "bastion_of_defense",        1, 12.0,   0, talents.bastion_of_defense -> proc_chance() );
  buffs_battle_stance             = new buff_t( this, "battle_stance"    );
  buffs_battle_trance             = new buff_t( this, "battle_trance",             1, 15.0,   0, talents.battle_trance -> proc_chance() );
  buffs_berserker_rage            = new buff_t( this, "berserker_rage",            1, 10.0 );
  buffs_berserker_stance          = new buff_t( this, "berserker_stance" );
  buffs_bloodsurge                = new buff_t( this, "bloodsurge",                2,  5.0,   0, talents.bloodsurge -> proc_chance() );
  buffs_colossus_smash            = new buff_t( this, "colossus_smash",            1,  6.0 );
  buffs_deadly_calm               = new buff_t( this, "deadly_calm",               1, 10.0 );
  buffs_death_wish                = new buff_t( this, "death_wish",                1, 30.0 );
  buffs_defensive_stance          = new buff_t( this, "defensive_stance" );
  buffs_enrage                    = new buff_t( this, "enrage",                    1,  9.0,   0, talents.enrage -> proc_chance() );
  buffs_executioner_talent        = new buff_t( this, "executioner_talent",        5,  9.0 );
  buffs_flurry                    = new buff_t( this, "flurry",                    3, 15.0,   0, talents.flurry -> proc_chance() );
  buffs_hold_the_line             = new buff_t( this, "hold_the_line",             1,  5.0 * talents.hold_the_line -> rank() ); 
  buffs_incite                    = new buff_t( this, "incite",                    1, 10.0, 6.0, talents.incite -> proc_chance() );
  buffs_inner_rage                = new buff_t( this, "inner_rage",                1, 15.0 );
  buffs_overpower                 = new buff_t( this, "overpower",                 1,  6.0, 1.0 );
  buffs_lambs_to_the_slaughter    = new buff_t( this, "lambs_to_the_slaughter",    1, 15.0,  0, talents.lambs_to_the_slaughter -> proc_chance() );
  buffs_meat_cleaver              = new buff_t( this, "meat_cleaver",              3, 10.0,  0, talents.meat_cleaver -> proc_chance() );
  buffs_recklessness              = new buff_t( this, "recklessness",              3, 12.0 );
  buffs_revenge                   = new buff_t( this, "revenge",                   1,  5.0 );
  buffs_rude_interruption         = new buff_t( this, "rude_interruption",         1, 15.0 * talents.rude_interruption ->rank() );
  buffs_shield_block              = new buff_t( this, "shield_block",              1, 10.0 );
  buffs_sweeping_strikes          = new buff_t( this, "sweeping_strikes",          1, 10.0 );
  buffs_sword_and_board           = new buff_t( this, "sword_and_board",           1,  5.0,   0, talents.sword_and_board -> proc_chance() );
  buffs_taste_for_blood           = new buff_t( this, "taste_for_blood",           1,  9.0, 6.0, talents.taste_for_blood -> proc_chance() );
  buffs_thunderstruck             = new buff_t( this, "thunderstruck",             3, 20.0,   0, talents.thunderstruck -> proc_chance() );
  buffs_victory_rush              = new buff_t( this, "victory_rush",              1, 20.0 + glyphs.enduring_victory * 5.0 );
  buffs_wrecking_crew             = new buff_t( this, "wrecking_crew",             1, 12.0,   0 );
  buffs_tier10_2pc_melee          = new buff_t( this, "tier10_2pc_melee",          1, 10.0,   0, set_bonus.tier10_2pc_melee() * 0.02 );
  buffs_tier10_4pc_melee          = new buff_t( this, "tier10_4pc_melee",          2, 20.0,   0, set_bonus.tier10_4pc_melee() );
}

// warrior_t::init_gains ====================================================

void warrior_t::init_gains()
{
  player_t::init_gains();

  gains_anger_management       = get_gain( "anger_management"      );
  gains_avoided_attacks        = get_gain( "avoided_attacks"       );
  gains_battle_shout           = get_gain( "battle_shout"          );
  gains_berserker_rage         = get_gain( "berserker_rage"        );
  gains_blood_frenzy           = get_gain( "blood_frenzy"          );
  gains_incoming_damage        = get_gain( "incoming_damage"       );
  gains_mh_attack              = get_gain( "mh_attack"             );
  gains_oh_attack              = get_gain( "oh_attack"             );
  gains_shield_specialization  = get_gain( "shield_specialization" );
  gains_sudden_death           = get_gain( "sudden_death"          );
}

// warrior_t::init_procs ====================================================

void warrior_t::init_procs()
{
  player_t::init_procs();

  procs_deferred_deep_wounds    = get_proc( "deferred_deep_wounds"   );
  procs_munched_deep_wounds     = get_proc( "munched_deep_wounds"    );
  procs_rolled_deep_wounds      = get_proc( "rolled_deep_wounds"     );
  procs_parry_haste             = get_proc( "parry_haste"            );
  procs_strikes_of_opportunity  = get_proc( "strikes_of_opportunity" );
  procs_sudden_death            = get_proc( "sudden_death"           );
}

// warrior_t::init_uptimes ==================================================

void warrior_t::init_uptimes()
{
  player_t::init_uptimes();

  uptimes_deep_wounds = get_uptime( "deep_wounds" );
  uptimes_rage_cap    = get_uptime( "rage_cap"    );
  uptimes_rend        = get_uptime( "rend"        );
}

// warrior_t::init_rng ======================================================

void warrior_t::init_rng()
{
  player_t::init_rng();

  rng_blood_frenzy              = get_rng( "blood_frenzy"              );
  rng_executioner_talent        = get_rng( "executioner_talent"        );
  rng_impending_victory         = get_rng( "impending_victory"         );
  rng_strikes_of_opportunity    = get_rng( "strikes_of_opportunity"    );
  rng_sudden_death              = get_rng( "sudden_death"              );
  rng_tier10_4pc_melee          = get_rng( "tier10_4pc_melee"          );
  rng_wrecking_crew             = get_rng( "wrecking_crew"             );
}

// warrior_t::init_actions ==================================================

void warrior_t::init_actions()
{
  if ( main_hand_weapon.type == WEAPON_NONE )
  {
    sim -> errorf( "Player %s has no weapon equipped at the Main-Hand slot.", name() );
    quiet = true;
    return;
  }

  if ( action_list_str.empty() )
  {
    action_list_str = "flask,type=endless_rage/food,type=fish_feast";
    if      ( primary_tree() == TREE_ARMS       ) action_list_str += "/stance,choose=battle,if=in_combat=0";
    else if ( primary_tree() == TREE_FURY       ) action_list_str += "/stance,choose=berserker,if=in_combat=0";
    else if ( primary_tree() == TREE_PROTECTION ) action_list_str += "/stance,choose=defensive,if=in_combat=0";
    action_list_str += "/auto_attack";
    action_list_str += "/snapshot_stats";
    int num_items = ( int ) items.size();
    for ( int i=0; i < num_items; i++ )
    {
      if ( items[ i ].use.active() )
      {
        action_list_str += "/use_item,name=";
        action_list_str += items[ i ].name();
      }
    }
    if ( race == RACE_ORC )
    {
      action_list_str += "/blood_fury";
    }
    else if ( race == RACE_TROLL )
    {
      action_list_str += "/berserking";
    }
    if ( primary_tree() == TREE_ARMS )
    {
      if ( talents.sweeping_strikes -> rank() ) action_list_str += "/sweeping_strikes,if=target.adds>0";
      if ( talents.deadly_calm -> rank() ) action_list_str += "/deadly_calm,rage<10";
      action_list_str += "/inner_rage,rage>=90";
      action_list_str += "/heroic_strike,rage>=75,if=target.adds=0";
      action_list_str += "/cleave,rage>=75,if=target.adds>0";
      action_list_str += "/rend,if=!ticking";
      action_list_str += "/overpower,if=buff.taste_for_blood.remains<1.5";
      action_list_str += "/bladestorm";
      action_list_str += "/mortal_strike";
      action_list_str += "/colossus_smash";
      action_list_str += "/overpower,if=buff.taste_for_blood.react";
      action_list_str += "/execute,health_percentage<=20";
      action_list_str += "/slam";
      action_list_str += "/battle_shout";
      if ( glyphs.berserker_rage ) action_list_str += "/berserker_rage";
    }
    else if ( primary_tree() == TREE_FURY )
    {
      action_list_str += "/recklessness";
      if ( talents.death_wish -> rank() ) action_list_str += "/death_wish";
      action_list_str += "/inner_rage,rage>=90";
      action_list_str += "/heroic_strike,rage>=75,if=target.adds=0";
      action_list_str += "/cleave,rage>=75,if=target.adds>0";
      action_list_str += "/whirlwind,if=target.adds>0";      
      action_list_str += "/bloodthirst";
      action_list_str += "/colossus_smash";
      action_list_str += "/raging_blow";
      action_list_str += "/slam,if=buff.bloodsurge.react";
      action_list_str += "/execute";
      action_list_str += "/battle_shout";
      if ( glyphs.berserker_rage ) action_list_str += "/berserker_rage";
    }
    else if ( primary_tree() == TREE_PROTECTION )
    {
      action_list_str += "/heroic_strike,rage>=15";
      action_list_str += "/revenge";
      if ( talents.shockwave -> rank() ) action_list_str += "/shockwave";
      action_list_str += "/shield_block,sync=shield_slam";
      action_list_str += "/shield_slam";
      if ( talents.devastate -> rank() ) action_list_str += "/devastate";
      action_list_str += "/battle_shout";
      if ( glyphs.berserker_rage ) action_list_str += "/berserker_rage";
    }
    else
    {
      action_list_str += "/stance,choose=berserker/auto_attack";
    }

    action_list_default = 1;
  }

  player_t::init_actions();
}

// warrior_t::combat_begin ==================================================

void warrior_t::combat_begin()
{
  player_t::combat_begin();

  // We start with zero rage into combat.
  resource_current[ RESOURCE_RAGE ] = 0;

  if ( active_stance == STANCE_BATTLE && ! buffs_battle_stance -> check() )
  {
    buffs_battle_stance -> trigger();
  }

  if ( talents.rampage -> rank() )
    sim -> auras.rampage -> trigger();
}

// warrior_t::reset =========================================================

void warrior_t::reset()
{
  player_t::reset();
  active_stance = STANCE_BATTLE;
  deep_wounds_delay_event = 0;
}

// warrior_t::interrupt =====================================================

void warrior_t::interrupt()
{
  player_t::interrupt();

  buffs_rude_interruption -> trigger();

  if ( main_hand_attack ) main_hand_attack -> cancel();
  if (  off_hand_attack )  off_hand_attack -> cancel();
}

// warrior_t::composite_attack_power_multiplier =============================

double warrior_t::composite_attack_power_multiplier() SC_CONST
{
  double mult = player_t::composite_attack_power_multiplier();

  if ( buffs_tier10_2pc_melee -> up() )
    mult *= 1.16;
  return mult;
}

// warrior_t::composite_attack_hit ==========================================

double warrior_t::composite_attack_hit() SC_CONST
{
  double ah = player_t::composite_attack_hit();
  if ( spec.precision -> ok() )
  {
    ah += spec.precision -> effect_base_value( 1 ) / 100.0;
  }
  return ah;
}

// warrior_t::composite_attack_penetration ====================================

double warrior_t::composite_attack_penetration() SC_CONST
{
  double arp = player_t::composite_attack_penetration();

  if ( buffs_colossus_smash -> up() )
    arp = 1.0;

  return arp;
}

// warrior_t::composite_attribute_multiplier ===============================

double warrior_t::composite_attribute_multiplier( int attr ) SC_CONST
{
  double m = player_t::composite_attribute_multiplier( attr );

  if ( ( attr == STAT_STRENGTH ) && plate_specialization && ( primary_tree() == TREE_ARMS || primary_tree() == TREE_FURY ) )
    m *= 1.05;
  else if ( ( attr == STAT_STAMINA ) && plate_specialization && primary_tree() == TREE_PROTECTION )
    m *= 1.05;

  return m;
}

// warrior_t::composite_tank_block ==========================================

double warrior_t::composite_tank_block() SC_CONST
{
  double b = player_t::composite_tank_block();
  if ( buffs_shield_block -> check() )
    b = 1.0;
  return b;
}

// warrior_t::regen =========================================================

void warrior_t::regen( double periodicity )
{
  player_t::regen( periodicity );

  if ( spec.anger_management -> ok() )
  {
    resource_gain( RESOURCE_RAGE, ( periodicity / 3.0 ), gains_anger_management );
  }

  uptimes_deep_wounds -> update( dots_deep_wounds -> ticking() );
  uptimes_rage_cap    -> update( resource_current[ RESOURCE_RAGE ] ==
                                 resource_max    [ RESOURCE_RAGE] );
  uptimes_rend        -> update( dots_rend -> ticking() );
}

// warrior_t::resource_loss =================================================

double warrior_t::resource_loss( int       resource,
                                 double    amount,
                                 action_t* action )
{
  double actual_amount = player_t::resource_loss( resource, amount, action );

  if ( resource == RESOURCE_HEALTH )
  {
    // FIXME!!! Only works for level 80 currently!
    double coeff_60 = 453.3;
    double coeff_70 = 453.3;
    double coeff_80 = 453.3;
    double coeff_85 = 453.3; // FIXME

    double coeff = rating_t::interpolate( level, coeff_60, coeff_70, coeff_80, coeff_85 );

    double rage_gain = 5 * amount / ( 2 * coeff );

    resource_gain( RESOURCE_RAGE, rage_gain, gains_incoming_damage );
  }

  return actual_amount;
}

// warrior_t::target_swing ==================================================

int warrior_t::target_swing()
{
  int result = player_t::target_swing();

  if ( sim -> log ) log_t::output( sim, "%s swing result: %s", sim -> target -> name(), util_t::result_type_string( result ) );

  if ( result == RESULT_HIT    ||
       result == RESULT_CRIT   ||
       result == RESULT_GLANCE ||
       result == RESULT_BLOCK  )
  {
    resource_gain( RESOURCE_RAGE, 100.0, gains_incoming_damage );  // FIXME! Assume it caps rage every time.
  }
  if ( result == RESULT_BLOCK )
  {
    if ( talents.shield_specialization -> rank() )
    {
      resource_gain( RESOURCE_RAGE, 5.0 * talents.shield_specialization -> rank(), gains_shield_specialization );
    }
  }
  if ( result == RESULT_BLOCK || 
       result == RESULT_DODGE ||
       result == RESULT_PARRY )
  {
       buffs_bastion_of_defense -> trigger();
  }
  if ( result == RESULT_PARRY )
  {
    buffs_hold_the_line -> trigger();

    if ( main_hand_attack && main_hand_attack -> execute_event )
    {
      double swing_time = main_hand_attack -> time_to_execute;
      double max_reschedule = ( main_hand_attack -> execute_event -> occurs() - 0.20 * swing_time ) - sim -> current_time;

      if ( max_reschedule > 0 )
      {
	      main_hand_attack -> reschedule_execute( std::min( ( 0.40 * swing_time ), max_reschedule ) );
	      procs_parry_haste -> occur();
      }
    }
  }
  return result;
}

// warrior_t::get_talent_trees ==============================================

std::vector<talent_translation_t>& warrior_t::get_talent_list()
{
  talent_list.clear();
  return talent_list;
}

// warrior_t::get_options ===================================================

std::vector<option_t>& warrior_t::get_options()
{
  if ( options.empty() )
  {
    player_t::get_options();

    option_t warrior_options[] =
    {
      // @option_doc loc=player/warrior/talents title="Talents"
      { "plate_specialization", OPT_BOOL, &plate_specialization },
      { NULL, OPT_UNKNOWN, NULL }
    };

    option_t::copy( options, warrior_options );
  }

  return options;
}

// warrior_t::decode_set ====================================================

int warrior_t::decode_set( item_t& item )
{
  if ( item.slot != SLOT_HEAD      &&
       item.slot != SLOT_SHOULDERS &&
       item.slot != SLOT_CHEST     &&
       item.slot != SLOT_HANDS     &&
       item.slot != SLOT_LEGS      )
  {
    return SET_NONE;
  }

  const char* s = item.name();

  bool is_melee = ( strstr( s, "helmet"         ) ||
		                strstr( s, "shoulderplates" ) ||
		                strstr( s, "battleplate"    ) ||
		                strstr( s, "legplates"      ) ||
		                strstr( s, "gauntlets"      ) );

  bool is_tank = ( strstr( s, "greathelm"   ) ||
		               strstr( s, "pauldrons"   ) ||
		               strstr( s, "breastplate" ) ||
		               strstr( s, "legguards"   ) ||
		               strstr( s, "handguards"  ) );

  if ( strstr( s, "ymirjar" ) )
  {
    if ( is_melee ) return SET_T10_MELEE;
    if ( is_tank  ) return SET_T10_TANK;
  }
  if ( strstr( s, "earthen" ) )
  {
    bool is_melee = ( strstr( s, "helmet"        ) ||
		                  strstr( s, "pauldrons"     ) ||
		                  strstr( s, "battleplate"   ) ||
		                  strstr( s, "legplates"     ) ||
		                  strstr( s, "gauntlets"     ) );

    bool is_tank = ( strstr( s, "faceguard"      ) ||
		                 strstr( s, "shoulderguards" ) ||
		                 strstr( s, "chestguard"     ) ||
		                 strstr( s, "legguards"      ) ||
		                 strstr( s, "handguards"     ) );

    if ( is_melee ) return SET_T11_MELEE;
    if ( is_tank  ) return SET_T11_TANK;
  }

  return SET_NONE;
}

// ==========================================================================
// PLAYER_T EXTENSIONS
// ==========================================================================

// player_t::create_warrior =================================================

player_t* player_t::create_warrior( sim_t* sim, const std::string& name, race_type r )
{
  return new warrior_t( sim, name, r );
}

// warrior_init =============================================================

void player_t::warrior_init( sim_t* sim )
{
  sim -> auras.battle_shout = new aura_t( sim, "battle_shout", 1, 120.0 );
  sim -> auras.rampage      = new aura_t( sim, "rampage",      1, 0.0 );

  target_t* t = sim -> target;
  t -> debuffs.blood_frenzy_bleed    = new debuff_t( sim, "blood_frenzy_bleed",    1, 15.0 );
  t -> debuffs.blood_frenzy_physical = new debuff_t( sim, "blood_frenzy_physical", 1, 15.0 );
  t -> debuffs.sunder_armor          = new debuff_t( sim, "sunder_armor",          1, 30.0 );
  t -> debuffs.thunder_clap          = new debuff_t( sim, "thunder_clap",          1, 30.0 );
}

// player_t::warrior_combat_begin ===========================================

void player_t::warrior_combat_begin( sim_t* sim )
{
  if ( sim -> overrides.battle_shout ) 
    sim -> auras.battle_shout -> override( 1, sim -> sim_data.effect_min( 6673, ( sim -> P403 ) ? 85 : 80, E_APPLY_AURA, A_MOD_STAT ) );

  if ( sim -> overrides.rampage      ) sim -> auras.rampage      -> override();

  target_t* t = sim -> target;
  if ( sim -> overrides.blood_frenzy_bleed    ) t -> debuffs.blood_frenzy_bleed    -> override( 1, 30 );
  if ( sim -> overrides.blood_frenzy_physical ) t -> debuffs.blood_frenzy_physical -> override( 1,  4 );
  if ( sim -> overrides.sunder_armor          ) t -> debuffs.sunder_armor          -> override( 3 );
  if ( sim -> overrides.thunder_clap          ) t -> debuffs.thunder_clap          -> override();
}
