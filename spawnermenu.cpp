#include "plugin.h"
#include "mm/imgui/imgui.h"

#include "mm/core/avasingle.h"
#include "mm/core/graphics/graphicsengine.h"
#include "mm/core/input.h"

#include "mm/game/spawnsystem.h"
#include "mm/game/charactermanager.h"

const char* exported_ext = ".ee";
const char* empty_vehicle[] = // id - -5
{
	"editor/entities/a00/exported/a00_vehicle_empty_buggy",
	"editor/entities/a00/exported/a00_vehicle_empty_buzzards_boarderpatrol",
	"editor/entities/a00/exported/a00_vehicle_empty_buzzards_dropkicker",
	"editor/entities/a00/exported/a00_vehicle_empty_buzzards_fireraider",
	"editor/entities/a00/exported/a00_vehicle_empty_buzzards_medium_alt",
	"editor/entities/a00/exported/a00_vehicle_empty_buzzards_spiker",
	"editor/entities/a00/exported/a00_vehicle_empty_convoy_truck",
	"editor/entities/a00/exported/a00_vehicle_empty_dune_vessel_carrier_sm",
	"editor/entities/a00/exported/a00_vehicle_empty_gastown_heavy",
	"editor/entities/a00/exported/a00_vehicle_empty_gastown_heavy_02",
	"editor/entities/a00/exported/a00_vehicle_empty_gastown_light",
	"editor/entities/a00/exported/a00_vehicle_empty_gastown_light_02",
	"editor/entities/a00/exported/a00_vehicle_empty_gastown_medium",
	"editor/entities/a00/exported/a00_vehicle_empty_gastown_medium_02",
	"editor/entities/a00/exported/a00_vehicle_empty_highvalue_01",
	"editor/entities/a00/exported/a00_vehicle_empty_highvalue_02",
	"editor/entities/a00/exported/a00_vehicle_empty_highvalue_03",
	"editor/entities/a00/exported/a00_vehicle_empty_highvalue_mm3020",
	"editor/entities/a00/exported/a00_vehicle_empty_interceptor",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_boombug",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_crusher",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_crusher_armored",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_crusher_armored_heavy",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_fireraider",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_metalgrinder",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_rammerhead",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_spotter",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_spotter_armored",
	"editor/entities/a00/exported/a00_vehicle_empty_roadkill_spotter_armored_heavy",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_boarderpatrol",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_fireraider",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_fueler",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_fueler_sm",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_hauler",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_metalgrinder",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_rammerhead",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_spotter",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_spotter_armored",
	"editor/entities/a00/exported/a00_vehicle_empty_scrotus_spotter_armored_heavy",
	"editor/entities/a00/exported/a00_vehicle_empty_v8carrier"
};


