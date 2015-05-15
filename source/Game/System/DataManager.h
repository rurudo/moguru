#pragma once
#include "BoolArray.h"
#include "StoreData.h"
#include "DxLib.h"
#include <string>
#include <map>
/*
 * 使い方
 * 1.enumに追加して、追加した分のパスを登録
 * m_GraphicPath[GraphicPict01].assign("resource/texture/sato1.png");
 *
 * 2.Get関数で呼び出す（その場でロード）
 * DXLibMath::DrawRotaGraphResize(0.5, 0.5, 0.3, 0.0, data.Get(DataManager::GraphicPict01), TRUE);
 *
 * 3.事前ロードをするならLoad関数を編集のこと
*/
class DataManager
{
public:
	// 単品画像
	enum GraphicSet
	{
		// ステージセレクト
		Cur_stage,
		Ic_stage1,
		Ic_stage2,
		Ic_stage3,
		Ic_stage4,
		Ic_stage5,
		Ic_stage1_Back,
		Ic_stage2_Back,
		Ic_stage3_Back,
		Ic_stage4_Back,
		Ic_stage5_Back,
		Spaceship,
		JetRing,
		StageInfo_Bar,
		StageSelect_Background,
		StageSelect_Frame,
		StageSelect_Frame_Back,
		StageSelect_FrameCharacter,
		StageSelect_FrameCharacter_Add,
		Unit_shuttle,
		Ic_stage_Cascade,
		//メニューリソース
		Equipment_Font_Frame,
		Equipment_Icon_Frame,
		Menu_StageMask,
		Equipment_sin,
		New_sin,
		Icon_Description_Frame,
		Menu_Background,
		Question_ic,
		Invently_ic,
		Confirmation_Frame,
		Click,
		RightClick,
		test,
		// タイトルリソース
		Team_logo,
		Title_stone,
		Title_stone_break_left,
		Title_stone_break_right,
		Title_stone_Crack1,
		Title_stone_Crack2,
		Title_stone_Crack3,
		Title_stone_Crash1,
		Title_stone_Crash2,
		Title_logo,
		Title_logo_Back,
		Block_soil,
		Block_soilsub,
		Block_stone,
		Block_Rock,
		Unit_moguru,
		Unit_moguru_chest,
		Title_Back,

		Start1,
		Start2,
		Start3,
		Start4,
		StartBack,
		Unit_moguru_top,
		Unit_moguru_under,

