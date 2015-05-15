#include "DataManager.h"
#include "string.h"
#include "../Menu/MixTreeData.h"
#include "../Menu/MenuIconSort.h"

DataManager::DataManager(void)
{
	memset(m_GraphicHandle, UNDEFINE, sizeof(m_GraphicHandle));
	memset(m_SoundHandle, UNDEFINE, sizeof(m_SoundHandle));
	// 全リソースのパスだけ予め登録しておく
	// 画像のパス登録
	// ステージセレクト
	m_GraphicPath[Cur_stage].assign("resource/texture/StageSelect/Cur_stage.png");
	m_GraphicPath[Ic_stage1].assign("resource/texture/StageSelect/Ic_stage1.png");
	m_GraphicPath[Ic_stage2].assign("resource/texture/StageSelect/Ic_stage2.png");
	m_GraphicPath[Ic_stage3].assign("resource/texture/StageSelect/Ic_stage3.png");
	m_GraphicPath[Ic_stage4].assign("resource/texture/StageSelect/Ic_stage4.png");
	m_GraphicPath[Ic_stage5].assign("resource/texture/StageSelect/Ic_stage5.png");
	m_GraphicPath[Ic_stage1_Back].assign("resource/texture/StageSelect/Ic_stage1_Back.png");
	m_GraphicPath[Ic_stage2_Back].assign("resource/texture/StageSelect/Ic_stage2_Back.png");
	m_GraphicPath[Ic_stage3_Back].assign("resource/texture/StageSelect/Ic_stage3_Back.png");
	m_GraphicPath[Ic_stage4_Back].assign("resource/texture/StageSelect/Ic_stage4_Back.png");
	m_GraphicPath[Ic_stage5_Back].assign("resource/texture/StageSelect/Ic_stage5_Back.png");
	m_GraphicPath[Spaceship].assign("resource/texture/StageSelect/Spaceship.png");
	m_GraphicPath[JetRing].assign("resource/texture/StageSelect/JetRing.png");
	m_GraphicPath[StageInfo_Bar].assign("resource/texture/StageSelect/StageInfo_Bar.png");
	m_GraphicPath[StageSelect_Background].assign("resource/texture/StageSelect/StageSelect_Background.png");
	m_GraphicPath[StageSelect_Frame].assign("resource/texture/StageSelect/StageSelect_Frame.png");
	m_GraphicPath[StageSelect_Frame_Back].assign("resource/texture/StageSelect/StageSelect_Frame_Back.png");
	m_GraphicPath[StageSelect_FrameCharacter].assign("resource/texture/StageSelect/StageSelect_FrameCharacter.png");
	m_GraphicPath[StageSelect_FrameCharacter_Add].assign("resource/texture/StageSelect/StageSelect_FrameCharacter_add.png");
	m_GraphicPath[Unit_shuttle].assign("resource/texture/StageSelect/Unit_shuttle.png");
	m_GraphicPath[Ic_stage_Cascade].assign("resource/texture/StageSelect/Ic_stage_Cascade.png");

	//メニューリソースパス
	m_GraphicPath[Equipment_Font_Frame].assign("resource/texture/Menu/Equipment_Font_Frame.png");						//
	m_GraphicPath[Equipment_Icon_Frame].assign("resource/texture/Menu/Equipment_Icon_Frame.png");						//
	m_GraphicPath[Menu_StageMask].assign("resource/texture/Menu/Menu_StageMask.png");									//
	m_GraphicPath[Equipment_sin].assign	("resource/texture/Menu/Equipment_sin.png");									//装備時の"E"シンボル
	m_GraphicPath[New_sin].assign		("resource/texture/Menu/New_sin.png");											//新しいものの"New"シンボル
	m_GraphicPath[Icon_Description_Frame].assign("resource/texture/Menu/Icon_Description_Frame.png");					//装備・ユニットの説明の背景
	m_GraphicPath[Menu_Background].assign("resource/texture/Menu/Menu_Background.png");									//インベントリの背景
	m_GraphicPath[Question_ic].assign("resource/texture/Menu/Question_ic.png");											//未獲得品の表示用？アイコン
	m_GraphicPath[Invently_ic].assign("resource/texture/Menu/Invently_ic.png");											//インベントリ開くアイコン
	m_GraphicPath[Confirmation_Frame].assign("resource/texture/Menu/Confirmation_Frame.png");							//確認時枠
	m_GraphicPath[Click].assign		("resource/texture/Menu/Click.png");												//クリック説明画像
	m_GraphicPath[RightClick].assign("resource/texture/Menu/RightClick.png");											//右クリック説明画像

	m_GraphicPath[test].assign("resource/texture/cursor_test.png");
	// タイトルリソースパス
	m_GraphicPath[Team_logo].assign("resource/texture/Title/Team_logo.png");
	m_GraphicPath[Title_stone].assign("resource/texture/Title/Title_stone.png");
	m_GraphicPath[Title_stone_break_left].assign("resource/texture/Title/Title_stone_break_left.png");
	m_GraphicPath[Title_stone_break_right].assign("resource/texture/Title/Title_stone_break_right.png");
	m_GraphicPath[Title_stone_Crack1].assign("resource/texture/Title/Title_stone_Crack1.png");
	m_GraphicPath[Title_stone_Crack2].assign("resource/texture/Title/Title_stone_Crack2.png");
	m_GraphicPath[Title_stone_Crack3].assign("resource/texture/Title/Title_stone_Crack3.png");
	m_GraphicPath[Title_stone_Crash1].assign("resource/texture/Title/Title_stone_Crash1.png");
	m_GraphicPath[Title_stone_Crash2].assign("resource/texture/Title/Title_stone_Crash2.png");
	m_GraphicPath[Title_logo].assign("resource/texture/Title/Title_logo.png");
	m_GraphicPath[Title_logo_Back].assign("resource/texture/Title/Title_logo_Back.png");
	m_GraphicPath[Block_soil].assign("resource/texture/Title/Block_soil.png");
	m_GraphicPath[Block_soilsub].assign("resource/texture/Title/Block_soilsub.png");
	m_GraphicPath[Block_stone].assign("resource/texture/Title/Block_stone.png");
	m_GraphicPath[Block_Rock].assign("resource/texture/Title/Block_Rock.png");
	m_GraphicPath[Unit_moguru].assign("resource/texture/Title/Unit_moguru.png");
	m_GraphicPath[Unit_moguru_chest].assign("resource/texture/Title/Unit_moguru_chest.png");
	m_GraphicPath[Title_Back].assign("resource/texture/Title/Title_Back.png");
	m_GraphicPath[Start1].assign("resource/texture/Title/Start1.png");
	m_GraphicPath[Start2].assign("resource/texture/Title/Start2.png");
	m_GraphicPath[Start3].assign("resource/texture/Title/Start3.png");
	m_GraphicPath[Start4].assign("resource/texture/Title/Start4.png");
	m_GraphicPath[StartBack].assign("resource/texture/Title/StartBack.png");
	m_GraphicPath[Unit_moguru_top].assign("resource/texture/Title/Unit_moguru_top.png");
	m_GraphicPath[Unit_moguru_under].assign("resource/texture/Title/Unit_moguru_under.png");

	// プレイ中リソースパス
	m_GraphicPath[Play_MogllUp].assign("resource/texture/Object/Game_Mogll_Body.png");
	m_GraphicPath[GameStart_Menu].assign("resource/texture/Object/GameStart_Menu.png");
	m_GraphicPath[GameStart_Icon_Go].assign("resource/texture/Object/GameStart_Icon_Go.png");
	m_GraphicPath[Play_GetTreasure_BG].assign("resource/texture/Object/Play_Treasure_Cutin.png");
	m_GraphicPath[red_shot].assign("resource/texture/Object/red_shot.png");
	m_GraphicPath[yellow_shot].assign("resource/texture/Object/yellow_shot.png");
	m_GraphicPath[blue_shot].assign("resource/texture/Object/blue_shot.png");
	m_GraphicPath[Play_Treasure_Tree2].assign("resource/texture/Get/Tree/Play_Treasure_Tree2.png");
	m_GraphicPath[Play_Treasure_Tree3].assign("resource/texture/Get/Tree/Play_Treasure_Tree3.png");
	m_GraphicPath[Play_Treasure_Tree4].assign("resource/texture/Get/Tree/Play_Treasure_Tree4.png");
	m_GraphicPath[Play_TreasureBox].assign("resource/texture/Object/TreasureBox.png");
	m_GraphicPath[Play_MapBox].assign("resource/texture/Object/MapBox.png");
	//ChangeVolumeSoundMem( int VolumePal , int SoundHandle ) ;
	// 右側UI
	m_GraphicPath[Play_Playmode_UI].assign("resource/texture/UI/Playmode_UI.png");
	m_GraphicPath[Play_UnitCreate_Frame].assign("resource/texture/UI/UnitCreate_Frame.png");
	m_GraphicPath[Play_UI_Line].assign("resource/texture/UI/line.png");
	m_GraphicPath[Play_UI_Radar_enemy_marker].assign("resource/texture/UI/Radar_enemy_marker.png");
	m_GraphicPath[Play_UI_Radar_treasure_marker].assign("resource/texture/UI/Radar_treasure_marker.png");
	m_GraphicPath[Play_UI_Rader].assign("resource/texture/UI/Rader.png");
	m_GraphicPath[Play_UI_Escape_Button].assign("resource/texture/UI/Play_Escape_Graph.png");
	m_GraphicPath[Play_UI_Escape_Button_Red].assign("resource/texture/UI/Button_Red.png");
	m_GraphicPath[Play_UI_Escape_Button_Yellow].assign("resource/texture/UI/Button_Yellow.png");
	m_GraphicPath[Play_UI_Escape_Button_Blue].assign("resource/texture/UI/Button_Blue.png");
	m_GraphicPath[Play_UI_Rader_GreenLine].assign("resource/texture/UI/Rader_GreenLine.png");
	m_GraphicPath[Play_UI_Rader_RedLine].assign("resource/texture/UI/Rader_RedLine.png");
	m_GraphicPath[Play_UI_Play_HelpButton].assign("resource/texture/UI/Play_HelpButton.png");
	m_GraphicPath[Play_UI_Meter_Panel].assign("resource/texture/UI/Play_UI_Meter_Panel.png");
	m_GraphicPath[Play_UI_Meter_GreenArrow].assign("resource/texture/UI/Play_UI_Meter_GreenArrow.png");
	m_GraphicPath[Play_UI_Meter_RedArrow].assign("resource/texture/UI/Play_UI_Meter_RedArrow.png");
	m_GraphicPath[Play_UI_Damage].assign("resource/texture/UI/Play_UI_Damage.png");

	//お宝取得演出
	m_GraphicPath[Play_Treasure_Shine].assign					("resource/texture/Get/Play_Treasure_Shine.png");
	m_GraphicPath[Play_Treasure_Mogll_Graph].assign				("resource/texture/Get/Play_Treasure_Mogll_Graph_Front.png");
	m_GraphicPath[Play_Treasure_Mogll_Graph_Back].assign		("resource/texture/Get/Play_Treasure_Mogll_Graph_Back.png");
	m_GraphicPath[Play_Treasure_Mogll_Graph_BoX_Blue].assign	("resource/texture/Get/Play_Treasure_Mogll_Graph_Box_Blue.png");
	m_GraphicPath[Play_Treasure_Mogll_Graph_BoX_Pink].assign	("resource/texture/Get/Play_Treasure_Mogll_Graph_Box_Pink.png");

	// プレイ階層選択リソースパス
	m_GraphicPath[Floor_Number_1].assign("resource/texture/StageStart/Floor_Number_1.png");
	m_GraphicPath[Floor_Number_2].assign("resource/texture/StageStart/Floor_Number_2.png");
	m_GraphicPath[Floor_Number_3].assign("resource/texture/StageStart/Floor_Number_3.png");
	m_GraphicPath[Floor_Number_4].assign("resource/texture/StageStart/Floor_Number_4.png");
	m_GraphicPath[Floor_Number_5].assign("resource/texture/StageStart/Floor_Number_5.png");
	m_GraphicPath[Floor_Number_6].assign("resource/texture/StageStart/Floor_Number_6.png");
	m_GraphicPath[Floor_Number_7].assign("resource/texture/StageStart/Floor_Number_7.png");
	m_GraphicPath[Floor_Number_8].assign("resource/texture/StageStart/Floor_Number_8.png");
	m_GraphicPath[Floor_Number_9].assign("resource/texture/StageStart/Floor_Number_9.png");
	m_GraphicPath[Play_Button_Floor].assign("resource/texture/StageStart/Play_Button_Floor.png");
	m_GraphicPath[Play_Button_Floor_Down].assign("resource/texture/StageStart/Play_Button_Floor_Down.png");
	m_GraphicPath[Play_Button_Go].assign("resource/texture/StageStart/Play_Button_Go.png");
	m_GraphicPath[Play_Button_Go_Down].assign("resource/texture/StageStart/Play_Button_Go_Down.png");
	m_GraphicPath[Play_Challenge].assign("resource/texture/StageStart/Play_Challenge.png");
	m_GraphicPath[Play_Challenge_Seet].assign("resource/texture/StageStart/Play_Challenge_Seet.png");
	m_GraphicPath[StageSelect_Star].assign("resource/texture/StageStart/StageSelect_Star.png");

	// ゲームクリア画像パス登録
	m_GraphicPath[Play_Graph_Clear1].assign("resource/texture/GameClear/Play_Graph_Clear1.png");
	m_GraphicPath[Play_Graph_Clear2].assign("resource/texture/GameClear/Play_Graph_Clear2.png");
	m_GraphicPath[Play_Graph_Clear3].assign("resource/texture/GameClear/Play_Graph_Clear3.png");
	m_GraphicPath[Play_Graph_Clear4].assign("resource/texture/GameClear/Play_Graph_Clear4.png");
	m_GraphicPath[Play_Graph_Clear5].assign("resource/texture/GameClear/Play_Graph_Clear5.png");
	m_GraphicPath[Play_Graph_Clear6].assign("resource/texture/GameClear/Play_Graph_Clear6.png");
	m_GraphicPath[Play_Graph_Clear7].assign("resource/texture/GameClear/Play_Graph_Clear7.png");
	m_GraphicPath[Play_Graph_Clear8].assign("resource/texture/GameClear/Play_Graph_Clear8.png");
	m_GraphicPath[Play_Graph_Clear9].assign("resource/texture/GameClear/Play_Graph_Clear9.png");

	// ゲームオーバー画像パス登録
	m_GraphicPath[Moguru_Salvage1].assign("resource/texture/GameOver/Moguru_Salvage1.png");
	m_GraphicPath[Moguru_Salvage2].assign("resource/texture/GameOver/Moguru_Salvage2.png");
	m_GraphicPath[Moguru_Salvage3].assign("resource/texture/GameOver/Moguru_Salvage3.png");
	m_GraphicPath[Play_Graph_Dead1].assign("resource/texture/GameOver/Play_Graph_Dead1.png");
	m_GraphicPath[Play_Graph_Dead2].assign("resource/texture/GameOver/Play_Graph_Dead2.png");
	m_GraphicPath[Play_Graph_Dead3].assign("resource/texture/GameOver/Play_Graph_Dead3.png");
	m_GraphicPath[Play_Graph_Dead4].assign("resource/texture/GameOver/Play_Graph_Dead4.png");

	// プレイ開始時背景画像パス登録
	// 地下都市
	m_GraphicPath[Stage_Chikatoshi_1].assign("resource/texture/StageBack/Chikatoshi/Stage_Chikatoshi_1.png");
	m_GraphicPath[Stage_Chikatoshi_2].assign("resource/texture/StageBack/Chikatoshi/Stage_Chikatoshi_2.png");
	m_GraphicPath[Stage_Chikatoshi_3].assign("resource/texture/StageBack/Chikatoshi/Stage_Chikatoshi_3.png");
	m_GraphicPath[Stage_Chikatoshi_4].assign("resource/texture/StageBack/Chikatoshi/Stage_Chikatoshi_4.png");
	m_GraphicPath[Stage_Chikatoshi_Sky].assign("resource/texture/StageBack/Chikatoshi/Stage_Chikatoshi_Sky.png");
	m_GraphicPath[Stage_Chikatoshi_Effect].assign(	"resource/texture/StageBack/Chikatoshi/Stage_Chikatoshi_Filter1.png");
	// 氷河
	m_GraphicPath[Stage_Hyoukai_1].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_1.png");
	m_GraphicPath[Stage_Hyoukai_2].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_2.png");
	m_GraphicPath[Stage_Hyoukai_3].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_3.png");
	m_GraphicPath[Stage_Hyoukai_4].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_4.png");
	m_GraphicPath[Stage_Hyoukai_5].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_5.png");
	m_GraphicPath[Stage_Hyoukai_Sky].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_Sky.png");
	m_GraphicPath[Stage_Hyoukai_Effect1].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_Filter1.png");
	m_GraphicPath[Stage_Hyoukai_Effect2].assign("resource/texture/StageBack/Hyoukai/Stage_Hyoukai_Filter2.png");
	// 火山
	m_GraphicPath[Stage_Maguma_1].assign("resource/texture/StageBack/Maguma/Stage_Maguma_1.png");
	m_GraphicPath[Stage_Maguma_2].assign("resource/texture/StageBack/Maguma/Stage_Maguma_2.png");
	m_GraphicPath[Stage_Maguma_3].assign("resource/texture/StageBack/Maguma/Stage_Maguma_3.png");
	m_GraphicPath[Stage_Maguma_4].assign("resource/texture/StageBack/Maguma/Stage_Maguma_4.png");
	m_GraphicPath[Stage_Maguma_Sky].assign("resource/texture/StageBack/Maguma/Stage_Maguma_Sky.png");	
	m_GraphicPath[Stage_Maguma_Effect1].assign("resource/texture/StageBack/Maguma/Stage_Maguma_Filter1.png");
	m_GraphicPath[Stage_Maguma_Effect2].assign("resource/texture/StageBack/Maguma/Stage_Maguma_Filter2.png");
	// 沼地
	m_GraphicPath[Stage_Numachi_1].assign("resource/texture/StageBack/Numachi/Stage_Numachi_1.png");
	m_GraphicPath[Stage_Numachi_1_ani].assign("resource/texture/StageBack/Numachi/Stage_Numachi_1_ani.png");
	m_GraphicPath[Stage_Numachi_2].assign("resource/texture/StageBack/Numachi/Stage_Numachi_2.png");
	m_GraphicPath[Stage_Numachi_3].assign("resource/texture/StageBack/Numachi/Stage_Numachi_3.png");
	m_GraphicPath[Stage_Numachi_4].assign("resource/texture/StageBack/Numachi/Stage_Numachi_4.png");
	m_GraphicPath[Stage_Numachi_5].assign("resource/texture/StageBack/Numachi/Stage_Numachi_5.png");
	m_GraphicPath[Stage_Numachi_Sky].assign("resource/texture/StageBack/Numachi/Stage_Numachi_Sky.png");
	m_GraphicPath[Stage_Numachi_Effect1].assign("resource/texture/StageBack/Numachi/Stage_Numachi_Filter1.png");
	m_GraphicPath[Stage_Numachi_Effect2].assign("resource/texture/StageBack/Numachi/Stage_Numachi_Filter2.png");
	// 近未来
	m_GraphicPath[Stage_Kinmirai_1].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_1.png");
	m_GraphicPath[Stage_Kinmirai_2].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_2.png");
	m_GraphicPath[Stage_Kinmirai_3].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_3.png");
	m_GraphicPath[Stage_Kinmirai_4].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_4.png");
	m_GraphicPath[Stage_Kinmirai_Sky].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_Sky.png");
	m_GraphicPath[Stage_Kinmirai_Effect1].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_Filter1.png");
	m_GraphicPath[Stage_Kinmirai_Effect2].assign("resource/texture/StageBack/Kinmirai/Stage_Kinmirai_Filter2.png");

	// チュートリアルパス登録
	m_GraphicPath[Help_BG].assign("resource/texture/Tutorial/Help_BG.png");
	m_GraphicPath[Help_Label].assign("resource/texture/Tutorial/Help_Label.png");
	m_GraphicPath[Help_Index].assign("resource/texture/Tutorial/Help_Index.png");
	m_GraphicPath[Help_Button_Back].assign("resource/texture/Tutorial/Help_Button_Back.png");
	m_GraphicPath[Help_Button_Prev].assign("resource/texture/Tutorial/Help_Button_Prev.png");
	m_GraphicPath[Help_Button_Next].assign("resource/texture/Tutorial/Help_Button_Next.png");
	m_GraphicPath[Help_Button_Close].assign("resource/texture/Tutorial/Help_Button_Close.png");
	m_GraphicPath[Description1].assign("resource/texture/Tutorial/Description1.png");
	m_GraphicPath[Description2_1].assign("resource/texture/Tutorial/Description2_1.png");
	m_GraphicPath[Description2_2].assign("resource/texture/Tutorial/Description2_2.png");
	m_GraphicPath[Description3].assign("resource/texture/Tutorial/Description3.png");
	m_GraphicPath[Description4_1].assign("resource/texture/Tutorial/Description4_1.png");
	m_GraphicPath[Description4_2].assign("resource/texture/Tutorial/Description4_2.png");
	m_GraphicPath[Description5_1].assign("resource/texture/Tutorial/Description5_1.png");
	m_GraphicPath[Description5_2].assign("resource/texture/Tutorial/Description5_2.png");
	m_GraphicPath[Description6].assign("resource/texture/Tutorial/Description6.png");
	m_GraphicPath[Description7_1].assign("resource/texture/Tutorial/Description7_1.png");
	m_GraphicPath[Description7_2].assign("resource/texture/Tutorial/Description7_2.png");
	m_GraphicPath[Description8].assign("resource/texture/Tutorial/Description8.png");

	// 脱出確認ウィンドウのボタン
	m_GraphicPath[EscapeButton].assign("resource/texture/Menu/button.png");

	// 分割画像のパス登録
	SetMaptipData(&m_GraphicGroupData[GraphicGroupMaptip01]		, "resource/texture/Map/maptip.png", 28, 6, 5, 40, 40);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupExplode]		, "resource/texture/Anim/explode.png", 7, 7, 1, 120, 120);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupItemBG]		, "resource/texture/Menu/Item_ic_BG.png", 7, 1, 7, 40, 40 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupUnit]			, "resource/texture/Object/unit.png", 30, 6, 6, 40, 40 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupUnit2]		, "resource/texture/Object/unit2.png", 31, 6, 6, 40, 40 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupMaptip02]		, "resource/texture/Map/maptip_frame.png", 23, 6, 6, 40, 40 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupDrill]		, "resource/texture/Object/Game_Mogll_Drill.png", 4, 4, 1, 164, 172);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupTitleDrill]	, "resource/texture/Title/Unit_moguru_anime.png", 4, 4, 1, 370, 388);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupBullet]		, "resource/texture/Anim/bullet.png", 10, 10, 1, 256, 256);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupStatus]		, "resource/texture/Object/status.png", 7, 7, 1, 15, 15);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupString]		, "resource/texture/Object/equipfont.png", 180, 10, 18, 146, 20);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupBlockCrack]	, "resource/texture/Map/Play_Block_Crack.png", 3, 1, 3, 40, 40);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupMogll]		, "resource/texture/Object/Game_Mogll_Body.png", 20, 5, 4, 100, 100);
	SetMaptipData(&m_GraphicGroupData[GraphicGroupEquip]		, "resource/texture/Object/equipment.png",60, 8, 8, 40, 40 );

	//お宝取得演出
	SetMaptipData(&m_GraphicGroupData[GraphicGroupGetString1]	, "resource/texture/Get/Play_Treasure_Get_OTAKARA.png", 2, 1, 2, 302, 207 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupGetString2]	, "resource/texture/Get/Play_Treasure_Get_GET.png", 2, 1, 2, 500, 205 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupGetCracker]	, "resource/texture/Get/Play_Treasure_Cracker.png", 8, 4, 2, 100, 110 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupGetPaper]		, "resource/texture/Get/Play_Treasure_Ticker.png", 8, 1, 8, 56, 50 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupGetTapeRoll]	, "resource/texture/Get/Play_Treasure_Tape_Roll.png", 6, 3, 2, 136, 100 );
	SetMaptipData(&m_GraphicGroupData[GraphicGroupGetTapeSt]	, "resource/texture/Get/Play_Treasure_Tape_Straight.png", 12, 4, 3, 100, 146 );

	// 音楽のパス登録
	
	m_SoundPath[SoundBGM01].assign("resource/sound/BGM/BGM_Title.mp3");
	m_SoundPath[SoundBGM02].assign("resource/sound/BGM/BGM_StageSelect.mp3");
	m_SoundPath[SoundBGM03].assign("resource/sound/BGM/BGM_Stage_Intro.mp3");
	m_SoundPath[SoundBGM04].assign("resource/sound/BGM/BGM_Stage1.mp3");
	m_SoundPath[SoundBGM05].assign("resource/sound/BGM/BGM_Stage2.mp3");
	m_SoundPath[SoundBGM06].assign("resource/sound/BGM/BGM_Stage3.mp3");
	m_SoundPath[SoundBGM07].assign("resource/sound/BGM/BGM_Stage4.mp3");
	m_SoundPath[SoundBGM08].assign("resource/sound/BGM/BGM_Stage5.mp3");
	m_SoundPath[SoundBGM09].assign("resource/sound/BGM/BGM_Fanfare.mp3");
	m_SoundPath[SoundBGM10].assign("resource/sound/BGM/BGM_Gameover.mp3");
	m_SoundPath[SoundSE01].assign("resource/sound/SE/ItemGet.mp3");
	m_SoundPath[SoundSE02].assign("resource/sound/SE/InventoryOpen.mp3");
	m_SoundPath[SoundSE03].assign("resource/sound/SE/KiraKira.mp3");
	m_SoundPath[SoundSE04].assign("resource/sound/SE/Clap.mp3");
	m_SoundPath[SoundSE04_2].assign("resource/sound/SE/Clap.mp3");
	m_SoundPath[SoundSE04_3].assign("resource/sound/SE/Clap.mp3");
	m_SoundPath[SoundSE05].assign("resource/sound/SE/Cutin.mp3");
	m_SoundPath[SoundSE06].assign("resource/sound/SE/Cancel.mp3");
	m_SoundPath[SoundSE07].assign("resource/sound/SE/MouseOver.mp3");
	m_SoundPath[SoundSE08].assign("resource/sound/SE/Shuttlebooster.mp3");
	m_SoundPath[SoundSE09].assign("resource/sound/SE/Shuttle.mp3");
	m_SoundPath[SoundSE10].assign("resource/sound/SE/GameStart.mp3");
	m_SoundPath[SoundSE11].assign("resource/sound/SE/System.mp3");
	m_SoundPath[SoundSE12].assign("resource/sound/SE/Zoomin.mp3");
	m_SoundPath[SoundSE13].assign("resource/sound/SE/Title_Mogll_In.mp3");
	m_SoundPath[SoundSE14].assign("resource/sound/SE/Title_Rockbreak.mp3");
	m_SoundPath[SoundSE15].assign("resource/sound/SE/Title_Stonebreak.mp3");
	m_SoundPath[SoundSE16].assign("resource/sound/SE/Damage.mp3");
	m_SoundPath[SoundSE17].assign("resource/sound/SE/PandoraPOP.mp3");
	m_SoundPath[SoundSE18].assign("resource/sound/SE/Unit_Set.mp3");
	m_SoundPath[SoundSE19].assign("resource/sound/SE/Unit_Select..mp3");
	m_SoundPath[SoundSE20].assign("resource/sound/SE/Unit_Go.mp3");
	m_SoundPath[SoundSE21].assign("resource/sound/SE/Kurayami.mp3");
	m_SoundPath[SoundSE22].assign("resource/sound/SE/Break_Fossil.mp3");
	m_SoundPath[SoundSE23].assign("resource/sound/SE/Fire.mp3");
	m_SoundPath[SoundSE24].assign("resource/sound/SE/Heel.mp3");
	m_SoundPath[SoundSE25].assign("resource/sound/SE/Break_Rock.mp3");
	m_SoundPath[SoundSE26].assign("resource/sound/SE/Status_UP.mp3");
	m_SoundPath[SoundSE27].assign("resource/sound/SE/Dig.mp3");
	m_SoundPath[SoundSE28].assign("resource/sound/SE/Decide.mp3");
	m_SoundPath[SoundSE29].assign("resource/sound/SE/Fall.mp3");
	m_SoundPath[SoundSE30].assign("resource/sound/SE/Select.mp3");
	m_SoundPath[SoundSE31].assign("resource/sound/SE/Confu.mp3");
	m_SoundPath[SoundSE32].assign("resource/sound/SE/Sandbreak.mp3");
	m_SoundPath[SoundSE33].assign("resource/sound/SE/Death.mp3");
	m_SoundPath[SoundSE34].assign("resource/sound/SE/Get_Resource.mp3");
	m_SoundPath[SoundSE35].assign("resource/sound/SE/No_Resource.mp3");
	m_SoundPath[SoundSE36].assign("resource/sound/SE/Status_DOWN.mp3");
	m_SoundPath[SoundSE37].assign("resource/sound/SE/Alarm.mp3");
	m_SoundPath[SoundSE38].assign("resource/sound/SE/Equip.mp3");
	m_SoundPath[SoundSE39].assign("resource/sound/SE/Landing.mp3");
	m_SoundPath[SoundSE40].assign("resource/sound/SE/Stop.mp3");
	m_SoundPath[SoundSE41].assign("resource/sound/SE/Enemy_POP.mp3");
	m_SoundPath[SoundSE42].assign("resource/sound/SE/Enemy_Break.mp3");
	m_SoundPath[SoundSE43].assign("resource/sound/SE/Electric.mp3");
	m_SoundPath[SoundSE44].assign("resource/sound/SE/Electric_Damege.mp3");
	m_SoundPath[SoundSE45].assign("resource/sound/SE/Freeze.mp3");
	m_SoundPath[SoundSE46].assign("resource/sound/SE/Claybreak.mp3");
	m_SoundPath[SoundSE47].assign("resource/sound/SE/No_break.mp3");
	m_SoundPath[SoundSE48].assign("resource/sound/SE/Explosion.mp3");
	m_SoundPath[SoundSE49].assign("resource/sound/SE/Treasure.mp3");
	m_SoundPath[SoundSE50].assign("resource/sound/SE/Flyout.mp3");
	m_SoundPath[SoundSE51].assign("resource/sound/SE/Icebreak.mp3");
	m_SoundPath[SoundSE52].assign("resource/sound/SE/Cannon.mp3");
	m_SoundPath[SoundSE53].assign("resource/sound/SE/Mahi.mp3");
	m_SoundPath[SoundSE54].assign("resource/sound/SE/Cracker.mp3");
	m_SoundPath[SoundSE55].assign("resource/sound/SE/Mogll_Landing.mp3");
	m_SoundPath[SoundSE56].assign("resource/sound/SE/Magma_In.mp3");
	m_SoundPath[SoundSE57].assign("resource/sound/SE/Water_In.mp3");
}

