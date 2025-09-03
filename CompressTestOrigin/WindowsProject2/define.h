#pragma once

// Mgr 클래스들은 프로그램이 실행되는 동안에 하나만 존재해야 하기 때문에
// 싱글톤 패턴을 쓰기 쉽게 전처리기로 만들어 두었습니다
#define SINGLE(type) public:\
					 static type* GetInstance()\
					{\
						static type mgr;\
						return &mgr;\
					}\
					 private:\
						type(); \
						~type();

// 원형의 파이 입니다
const double PI = -3.1415926535;

const int BOARD_TILE = 120;
const int BOARD_SIZE_COL = 13;
const int BOARD_SIZE_ROW = 9;
const int BOARD_PENDING = 3;


// Object 타입입니다. 
// Object 를 추가할 경우에 여기에 Type도 추가해주어야 합니다.
enum class GROUP_TYPE
{
	DEFAULT,				// 기본
	BACKGROUND,
	TILE,					// 타일 ( 추가 : 이건재 )
	TILE_APPERENCE,
	MONSTER,				// 몬스터
	MONSTER_ABSOLUTE,		// 절대적 몬스터
	PROJ_PLAYER,			// 플레이어 투사체
	PROJ_MONSTER,			// 몬스터 투사체
	PROJ_MONSTER_ABLSOLUTE,	// 절대적 몬스터 투사체
	TRAP_FIRE,				// 함정 ( 불 )
	TRAP_ARROW,				// 함정 ( 화살 )
	RELICS,					// 유물
	LEVER,					// 레버
	DOOR,					// 문
	PLAYER,					// 플레이어
	PANEL_UI ,


	Event_UI = 30,
	UI = 31,
	END = 32,
};

// Scene 타입입니다.
// Scene 을 추가할 경우에 여기에 Type도 추가해주어야 합니다.
enum class SCENE_TYPE
{
	TITLE,			// 시작창
	TOOL,				// 툴 맵
	TEST,
	SELCETMAP,
	CUTSCENE,
	START,				// 스타트 맵

	STAGE_1_1,			
	STAGE_1_2,		
	STAGE_1_3,
	STAGE_1_5,
	STAGE_1_6,
	STAGE_1_7,
	STAGE_1_8,

	STAGE_2_1,
	STAGE_2_2,
	STAGE_2_3,
	STAGE_2_4,
	STAGE_2_5,
	STAGE_2_6,

	STAGE_3_1,
	STAGE_3_2,

	STAGE_END,

	ENDING,
	CREDIT,
	END,
};

// 브러쉬 타입입니다.
enum class BRUSH_TYPE
{
	HOLLOW,
	RED,
	END,
};

// 펜 타입입니다
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	BLACK,
	WHITE,
	PUPLE,
	YELLOW,
	ORENGE,
	END,
};

// 이벤트 타입입니다.
// 이벤트를 추가할 경우에 여기에 TYPE도 추가해 주어야 합니다.
enum class EVENT_TYPE
{
	CREATE_OBJECT,		// 오브젝트 생성될 때,
	DELETE_OBJECT,		// 오브젝트 삭제될 때
	SCENE_CHANGE,		// 씬이 종료될 때
	SCENE_SWAP,
	TRIGGER_ON,			// 트리거가 발생할 때
	LEVERTRIGGER_ON,	// 레버 트리거가 발생할 때

	END
};

enum class OBJECT_DIR
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};

// 타일 타입에 따라 콜리전 처리
enum class TILE_TYPE
{
	MOVABLE = 0,
	WALL,
	FATAL,
	TRAP,
	POSION,
	FIRE,
	SCENE_CHANGE,
	TRIGGER,
	END,
	TRIGGER_FATAL,
	TRIGGER_MOVABLE,
};

enum class MONSTER_STATE
{
	IDLE,
	CHASE,
	DELAY,
	STUN
};

enum class DRAIN_STATE
{
	DRAIN1,
	DRAIN2,
	DRAIN3,
};