		// プレイ中リソース
		Play_MogllUp,
		GameStart_Menu,
		GameStart_Icon_Go,
		Play_GetTreasure_BG,
		red_shot,
		yellow_shot,
		blue_shot,
		Play_Treasure_Tree2,
		Play_Treasure_Tree3,
		Play_Treasure_Tree4,
		Play_TreasureBox,
		Play_MapBox,
		// 右側UI
		Play_Playmode_UI,
		Play_UnitCreate_Frame,
		Play_UI_Line,
		Play_UI_Radar_enemy_marker,
		Play_UI_Radar_treasure_marker,
		Play_UI_Rader,
		Play_UI_Escape_Button,
		Play_UI_Escape_Button_Red,
		Play_UI_Escape_Button_Blue,
		Play_UI_Escape_Button_Yellow,
		Play_UI_Rader_GreenLine,
		Play_UI_Rader_RedLine,
		Play_UI_Play_HelpButton,
		Play_UI_Meter_Panel,
		Play_UI_Meter_RedArrow,
		Play_UI_Meter_GreenArrow,
		Play_UI_Damage,
		// 宝取得演出
		Play_Treasure_Shine,
		Play_Treasure_Mogll_Graph,
		Play_Treasure_Mogll_Graph_Back,
		Play_Treasure_Mogll_Graph_BoX_Blue,
		Play_Treasure_Mogll_Graph_BoX_Pink,
		// プレイ階層選択リソース
		Floor_Number_1,
		Floor_Number_2,
		Floor_Number_3,
		Floor_Number_4,
		Floor_Number_5,
		Floor_Number_6,
		Floor_Number_7,
		Floor_Number_8,
		Floor_Number_9,
		Play_Button_Floor,
		Play_Button_Floor_Down,
		Play_Button_Go,
		Play_Button_Go_Down,
		Play_Challenge,
		Play_Challenge_Seet,
		StageSelect_Star,
		// ゲームクリアリソース
		Play_Graph_Clear1,
		Play_Graph_Clear2,
		Play_Graph_Clear3,
		Play_Graph_Clear4,
		Play_Graph_Clear5,
		Play_Graph_Clear6,
		Play_Graph_Clear7,
		Play_Graph_Clear8,
		Play_Graph_Clear9,
		// ゲームオーバーリソース
		Moguru_Salvage1,
		Moguru_Salvage2,
		Moguru_Salvage3,
		Play_Graph_Dead1,
		Play_Graph_Dead2,
		Play_Graph_Dead3,
		Play_Graph_Dead4,
		// プレイ開始時背景リソース
		// 地下都市
		Stage_Chikatoshi_1,
		Stage_Chikatoshi_2,
		Stage_Chikatoshi_3,
		Stage_Chikatoshi_4,
		Stage_Chikatoshi_Sky,
		Stage_Chikatoshi_Effect,
		// 氷河
		Stage_Hyoukai_1,
		Stage_Hyoukai_2,
		Stage_Hyoukai_3,
		Stage_Hyoukai_4,
		Stage_Hyoukai_5,
		Stage_Hyoukai_Sky,
		Stage_Hyoukai_Effect1,
		Stage_Hyoukai_Effect2,
		// 火山
		Stage_Maguma_1,
		Stage_Maguma_2,
		Stage_Maguma_3,
		Stage_Maguma_4,
		Stage_Maguma_5,
		Stage_Maguma_Sky,
		Stage_Maguma_Effect1,
		Stage_Maguma_Effect2,
		// 沼地
		Stage_Numachi_1,
		Stage_Numachi_1_ani,
		Stage_Numachi_2,
		Stage_Numachi_3,
		Stage_Numachi_4,
		Stage_Numachi_5,
		Stage_Numachi_Sky,
		Stage_Numachi_Effect1,
		Stage_Numachi_Effect2,
		// 近未来
		Stage_Kinmirai_1,
		Stage_Kinmirai_2,
		Stage_Kinmirai_3,
		Stage_Kinmirai_4,
		Stage_Kinmirai_5,
		Stage_Kinmirai_Sky,
		Stage_Kinmirai_Effect1,
		Stage_Kinmirai_Effect2,
		// チュートリアルリソース
		Help_BG,
		Help_Label,
		Help_Index,
		Help_Button_Back,
		Help_Button_Prev,
		Help_Button_Next,
		Help_Button_Close,
		Description1,
		Description2_1,
		Description2_2,
		Description3,
		Description4_1,
		Description4_2,
		Description5_1,
		Description5_2,
		Description6,
		Description7_1,
		Description7_2,
		Description8,
		// ボタン
		EscapeButton,