DataManager::~DataManager(void)
{
}

void DataManager::SetMaptipData(GraphicGroupData *data, char *filePath, int allNum, int numX, int numY, int width, int height)
{
	// 分割画像のパス登録
	data->allNum = allNum;
	data->numX = numX;
	data->numY = numY;
	data->width = width;
	data->height = height;
	data->path.assign(filePath);
	data->handle =
		new int[data->allNum];
	for(int i = 0; i < data->allNum; i++)
	{
		data->handle[i] = UNDEFINE;
	}
}

void DataManager::Load(ResourceSet set)
{
	BoolArray graph, sound, graphG;
	switch(set)
	{
	case ResourceSetTitle:
		SetTitle(&graph, &sound, &graphG);
		break;
	case ResourceSetStageSelect:
		SetStageSelect(&graph, &sound, &graphG);
		break;
	case ResourceSetPlay:
		SetPlay(&graph, &sound, &graphG);
		break;
	default:
		Release();
		return;
	}
	// 画像の必要分ロードと不要分のアンロード
	for(unsigned int i = 0; i < GraphicMax; i++)
	{
		if(graph.Get(i))
		{
			if(m_GraphicHandle[i] == UNDEFINE)
			{
				m_GraphicHandle[i] = LoadGraph(m_GraphicPath[i].c_str());
			}
		}
		else
		{
			if(m_GraphicHandle[i] != UNDEFINE)
			{
				DeleteGraph(m_GraphicHandle[i]);
				m_GraphicHandle[i] = UNDEFINE;
			}
		}
	}
	// 分割画像の必要分ロードと不要分のアンロード
	for(unsigned int i = 0; i < GraphicGroupMax; i++)
	{
		if(graphG.Get(i))
		{
			if(m_GraphicGroupData[i].handle[0] == UNDEFINE)
			{
				LoadDivGraph(m_GraphicGroupData[i].path.c_str(),
					m_GraphicGroupData[i].allNum,
					m_GraphicGroupData[i].numX,
					m_GraphicGroupData[i].numY,
					m_GraphicGroupData[i].width,
					m_GraphicGroupData[i].height,
					m_GraphicGroupData[i].handle);
			}
		}
		else
		{
			if(m_GraphicGroupData[i].handle[0] != UNDEFINE)
			{
				for(int j = 0; j < m_GraphicGroupData[i].allNum; j++)
				{
					DeleteGraph(m_GraphicGroupData[i].handle[j]);
					m_GraphicGroupData[i].handle[j] = UNDEFINE;
				}
			}
		}
	}
	// 音楽の必要分ロードと不要分のアンロード
	for(unsigned int i = 0; i < SoundMax; i++)
	{
		if(sound.Get(i))
		{
			if(m_SoundHandle[i] == UNDEFINE)
			{
				m_SoundHandle[i] = LoadSoundMem(m_SoundPath[i].c_str());
			}
			// 音楽が前シーンで再生中の可能性があるのでチェックして止める
			else if( CheckSoundMem( m_SoundHandle[i] == 1 ) && i < SoundSE01)
			{
				StopSoundMem( m_SoundHandle[i] );
			}
		}
		else
		{
			if(m_SoundHandle[i] != UNDEFINE)
			{
				DeleteSoundMem(m_SoundHandle[i]);
				m_SoundHandle[i] = UNDEFINE;
			}
		}
	}
}

