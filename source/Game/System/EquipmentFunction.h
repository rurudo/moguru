#pragma once
#include "../Unit/UnitBase.h"
// ユニットの消費コスト削減
int EquipmentFunction_01( int value );
// 10フレームに1回復
void EquipmentFunction_02( int frame );
// 最大資源値上昇
void EquipmentFunction_03( void );
// ユニット犠牲
int EquipmentFunction_04( int );
// モグルがブロックから受けるダメージを減少
int EquipmentFunction_05( int value );
// スロウ地形の効果をユニットが受けない
float EquipmentFunction_06( float value );
// 取得資源が多くなる
int EquipmentFunction_07( int value );
// ユニットの与えるダメージが増加する
int EquipmentFunction_08( int value );
// ユニットのレンジ増加
float EquipmentFunction_09( float value );
// 全てのユニットが宝特攻を得る
bool EquipmentFunction_10( void );
// 石等を掘った時のダメージが減る
int EquipmentFunction_11( int value );
// 状態異常を治りやすくする
float EquipmentFunction_12( float value );
// 資源が自動でたまっていく
void EquipmentFunction_13( int frame );
// 敵の攻撃のダメージを無効にするが資源が減っていく
int EquipmentFunction_14( int value);
void EquipmentFunction_14_Dec( int frame );
// 自ユニットの攻撃が敵とブロックに当たるようになる
bool EquipmentFunction_15( void );
// 自ユニットが仲間割れをするようになるが攻撃がかなり増加
bool EquipmentFunction_16( void );
int EquipmentFunction_16_Value( int );	// 上昇値
// ブロックに対して攻撃力増加、敵に対してはダウン
int EquipmentFunction_17_Block( int );
int EquipmentFunction_17_Enemy( int );
// 敵に対して攻撃力増加、ブロックに対してはダウン
int EquipmentFunction_18_Block( int );
int EquipmentFunction_18_Enemy( int );
// 混乱にならない
float EquipmentFunction_19( float value, bool isEnemy );
// 攻撃力を増加させるが自分にもダメージ
int EquipmentFunction_20( int power, int *hp);
// ユニット攻撃にレンジ減少を付加
void EquipmentFunction_21( int *type, float *time, float *value);
// ユニット攻撃に麻痺を付加
void EquipmentFunction_22( int *type, float *time);
// ユニット攻撃に凍結を付加
void EquipmentFunction_23( int *type, float *time);
// ユニット攻撃に燃焼を付加
void EquipmentFunction_24( int *type, float *time, float *value);
// ユニット攻撃に混乱を付加
void EquipmentFunction_25( int *type, float *time);
// 100以下のダメージを半減する
int EquipmentFunction_26( int );
// 状態異常の効果を増幅させる
void EquipmentFunction_27( int *type, float *time, float *value1, float *value2);
// トラップブロックを見破れる
bool EquipmentFunction_28( void );
// 敵の攻撃頻度を減少させる
float EquipmentFunction_29( float value );
// 敵の攻撃力を下げる
int EquipmentFunction_30( int value );
// ユニット攻撃に攻撃頻度減少を付与する
void EquipmentFunction_31( int *type, float *time, float *value);
// レンジを縮めて攻撃力をあげる
void EquipmentFunction_32( int *attack, float *range);
// 一定時間毎にユニットが回復する
void EquipmentFunction_33( int frame );
// 指定地点に味方を誘導する
void EquipmentFunction_34( float x, float y );
// 掘るのが遅くなる
bool EquipmentFunction_35( int frame );
// 自ユニットの攻撃頻度を上げる
float EquipmentFunction_36( float value );
// 地形に与えるダメージ増加
int EquipmentFunction_37( int value );
// モグルが敵から受けるダメージを減少する
int EquipmentFunction_38( int value );
// ユニットの受けるダメージを減少する
int EquipmentFunction_39( int value );
// 落ちるのが速くなる
float EquipmentFunction_40( float value );
// 味方が爆発する
void EquipmentFunction_41( UnitBase* base );
// ユニットの移動速度を上昇
float EquipmentFunction_42( float value );
// 止まってた味方を誘導する
void EquipmentFunction_43( float x, float y );
// モグルからレンジaの敵の速度をb%にする
void EquipmentFunction_44( int frame );
// モグルへのダメージが定数になる
int EquipmentFunction_45( int value );
// 掘るのが遅くなる
bool EquipmentFunction_46( void );
// 普段資源にならないブロックからも資源を得る
int EquipmentFunction_47( int value );
// ユニットの画面に留まる時間が長くなる
void EquipmentFunction_48( int frame );
// ユニットを自動で出す
void EquipmentFunction_49( int frame );
// 敵がいない状態だと資源と耐久値を回復
void EquipmentFunction_50( int frame );
// ユニット攻撃にスロウを付加
void EquipmentFunction_51( int *type, float *time, float *value);
// 敵が爆発する
void EquipmentFunction_52( UnitBase* base );
// 敵撃破時にライフ回復
void EquipmentFunction_53( void );
// メインユニットが弾を撃つ
void EquipmentFunction_54( int frame );
// ユニット攻撃にノックバックを付与
void EquipmentFunction_55( int *type, float *time, float *x, float *y,
	float dx, float dy);
// モグルがブロックから受けるダメージを減少
int EquipmentFunction_56( int value );
// 瞬時に指定ポイントへユニットを召喚する
bool EquipmentFunction_57( void );
// 一定時間毎にユニットの周辺にダメージ
void EquipmentFunction_58( int frame );
// 一定時間毎に全てのユニットにダメージ
void EquipmentFunction_59( int frame );
// 常にリソースが9999
void EquipmentFunction_60( void );