		GraphicMax								//常に最後にする
	};
	// 分割画像
	// GraphicGroupSetと順番を合わせる
	enum GraphicGroupIndex
	{
		GG_MAPTIP_None,
		GG_MAPTIP_SAND,
		GG_MAPTIP_SOIL,
		GG_MAPTIP_STONE,
		GG_MAPTIP_ROCK,
		GG_MAPTIP_OLDBONE,
		GG_MAPTIP_METAL,
		GG_MAPTIP_DIAMOND,
		GG_MAPTIP_MUD,
		GG_MAPTIP_DEEPMUD,
		GG_MAPTIP_TREE,
		GG_MAPTIP_RESOURCE,
		GG_MAPTIP_BOMB,
		GG_MAPTIP_ALARM,
		GG_MAPTIP_WATER,
		GG_MAPTIP_WEAKICE,
		GG_MAPTIP_HARDICE,
		GG_MAPTIP_ENEMYICE,
		GG_MAPTIP_FIREROCK,
		GG_MAPTIP_FIRE,
		GG_MAPTIP_CONFUSE,
		GG_MAPTIP_DARK,
		GG_MAPTIP_DUMMY,
		GG_MAPTIP_HARDSOIL,
		GG_MAPTIP_1,
		GG_MAPTIP_2,
		GG_MAPTIP_3,
		GG_MAPTIP_BACKBLOCK,
		// 爆発アニメ
		GraphicGroupExplodeAnim_1,
		GraphicGroupExplodeAnim_2,
		GraphicGroupExplodeAnim_3,
		GraphicGroupExplodeAnim_4,
		GraphicGroupExplodeAnim_5,
		GraphicGroupExplodeAnim_6,
		GraphicGroupExplodeAnim_7,
		// アイテム背景
		GG_ICONBG_Stage1,
		GG_ICONBG_Stage2,
		GG_ICONBG_Stage3,
		GG_ICONBG_Stage4,
		GG_ICONBG_Stage5,
		GG_ICONBG_Mix,
		GG_ICONBG_Unit,
		// ユニット
		GG_UNIT_Treasure,
		GG_UNIT_SmallMog,
		GG_UNIT_FireMog,
		GG_UNIT_BombMog,
		GG_UNIT_GoldenMog,
		GG_UNIT_GalaxyMog,
		GG_UNIT_Salamander,
		GG_UNIT_Dig,
		GG_UNIT_Mud,
		GG_UNIT_Frozen,
		GG_UNIT_Metal,			// 鎧モグラ
		GG_UNIT_MetalTreasure,	// 鎧トレジャー
		GG_UNIT_BigMog,
		GG_UNIT_SpaceMog,
		GG_UNIT_BattleMog,
		GG_UNIT_FrozenEX,
		GG_UNIT_King,
		GG_UNIT_Hell,
		GG_UNIT_Ninja,
		GG_UNIT_Punch,
		GG_UNIT_Thunder,
		GG_UNIT_BombBox,
		GG_UNIT_HeroMog,	// 勇者モグラ
		GG_UNIT_Guardian,
		GG_UNIT_Zombie,
		GG_UNIT_Tyranno,	// ティラノ
		GG_UNIT_Slime,
		GG_UNIT_Cuttlefish,	// イカ
		GG_UNIT_ClockRabbit,
		GG_UNIT_Chop,
		GG_UNIT_Treasure2,
		GG_UNIT_SmallMog2,
		GG_UNIT_FireMog2,
		GG_UNIT_BombMog2,
		GG_UNIT_GoldenMog2,
		GG_UNIT_GalaxyMog2,
		GG_UNIT_Salamander2,
		GG_UNIT_Dig2,
		GG_UNIT_Mud2,
		GG_UNIT_Frozen2,
		GG_UNIT_Metal2,			// 鎧モグラ
		GG_UNIT_MetalTreasure2,	// 鎧トレジャー
		GG_UNIT_BigMog2,
		GG_UNIT_SpaceMog2,
		GG_UNIT_BattleMog2,
		GG_UNIT_FrozenEX2,
		GG_UNIT_King2,
		GG_UNIT_Hell2,
		GG_UNIT_Ninja2,
		GG_UNIT_Punch2,
		GG_UNIT_Thunder2,
		GG_UNIT_BombBox2,
		GG_UNIT_HeroMog2,	// 勇者モグラ
		GG_UNIT_Guardian2,
		GG_UNIT_Zombie2,
		GG_UNIT_Tyranno2,	// ティラノ
		GG_UNIT_Slime2,
		GG_UNIT_Cuttlefish2,	// イカ
		GG_UNIT_ClockRabbit2,
		GG_UNIT_Chop2,
		GG_UNIT_None,		// ※未装備
		// マップチップの縁
		GG_MAPTIP_FRAME_SAND,
		GG_MAPTIP_FRAME_SOIL,
		GG_MAPTIP_FRAME_STONE,
		GG_MAPTIP_FRAME_ROCK,
		GG_MAPTIP_FRAME_OLDBONE,
		GG_MAPTIP_FRAME_METAL,
		GG_MAPTIP_FRAME_DIAMOND,
		GG_MAPTIP_FRAME_MUD,
		GG_MAPTIP_FRAME_DEEPMUD,
		GG_MAPTIP_FRAME_TREE,
		GG_MAPTIP_FRAME_RESOURCE,
		GG_MAPTIP_FRAME_BOMB,
		GG_MAPTIP_FRAME_ALARM,
		GG_MAPTIP_FRAME_WATER,
		GG_MAPTIP_FRAME_WEAKICE,
		GG_MAPTIP_FRAME_HARDICE,
		GG_MAPTIP_FRAME_ENEMYICE,
		GG_MAPTIP_FRAME_FIREROCK,
		GG_MAPTIP_FRAME_FIRE,
		GG_MAPTIP_FRAME_CONFUSE,
		GG_MAPTIP_FRAME_DARK,
		GG_MAPTIP_FRAME_DUMMY,
		GG_MAPTIP_FRAME_HARDSOIL,
		//ゲット演出
		//文字
		GG_Get_Treasure_String1,
		GG_Get_Treasure_String2,
		GG_Get_Get_String1,
		GG_Get_Get_String2,
		//クラッカー
		GG_Get_CrackerBD1,
		GG_Get_CrackerBD2,
		GG_Get_CrackerBS1,
		GG_Get_CrackerBS2,
		GG_Get_CrackerRD1,
		GG_Get_CrackerRD2,
		GG_Get_CrackerRS1,
		GG_Get_CrackerRS2,
		//紙吹雪
		GG_Get_PaperB1,
		GG_Get_PaperB2,
		GG_Get_PaperG1,
		GG_Get_PaperG2,
		GG_Get_PaperP1,
		GG_Get_PaperP2,
		GG_Get_PaperW1,
		GG_Get_PaperW2,
		//テープロール
		GG_Get_TapeRoll1,
		GG_Get_TapeRoll2,
		GG_Get_TapeRoll3,
		GG_Get_TapeRoll4,
		GG_Get_TapeRoll5,
		GG_Get_TapeRoll6,
		//テープストレート
		GG_Get_TapeSt1,
		GG_Get_TapeSt2,
		GG_Get_TapeSt3,
		GG_Get_TapeSt4,
		GG_Get_TapeSt5,
		GG_Get_TapeSt6,
		GG_Get_TapeSt7,
		GG_Get_TapeSt8,
		GG_Get_TapeSt9,
		GG_Get_TapeSt10,
		GG_Get_TapeSt11,
		GG_Get_TapeSt12,
		// モグルの下のドリル
		GG_PLAYER_Drill01,
		GG_PLAYER_Drill02,
		GG_PLAYER_Drill03,
		GG_PLAYER_Drill04,
		// タイトルモグルの下のドリル
		GG_TITLE_Drill01,
		GG_TITLE_Drill02,
		GG_TITLE_Drill03,
		GG_TITLE_Drill04,
		// 弾
		GG_BULLET_NORMAL01,
		GG_BULLET_NORMAL02,
		GG_BULLET_NORMAL03,
		GG_BULLET_NORMAL04,
		GG_BULLET_NORMAL05,
		GG_BULLET_NORMAL06,
		GG_BULLET_NORMAL07,
		GG_BULLET_NORMAL08,
		GG_BULLET_NORMAL09,
		GG_BULLET_NORMAL10,
		// 状態異常アイコン
		GG_STATUS_FIRE,
		GG_STATUS_SLOW,
		GG_STATUS_STOP,
		GG_STATUS_PARALYSIS,
		GG_STATUS_RANGE,
		GG_STATUS_CONFUSION,
		GG_STATUS_ATTACKSPEED,
		// 装備名称フォント
		GG_STRING01_BLUE,
		GG_STRING02_BLUE,
		GG_STRING03_BLUE,
		GG_STRING04_BLUE,
		GG_STRING05_BLUE,
		GG_STRING06_BLUE,
		GG_STRING07_BLUE,
		GG_STRING08_BLUE,
		GG_STRING09_BLUE,
		GG_STRING10_BLUE,
		GG_STRING01_RED,
		GG_STRING02_RED,
		GG_STRING03_RED,
		GG_STRING04_RED,
		GG_STRING05_RED,
		GG_STRING06_RED,
		GG_STRING07_RED,
		GG_STRING08_RED,
		GG_STRING09_RED,
		GG_STRING10_RED,
		GG_STRING01_GRAY,
		GG_STRING02_GRAY,
		GG_STRING03_GRAY,
		GG_STRING04_GRAY,
		GG_STRING05_GRAY,
		GG_STRING06_GRAY,
		GG_STRING07_GRAY,
		GG_STRING08_GRAY,
		GG_STRING09_GRAY,
		GG_STRING10_GRAY,
		GG_STRING11_BLUE,
		GG_STRING12_BLUE,
		GG_STRING13_BLUE,
		GG_STRING14_BLUE,
		GG_STRING15_BLUE,
		GG_STRING16_BLUE,
		GG_STRING17_BLUE,
		GG_STRING18_BLUE,
		GG_STRING19_BLUE,
		GG_STRING20_BLUE,
		GG_STRING11_RED,
		GG_STRING12_RED,
		GG_STRING13_RED,
		GG_STRING14_RED,
		GG_STRING15_RED,
		GG_STRING16_RED,
		GG_STRING17_RED,
		GG_STRING18_RED,
		GG_STRING19_RED,
		GG_STRING20_RED,
		GG_STRING11_GRAY,
		GG_STRING12_GRAY,
		GG_STRING13_GRAY,
		GG_STRING14_GRAY,
		GG_STRING15_GRAY,
		GG_STRING16_GRAY,
		GG_STRING17_GRAY,
		GG_STRING18_GRAY,
		GG_STRING19_GRAY,
		GG_STRING20_GRAY,
		GG_STRING21_BLUE,
		GG_STRING22_BLUE,
		GG_STRING23_BLUE,
		GG_STRING24_BLUE,
		GG_STRING25_BLUE,
		GG_STRING26_BLUE,
		GG_STRING27_BLUE,
		GG_STRING28_BLUE,
		GG_STRING29_BLUE,
		GG_STRING30_BLUE,
		GG_STRING21_RED,
		GG_STRING22_RED,
		GG_STRING23_RED,
		GG_STRING24_RED,
		GG_STRING25_RED,
		GG_STRING26_RED,
		GG_STRING27_RED,
		GG_STRING28_RED,
		GG_STRING29_RED,
		GG_STRING30_RED,
		GG_STRING21_GRAY,
		GG_STRING22_GRAY,
		GG_STRING23_GRAY,
		GG_STRING24_GRAY,
		GG_STRING25_GRAY,
		GG_STRING26_GRAY,
		GG_STRING27_GRAY,
		GG_STRING28_GRAY,
		GG_STRING29_GRAY,
		GG_STRING30_GRAY,
		GG_STRING31_BLUE,
		GG_STRING32_BLUE,
		GG_STRING33_BLUE,
		GG_STRING34_BLUE,
		GG_STRING35_BLUE,
		GG_STRING36_BLUE,
		GG_STRING37_BLUE,
		GG_STRING38_BLUE,
		GG_STRING39_BLUE,
		GG_STRING40_BLUE,
		GG_STRING31_RED,
		GG_STRING32_RED,
		GG_STRING33_RED,
		GG_STRING34_RED,
		GG_STRING35_RED,
		GG_STRING36_RED,
		GG_STRING37_RED,
		GG_STRING38_RED,
		GG_STRING39_RED,
		GG_STRING40_RED,
		GG_STRING31_GRAY,
		GG_STRING32_GRAY,
		GG_STRING33_GRAY,
		GG_STRING34_GRAY,
		GG_STRING35_GRAY,
		GG_STRING36_GRAY,
		GG_STRING37_GRAY,
		GG_STRING38_GRAY,
		GG_STRING39_GRAY,
		GG_STRING40_GRAY,
		GG_STRING41_BLUE,
		GG_STRING42_BLUE,
		GG_STRING43_BLUE,
		GG_STRING44_BLUE,
		GG_STRING45_BLUE,
		GG_STRING46_BLUE,
		GG_STRING47_BLUE,
		GG_STRING48_BLUE,
		GG_STRING49_BLUE,
		GG_STRING50_BLUE,
		GG_STRING41_RED,
		GG_STRING42_RED,
		GG_STRING43_RED,
		GG_STRING44_RED,
		GG_STRING45_RED,
		GG_STRING46_RED,
		GG_STRING47_RED,
		GG_STRING48_RED,
		GG_STRING49_RED,
		GG_STRING50_RED,
		GG_STRING41_GRAY,
		GG_STRING42_GRAY,
		GG_STRING43_GRAY,
		GG_STRING44_GRAY,
		GG_STRING45_GRAY,
		GG_STRING46_GRAY,
		GG_STRING47_GRAY,
		GG_STRING48_GRAY,
		GG_STRING49_GRAY,
		GG_STRING50_GRAY,
		GG_STRING51_BLUE,
		GG_STRING52_BLUE,
		GG_STRING53_BLUE,
		GG_STRING54_BLUE,
		GG_STRING55_BLUE,
		GG_STRING56_BLUE,
		GG_STRING57_BLUE,
		GG_STRING58_BLUE,
		GG_STRING59_BLUE,
		GG_STRING60_BLUE,
		GG_STRING51_RED,
		GG_STRING52_RED,
		GG_STRING53_RED,
		GG_STRING54_RED,
		GG_STRING55_RED,
		GG_STRING56_RED,
		GG_STRING57_RED,
		GG_STRING58_RED,
		GG_STRING59_RED,
		GG_STRING60_RED,
		GG_STRING51_GRAY,
		GG_STRING52_GRAY,
		GG_STRING53_GRAY,
		GG_STRING54_GRAY,
		GG_STRING55_GRAY,
		GG_STRING56_GRAY,
		GG_STRING57_GRAY,
		GG_STRING58_GRAY,
		GG_STRING59_GRAY,
		GG_STRING60_GRAY,
		//ブロックのひび割れ
		GG_BLOCK_CRACK1,
		GG_BLOCK_CRACK2,
		GG_BLOCK_CRACK3,
		// モグル本体
		GG_MOGLL_BODY_1_1,
		GG_MOGLL_BODY_2_1,
		GG_MOGLL_BODY_3_1,
		GG_MOGLL_BODY_4_1,
		GG_MOGLL_BODY_5_1,
		GG_MOGLL_BODY_1_2,
		GG_MOGLL_BODY_2_2,
		GG_MOGLL_BODY_3_2,
		GG_MOGLL_BODY_4_2,
		GG_MOGLL_BODY_5_2,
		GG_MOGLL_BODY_1_3,
		GG_MOGLL_BODY_2_3,
		GG_MOGLL_BODY_3_3,
		GG_MOGLL_BODY_4_3,
		GG_MOGLL_BODY_5_3,
		GG_MOGLL_BODY_1_4,
		GG_MOGLL_BODY_2_4,
		GG_MOGLL_BODY_3_4,
		GG_MOGLL_BODY_4_4,
		GG_MOGLL_BODY_5_4,
		// アイテム
		GG_ITEM0,
		GG_ITEM1,
		GG_ITEM2,
		GG_ITEM3,
		GG_ITEM4,
		GG_ITEM5,
		GG_ITEM6,
		GG_ITEM7,
		GG_ITEM8,
		GG_ITEM9,
		GG_ITEM10,
		GG_ITEM11,
		GG_ITEM12,
		GG_ITEM13,
		GG_ITEM14,
		GG_ITEM15,
		GG_ITEM16,
		GG_ITEM17,
		GG_ITEM18,
		GG_ITEM19,
		GG_ITEM20,
		GG_ITEM21,
		GG_ITEM22,
		GG_ITEM23,
		GG_ITEM24,
		GG_ITEM25,
		GG_ITEM26,
		GG_ITEM27,
		GG_ITEM28,
		GG_ITEM29,
		GG_ITEM30,
		GG_ITEM31,
		GG_ITEM32,
		GG_ITEM33,
		GG_ITEM34,
		GG_ITEM35,
		GG_ITEM36,
		GG_ITEM37,
		GG_ITEM38,
		GG_ITEM39,
		GG_ITEM40,
		GG_ITEM41,
		GG_ITEM42,
		GG_ITEM43,
		GG_ITEM44,
		GG_ITEM45,
		GG_ITEM46,
		GG_ITEM47,
		GG_ITEM48,
		GG_ITEM49,
		GG_ITEM50,
		GG_ITEM51,
		GG_ITEM52,
		GG_ITEM53,
		GG_ITEM54,
		GG_ITEM55,
		GG_ITEM56,
		GG_ITEM57,
		GG_ITEM58,
		GG_ITEM59,
		GG_ITEM60,