void DataManager::Release(void)
{
	InitSoundMem();
	InitGraph();
	m_ResourceID = ResourceSetNone;
	memset(m_GraphicHandle, UNDEFINE, sizeof(m_GraphicHandle));
	memset(m_SoundHandle, UNDEFINE, sizeof(m_SoundHandle));
}

void DataManager::MemRelease(void)
{
	for(int i = 0; i < GraphicGroupMax; i++)
	{
		delete m_GraphicGroupData[i].handle;
	}
}
int DataManager::Get(GraphicSet graph)
{
	if(m_GraphicHandle[graph] == UNDEFINE)
	{
		m_GraphicHandle[graph] = LoadGraph(m_GraphicPath[graph].c_str());
	}
	return m_GraphicHandle[graph];
}

int DataManager::Get(SoundSet sound)
{
	if(m_SoundHandle[sound] == UNDEFINE)
	{
		m_SoundHandle[sound] = LoadSoundMem(m_SoundPath[sound].c_str());
	}
	return m_SoundHandle[sound];
}

int DataManager::Get(GraphicGroupIndex graphIdx)
{
	return GetGraphicGroupData(graphIdx);
}

int DataManager::GetGraphicGroupData(int index)
{
	int sum = 0;
	for(unsigned int i = 0; i < GraphicGroupMax; i++)
	{
		if(sum + m_GraphicGroupData[i].allNum > index)
		{
			if(m_GraphicGroupData[i].handle[0] == UNDEFINE)
			{
				LoadDivGraph(m_GraphicGroupData[i].path.c_str(),
					m_GraphicGroupData[i].allNum,
					m_GraphicGroupData[i].numX,
					m_GraphicGroupData[i].numY,
					m_GraphicGroupData[i].width,
					m_GraphicGroupData[i].height,
					m_GraphicGroupData[i].handle);
			}
			return m_GraphicGroupData[i].handle[index - sum];
		}
		sum += m_GraphicGroupData[i].allNum;
	}
	return -1;
}

