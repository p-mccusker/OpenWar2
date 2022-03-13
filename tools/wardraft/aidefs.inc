; *************************************************
; * WarDraft-AI-compiler standard include file    *
; * last updated: Mar.06 1997  by: Alexander Cech *
; * Version: 1.0                                  *
; *************************************************

; basic commands understood by the compiler:
; var    x=y   x: (byte)  variable-number  y: (byte) value
; do     x     x: (byte)  item-code
; goto   x     x: (word)  destination
; sleep  x     x: (dword) number of ticks (?) to sleep
; wait   x     x: (byte)  type of wait
; rate   x=y   x: (byte)  rate-number      y: (word) value
; item   x=y   x: (byte)  item-number      y: (byte) value

; --- Commands: ---

#define	wait_1		wait 1
#define	wait_2		wait 2
#define	wait_3		wait 3
#define	wait_4		wait 4
#define	wait_5		wait 5
#define	wait_6		wait 6
#define	wait_7		wait 7
#define	wait_keep	wait 1
#define	wait_stronghold	wait 1
#define	wait_castle	wait 2
#define	wait_fortress	wait 2
#define	wait_worker	wait 3
#define	wait_peasants	wait 3
#define	wait_peons	wait 3
#define	wait_land	wait 4
#define	wait_water	wait 5
#define	wait_air	wait 6

#define build		do
#define	upgrade		do
#define	upgrd		do
#define	learn		do
#define	make		do

#define	reset_land	var $09=0
#define	reset_water	var $0A=0
#define	reset_air	var $0B=0
#define	attk_land	var $09=1
#define	attk_water	var $0A=1
#define	attk_air	var $0B=1

#define	strat_off	var $0C=0
#define	strat_on	var $0C=1

#define	aggr_low	var $21=0
#define	aggr_high	var $21=$FF

#define	reset_items	var $22=0

; --- Variables: ---

#define	size_land	var $0D
#define	size_water	var $0F
#define	size_air	var $11
#define	ptys_land	var $0E
#define	ptys_water	var $10
#define	ptys_air	var $12
#define	peasants	var $13
#define	peons		var $13
#define	footmen		var $14
#define	grunts		var $14
#define	archers		var $15
#define	axethrowers	var $15
#define	ballistas	var $16
#define	catapults	var $16
#define	knights		var $17
#define	ogres		var $17
#define	tankers		var $18
#define	destroyers	var $19
#define	transports	var $1A
#define	battleships	var $1B
#define	juggernaughts	var $1B
#define	submarines	var $1C
#define	turtles		var $1C
#define	mages		var $1D
#define	deathknights	var $1D
#define	flyers		var $1E
#define	zeppelins	var $1E
#define	demosquads	var $1F
#define	sappers		var $1F
#define	gryphons	var $20
#define	dragons		var $20

; --- other spellings for variables: ---
#define grps_land	ptys_land
#define	grps_water	ptys_water
#define	grps_air	ptys_air
#define	flyingmachines	flyers
#define	gryphonriders	gryphons
#define	juggs		juggernaughts
#define	subs		submarines
#define	worker		peasants

; --- Rates: ---

#define	disabled	$FFFF

#define	rt_Hbarracksfolk	rate $02
#define	rt_Obarracksfolk	rate $03
#define	rt_paladins		rate $04
#define	rt_ogremages		rate $05
#define	rt_Hguardtower		rate $06
#define	rt_Oguardtower		rate $07
#define	rt_flyers		rate $0A
#define	rt_zeppelins		rate $0B
#define	rt_gryphons		rate $0C
#define	rt_dragons		rate $0D
#define	rt_Hships		rate $0E
#define	rt_Oships		rate $0F
#define	rt_peasants		rate $10
#define	rt_peons		rate $11
#define	rt_up_archers		rate $12
#define	rt_up_axethrowers	rate $13
#define	rt_Hup_shipcannons	rate $14
#define	rt_Oup_shipcannons	rate $15
#define	rt_mages		rate $16
#define	rt_deathknights		rate $17
#define	rt_Hup_weapons		rate $18
#define	rt_Oup_weapons		rate $19
#define	rt_up_castle		rate $1E
#define	rt_up_fortress		rate $1F
#define	rt_castlepeasants	rate $20
#define	rt_fortresspeons	rate $21