		GraphicGroupIndexMax					//常に最後にする
	};
	// 音楽
	enum SoundSet
	{
		SoundBGM01,								//タイトル
		SoundBGM02,								//ステージセレクト
		SoundBGM03,								//ステージスタート
		SoundBGM04,								//ステージ１_遺跡
		SoundBGM05,								//ステージ２_氷
		SoundBGM06,								//ステージ３_沼地
		SoundBGM07,								//ステージ４_マグマ
		SoundBGM08,								//ステージ５_トラップ
		SoundBGM09,								//ファンファーレ
		SoundBGM10,								//ゲームオーバー
		SoundSE01,								//アイテムゲット
		SoundSE02,								//インベントリオープン
		SoundSE03,								//カットイン_キラキラ
		SoundSE04,								//カットイン_拍手
		SoundSE04_2,							//カットイン_拍手
		SoundSE04_3,							//カットイン_拍手
		SoundSE05,								//カットイン・カットアウト
		SoundSE06,								//キャンセル
		SoundSE07,								//システム音
		SoundSE08,								//シャトルブースター
		SoundSE09,								//シャトル移動
		SoundSE10,								//スタート音
		SoundSE11,								//ステージカーソル
		SoundSE12,								//ステージズームイン
		SoundSE13,								//タイトル_モグル埋まり
		SoundSE14,								//タイトル岩壊れ
		SoundSE15,								//タイトル岩掘
		SoundSE16,								//ダメージ
		SoundSE17,								//ミミック変身
		SoundSE18,								//ユニット設置
		SoundSE19,								//ユニット選択
		SoundSE20,								//ユニット発射
		SoundSE21,								//暗闇
		SoundSE22,								//化石破壊
		SoundSE23,								//火音
		SoundSE24,								//回復音
		SoundSE25,								//岩破壊
		SoundSE26,								//強化
		SoundSE27,								//掘る音
		SoundSE28,								//決定
		SoundSE29,								//穴に入る
		SoundSE30,								//項目選択
		SoundSE31,								//混乱
		SoundSE32,								//砂破壊
		SoundSE33,								//死亡
		SoundSE34,								//資源収集
		SoundSE35,								//資源なし
		SoundSE36,								//弱化
		SoundSE37,								//召喚アラーム
		SoundSE38,								//装備ユニット変更
		SoundSE39,								//着陸音
		SoundSE40,								//停止音
		SoundSE41,								//敵登場
		SoundSE42,								//敵破壊
		SoundSE43,								//電気音
		SoundSE44,								//電撃ダメージ
		SoundSE45,								//凍結
		SoundSE46,								//粘土破壊
		SoundSE47,								//破壊不可
		SoundSE48,								//爆発音
		SoundSE49,								//秘宝
		SoundSE50,								//飛び出し音
		SoundSE51,								//氷破壊
		SoundSE52,								//砲台の攻撃
		SoundSE53,								//麻痺
		SoundSE54,								//クラッカー
		SoundSE55,								//モグル着地
		SoundSE56,								//マグマ＿イン
		SoundSE57,								//水中＿イン
		SoundMax								//常に最後にする
	};
	// リソースセット
	enum ResourceSet
	{
		ResourceSetNone,
		ResourceSetTitle,
		ResourceSetPlay,
		ResourceSetStageSelect
	};
	enum LoadStatuse
	{
		UNDEFINE
	};
	enum ItemStatus
	{
		ITEM_NOT_FIND,		// 0未発見
		ITEM_NEW,			// 1新しく手に入れたもの
		ITEM_EXIST,			// 2有る
		ITEM_NO_EXIST,		// 3無い
		ITEM_EQUIP,			// 4装備中
		ITEM_CANMIX,		// 5合成できる:新しく合成できるようになったもの
		ITEM_CANMIX_EXIST,	// 6合成できる:持ったことがある
		ITEM_MATERIAL,		// 7合成素材になっている
		ITEM_MIX,			// 8合成されている
		ITEM_MIX_EQUIP		// 9合成されている:装備中
	};
	// 装備品の画像
	enum EquipItemImage{
		EI_IMAGE_Gear,
		EI_IMAGE_Iron,
		EI_IMAGE_Drill,
		EI_IMAGE_Circuit,
		EI_IMAGE_Sword,
		EI_IMAGE_Orb,
		EI_IMAGE_Medal
	};
	StoreData m_SaveData;
	// 外部から読みだしたシステムデータ
	struct GameSystemData
	{
		struct Equip
		{
			char name[32];
			char text[256];
			char shortText[32];
			int a, b;
		} equip[60];
		struct Unit
		{
			char name[32];
			char text[256];
			int cost;
			float rang;
			int power;
			float aSpd;
			int hp;
			float spd;
		} unit[30];
		struct Block
		{
			char name[32];
			char text[256];
			int resource;
			int hp;
			int moveType;
			int priority;
			int damage;
		} block[34];
		struct TreasurePosition
		{
			int id, x, y, isEnemy, life;
		} treasure[54];
		struct Challenge
		{
			char text[256];
		} challenge[100];
	}m_SystemData;
	// モグル関係のステータス
	struct MogllStatus{
		VECTOR position;
		int maxLife;		// 最大耐久値
		int life;			// 耐久値
		int maxResource;	// 最大資源値
		int resource;		// 資源値
		int equip[3];		// 装備中の装備
		int equipUnit[6];	// 装着中のユニット
		int treasureStatus;	// お宝発見状態。通常-1、見つけた時宝のIDが入る
		int currentUnitID;	// 現在出撃準備中のユニットID
		int equipStatus[3];	// 装備のスキル発動状態
		int frameSkip;		// フレームを飛ばすフラグ
		int unitCount[30];	// 召喚できるユニット残数
		int noHitTime;		// 無敵時間	
	}m_MogllStatus;
private:
	// 分割画像
	enum GraphicGroupSet
	{
		GraphicGroupMaptip01,					// ブロックマップチップ
		GraphicGroupExplode,					// 爆発アニメ
		GraphicGroupItemBG,						// アイテム背景
		GraphicGroupUnit,						// ユニット画像
		GraphicGroupUnit2,						// ユニット画像2
		GraphicGroupMaptip02,					// ブロックの縁
		GraphicGroupGetString1,					// お宝:文字
		GraphicGroupGetString2,					// ゲット:文字
		GraphicGroupGetCracker,					// クラッカー
		GraphicGroupGetPaper,					// 紙吹雪
		GraphicGroupGetTapeRoll,				// テープロール
		GraphicGroupGetTapeSt,					// テープストレート
		GraphicGroupDrill,						// モグルの下のドリル
		GraphicGroupTitleDrill,					// タイトルのドリルアニメ
		GraphicGroupBullet,						// 弾
		GraphicGroupStatus,						// 状態異常アイコン
		GraphicGroupString,						// 装備名称フォント
		GraphicGroupBlockCrack,					// ブロックひび割れ
		GraphicGroupMogll,						// モグル本体
		GraphicGroupEquip,						// アイテム画像
		GraphicGroupMax							//常に最後にする
	};
	// 分割画像読み込みデータ
	struct GraphicGroupData
	{
		std::string path;
		int numX, numY;
		int width, height;
		int allNum;
		int *handle;
	};