void DataManager::SaveData(void)
{
	FILE* fp;
	fopen_s( &fp, "save.dat" , "wb" );
	fwrite( &m_SaveData , sizeof( StoreData ), 1, fp );
	fclose( fp );
}

void DataManager::LoadData(char *filePath)
{
	FILE* fp;
	// システムデータも読み込む
	if(fopen_s(&fp, "resource/data/system.dat", "rb") != 0)
	{
		printfDx("Systemファイルがありません\n");
	}
	else
	{
		fread( &m_SystemData , sizeof( GameSystemData ), 1, fp );
		fclose(fp);
	}
	// セーブデータ読み込み
	if(fopen_s(&fp, filePath, "rb") != 0)
	{
		// ファイルが無かった時の処理
		memset(&m_SaveData, 0, sizeof(StoreData));
		m_SaveData.header[0] = 'S';
		m_SaveData.header[1] = 'A';
		m_SaveData.header[2] = 'V';
		m_SaveData.header[3] = 'E';

		//すべてのユニットを持っている
		for(int i = 0;i<30;i++){
			m_SaveData.unitStatus[i] = DataManager::ITEM_NO_EXIST;
		}
		//すべての装備品を持っている
		for(int i = 0;i<60;i++){
			m_SaveData.itemStatus[i] = DataManager::ITEM_NO_EXIST;
		}

		//装備中アイテムの設定
		m_SaveData.equipItem[0] = -1;
		m_SaveData.equipItem[1] = -1;
		m_SaveData.equipItem[2] = -1;

		//ユニットのステータスの設定
		m_SaveData.unitStatus[SORT_UnitIconSortList[0]] = DataManager::ITEM_EQUIP;
		m_SaveData.unitStatus[SORT_UnitIconSortList[1]] = DataManager::ITEM_EQUIP;
		m_SaveData.unitStatus[SORT_UnitIconSortList[2]] = DataManager::ITEM_EQUIP;

		//装備中ユニットの設定
		m_SaveData.equipUnit[0] = SORT_UnitIconSortList[0];
		m_SaveData.equipUnit[1] = SORT_UnitIconSortList[1];
		m_SaveData.equipUnit[2] = SORT_UnitIconSortList[2];
		m_SaveData.equipUnit[3] = -1;
		m_SaveData.equipUnit[4] = -1;
		m_SaveData.equipUnit[5] = -1;
		// ステージデータの初期化
		for(int i=1; i<5; i++)	m_SaveData.stageDepth[i] = -1;

		SaveData();
	}
	else
	{
		// セーブデータを読み出し
		fread( &m_SaveData , sizeof( StoreData ), 1, fp );
		fclose(fp);
	}
}

