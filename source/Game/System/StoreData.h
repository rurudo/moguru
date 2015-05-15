#pragma once

// セーブデータ
struct StoreData
{
	char header[32];				// ヘッダー
	char itemStatus[60];			// 装備の所持、未所持、未発見、装備等のステータス
	char unitStatus[30];			// ユニットの所持、未所持、未発見、装備等のステータス
	char stageItemStatus[51];		// 各ステージの宝取得状況
	int stageDepth[5];				// 各ステージの最大深度
	int equipItem[3];				// 装着中の装備
	int equipUnit[6];				// 装着中のユニット
	int playFrame;					// プレイ時間（フレーム単位）
	bool challengeFlag[100];		// チャレンジ項目達成フラグ
};