	ResourceSet m_ResourceID;								// 現在設定されているリソースセット
	std::string m_GraphicPath[GraphicMax];					// 事前に登録されている画像までのパス
	std::string m_SoundPath[SoundMax];						// 事前に登録されている音楽までのパス
	int m_GraphicHandle[GraphicMax];						// グラフィックハンドル
	int m_SoundHandle[SoundMax];							// 音楽ハンドル
	GraphicGroupData m_GraphicGroupData[GraphicGroupMax];	// 分割画像読み込みデータ
	// プライベートコンストラクタ
	DataManager(void);
	void SetMaptipData(GraphicGroupData *data, char *filePath, int allNum, int numX, int numY, int width, int height);
	// リソースセットの実装
	void SetTitle(BoolArray *graph, BoolArray *sound, BoolArray *maptip);
	void SetPlay(BoolArray *graph, BoolArray *sound, BoolArray *maptip);
	void SetStageSelect(BoolArray *graph, BoolArray *sound, BoolArray *maptip);
public:
	~DataManager(void);
	// シーン間のやり取りにはマップを使用
	std::map<std::string, int> m_SceneInt;					// シーン間の情報やり取り様のマップint版
	std::map<std::string, float> m_SceneFloat;				// シーン間の情報やり取り様のマップfloat版
	// ResourceSetのデータセットをロードする
	void Load(ResourceSet set);
	// 指定したIDのリソースハンドルを返す
	// リソースがセットされていなかった場合、その場でロードする
	int Get(GraphicSet graph);
	int Get(SoundSet sound);
	int Get(GraphicGroupIndex graphIdx);
	int GetGraphicGroupData(int index);
	// 全データを開放し、初期化する
	void Release(void);
	// メモリを開放する
	void MemRelease(void);
	// セーブデータをロードする
	void LoadData(char *filePath);
	// 現在のデータをセーブする
	void SaveData(void);
	//インスタンス取得
	static DataManager& GetInstance(void)
	{
		static DataManager dataManager;
		return dataManager;
	}