// 読み込むデータの定義
void DataManager::SetTitle(BoolArray *graph, BoolArray *sound, BoolArray *maptip)
{
	sound->Set(SoundBGM01, true );
}

void DataManager::SetPlay(BoolArray *graph, BoolArray *sound, BoolArray *maptip)
{
	switch( DataManager::GetInstance().m_SceneInt["StageNo"] )
	{
	case 1:
		sound->Set(SoundBGM05, true );
		break;
	case 2:
		sound->Set(SoundBGM06, true );
		break;
	case 3:
		sound->Set(SoundBGM07, true );
		break;
	case 4:
		sound->Set(SoundBGM08, true );
		break;
	default:
		sound->Set(SoundBGM04, true );
		break;
	}
	sound->Set(SoundBGM09, true );
	sound->Set(SoundBGM10, true );
	sound->Set(SoundSE02, true );
	sound->Set(SoundSE06, true );
	sound->Set(SoundSE10, true );
	sound->Set(SoundSE16, true );
	sound->Set(SoundSE18, true );
	sound->Set(SoundSE19, true );
	sound->Set(SoundSE20, true );
	sound->Set(SoundSE27, true );
	//sound->Set(SoundSE28, true );
}

void DataManager::SetStageSelect(BoolArray *graph, BoolArray *sound, BoolArray *maptip)
{
	sound->Set(SoundBGM02, true );
	sound->Set(SoundSE08, true );
	sound->Set(SoundSE11, true );
	sound->Set(SoundSE12, true );
}