; --- other spellings for rates: ---
#define	rt_flyingmachines		rt_flyers
#define	rt_gryphonriders		rt_gryphons
#define	rt_up_arrows			rt_up_archers
#define	rt_up_axes			rt_up_axethrowers
#define	rt_up_keep_to_castle		rt_up_castle
#define	rt_up_stronghold_to_fortress	rt_up_fortress

; --- Items: ---

#define	nothing		$00
#define all_items	$FF

#define	farm			$3a
#define	barracks		$3c
#define	church			$3e
#define	altar			$3e
#define	tower			$40
#define	stables			$42
#define	ogremound		$42
#define	inventor		$44
#define	alchemist		$44
#define	aviary			$46
#define	roost			$46
#define	shipyard		$48
#define	townhall		$4a
#define	greathall		$4a
#define	lumbermill		$4c
#define	foundry			$4e
#define	magetower		$50
#define	temple			$50
#define	blacksmith		$52
#define	refinery		$54
#define	oilwell			$56
; #define	keep			$58
; #define	stronghold		$58
; #define	castle			$5a
; #define	fortress		$5a
#define	up_arrow_1		$80
#define	up_axe_1		$80
#define	up_arrow_2		$81
#define	up_axe_2		$81
#define	up_rangers		$82
#define	up_berserkers		$82
#define	up_rangers_A		$83
#define	up_berserkers_A		$83
#define	up_rangers_B		$84
#define	up_berserkers_B		$84
#define	up_rangers_C		$85
#define	up_berserkers_C		$85
#define	up_footmen_A1		$86
#define	up_grunts_A1		$86
#define	up_footmen_A2		$87
#define	up_grunts_A2		$87
#define	up_footmen_B1		$88
#define	up_grunts_B1		$88
#define	up_footmen_B2		$89
#define	up_grunts_B2		$89
#define	up_ballistas_1		$8A
#define	up_catapults_1		$8A
#define	up_ballistas_2		$8B
#define	up_catapults_2		$8B
#define	up_shipcannons_1	$8C
#define	up_shipcannons_2	$8D
#define	up_shiparmor_1		$8E
#define	up_shiparmor_2		$8F
#define	up_paladins		$90
#define	up_ogremages		$90
#define	sp_paladin_A		$91
#define	sp_ogremage_A		$91
#define	sp_paladin_B		$92
#define	sp_ogremage_B		$92
#define	sp_mage_A		$93
#define	sp_deathknight_A	$93
#define	sp_mage_B		$94
#define	sp_deathknight_B	$94
#define	sp_mage_C		$95
#define	sp_deathknight_C	$95
#define	sp_mage_D		$96
#define	sp_deathknight_D	$96
#define	sp_mage_E		$97
#define	sp_deathknight_E	$97
#define	up_keep			$98
#define	up_stronghold		$98
#define	up_castle		$99
#define	up_fortress		$99

; --- other spellings for items: ---
#define	altarofstorms			altar
#define	stower				tower
#define	scouttower			tower
#define	mound				ogremound
#define	gnomishinventor			inventor
#define	goblinalchemist			alchemist
#define	gryphonaviary			aviary
#define	dragonroost			roost
#define	up_archers_to_rangers		up_rangers
#define	up_axethrowers_to_berserkers	up_berserkers
#define	up_knights_to_paladins		up_paladins
#define	up_ogres_to_ogremages		up_ogremages
#define	up_townhall_to_keep		up_keep
#define	up_greathall_to_stronghold	up_stronghold
#define	up_keep_to_castle		up_castle
#define	up_stronghold_to_fortress	up_fortress


