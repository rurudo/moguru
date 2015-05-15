//------------------------------------------------------------------------
//	Struct
//------------------------------------------------------------------------
typedef struct IdData{
	int x,y,z;
}IdData;

typedef struct EquipData{
	IdData			id;			//どのアイコンかの番号
	char			type;		//装備かユニットか
}EquipData;

typedef struct TreeData{
	int				id;			//どのアイコンかの番号
	char			type;		//装備かユニットか
}TreeData;