const char* all_entity[] = {
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_boombug_driver",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_boombug_driver_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_rammerhead_level0",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_rammerhead_level0_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_rammerhead_level1",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_rammerhead_level1_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_redneckexpress_level0",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_redneckexpress_level0_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_redneckexpress_level1",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_redneckexpress_level1_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_redneckexpress_level2",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_redneckexpress_level2_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level0",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level0_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level1",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level1_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level2",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level2_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level3",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_roadkill_stinkwheel_level3_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_boombug_driver",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_boombug_driver_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_rammerhead_level0",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_rammerhead_level0_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_rammerhead_level1",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_rammerhead_level1_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_redneckexpress_level0",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_redneckexpress_level0_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_redneckexpress_level1",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_redneckexpress_level1_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_redneckexpress_level2",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_redneckexpress_level2_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level0",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level0_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level1",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level1_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level2",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level2_db",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level3",
"editor/entities/a00/activities/deathrun/exported/a00_ac_dr_tb_roadkill_stinkwheel_level3_db",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_convoytruck_01",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_convoytruck_02",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_convoytruck_03",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_fueler_01",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_fueler_02",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_fueler_03",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_topdogtruck_01",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_topdogtruck_02",
"editor/entities/a00/activities/exported/convoy/a00_ac_convoy_composition_topdogtruck_03",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_driver",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_driver_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_driver_mm3030",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_level1",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_level1_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_level1_mm3030",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_rammerhead_level1_mm3030_2",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_2boarders",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_2boarders_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_2boarders_thunderstick",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_2boarders_thunderstick_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_3boarders",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_3boarders_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_3boarders_thunderstick",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_3boarders_thunderstick_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_4boarders",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_4boarders_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_4boarders_thunderstick",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_redneckexpress_4boarders_thunderstick_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_0boarder",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_0boarder_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_1boarder",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_1boarder_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_driver",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_driver_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_driver_mm3030",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_driver_mm3030_1",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_driver_mm3030_2",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level2",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level2_0boarder",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level2_0boarder_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level2_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level2_mm3030",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level2_mm3030_2",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level3",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level3_db",
"editor/entities/a00/activities/exported/convoy/guards/scrotus_stinkwheel_level3_mm3030",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_convoytruck",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_convoytruck_epic",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_fueler",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_fueler_epic",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_fueler_mission",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_landmover_mm3030",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_topdogtruck",
"editor/entities/a00/activities/exported/convoy/leader/a00_ac_convoy_leader_topdogtruck_epic",
"editor/entities/a00/activities/exported/fuel_convoy/a00_ac_fuel_convoy_level_0",
"editor/entities/a00/activities/exported/fuel_convoy/a00_ac_fuel_convoy_level_1",
"editor/entities/a00/activities/exported/fuel_convoy/a00_ac_fuel_convoy_level_2",
"editor/entities/a00/activities/exported/fuel_convoy/a00_ac_fuel_convoy_level_3",
"editor/entities/a00/activities/exported/tier2_convoy/a00_ac_tier2_convoy_level_2",
"editor/entities/a00/encounters/exported/a00_ch_griffa",
"editor/entities/a00/encounters/exported/critters/encounter_lizard_01",
"editor/entities/a00/encounters/exported/critters/encounter_rat_01",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_rammerhead_level0",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_rammerhead_level1",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_redneckexpress_2boarders",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_redneckexpress_3boarders",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_redneckexpress_4boarders",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_stinkwheel_level0",
"editor/entities/a00/encounters/exported/road/a00_en_road_buzzards_stinkwheel_level1",
"editor/entities/a00/encounters/exported/road/a00_en_road_gastown_heavy_02_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_gastown_heavy_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_gastown_light_02_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_gastown_light_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_gastown_medium_02_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_gastown_medium_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_boombug_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_boombug_driver_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_rammerhead_level0",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_rammerhead_level0_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_rammerhead_level1",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_rammerhead_level1_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_redneckexpress_level0",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_redneckexpress_level0_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_redneckexpress_level1",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_redneckexpress_level1_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_redneckexpress_level2",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_redneckexpress_level2_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level0",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level0_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level1",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level1_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level2",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level2_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level3",
"editor/entities/a00/encounters/exported/road/a00_en_road_roadkill_stinkwheel_level3_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_rammerhead_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_rammerhead_driver_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_rammerhead_level1",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_rammerhead_level1_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_2boarders",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_2boarders_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_2boarders_thunderstick",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_2boarders_thunderstick_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_3boarders",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_3boarders_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_3boarders_thunderstick",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_3boarders_thunderstick_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_4boarders",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_4boarders_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_4boarders_thunderstick",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_redneckexpress_4boarders_thunderstick_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_scrap_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_0boarder",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_0boarder_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_1boarder",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_1boarder_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_driver",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_driver_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_level2",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_level2_0boarder",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_level2_0boarder_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_level2_db",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_level3",
"editor/entities/a00/encounters/exported/road/a00_en_road_scrotus_stinkwheel_level3_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_buzzard_bullies_dif1_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_buzzard_bullies_dif1_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_buzzard_bullies_dif1_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_buzzard_bullies_dif1_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_buzzard_bullies_dif1_05",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_buzzard_bullies_dif1_06",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_aftermath_dif0_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_aftermath_dif0_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_aftermath_dif0_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif1_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif1_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif1_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif1_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif2_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif2_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif2_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_brokencar_dif2_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_03_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_04_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_05",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_05_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_06",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif1_06_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_03_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_04_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_05",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_05_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_06",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_bullies_dif2_06_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_mercykill_dif0_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_mercykill_dif0_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif0_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif0_05",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif0_06",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif1_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif1_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif1_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif2_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif2_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_roadkill_wreck_dif2_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_aftermath_dif0_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_aftermath_dif0_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_aftermath_dif0_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif1_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif1_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif1_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif1_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif2_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif2_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif2_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_brokencar_dif2_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_03_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_04_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_05",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_05_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_06",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif1_06_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_01_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_02",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_02_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_03",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_03_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_04",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_04_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_05",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_05_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_06",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_bullies_dif2_06_db",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_gimptransport_dif0_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_mercykill_dif0_01",
"editor/entities/a00/encounters/exported/roadside/a00_encounters_roadside_scrotus_mercykill_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_ambush_dif1_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_bullies_dif1_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_bullies_dif1_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_bullies_dif1_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_bullies_dif1_04",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_bullies_dif1_05",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_buzzard_bullies_dif1_06",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_corpses_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_corpses_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_corpses_dif0_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_corpses_dif0_04",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_corpses_dif0_05",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_corpses_dif0_06",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_mercykill_roadkill_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_mercykill_roadkill_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif1_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif1_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif1_02_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif1_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif1_03_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif2_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif2_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif2_02_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif2_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_campsite_dif2_03_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_gluesniffers_dif1_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_gluesniffers_dif1_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_gluesniffers_dif2_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_gluesniffers_dif2_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_raided_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_raided_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_roadkill_raided_dif0_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif1_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif1_01_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif1_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif1_02_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif1_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif1_03_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif2_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif2_01_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif2_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif2_02_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif2_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_campsite_dif2_03_db",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_gluesniffers_dif1_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_gluesniffers_dif1_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_gluesniffers_dif2_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_gluesniffers_dif2_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_mercykill_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_scrotus_mercykill_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_campsite_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_campsite_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_campsite_dif0_03",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_mercykill_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_mercykill_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_raided_dif0_01",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_raided_dif0_02",
"editor/entities/a00/encounters/exported/wasteland/a00_encounters_wasteland_wanderer_raided_dif0_03",
"editor/entities/a00/exported/a00_vehicle_empty_buggy",
"editor/entities/a00/exported/a00_vehicle_empty_buzzards_boarderpatrol",
"editor/entities/a00/exported/a00_vehicle_empty_buzzards_dropkicker",
"editor/entities/a00/exported/a00_vehicle_empty_buzzards_fireraider",
"editor/entities/a00/exported/a00_vehicle_empty_buzzards_medium_alt",
"editor/entities/a00/exported/a00_vehicle_empty_buzzards_spiker",
"editor/entities/a00/exported/a00_vehicle_empty_convoy_truck",
"editor/entities/a00/exported/a00_vehicle_empty_dune_vessel_carrier_sm",
"editor/entities/a00/exported/a00_vehicle_empty_gastown_heavy",
"editor/entities/a00/exported/a00_vehicle_empty_gastown_heavy_02",
"editor/entities/a00/exported/a00_vehicle_empty_gastown_light",
"editor/entities/a00/exported/a00_vehicle_empty_gastown_light_02",
"editor/entities/a00/exported/a00_vehicle_empty_gastown_medium",
"editor/entities/a00/exported/a00_vehicle_empty_gastown_medium_02",
"editor/entities/a00/exported/a00_vehicle_empty_highvalue_01",
"editor/entities/a00/exported/a00_vehicle_empty_highvalue_02",
"editor/entities/a00/exported/a00_vehicle_empty_highvalue_03",
"editor/entities/a00/exported/a00_vehicle_empty_highvalue_mm3020",
"editor/entities/a00/exported/a00_vehicle_empty_interceptor",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_boombug",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_crusher",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_crusher_armored",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_crusher_armored_heavy",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_fireraider",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_metalgrinder",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_rammerhead",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_spotter",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_spotter_armored",
"editor/entities/a00/exported/a00_vehicle_empty_roadkill_spotter_armored_heavy",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_boarderpatrol",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_fireraider",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_fueler",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_fueler_sm",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_hauler",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_metalgrinder",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_rammerhead",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_spotter",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_spotter_armored",
"editor/entities/a00/exported/a00_vehicle_empty_scrotus_spotter_armored_heavy",
"editor/entities/a00/exported/a00_vehicle_empty_v8carrier",
"editor/entities/a00/exported/a00_vh_sidemission_dunevesselcarrier",
"editor/entities/a00/exported/a00_vh_sidemission_hvv",
"editor/entities/a00/exported/a00_vh_sidemission_speakercar",
"editor/entities/a00/missions/side_missions/exported/dune_vessel_wanderer_crowd",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_armory_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_armory_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_cleanup_crew_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_cleanup_crew_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_doghouse_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_doghouse_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_maggot_farm_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_maggot_farm_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_scrap_crew_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_scrap_crew_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_stockpile_large_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_stockpile_large_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_stockpile_medium_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_stockpile_medium_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_stockpile_small_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_stockpile_small_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_super_fuel_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_super_fuel_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_super_water_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_super_water_01_locked",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_survey_crew_01",
"editor/entities/a00/propsenc/expentity/a00_propsenc_projects_survey_crew_01_locked",
"editor/entities/a01/encounters/exported/loot/a01_wasteland_lootbox_roadkill_normal",
"editor/entities/a01/encounters/exported/loot/a01_wasteland_lootbox_roadkill_poor",
"editor/entities/a01/encounters/exported/loot/a01_wasteland_lootbox_roadkill_rich",
"editor/entities/a01/encounters/exported/loot/a01_wasteland_lootbox_roadkill_trap",
"editor/entities/a01/encounters/exported/narrow_roads/a01_enc_roadblock_1",
"editor/entities/a01/encounters/exported/narrow_roads/a01_enc_roadblock_2",
"editor/entities/a01/encounters/exported/narrow_roads/a01_enc_roadblock_3",
"editor/entities/a01/encounters/exported/road/a01_buzzards_dropkicker_boarderpatrol",
"editor/entities/a01/encounters/exported/road/a01_buzzards_fireraider_boarderpatrol",
"editor/entities/a01/encounters/exported/road/a01_buzzards_spiker",
"editor/entities/a01/encounters/exported/road/a01_buzzards_spiker_boarderpatrol",
"editor/entities/a01/encounters/exported/road/a01_buzzards_spiker_boarderpatrol_dropkicker",
"editor/entities/a01/encounters/exported/road/a01_buzzards_spiker_boarderpatrol_fireraider",
"editor/entities/a01/encounters/exported/road/a01_buzzards_spiker_spiker",
"editor/entities/a01/encounters/exported/road/a01_roadkill_crusher",
"editor/entities/a01/encounters/exported/road/a01_roadkill_rammerhead",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotter",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotter_boombug",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotter_crusher",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotter_rammerhead",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotter_spotter",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_boombug",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_crusher",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_crusherarmor",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_fireraider",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_metalgrinder",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_rammerhead",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmor_spotter",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmorheavy_metalgrinder_crusherarmorheavy",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmorheavy_rammerhead_crusherarmorheavy",
"editor/entities/a01/encounters/exported/road/a01_roadkill_spotterarmorheavy_spotterarmor_boombug",
"editor/entities/a01/encounters/exported/road/a01_scrotus_boarderpatrol_rammerhead_metalgrinder",
"editor/entities/a01/encounters/exported/road/a01_scrotus_fireraider_rammerhead_metalgrinder",
"editor/entities/a01/encounters/exported/road/a01_scrotus_rammerhead_metalgrinder",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotter",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotter_boarderpatrol",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotter_rammerhead",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotter_spotter",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmor_boarderpatrol",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmor_fireraider",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmor_metalgrinder",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmor_rammerhead",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmor_spotter",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmorheavy_boarderpatrol_fireraider",
"editor/entities/a01/encounters/exported/road/a01_scrotus_spotterarmorheavy_spotterarmor_fireraider",
"editor/entities/a01/encounters/exported/road_buzzard/a01_buzzard_stinkwheel_attacker_0001",
"editor/entities/a01/encounters/exported/road_buzzard/a01_buzzard_stinkwheel_attacker_0002",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_buzzard_dif_01",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_buzzard_dif_02",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_buzzard_dif_03",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_buzzard_dif_04",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_buzzard_dif_05",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_roadkill_dif_01",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_roadkill_dif_02",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_roadkill_dif_03",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_roadkill_dif_04",
"editor/entities/a01/encounters/exported/road_side/a01_encounter_brokencar_roadkill_dif_05",
"editor/entities/a01/encounters/exported/road_side/a01_mercy_carwreck_001",
"editor/entities/a01/encounters/exported/road_side/a01_static_wreck_0001_night",
"editor/entities/a01/encounters/exported/road_side/a01_static_wreck_0002",
"editor/entities/a01/encounters/exported/road_side/a01_static_wreck_0003",
"editor/entities/a01/encounters/exported/road_side/a01_static_wreck_0004_night",
"editor/entities/a01/encounters/exported/road_side/a01_static_wreck_0005",
"editor/entities/a01/encounters/exported/road_side/a01_static_wreck_0006_birds",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_roadkill_cooking_dif01",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_roadkill_cooking_dif02",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_roadkill_cooking_dif03",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_roadkill_cooking_dif04",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_roadkill_cooking_dif05",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_wanderer_group_3",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_wanderer_group_4",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_wanderer_group_5",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_wanderer_group_stationary_01",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_wanderer_group_stationary_02",
"editor/entities/a01/encounters/exported/wasteland/a01_encounter_wanderer_group_stationary_03",
"editor/entities/a01/encounters/exported/wasteland/a01_roadkill_barrel_0001_night",
"editor/entities/a01/encounters/exported/wasteland/a01_roadkill_barrel_0002_night",
"editor/entities/a01/encounters/exported/wasteland/a01_roadkill_barrel_0003_night",
"editor/entities/a01/encounters/exported/wasteland/a01_scrotus_gimp_cage_0001",
"editor/entities/a01/encounters/exported/wasteland/a01_scrotus_gimp_cage_0002",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_corpses_0001",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_corpses_0002",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_corpses_0003",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_corpses_0004_birds",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_mercy_corpses_0001",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_worship_0001",
"editor/entities/a01/encounters/exported/wasteland/a01_wasteland_worship_0002",
"editor/entities/a01/encounters/exported/wasteland_buzzard/a01_wasteland_buzzard_ambush_0001",
};