	// 装備ID
	enum EquipmentID
	{
		EqID_01,
		EqID_02,
		EqID_03,
		EqID_04,
		EqID_05,
		EqID_06,
		EqID_07,
		EqID_08,
		EqID_09,
		EqID_10,
		EqID_11,
		EqID_12,
		EqID_13,
		EqID_14,
		EqID_15,
		EqID_16,
		EqID_17,
		EqID_18,
		EqID_19,
		EqID_20,
		EqID_21,
		EqID_22,
		EqID_23,
		EqID_24,
		EqID_25,
		EqID_26,
		EqID_27,
		EqID_28,
		EqID_29,
		EqID_30,
		EqID_31,
		EqID_32,
		EqID_33,
		EqID_34,
		EqID_35,
		EqID_36,
		EqID_37,
		EqID_38,
		EqID_39,
		EqID_40,
		EqID_41,
		EqID_42,
		EqID_43,
		EqID_44,
		EqID_45,
		EqID_46,
		EqID_47,
		EqID_48,
		EqID_49,
		EqID_50,
		EqID_51,
		EqID_52,
		EqID_53,
		EqID_54,
		EqID_55,
		EqID_56,
		EqID_57,
		EqID_58,
		EqID_59,
		EqID_60		// 虹色の宝石
	};
};