class ImGuiSpawnerMenu : public ImGuiRenderer {
public:
	ImGuiSpawnerMenu() : ImGuiRenderer() {

	}

	void Game() override {

	}

	void GameHandleEvent(Event const& _event) override {
		if (_event.hash == HASHSTR("focus")) {
			//CAvaSingleInstance_EXE(CDeviceManager, ->GetInputManager()->SetInFocus(!_event.Arg<bool>(0)));
			//CAvaSingle<NGraphicsEngine::CGraphicsEngine>::Instance->SetCursor(_event.Arg<bool>(0) ? 0 : -1);
		}
	};

	bool show = false;
	bool show_list1 = false;
	bool show_list2 = false;
	std::string selected_item1 = "";
	std::string selected_item2 = "";
	char input_buffer[256] = { 0 };
	void Render() override {


		Log("Render start");

		if (ImGui::IsKeyJustDown(ImGuiKey_Slash)) {
			show = !show;
			memset(input_buffer, 0, 256);
			SendGameEvent(Event("focus").Add(show));
		}

		if (!show)
			return;

		ImGui::Begin("Spawner 0.1");

		

		if (ImGui::Button("Empty Vehicles"))
		{
			show_list1 = true;
			show_list2 = false;
			memset(input_buffer, 0, 256);
		}

		ImGui::SameLine();

		if (ImGui::Button("All Entities"))
		{
			show_list2 = true;
			show_list1 = false;
			memset(input_buffer, 0, 256);
		}

		ImGui::InputText("##searcher", input_buffer, IM_ARRAYSIZE(input_buffer));

		ImGui::SameLine();

		if (ImGui::Button("Spawn"))
		{
			std::string out(input_buffer);
			SendGameEvent([out]() {

				if (!CAvaSingle<CCharacterManager>::Instance->GetPlayerCharacter())
					return;

				
				CHashString spawnId = SpawnSystemGetNewSpawnId().m_Hash;
				auto newInfo = SSpawnInstanceInfo::New();
				newInfo->m_SpawnId.m_Hash = spawnId.m_Hash;
				newInfo->m_SpawnPatchId.m_Hash = spawnId.m_Hash;
				newInfo->m_DespawnDistanceSq = 90000.0f;
				newInfo->m_SpawnPriority = E_SPAWN_PRIORITY_CRITICAL;
				newInfo->SetEntityFile((out + exported_ext).c_str());

				CMatrix Mat;
				CQuaternion rot;
				CAvaSingle<CCharacterManager>::Instance->GetPlayerCharacter()->GetTransform(&Mat);
				rot.FromMatrix4(Mat);
				auto pos = Mat.Position() + (rot * CVector3f(0, 0.2, -8)); // forward
				Mat.SetPosition(pos);

				

				s_SpawnSystemContext->m_UseSpawnLimits = false;
				SpawnSystemSpawn(newInfo, &Mat);
				SSpawnInstanceInfo::Delete(newInfo);
				});
		}

		
		if (show_list1)
		{
			ImGui::BeginChild("##Child1", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
			for (const auto& item : empty_vehicle)
			{
				if (!input_buffer[0] || strstr(item, input_buffer)) {
					if (ImGui::Selectable(item))
					{
						selected_item1 = item;
						sprintf(input_buffer, "%s", item);
						input_buffer[sizeof(input_buffer) - 1] = '\0';
					}
				}
			}
			ImGui::EndChild();
		}

		
		if (show_list2)
		{
			ImGui::BeginChild("##Child2", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
			for (const auto& item : all_entity)
			{
				if (!input_buffer[0] || strstr(item, input_buffer)) {
					if (ImGui::Selectable(item))
					{
						selected_item2 = item;
						sprintf(input_buffer, "%s", item);
						input_buffer[sizeof(input_buffer) - 1] = '\0';
					}
				}
				
			}
			ImGui::EndChild();
		}

		ImGui::End();

		Log("Render end");
	}
};

ImGuiSpawnerMenu spawnerMenu;